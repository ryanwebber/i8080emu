#ifndef LOADER_H
#define LOADER_H

#include <stdint.h>

/**
 * Loads the contents of a file into memory. Points the given 
 * pointer to the address of the stored uint8 array and returns
 * the number of bytes in the data. If the file cannot be read
 * the pointer will point to NULL
 *
 * The caller is responsible for freeing the allocated memory
 */
uint32_t load(const char* filename, uint8_t **data_ptr);

#endif

