#define _GNU_SOURCE
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

int searchdir(char *name);

int maxsize=0;
int minsize=0;
char* mindate;
char* maxdate;
struct tm mintime, maxtime;
time_t mind, maxd;

FILE *f1;

int main(int argc, char *argv[])
{
	if (argc != 7) {
		fprintf(stderr,"Invalid number of parameters\n");
		return 0;
	}	
	maxsize=atoi(argv[4]);	
	minsize=atoi(argv[3]);
	maxdate=argv[6];
	mindate=argv[5];
	if (f1=fopen(argv[2],"w"))
	{
		strptime(mindate, "%Y-%m-%d", &mintime);
		strptime(maxdate, "%Y-%m-%d", &maxtime);
		mind= mktime(&mintime);
		maxd = mktime(&maxtime);
		searchdir(argv[1]);
		
		fclose(f1);
		return 0;
	}
	else
	{
		fprintf(stderr,"Error opening file\n");
		return 0;
	}
}

int searchdir(char *name)
{
	char dirname[256];
	char newname[256];
	DIR *d1;
	struct dirent *d;
	struct stat st1;
	if ((d1=opendir(name)) == NULL)
     {
        fprintf(stderr, "\nCouldn't Open directory!\n");
        return 0;
     }
	
	d=readdir(d1);
	
	strcpy(dirname,name);
	strcat(dirname,"/");
	
	while (d!=NULL)
	{
	if (d->d_type == DT_DIR)
	{
		if ((strcmp(d->d_name,".")!=0)&&(strcmp(d->d_name,"..")!=0))
		{
		strcpy(newname,dirname);
		strcat(newname,d->d_name);
		
		searchdir(newname);
		}
	}
	d=readdir(d1);
 }
 
 rewinddir(d1);
 while ((d=readdir(d1))!=0)
 {
   if (d->d_type==DT_REG)
   {
		strcpy(newname,name);
		strcat(newname,d->d_name);
     
     stat(newname,&st1);
	 char* path = realpath(newname, NULL);
     if (((st1.st_size)>=minsize)&&((st1.st_size)<=maxsize))
     {
       if (((st1.st_mtime)>=mind)&&((st1.st_mtime)<=maxd))
       {
		   if (fprintf(f1,"%s  %ld  %s\n",path,st1.st_size,ctime(&st1.st_mtime))<0)
		   {
			   	fprintf(stderr, "\nCannot write to file!\n");
		   }
			
			printf("%s  %ld  %s\n",path,st1.st_size,ctime(&st1.st_mtime));
       }
     }
   }
   d=readdir(d1);
 }
 closedir(d1);
}
