#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

void _exit(int code) {
	// DO NOTHING
}

void* _malloc(int size) {
	return malloc(size);
}

void _free(void* buffer) {
	free(buffer);
}

void _consoleNumber(int number) {
	printf("%d\n", number);
}

void _consoleBuffer(void* buffer) {
	printf("%d\n", (unsigned int)buffer);
}

void _consoleLog(const char* offset, int len) {
	printf("%s\n", offset);
}

void _runScript(const char* script, int len) {
	// DO NOTHING
}

void _requestFileSize(const char* path) {
	// DO NOTHING
}

#ifdef __cplusplus
}
#endif