#include "Decrypt.h"

int decrypt_file(const char *filepath, unsigned char *hashed_key, int silent)
{

    FILE *file = fopen(filepath, "rb");
    if (!file)
        return (-1);

    // 2. Read the Nonce (the first 24 bytes)
    unsigned char nonce[crypto_secretbox_NONCEBYTES];
    if (fread(nonce, 1, sizeof(nonce), file) != sizeof(nonce))
    {
        fclose(file);
        return (-1);
    }

    // 3. Determine Ciphertext size and Read it
    fseek(file, 0, SEEK_END);
    long total_size = ftell(file);
    fseek(file, sizeof(nonce), SEEK_SET); // Move past the nonce

    long ciphertext_len = total_size - sizeof(nonce);
    unsigned char *ciphertext = malloc(ciphertext_len);
    fread(ciphertext, 1, ciphertext_len, file);
    fclose(file);

    // 4. Decrypt
    // Plaintext size is ciphertext_len - crypto_secretbox_MACBYTES
    unsigned char *plaintext = malloc(ciphertext_len - crypto_secretbox_MACBYTES);
    
    if (crypto_secretbox_open_easy(plaintext, ciphertext, ciphertext_len, nonce, hashed_key) != 0)
    {
        if (!silent)
            printf("Error: Invalid key for %s\n", filepath);
        free(ciphertext);
        free(plaintext);
        return (-1);
    }

    // 5. Restore original filename (remove .ft)
    char *old_filename = strdup(filepath);
    size_t len = strlen(old_filename);
    if (len > 3)
        old_filename[len - 3] = '\0'; // Truncate ".ft"

    // 6. Write Plaintext to original filename
    FILE *out = fopen(old_filename, "wb");
    if (out) {
        fwrite(plaintext, 1, ciphertext_len - crypto_secretbox_MACBYTES, out);
        fclose(out);
        remove(filepath); // Remove the encrypted version
        if (!silent)
            printf("Decrypted: %s\n", old_filename);
    }

    free(ciphertext);
    free(plaintext);
    free(old_filename);
    return 0;
}
