#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <sys/types.h>

int main(int argc, char * argv[]) {
	FILE *src;
	FILE *dst;
	DIR *pdir;
	struct dirent *pde;
	int i = 0;
	char ch;
	int count = 0 ;

	if(argc<4) {
		printf("Usage : file_copy sourcefile destination_file \n");
		exit(1);
	}

	if((src = fopen(argv[1],"r")) == NULL) {
		perror("fopen: src");
		exit(1);
	}

	if((dst = fopen(argv[2],"w")) == NULL) {
		perror("fopen:dst");
		exit(1);
	}

	if((pdir = opendir(argv[3]))<0) {
		perror("opendir");
		exit(1);
	}

	while ( !feof(src) ) {
		ch = (char) fgetc(src);
		if ( ch != EOF )
			fputc((int)ch, dst);
		count++;
	}

	while ((pde = readdir(pdir)) != NULL) {
		printf("%20s ", pde->d_name);
		if (++i % 3 == 0)
			printf("\n");
	}

	printf("\n");
	fclose(src);
	fclose(dst);
	closedir(pdir);
}
