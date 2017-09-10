/* 
 * CS:APP Data Lab 
 * 
 */

/*

INTEGER CODING RULES:
 
  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.


FLOATING POINT CODING RULES

  For the problems that require you to implent floating-point operations,
  the coding rules are less strict.  You are allowed to use looping and
  conditional control.  You are allowed to use both ints and unsigneds.
  You can use arbitrary integer and unsigned constants.

  You are expressly forbidden to:
    1. Define or use any macros.
    2. Define any additional functions in this file.
    3. Call any functions.
    4. Use any form of casting.
    5. Use any data type other than int or unsigned.  This means that you
       cannot use arrays, structs, or unions.
    6. Use any floating point data types, operations, or constants.
 */



/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  return ~(~x | ~y);
}

/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  int temp0 = n << 3;
  int temp1 = x >> temp0;
  int temp2 = temp1 & 0xff;
  return temp2;
}

/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {

  // JJ's solution
  int seven_f__f = ~(1 << 31);
  int mask = ((seven_f__f >> n) << 1) | 1;
  return (x >> n) & mask;
  
  /*
   * my solution
  int hbit = 31; // highest bit
  int temp1 = x >> hbit;
  int msbit = temp1 & 0xFF; // most significant bit
  int msbit_zeros = msbit << hbit; // most significant bit with all zeros
  int zero_x = x & (~msbit_zeros); // zero + lowest 31-bit of x
  int zero_x_n = zero_x >> n;  // part 1: x(removed most significant bit) >> n
  int msbit_n_arith = msbit_zeros >> n;
  int msbit_n_logic = msbit_n_arith ^ (msbit_n_arith << 1);  // part 2: logical shift of the most significant bit
  int ret = zero_x_n + msbit_n_logic;
  return ret;
  */
}

/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  // Hamming Weight
  int t = 0x55 + (0x55 << 8);
  int every2mask = t + (t << 16);
  int every2 = (x & every2mask) + ((x >> 1) & every2mask);

  t = 0x33 + (0x33 << 8);
  int every4mask = t + (t << 16);
  int every4 = (every2 & every4mask) + ((every2 >> 2) & every4mask);

  t = 0x0f + (0x0f << 8);
  int every8mask = t + (t << 16);
  int every8 = (every4 & every8mask) + ((every4 >> 4) & every8mask);

  int every16mask = 0xff + (0xff << 16);
  int every16 = (every8 & every16mask) + ((every8 >> 8) & every16mask);

  int every32mask = 0xff + (0xff << 8);
  int every32 = (every16 & every32mask) + ((every16 >> 16) & every32mask);

  return every32;
}

/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  x |= x >> 16;
  x |= x >> 8;
  x |= x >> 4;
  x |= x >> 2;
  x |= x >> 1;
  return ~x & 0x1;
}

/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 0x1 << 31;
}

/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  int minus1 = ~0x0;
  int nbit = (x >> (n + minus1)) & 0x1;
  nbit |= nbit << 1;
  nbit |= nbit << 2;
  nbit |= nbit << 4;
  nbit |= nbit << 8;
  nbit |= nbit << 16;
  int lbits = x >> n;
  return !(nbit ^ lbits);
}

/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
  int hbit = (x >> 31) & 0x1;
  int nbits1 = !!(x << (~n + 1)); // whether bits from 1 to n include 1's
  int adj = (hbit & !!n) & nbits1; // adjust for negative odd numbers.
  return (x >> n) + adj;
}

/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x + 1;
}

/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
  int hbit = (x >> 31) & 0x1;
  return !hbit & !!x;
}

/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int mask = 0xff | 0xff << 8;
  int x1 = x >> 16; int x2 = x & mask;
  int y1 = y >> 16; int y2 = y & mask;
  int ny1 = ~y1 + 1; int ny2 = ~y2 + 1;
  int sum1 = x1 + ny1; int sum2 = x2 + ny2;
  int hbit_sum1 = (sum1 >> 31) & 0x1;
  int hbit_sum2 = (sum2 >> 31) & 0x1;
  return hbit_sum1 | (!sum1 & (hbit_sum2 | !sum2));
}

/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
  int xonly1 = x | x >> 1;
  xonly1 |= xonly1 >> 2;
  xonly1 |= xonly1 >> 4;
  xonly1 |= xonly1 >> 8;
  xonly1 |= xonly1 >> 16;
  return bitCount(xonly1 >> 1);
}

/*
Floating Point Observations:
- Say there are k bits in exp. When exp = 0x7ff...f, exp = pwr(2, k-1) - 1. That means, E = exp - bias = 0.
- Say there are j bits in frac, and "jump rate" indicate the distance between two immediate floating point numbers. 
  - When exp = 0x7ff...f, jump rate = pwr(2, -j).
  - When exp = 0x7ff...f + 1, jump rate = pwr(2, -j+1).
  - When exp = 0x7ff...f + j, jump rate = pwr(2, -j+j) = 1.
*/

/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
  int exp = (uf & 0x7f800000) >> 23;
  int frac = uf & 0x007fffff;
  if(exp == 0xff && !!frac) return uf;
  else return uf ^ 0x80000000;;
}

/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */

unsigned float_i2f(int x) {
  int s = x & 0x80000000;
  int exp = 0x80;
  int frac = 0;
  if(s) x = -x;
  if(x == 0) return x;
  else {
    int i = ilog2(x);
    exp = exp + i - 1;
    if(i >= 31) {exp = 0x9e; frac = 0;}
    else {
      int base = 1 << i;
      int leftover = x - base;
      if(i <= 23) frac = leftover << (23 - i);
      else {
        frac = leftover >> (i - 23);
        int tail_mask = 1 << (i - 23);
        int tail = leftover & (tail_mask - 1);
        int middle = 1 << (i - 24);
        int lsb = leftover & tail_mask; // the least significant bit before the tail
        if(tail > middle || (tail == middle && lsb)) frac += 1;
      }
    }
  }

  exp = exp << 23;
  return s + exp + frac;
}

/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  int s = uf & 0x80000000;
  int exp = (uf & 0x7f800000) >> 23;
  int frac = uf & 0x007fffff;
  if(exp == 0xff) return uf;
  else if(exp == 0) {
    frac = frac << 1;
    exp = exp << 23;
    return s + exp + frac;
  }
  else {
    exp += 1;
    exp = exp & 0xff;
    exp = exp << 23;
    return s + exp + frac;
  }
}
