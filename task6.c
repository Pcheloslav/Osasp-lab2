#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>


void readDir(char* dir) {
	DIR *dirp;
	if ((dirp = opendir(dir))==NULL) {
		fprintf(stderr,"Error opening directory\n");
		return;
	}
	struct dirent *rddir;
	while ((rddir = readdir(dirp))!=NULL) {
		printf("%s\n", rddir->d_name);
	}
	if (closedir(dirp)==-1)
		perror("closedir(dirp) ");
	return;
}

int main(void){
	char dir[1024];
	getcwd(dir, 1024);
	readDir(dir);
	readDir("/");
	return 0;	
}
