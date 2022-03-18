#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
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

int main(int argc, char *argv[]){

	if (argc != 3) {
		fprintf(stderr,"Invalid number of parameters\n");
		return 0;
	}
	int N;
	if ((N = atoi(argv[2]))==0) {
		fprintf(stderr,"Invalid parameter 2\n");
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
