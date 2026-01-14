#ifndef DECRYPT_H
# define DECRYPT_H

#include "Encrypt.h"
#include <string.h>


int decrypt_file(const char *filepath, unsigned char *hashed_key, int silent);

#endif
