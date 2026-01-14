#ifndef ENCRYPT_H
# define ENCRYPT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sodium.h>


int encrypt(const char *filepath, unsigned char *hashed_key, int silent);


#endif
