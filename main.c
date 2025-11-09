#include "./inc/directory.h"
#include <sys/stat.h> // Required for stat() and S_ISDIR()

int main (
	__attribute__((unused)) int argc
	, __attribute__((unused)) char* argv[]
) {
	Tree* tree = create_tree ();
	//String* path = create_string (1, ".");
	String* path = create_string (3, "src");
	//display_string (path);

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

	Node* node = create_node (N_Tree);
	set_node_name (node, path -> length, path -> text);
	delete_string (&path);
	display_node (node);
	set_tree_root_node (tree, node);
	delete_node (&node);

	node = tree -> root_node;

	find_inner_files (tree, node);

	display_tree (tree);
	delete_tree (&tree);

	printf ("\n");

	manage_memory ();

	return EXIT_SUCCESS;
}
