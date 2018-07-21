//Madelaine Zinser CSI 130 Guessing Game//
#include <iostream>
using namespace std;
int main ()
{ int num, guess;
num=0;
cout<<"Guess a number."<<endl;
cin>>guess;
while (num!=guess)
	{if (guess<num)
		cout<<"Guess higher"<<endl;
	else if(guess>num)
		cout<<"Guess lower"<<endl<<endl;
	cin>>guess;
	}
cout<<"Congrats! You guessed it!"<<endl<<endl;
return 0;
}