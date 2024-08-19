#include <stdio.h>
#include "ossl.h"

#define TEMP_FILE_SRC "D:\\temp\\foo.txt"
#define TEMP_FILE_DEST "D:\\temp\\boo.txt"

int openssl_main(const char* cmdline)
{
	int result = system(cmdline);

    if (result != 0) 
    {
        printf("Error: OpenSSL command failed with exit code %d\n", result);
    }
    else 
    {
        printf("OpenSSL command executed successfully.\n");
    }
}

STATUS openssl_3des_encrypt(char* key192, char* input, int inputSize, char* output, int outputSize, int* actualOutSize)
{
    char cmdBuffer[4096];

    unsigned long fileSize;

    FILE* fp = fopen(TEMP_FILE_SRC, "w");

    if (!fp)
    {     
        return OSSL_E_IO_FAILURE;
    }

    fwrite(input, 1, inputSize, fp);
    fclose(fp);

    sprintf(cmdBuffer, "openssl enc -e -des-ede3 -md md5 -base64 -in %s -out %s -K %s", TEMP_FILE_SRC, TEMP_FILE_DEST, key192);
    
    openssl_main(cmdBuffer);

    // Open the dest file
    fp = fopen(TEMP_FILE_DEST, "r");

    if (!fp)
    {
        return OSSL_E_IO_FAILURE;
    }
    
    fseek(fp, 0, SEEK_END);
    fileSize = ftell(fp);

    if (outputSize < fileSize)
    {
        return OSSL_E_BUFFER_TOO_SMALL;
    }

    memset(output, 0, fileSize + 1);
    fseek(fp, 0, SEEK_SET);
    fread(output, fileSize, 1, fp);

    if (actualOutSize)
    {
        *actualOutSize = fileSize;
    }

    fclose(fp);

    return OSSL_OK;
}

STATUS openssl_3des_decrypt(char* key192, char* input, int inputSize, char* output, int outputSize, int* actualOutSize)
{
    char cmdBuffer[4096];

    unsigned long fileSize;

    FILE* fp = fopen(TEMP_FILE_SRC, "wb");

    if (!fp)
    {
        return OSSL_E_IO_FAILURE;
    }

    fwrite(input, inputSize, 1, fp);
    fclose(fp);

    sprintf(cmdBuffer, "openssl enc -d -des-ede3 -md md5 -base64 -in %s -out %s -K %s", TEMP_FILE_SRC, TEMP_FILE_DEST, key192);

    // todo: validate return value here
    openssl_main(cmdBuffer);

    // Open the dest file
    fp = fopen(TEMP_FILE_DEST, "rb");

    if (!fp)
    {
        return OSSL_E_IO_FAILURE;
    }

    fseek(fp, 0, SEEK_END);
    fileSize = ftell(fp);

    if (outputSize < fileSize)
    {
        // insufficient output buffer size
        return;
    }

    memset(output, 0, fileSize);
    fseek(fp, 0, SEEK_SET);
    fread(output, fileSize, 1, fp);

    if (actualOutSize)
    {
        *actualOutSize = fileSize;
    }

    fclose(fp);

    return OSSL_OK;
}