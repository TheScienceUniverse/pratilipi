#include "./inc/directory.h"

int main (
	__attribute__((unused)) int argc
	, __attribute__((unused)) char* argv[]
) {
	Tree* tree = create_tree ();
	//String* path = create_string (1, ".");
	String* path = create_string (3, "DSA");
	//display_string (path);

	Node* node = create_node (N_Tree);
	set_node_name (node, path -> length, path -> text);
	display_node (node);
	set_tree_root_node (tree, node);
	delete_node (&node);

	node = tree -> root_node;

	find_inner_files (tree, node);

	delete_string (&path);

	display_tree (tree);
	delete_tree (&tree);

	printf ("\n");

	return EXIT_SUCCESS;
}
