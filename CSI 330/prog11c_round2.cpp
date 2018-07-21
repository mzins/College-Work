//Madelaine Zinser
//11c Prims algorithm and shortest path
//11/19/2015

#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <string>
using namespace std;

void warshall(int **, int );
void prims(int **, int);
void display(int **, int );

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

int main ()
{
  int sz=0, i, j;
  int **matrix;
  string filename, inputfilename;
  ifstream fin;
  while (!fin.is_open()) {
    cout<<"Input filename: ";
    getline(cin, inputfilename);
    fin.open(inputfilename.c_str(), ios::in | ios::binary);
  }//end while

  matrix=Matrix(sz, fin);
  //display(matrix, sz); 
  prims(matrix, sz);
  warshall(matrix, sz);
  
  return 0;
}

//****************************display matrix***********************************
void display(int **m, int size){
  int i, j;
  for(i=0; i<size; i++){
    for(j=0; j<size; j++){
      cout<<"\t"<<m[i][j];
    }//end for  
    cout<<endl;
  }//end for
}//end display()



//*********************spanning tree********************************
void prims(int **m, int size)
{//INPUT: Pointer to adjacency matrix and size of 2D array
 //OUTPUT: none
 //PURPOSE: Find the spanning tree
  const bool DEBUG=false;
  if(size>100){
    cout<<"ERROR!! Size cannot be greater than 100\n";
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
  for(int i=0; i<size; i++){
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
  for(int i=0; i<(size-1); i++)
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


