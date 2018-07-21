//NAME: Madelaine Zinser
//DATE: 11/9/2015
//PURPOSE: Allow user to convert a string to 1s and 0s or enter a string of 
//1s and 0s to get a string of characters 
#include <iostream>
#include <fstream>
#include <string>
#include "/lib/330/tree.h"
#include <cstdlib>
using namespace std;
const bool DEBUG=false, debug=false;
class Huffman:  public Tree <char>
{
  private:
    string huff(char c, treeNode<char> *tp, string input="")
    {//INPUT: Character to be searched, pointer to starting node, string for
     //       input string
     //OUTPUT: A string of 1s or 0s
     //PURPOSE: Use recursion to find binary code representation 
      string retval="";
      DEBUG && cout<<"Make it to huff recursion\n";
      if(tp==NULL)//nothing in tree
      {
        retval="";
        cerr<<"ERROR: Tree is empty!";
        exit(-5);
        DEBUG && cout<<"In huff recursion says root==NULL\n";
      }
      else if(tp->left==NULL && tp->right==NULL)//at a leaf
      {
        DEBUG && cout<<"says tp is at a leaf\n";
        if(tp->item==c)//found
        {
          retval=input;
          DEBUG && cout<<"Made it to retval=input because item=c\n";
        }
      }//end else if
      else
      {
        DEBUG && cout<<"Made it to else in loof before NULL checks \n";
        if(tp->left!=NULL)//go left
          retval=huff(c, tp->left, input+"0");
        if(tp->right!=NULL && retval=="")//go right
          retval=huff(c, tp->right, input+"1");
      }//end else
      return retval;
    }//end huff
  public:
    string gethuff(string s)
    {//INPUT: String of characters
     //OUTPUT: String of 1s and 0s
     //PURPOSE: Convert characters to code of 1s and 0s 
      string retstring="", newstring="";
      DEBUG && cout<<"Make it here gethuff 1\n";
      if(root==NULL)//nothing in tree
      {
        cerr<<"ERROR: No tree (gethuff)\n";
        exit(-1);
      }
      for(int i=0; i<s.length(); i++)
      {DEBUG && cout<<"Make it here inside for loop gethuff 2\n i="<<i<<endl;
        if(s[i]>='A' && s[i]<='Z' || s[i]>='a' && s[i]<='z')//get rid of __
        {
          DEBUG && cout<<"Make it inside if statement gethuff 3 before call\n";
          newstring+=toupper(s[i]);//make all upper case
          DEBUG && cout<<"make it after string toupper gethuff\n";
          retstring+=huff(newstring[i],root);//call recursive function
          DEBUG && cout<<"Make it after call to private recursion gethuff\n";
        }
      }//end for loop
      return retstring;
    }//end gethuff
    string getword(string b)
    {//INPUT: String of 1s and 0s
     //OUTPUT: String of characters
     //PURPOSE: Convert coded 1s and 0s to character string
      string retstring="";
      treeNode<char> *node;
      node=root;
      
      debug && cout<<"made it to getword\n";
      if(root==NULL)//nothing in tree
      {
        cerr<<"ERROR: No tree (getword)\n";
        exit(-2);
      }//end if
      else
      {
        debug && cout<<"Made it to else in getword\n";
        for(int i=0; i<b.length(); i++)
        {
          if(b[i]=='0')//go left
          {
            debug && cout<<"Went left\n";
            node=node->left;
          }
          else         //go right
          {
            debug && cout<<"Went right\n";
            node=node->right;
          }
          if(node->left==NULL && node->right==NULL)
          {
            debug && cout <<"found item\n";
            retstring+=node->item;
            node=root;
          }
        }
        if(node!=root && node->item=='*')//cannot find message
        {
          cerr<<"ERROR: cannot generate message\n";
          exit(-3);
        }
      }//end else
      return retstring;
    }//end getword   
};//end class

int main()
{
  Tree<char> t;
  Huffman h;
  bool check;
  ifstream IN;
  int choice;
  string filename, inputfilename,input;
  ifstream inputfile;
  while(!inputfile.is_open())
  {
    cout<<"Input filename: ";
    getline(cin, inputfilename);
    inputfile.open(inputfilename.c_str(), ios::in | ios::binary);
  }
  check=h.insertFromFile(inputfile);
 // t.postOrder();
  cout<<"Do you want to\n1. Convert string to binary?\n2. Binary to string?\n";
  cin>>choice;
  switch(choice)
  {
    case 1:
      cout<<"Enter string of characters\n";
      cin.ignore(3000,'\n');
      getline(cin,input);
      cout<<h.gethuff(input)<<endl;
      break;
    case 2:
      cout<<"Enter a string of binary\n";
      cin.ignore(3000, '\n');
      getline(cin, input);
      cout<<h.getword(input)<<endl;
      break;
    default:
      break;
  };
  return 0;
}
