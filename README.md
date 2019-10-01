# 4190.308 Computer Architecture (Fall 2019)
# Project #2: Half-precision Floating Points
### Due: 11:59PM, October 21 (Monday),


## Introduction

The goal of this project is to get familiar with the floating-point representation by implementing the 16-bit half-precision floating-point representation.

## Problem specification

The half-precision (`hfp` for short) floating-point representation is a binary floating-point defined in the IEEE 754 standard that occupies 16 bits. The overall structure of the `hfp` representation is shown below. The MSB (Most Significant Bit) is used as a sign bit (`S`). The next five bits are used for exponent (`E`) with a bias value of 15. The last ten bits are used for the fractional part (`F`).

```
bit 15 14 13 12 11 10 9  8  7  6  5  4  3  2  1  0
    S  E  E  E  E  E  F  F  F  F  F  F  F  F  F  F
    ^  +-----+-----+  +------------+-------------+
    |        |                     |                       
Sign bit     |               Fraction (10 bits)
         Exponent (5 bits)                   
```

Note that the smallest positive number in the `hfp` format is 0.0000000001 x 2<sup>-14</sup> and the largest positive number is 1.1111111111 x 2<sup>15</sup>,


In C, the new type `hfp` is defined as follows.

```
typedef unsigned short int hfp;
```

Your task is to implement the following four C functions that convert `int` or `float` type values to the `hfp` format and vice versa.

```
hfp int2hfp(int n);                // convert int -> hfp
int hfp2int(hfp h);                // convert hfp -> int
hfp float2hfp(float f);            // convert float -> hfp
float hfp2float(hfp h);            // convert hfp -> float
```

## Implementation details

### int2hfp() (20 points)

 * Not all the `int`-type values can be represented in the `hfp` format because `hfp` has only ten bits of fraction and a limited range. When necessary, you should use the round-to-even rounding mode.
 * The value 0.0 in `int` should be converted to plus zero (+0.0) in `hfp`.
 * Any `int`-type value that exceeds the range of the `hfp` representation (after rounding) should be converted to the infinity in `hfp` (+&infin; or -&infin; depending on the sign).

### hfp2int() (20 points)
 * Any fractional part is dropped when `hfp`-type values are converted to integers. This is same as rounding into the integer using the round-toward-zero mode.
 * Both of -0.0 and +0.0 in `hfp` should be converted to the value 0 in `int`.
 * Convert +&infin; and -&infin; in `hfp` to the smallest number in `int` (i.e., 0x80000000).
 * +NaN and -NaN in `hfp` are also converted to the smallest number in `int` (i.e., 0x80000000).

### float2hfp() (40 points)
 * Not all the `float`-type values can be represented in the `hfp` format. When necessary, you should use the round-to-even rounding mode.
 * Any floating-point value that exceeds the range of the `hfp` representation (after rounding) should be converted to the infinity in `hfp` (+&infin; or -&infin; depending on the sign).
 * +&infin; and -&infin; in `float` should be converted to the corresponding +&infin; and -&infin; in `hfp`, respectively.
 * +NaN and -NaN in `float` should be converted to the corresponding +NaN and -NaN in `hfp`, respectively.

### hfp2float() (20 points)
 * The `hfp` type is a subset of the `float` type. Hence, all the values in `hfp` can be converted in the `float` format without any error.
 * Again, +&infin; and -&infin; in `hfp` should be converted to the corresponding +&infin; and -&infin; in `float`, respectively. +NaN and -NaN in `hfp` should be converted to the corresponding +NaN and -NaN in `float`, respectively.


## Skeleton code

We provide you with the skeleton code for this project. It can be download from Github at https://github.com/snu-csl/ca-pa2/. To download and build the skeleton code, please follow these steps:

```
$ git clone https://github.com/snu-csl/ca-pa2.git
$ cd ca-pa2
$ make
gcc -g -O2 -Wall  -c pa2-test.c -o pa2-test.o
gcc -g -O2 -Wall  -c pa2.c -o pa2.o
gcc -g -O2 -Wall  -o pa2 pa2-test.o pa2.o
```

The result of a sample run looks like this:

```
$ ./pa2

Test 1: Casting from int to hfp
int(00000000 00000000 00000000 00000001) => hfp(00000000 00001001), WRONG
int(11111111 11111111 11111111 10011011) => hfp(00000000 00001001), WRONG
int(00000000 00000000 11111111 11100001) => hfp(00000000 00001001), WRONG
int(11111111 11111111 00000000 00010000) => hfp(00000000 00001001), WRONG
int(01111111 11111111 11111111 11111111) => hfp(00000000 00001001), WRONG
int(10000000 00000000 00000000 00000000) => hfp(00000000 00001001), WRONG

Test 2: Casting from hfp to int
hfp(00000000 00000001) => int(00000000 00000000 00000000 00001001), WRONG
hfp(00101011 11111111) => int(00000000 00000000 00000000 00001001), WRONG
hfp(11011110 10001100) => int(00000000 00000000 00000000 00001001), WRONG
hfp(10000000 00000000) => int(00000000 00000000 00000000 00001001), WRONG
hfp(11111111 11111111) => int(00000000 00000000 00000000 00001001), WRONG
hfp(01111100 00000000) => int(00000000 00000000 00000000 00001001), WRONG

Test 3: Casting from float to hfp
float(00111111 10000000 00000000 00000000) => hfp(00000000 00001001), WRONG
float(00110011 01000000 00000000 00000000) => hfp(00000000 00001001), WRONG
float(00110011 00000000 00000000 00000000) => hfp(00000000 00001001), WRONG
float(00110010 10100000 00000000 00000000) => hfp(00000000 00001001), WRONG
float(01000011 11011111 11110000 00000000) => hfp(00000000 00001001), WRONG
float(01001000 01000000 00000000 00000000) => hfp(00000000 00001001), WRONG

Test 4: Casting from hfp to float
hfp(00111100 00000000) => float(01000001 00011111 11010111 00001010), WRONG
hfp(00000000 00000001) => float(01000001 00011111 11010111 00001010), WRONG
hfp(01111011 11111111) => float(01000001 00011111 11010111 00001010), WRONG
hfp(00000100 00000000) => float(01000001 00011111 11010111 00001010), WRONG
hfp(11111111 11111111) => float(01000001 00011111 11010111 00001010), WRONG
hfp(01111100 00000000) => float(01000001 00011111 11010111 00001010), WRONG
```

You are required to complete the `int2hfp()`, `hfp2int()`, `float2hfp()`, and `hfp2float()` functions in the `pa2.c` file.


## Restrictions

* You should not use any array even in the comment lines. Any source file that contains the symbol [ or ] will be rejected by the server.

* You are not allowed to use any pointers.

* You are not allowed to use the `long` or `double` data type. Any source file that contains the word `long` or `double` (even in the comment lines) will be rejected.

* Do not include any header file other than `stdio.h` and `pa2.h` in the `pa2.c` file.

* Your `pa2.c` file should not contain any `printf()` functions. Please remove them before you submit your code to the server.

* Your code should finish within a reasonable time. We will measure the time to perform a certain number of operations. If your code does not finish within a predefined threshold (e.g., 5 sec), it will be killed.

* **The top 3 fastest float2hfp() implementations will receive a 10% extra bonus.**

## Hand in instructions

* Submit only the `pa2.c` file to the submission server.

## Logistics

* You will work on this project alone.
* Only the upload submitted before the deadline will receive the full credit. 25% of the credit will be deducted for every single day delay.
* __You can use up to 5 _slip days_ during this semester__. If your submission is delayed by 1 day and if you decided to use 1 slip day, there will be no penalty. In this case, you should explicitly declare the number of slip days you want to use in the QnA board of the submission server after each submission. Saving the slip days for later projects is highly recommended!
* Any attempt to copy others' work will result in heavy penalty (for both the copier and the originator). Don't take a risk.

Have fun!

[Jin-Soo Kim](mailto:jinsoo.kim_AT_snu.ac.kr)  
[Systems Software and Architecture Laboratory](http://csl.snu.ac.kr)  
[Dept. of Computer Science and Engineering](http://cse.snu.ac.kr)  
[Seoul National University](http://www.snu.ac.kr)
