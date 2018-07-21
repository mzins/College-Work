// NAME:    Jim Feher
// DATE:    Oct 17, 2009
// PURPOSE: Program to illustrate issues dealing with pointers
//          companion to extra_pointers.txt assignment

#include <iostream>
#include <iomanip>
using namespace::std;

int main () {

  int *iPTR,*jPTR;
  int i=2,j=3;
  int a[5] = {2,1,0,8,9};

  cout << "STARTING:\n";
  cout <<setw(6)<< "i:"    <<setw(16)<< i    << "\t&i:\t"    << &i    << endl;
  cout <<setw(6)<< "j:"    <<setw(16)<< j    << "\t&j:\t"    << &j    << endl;
  cout <<setw(6)<< "iPTR:" <<setw(16)<< iPTR << "\t&iPTR:\t" << &iPTR << endl;
  cout <<setw(6)<< "jPTR:" <<setw(16)<< jPTR << "\t&jPTR:\t" << &jPTR << endl;
  cout <<setw(6)<< "a:"    <<setw(16)<< a    << endl;
  
  iPTR = &i;
  jPTR = iPTR; 

  cout << "After: iPTR = &i;\nAnd  : jPTR = IPTR;\n";
  cout << "i:\t"      << i     << "\t&i:\t"  << &i   << endl;
  cout << "*iPTR:\t"  << *iPTR << "\tiPTR\t" << iPTR << endl;
  cout << "j:\t"      << j     << "\t&j:\t"  << &j   << endl;
  cout << "*jPTR:\t"  << *jPTR << "\tjPTR\t" << jPTR << endl << endl;


  *iPTR = 7.0;
  cout << "After: *iPTR = 7;\n";
  cout << "i:\t"      << i     << "\t&i:\t"  << &i   << endl;
  cout << "*iPTR:\t"  << *iPTR << "\tiPTR\t" << iPTR << endl;
  cout << "j:\t"      << j     << "\t&j:\t"  << &j   << endl;
  cout << "*jPTR:\t"  << *jPTR << "\tjPTR\t" << jPTR << endl << endl;

  
  jPTR = &j;
  cout << "\nAfter: jPTR = &j; \n";
  cout << "i:\t"      << i     << "\t&i:\t"  << &i   << endl;
  cout << "*iPTR:\t"  << *iPTR << "\tiPTR\t" << iPTR << endl;
  cout << "j:\t"      << j     << "\t&j:\t"  << &j   << endl;
  cout << "*jPTR:\t"  << *jPTR << "\tjPTR\t" << jPTR << endl << endl;


  iPTR = jPTR;
  cout << "\nAfter: iPTR = jPTR; \n";
  cout << "i:\t"      << i     << "\t&i:\t"  << &i   << endl;
  cout << "*iPTR:\t"  << *iPTR << "\tiPTR\t" << iPTR << endl;
  cout << "j:\t"      << j     << "\t&j:\t"  << &j   << endl;
  cout << "*jPTR:\t"  << *jPTR << "\tjPTR\t" << jPTR << endl << endl;
 
  j = 4;
  cout << "\nAfter: j = 4; \n";
  cout << "i:\t"      << i     << "\t&i:\t"  << &i   << endl;
  cout << "*iPTR:\t"  << *iPTR << "\tiPTR\t" << iPTR << endl;
  cout << "j:\t"      << j     << "\t&j:\t"  << &j   << endl;
  cout << "*jPTR:\t"  << *jPTR << "\tjPTR\t" << jPTR << endl << endl;

  for (int ii=0; ii<1000; ii++) {
    cout << "&a[" << ii << "]: " << &a[ii] 
         << "\t&a: " << a 
         << "\ta[" << ii << "]: " << a[ii] << endl;
  }

  for (iPTR = a; iPTR <= &a[4]; iPTR++) {
    cout << "iPTR: " << iPTR << "\t*iPTR: " << *iPTR << endl;
  }

  return 0;
  
}  // end main
//b) i,j,iptr, and jptr were assigned 4 byes. Array a, was given 20 bytes
//c)The addresses change. The computer is running multiple programs at once and //allocates new memory each time it is compiled. 
//d)The array went out of bounds, so the numbers displayed are from other memory//locations. a[8] and a[9] share the same addresses as j and i. 
//e)The array printed out the 1000 memory location addresses and variables proc
//eeding the array.
//f)The second loop adds one byte to the pointer address. 
