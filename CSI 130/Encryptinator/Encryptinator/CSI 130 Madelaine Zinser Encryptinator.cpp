//Madelaine Zinser CSI 130 Encryptinator//
#include <iostream>
using namespace std;
int main () {
cout<< "Enter characters"<<endl;
char c;
cin>>c ;
while (c!='#')
	{if (c>=65 && c<=90)
		cout<< c-65+8;
	if (c>=97 && c<= 122)
		cout<< c-97+8;
	if (c=='.')
		cout<<"A";
	if (c==',')
		cout<<"B";
	if (c=='?')
		cout<<"C";
	if (c=='!')
		cout<<"D";
	cin>>c;
}
	return 0;
}