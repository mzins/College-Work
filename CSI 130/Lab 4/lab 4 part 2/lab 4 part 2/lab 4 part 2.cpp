//Madelaine Zinser CSI 130 Lab 4 part 2//
#include <iostream>
using namespace std;
int main() {
int a,b,c,d,e;
float ans;
cout<<"Enter 5 numbers:"<<endl;
cin>>a>>b>>c>>d>>e;
cout<<endl;
ans= (a+b+c+d+e)/5.0;
if((0<ans && ans<19)||  (80<ans && ans<100))
	cout<<"WOW!!"<<endl;
else if(60<ans && ans<70)
	cout<<"Middle"<<endl;
else if(70<ans && ans<80)
	cout<<"High"<<endl;
else if(20<ans && ans<59)
	cout<<"Low"<<endl;
	return 0;
}