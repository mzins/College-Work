//Madelaine Zinser
//program 11b Breadth and Depth first search
//11/15/2015

#include <iostream>
#include "/lib/330/queue.h"
#include "/lib/330/stack.h"
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

bool finished(int [], int);
void display(int, int);
void depthfirst(int **matrix, int size);
void bredthfirst(int **matrix, int size);
void displayMatrix(int**t, int size);
int getInt(int);

int ** Matrix(int &s)
{
  int **ary=new int*[s];
  for(int i=0; i<s; i++)
  {
    ary[i]=new int[s];
  }
  return ary;
}//end matrix




int main()
{
  int size, choice=0;
  int **matrix;
  string filename, inputfilename;
  ifstream inputfile;
  while(!inputfile.is_open())
  {
    cout<<"Input filename: ";
    getline(cin, inputfilename);
    inputfile.open(inputfilename.c_str(), ios::in | ios::binary);
  }

  
  inputfile>>size; 
  matrix=Matrix(size);


  for(int i=0; i<size; i++){
    for(int j=0; j<size; j++)
      inputfile>>matrix[i][j];
  }//end for

  do{
    cout<<"Do you want to\n1)Perform Bredth-First Search\n";
    cout<<"2)Depth-First Search\n";
    cout<<"3)Display matrix\n";
    cout<<"4)Quit :(\n";
    choice=getInt(1);

    switch(choice)
    {
      case 1:
        bredthfirst(matrix, size);
        break;
      case 2:
        depthfirst(matrix, size);
        break;
      case 3:
        displayMatrix(matrix, size);
        break;
      case 4:
        cout<<"See Ya!\n";
        break;
      default:
        break;       
    }

  }while(choice!=4);
  
  return 0;
}

void bredthfirst(int **matrix, int size)
{//INPUT: take in adj matrix and size
 //OUTPUT: no output
 //PURPOSE: demonstrate a bredthfirst search

  int temp, start=0;
  Queue<int> q;
  int visit[size];
  for(int i=0; i<size; i++)
    visit[i]=0;

  cout<<"What node should I start at?\n";
  start=getInt(0);;

  visit[start]=1;
  q.enqueue(start);
  while(!q.empty() && !finished(visit, size)){
    temp=q.dequeue();
    //visit[row]=1;
    for(int i=0; i<size; i++){
      if(matrix[temp][i]>=1){
        if(visit[i]==0){
          visit[i]=1;
          display(temp, i);
          q.enqueue(i);
        }//end if
      }//end if
    }//end for(i)
  }//end while
  cout<<endl;
}//end bredth-first search


void depthfirst(int **matrix, int size)
{//take in adj matrix
 //no output
 // demonstrate a depth-first search
  int start, row, prev;
  Stack<int> s;
  int visit[size];
  
  for(int i=0; i<size; i++)     //set visit to 0
    visit[i]=0;
  cout<<"Where do I start?\n";
  start=getInt(0);
  
  visit[start]=1; 
  s.push(start);
  row=s.getTop();

  while(!s.empty() && !finished(visit, size)){
    for(int i=0; i<size; i++){
      if(matrix[row][i]>=1){
        if(visit[i]==0){
          s.push(i);
          display(row,i);
          prev=row;
          row=i;
          visit[i]=1;
          i=-1;
        }//end if(visited)
      }//end if(matrix[row][i])
    }//end for
    if(!finished(visit, size)){
      row=s.pop();
      prev=s.getTop();
      cout<<prev<<" <- "<<row<<endl;
      row=prev;
    }//end if
  }//end while
}//end depth-first search


bool finished(int v[], int size)
{//take in visited array
 //T/F if all 1s
 //determine if the nodes are all visited
  bool retval=true;
  for(int i=0; i<size; i++)
  {
    if(v[i]<1)
    {
      retval=false;
    }
  }
  return retval;
}//end finished

void display(int a, int b)
{//two int nodes
 // no output
 // display transition
  cout<<a<<" -> "<<b<<"\n";
}//end display


void displayMatrix(int **a, int size)
{
// INPUT  : a square matrix, size of the matrix
// OUTPUT : matrix
// PURPOSE: Display the matrix neatly
  for(int i=0; i<size; i++)
  {
    for(int j=0; j<size; j++)
    {
      cout<<setw(3)<<a[i][j]<<"\t";
    }
    cout<<endl;
  }
}

int getInt(int min){
//INPUT: The minimum value that the int can take
//OUTPUT: Valid int
//PURPOSE: Insure that we get a good int
  int a;
  cin>>a;
  while(!cin || a < min){
    if(!cin){
      cin.clear();
      cin.ignore(100, '\n');
    }//end if
    cout<<"Please enter an integer equal to or "; 
    cout<<"greater than: "<<min<<endl;
    cin>>a;
  }//end while
  return a;
}//end getInt()























