//Madelaine Zinser
//CSI 130
//LAB 11
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
	SymTab st[25];
	int adder=255, choice, i=0, j=0;
	string tempst; 

	//Print Menu
	cout<<"Press \n 1) Input a value to the array. \n 2) Check if a specific identifier string is in the array. \n 3) Quit \n";
	cin>>choice;
	
	while(choice!=3)
	{
		if(choice==1)
		{
			cin>>st[i].identifier;
			st[i].address=adder;
			i++;
			adder--;
		}
		if(choice==2)
		{
			cin>>tempst;
			for(j=0; j<i; j++)
			{
				if(tempst==st[j].identifier)
				{
					cout<<st[j].identifier<<endl<<st[j].address<<endl<<j<<endl;
				}
			}
		}

	cout<<"Press \n 1) Input a value to the array. \n 2) Check if a specific identifier string is in the array. \n 3) Quit \n";
	cin>>choice;
	}



	return 0;
}