//NAME: Madelaine Zinser
//DATE: 10/2/2015
//PURPOSE: Class stack and decimal to hexadecimal conversion

#include <iostream>
#include "/lib/330/getInt.cpp"
using namespace std;

typedef struct node *nodePtr;
//struct for nodes
struct node
{
  char item;
  nodePtr next;
};//end struct


class Stack
{
  private: 
    nodePtr first;
    int count;
  public: 
    // stack constructor
    Stack()
    {
      first=NULL;
      count=0;
    }
    void push(char val);
    char pop();
    bool empty() const { return first==NULL; }
    int getNumItems() const { return count;  }
};//end class Stack

void Stack :: push(char val)
{//INPUT: New value to be added to stack
 //OUTPUT:none
 //PURPOSE: Add a new node to the top of the stack
  nodePtr cur_node;
  cur_node=new node;
  cur_node->item=val;
  cur_node->next=first;
  first=cur_node;
  count++;
}//end push function

char Stack :: pop()
{//INPUT: none
 //OUTPUT: the character item at the top of the stack
 //PURPOSE: delete the top node and return item
  nodePtr dataout;
  char out=' ';

  if(first==NULL)
  {
    cerr<<"ERROR: cannot pop. Stack is empty";
    return -1;
  }
  else
  {
   dataout=first;
   out= dataout->item;
   first=dataout->next;
   delete dataout;
  }
  count--;
  return out;
}//end pop function

char num2char(int);
int main()
{
  int number;
  char digit;
  Stack x;
  cout<<"Enter a number.   ";
  number=getInt(0);

  while(number>0)
  {
    digit=number%16;
    x.push(num2char(digit));
    number/=16;
  }
  while(!x.empty())
  {
    cout<<x.pop()<<" ";
  }
  return 0;
}//end main

char num2char (int n)
{//INPUT:integer number to be converted to hex
 //OUTPUT: hex character value
 //PURPOSE: convert integers to hex digits as characters
  char ret_val=' ';
  if(n>=0 && n<=9)
  {
    ret_val=char('0'+n);
  }
  else
    ret_val=char('A'+(n-10));

  return ret_val;
}//end num2char function
