#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <gmp.h>

 const uint64_t n = 1933545007396, N = n + 1;  /* N = 1019 -- prime     */
 const uint64_t alpha = 3;            /* generator             */
 const uint64_t beta = 1046577355951; /* 2^{10} = 1024 = 5 (N) */
 
 void new_xab( uint64_t& x, uint64_t& a, uint64_t& b ) {
   switch( x%3 ) {
   case 0: x = x*x     % N;  a =  a*2  % n;  b =  b*2  % n;  break;
   case 1: x = x*alpha % N;  a = (a+1) % n;                  break;
   case 2: x = x*beta  % N;                  b = (b+1) % n;  break;
   }
 }
 
 int main(void) {
   uint64_t x=1, a=0, b=0;
   uint64_t X=x, A=a, B=b;
   for(int i = 1; i < n; ++i ) {
     new_xab( x, a, b );
     new_xab( X, A, B ); new_xab( X, A, B );
     printf( "%3d  %4d %3d %3d  %4d %3d %3d\n", i, x, a, b, X, A, B );
     if( x == X ) break;
   }
   return 0;
 }
