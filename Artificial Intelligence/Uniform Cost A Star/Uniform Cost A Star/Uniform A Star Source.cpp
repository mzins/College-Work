//Madelaine Zinser
//CSI 440
//2/16/16
//Create a uniform search on a maze

#include <iostream>
#include <string>
#include <queue>
#include <cmath>
using namespace std;

int getint(char x);
char getchar(int x);
string funct(string path, int start, int end);
int hvalue(int n);
void uniformcost();
void astar();

struct node{
  string path;
  int cost;
  bool operator<(const node&rhs)const{
    return cost > rhs.cost;
  }
};//end path

const int SZE=35;
int adjmax[SZE][SZE]={0,	28,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
28,	0,	2,	0,	0,	0,	0,	0,	4,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
0,	2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	17,
0,	0,	0,	0,	2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	14,	0,	0,	0,	0,	0,	0,
0,	0,	0,	2,	0,	24,	2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
0,	0,	0,	0,	24,	0,	0,	5,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
0,	0,	0,	0,	2,	0,	0,	22,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	12,	0,	0,	0,	0,	0,
0,	0,	0,	0,	0,	5,	22,	0,	4,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	8,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
0,	4,	0,	0,	0,	0,	0,	4,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	10,	0,	0,	0,	0,	0,	0,	0,
0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	8,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	0,	16,	0,	0,	0,	0,	0,	6,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	16,	0,	0,	0,	0,	0,	0,	0,	0,	0,	6,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	0,	0,	0,	0,	5,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	8,	0,	0,
0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	9,	0,
0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	0,	6,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	6,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	6,	0,	0,	0,	0,	0,	0,	0,	4,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	5,	0,	0,	0,	0,	4,	0,	0,	0,	0,	0,	2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	5,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	6,	0,	0,	0,	0,	0,	0,	0,	5,	0,	2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
0,	0,	0,	0,	0,	0,	0,	8,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	0,	0,	0,	0,	2,	0,	0,	0,	0,	0,	0,	0,	0,	0,
0,	0,	0,	0,	0,	0,	0,	0,	0,	8,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	4,	0,	0,	0,	0,	0,	0,	3,	0,	0,	0,	0,
0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	0,	0,	0,	4,	0,	0,	0,	0,	0,	0,	0,	0,	2,	0,	0,	0,
0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	10,	0,	0,	0,	0,	0,	0,	0,	0,	0,
0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	0,	0,	10,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	0,	0,	0,	0,	0,	0,	0,
0,	0,	0,	0,	0,	0,	0,	0,	10,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	0,	0,	0,	0,	0,	0,	0,	3,
0,	0,	0,	14,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	0,	0,	0,	0,	0,
0,	0,	0,	0,	0,	0,	12,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	0,	4,	0,	0,	0,	0,
0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	3,	0,	0,	0,	0,	0,	0,	4,	0,	0,	0,	0,	0,
0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	0,	0,	0,	0,	0,	0,	0,	0,	2,	0,	0,
0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	8,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	0,	2,	0,
0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	9,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	0,	18,
0,	0,	17,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	3,	0,	0,	0,	0,	0,	18,	0};

int hmatx[SZE][2]={3,1,32,1,35,1,1,3,4,3,27,3,4,6,27,6,32,6,6,18,6,15,6,10,11,17,13,17,16,31,19,31,19,24,9,15,9,17,24,13,24,10,27,10,6,25,9,25,16,15,27,15,32,19,32,16,1,19,4,19,4,25,13,25,13,21,16,21,35,21};

int main (){
  int choice=0;

  do{
    do{
      cout<<"Enter 1 for Uniform cost search\nEnter 2 for A* Algorithm Search\nEnte 3 to quit\n";
      cin>>choice;
    }while(choice<1 || choice>3);
    switch (choice){
      case 1:
        uniformcost();
        break;
      case 2:
        astar();
        break;
      case 3:
        cout<<endl;
    }
  }while(choice!=3);
  
  return 0;
}//end main

void uniformcost(){
//input: none
//output: none
//purpose: use adjacency matrix to find the cheapest cost from node a to G with a uniform cost search
  int size, newcost, nextnodeI, checksize;
  char nextnode, addnode;
  priority_queue<node> pq;
  node temp,curnode,check;
  bool done=false, DEBUG=false;
  
  //start at a so push path "a" to queue with starting cost of 0
  curnode.path="a";
  curnode.cost=0;
  pq.push(curnode);
  //while loop starts here
  while(!done){
    temp=pq.top();
    pq.pop();
    size=temp.path.length();
    nextnode=temp.path[size-1];
    nextnodeI=getint(nextnode);

    for(int j=0; j<SZE; j++){
      if(adjmax[nextnodeI][j]>0){ //found a connection
        addnode=getchar(j);       //get character connection
        newcost=adjmax[nextnodeI][j];
        curnode.path=temp.path+addnode;
        curnode.cost=temp.cost+newcost;
        pq.push(curnode);
      }//end if
    }//end for
    //check if done here
    check=pq.top();
    checksize=check.path.length();
    DEBUG && cout<<"\tNext node is: "<<nextnode<<endl<<"\tTemp.cost: "<<temp.cost<<endl<<"\tCheck.cost: "<<check.cost<<endl;
    if(nextnode=='G' && (temp.cost < check.cost+1))
      done=true;
    
    DEBUG && cout<<"Path is: "<<temp.path<<"\nCost: "<<temp.cost<<endl;
  }//end while
  cout<<"Uniform Cost\n"<<funct(temp.path, 0, 1)<<endl<<"Cost is: "<<temp.cost<<endl<<endl;
}//end uniformcost


void astar() {
//input: none
//output: node
//purpose: find the cheapest path between nodes a and G by using A* algorithm
  int size, newcost, nextnodeI, checksize;
  char nextnode, addnode;
  priority_queue<node> pq;
  node temp,curnode,check;
  bool done=false, DEBUG=false;
  //start at a so push path "a" to queue with starting cost of 0
  curnode.path="a";
  curnode.cost=0;
  pq.push(curnode);
  
  while(!done){
    temp=pq.top();
    pq.pop();
    size=temp.path.length();
    nextnode=temp.path[size-1];
    nextnodeI=getint(nextnode);

    for(int j=0; j<SZE; j++){
      if(adjmax[nextnodeI][j]>0){ //found a connection
        addnode=getchar(j);       //get character connection
        newcost=adjmax[nextnodeI][j];
        curnode.path=temp.path+addnode;
        curnode.cost=temp.cost+newcost+hvalue(j);
        pq.push(curnode);
      }//end if
    }//end for
    //check if done here
    check=pq.top();
    checksize=check.path.length();
    DEBUG && cout<<"\tNext node is: "<<nextnode<<endl<<"\tTemp.cost: "<<temp.cost<<endl<<"\tCheck.cost: "<<check.cost<<endl;
    if(nextnode=='G' && (temp.cost < check.cost+1))
      done=true;
    
    DEBUG && cout<<"Path is: "<<temp.path<<"\nCost: "<<temp.cost<<endl;
  }//end while
  cout<<"A*\n"<<funct(temp.path, 0, 1)<<endl<<"Cost is: "<<temp.cost<<endl<<endl;
} //end astar

int getint(char x){
//input: character that represents a node
//output: the integer value represented in the adjacency matrix
//purpose: find the integer value represented by the character 
  if(x>='a' && x<='z')
    return x-97;
  else if(x>='A' && x<='Z')
    return x-39;
}//end getint

char getchar(int x){
//input: the integer value represented in the adjacency matrix
//output: character that represents a node
//purpose: find the character represented by integer value 
  if(x>=0 && x<=25)
    return x+97;
  else if(x>=26 && x<=34)
    return x+39;
}//end getchar

string funct(string path, int start, int end){
//input: final path, where start on the expansion, what the starting node is connected to next
//output: the path in full expansion form
//purpose: transform the stored path in to the expanded notation
  string retstring="";
  if (end>=path.length()){
    retstring=retstring+path[start]+'('+')';
    return retstring;
  }
  else{
    retstring=retstring+path[start]+'(';
    for(int i=0; i<SZE; i++){
      if(adjmax[getint(path[start])][i]>0){ // found connection in adjmatrix
        if(getchar(i)==path[end])       //connection is next node in path
          retstring+=funct(path, end, end+1);
        else
          retstring=retstring+getchar(i)+',';
        }//end if
      }//end for
  }//end else
  return retstring+')';
}//end funct

int hvalue(int n) {
//input: array index for node
//output: distance between node n and destination node
//purpose: calculate the heuristic value between two nodes

  const int xfinal=13;
  const int yfinal=21;
  int x,y, distx, disty;
  x=hmatx[n][0];
  y=hmatx[n][1];

  distx=xfinal-x;
  distx*=distx;
  disty=yfinal-y;
  disty*=disty;

  return sqrt(distx+disty);

}//end hvalue


 