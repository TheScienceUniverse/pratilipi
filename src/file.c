#include "../inc/file.h"

size_t get_file_size (String* path) {
	FILE* file = fopen (path -> text, "rb");

	if (NULL == file) {
		perror ("Unable to open the file!");
		return EXIT_FAILURE;
	}

	fseek (file, 0, SEEK_END);
	size_t size = ftell (file); // in bytes
	fclose (file);

	return size;
}
