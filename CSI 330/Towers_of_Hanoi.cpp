//Name: Madelaine Zinser
//Date:9/27/2015
//Purpose: Solve the Towers of Hanoi problem

#include <iostream>
using namespace std;

void hanoi(int, char, char, char);

int main()
{
  int num_disks;
  cout<<"Please enter number of disks:   ";
  cin>>num_disks;
  cout<<"Start Towers of Hanoi\n";
  hanoi(num_disks, 'A', 'B', 'C');
  cout<<"I hope you didnt select 64 and end the world!\n";

  return 0;
}

void hanoi(int n, char source, char dest, char temp)
{
  //INPUT: number of rings, characters for the source, destination, and 
  //temporary pegs
  //OUTPUT: na
  //PURPOSE: demonstrate/ solve the steps in the Tower of Hanoi problem
  static int step=0;
  
  if (n>0)
  {
    //Move n-1 disks  from the source to temp using dest as the temporary peg
    hanoi(n-1, source, temp, dest);
    
    //Move a disk from source to dest
    cout<<"\nStep "<<++step<<": Move a disk from "<<source<<" to "<<dest<<endl;

    //move n-1 disks from temp to dest using source as the temporary peg
    hanoi(n-1, temp, dest, source);

  }

}

