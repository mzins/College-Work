//Madelaine Zinser
//11c Prims algorithm and shortest path
//11/19/2015


#include <iostream>
#include "/lib/330/queue.h"
#include "/lib/330/stack.h"
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <string>
using namespace std;

void warshall(int **, int );
void prims(int **, int);
void display(int , int );
void displayMatrix(int**t, int size);
void depthfirst(int **matrix, int size);
void bredthfirst(int **matrix, int size);
int getInt(int);
bool finished(int [], int);

int ** Matrix(int &s, ifstream &fin){
  fin>>s;
  int **ary = new int *[s];
  for(int i=0; i<s; i++)
    ary[i]=new int[s];

  for(int i=0; i<s; i++) {
    for(int j=0; j<s; j++){
       fin>>ary[i][j];    
    }//end for
  }//end for

  return ary;
}//end Matrix()

int main()
{
  int size=0, choice=0;
  int **matrix;
  string filename, inputfilename;
  ifstream fin;
  while(!fin.is_open()){
    cout<<"Input filename: ";
    getline(cin, inputfilename);
    fin.open(inputfilename.c_str(), ios::in | ios::binary);
  }//end while
  
  matrix=Matrix(size, fin);

  do{
    cout<<"Do you want to\n1)Perform Bredth-First Search\n";
    cout<<"2)Depth-First Search\n";
    cout<<"3)Spanning tree\n";
    cout<<"4)Minimum Path\n";
    cout<<"5)Display matrix\n";
    cout<<"6)Quit :(\n";
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
        prims(matrix, size);
        break;
      case 4:
        warshall(matrix, size);
        break;
      case 5:
        displayMatrix(matrix, size);
        break;
      case 6:
        cout<<"See Ya!\n";
        break;
      default:
        break;       
    }

  }while(choice!=6);
  
  return 0;
}

//*********bredthfirst**************
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

//***********depthfirst***************
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


//*********************spanning tree********************************
void prims(int **m, int size){
 //INPUT: Pointer to adjacency matrix and size of 2D array
 //OUTPUT: none
 //PURPOSE: Find the spanning tree
  const bool DEBUG=false;
  if(size>100||size<0){
    cout<<"ERROR!! Size cannot be greater than 100 or less than 0\n";
    exit(-1);
  }//end if(size)

  int visited[size];
  int path[size][2];
  int start, lcost, lcost_from, lcost_to, count=0, ii, jj;
  bool finished=false;

  for(int i=0; i<size; i++){
    visited[i]=0;
    path[i][0]=1111;
    path[i][1]=1111;
  }//end for
  cout<<"Where should I start?   ";
  cin>>start;

  visited[start]=1;
  /*for(int i=0; i<size; i++){
    for(int j=0; j<size; j++){
      if(m[i][j]>0 && (lcost<0 || lcost>m[i][j])){
        lcost=m[i][j];
        lcost_from=i;
        lcost_to=j;
      }//end if
    }//end for(j)
  }//end for(i)

  path[0][0]=lcost_to;
  path[0][1]=lcost_from;
  count++;
  DEBUG && cout<<"\tin first for loop, count is: "<<count<<"\n\n";
  DEBUG && cout << "lcf: " << lcost_from << " lct: " << lcost_to << endl;
  visited[lcost_from]=1;
  visited[lcost_to]=1;
*/
  while(!finished && count<(size-1)){
    lcost=-1;
    for(int r=0; r<size; r++){
      if(visited[r]>0){
        for(int c=0; c<size; c++){
          DEBUG && cout<<"\tBefore if statement\n";
          DEBUG && cout<<"\t\tR is: "<<r<<" C is: "<<c<< " cost: "
                       << m[r][c] << " lc: " << lcost << " v: "
                       << visited[c] << " count: " << count << endl;
          if(m[r][c]>0 && (lcost<1 || lcost>m[r][c]) && visited[c]<1){
            DEBUG && cout<<"\tInside if statement\n";
            DEBUG && cout<<"\t\tR is: "<<r<<" C is: "<<c<< " cost: "
                         << m[r][c] << endl;
            lcost=m[r][c];
            lcost_from=r;
            lcost_to=c;
          }//end if loop
        }//end for(c) loop
      }//end if(visit) loop
    }//end for(r) loop
    path[count][0]=lcost_from;
    path[count][1]=lcost_to;
    count++;
    DEBUG && cout<<"\tcount is: "<<count<<endl;
    visited[lcost_to]=1;
    visited[lcost_from]=1; //made changes here
    //check to see if finished
    finished=true;
    for(int i=0; i<size; i++){
      if(visited[i]<1){
        finished=false;
        DEBUG && cout<<"finished is: "<<finished<<"\n";
      }//end if
    }//end for
  }//end while loop
  cout<<"Here is the spanning tree\n";
  for(int i=0; i<count; i++)
    cout<<path[i][0]<<" -> "<<path[i][1]<<endl;
}//end prims()


//********************minimum path******************************
void warshall(int **m, int size){
//INPUT: adjacency matrix
//OUTPUT: none
//PURPOSE: the minimum path from two points
  int i,j,k, cost, start=0, end=0;
  int from, to; 
  const int DEBUG=true;

  cout<<"Where should the path start?   ";
  cin>>start;
  cout<<"Where should the path end?   ";
  cin>>end;

  int adjMat[size][size], nextHop[size][size];
  
  if (size!= 0) {
    for (i=0; i<size; i++) {
      for (j=0; j<size; j++) {
        if(m[i][j]==0){
          adjMat[i][j]  = 1000000;
          nextHop[i][j] = -1;
        }//end if
        else{
          adjMat[i][j]=m[i][j];
          nextHop[i][j]=j;
        }//end else
      }//end for
    }//end for
  }// end if
  else{
    cout<<"ERROR! Cannot find shortest path because graph is empty\n";
    exit(-1);
  }
  
  // do warshalls now
  for (k=0; k<size; k++) {
    for (i=0; i<size; i++) {
      for (j=0; j<size; j++) {
        if (adjMat[i][k] + adjMat[k][j] < adjMat[i][j]) {
          // just found a cheaper path
          adjMat[i][j] = adjMat[i][k] + adjMat[k][j];
          nextHop[i][j] = nextHop[i][k];
        }//end if
      }//end for
    }//end for
  }//end for

  i=start;
  j=0;
  
  cout<<"Here is the shortest path:\n";
  while(i!=end){
    cout<<i<<" -> ";
    i=nextHop[i][end];
    j=i;
    if(i!=end){
      cout<<j<<endl;
    }//end if
  }//end while
  
  cout << end << endl;

}// end warshall


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

void display(int a, int b){
 //two int nodes
 // no output
 // display transition
  cout<<a<<" -> "<<b<<"\n";
}//end display


void displayMatrix(int **a, int size){
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
}//end displayMatrix

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


