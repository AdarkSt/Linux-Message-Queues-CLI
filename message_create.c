#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/msg.h>
#include <sys/stat.h>

static void usageError(char* progName, char* msg){
	if(msg != NULL){
		fprintf(stderr, "%s" ,msg);
	}
	
	fprintf(stderr, "Usage: %s [-cx] {-f pathname | -k key | -p} [octal-perms]\n", progName);
	fprintf(stderr, "-c Use IPC_CREATE flag\n");
	fprintf(stderr, "-x Use IPC_EXCL flag\n");
	fprintf(stderr, "-f Use pathname to Generate key using ftok()\n");
	fprintf(stderr, "-k key Use key as key\n");
	fprintf(stderr, "-p Use IPC_PRIVATE key\n");
	exit(EXIT_FAILURE);
}	

int getInt(const char* arg){
	long res;
	char* endptr;
	int base = 8;
	res = strtol(arg, &endptr, base);
	return (int) res;
}

int main(int argc, char *argv[]){
	int numKeyFlags; /* Counts -f, -k, and -p options */
	int flags, msqid, opt;
	unsigned int perms;
	long lkey;
	key_t key;
	
	/* Parse command-line options and arguments*/
	numKeyFlags = 0;
	flags = 0;
	
	while ((opt = getopt(argc, argv, "cf:k:px")) != -1){
		switch (opt) {
		case 'c':
			flags |= IPC_CREAT;
			break;
		case 'f':
			key = ftok(optarg, 1);
			
			if(key == -1) {
				exit(EXIT_FAILURE);
			}
			
			numKeyFlags++;
			break;
		case 'k':
			if(sscanf(optarg, "%li", &lkey) != 1){
				fprintf(stderr, "Command-line usage error: -k option requires a numeric argument\n");
			}
			
			key = lkey;
			numKeyFlags++;
			break;
		case 'p':
			key = IPC_PRIVATE;
			numKeyFlags++;
			break;
		case 'x':
			flags |= IPC_EXCL;
			break;
		default:
			usageError(argv[0], "Bad option\n");
		}
	}
		
	if(numKeyFlags != 1) {
		usageError(argv[0], "Exactly one of the options -f, -k, -p must be supplied\n");
	}
	
	perms = (optind == argc) ? (S_IRUSR | S_IWUSR) : getInt(argv[optind]);
	msqid = msgget(key, flags | perms);
	
	if (msqid == -1) {
		switch (errno)
		{
			case EEXIST:
				printf(
					"IPC_CREATE and IPC_EXCL were specified in msgflag, "
					"but a message queue already exists for key.\n"
				);
				break;
			case ENOENT:
				printf("No message queue exists for key and msgflg did not specify IPC_CREAT.\n");
				break;
			default:
				break;
		}
		
		exit(EXIT_FAILURE);
	}
	
	printf("%d\n", msqid);
	exit(EXIT_SUCCESS);
}
