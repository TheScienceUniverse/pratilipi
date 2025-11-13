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

bool does_directory_exist (String* directory) {
	struct stat buffer;
    return (0 == stat (directory -> text, &buffer) && S_ISDIR (buffer.st_mode));
}

bool does_file_exist (String* file_path) {
	struct stat buffer;
	return (/*0 == access (file_path -> text, F_OK)) && */(0 == stat (file_path -> text, &buffer)));
}

String* build_file_path (String* directory, String* file) {
	if (NULL == directory || NULL == directory -> text) {
		perror ("No directory provided to build file path!");
		return NULL;
	}

	if (NULL == file || NULL == file -> text) {
		perror ("No file provided to build file path!");
		return NULL;
	}

	String* file_path = NULL;
	String* terminator = create_String (1, "\0");

	if ('/' == *(directory -> text + directory -> length - 1)) {
		file_path = concatenate_Strings (3, directory, file, terminator);
	} else {
		String* delimeter = create_String (1, "/");
		file_path = concatenate_Strings (3, directory, delimeter, file);
		delete_String (&delimeter);
	}

	delete_String (&terminator);

	return file_path;
}

void split_file (String* src_dir, String* dst_dir, String* f_name) {
	String* file_path = build_file_path (src_dir, f_name);
//	display_string_details (file_path);
//	ENDL();

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
	display_String (file_path);
	printf (" [");
	String* file_name_checksum = encode_adler32 (file_path);
	display_String (file_name_checksum);
	delete_String (&file_name_checksum);
	printf ("] ");
	size_t file_size = get_file_size (file_path);
	printf (" Size: %lu bytes", file_size);
	ENDL();

	delete_String (&file_path);

	size_t segment_size = 1024;	// 1 KiB
	size_t segment_count = file_size / segment_size;

	if (file_size > segment_count * segment_size) {
		++segment_count;
	}

	printf ("Number of segments: %lu\n", segment_count);

	String* tmp_str = NULL;
	FILE* op_file = NULL;

	for (size_t i = 0; i < segment_count; i++) {

		file_path = build_file_path (dst_dir, f_name);
		tmp_str = file_path;

		file_path = encode_adler32 (file_path);
		display_String_details (file_path);
		delete_String (&tmp_str);
		tmp_str = file_path;

//		file_path = append_integer_to_raw_string (file_path, i);
//		delete_string (&tmp_str);
/*
		op_file = fopen (file_path -> text, "wb");

		if (NULL == op_file) {
			perror ("Unable to open segment file!");
			exit (EXIT_FAILURE);
		}

		fclose (op_file);
*/
		delete_String (&file_path);
	}

	// FILE* op_file = fopen (file_path -> text, "rb");

	fclose (ip_file);
}
