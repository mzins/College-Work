#include <iostream>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <cmath>
#include <ctime>


using namespace std;
int findcost(int map[]);
char getchar(int x);
void setnext(int next[], int cp[]);
void print(int arr[]);
bool keep(double pb);
void annealing();
void genetic();
bool charsearch(int s[], int x);



const int sze=10;
int adjmatx[sze][sze]={-1,8,6,23,3,14,17,55,13,8,-1,11,39,21,4,8,27,55,6,11,-1,12,2,13,10,21,18,23,39,12,-1,9,16,4,13,34,3,21,2,9,-1,8,31,12,15,14,4,13,16,8,-1,7,22,11,17,8,10,4,31,7,-1,3,7,55,27,21,13,12,22,3,-1,19,13,55,18,34,15,11,7,19,-1};

struct org{
  int path[sze];
  int fitness;
  double prob;
};
void setfitness(vector <org> &p);
int findprob(vector <org> &p);
void crossover(int p[], int m[], vector <org> &c);


int main(){
  int choice=0;
  do{
    do{
      cout<<"Press 1 for Annealing \nPress 2 for Genetic Algorithm\n";
      cout<<"Press 3 to quit\n";
      cin>>choice;
    }while (choice<1 || choice>3);
    switch(choice){
      case 1:
        annealing();
        break;
      case 2:
        genetic();
        break;
    };
  }while(choice!=3);

  srand(time(NULL));
  return 0;
}//end main

void genetic(){
  int p1, p2, best=0;
  vector <org> pop(10);
  vector <org> gop(10);
  std :: vector<org>::iterator it;
  int *str, *stp;
  int t=0;

  //initialize original population with random paths
  for(int i=0; i<pop.size(); i++) {
    str=pop[i].path+1;
    stp=pop[i].path+9;
    for(int j=1; j<sze-1; j++) {
      pop[i].path[j]=j;
    }//end for
    random_shuffle(str,stp);
  }//end for

//prints paths of original
  for(int i=0; i<pop.size(); i++) {
    cout<<"organism "<<i+1<<": ";
    for(int j=0; j<sze; j++) {
      cout<<pop[i].path[j]<<" ";
    }//end for
    cout<<endl;
  }//end for

  while(t<30){ 
    setfitness(pop);
    p1=findprob(pop);
    p2=findprob(pop);

    gop.erase(gop.begin(), gop.end());
    while(gop.size()<=8){
      crossover(pop[p1].path,pop[p2].path,gop);
    }
    setfitness(gop);
    //make children the new parents
    pop=gop;
    t++;
    //print
    for(int i=0; i<pop.size(); i++) {
      cout<<"organism "<<i+1<<": ";
      for(int j=0; j<sze; j++) {
        cout<<pop[i].path[j]<<" ";
      }//end for
      cout<<endl;
    }//end for
  }//end while


  for(int i=1; i<pop.size(); i++) {
    if(pop[i].fitness<pop[best].fitness) 
      best=i;
  }//end for
  cout<<"Best fitness is: "<<pop[best].fitness<<" with path ";
  for(int i=0; i<sze; i++)
    cout<<getchar(pop[best].path[i])<<" ";
  cout<<endl;
}//end genetic

void crossover(int p[], int m[], vector <org> &c) {
//input: paths of both parents and the vector of new generation
//output: none
//purpose: perform cross over on both parents to create new path objects for children. 
//Push children org nodes onto new generation vector
  const bool DEBUG=false;
  int start, stop, temp;
  org child1, child2;
  start=rand()%10;
  stop=rand()%10;

  if(start==stop) //only keeps one node
    stop++;
  if(start>stop) {//puts start before stop
    temp=start;
    start=stop;
    stop=temp;
  }//end if
  for(int i=start; i<=stop; i++) {
    child1.path[i]=p[i];
    child2.path[i]=m[i];
  }//end for

  //make telomeres zero
  child1.path[0]=0;
  child2.path[0]=0;
  child1.path[sze-1]=0;
  child2.path[sze-1]=0;

  for(int i=1; i<sze-1; i++) {
    if(!(i>=start && i<=stop)) {
      for(int j=1; j<sze-1; j++) {
        if(!charsearch(child1.path, m[j])) {
          child1.path[i]=m[j];
        }//end if
        if(!charsearch(child2.path, p[j])) {
          child2.path[i]=p[j];
        }//end if
      }//end for
    }//end if
  }//end for

  //mutate

  int mut=rand()%1000;
  if(mut<5){
    int swap1=rand()%sze;
    int swap2=swap1+1;
    int temp=child1.path[swap1];
    child1.path[swap1]=child1.path[swap2];
    child1.path[swap2]=temp;
    swap1=rand()%sze;
    swap2=swap1+1;
    temp=child2.path[swap1];
    child2.path[swap1]=child2.path[swap2];
    child2.path[swap2]=temp;
  }//end if


  c.push_back(child1);
  c.push_back(child2);

  if(DEBUG){
    cout<<"Parent one's path: ";
    for(int i=0; i<sze; i++)
      cout<<p[i]<<" ";
    cout<<endl;
    cout<<"Parent two's path: ";
    for(int i=0; i<sze; i++)
      cout<<m[i]<<" ";
    cout<<endl;
    cout<<"Child one's path: ";
    for(int i=0; i<sze; i++)
      cout<<child1.path[i]<<" ";
    cout<<endl;
    cout<<"Child two's path: ";
    for(int i=0; i<sze; i++)
      cout<<child2.path[i]<<" ";
    cout<<endl;
  }//end debug print
  
}//end crossover

bool charsearch(int s[], int x) {
//input: array of parent's path and character to search for
//output: boolean true or false if found
//purpose: search for a character in path array
  bool retans=false;
  for(int i=1; i<sze-1; i++) {
    if(s[i]==x)
      retans=true;
  }//end for
  return retans;
}//end charsearch



void setfitness(vector <org> &p){
  const bool DEBUG=false;
  double totalfit=0;
  for(int i=0; i<p.size(); i++){
    p[i].fitness=findcost(p[i].path);
    totalfit+=p[i].fitness;
  }//end for
  DEBUG && cout<<"totalfit: "<<totalfit<<endl;
  for(int i=0; i<p.size(); i++){
    p[i].prob=1.0-static_cast<double>(p[i].fitness/totalfit);
    p[i].prob=p[i].prob*1000;
  }//end for
}//end setfitness

int findprob(vector <org> &p) {
  int accept=0, checkcost=0, rnum;
  bool found=false;
  rnum=rand()%3000;
  for(int i=0; i<p.size() && !found; i++) {
    checkcost+=p[i].prob;
    if(rnum<checkcost) {
      found=true;
      accept=i;
    }//end if
  }//end for
  return accept;
}// end findprob

void annealing(){
  int curpath[sze]={0,1,2,3,4,5,6,7,8,0}, curcost;
  int nextpath[sze], nextcost;
  double E;
  float T=10000;
  const bool DEBUG=false;	
  int *first, *last; //create pointers to array to send to random_shuffle
  first=&curpath[1];	
  last=&curpath[sze-2];
  random_shuffle(first, last);
  setnext(nextpath, curpath);		//Set initial paths

  do{
    curcost=findcost(curpath);
    nextcost=findcost(nextpath);
    E=curcost-nextcost;
    if(E>0) {
      for(int x=0; x<sze; x++)	//nextpath is cheaper. Make nextpath curpath
        curpath[x]=nextpath[x];
      setnext(nextpath, curpath);
    }// end if
    else {//if  probability is correct, then switch and create new next
       if(keep(exp(E/T))) {
         for(int x=0; x<sze; x++) 
            curpath[x]=nextpath[x];
         setnext(nextpath, curpath);
       }//end if
       else
         setnext(nextpath, curpath);		//create new next
    }//end else
    T-=5;

		
  }while(T>0);
	
  cout<<"Curpath is: ";		
  print(curpath);
  cout<<"\nCurent cost is: "<<curcost<<endl;
	
}//end annealing

int findcost(int map[]) {
//input: array of the path
//output: the total cost of path
//purpose: find the cost of using traversing through the path
  const bool DEBUG=false;
  int totalcost=0;
  for(int i=0; i<sze-2; i++) {
    totalcost+=adjmatx[map[i]][map[i+1]];
    DEBUG && cout<<"finding cost between "<<getchar(map[i])<<" and "<<getchar(map[i+1])<<" is "<<adjmatx[map[i]][map[i+1]]<<endl;
  }//end for

  return totalcost;
}//end findcost

char getchar(int x){
//input: the integer value represented in the adjacency matrix
//output: character that represents a node
//purpose: find the character represented by integer value 
  if(x>=0 && x<=25)
    return x+97;
  else if(x>=26 && x<=34)
    return x+39;
}//end getchar

void setnext(int next[], int cp[]) {
//input: nextpath array by reference
//output: none
//purpose: create new path assigned as next
  const bool DEBUG=false;
  int s1, s2;
  for(int i=0; i<sze; i++) //set the values of cp to next
    next[i]=cp[i];
  s1=rand()%9;
  s2=rand()%9;
  /*if(s2==s1)		//if the program swaps the same index
    s2=rand()%9;*/
  if(s1>sze-1)
    s1--;
  swap(next[s1], next[s1+1]);

  DEBUG && cout<<"\nS1 is: "<<s1<<" S2 is: "<<s2<<endl;

}//end setnext

void print(int arr[]) {
//input: array to be printed
//ouput: none
//purpose: print out array
  for(int i=0; i<sze; i++)
    cout<<getchar(arr[i])<<" ";
}//end print

bool keep(double pb){
//input: the probability calculated with the Boltzman function
//output: boolean true or false
//purpose: indicate whether or not to accept nextpath as curentpath
  double testvalue=rand()%100;
  bool retval=false;
  pb*=100;
  if(testvalue<=pb)
    retval=true;
  return retval;
}//end keep