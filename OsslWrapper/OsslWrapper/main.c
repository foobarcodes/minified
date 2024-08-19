
#include "ossl.h"

#define ENCRYPT_KEY "646f74636f6d646f74636f6d646f74636f6d646f74636f6d646f"

int main(int argc, char* argv[])
{
	char* buffer = "Hello world";
	char outBuffer[4096];
	char decryptBuffer[4096];
	int actualSize = 0;
	
	openssl_3des_encrypt(ENCRYPT_KEY, buffer, strlen(buffer), outBuffer, sizeof(outBuffer), &actualSize);

	printf("Encoded Buffer: %s\n", outBuffer);

	openssl_3des_decrypt(ENCRYPT_KEY, outBuffer, actualSize-1, decryptBuffer, sizeof(decryptBuffer), &actualSize);

	decryptBuffer[actualSize] = '\0';

	printf("Decryptd buffer: %s\n", decryptBuffer);
   

	return 0;
}