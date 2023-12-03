#define _GNU_SOURCE /* Get definition of MSG_EXCEPT */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/msg.h>
#include "message_queue.h"

static void usageError(const char* progName, const char* msg){
	
	if(msg != NULL) {
		fprintf(stderr, "%s", msg);
	}
	
	fprintf(stderr, "Usage: %s [options] msqid [max-bytes]\n, progName");
	fprintf(stderr, "Permitted options are:\n");
	fprintf(stderr, " -e Use MSG_NOERROR flag\n");
	fprintf(stderr, " -t type Select message of given type\n");
	fprintf(stderr, " -n Use IPC_NOWAIT flag\n");

	
	#ifdef MSG_EXCEPT /* Depends on _GNU_SOURCE */
		fprintf(stderr, " -x Usae MSG_EXCEPT flag\n");
	#endif

	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]){
	int msqid, flags, type;
	struct mbuf msg; /* Message buffer for msgrcv() */
	ssize_t msgLen;
	size_t maxBytes;
	int opt; /* Option character from getopt() */
	
	/* Parse Command-line Options and arguments */
	flags = 0;
	type = 0;
	
	while((opt = getopt(argc, argv, "ent:x")) != -1) {
		switch (opt) {
			case 'e':
				flags |= MSG_NOERROR;
				break;
			case 'n':
				flags |= IPC_NOWAIT;
				break;
			case 't':
				type = atoi(optarg);
				break;
			#ifdef MSG_EXCEPT
			case 'x':
				flags |= MSG_EXCEPT;
				break;
			#endif
			default: 
				usageError(argv[0], NULL);
				break;
		}
	}
	
	if(argc < optind + 1 || argc > optind + 2) {
		usageError(argv[0], "Wrong number of arguments\n");
	}
	
	msqid = atoi(argv[optind]);
	maxBytes = (argc > optind + 1) ? atoi(argv[optind + 1]) : MAX_MTEXT;
	/* Get message and display on stdout */
	msgLen = msgrcv(msqid, &msg, maxBytes, type, flags);
	
	if (msgLen == -1) {
		switch (errno)
		{
		    case E2BIG:
		        fprintf(
		            stderr,
		            "The value of mtext is greater than msgsz and the flag MSG_NOERROR was not specified.\n"
		        );
		        break;
		    case EACCES:
		        fprintf(
		            stderr,
		            "The calling process does not have read permission "
		            "to the message queue associated with the message queue identifier msgid.\n"
		        );
		        break;
		    case EIDRM:
		        fprintf(
		            stderr,
		            "The message queue identifier, msgid, has been removed "
		            "from the system while the caller of msgrcv() was waiting.\n"
		        );
		        break;
		    case EINVAL:
		        fprintf(
		            stderr,
		            "The value of argument msgid is not a valid message queue identifier "
		            "or the value of msgsz is less than zero.\n"
		        );
		        break;
		    case ENOMSG:
		        fprintf(
		            stderr,
		            "The flag IPC_NOWAIT was specified and the message queue "
		            "does not contain a message of the desired type.\n"
		        );
		        break;
		    default:
		        break;
		}

        	exit(EXIT_FAILURE);
    	}
	
	printf("Received: type='%ld'; length='%ld' ", msg.mtype, (long) msgLen);
	
	if (msgLen > 0) {
        	printf("; body=%s", msg.mtext);
    	}
    	
    	printf("\n");
    	exit(EXIT_SUCCESS);
}
