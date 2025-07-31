#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#include "../DSA/inc/data.h"
#include "../DSA/inc/node.h"
#include "../DSA/inc/tree.h"

void display_type (unsigned char type);
String* get_relative_path (Tree* tree, Node* node);
void find_inner_files (Tree* tree, Node* anchor);
void prepend_chars_to_string (String* string, int n, char c);
void append_chars_to_string (String* string, int n, char c);

#endif // DIRECTORY_H
