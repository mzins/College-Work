//Madelaine Zinser
//CSI 130
//LAB 8
//CPU simulator 
#include <iostream>
#include <string>
using namespace std;
int main ()
{
	string assem=" ";
	int i,j,idADD, power, memory,carry, operand, opcode=0, PC=0, ACC[5]={0}, MDR[8]={0}, IR[8]={0}, mem[256][8]={{0}}, MAR[8]={0}, sopcode,soperand;
	//Menu
	cout<<"HALT\nLDIM \nSTORE \nLDID \nSTID \nADD \nCMIDE \nJMPNE \n";
	cin>>assem;
	if(assem=="HALT")
		opcode=0;
	else if(assem=="LDIM")
		opcode=1;
	else if(assem=="STORE")
		opcode=2;
	else if(assem=="LDID")
		opcode=3;
	else if(assem=="STID")
		opcode=4;
	else if(assem=="ADD")
		opcode=5;
	else if(assem=="CMPE")
		opcode=6;
	else if(assem=="JMPNE")
		opcode=7;

	//Enter opcodes and operands
	while (opcode!=0)
	{
		sopcode=opcode;
		for(i=2; i>=0; --i)
		{
			mem[PC][i]=sopcode%2;
			sopcode=sopcode/2;
		}

		cout<<"Enter a number between 0 and 31"<<endl;
		cin>>operand;
		soperand=operand;
		for(i=7; i>=3; --i)
		{
			mem[PC][i]=soperand%2;
			soperand=soperand/2;
		}
		if (opcode==3 || opcode==4)
		{ 
			cout<<"Enter a number between 0 to 255"<<endl;
			cin>>idADD;
			i=7;
			while(i>=0)
			{
				mem[operand][i]=idADD%2;
				idADD=idADD/2;
				--i;
			}

		}
		
		cout<<"\nHALT\nLDIM \nSTORE \nLDID \nSTID \nADD \nCMIDE \nJMPNE \n";
		cin>>assem;
		PC++;
		if(assem=="HALT")
		opcode=0;
		else if(assem=="LDIM")
			opcode=1;
		else if(assem=="STORE")
			opcode=2;
		else if(assem=="LDID")
			opcode=3;
		else if(assem=="STID")
			opcode=4;
		else if(assem=="ADD")
			opcode=5;
		else if(assem=="CMPE")
			opcode=6;
		else if(assem=="JMPNE")
			opcode=7;
	}
		
		cout<<"\nPress any Key to Print Memory"<<endl;
		cin>>memory;
		for(PC=0; PC<256; ++PC)
		{
			cout<<endl<<PC<<":";
			for(i=0; i<8; ++i)
			{
				cout<<mem[PC][i];
			}
		}
		


//PERFORM OPERATION
		
		cout<<"\nPress any Key to perform operation"<<endl;
		cin>>memory;
		PC=0;

		while(mem[PC][0]+mem[PC][1]+mem[PC][2] !=0)//not HALT instruction
		{  
			for(i=0; i<8; ++i) //read the nest instruction into the MDR
				MDR[i]=mem[PC][i];
			for(i=0; i<8; ++i)//move the instruction from the MDR to the IR
				IR[i]=MDR[i];
			//convert the opcode to decimal for the if statements
			i=2;
			power=1,
			opcode=0;
			while(i>=0)
			{
				opcode=opcode+IR[i]*power;
				power=power*2;
				i=i-1;
			}
		

			

			if(opcode==0)//****0-Halt****
				cout<<"\n PRESS ANY KEY TO CONTINUE";
			
			else if(opcode==1)
			{
				for(i=0; i<5; ++i)
					ACC[i]=IR[i+3];
			}
			else if(opcode==2)
			{  //get address to store the contents of the ACC
				i=7;
				power=1;
				idADD=0;
				while(i>=3)
				{
					idADD=idADD+IR[i]*power;
					power=power*2;
					i=i-1;
				}
				//move the contents of ACC to MDR
				for(i=0; i<5; ++i)
					MDR[i+3]=ACC[i];
				//store the contents of MDR in the address of idADD
				for(i=0; i<5; ++i)
					mem[idADD][i]=MDR[i];
			}
			else if(opcode==3)
			{  //get the address of the address of the operand
				i=7;
				power=1;
				idADD=0;
				while(i>=3)
				{
					idADD=idADD+IR[i]*power;
					power=power*2;
					i=i-1;
				}
				// get the address of the operand
				for(i=0; i<8; ++i)
					MAR[i]=mem[idADD][i];
				i=7;
				power=1;
				idADD=0;
				while(i>=0)
				{
					idADD=idADD+MAR[i]*power;
					power=power*2;
					--i;
				}
				//put the operand in the MDR
				for(i=0; i<8; ++i)
					MDR[i]=mem[idADD][i];
				//put the last 5 bits of the MDR into the ACC
				for(i=0; i<5; ++i)
					ACC[i]=MDR[i+3];
			}
			else if(opcode==4)
			{  //get the address of the address to store the contents of ACC
				i=7;
				power=1;
				idADD=0;
				while(i>=3)
				{
					idADD=idADD+IR[i]*power;
					power=power*2;
					--i;
				}
				//get the address to store the value
				for(i=0; i<8; ++i)
					MAR[i]= mem[idADD][i];
				//convert address to decimal
				i=7;
				power=1;
				idADD=0;
				while(i>=0)
				{
					idADD=idADD+MAR[i]*power;
					power=power*2;
					--i;
				}
				//put the ACC into the last 5 bits of the MDR
				for(i=0; i<5; ++i)
					MDR[i+3]=ACC[i];
				//put the contents of the MDR into memory
				for(i=0; i<8; ++i)
					mem[idADD][i]=MDR[i];
			}
			else if(opcode==5)
			{
				carry=0;
				for(i=4; i>0; --i)
				{
					ACC[i]=IR[i+3]+ACC[i]+carry;
					if(ACC[i]==0||ACC[i]==1)
						carry=0;
					if(ACC[i]==2)
					{
						ACC[i]=0;
						carry=1;
					}
					if(ACC[i]==3)
					{
						ACC[i]=1;
						carry=1;
					}

				}
				ACC[i]=carry+ACC[i];
			}
			else if(opcode==6)
			{
				j=0;
				for(i=0; i<=4; ++i)
				{
					ACC[i]=MDR[i+3];
					++j;
				}
				for(i=0;i<=4; ++i)
					ACC[i]=0;
				if(j==5)
					ACC[4]=1;

			}
			else if(opcode==7)
			{
				j=0;
				i=0;
				while(i<=4)
				{
					if(ACC[i]==0)
					{
						j++;
						i++;
					}
				}
				if(j==5)
				{
					i=3;
					while(i<=7)
					{
						ACC[i]=MDR[i];
						i++;
					}

				}
			}
			
			cout<<"\nPress any Key to Print Registers"<<endl;
			cin>>memory;

			//print out registers
			cout<<endl<<"ACC: ";
			for(i=0; i<5; ++i)
			{
				cout<<ACC[i];
			}
			cout<<endl<<" IR: ";
			for(i=0; i<8; ++i)
			{
				cout<<IR[i];
			}
			cout<<endl<<" PC: "<<PC;
			cout<<endl<<"MDR: ";
			for(i=0; i<8; ++i)
			{
				cout<<MDR[i];
			}
			cout<<endl<<"MAR: ";
			for(i=0; i<8; ++i)
			{
				cout<<MAR[i];
			}
			PC++;
		}

		cout<<"\nPress any Key to Print Memory"<<endl;
		cin>>memory;
			for(PC=0; PC<256; ++PC)
			{
				cout<<endl<<PC<<":";
				for(i=0; i<8; ++i)
				{
					cout<<mem[PC][i];
				}
			}

		cout<<endl<<endl<<endl;


	
	return 0;
}

