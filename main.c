#include "./inc/directory.h"
#include <sys/stat.h> // Required for stat() and S_ISDIR()

int main (
	__attribute__((unused)) int argc
	, __attribute__((unused)) char* argv[]
) {
	Tree* tree = create_Tree ();
	//String* path = create_String (1, ".");
	String* path = create_String (3, "src");
	//display_String (path);

	if (argc < 3) {
		perror ("Not enough input!\nProvide source and destination!");
		return (EXIT_FAILURE);
	}

	char* src_dir = argv [1];
	char* dst_dir = argv [2];

	struct stat status;

	if (!(stat (src_dir, &status) == 0 && S_ISDIR (status .st_mode))) {
		printf ("Source Directory '%s' does not exist!\n", src_dir);
		return EXIT_FAILURE;
	}

	if (!(stat (dst_dir, &status) == 0 && S_ISDIR (status .st_mode))) {
		printf ("Destination Directory '%s' does not exist!\n", dst_dir);
		return EXIT_FAILURE;
	}

	Node* node = create_Node (N_Tree);
	set_Node_name (node, path -> length, path -> text);
	delete_String (&path);
	display_Node (node);
	set_Tree_root_Node (tree, node);
	delete_Node (&node);

	node = tree -> root_node;

	find_inner_files (tree, node);

	display_Tree (tree);
	delete_Tree (&tree);

	printf ("\n");

	String* src_dir_str = create_String (2, "./");
	String* dst_dir_str = create_String (3, "dst");
	String* f_name_str = create_String (15, "lorem_ipsum.txt");

	split_file (src_dir_str, dst_dir_str, f_name_str);


//	manage_memory ();

	return EXIT_SUCCESS;
}
