#ifndef __MY_OPENSSL__
#define __MY_OPENSSL__

#include <openssl/evp.h>

extern char salt[];

void generate_otp(unsigned char *key, char *pph, char *timestamp, char *salt);
void adv_encrypt(unsigned char *ciphertext, int *ciphertext_len, unsigned char *plaintext, int plaintext_len, char *pph, char *timestamp);
void adv_decrypt(unsigned char *plaintext, int *plaintext_len, unsigned char *ciphertext, int ciphertext_len, char *pph, char *timestamp);

#endif
