//#define DEBUG 1

#define PRIME0 211
#define PRIME1 104381

/**
 * Typedef
 */
typedef const char *string;
typedef int any;
typedef int boolean;
typedef unsigned int _uint;

#define false 0
#define true 1
#define NULL ((void *)0)

/**
 * Internal Structures
 */

struct public_key_class
{
    long long modulus;
    long long exponent;
};

struct private_key_class
{
    long long modulus;
    long long exponent;
};

/**
 * JS Export Functions
 */
void _exit(int code);
void _login(const char *token);

void *_malloc(int size);
void _free(void *buffer);

void _consoleNumber(int number);
void _consoleBuffer(void *buffer);
void _consoleLog(const char *offset, int len);

void _runScript(const char *script, int len);

void _requestFileSize(const char *path);

#define MALLOC(size) _malloc(size);
#define FREE(buffer)    \
    if (buffer != NULL) \
    {                   \
        _free(buffer);  \
        buffer = NULL;  \
    }

/**
 * Internal System Functions
 */

void *memset(void *s, int c, int count)
{
    char *xs = s;

    while (count--)
        *xs++ = c;

    return s;
}

void *memcpy(void *dest, const void *src, int count)
{
    char *tmp = dest;
    const char *s = src;

    while (count--)
        *tmp++ = *s++;
    return dest;
}

void *memmove(void *dest, const void *src, int count)
{
    char *tmp;
    const char *s;

    if (dest <= src)
    {
        tmp = dest;
        s = src;
        while (count--)
            *tmp++ = *s++;
    }
    else
    {
        tmp = dest;
        tmp += count;
        s = src;
        s += count;
        while (count--)
            *--tmp = *--s;
    }
    return dest;
}

int memcmp(const void *cs, const void *ct, int count)
{
    const unsigned char *su1, *su2;
    int res = 0;

    for (su1 = cs, su2 = ct; 0 < count; ++su1, ++su2, count--)
        if ((res = *su1 - *su2) != 0)
            break;
    return res;
}

/**
 * Internal Util Functions
 */

int isPrime(int n)
{
    if (n == 1)
        return false;

    for (int i = 2; i <= n / 2; ++i)
    {
        // condition for nonprime number
        if (n % i == 0)
            return true;
    }

    return false;
}

int toUpper(int c)
{
    if (c >= 'a' && c <= 'z')
        return c + ('A' - 'a');

    return c;
}

int toLower(int c)
{
    if (c >= 'A' && c <= 'Z')
        return c + ('a' - 'A');

    return c;
}

// Thanks for sharing code: https://github.com/torvalds/linux/blob/master/lib/string.c
int stringCompare(const char *s1, const char *s2, boolean ignoreCase)
{
    int c1, c2;

    do
    {
        c1 = *s1++;
        c2 = *s2++;

        if (ignoreCase)
        {
            c1 = toLower(c1);
            c2 = toLower(c2);
        }
    } while (c1 == c2 && c1 != 0);

    return c1 - c2;
}

int stringLength(const char *str)
{
    int length = 0;
    while (*str++)
    {
        length++;
    }

    return length;
}

int searchStringL2R(const char *s1, const char *s2)
{
    const char *_s1 = s1;

    int l1, l2;

    l2 = stringLength(s2);
    if (!l2)
        return -1;

    l1 = stringLength(s1);
    while (l1 >= l2)
    {
        l1--;
        if (!memcmp(s1, s2, l2))
            return s1 - _s1;
        s1++;
    }

    return -1;
}

char *copyString(char *des, const char *src)
{
    char *_des = des;
    while (*src)
    {
        *des++ = *src++;
    }

    *des = 0;

    return _des;
}

char *allocString(const char *src)
{
    int length = stringLength(src);
    char *des = (char *)MALLOC(length + 1);
    copyString(des, src);

    return des;
}

char *appendString(char *des, const char *src, int clear)
{
    char *_des = des;

    if (clear)
    {
        des[0] = 0;
    }

    while (*des++)
    {
    }

    while (*src)
    {
        *des++ = *src++;
    }

    *des = 0;

    return _des;
}

/**
 * RSA Encode/Decode Functions
 */

// This should totally be in the math library.
long long gcd(long long a, long long b)
{
    long long c;
    while (a != 0)
    {
        c = a;
        a = b % a;
        b = c;
    }
    return b;
}

long long ExtEuclid(long long a, long long b)
{
    long long x = 0, y = 1, u = 1, v = 0, gcd = b, m, n, q, r;
    while (a != 0)
    {
        q = gcd / a;
        r = gcd % a;
        m = x - u * q;
        n = y - v * q;
        gcd = a;
        a = r;
        x = u;
        y = v;
        u = m;
        v = n;
    }
    return y;
}

long long rsa_modExp(long long b, long long e, long long m)
{
    if (b < 0 || e < 0 || m <= 0)
    {
        _exit(1);
    }
    b = b % m;
    if (e == 0)
        return 1;
    if (e == 1)
        return b;
    if (e % 2 == 0)
    {
        return (rsa_modExp(b * b % m, e / 2, m) % m);
    }
    if (e % 2 == 1)
    {
        return (b * rsa_modExp(b, (e - 1), m) % m);
    }
}

// Calling this function will generate a public and private key and store them in the pointers
// it is given.
void rsaGenKeys(long long p, long long q, struct public_key_class *pub, struct private_key_class *priv)
{
    long long e = 257; // powl(2, 8) + 1;

    long long max = p * q;
    long long phi_max = (p - 1) * (q - 1);

    // Next, we need to choose a,b, so that a*max+b*e = gcd(max,e). We actually only need b
    // here, and in keeping with the usual notation of RSA we'll call it d. We'd also like
    // to make sure we get a representation of d as positive, hence the while loop.
    long long d = ExtEuclid(phi_max, e);
    while (d < 0)
    {
        d = d + phi_max;
    }

    // We now store the public / private keys in the appropriate structs
    pub->modulus = max;
    pub->exponent = e;

    priv->modulus = max;
    priv->exponent = d;
}

int rsaGetEncryptSize(const char *message, unsigned long message_size)
{
    int encrypted_size = 0;
    for (int i = 0; i < message_size; i++)
    {
        char c = message[i];
        if (c < 0)
        {
            encrypted_size += 2;
        }
        else
        {
            encrypted_size += 1;
        }
    }

    return encrypted_size;
}

/**
 * JS Export Wrapper Functions
 */

void consoleNumber(int number)
{
    _consoleNumber(number);
}

void consoleBuffer(void *buffer)
{
    _consoleBuffer(buffer);
}

void consoleLog(const char *str)
{
    _consoleLog(str, stringLength(str));
}

void runScript(const char *str)
{
    _runScript(str, stringLength(str));
}

/**
 * Internal Global Info
 */

struct GlobalInfo
{
    // Login token
    char *token;

    // Random seeds
    unsigned int seeds[4];

    // Attributes to save engine abilities
    _uint _attributes;

    // Internal RAS keys
    struct public_key_class pub;
    struct private_key_class priv;

    // Current JS path and size
    char *jsPath;
    int jsFileSize;
};

struct GlobalInfo *__global__ = NULL;

void initGlobal(const char *jsPath, int jsFileSize)
{
    __global__ = (struct GlobalInfo *)MALLOC(sizeof(struct GlobalInfo));
    memset(__global__, 0, sizeof(struct GlobalInfo));

    // Here we use 2 prime numbers to generate keys
    const int primes[] = {PRIME0, PRIME1};
    rsaGenKeys(primes[0], primes[1], &__global__->pub, &__global__->priv);

    // Copy current JS path and size
    __global__->jsPath = allocString(jsPath);
    __global__->jsFileSize = jsFileSize;

#ifdef DEBUG

    consoleNumber(__global__->seeds[0]);
    consoleNumber(__global__->seeds[0]);
    consoleNumber(__global__->seeds[0]);
    consoleNumber(__global__->seeds[0]);
    consoleNumber(__global__->pub.exponent);
    consoleNumber(__global__->pub.modulus);
    consoleNumber(__global__->priv.exponent);
    consoleNumber(__global__->priv.modulus);
    consoleLog(__global__->jsPath);
    consoleNumber(__global__->jsFileSize);

#endif
}

void freeGlobal()
{
    FREE(__global__);
}

/**
 * Internal Random Functions
 */

void setRandomSeeds(int v1, int v2, int v3, int v4)
{
    unsigned int *seeds = __global__->seeds;
    seeds[0] = v1;
    seeds[1] = v2;
    seeds[2] = v3;
    seeds[3] = v4;
}

unsigned int random()
{
    unsigned int *seeds = __global__->seeds;
    unsigned int z1 = seeds[0], z2 = seeds[1], z3 = seeds[2], z4 = seeds[3];
    unsigned int b;
    b = ((z1 << 6) ^ z1) >> 13;
    z1 = ((z1 & 4294967294U) << 18) ^ b;
    b = ((z2 << 2) ^ z2) >> 27;
    z2 = ((z2 & 4294967288U) << 2) ^ b;
    b = ((z3 << 13) ^ z3) >> 21;
    z3 = ((z3 & 4294967280U) << 7) ^ b;
    b = ((z4 << 3) ^ z4) >> 12;
    z4 = ((z4 & 4294967168U) << 13) ^ b;
    setRandomSeeds(z1, z2, z3, z4);
    return (z1 ^ z2 ^ z3 ^ z4);
}

unsigned int randomUint(_min, _max)
{
    return (random() % (_max - _min + 1)) + _min;
}

/**
 * Auth Main Functions
 */

// Download file
any requestFileSize()
{
    _requestFileSize(__global__->jsPath);
}

// Recv file content
any onRecvFileSize(const char *path, int size)
{
#ifdef DEBUG
    consoleLog(__global__->jsPath);
    consoleLog(path);
#endif

    // If it's download JS file then validate it
    if (stringCompare(__global__->jsPath, path, false) == 0)
    {
#ifdef DEBUG
        consoleNumber(size);
        consoleNumber(__global__->jsFileSize);
#endif
        if (__global__->jsFileSize != size)
        {
            // Hmmm ... you are a hacker .... Let me show something for you
            __global__->_attributes |= 0x0004010;
        }
        else
        {
            // File size is OK now check the MD5 instead
        }
    }

#ifdef DEBUG
    consoleNumber(__global__->_attributes);
#endif
}

// Login to get token
any login(const char *token)
{
    // Copy token
    __global__->token = allocString(token);

    _login(__global__->token);
    
#ifdef DEBUG

    consoleLog(token);

#endif
}

// Encode string
any encodeString(const char *string)
{
    int length = stringLength(string);
    int encrypted_size = rsaGetEncryptSize(string, length);

    long long *encrypted = (long long *)MALLOC(sizeof(long long) * (encrypted_size + 1));

    struct public_key_class *pub = &__global__->pub;

    int index = 0;
    encrypted[index++] = rsa_modExp(encrypted_size, pub->exponent, pub->modulus);

    for (int i = 0; i < length; i++)
    {
        char c = string[i];
        if (c < 0)
        {
            encrypted[index++] = rsa_modExp(randomUint(1, 7), pub->exponent, pub->modulus);
            encrypted[index++] = rsa_modExp(-c, pub->exponent, pub->modulus);
        }
        else
        {
            encrypted[index++] = rsa_modExp(c, pub->exponent, pub->modulus);
        }
    }

    return encrypted;
}

// Decode string
any decodeString(const long long *buffer)
{
    struct private_key_class *priv = &__global__->priv;

    long long size = rsa_modExp(buffer[0], priv->exponent, priv->modulus);
    if (!size)
        return NULL;

    char *decrypted = (char *)MALLOC(size + 1);

    // Now we go through each 8-byte chunk and decrypt it.
    int index = 0;
    for (int i = 0; i < size; i++)
    {
        long long c = rsa_modExp(buffer[1 + i], priv->exponent, priv->modulus);
        if (c <= 7)
        {
            i++;
            decrypted[index++] = -rsa_modExp(buffer[1 + i], priv->exponent, priv->modulus);
        }
        else
        {
            decrypted[index++] = c;
        }
    }

    decrypted[index++] = 0;

    return decrypted;
}

any getAttributes()
{
    return __global__->_attributes;
}

any getRandomValue()
{
    return random();
}

any eval(const char *script)
{
    runScript(script);
}