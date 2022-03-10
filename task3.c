#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char *argv[]){

	if (argc != 2) {
		fprintf(stderr,"Invalid number of parameters\n");
		return 0;
	}

	const int StopSymbol = 6;
	int fd;
	if (fd = open(argv[1], O_WRONLY | O_CREAT, 0644)) 
	{
		FILE* fp;
		if (fp = fdopen(fd, "w")) 
		{
			int c;
			while ((c = getchar()) != StopSymbol) 
			{
				if (putc(c, fp)==EOF) 
					fprintf(stderr,"Error writing a character");
			}
	
		}	
		else
			fprintf(stderr,"Error opening file");
		if (fclose(fp)) 
			fprintf(stderr,"Error closing file");
	}	
	else
		fprintf(stderr,"Error opening file");
		
	return 0;
}
