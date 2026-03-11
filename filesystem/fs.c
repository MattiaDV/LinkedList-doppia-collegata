#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
	const char *filename = "mattia.txt";
	const char *dirname = "creation_test";
	const char *filepath = "creation_test/mattia.txt";
	
	if (mkdir(dirname, 0755) == -1) {
		fprintf(stderr, "Error: imposible to create a dir\n");
		return 1;
	} else {
		printf("Success: folder %s created!\n", dirname);
	}
	
	int fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	
	if (fd < 0) {
		fprintf(stderr, "Error: imposible create file\n");
		return 1;
	} else {
		printf("Success: file %s created!\n", filename);
	}
	
	DIR *dir = opendir(dirname);
	
	if (!dir) {
		fprintf(stderr, "Error: imposible to open the dir!\n");
		return 1;
	}
	
	struct dirent *entry;
	
	while ((entry = readdir(dir)) != NULL) {
		printf("%s\n", entry->d_name);
	}
	
	if (unlink(filepath) == -1) {
		fprintf(stderr, "Error: imposible to delete the file!\n");
		return 1;
	} else {
		printf("Success: file %s deleted!\n", filename);
	}
	
	if (rmdir(dirname) == -1) {
		fprintf(stderr, "Error: imposible to delete the dir!\n");
		return 1;
	} else {
		printf("Success: dir %s deleted!\n", dirname);
	}
	
	return 0;
}
