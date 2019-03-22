#define DEBUG 1

#define PRIME0 211
#define PRIME1 104381

/**
 * Typedef
 */

#ifndef false
#	define false 0
#endif

#ifndef true
#	define true 1
#endif

#ifndef size_t
#	define size_t unsigned int
#endif

#ifndef NULL
#	ifdef __cplusplus
#		define NULL 0
#	else
#		define NULL ((void*)0)
#	endif
#endif

/**
 * Internal Structures
 */

struct public_key_class {
	long long modulus;
	long long exponent;
};

struct private_key_class {
	long long modulus;
	long long exponent;
};

/**
 * JS Export Functions
 */
#ifdef __cplusplus
extern "C" {
#endif
void _exit(int code);

void* _malloc(int size);
void _free(void* buffer);

void _consoleNumber(int number);
void _consoleBuffer(void* buffer);
void _consoleLog(const char* offset, int len);

void _runScript(const char* script, int len);

void _requestFileSize(const char* path);
#ifdef __cplusplus
}
#endif

#define MALLOC(size) _malloc(size)
#define FREE(buffer)          \
	if (buffer != NULL) {     \
		_free((void*)buffer); \
		buffer = NULL;        \
	}

/**
 * Internal System Functions
 */

#ifdef __cplusplus
extern "C" {
#endif

unsigned int random();

#ifdef __cplusplus
}
#endif

void* memset(void* s, int c, int count) {
	char* xs = (char*)s;

	while (count--)
		*xs++ = c;

	return s;
}

void* memcpy(void* dest, const void* src, int count) {
	char* tmp = (char*)dest;
	const char* s = (const char*)src;

	while (count--)
		*tmp++ = *s++;
	return dest;
}

void* memmove(void* dest, const void* src, int count) {
	char* tmp;
	const char* s;

	if (dest <= src) {
		tmp = (char*)dest;
		s = (const char*)src;
		while (count--)
			*tmp++ = *s++;
	} else {
		tmp = (char*)dest;
		tmp += count;
		s = (const char*)src;
		s += count;
		while (count--)
			*--tmp = *--s;
	}
	return dest;
}

int memcmp(const void* cs, const void* ct, int count) {
	const unsigned char *su1, *su2;
	int res = 0;

	for (su1 = (const unsigned char*)cs, su2 = (const unsigned char*)ct; 0 < count; ++su1, ++su2, count--)
		if ((res = *su1 - *su2) != 0)
			break;
	return res;
}

/**
 * Internal Util Functions
 */

int isPrime(int n) {
	if (n == 1)
		return false;

	for (int i = 2; i <= n / 2; ++i) {
		// condition for nonprime number
		if (n % i == 0)
			return true;
	}

	return false;
}

int toUpper(int c) {
	if (c >= 'a' && c <= 'z')
		return c + ('A' - 'a');

	return c;
}

int toLower(int c) {
	if (c >= 'A' && c <= 'Z')
		return c + ('a' - 'A');

	return c;
}

int stringEquals(const char* s1, const char* s2, int ignoreCase) {
	int c1 = 0, c2 = 0;

	do {
		c1 = *s1++;
		c2 = *s2++;

		if (ignoreCase) {
			c1 = toLower(c1);
			c2 = toLower(c2);
		}

		if (c1 != c2) {
			return false;
		}

	} while (c1 && c2);

	return true;
}

int stringLength(const char* str) {
	int length = 0;
	while (*str++) {
		length++;
	}

	return length;
}

int searchStringL2R(const char* s1, const char* s2) {
	const char* _s1 = s1;

	int l1, l2;

	l2 = stringLength(s2);
	if (!l2)
		return -1;

	l1 = stringLength(s1);
	while (l1 >= l2) {
		l1--;
		if (!memcmp(s1, s2, l2))
			return s1 - _s1;
		s1++;
	}

	return -1;
}

char* copyString(char* des, const char* src, int length) {
	if (!length) {
		return (char*)NULL;
	}

	char* _des = des;
	while (*src) {
		*des++ = *src++;

		if (length != -1) {
			length--;

			if (!length) {
				break;
			}
		}
	}

	*des = 0;

	return _des;
}

void mixString(char* src) {
	while (*src++) {
		*src = random() % 255;
		*src ^= random() % 255;
	}
}

char* allocString(const char* src) {
	int length = stringLength(src);
	char* des = (char*)MALLOC(length + 1);
	copyString(des, src, length);

	return des;
}

char* appendString(char* des, const char* src, int clear) {
	char* _des = des;

	if (clear) {
		des[0] = 0;
	}

	while (*des++) {
	}

	while (*src) {
		*des++ = *src++;
	}

	*des = 0;

	return _des;
}

char* subString(const char* src, int start, int end) {
	int length = end - start;
	char* des = (char*)MALLOC(length + 1);
	copyString(des, src + start, length);
	return des;
}

/**
 * JS Export Wrapper Functions
 */

void consoleNumber(int number) {
	_consoleNumber(number);
}

void consoleBuffer(void* buffer) {
	_consoleBuffer(buffer);
}

void consoleLog(const char* str) {
	_consoleLog(str, stringLength(str));
}

void runScript(const char* str) {
	_runScript(str, stringLength(str));
}

/**
 * JSON Parser
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * JSON type identifier. Basic types are:
 * 	o Object
 * 	o Array
 * 	o String
 * 	o Other primitive: number, boolean (true/false) or null
 */
typedef enum {
	JSMN_UNDEFINED = 0,
	JSMN_OBJECT = 1,
	JSMN_ARRAY = 2,
	JSMN_STRING = 3,
	JSMN_PRIMITIVE = 4
} jsmntype_t;

enum jsmnerr {
	/* Not enough tokens were provided */
	JSMN_ERROR_NOMEM = -1,
	/* Invalid character inside JSON string */
	JSMN_ERROR_INVAL = -2,
	/* The string is not a full JSON packet, more bytes expected */
	JSMN_ERROR_PART = -3
};

#define JSMN_PARENT_LINKS

/**
 * JSON token description.
 * type		type (object, array, string etc.)
 * start	start position in JSON data string
 * end		end position in JSON data string
 */
typedef struct {
	jsmntype_t type;
	int start;
	int end;
	int size;
#ifdef JSMN_PARENT_LINKS
	int parent;
#endif
} jsmntok_t;

/**
 * JSON parser. Contains an array of token blocks available. Also stores
 * the string being parsed now and current position in that string
 */
typedef struct {
	unsigned int pos; /* offset in the JSON string */
	unsigned int toknext; /* next token to allocate */
	int toksuper; /* superior token node, e.g parent object or array */
} jsmn_parser;

/**
 * Easy to read JSON token with jsmntok_t structure
 */
typedef struct JSONToken {
	char* tokenName;
	const jsmntok_t* token;
	struct JSONToken* parent;
	struct JSONToken* child;
	struct JSONToken* next;
} JSONToken;

/**
 * Create JSON tokens.
 */
JSONToken* parseJSONString(const char* str, int* number);

/**
 * Free JSON tokens.
 */
void freeJSONToken(JSONToken* tokens, int number);

/**
 * Create JSON parser over an array of tokens
 */
void jsmn_init(jsmn_parser* parser);

/**
 * Run JSON parser. It parses a JSON data string into and array of tokens, each describing
 * a single JSON object.
 */
int jsmn_parse(jsmn_parser* parser, const char* js, size_t len,
               jsmntok_t* tokens, unsigned int num_tokens);

#ifdef __cplusplus
}
#endif

/**
 * Allocates a fresh unused token from the token pool.
 */
static jsmntok_t* jsmn_alloc_token(jsmn_parser* parser,
                                   jsmntok_t* tokens, size_t num_tokens) {
	jsmntok_t* tok;
	if (parser->toknext >= num_tokens) {
		return NULL;
	}
	tok = &tokens[parser->toknext++];
	tok->start = tok->end = -1;
	tok->size = 0;
#ifdef JSMN_PARENT_LINKS
	tok->parent = -1;
#endif
	return tok;
}

/**
 * Fills token type and boundaries.
 */
static void jsmn_fill_token(jsmntok_t* token, jsmntype_t type,
                            int start, int end) {
	token->type = type;
	token->start = start;
	token->end = end;
	token->size = 0;
}

/**
 * Fills next available token with JSON primitive.
 */
static int jsmn_parse_primitive(jsmn_parser* parser, const char* js,
                                size_t len, jsmntok_t* tokens, size_t num_tokens) {
	jsmntok_t* token;
	int start;

	start = parser->pos;

	for (; parser->pos < len && js[parser->pos] != '\0'; parser->pos++) {
		switch (js[parser->pos]) {
#ifndef JSMN_STRICT
			/* In strict mode primitive must be followed by "," or "}" or "]" */
		case ':':
#endif
		case '\t':
		case '\r':
		case '\n':
		case ' ':
		case ',':
		case ']':
		case '}':
			goto found;
		}
		if (js[parser->pos] < 32 || js[parser->pos] >= 127) {
			parser->pos = start;
			return JSMN_ERROR_INVAL;
		}
	}
#ifdef JSMN_STRICT
	/* In strict mode primitive must be followed by a comma/object/array */
	parser->pos = start;
	return JSMN_ERROR_PART;
#endif

found:
	if (tokens == NULL) {
		parser->pos--;
		return 0;
	}
	token = jsmn_alloc_token(parser, tokens, num_tokens);
	if (token == NULL) {
		parser->pos = start;
		return JSMN_ERROR_NOMEM;
	}
	jsmn_fill_token(token, JSMN_PRIMITIVE, start, parser->pos);
#ifdef JSMN_PARENT_LINKS
	token->parent = parser->toksuper;
#endif
	parser->pos--;
	return 0;
}

/**
 * Fills next token with JSON string.
 */
static int jsmn_parse_string(jsmn_parser* parser, const char* js,
                             size_t len, jsmntok_t* tokens, size_t num_tokens) {
	jsmntok_t* token;

	int start = parser->pos;

	parser->pos++;

	/* Skip starting quote */
	for (; parser->pos < len && js[parser->pos] != '\0'; parser->pos++) {
		char c = js[parser->pos];

		/* Quote: end of string */
		if (c == '\"') {
			if (tokens == NULL) {
				return 0;
			}
			token = jsmn_alloc_token(parser, tokens, num_tokens);
			if (token == NULL) {
				parser->pos = start;
				return JSMN_ERROR_NOMEM;
			}
			jsmn_fill_token(token, JSMN_STRING, start + 1, parser->pos);
#ifdef JSMN_PARENT_LINKS
			token->parent = parser->toksuper;
#endif
			return 0;
		}

		/* Backslash: Quoted symbol expected */
		if (c == '\\' && parser->pos + 1 < len) {
			int i;
			parser->pos++;
			switch (js[parser->pos]) {
				/* Allowed escaped symbols */
			case '\"':
			case '/':
			case '\\':
			case 'b':
			case 'f':
			case 'r':
			case 'n':
			case 't':
				break;
				/* Allows escaped symbol \uXXXX */
			case 'u':
				parser->pos++;
				for (i = 0; i < 4 && parser->pos < len && js[parser->pos] != '\0'; i++) {
					/* If it isn't a hex character we have an error */
					if (!((js[parser->pos] >= 48 && js[parser->pos] <= 57) || /* 0-9 */
					      (js[parser->pos] >= 65 && js[parser->pos] <= 70) || /* A-F */
					      (js[parser->pos] >= 97 && js[parser->pos] <= 102))) { /* a-f */
						parser->pos = start;
						return JSMN_ERROR_INVAL;
					}
					parser->pos++;
				}
				parser->pos--;
				break;
				/* Unexpected symbol */
			default:
				parser->pos = start;
				return JSMN_ERROR_INVAL;
			}
		}
	}
	parser->pos = start;
	return JSMN_ERROR_PART;
}

/**
 * Parse JSON string and fill tokens.
 */
int jsmn_parse(jsmn_parser* parser, const char* js, size_t len,
               jsmntok_t* tokens, unsigned int num_tokens) {
	int r;
	int i;
	jsmntok_t* token;
	int count = parser->toknext;

	for (; parser->pos < len && js[parser->pos] != '\0'; parser->pos++) {
		char c;
		jsmntype_t type;

		c = js[parser->pos];
		switch (c) {
		case '{':
		case '[':
			count++;
			if (tokens == NULL) {
				break;
			}
			token = jsmn_alloc_token(parser, tokens, num_tokens);
			if (token == NULL)
				return JSMN_ERROR_NOMEM;
			if (parser->toksuper != -1) {
				tokens[parser->toksuper].size++;
#ifdef JSMN_PARENT_LINKS
				token->parent = parser->toksuper;
#endif
			}
			token->type = (c == '{' ? JSMN_OBJECT : JSMN_ARRAY);
			token->start = parser->pos;
			parser->toksuper = parser->toknext - 1;
			break;
		case '}':
		case ']':
			if (tokens == NULL)
				break;
			type = (c == '}' ? JSMN_OBJECT : JSMN_ARRAY);
#ifdef JSMN_PARENT_LINKS
			if (parser->toknext < 1) {
				return JSMN_ERROR_INVAL;
			}
			token = &tokens[parser->toknext - 1];
			for (;;) {
				if (token->start != -1 && token->end == -1) {
					if (token->type != type) {
						return JSMN_ERROR_INVAL;
					}
					token->end = parser->pos + 1;
					parser->toksuper = token->parent;
					break;
				}
				if (token->parent == -1) {
					if (token->type != type || parser->toksuper == -1) {
						return JSMN_ERROR_INVAL;
					}
					break;
				}
				token = &tokens[token->parent];
			}
#else
			for (i = parser->toknext - 1; i >= 0; i--) {
				token = &tokens[i];
				if (token->start != -1 && token->end == -1) {
					if (token->type != type) {
						return JSMN_ERROR_INVAL;
					}
					parser->toksuper = -1;
					token->end = parser->pos + 1;
					break;
				}
			}
			/* Error if unmatched closing bracket */
			if (i == -1) return JSMN_ERROR_INVAL;
			for (; i >= 0; i--) {
				token = &tokens[i];
				if (token->start != -1 && token->end == -1) {
					parser->toksuper = i;
					break;
				}
			}
#endif
			break;
		case '\"':
			r = jsmn_parse_string(parser, js, len, tokens, num_tokens);
			if (r < 0) return r;
			count++;
			if (parser->toksuper != -1 && tokens != NULL)
				tokens[parser->toksuper].size++;
			break;
		case '\t':
		case '\r':
		case '\n':
		case ' ':
			break;
		case ':':
			parser->toksuper = parser->toknext - 1;
			break;
		case ',':
			if (tokens != NULL && parser->toksuper != -1 &&
			    tokens[parser->toksuper].type != JSMN_ARRAY &&
			    tokens[parser->toksuper].type != JSMN_OBJECT) {
#ifdef JSMN_PARENT_LINKS
				parser->toksuper = tokens[parser->toksuper].parent;
#else
				for (i = parser->toknext - 1; i >= 0; i--) {
					if (tokens[i].type == JSMN_ARRAY || tokens[i].type == JSMN_OBJECT) {
						if (tokens[i].start != -1 && tokens[i].end == -1) {
							parser->toksuper = i;
							break;
						}
					}
				}
#endif
			}
			break;
#ifdef JSMN_STRICT
			/* In strict mode primitives are: numbers and booleans */
		case '-':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 't':
		case 'f':
		case 'n':
			/* And they must not be keys of the object */
			if (tokens != NULL && parser->toksuper != -1) {
				jsmntok_t* t = &tokens[parser->toksuper];
				if (t->type == JSMN_OBJECT ||
				    (t->type == JSMN_STRING && t->size != 0)) {
					return JSMN_ERROR_INVAL;
				}
			}
#else
			/* In non-strict mode every unquoted value is a primitive */
		default:
#endif
			r = jsmn_parse_primitive(parser, js, len, tokens, num_tokens);
			if (r < 0) return r;
			count++;
			if (parser->toksuper != -1 && tokens != NULL)
				tokens[parser->toksuper].size++;
			break;

#ifdef JSMN_STRICT
			/* Unexpected char in strict mode */
		default:
			return JSMN_ERROR_INVAL;
#endif
		}
	}

	if (tokens != NULL) {
		for (i = parser->toknext - 1; i >= 0; i--) {
			/* Unmatched opened object or array */
			if (tokens[i].start != -1 && tokens[i].end == -1) {
				return JSMN_ERROR_PART;
			}
		}
	}

	return count;
}

/**
 * Creates a new parser based over a given  buffer with an array of tokens
 * available.
 */
void jsmn_init(jsmn_parser* parser) {
	parser->pos = 0;
	parser->toknext = 0;
	parser->toksuper = -1;
}

JSONToken* parseJSONString(const char* str, int* number) {
	jsmn_parser* p = (jsmn_parser*)MALLOC(sizeof(jsmn_parser));
	jsmn_init(p);

	const int bufferNumber = 1024;
	jsmntok_t* tokens = (jsmntok_t*)MALLOC(bufferNumber * sizeof(jsmntok_t));
	memset(tokens, 0, sizeof(jsmntok_t) * bufferNumber);
	int tokenNumber = jsmn_parse(p, str, stringLength(str), tokens, bufferNumber);

	if (number) {
		*number = tokenNumber;
	}

	int bufferSize = tokenNumber * sizeof(JSONToken);
	JSONToken* jsonTokens = (JSONToken*)MALLOC(bufferSize);
	memset(jsonTokens, 0, bufferSize);
	for (int i = 0; i < tokenNumber; i++) {
		const jsmntok_t* token = &tokens[i];
		if (token->type != JSMN_STRING && token->type != JSMN_PRIMITIVE) {
			continue;
		}

		JSONToken* jsonToken = &jsonTokens[i];
		jsonToken->tokenName = subString(str, token->start, token->end);
		jsonToken->token = token;

		if (token->parent != -1) {
			jsonToken->parent = &jsonTokens[token->parent];

			JSONToken* parent = jsonToken->parent;
			if (parent->child) {
				parent->child->next = &jsonTokens[i];
			} else {
				parent->child = &jsonTokens[i];
			}
		}
	}

	return jsonTokens;
}

void freeJSONToken(JSONToken* tokens, int number) {
	for (int i = 0; i < number; i++) {
		JSONToken* jsonToken = &tokens[i];
		FREE(jsonToken->tokenName);
	}

	FREE(tokens);
}

/**
 * RSA Encode/Decode Functions
 */

// This should totally be in the math library.
long long gcd(long long a, long long b) {
	long long c;
	while (a != 0) {
		c = a;
		a = b % a;
		b = c;
	}
	return b;
}

long long ExtEuclid(long long a, long long b) {
	long long x = 0, y = 1, u = 1, v = 0, gcd = b, m, n, q, r;
	while (a != 0) {
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

long long rsa_modExp(long long b, long long e, long long m) {
	if (b < 0 || e < 0 || m <= 0) {
		_exit(1);
	}
	b = b % m;
	if (e == 0)
		return 1;
	if (e == 1)
		return b;
	if (e % 2 == 0) {
		return (rsa_modExp(b * b % m, e / 2, m) % m);
	}
	if (e % 2 == 1) {
		return (b * rsa_modExp(b, (e - 1), m) % m);
	}

	return 0;
}

// Calling this function will generate a public and private key and store them in the pointers
// it is given.
void rsaGenKeys(long long p, long long q, struct public_key_class* pub, struct private_key_class* priv) {
	long long e = 257; // powl(2, 8) + 1;

	long long max = p * q;
	long long phi_max = (p - 1) * (q - 1);

	// Next, we need to choose a,b, so that a*max+b*e = gcd(max,e). We actually only need b
	// here, and in keeping with the usual notation of RSA we'll call it d. We'd also like
	// to make sure we get a representation of d as positive, hence the while loop.
	long long d = ExtEuclid(phi_max, e);
	while (d < 0) {
		d = d + phi_max;
	}

	// We now store the public / private keys in the appropriate structs
	pub->modulus = max;
	pub->exponent = e;

	priv->modulus = max;
	priv->exponent = d;
}

int rsaGetEncryptSize(const char* message, int message_size) {
	int encrypted_size = 0;
	for (int i = 0; i < message_size; i++) {
		char c = message[i];
		if (c < 0) {
			encrypted_size += 2;
		} else {
			encrypted_size += 1;
		}
	}

	return encrypted_size;
}

/**
 * Internal Global Info
 */

struct GlobalInfo {
	// Random seeds
	unsigned int seeds[4];

	// Attributes to save engine abilities
	unsigned int attributes;
	// The attribute time stamp to validate with current local time
	char* timeStamp;

	// Internal RSA keys
	struct public_key_class pub;
	struct private_key_class priv;

	// Current JS path and size
	char* jsPath;
	int jsFileSize;
};

struct GlobalInfo* __global__ = NULL;

void initGlobal(const char* jsPath, int jsFileSize) {
	__global__ = (struct GlobalInfo*)MALLOC(sizeof(struct GlobalInfo));
	memset(__global__, 0, sizeof(struct GlobalInfo));

	// Here we use 2 prime numbers to generate keys
	const int primes[] = {PRIME0, PRIME1};
	rsaGenKeys(primes[0], primes[1], &__global__->pub, &__global__->priv);

	// Copy current JS path and size
	__global__->jsPath = allocString(jsPath);
	__global__->jsFileSize = jsFileSize;

#ifdef DEBUG

	consoleNumber(__global__->pub.exponent);
	consoleNumber(__global__->pub.modulus);
	consoleNumber(__global__->priv.exponent);
	consoleNumber(__global__->priv.modulus);
	consoleLog(__global__->jsPath);
	consoleNumber(__global__->jsFileSize);

#endif
}

void freeGlobal() {
	FREE(__global__);
}

/**
 * Internal Random Functions
 */

void setRandomSeeds(int v1, int v2, int v3, int v4) {
	unsigned int* seeds = __global__->seeds;
	seeds[0] = v1;
	seeds[1] = v2;
	seeds[2] = v3;
	seeds[3] = v4;
}

unsigned int random() {
	unsigned int* seeds = __global__->seeds;
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

unsigned int randomUint(_min, _max) {
	return (random() % (_max - _min + 1)) + _min;
}

/**
 * Auth Main Functions
 */

// Download file
void requestFileSize() {
	_requestFileSize(__global__->jsPath);
}

// Recv file content
void onRecvFileSize(const char* path, int size) {
#ifdef DEBUG
	consoleLog(__global__->jsPath);
	consoleLog(path);
#endif

	// Get the file path
	path = path ? path : "";

	// If it's download JS file then validate it
	if (__global__->jsPath[0] && path[0] && stringEquals(__global__->jsPath, path, false)) {
#ifdef DEBUG
		consoleNumber(size);
		consoleNumber(__global__->jsFileSize);
#endif
		if (__global__->jsFileSize && __global__->jsFileSize != size) {
			// Hmmm ... you are a hacker .... Let me show something for you
			__global__->attributes |= 0x0004010;
		} else {
			// File size is OK now check the MD5 instead
		}
	}

#ifdef DEBUG
	consoleNumber(__global__->attributes);
#endif
}

// Encode string
long long* encodeString(const char* string) {
	int length = stringLength(string);
	int encrypted_size = rsaGetEncryptSize(string, length);
	long long* encrypted = (long long*)MALLOC(sizeof(long long) * (encrypted_size + 1));

	struct public_key_class* pub = &__global__->pub;

	int index = 0;
	encrypted[index++] = rsa_modExp(encrypted_size, pub->exponent, pub->modulus);

	for (int i = 0; i < length; i++) {
		char c = string[i];
		if (c < 0) {
			encrypted[index++] = rsa_modExp(randomUint(1, 7), pub->exponent, pub->modulus);
			encrypted[index++] = rsa_modExp(-c, pub->exponent, pub->modulus);
		} else {
			encrypted[index++] = rsa_modExp(c, pub->exponent, pub->modulus);
		}
	}

	return encrypted;
}

// Decode string
char* decodeString(const long long* buffer) {
	struct private_key_class* priv = &__global__->priv;

	int size = (int)rsa_modExp(buffer[0], priv->exponent, priv->modulus);
	if (!size)
		return NULL;

	char* decrypted = (char*)MALLOC(size + 1);

	// Now we go through each 8-byte chunk and decrypt it.
	int index = 0;
	for (int i = 0; i < size; i++) {
		long long c = rsa_modExp(buffer[1 + i], priv->exponent, priv->modulus);
		if (c <= 7) {
			i++;
			decrypted[index++] = (char)-rsa_modExp(buffer[1 + i], priv->exponent, priv->modulus);
		} else {
			decrypted[index++] = (char)c;
		}
	}

	decrypted[index++] = 0;

	return decrypted;
}

unsigned int getAttributes() {
	return __global__->attributes;
}

const char* getTimeStamp() {
	return __global__->timeStamp;
}

void setAttributes(const long long* buffer) {
	char* str = decodeString(buffer);
	if (!str) {
		return;
	}

	int* number = (int*)MALLOC(sizeof(int));
	JSONToken* jsonToken = parseJSONString(str, number);
	if (!jsonToken) {
		return;
	}

	// Get the 'timestamp'
	__global__->timeStamp = allocString(jsonToken->child->child->tokenName);
	consoleLog(__global__->timeStamp);

	freeJSONToken(jsonToken, *number);

	// Mix a little to save the original text
	mixString(str);

	FREE(number);
	FREE(str);
}

unsigned int getRandomValue() {
	return random();
}

void eval(const char* script) {
	runScript(script);
}