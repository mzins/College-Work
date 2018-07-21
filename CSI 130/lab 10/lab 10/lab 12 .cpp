//Madelaine Zinser
//CSI 130
//lab 12
#include <iostream>;
#include <cmath>;
using namespace std;

//Function that puts characters in order
void alpha( )
{
	char ch1,ch2,ch3;
	cout<<endl<<"Enter 3 characters"<<endl;
	cin>>ch1>>ch2>>ch3;
	if(ch1 < ch2 && ch2 < ch3)
	{
		cout<<endl<<ch1<<ch2<<ch3;
	}
	else if(ch1 < ch3 && ch3 < ch2)
	{
		cout<<endl<<ch1<<ch3<<2;
	}
	else if(ch2 < ch1 && ch1 < ch3)
	{
		cout<<endl<<ch2<<ch1<<ch3;
	}
	else if(ch3< ch2 && ch2 < ch1)
	{
		cout<<endl<<ch3<<ch2<<ch1;
	}
	else if(ch2 < ch3 && ch3 < ch1)
	{
		cout<<endl<<ch2<<ch3<<ch1;
	}
	else 
		cout<<endl<<ch3<<ch2<<ch1;
	
}

//Function that performs binary converstions
void binary()
{
	int i=0,j, num=0, numsave=0, a[8]={0}, ans=0;
	cout<<endl<<"Enter a number between 0 and 255"<<endl;
	cin>>num;
	numsave=num;
	while (num>0)
	{
		a[i]=num%2;
		num=num/2;
		i++;
	}
	j=i-1;
	while(j>=0)
	{
		ans=ans+pow(2,j)*a[j];
		j--;
	}
	cout<<endl<<"Your input: "<<numsave;
	cout<<endl<<"Binary Number: ";
	j=i-1;
	while(j>=0)
	{
		cout<<a[j];
		j--;
	}
	cout<<endl<<"Converted Decimal: "<<ans<<endl;

}
//Function to sum numbers

void sum(int num)
{
	int sum=0;
	while(num>=0)
	{
		sum=num+sum;
		num--;
	}
	cout<<endl<<"The sum is "<<sum<<endl;
}

//Function to find volume

float volume(float l, float w, float h)
{
	float vol;
	vol=l*w*h;
	return vol;
}

//Main function

int main()
{
	int choice=0, num=0, l, w, h, vol;
	cout<<"\nPress\n 1)Put characters in order\n 2)Binary Conversions\n 3)Add all numbers up to input\n 4)Find Volume\n 5)Quit\n";
	cin>>choice;
	while(choice!=5)
	{
		if (choice==1)
		{
			alpha ();
		}
		else if(choice==2)
		{
			binary();
		}
		else if(choice==3)
		{
			cout<<endl<<"Enter a number"<<endl;
			cin>>num;
			sum(num);
		}
		else if(choice==4)
		{
			cout<<endl<<"Enter length"<<endl;
			cin>>l;
			cout<<endl<<"Enter width"<<endl;
			cin>>w;
			cout<<endl<<"Enter height"<<endl;
			cin>>h;
			vol=volume(l,w,h);
			cout<<"The volume is: "<<vol<<endl;

		}
	cout<<"\nPress\n 1)Put characters in order\n 2)Binary Conversions\n 3)Add all numbers up to input\n 4)Find Volume\n 5)Quit\n";
	cin>>choice;
	}
	return 0;
}