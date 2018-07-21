//Madelaine Zinser CSI 130 Lab 3: Flowcharts and C++"//
#include <iostream>
using namespace std;
int main ()
{ float G1, G2, G3, G4, mean; 
cout<<"Enter Four Numeric Grades"<<endl;
cin>>G1>>G2>>G3>>G4;
cout<<endl;
mean= (G1+G2+G3+G4)/4.0;
if(mean<=59)
	cout<<"Failing"<<endl<<endl<<endl; 
else if(mean<=69)
	cout<<"Dwindling"<<endl<<endl<<endl;
else if(mean<=79)
	cout<<"Creative"<<endl<<endl<<endl;
else if(mean<=89)
	cout<<"Beautiful"<<endl<<endl<<endl;
else 
	cout<<"Amazing"<<endl<<endl<<endl;
return 0;
}
