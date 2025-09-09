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

bool does_file_exist (String* file_path) {
	struct stat buffer;
	return (0 == access (file_path -> text, F_OK)) && (0 == stat (file_path -> text, &buffer));

}

void split_file (String* file_path, String* temp_path) {
	if (!does_file_exist (file_path)) {
		perror ("File does not exist to split!");
		exit (EXIT_FAILURE);
	}

	FILE* ip_file = fopen (file_path -> text, "rb");

	if (NULL == ip_file) {
		perror ("Unable to access file to split!");
		exit (EXIT_FAILURE);
	}

	printf ("File: ");
	display_string (file_path);
	printf (" [");
	String* file_name_checksum = encode_adler32 (file_path);
	display_string (file_name_checksum);
	delete_string (&file_name_checksum);
	printf ("] ");
	size_t file_size = get_file_size (file_path);
	printf (" Size: %lu bytes", file_size);
	ENDL();

	size_t segment_size = 1024;	// 1 KiB
	size_t segment_count = file_size / segment_size + 1;
	printf ("Number of segments: %lu\n", segment_count);

	for (size_t i = 0; i < segment_count; i++) {
/*
		FILE* op_file = fopen (temp_path, "wb");

		if (NULL == op_file) {
			perror ("Unable to open segment file!");
			exit (EXIT_FAILURE);
		}

		fclose (op_file);
*/
	}

	// FILE* op_file = fopen (file_path -> text, "rb");

	fclose (ip_file);
}
