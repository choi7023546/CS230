/* 
 * CS:APP Data Lab 
 * 
 * <choi jee young and 20150774>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

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

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

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


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 8.0.0.  Version 8.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2014, plus Amendment 1 (published
   2015-05-15).  */
/* We do not support C11 <threads.h>.  */
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  // by the De Morgan's law
  int result;
  result = ~(~x|~y);
  return result;
}
/* 
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96) = 0x20
     96 = 1100000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2 
 */
int leastBitPos(int x) {
    // if converse 0,1 and add 1, it remains only the least bit when apply &.
    int opposite = ~x +1;
    return (opposite & x);

}

/* 
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c) {
    // we have to move c to nth byte. one byte is 8 bits, so multiply 8 to n first and move 11111111 (= 0xFF) to that position.
    // nth byte of x have to be 00000000. 
     return (~((0xFF)<<(n<<3)) & x) | (c<<(n<<3)) ;
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
    // if x is 0, return 1. if x is not 0, return 0.
    // we can determine that x is not 0, if sign of x and sign of negate x are different.

    int negate_x = ~x+1;  
    return (((x>>31) & 0x1) | ((negate_x>>31) & 0x1)) ^ 0x1;
}
/*
 * leftBitCount - returns count of number of consective 1's in
 *     left-hand (most significant) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Rating: 4
 */
int leftBitCount(int x) {
    int result = x & (x>>1);
    int temp = result>>2;
    result = result & temp;
    temp = result>>4;
    result = result & temp;
    temp = result>>8;
    result = result & temp;
    temp = result>>16;
    result = result & temp;
    temp = result>>32;
    result = result & temp;

    int mask2 = 0x55<<24 + 0x55<<16 + 0x55<<8 + 0x55;
    int mask4 = (0x33<<24) + (0x33<<16) + (0x33<<8) + 0x33; 
    int mask8 = (0xF<<24) + (0xF<<16) + (0xF<<8) + 0xF;
    int mask16 = (0xFF<<16) + 0xFF;
    int mask32 = (0xFF<<8) + 0xFF; 

    int a1 = (result&mask2) + ((result>>1)&mask2);
    int a2 = (a1&mask4) + ((a1>>2)&mask4);
    int a3 = (a2&mask8) + ((a2>>4)&mask8);
    int a4 = (a3&mask16) + ((a3>>8)&mask16);
    int a5 = (a4&mask32) + ((a4>>16)&mask32);

    return a5;
}
/* 
 * TMax - return maximum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmax(void) {
    // maximum two's complement integer is when sign bit is 0 and rest of bits are 1.
    // so we have to inverse 0x40000000 (is same with move 31 bits of 0x1) 
     int c_n = 1;
     return ~(c_n<<31);
}
/* 
 * implication - return x -> y in propositional logic - 0 for false, 1
 * for true
 *   Example: implication(1,1) = 1
 *            implication(1,0) = 0
 *   Legal ops: ! ~ ^ |
 *   Max ops: 5
 *   Rating: 2
 */
int implication(int x, int y) {
    // by definition of implication in descrete mathematics, not x or y
    return (!x)|(y);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
    return ~x+1;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
    // if x is true, return y. if x is false, return z.
    // if we want to get y or z , we have to use '&' operation with 0xffffffff
    // if x is true, !!x is 1 and !x is 0
    // below expression means that if x is true !x+(~0) is 0xffffffff and !!x+(~0) is 0
    // therefore, we can get y and ignore z.
    // opposite case is same as explained
    return (y&(!x+(~0))) + (z&(!!x+(~0)));
}
/* 
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
    // case 1 : sign x and sign y are different
    // there is no overflow case
    // case 2 : sign x and sign y are same
    // if both signs and sign of x+y, this is overflow
    int x_sign = (x>>31)&0x1;
    int y_sign = (y>>31)&0x1;
    int add_sign = ((x+y)>>31)&0x1;
    

    return (x_sign^y_sign) | !((x_sign^y_sign)|(x_sign^add_sign));

}
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
    int x_sign = (x>>31);
    int y_sign = (y>>31);
    /* case1 covers when sign of x and y are same 
    x_sign^y_sign will be 0, so inverse it to True.
    */
    int case1 = !(x_sign^y_sign) & !((x+(~y))>>31); 
    /* case2 covers when sign of x and y are different
    if sign of x is 0, return 1. if sign of y is 0, return0.
    */

    int case2 = !(x_sign) & y_sign;

  return case1 | case2;
}
/*
 * satMul3 - multiplies by 3, saturating to Tmin or Tmax if overflow
 *  Examples: satMul3(0x10000000) = 0x30000000
 *            satMul3(0x30000000) = 0x7FFFFFFF (Saturate to TMax)
 *            satMul3(0x70000000) = 0x7FFFFFFF (Saturate to TMax)
 *            satMul3(0xD0000000) = 0x80000000 (Saturate to TMin)
 *            satMul3(0xA0000000) = 0x80000000 (Saturate to TMin)
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 3
 */
int satMul3(int x) {
    
    // we have to check signs of x, multi2, multi3. if one of them is different, it is overflow.
    // if overflow is 1, return TMax or TMin(it depends on sign of x).
    // if overflow is 0. return value of multi3.
    int multi2 = x+x;
    int multi3 = x+x+x;
    int sign_x = 0x1 & (x>>31);
    int sign_m2 = 0x1 & (multi2>>31);
    int sign_m3 = 0x1 & (multi3>>31);
    int overflow = (sign_x ^ sign_m2) | (sign_m2 ^ sign_m3);
    return ((~(!overflow)+1) & multi3) | ((~(overflow)+1) & (sign_x + ~(0x1<<31)));


}
/* 
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) {
    // make uf to absolute value 
    unsigned sign = 0x1 << 31;
    unsigned u_mask = ~sign;
    // plus NaN means infinite. if some value is bigger than plus NaN, it will be all NaN. 
    unsigned plus_NaN = 0xFF << 23;
    unsigned result = u_mask & uf;
    
    if(result>plus_NaN){
        return uf;
    }
    else{
        return result;
    }
}
/* 
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf) {
    
    unsigned exp = (uf>>23) & 0xFF ;
    unsigned frac = uf & 0x7FFFFF;
    unsigned bias = 0x7F;
    unsigned result = frac;
    
    // infinite case
    if(exp==0xFF) {       
        return 0x80000000u;
    }
    // denormalized case and nomalized case that less than 1. make these cases to zero. 
    if(exp<bias){
        return 0;
    }   
    // nomalized case
    // overflow case
    exp = exp-bias;
    if(exp>=31) {
        
        return 0x80000000u;
    }
   
    if(exp>22) {
        result = frac << (exp-23);
    }
    else{
        result = frac >> (23-exp);    
    } 
    
    result = result +(1<<exp);
    // reverse to minus if sign of x is 1
    if((uf>>31&0x1)==1){
        return - result;
    }
    else{
        return result;
    }

}
