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
 mode_t file_mask = 0000;


 if (src == NULL || dest == NULL) {
	printf("\nError: Utilizati directoare\n");
	exit(0);
 }

 stat(src, &fileBuf);

 while ((entry = readdir(dir1)) != NULL) {
	char pathSrc[1000], pathDest[1000];
	strcpy(pathSrc, src);
	strcat(pathSrc, "/");
	strcat(pathSrc, entry->d_name);
	
	strcpy(pathDest, dest);
	strcat(pathDest, "/");
	strcat(pathDest, entry->d_name);	
	stat(pathSrc, &buf);

	file_mask = 0000;
	file_mask += ((buf.st_mode & S_IRUSR)) ? 0400 : 0000;
	file_mask += ((buf.st_mode & S_IWUSR)) ? 0200 : 0000;
	file_mask += ((buf.st_mode & S_IXUSR)) ? 0100 : 0000;
	file_mask += ((buf.st_mode & S_IRGRP)) ? 0040 : 0000;
	file_mask += ((buf.st_mode & S_IWGRP)) ? 0020 : 0000;
	file_mask += ((buf.st_mode & S_IXGRP)) ? 0010 : 0000;
	file_mask += ((buf.st_mode & S_IROTH)) ? 0004 : 0000;
	file_mask += ((buf.st_mode & S_IWOTH)) ? 0002 : 0000;
	file_mask += ((buf.st_mode & S_IXOTH)) ? 0001 : 0000;
	
	if (dir2 == NULL) {
		mkdir(dest, fileBuf.st_mode);
	}

	chmod(dest, fileBuf.st_mode);
	
	if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
		copiere(pathSrc, pathDest);
	} else if (entry->d_type == DT_REG && buf.st_size > 500) {
		char info[256];
	
		int fdr = open(pathSrc, O_RDONLY);
		int fdw = open(pathDest, O_CREAT|O_WRONLY|O_TRUNC, buf.st_mode);
		int read_line;
		while ((read_line = read(fdr, &info, 128)) > 0) {
			write(fdw, &info, read_line);
		}	
		chmod(pathDest, file_mask);
		
	} else if (entry->d_type == DT_REG && buf.st_size <= 500) {
		char pathSrcLnk[1000], pathDestLnk[1000];
		char *ptr;
		realpath(pathSrc, pathSrcLnk);
		realpath(pathDest, pathDestLnk);
		
		int make_link = symlink(pathSrcLnk, pathDestLnk);
		if (make_link == -1) {	
			printf("\nLink-ul pentru '%s' exista deja\n\n", pathSrcLnk);
		
		} else {
			printf("Link realizat cu succes\n");
			printf("%s->%s\n", pathDest, pathSrc);
			chmod(pathSrc, file_mask & ~(0333));
		}	
	}	
 }
 closedir(dir1);
 closedir(dir2);
}


int main(int argc, char *argv[]){
 copiere(argv[1], argv[2]);
 return 0;
}
