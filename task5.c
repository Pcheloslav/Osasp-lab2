#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[]){

	if (argc !=3)
  {
		fprintf(stderr,"Invalid number of parameters\nfuncname dest src\n");
		return 0;
	}
	int fdsrc;
	if ((fdsrc = open(argv[2], O_RDONLY))==0)
	{
		perror("open(src) :");
		return 0;
	}
		
	int fddest;
	if ((fddest = open(argv[1], O_WRONLY | O_CREAT))==0) 
	{
		perror("open(dest) ");	
		return 0;
	}
					
	FILE *fpsrc;
	if ((fpsrc = fdopen(fdsrc, "r"))==0) {
		perror("fdopen(src) ");
		return 0;
	}
	
	FILE *fpdest;
	if ((fpdest = fdopen(fddest, "w"))==0) 
	{
		perror("fdopen(dest) ");
		return 0;
	}
	
	int c;
	while ((c = getc(fpsrc))!=EOF)
		putc(c, fpdest);
			
	struct stat buf;
	if (fstat(fdsrc,&buf)==-1) 
	{
		perror("fstat(src) ");
		return 0;
	}
	else if (fchmod(fddest,buf.st_mode)==-1) 
	{
		perror("fchmod(desr) ");
		return 0;
	}
	
	if (fclose(fpsrc)!=0) 
		perror("fclose(src) ");
	if (fclose(fpdest)!=0)
		perror("fclose(dest) ");	

	return 0;
}
