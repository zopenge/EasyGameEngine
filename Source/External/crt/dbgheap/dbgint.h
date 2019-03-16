/*
 * For diagnostic purpose, blocks are allocated with
 *  extra information and
 * stored in a doubly-linked list.  This makes all blocks
 *  registered with
 * how big they are, when they were allocated, and what
 *  they are used for.
 */

#define nNoMansLandSize 4

typedef struct _CrtMemBlockHeader
{
        struct _CrtMemBlockHeader * pBlockHeaderNext;
        struct _CrtMemBlockHeader * pBlockHeaderPrev;
        char *                      szFileName;
        int                         nLine;
#ifdef _WIN64
        /* These items are reversed on Win64 to eliminate
   *  gaps in the struct
         * and ensure that sizeof(struct)%16 == 0, so
   *  16-byte alignment is
         * maintained in the debug heap.
         */
        int                         nBlockUse;
        size_t                      nDataSize;
#else  /* _WIN64 */
        size_t                      nDataSize;
        int                         nBlockUse;
#endif  /* _WIN64 */
        long                        lRequest;
        unsigned char               gap[nNoMansLandSize];
        /* followed by:
         *  unsigned char       data[nDataSize];
         *  unsigned char       anotherGap[nNoMansLandSize];
         */
} _CrtMemBlockHeader;

#define pbData(pblock) \
    ((unsigned char *)((_CrtMemBlockHeader *)pblock + 1))
#define pHdr(pbData) (((_CrtMemBlockHeader *)pbData)-1)