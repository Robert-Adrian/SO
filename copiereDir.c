#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

void copiere(char *src, char *dest) {
 struct stat buf;
 struct stat fileBuf;
 struct dirent *entry;
 DIR *dir1 = opendir(src);
 DIR *dir2 = opendir(dest);
 char pathSrc[1000], pathDest[1000];

 
 if (dir1 == NULL)
	return;

 stat(src, &fileBuf);

 while ((entry = readdir(dir1)) != NULL) {
	stat(entry->d_name, &buf);
	
	if (dir2 == NULL) {
		mkdir(dest, fileBuf.st_mode);
		
	}

	chmod(dest, fileBuf.st_mode);
	
	if (S_ISDIR(buf.st_mode) && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
		
		strcpy(pathSrc, src);
		strcat(pathSrc, "/");
		strcat(pathSrc, entry->d_name);

		strcpy(pathDest, dest);
		strcat(pathDest, "/");
		strcat(pathDest, entry->d_name);
		copiere(pathSrc, pathDest);
	} else if (S_ISREG(buf.st_mode)) {
		printf("%s:%ld\n", entry->d_name, buf.st_size);
	}
 }
 closedir(dir1);
}


int main(int argc, char *argv[]){
 
 //printf("%s:%s", argv[1], argv[2]);
 copiere(argv[1], argv[2]);
 return 0;
}