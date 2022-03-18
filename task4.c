#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>


int print(FILE* fp) {
	int c = getc(fp);
	while (c!=EOF && c!='\n') {
		if (putc(c,stdout)==EOF) 
			fprintf(stderr,"Cannot write a character\n");
		c = getc(fp);
	}
	if (c!=EOF)
		putc(c,stdout);
	return c;
}

long validateInp(char* Inp)
{
    char *endptr;
    long res = strtol(Inp, &endptr, 10);

    if ((errno == ERANGE && (res == LONG_MAX || res == LONG_MIN)) || (errno != 0 && res == 0)) {
       perror("strtol");
       return -1;
    }

    if (endptr == Inp) {
       fprintf(stderr, "Second parameter should have int value\n");
       return -1;
    }

    return res;
}

int main(int argc, char *argv[]){

	if (argc != 3) {
		fprintf(stderr,"Invalid number of parameters\n");
		return 0;
	}
	long N;
	if ((N = validateInp(argv[2]))==-1) {
		return 0;
	}
	
	int fd;	
	if (fd = open(argv[1], O_RDONLY)) { 
		
		FILE *fp;
		if (fp = fdopen(fd,"r")) {
			int line = 0, c = 0;	
			for (int line = 0; c!=EOF; ) {
				c = print(fp);
				if (c=='\n') 
					line++;
				if (line >= N &&  N!=0 ) {
					getc(stdin);
					line = 0;
				}
			}
		}
		else {
			fprintf(stderr,"Error opening file\n");
			return 0;
		}
		if (fclose(fp)!=0) {
			fprintf(stderr,"Error closing file\n");
			return 0;
		}
	}	
	else
	{
		fprintf(stderr,"Error opening file\n");
		return 0;
	}
	return 0;
}
