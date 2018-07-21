//Madelaine Zinser CSI 130 Lab 6//
#include <iostream>
using namespace std;
int main ()
{
  int num1, num2, i=0, carry = 0;
  char choice='x';
  int a[4], b[4], c[5]={0};
 
  while(choice !='q')
  {if(choice=='q')
		 cout<<"Bye!";
	 choice='x';
	 cout<<endl<<"Type '+' to ADD 2 binary numbers"<<endl<<"Type 'a' to AND 2 binary numbers"<<endl<<"Type 'o' to OR 2 binary numbers"<<endl<<"Type 'q' to quit"<<endl;
     cin>>choice;
	 if(choice=='q')
		 cout<<"Bye!";
     else 
		cout<<"Enter a 4-bit binary number  ";
		cin>>num1;
		cout<<endl<<"Enter a 4-bit binary number  ";
		cin>>num2;
	i=0;
	while (i<4) {
       a[i]=b[i]=0;
	   i++;
	}
	i=0;
	while(num1>0)								//Converts 1st number to binary//
   { 
	  a[i]=num1%10;
	  num1=num1/10;
	  i=i+1;
	  
   }
   i = 0;
   while(num2>0)								//Converts 2nd number to binary//
   {
     b[i]=num2%10;
	 num2=num2/10;
	 i=i+1;
   }
   if(choice=='a')								//This will AND the two binary numbers//
   {
     for(i=0; i<4; i=i+1)
	 {
		if(a[i]==1 && b[i]==1)
		  c[i]=1;
		else
		  c[i]=0;
	 }
     if((c[0]+c[1]+c[2]+c[3])>0)
		  cout<<"True"<<endl;
		else
		  cout<<"False"<<endl;
   }

   else if(choice=='o')								//This will OR the two binary numbers//
   {  for(i=0; i<4; i=i+1)					
	  {
		if(a[i]==0 && b[i]==0)
			c[i]=0;
		else
			c[i]=1;
      }
		if((c[0]+c[1]+c[2]+c[3])>0)
			cout<<"True"<<endl;
		else
			cout<<"False"<<endl;
   }
  else if(choice=='+')								//This will ADD the two binary numbers//
  { 
	 for(i=0; i<4; i=i+1)
	 {
		c[i]=a[i]+b[i]+carry;
		if(c[i]==0)
			carry=0;
		else if(c[i]==2)
	    {
			c[i]=0;
			carry=1;
		}
		else if (c[i]==3)
		{
			c[i]=1;
			carry=1;
		}
		else if (c[i]==1)
		{
			c[i]=1;
			carry=0;
		}
	}
	c[i]=carry;
	for(i=4; i>=0; i=i-1)
		cout<<c[i];

  }
   cout<<endl<<"Type '+' to ADD 2 binary numbers"<<endl<<"Type 'a' to AND 2 binary numbers"<<endl<<"Type 'o' to OR 2 binary numbers"<<endl<<"Type 'q' to quit"<<endl;
     cin>>choice;
	  if(choice=='q')
		 cout<<"Bye!";
     else
	 {
		cout<<"Enter a 4-bit binary number  ";
		cin>>num1;
		cout<<endl<<"Enter a 4-bit binary number  ";
		cin>>num2;
	  }
}
 
return 0;
}