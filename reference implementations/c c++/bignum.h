/*
   This version of "bignum.h" has been slightly modified for use in
   assignment 8 of cs226 for Spring of 1999.
*/



#ifndef BIGNUM_H
#define BINNUM_H

typedef struct BigNum_tag *BigNum;

#define B BigNum

/*
   Convert an ascii string to a BigNum. Caller needs to free
   the BigNum returned after using it.
*/
extern B BigNum_fromString(const char *str);

/*
   Convert a BigNum to string. Caller needs to free
   the string returned after using it.
*/
extern char* BigNum_toString(B b);

/*
   Given two BigNums b1 and b2, perform the appropriate operation and
   returns the resulting BigNum. Again the caller needs to free
   the BigNum returned.
*/
extern B BigNum_add(B b1, B b2); /* addition */
extern B BigNum_sub(B b1, B b2); /* subtraction */
extern B BigNum_mul(B b1, B b2); /* multiplication */
extern B BigNum_div(B b1, B b2); /* division */
extern B BigNum_rem(B b1, B b2); /* modulo */

/*
   Given two BigNums b1 and b2, perform the appropriate comparison and
   returns 1 if true, or 0 if false.
*/
int BigNum_eq(B b1, B b2);  /* equality */
int BigNum_gt(B b1, B b2);  /* greater than */
int BigNum_lt(B b1, B b2);  /* less than */

extern B BigNum_neg(B b);        /* unary negation */

extern B BigNum_clone(B b);      /* cloning */


/*
   Given BigNum b, returns a pseudo-random BigNum in the range [0,b-1].
   Again the caller needs to free the BigNum returned
*/
extern B BigNum_rand(B b);


/*
   Sets the seed for the random number generator.
*/
void BigNum_srand(unsigned int seed);


extern void BigNum_free(B b);

#undef B
#endif