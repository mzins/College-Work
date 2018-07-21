//NAME: Madelaine Zinser
//DATE: 10/18/2015
//PURPOSE: Create a doublly linked list class that allows users to enter a
//specified file that has operations for the list

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;
const bool DEBUG=true;

typedef struct node *nodePtr;
struct node
{
  int item;
  nodePtr next;
  nodePtr prev;
};

class DoubllyLinked
{
  private: 
    nodePtr first;
    nodePtr last;
    int count;
  public: 
    DoubllyLinked()
    {
      first=last=NULL;
      count=0;
    }
    ~DoubllyLinked()
    {
      while(!empty())
      {
        removeFront();
      }
      if (!empty())
        first=last=NULL;
    }

    void addFront(int);         //1
    void addBack(int);          //2
    int removeFront();          //3
    int removeBack();           //4
    int getFront();             //5
    int getBack();              //6
    void addInOrder(int);       //7
    bool deleteItem(int);       //8
    bool getFull();             //9
    bool empty();               //10
    void displayForward();      //11
    void displayBackward();     //12
};


void DoubllyLinked :: addFront(int val)
{//INPUT: value to be added to the front of the list
 //OUTPUT: none
 //PURPOSE: add a value tot he front of the list
  if(empty())
  {
    first=new node;
    first->item=val;
    first->next=NULL;
    first->prev=NULL;
    last=first;
  }
  else
  {
    nodePtr curnode=new node;
    curnode->item=val;
    curnode->prev=NULL;
    curnode->next=first;
    first->prev=curnode;
    first=curnode;
  }
}//end addFront

void DoubllyLinked :: addBack(int val)
{//INPUT: value to be added to the back
 //OUTPUT: none
 //PURPOSE: add a value to the end of the list
  if(empty())
  {
    first=new node;
    first->item=val;
    first->next=NULL;
    first->prev=NULL;
    last=first;
  }
  else
  {
    nodePtr curnode=new node;
    curnode->item=val;
    curnode->next=NULL;
    curnode->prev=last;
    last->next=curnode;
    last=curnode;
  }
}//end addBack

int DoubllyLinked :: removeFront()
{//INPUT: none
 //OUTPUT: value at the front of the list
 //PURPOSE: remove the value at the front of the list
  int retval;
  if(empty())
  {
    cout<<"\nError! cannot remove front, list is empty\n";
    return -1;
  }
  else if (first==last)
  {
    retval=first->item;
    delete first;
    first=last=NULL;
  }
  else
  {
    nodePtr curnode;
    curnode=first->next;
    curnode->prev=NULL;
    retval=first->item;
    delete first;
    first=curnode;
  }
  return retval;
}//end removeFront

int DoubllyLinked ::  removeBack()
{//INPUT: none
 //OUTPUT: value in back of list
 //PURPOSE: remove and return value in the back of the list
  int retval;
  if(empty())
  {
    cout<<"Error! Cannot removeBack, list is empty \n";
    return -1;
  }
  else if(first==last)
  {
    retval=first->item;
    delete first;
    last=first=NULL;
  }
  else
  {
    nodePtr curnode;
    curnode=last->prev;
    curnode->next=NULL;
    retval=last->item;
    delete last;
    last=curnode;
  }
  return retval;
}//end removeBack

int DoubllyLinked :: getFront()
{//INPUT: none
 //OUTPUT: item at front of list
 //PURPOSE: return item at the front of the list without deleting
  return first->item;
}//end getFront

int DoubllyLinked :: getBack()
{//INPUT: none
 //OUTPUT: item at back of list
 //PURPOSE: return item at the back of the list without deleting
  return last->item;
}//end getFront

void DoubllyLinked :: addInOrder(int val)
{//INPUT: value to add to the list
 //OUTPUT: node
 //PURPOSE: add values to the linked list in order
  nodePtr curnode=new node;
  nodePtr temp, prev;
  curnode->item=val;
  if (first == NULL || first->item >=val)
  {
    if(first!=NULL)
    {
      first->prev=curnode;
    }
    curnode->next=first;
    first->prev=curnode;
    curnode->prev=NULL;
    first=curnode;
    if(last==NULL)
    {
      last=curnode;
    }
  }
  else 
  {
    for(prev=temp=first; temp!=NULL && temp->item<val; temp=temp->next)
    {
      prev=temp;
    }
    curnode->next=temp;
    if(temp==NULL)
    {
      curnode->prev=prev;
      prev->next=curnode;
      last=curnode;
    }
    else
    {
      temp->prev=curnode;
      curnode->prev=prev;
      prev->next=curnode;
    }
  }
}//end addinorder 
        
bool DoubllyLinked :: deleteItem(int val)
{
  bool retval=false;
  nodePtr tmp, next;
  if(empty())
  {    
    return retval;
  }
  else
  {
    for(tmp=next=first; tmp->item != val && tmp->next != NULL; tmp = tmp->next);
    if (tmp ->item == val)
    {
      if (tmp -> prev == NULL)
      {
        first = first -> next;
        delete tmp;
        first -> prev = NULL;
          if (first == NULL)
            last = NULL;
          
        retval = true;
      }
    
      else if (tmp -> next == NULL)
      {
        last = last -> prev;
        last -> next = NULL;
        delete tmp;
        retval = true;
      }
      else
      { 
        tmp -> next -> prev = tmp -> prev;
        tmp -> prev -> next = tmp -> next;
        delete tmp;
        retval = true;
      }
    }
  }
  
  return retval;
}

bool DoubllyLinked :: getFull()
{
  return false;
}
bool DoubllyLinked :: empty()
{//INPUT: none
 //OUTPUT: true/false indication of empty status
 //PURPOSE: determine if the list is empty
  bool retval=false;
  if(first==NULL && last==NULL)
    retval=true;
  return retval;
}//end empty

void DoubllyLinked :: displayForward() 
{//INPUT: none
 //OUTPUT: node
 //PURPOSE: display the list forward
  nodePtr curnode;
  cout<<"\nList in order: \n";
  for (curnode=first; curnode!=NULL; curnode=curnode->next)
    cout<<curnode->item<<" ";
  cout<<endl;
}//end displayForward

void DoubllyLinked :: displayBackward()
{//INPUT: none
 //OUTPUT: node
 //PURPOSE: display the list reverse
  nodePtr curnode;
  cout<<"\nList in reverse: \n";
  for (curnode=last; curnode!=NULL; curnode=curnode->prev)
    cout<<curnode->item<<" ";
  cout<<endl;
}//end displayBackward

int main()
{
  string filename, inputfilename;
  ifstream inputfile;
  while(!inputfile.is_open())
  {
    cout<<"Input filename: ";
    getline(cin, inputfilename);
    inputfile.open(inputfilename.c_str(), ios::in | ios::binary);
  }
  DoubllyLinked list;
  int temp, command, data;
  bool display,check;
  
  while(inputfile>>command)
  {
    display=false;
    if(command==13)
    {
      display=true;
      inputfile>>command;
    }

    //cout << "Command: " << command << endl;
    switch(command)
    {
      case 1:
        inputfile>>data;
        list.addFront(data);
        break;
      case 2:
        inputfile>>data;
        list.addBack(data);
        break;
      case 3:
        temp=list.removeFront();
        display && cout<<"Removed "<<temp<<" from Front\n";
        break;
      case 4:
        temp=list.removeBack(); 
        display && cout<<"Removed "<<temp<<" from Back\n";
        break;
      case 5:
        temp=list.getFront();
        display && cout<<"Front item is "<<temp<<endl;
        break;
      case 6:
        temp=list.getBack();
        display && cout<<"Back item is "<<temp<<endl;
        break;
      case 7:
        inputfile>>data;
        list.addInOrder(data);
        break;
      case 8:
        inputfile>>data;
        check=list.deleteItem(data);
        display && cout<<"Delete item "<<check<<endl;
        break;
      case 9:
        check=list.getFull();
        display && cout<<"Get full "<<check<<endl;
        break;
      case 10:
        check=list.empty();
        display && cout<<"Get empty "<<check<<endl;
        break;
      case 11:
        list.displayForward();
        break;
      case 12:
        list.displayBackward();
        break;
    }
   
  }

 /* x.addFront(2);
  x.displayForward();
  x.addBack(3);
  x.displayForward();
  y=x.removeFront();
  x.displayForward();
  y=x.removeBack();
  x.displayForward();
  x.addFront(1);
  x.addBack(3);
  x.displayForward();
  x.addInOrder(2);
  x.displayForward();
  z=x.deleteItem(2);
  x.displayForward();
  z=x.deleteItem(1);
  x.displayForward();*/



  return 0;
}






