//Madelaine Zinser CSI 130 Lab 4 part 3//
#include <iostream>
using namespace std;
int main () {
cout<<"Enter a number"<<endl;
int sum, num;
sum=0;
num=0;
cin>>num;
while(num>=0)
	{
	sum=num+sum;
	num=num-1;
	}
cout<<sum<<endl;

	return 0;
}