//Madelaine Zinser	 CSI 130 Lab 5//
#include <iostream>
#include <cmath>
using namespace std;
int main () {
cout<<"Enter a number between 0 and 255";
int i=0, num=0, numsave=0, base=2, ans=0, j;
int a[8];
cin>> num;
numsave=num;
while (num>0)
	{a[i]=num % base;
	num=num / base;
	i=i+1;}
for(j=i-1; j>=0; j=j-1)
{ans=ans+ pow(2,j) *a[j];}
cout<<"Your input:  "<<numsave<<endl;
cout<<"Binary number:   ";
for(j=i-1; j>=0; j=j-1)
{cout<<a[j];}
cout<<endl<<"Converted decimal:   "<<ans<<endl<<endl<<endl<<endl<<"I deserve an A+"<<endl<<endl;



	return 0;}
