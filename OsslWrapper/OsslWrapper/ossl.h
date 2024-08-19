#include <stdio.h>

typedef unsigned int STATUS;

#define OSSL_OK                     0
#define OSSL_ERROR(code)            (-(code))

#define OSSL_E_INVALID_ARG          OSSL_ERROR(1)
#define OSSL_E_IO_FAILURE           OSSL_ERROR(2)
#define OSSL_E_BUFFER_TOO_SMALL     OSSL_ERROR(3)


STATUS openssl_3des_encrypt(char* key192, char* input, int inputSize, char* output, int outputSize, int* actualOutSize);
STATUS openssl_3des_decrypt(char* key192, char* input, int inputSize, char* output, int outputSize, int* actualOutSize);