//NAME: Madelaine Zinser
//DATE: 11/2/2015
//PURPOSE: Binary search tree

#include <iostream>
#include <string>
#include "/lib/330/tree.h"
#include <fstream>
using namespace std;

int main ()
{
  string filename, inputfilename, addString;
  ifstream inputfile;
  int addInt;
  Tree<int> ti;
  while(!inputfile.is_open())
  {
    cout<<"\nInput filename: ";
    getline(cin, inputfilename);
    inputfile.open(inputfilename.c_str(), ios::in | ios::binary);
  }
  while (inputfile>>addInt)
  {
    ti.insert(addInt);
  }
  cout<<"\nHere is pre-order:\n";
  ti.preOrder();
  cout<<"\nHere is post-order:\n";
  ti.postOrder();
  cout<<"\nHere is in-order:\n";
  ti.inOrder();

  inputfile.close();

  do{
    cout<<"\nInput filename: ";
    getline(cin, inputfilename);
    inputfile.open(inputfilename.c_str(), ios::in | ios::binary);
  }while(!inputfile.is_open());

  Tree<string> tii;
  while(inputfile >> addString)
  {
    tii.insert(addString);
  }
  cout<<"\nHere is pre-order:\n";
  tii.preOrder();
  cout<<"\nHere is post-order:\n";
  tii.postOrder();
  cout<<"\nHere is in-order:\n";
  tii.inOrder();

  return 0;
}
