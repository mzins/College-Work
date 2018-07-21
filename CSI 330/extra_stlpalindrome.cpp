//Madelaine Zinser
//Extra credit program
//Use STL vectors to determine if a string is a palindrome
//12/17/2015

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main (){
  vector<char> forward;
  vector<char> backward;
  string word;
  int length;
  char f,b;
  bool check=true;

  cout<<"Enter a string   ";
  getline(cin, word);
  length=word.length();

  for(int i=0; i<length; i++){
    if(word[i]>='A' &&word[i]<='Z'||word[i]>='a' && word[i]<='z'){
      forward.push_back(word[i]);
      backward.push_back(word[i]);
    }//end if
  }//end for
  reverse(backward.begin(), backward.end());

  for(int i=0; i<length; i++){
   //f=forward.pop_back();
   //b=backward.pop_back();
    if(forward[i]!=backward[i])
      check=false;   
  }//end for

  if(check)
    cout<<"Yes! "<<word<<" is a palindrome!\n";
  else 
    cout<<"No "<<word<<" is not a palindrome.\n";

  return 0;
}
