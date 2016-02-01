#include "my-openssl.h"
#include <string.h>
#include <openssl/md5.h>

char salt[] = "salt is better than sugar";

void generate_otp(unsigned char *key, char *pph, char *timestamp, char *salt) {
#if 1
    int n;
    MD5_CTX ctx;
    char data[100];

    n = sprintf(data, "%s%s%s", pph, timestamp, salt);

    MD5_Init(&ctx);
    MD5_Update(&ctx, data, strlen(data));
    MD5_Final(key, &ctx);
#endif
}

void adv_encrypt(unsigned char *ciphertext, int *ciphertext_len, unsigned char *plaintext, int plaintext_len, char *pph, char *timestamp) {
    EVP_CIPHER_CTX *ctx;
    int len;
    int temp;
    unsigned char key1[MD5_DIGEST_LENGTH]; //defined in md5.h, MD5_DIGEST_LENGTH = 16

    generate_otp(key1, pph, timestamp, salt);

    ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit(ctx, EVP_aes_128_cbc(), key1, NULL);
    EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len);
    temp = len;
    EVP_EncryptFinal_ex(ctx, ciphertext + len,  &len);
    temp += len;

    *ciphertext_len = temp;
    
    EVP_CIPHER_CTX_free(ctx);
    printf("Encrypted Done! ");
}

void adv_decrypt(unsigned char *plaintext, int *plaintext_len, unsigned char *ciphertext, int ciphertext_len, char *pph, char *timestamp) {
    EVP_CIPHER_CTX *ctx;
    int len;
    int temp;
    unsigned char key2[MD5_DIGEST_LENGTH];

    generate_otp(key2, pph, timestamp, salt);

    ctx = EVP_CIPHER_CTX_new();
    
    EVP_DecryptInit(ctx, EVP_aes_128_cbc(), key2, NULL);
    EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len);
    temp = len;
    EVP_DecryptFinal(ctx, plaintext + len,  &len);
    temp += len;

    *plaintext_len = temp;

    EVP_CIPHER_CTX_free(ctx);
    printf("Decrypted Done! ");
}

