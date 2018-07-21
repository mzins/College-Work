#include <iostream>
#include <string>
using namespace std;
struct SymTab
	{
		string identifier;
		int address;
	};
int main()
{
	int ch=0,Adder=255,i=0,j=0;
	string tempst;
	SymTab st[25];
	 

	while(ch!=3)
	{
		cout<<"1)Input a value to the array"<<endl<<"2)Check if a specific identifier string is in the array"<<endl<<"3)Quit"<<endl;
		cin>>ch;

		
		if(ch==1)
		{
			cout<<"Input string"<<endl;
			cin>>st[i].identifier;
			st[i].address=Adder;
			i=i+1;
			Adder=Adder-1;
		}


		if(ch==2)
		{
			cout<<"Input string"<<endl;
			cin>>tempst;

			for(j=0;j<i;j=j+1)
				if(tempst==st[j].identifier)
					cout<<st[j].identifier<<endl<<st[j].address<<endl<<j<<endl;
				
		}


		if(ch==3)
			cout<<"Bye!"<<endl;
	}

return 0;
}