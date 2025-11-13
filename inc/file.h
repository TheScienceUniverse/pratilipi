#ifndef FILE_H
#define FILE_H

#include <unistd.h>
#include <sys/stat.h>

#include "../../DSA/inc/string.h"
#include "../../codec/inc/adler32.h"

size_t get_file_size (String* path);
bool does_directory_exist (String* directory);
bool does_file_exist (String* file_path);
String* build_file_path (String* directory, String* file);
void split_file (String* src_dir, String* dst_dir, String* f_name);

#endif	// FILE_H
