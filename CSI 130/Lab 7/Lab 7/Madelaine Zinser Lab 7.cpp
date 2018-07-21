//Madelaine Zinser/ Lab 7/ CSI 130//
#include <iostream>
using namespace std;
int main () {
	int choice=0, num=0, opcode=0,operand=0;
	int i=0,j=0,R=0;
	int mem[256][8]={{0}};
	cout<<"Type"<<endl<< "1 to enter a binary number"<<endl<< "2 to enter a decimal number"<<endl<< "3 to print memory"<<endl<< "4 to quit"<<endl;
	cin>>choice;

	while(choice!=4)
	{
		if(choice==1)
		{
			cout<<"Enter a binary number.";
			cin>>num;
			for(i=7;i>=0;i=i-1)
			{
				mem[R][i]=num%10;
				num=num/10;
			}
			R=R+1;
		}
		else if(choice==2)
		{
			cout<<"Enter a number (0-7)";
			cin>>opcode;
			for(i=2;i>=0;i=i-1)
			{
				mem[R][i]=opcode%2;
				opcode=opcode/2;
			}
			cout<<"Enter a number (0-15)";
			cin>>operand;
			for(i=7;i>=3;i=i+1)
			{
				mem[R][i]=operand%2;
				operand=operand/2;
			}
			R=R+1;


		}
		else if(choice==3)
		{
			for(j=0;j<255;j=j+1)
			{
				cout<<endl<<j<<":";
				for(i=0;i<=7;i=i+1)
				{
					cout<<mem[j][i];
				}
			}
		}

		
	cout<<endl<<"Type"<<endl<< "1 to enter a binary number"<<endl<< "2 to enter a decimal number"<<endl<< "3 to print memory"<<endl<< "4 to quit"<<endl;
	cin>>choice;
	}

	return 0;}