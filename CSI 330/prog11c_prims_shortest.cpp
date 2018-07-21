//Madelaine Zinser
//11c Prims algorithm and shortest path
//11/19/2015

#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <cstring>
using namespace std;

int ** Matrix(int &s)
{
  int **ary = new int *[s];
  for(int i=0; i<s; i++)
    ary[i]=new int[s];
  return ary;
}//end matrix

bool DEBUG = false;
int adjMat[20][20];
int nextHop[20][20];
int start, end, numNodes, numPaths;


void prims(int **m , int size);
void warshall();
bool getData();
void displayMatrix(int m[][20], int r, int c);

ifstream fin;
int main ()
{
  int size;
  int **matrix;
  string filename, inputfilename;
  ifstream fin;
  while (!fin.is_open())
  {
    cout<<"Input filename: ";
    getline(cin, inputfilename);
    fin.open(inputfilename.c_str(), ios::in | ios::binary);

  }

  fin>>size;
  matrix=Matrix(size);

  for(int i=0; i<size; i++)
  {for(int j=0; j<size; j++)
    fin>>matrix[i][j];    
  }
//  for(int i=0; i<size; i++)
//  {for(int j=0; j<size; j++)
//    cout << "\t" << matrix[i][j];    
//  }
  prims(matrix, size);
 
  bool s=false;
  if(s)
    warshall();
  
  return 0;
}


bool getData() {
  bool retVal = true;
  int i, j, from, to, cost;
  
  // set the nextHops to -1 to indicate no path available
  // set the adjMat distances to 1000000, which is larger than
  // the longest possible path for this case, could set to inf
  // or use max_int or max_float from climits or cfloat class
  for (i=0; i<20; i++) {
    for (j=0; j<20; j++) {
      adjMat[i][j]  = 1000000;
      nextHop[i][j] = -1;
    }
  }
  
  fin >> numNodes;
  if ( numNodes == 0) {
    retVal = false;
  } else {
    fin >> numPaths >> start >> end;
    for (i=0; i<numPaths; i++) {
      fin >> from >> to >> cost;
      // sub 1 from from and to as the indicies of array start with 0
      adjMat[from-1][to-1] = cost;
      nextHop[from-1][to-1] = to-1;
      
      adjMat[to-1][from-1] = cost;
      nextHop[to-1][from-1] = from-1;
    }
  }
  return retVal;
}

void warshall()
{
  int i,j,k, cost;
  const int DEBUG=true;

  while (getData()){
    DEBUG && cout << "Got Data " << endl;
    if (DEBUG) {
      displayMatrix(adjMat, numNodes, numNodes);
      cout << endl;
      displayMatrix(nextHop, numNodes, numNodes);
    }

    // do warshalls now
    for (k=0; k<numNodes; k++) {
      for (i=0; i<numNodes; i++) {
        for (j=0; j<numNodes; j++) {
          if (adjMat[i][k] + adjMat[k][j] < adjMat[i][j]) {
            // just found a cheaper path
            adjMat[i][j] = adjMat[i][k] + adjMat[k][j];
            nextHop[i][j] = nextHop[i][k];
          }
        }
      }
    }
    if (DEBUG) {
      cout << endl;
      displayMatrix(adjMat, numNodes, numNodes);
      cout << endl;
      displayMatrix(nextHop, numNodes, numNodes);
    }

    cout << adjMat[start-1][end-1] << endl;
    // print the path taken
    i=start-1;
    while (i != end-1) {
      cout << i+1 << " ";
      i = nextHop[i][end-1];
    }
    cout << end << endl;

  }
}

void displayMatrix(int m[][20], int r, int c) {
  int i, j;
  for (i=0; i<r; i++) {
    for (j=0; j<c; j++ ) {
      cout << setw(10) << m[i][j];
    }
    cout << endl;
  }
}


void prims(int **m, int size)
{//INPUT: Pointer to adjacency matrix and size of 2D array
 //OUTPUT: none
 //PURPOSE: Find the spanning tree
  const bool DEBUG=true;
  if(size>100)
  {
    cout<<"ERROR!! Size cannot be greater than 100\n";
    exit(-1);
  }
  int visited[size];
  int path[size][2];
  for(int i=0; i<size; i++)
  {
    visited[i]=0;
    path[i][0]=1111;
    path[i][1]=1111;
  }
  int lcost, lcost_from, lcost_to, count=0, ii, jj;
  bool finished=false;

  for(int i=0; i<size; i++)
  {for(int j=0; j<size; j++)
    {if(m[i][j]>0 && (lcost<0 || lcost>m[i][j]))
      {
        lcost=m[i][j];
        lcost_from=i;
        lcost_to=j;
      }
    }
  }
/*
  for(ii=0; ii<size; ii++)
  {for(jj=0; jj<size; jj++) 
    cout << "\t" << m[ii][jj];
    cout << endl;
  }
*/

  path[0][0]=lcost_from;
  path[0][1]=lcost_to;
  count++;
  DEBUG && cout<<"\tin first for loop, count is: "<<count<<"\n\n";
  DEBUG && cout << "lcf: " << lcost_from << " lct: " << lcost_to << endl;
  visited[lcost_from]=1;
  visited[lcost_to]=1;

  while(!finished && count<(size-1))
  {
    cout << "here\n";
    lcost=-1;
 
    for(int r=0; r<size; r++)
    {if(visited[r]>0)
      {for(int c=0; c<size; c++)
        {
          DEBUG && cout<<"\tBefore if statement\n";
            DEBUG && cout<<"\t\tR is: "<<r<<" C is: "<<c<< " cost: "
                         << m[r][c] << " lc: " << lcost << " v: "
                         << visited[c] << " count: " << count << endl;
          if(m[r][c]>0 && (lcost<1 || lcost>m[r][c]) && visited[c]<1)
          {
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
    for(int i=0; i<size; i++)
    {
      if(visited[i]<1)
      { finished=false;
        DEBUG && cout<<"finished is: "<<finished<<"\n";
      }

    }
  }//end while loop
  cout<<"Here is the path\n";
  for(int i=0; i<(size-1); i++)
  {
      cout<<path[i][0]<<" - "<<path[i][1]<<endl;
  }
}//end prims();

