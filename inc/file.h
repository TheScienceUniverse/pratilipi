#ifndef FILE_H
#define FILE_H

#include <unistd.h>
#include <sys/stat.h>

#include "../../DSA/inc/string.h"
#include "../../codec/inc/adler32.h"

size_t get_file_size (String* path);
bool does_file_exist (String* file_path);
void split_file (String* file_path, String* temp_path);

#endif	// FILE_H
