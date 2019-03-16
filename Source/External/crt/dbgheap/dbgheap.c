// ---- dbgheap.c ----

/*
 * The following values are non-zero, constant, odd,
 * large, and atypical
 *      Non-zero values help find bugs assuming zero
 *      filled data.
 *      Constant values are good so that memory filling
 *      is deterministic (to help make bugs reproducable).
 *      Of course it is bad if the constant filling of
 *      weird values masks a bug.
 *      Mathematically odd numbers are good for finding
 *      bugs assuming a cleared lower bit.
 *      Large numbers (byte values at least) are less
 *      typical, and are good at finding bad addresses.
 *      Atypical values (i.e. not too often) are good
 *      since they typically cause early detection in code.
 *      For the case of no-man's land and free blocks, if
 *      you store to any of these locations, the memory
 *      integrity checker will detect it.
 */

static unsigned char _bNoMansLandFill = 0xFD;
  /* fill no-man's land with this */
static unsigned char _bDeadLandFill   = 0xDD;
  /* fill free objects with this */
static unsigned char _bCleanLandFill  = 0xCD;
  /* fill new objects with this */
static unsigned char _bAlignLandFill  = 0xBD;
  /* fill no-man's land for aligned routines */