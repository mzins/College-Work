#include <iostream>
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
{
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
}

void Queue :: enqueue (int num)
{
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
}

bool Queue :: empty()
{
  bool retval=false;
  if(first==NULL)
    retval=true;
  return retval;
}












