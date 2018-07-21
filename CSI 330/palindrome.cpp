//NAME: Madelaine Zinser
//DATE: 10/16/2015
//PURPOSE: Check to see if a string of words is a palindrome
#include "/lib/330/stack.h"
#include <iostream>
#include <string>
using namespace std;

int main ()
{
  const bool DEBUG=false;
  string word, forward=""; 
  int length, check=0;
  Stack <char>   w(100);

  cout<<"Enter a string   ";
  getline(cin,word);
  length=word.length();

  DEBUG &&  cout<<"\tword is: "<<word<<endl<<"\tLength is: "<<length<<endl;

  for(int i=0; i<length; i++)
  {
    if(word[i]>='A' && word [i]<='Z' || word[i]>='a' && word[i]<='z')
    {
      w.push(word[i]);
      forward.push_back(word[i]);

    }
  }

  length=forward.length();
  DEBUG && cout<<"\nforward is: "<<forward<<"\n\tlength is: "<<length<<endl;
  cout<<"Reverse: ";
  
  for(int i=0; i<length; i++)
  {
    char x=w.pop();
    cout<<x;
    if(forward[i]==x)
    {
      check++;
    }
  } 
  
  cout<<endl<<"Forward: "<<forward<<endl;

  if(check/length==1)
  {
    cout<<"They are a match!!"<<endl;
  }
  else
    cout<<"Sorry, this is not a Palindrome"<<endl;
 
  return 0;
}
