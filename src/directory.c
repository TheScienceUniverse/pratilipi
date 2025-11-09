#include "../inc/directory.h"

void display_type (unsigned char type) {
	switch (type) {
		case DT_UNKNOWN:
			printf ("unknown");
			break;
		case DT_REG:
			printf ("file");
			break;
		case DT_DIR:
			printf ("directory");
			break;
		case DT_FIFO:
			printf ("named pipe");
			break;
		case DT_SOCK:
			printf ("socket");
			break;
		case DT_CHR:
			printf ("character device");
			break;
		case DT_BLK:
			printf ("block device");
			break;
		case DT_LNK:
			printf ("symbolic link");
			break;
		default:
			break;
	}
}

String* get_relative_path (Tree* tree, Node* node) {
	if (NULL == tree) {
		perror ("Tree does not exist to construct relative path!");
		return NULL;
	}

	if (NULL == node) {
		perror ("Node does not exist to construct relative path!");
		return NULL;
	}

	if (node -> type != N_Tree) {
		perror ("Given Node doesn't belong to a tree to construct relative path!");
		return NULL;
	}

	String* path = duplicate_string (node -> name);
	char last_char = get_char_at (path, path -> length - 1);

	if ('\0' != last_char) {
		append_chars_to_string (path, 1, '\0');
	}

	if (tree -> root_node == node) {
		return path;
	}

	ssize_t height = tree -> height;

	while (
		height--
		&& NULL != node
	) {
		node = node -> address_list -> head_chunk -> first_data_address -> address;

		if (NULL != node) {
			prepend_chars_to_string (path, 1, '/');
			String* tmp_str = concatenate_strings (2, node -> name, path);
			//display_string_details (tmp_str);
			delete_string (&path);
			path = tmp_str;
		}
	}

	return path;
}

void prepend_chars_to_string (String* string, int n, char c) {
	char* ptr = string -> text;

	string -> text = malloc ((string -> length + n) * sizeof (char));

	if (NULL == string -> text) {
		perror ("Unable to extend memory to append characters to string!");
		string -> text = ptr;
		exit (EXIT_FAILURE);
	}

	char* dst_ptr = string -> text;

	for (size_t i = 0; i < n; i++) {
		*dst_ptr++ = c;
	}

	copy_raw_byte_stream (string -> length, (BYTE*) ptr, (BYTE*) dst_ptr);

	string -> length += n;
}

void append_chars_to_string (String* string, int n, char c) {
	char* ptr = string -> text;

	string -> text = (char*) malloc (sizeof (char) * (string -> length + n));

	if (NULL == string -> text) {
		perror ("Unable to extend memory to append characters to string!");
		string -> text = ptr;
		exit (EXIT_FAILURE);
	}

	copy_raw_byte_stream (string -> length, (BYTE*) ptr, (BYTE*)(string -> text));

	ptr = string -> text + string -> length;

	for (size_t i = 0; i < n; i++) {
		*ptr++ = c;
	}

	string -> length += n;
}

void find_inner_files (Tree* tree, Node* anchor) {
	if (NULL == tree) {
		perror ("Tree does not exist to include files!");
		return;
	}

	if (anchor == NULL) {
		perror ("Anchor node does not exist to include files!");
		return;
	}

/*{
	ino_t d_ino;	// inode number
	off_t d_off;	// offset to the next dirent
	unsigned short d_reclen;	// length of this record
	unsigned char  d_type;	// type of file; not supported by all file system types
	char d_name[256];	filename, NULL terminated
	unsigned short int d_namlen - length of name
}*/

	String* path = get_relative_path (tree, anchor);
// display_string_details (path);

	DIR *dir;	// directory
	dir = opendir (path -> text);
	// dir = opendir (".");

	if (NULL == dir) {
		perror ("Error: directory unaccisible\n");
		exit (EXIT_FAILURE);
	}

	delete_string (&path);

	struct dirent *dir_ent; // directory entries
	char* f_name;
	Node* node = create_node (N_Tree);

	while (NULL != (dir_ent = readdir (dir))) {
		//printf ("File => ");
		//printf ("#inode: %lu", dir_ent -> d_ino);
		//printf (", offset: %d", dir_ent -> d_off);
		//printf (", record length: %hu", dir_ent -> d_reclen);
		//printf (", type: ");
		//display_type (dir_ent -> d_type);

		f_name = dir_ent -> d_name;

		if (0 == strcmp (".", f_name)
			|| 0 == strcmp ("..", f_name)
		) {
			continue;
		}

		set_node_name (node, strlen (f_name), f_name);
//		display_node (node);
		append_child_node (tree, anchor, node);

		// handle directory
		if (DT_DIR == dir_ent -> d_type) {
			Node* child_node = get_last_child_node_address (anchor);
			find_inner_files (tree, child_node);
		}

		// handle file
		if (DT_REG == dir_ent -> d_type) {
			Node* child_node = get_last_child_node_address (anchor);
			String* temp_path = create_string (5, "tmp/\0");
			String* file_path = get_relative_path (tree, child_node);
			// display_string_details (file_path);
			split_file (file_path, temp_path);
			delete_string (&file_path);
			delete_string (&temp_path);
		}

		//printf (", name: %s", dir_ent -> d_name);
		//printf (", name length: %hu", dir_ent -> d_namlen);
		//putchar ('\n');
	}

	closedir (dir);

	delete_node (&node);
}
