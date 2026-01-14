#include "Encrypt.h"

int encrypt(const char *filepath, unsigned char *hashed_key, int silent)
{
    (void)filepath; 
    (void)silent; 

    FILE *file;
    long size;
    unsigned char *plaintext;
    

    file = fopen("test_file.txt", "rb");
    
    // get size
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fseek(file, 0, SEEK_SET);
    

    // read and store in memory
    plaintext = malloc(size);
    fread(plaintext, 1, size, file);
    fclose(file);
    
    // nonce
    unsigned char nonce[crypto_secretbox_NONCEBYTES];
    randombytes_buf(nonce, sizeof(nonce));

    // signature to check if data has been tempered with
    unsigned char *signature = malloc(crypto_secretbox_MACBYTES + size);
     
    //encrypt
    crypto_secretbox_easy(signature, plaintext, size, nonce, hashed_key);

    
    // 4. Write to file.ft: nonce FIRST, then ciphertext
    FILE *out = fopen("test_file.txt", "wb");
    fwrite(nonce, 1, sizeof(nonce), out);
    fwrite(signature, 1, crypto_secretbox_MACBYTES + size, out);
    fclose(out);

    // 5. Clean up
    free(signature);
    free(plaintext);


    printf("Encrypted!\n");
    return(0);
}


