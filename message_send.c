#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/msg.h>
#include "message_queue.h"

static void usageError(const char* progName, const char* msg){
	if(msg != NULL) {
		fprintf(stderr, "%s", msg);
	}
	
	fprintf(stderr, "Usage: %s [-n] msqid msg-type [msg-text]\n", progName);
	fprintf(stderr, "-n Use IPC_NOWAIT flag\n");
	
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]){
	int msqid, flags, msgLen;
	int opt; /* Option character from getopt() */
	struct mbuf msg; /* Message Buffer for msgsnd */
	
	/* Parse command-line options and arguments*/
	flags = 0;
	
	while((opt = getopt(argc, argv, "n")) != -1) {
		if(opt == 'n'){
			flags |= IPC_NOWAIT;
		} else {
			usageError(argv[0], NULL);
		}
	}
	
	if(argc < optind + 2 || argc > optind + 3) {
		usageError(argv[0], "Wrong number of arguments\n");
	}
	
	msqid = atoi(argv[optind]);
	msg.mtype = atoi(argv[optind+1]);
	
	if(argc > optind + 2){ /* 'msg-text' was supplied*/
		msgLen = strlen(argv[optind + 2]) + 1;
		
		if(msgLen > MAX_MTEXT) {
			fprintf(stderr, "Command-line usage error: msg-txt too long (max: %d characters) \n", MAX_MTEXT);
		}
		
		memcpy(msg.mtext, argv[optind+2], msgLen);
		
	} else { /* No 'msg-text' ==> zero-length msg */
		msgLen = 0;
	}
	
	/* Send Message*/

	if(msgsnd(msqid, &msg, msgLen, flags) == -1) {
		fprintf(stderr, "msgsnd error");
		exit(EXIT_FAILURE);
	}
	
	exit(EXIT_SUCCESS);
}
