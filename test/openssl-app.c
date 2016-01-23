#include <stdio.h>
#include <string.h>
#include "my-openssl.h"


int main() {
    char *key = "01234567890123456789012345678901";
    char *iv = "01234567890123456"; //If key is one time pass then iv can be null or fixed
    char plaintext[] = "The quick brown fox jumps over the lazy dog";
    char ciphertext[128];
    char decryptedtext[128];

    int ciphertext_len;
    int decryptedtext_len;

    ciphertext_len = encrypt(plaintext, strlen(plaintext), key, iv, ciphertext);
    printf("Ciphertext is:\n");
    BIO_dump_fp (stdout, (const char *)ciphertext, ciphertext_len);

    decryptedtext_len = decrypt(ciphertext, ciphertext_len, key, iv, decryptedtext);
    decryptedtext[decryptedtext_len] = '\0';

    printf("Decrypted text is:\n");
    printf("%s\n", decryptedtext);

    return 0;
}
