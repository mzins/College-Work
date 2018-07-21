//NAME: Madelaine Zinser
//DATE: 10/15/2015
//PURPOSE: Solve book problem by writing a queue class and include a stack 
//class
#include <iostream>
#include "/lib/330/stack.h"

using namespace std;

typedef struct node *nodePtr;
struct node
{
  int item;
  nodePtr next;
};


class Queue
{
  private: 
    nodePtr first, tail;
    int count;
  public: 
    Queue()
    {
      first=tail=NULL;
      count=0;
    }
    ~Queue()
    {
      while(!empty())
      {
        dequeue();
      }
    }
    int dequeue();
    void enqueue(int);
    bool empty();
};

int Queue :: dequeue()
{//INPUT:none
 //OUTPUT:value that was saved in front of the list
 //PURPOSE:get the value on top of the queue
  int retval;
  if(empty())
  {
    cerr<<"ERROR! Cannot dequeue, queue is empty!";
    return -1;
  }
  else
  {
    retval=first->item;
    nodePtr curnode;
    curnode=first;
    first=curnode->next;
    delete curnode;
    count--;
    if(first==NULL)
      tail=NULL;
  }
  return retval;
}//end dequeue

void Queue :: enqueue (int num)
{//INPUT:value to add to the end of the queue
 //OUTPUT: none
 //PURPOSE: add to the end of the queue
  nodePtr curnode;
  curnode=new node;
  curnode->item=num;
  curnode->next=NULL;
  if (first==NULL)
  {
    first=curnode;
    tail=curnode;
  }
  else 
  {
    tail->next=curnode;
    tail=curnode;
  }
}//end enqueue

bool Queue :: empty()
{//INPUT:none
 //OUTPUT:true or false
 //PURPOSE:determine if the queue is empty
  bool retval=false;
  if(first==NULL)
    retval=true;
  return retval;
}//end empty

int main()
{
  int x=0,z=0,y=0;
  bool DEBUG = false;
  Stack <int> S(100);
  Queue Q1;
  Queue Q2;

  Q1.enqueue(5);
          DEBUG && cout<<"Push 5 to Q1\n";
  Q1.enqueue(6);
          DEBUG && cout<<"Push 6 to Q1\n";
  Q1.enqueue(9);
          DEBUG && cout<<"Push 9 to Q1\n";
  Q1.enqueue(0);
          DEBUG && cout<<"Push 0 to Q1\n";
  Q1.enqueue(7);
          DEBUG && cout<<"Push 7 to Q1\n";
  Q1.enqueue(5);
          DEBUG && cout<<"Push 5 to Q1\n";
  Q1.enqueue(0);
          DEBUG && cout<<"Push 0 to Q1\n";
  Q1.enqueue(2);     
          DEBUG && cout<<"Push 2 to Q1\n";
  Q1.enqueue(6);
          DEBUG && cout<<"Push 6 to Q1\n";

  while(!Q1.empty())
  {
    x=Q1.dequeue();
         DEBUG && cout<<"\nDequeue Q1 x= "<<x<<endl;
    if(x==0)
    {
      z=0;
      while(!S.empty())
      {
        y=S.pop();
                 DEBUG && cout<<"Pop S  "<<y<<endl;
        z=z+y;
      }
                DEBUG && cout<<"Enqueue Q2 "<< z<<endl;
     Q2.enqueue(z);
    }
    else{ 
      DEBUG && cout<<"Push S  "<<x<<endl;
      S.push(x);
    }
  }
  cout<<"Here is Q1:\n";
  while(!Q1.empty())
  {
    cout<<Q1.dequeue()<<endl;
  }

  cout<<"Here is Q2:\n";
  while(!Q2.empty())
  {
    cout<<Q2.dequeue()<<endl;
  }

  cout<<"Here is the stack:\n";
  while(!S.empty())
  {
    cout<<S.pop()<<endl;
  }





  return 0;
}
