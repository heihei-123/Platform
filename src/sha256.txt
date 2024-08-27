#include "param.h"



void sha256_encode(char* input, size_t input_len, char* output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input, input_len);
    SHA256_Final(hash, &sha256);

    char hex[3];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hex, "%02x", hash[i]);
        output[i * 2] = hex[0];
        output[i * 2 + 1] = hex[1];
    }
    output[SHA256_DIGEST_LENGTH * 2] = '\0';
}