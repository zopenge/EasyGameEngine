/**
 * Auth Main Functions
 */

#ifdef __cplusplus
extern "C"
{
#endif

    void requestFileSize();

    void onRecvFileSize(const char *path, int size);

    void login(const char *token);

    long long *encodeString(const char *string);
    char *decodeString(const long long *buffer);

    unsigned int getAttributes();

    unsigned int getRandomValue();

    void eval(const char *script);

#ifdef __cplusplus
}
#endif