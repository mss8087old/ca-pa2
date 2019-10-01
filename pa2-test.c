//---------------------------------------------------------------
//
//  4190.308 Computer Architecture (Fall 2019)
//
//  Project #2: Half-precision Floating Points
//
//  October 1, 2019
//
//  Jin-Soo Kim (jinsoo.kim@snu.ac.kr)
//  Systems Software & Architecture Laboratory
//  Dept. of Computer Science and Engineering
//  Seoul National University
//
//---------------------------------------------------------------

#include <stdio.h>
#include "pa2.h"

#define BYTE_FORMAT 		"%c%c%c%c%c%c%c%c"
#define BYTE_TO_BITS(byte)  ((byte) & 0x80 ? '1' : '0'), \
  							((byte) & 0x40 ? '1' : '0'), \
  							((byte) & 0x20 ? '1' : '0'), \
  							((byte) & 0x10 ? '1' : '0'), \
  							((byte) & 0x08 ? '1' : '0'), \
  							((byte) & 0x04 ? '1' : '0'), \
  							((byte) & 0x02 ? '1' : '0'), \
  							((byte) & 0x01 ? '1' : '0') 

#define PRINT_WORD(s,i,p)	printf(s"("BYTE_FORMAT" ", BYTE_TO_BITS((i) >> 24));	\
							printf(BYTE_FORMAT" ", BYTE_TO_BITS((i) >> 16)); 		\
							printf(BYTE_FORMAT" ", BYTE_TO_BITS((i) >> 8)); 		\
							printf(BYTE_FORMAT")"p, BYTE_TO_BITS(i));	
#define PRINT_HWORD(s,i,p)	printf(s"("BYTE_FORMAT" ", BYTE_TO_BITS((i) >> 8));		\
							printf(BYTE_FORMAT")"p, BYTE_TO_BITS(i));	

#define PRINT_HFP(i,p)		PRINT_HWORD("hfp", i, p)
#define PRINT_FLOAT(i,p)	PRINT_WORD("float", i, p)
#define PRINT_INT(i,p)		PRINT_WORD("int", i, p)

#define HFP_INF_NAN(h)		((((h) >> 10) & 0x1f) == 0x1f)
#define FLOAT_INF_NAN(f)	((((f) >> 23) & 0xff) == 0xff)
#define TEST_INF_NAN(f,h)	(HFP_INF_NAN(h) && FLOAT_INF_NAN(f) && 						\
							((((h) >> 15) == (f) >> 31) && 								\
							(((((h) & 0x03ff) == 0) && (((f) & 0x007fffff) == 0)) || 	\
							(((h) & 0x03ff) && ((f) & 0x007fffff)))))

#define CHECK_VALUE(r,a)	printf("%s\n", ((r) == (a))? "CORRECT" : "WRONG")
#define CHECK_INF_NAN(f,h)	printf("%s\n", TEST_INF_NAN(f,h)? "CORRECT" : "WRONG")

#define N 	6


int		int_in[N]			= {	1,			-101,		65505,		-65520,		0x7fffffff,		0x80000000	};
hfp		int2hfp_ans[N]		= { 0x3c00,		0xd650,		0x7bff,		0xfc00,		0x7c00,			0x8000		};

hfp		hfp_in[N]			= { 0x0001,		0x2bff,		0xde8c,		0x8000,		0xffff,			0x7c00		};
int		hfp2int_ans[N]		= { 0,			0,			-419,		0,			0x80000000,		0x80000000	};

float 	float_in[N]			= {	1.0,		3.0/(float)(1<<26),		1.0/(float)(1<<25),		5.0/(float)(1<<28),		3583.0/8.0,		3.0*(float)(1<<16) };
hfp		float2hfp_ans[N]	= {	0x3c00,		0x0001,					0x0000,					0x0000,					0x5f00,			0x7c00			   };

hfp		hfp_fin[N]			= { 0x3c00,		0x0001,					0x7bff,		0x0400,			0xffff,		0x7c00 	};
float	hfp2float_ans[N]	= { 1.0,		1.0/(float)(1<<24),		65504.0,	1.0/16384.0,	-0.0/0.0,	1.0/0.0 };


int main(void)
{
	int i;
	hfp	h;
	int	n;
	
	union {
		unsigned int u;
		float f;
	} x;

	printf ("\nTest 1: Casting from int to hfp\n");
	for (i = 0; i < N; i++)
	{
		n = int_in[i];
		h = int2hfp(n);
		PRINT_INT(n, " => ");
		PRINT_HFP(h, ", ");
		CHECK_VALUE(h, int2hfp_ans[i]);
	}

	printf ("\nTest 2: Casting from hfp to int\n");
	for (i = 0; i < N; i++)
	{
		h = hfp_in[i];
		n = hfp2int(h);
		PRINT_HFP(h, " => ");
		PRINT_INT(n, ", ");
		CHECK_VALUE(n, hfp2int_ans[i]);
	}

	printf ("\nTest 3: Casting from float to hfp\n");
	for (i = 0; i < N; i++)
	{
		x.f = float_in[i];
		h = float2hfp(x.f);
		PRINT_FLOAT(x.u, " => ");
		PRINT_HFP(h, ", ");
		FLOAT_INF_NAN(x.u)? CHECK_INF_NAN(x.u, h) : CHECK_VALUE(h, float2hfp_ans[i]);
	}

	printf ("\nTest 4: Casting from hfp to float\n");
	for(i = 0; i < N; i++)
	{
		h = hfp_fin[i];
		x.f = hfp2float(h);
		PRINT_HFP(h, " => ");
		PRINT_FLOAT(x.u, ", ");
		HFP_INF_NAN(h)? CHECK_INF_NAN(x.u, h) : CHECK_VALUE(x.f, hfp2float_ans[i]);
	}

	return 0;
}
