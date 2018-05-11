#include <iostream>
#include <math.h>
#include <ctime>
using namespace std;
long long gcd(long long a,long long b)
{
return b==0?
a:gcd(b,a%b);
}

int main()
{

	long long n=115;
	long long y=2;
	long long x=2;
	
	long long d=1;	


	//for(int i=0;i<3;i++)
	//{
	//	x=(x*x+1)%n;
	//	y=(x*x+1)%n;

	//	d=gcd(n,x-y);

	//	cout<<"==========""turn "<<i<<endl;
	//	cout<<"x: "<<x<<endl;
	//	cout<<"y: "<<y<<endl;
	//	cout<<"D: "<<d<<endl;

	//}
	while(d==1)
{
	x=(x*x+1)%n;
	y=((y*y+1) * (y*y+1) + 1)%n;
	gcd(n,abs(x - y));
}
	cout<<"Divisor:"<<d<<endl;

	return 0;
}