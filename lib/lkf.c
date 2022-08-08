/*
 * VUI - Voice User Interface for TFP  
 * 
 * Author: Anton Prozorov <prozanton@gmail.com>
 * 
 * Copyright 2013-2014 KRUST, Ltd.
 */

#include "lkf.h"

const uint32_t xkey[4] = {0x8AC14C27,0x42845AC1,0x136506BB,0x05D47C66}; //xtea magic key for books


const unsigned long DELTA = 0x9e3779b9; //fucking "delta"
#define MX  ( (((z>>5)^(y<<2))+((y>>3)^(z<<4)))^((sum^y)+(xkey[(p&3)^e]^z)) )

long _btea(uint32_t * v, long n)
{
    unsigned long z /* = v[n-1] */, y=v[0], sum=0, e;
    long p, q ;
    if (n > 1) {          /* Coding Part */
      z=v[n-1];           /* Moved z=v[n-1] to here, else segmentation fault in decode when n < 0 */
      q = 3+52/n ;
      while (q-- > 0) {
        sum += DELTA;
        e = sum >> 2&3 ;
        for (p=0; p<n-1; p++) y = v[p+1], z = v[p] += MX;
        y = v[0];
        z = v[n-1] += MX;
      }
      return 0 ;
    } else if (n < -1) {  /* Decoding Part */
      n = -n ;

      q = 3+52/n ;
      sum = q*DELTA ;
      while (sum != 0) {
        e = sum>>2 & 3;
        for (p=n-1; p>0; p--) z = v[p-1], y = v[p] -= MX;
        z = v[n-1];
        y = v[0] -= MX;
        sum -= DELTA;
      }
      return 0;
    }
    return 1;
}

void decode_lkf_block(uint32_t *v, int num_blocks)
{
  int i;
  for (i = 0; i < num_blocks; i++) {
    _btea(v, -(signed long)(((long)LKF_BLOCK_SIZE)/sizeof(uint32_t)));
    v += LKF_BLOCK_SIZE / 4;
  }
}

