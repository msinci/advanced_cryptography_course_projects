#include <iostream>
#include <cstdlib>
typedef  unsigned long long int ULL;
ULL gcd(ULL a, ULL b)
{
   for(; b >0 ;)
   {
       ULL rem = a % b;
       a = b;
       b = rem;
   }
   return a;
}
void pollard_rho(ULL n)
{
   ULL i = 0,y,k,d;
   ULL *x = new ULL[2*n];
   x[0] = rand() % n;
   y = x[0];
   k = 2;
	while(d == 1)
	{
		x = (x*x - 1) % n;
		y = (y*y - 1) % n;
		y = (y*y - 1) % n;
		d = abs(gcd(y-x,n))%n;
	}
	if(d!=n)
	  std::cout <<d<<std::endl;
	else
	  std::cout<<"Can't find result with this function \n";
       }
   }
}

int main()
{
   srand(time(NULL));
   pollard_rho(10);

}