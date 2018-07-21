//NAME: Madelaine Zinser
//DATE: 10/18/2015
//PURPOSE: Create a doublly linked list class that allows users to enter a
//specified file that has operations for the list

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
const bool DEBUG=true;

template <typename T> struct node
{
  T item;
  node<T> *next;
  node<T> *prev;
};
template <typename T> class DoubllyLinked
{
  private:
    node<T> *first;
    node<T> *last;
  public: 
    DoubllyLinked();          //Constructor
    ~DoubllyLinked();         //Destructor
    void addFront(T);         //1
    void addBack(T);          //2
    T removeFront();          //3
    T removeBack();           //4
    T getFront();             //5
    T getBack();              //6
    void addInOrder(T);       //7
    bool deleteItem(T);       //8
    bool getFull();           //9
    bool empty();             //10
    void displayForward();    //11
    void displayBackward();   //12
};
    
template <typename T> DoubllyLinked <T> ::DoubllyLinked()
{
  first=last=NULL;
}
template <typename T> DoubllyLinked <T> :: ~DoubllyLinked()
{
  while(!empty())
  {
    removeFront();
  }
  if (!empty())
    first=last=NULL;
}
template <typename T> void DoubllyLinked<T> :: addFront(T val)
{//INPUT: value to be added to the front of the list
 //OUTPUT: none
 //PURPOSE: add a value tot he front of the list
  if(empty())
  {
    first=new node<T>;
    first->item=val;
    first->next=NULL;
    first->prev=NULL;
    last=first;
  }
  else
  {
    node<T> *curnode=new node<T>;
    curnode->item=val;
    curnode->next=first;
    first->prev=curnode;
    first=curnode;
  }
}//end addFront

template <typename T> void DoubllyLinked<T> :: addBack(T val)
{//INPUT: value to be added to the back
 //OUTPUT: none
 //PURPOSE: add a value to the end of the list
  if(empty())
  {
    first=new node<T>;
    first->item=val;
    first->next=NULL;
    first->prev=NULL;
    last=first;
  }
  else
  {
    node<T> *curnode=new node<T>;
    curnode->item=val;
    curnode->next=NULL;
    curnode->prev=last;
    last->next=curnode;
    last=curnode;
  }
}//end addBack

template <typename T> T DoubllyLinked<T> :: removeFront()
{//INPUT: none
 //OUTPUT: value at the front of the list
 //PURPOSE: remove the value at the front of the list
  T retval;
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
    node<T>*curnode;
    curnode=first->next;
    curnode->prev=NULL;
    retval=first->item;
    delete first;
    first=curnode;
  }
  return retval;
}//end removeFront

template <typename T> T DoubllyLinked<T> ::  removeBack()
{//INPUT: none
 //OUTPUT: value in back of list
 //PURPOSE: remove and return value in the back of the list
  T retval;
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
    node<T>*curnode;
    curnode=last->prev;
    curnode->next=NULL;
    retval=last->item;
    delete last;
    last=curnode;
  }
  return retval;
}//end removeBack

template <typename T> T DoubllyLinked<T> :: getFront()
{//INPUT: none
 //OUTPUT: item at front of list
 //PURPOSE: return item at the front of the list without deleting
  return first->item;
}//end getFront

template <typename T> T DoubllyLinked<T> :: getBack()
{//INPUT: none
 //OUTPUT: item at back of list
 //PURPOSE: return item at the back of the list without deleting
  return last->item;
}//end getFront

template <typename T> void DoubllyLinked<T> :: addInOrder(T val)
{//INPUT: value to add to the list
 //OUTPUT: node
 //PURPOSE: add values to the linked list in order
  node<T> *curnode=new node<T>;
  node<T> *temp, *prev;
  curnode->item=val;
  if (first == NULL || first->item >val)
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

template <typename T> bool DoubllyLinked<T> :: deleteItem(T val)
{
  bool retval;
  node<T>*temp, *prev;
  if(empty())
  {
    return false;
  }
  else if(first->item==val)
  {
    T x=removeFront();
    retval=true;
  }
  else
  {
    for(prev=temp=first; temp->item!=val && temp!=NULL; temp=temp->next)
       prev=temp;
    if(temp==last)
    {
      T x=removeBack();
      retval=true;
    }
    else
    {
      prev=temp->next;
      temp->next->prev=temp->prev;
      delete temp;
      retval=true;
    }
  }
  return retval;
}

template <typename T> bool DoubllyLinked<T> :: getFull()
{
  return false;
}

template <typename T> bool DoubllyLinked<T> :: empty()
{//INPUT: none
 //OUTPUT: true/false indication of empty status
 //PURPOSE: determine if the list is empty
  bool retval=false;
  if(first==NULL && last==NULL)
    retval=true;
  return retval;
}//end empty

template <typename T> void DoubllyLinked<T> :: displayForward() 
{//INPUT: none
 //OUTPUT: node
 //PURPOSE: display the list forward
  node<T> *curnode;
  cout<<"\nList in order: \n";
  for (curnode=first; curnode!=NULL; curnode=curnode->next)
    cout<<curnode->item<<endl;
}//end displayForward

template <typename T> void DoubllyLinked<T> :: displayBackward()
{//INPUT: none
 //OUTPUT: node
 //PURPOSE: display the list reverse
  node<T> *curnode;
  cout<<"\nList in reverse: \n";
  for (curnode=last; curnode!=NULL; curnode=curnode->prev)
    cout<<curnode->item<<endl;
}//end displayBackward

int main()
{
  T i, j;

  cout << "Working with an int doublly linked list\n";
  DoubllyLinked  <int> di;

  di.addFront(3);
  di.addBack(7);
  di.addInOrder(10);
  di.addInOrder(1);
  di.addInOrder(5);
  di.displayForward(); 
  di.displayReverse();
  di.deleteItem(5);
  di.deleteItem(6);
  di.deleteItem(1);
  di.deleteItem(10);
  while (!di.empty()) {
    cout << di.removeFront() << " ";
  } 
  cout << endl << endl;
  
  cout << "Working with an string doublly linked list\n";
  DoubllyLinked <string> ds;

  ds.addFront("Jacob");
  ds.addBack("Sean");
  ds.addInOrder("Madelaine");
  ds.addInOrder("Stacey");
  ds.addInOrder("Greg");
  ds.addInOrder("Alexis");
  ds.addInOrder("Kaleb");
  ds.addInOrder("Aaron");
  ds.addInOrder("Josh");
  ds.displayForward(); 
  ds.displayReverse();
  while (!ds.empty()) {
    cout << ds.removeBack() << " ";
  } 
  cout << endl << endl;

  return 0;
} // end main
