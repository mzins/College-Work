// Open a file to read data into a linked list using 
// a simple structure
// DATE: 9/19/15
// NAME: Madelaine Zinser
// STUDENT ASSIGNMENT:
//   1. Write a function that takes the first pointer and displays list
//   2. Write a function that takes the first and returns the average
//   3. Write a function that allows the insertion of an item at the end
//      of the list, given you are only provided the first pointer
//      This should work even if the first points to NULL


#include <iostream>
#include <fstream>

using namespace std;

struct node 
{
	int item;
	node *next;
};

void displayList(node *);
float average(node *);
void insert(node *, int);

int main () 
{
        ifstream IN;
	node *first, *current_node;
	int i, temp;

  IN.open("file.txt");
  if (!IN) 
  {
	  cout << "Bad file, numbers.dat, it cannot be opened.\n";
	  return -1;
  }

  // priming read for first item
  if (IN >> temp)
  {
	  first = new node;
	  first->item = temp;
	  first->next = NULL;
	  current_node = first;
  }

  while (IN) 
  {
	  IN >> temp;
	  if (IN)
	  {
		  insert(first, temp);
	  }
  }
  displayList(first);
  cout<<"\nThe average is "<<average(first)<<endl;
  cout<<"Add a new number   ";
  cin>>temp;
  insert(first, temp);

  displayList(first);
  cout<<"\nThe average is "<<average(first)<<endl;

  IN.close();
  return 0;

}  // end main

void displayList(node *f)
{
// INPUT  : Pointer to first item in list
// OUTPUT : 
// PURPOSE: Display the list
  node *curNode;
  
  for (curNode = f; curNode != NULL; curNode = curNode->next)
  {
	  cout << curNode->item << endl;
  }
} // end displayList

float average(node *f)
{
// INPUT  : Pointer to first item in list
// OUTPUT : Average of the list
// PURPOSE: Display the list
  node *curNode;
  float total=0;
  int counter=0;
  
  for (curNode = f; curNode != NULL; curNode = curNode->next) 
  {
	  total+=curNode->item;
	  counter++;
  }
  return total/counter;
}//end of average

void insert(node *f, int temp)
{
// INPUT  : Pointer to first item in list
// OUTPUT : 
// PURPOSE: Add new node to the end of list
	
  node *current_node, *next_node, *last_node;

	if(f==NULL)
	{
		f = new node;
		f->item = temp;
		f->next = NULL;
		current_node = f;
	}

	for (last_node = next_node = f; next_node != NULL; next_node = next_node->next)
		{
			last_node = next_node;
		}
		last_node->next=new node; 
		last_node= last_node->next;
		last_node->item = temp;
		last_node->next = NULL;  

}//end of insert
