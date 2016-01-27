#include <stdio.h>
#include <string.h>
#include "my-openssl.h"


int main() {
    char plaintext[] = "T12340";
    char ciphertext[100];
    char decryptedtext[100];

    int plaintext_len;
    int ciphertext_len;
    int decryptedtext_len;

    char pph[]="abcxyz";
    char timestamp[]="26/1/2016 16:00:00";
    
    plaintext_len = strlen(plaintext);
    adv_encrypt(ciphertext, &ciphertext_len, plaintext, plaintext_len, pph, timestamp);
    printf("Ciphertext is:\n");
    BIO_dump_fp (stdout, (const char *)ciphertext, ciphertext_len);
    printf("Ciphertext length: %d\n", ciphertext_len);

    printf("====================================\n");

    adv_decrypt(decryptedtext, &decryptedtext_len, ciphertext, ciphertext_len, pph, timestamp);
    decryptedtext[decryptedtext_len] = '\0';
    printf("Decrypted text is:\n");
    printf("%s\n", decryptedtext);
    printf("Decrypted text length: %d\n", decryptedtext_len);
    return 0;
}
