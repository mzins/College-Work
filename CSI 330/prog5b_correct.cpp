//NAME: Madelaine Zinser
//DATE: 11/1/2015
//PURPOSE: Create a doublly linked list template class with overloaded operaters

#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

template <class T> class node
{
  public:
    node<T> *next, *prev;
    T item;
    node()
    {
      next=prev=NULL;
    }
};

template <class T> class DoubllyLinked
{
  protected:
    node<T> *first, *last;
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
    DoubllyLinked(const DoubllyLinked &orig);
    void operator=(const DoubllyLinked &orig);
    T &operator[](int) const;
};
template <class T> DoubllyLinked <T> :: DoubllyLinked()
{
  first=last=NULL;
}
template <class T> DoubllyLinked <T> :: ~DoubllyLinked()
{
  while(!empty())
  {
    removeFront();
    cout<<"Made it here destructor\n";
  }
}
template <class T> DoubllyLinked<T>::DoubllyLinked(const DoubllyLinked &orig)
{
  node<T> *p;
  node<T> *last;
  if (orig.first==NULL)                 //if orig is empty
  {
    first=NULL;
  }
  else 
  {
    node<T> *temp= new node<T>;         //copy first node
    temp->item=orig.first->item;
    temp->next=NULL;
    first=temp;
    last=first;
    p=orig.first->next;
    while(p!=NULL)                      //copy remaining nodes
    {
      temp=new node<T>;
      temp->item=p->item;
      temp->next=NULL;
      last->next=temp;
      last=last->next;
      p=p->next;
    }
  }
}//end copy constructor

template <class T> void DoubllyLinked<T>::operator=(const DoubllyLinked &orig)
{
  node<T> *p;
  node<T> *temp;
    while(first!=NULL)
    {
      temp=first;
      first=first->next;
      delete temp;
    }
    if(orig.first!=NULL)
    {
      temp=new node<T>;
      temp->item=orig.first->item;
      temp->next=NULL;
      first=temp;
      last=first;
      p=orig.first->next;
      while(p!=NULL)
      {
        temp=new node<T>;
        temp->item=p->item;
        temp->next=NULL;
        last->next=temp;
        last=last->next;
        p=p->next;
      }
    }
}//end operator=

template <class T> T &DoubllyLinked<T> :: operator[](int i)const
{
  node<T> *temp;
  int count=0;
  if(i<0|| first==NULL)
  {
    cout<<"\nERROR!! Cannot find that index []\n";
    return first->item;
  }
  for(temp=first; temp!=NULL && count!=i; temp=temp->next)
    count++;
  return temp->item;
}

template <class T> void DoubllyLinked<T> :: addFront(T val)
{//INPUT: value to be added to the front of the list
 //OUTPUT: none
 //PURPOSE: add value to the front of the list
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
    exit(-1);
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
    exit(-2);
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
  if(empty())
    return -1;
  return first->item;
}//end getFront

template <typename T> T DoubllyLinked<T> :: getBack()
{//INPUT: none
 //OUTPUT: item at back of list
 //PURPOSE: return item at the back of the list without deleting
  if(empty())
    return -1;
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
{// INPUT: value to delete
 // OUTPUT: boolean value representing success of deletion 
 // PURPOSE: searches list to delete user defined value
  bool retval = false;
  node<T> *tmp, *next;
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

// make sure to put a header on this.
// make sure to put your list code above this

int main () {
  int i, j;

  cout << "Working with an int doublly linked list\n";
  DoubllyLinked <int> di;
  DoubllyLinked <int> dii;

  di.addFront(3);
  di.addBack(7);
  di.addInOrder(10);
  di.addInOrder(1);
  di.addInOrder(5);
  
  // now copy dii over since there are items in di
  dii = di;
  
  di.displayForward(); 
  di.displayBackward();
  di.displayForward(); 
  di.deleteItem(5);
  di.deleteItem(6);
  di.deleteItem(1);
  di.deleteItem(10);
  for (i=0; i<3; i++) 
    dii[i] = i;
  while (!di.empty()) {
    cout << di.removeFront() << " ";
  } 
  for (i=0; i<3; i++) 
    cout << dii[i] << " ";
  cout << endl;
  dii.displayForward();
  cout << endl << endl;
  
  cout << "Working with an string doublly linked list\n";
  DoubllyLinked  <string> ds;

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
  ds.displayBackward();
  ds[0] = "Bob";
  while (!ds.empty()) {
    cout << ds.removeBack() << " ";
  } 
  cout << endl << endl;

  // should cause some sort of error since nothing in ds
  ds[0] = "Bob";

  return 0;
} // end main
