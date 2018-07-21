#include <iostream>
using namespace std;

int ournacci(int);

int main ()
{
  int n;
  cout<<"Enter n   ";
  cin>>n;
  cout<<ournacci(n)<<endl;
  return 0;
}



// function definition
int getInt(int min) {
  // PURPOSE: Insure that we get a good int
  // INPUT  : The minimum value that the int can take, default to 0 if 
  //          if nothing entered.
  // OUTPUT : valid int
  int a;
  cin >> a;
  while ( !cin || a < min )
  {
    if (!cin)
    {// only fix if broken
      cin.clear();              // fix cin
      cin.ignore(100,'\n');       // clear the input buffer
    }
    cout << "Please enter an integer equal to or greater than: " << min;
    cin >> a;  } 
          return a;
} // end getInt

int ournacci(int n) 
{
// INPUT  : n>=0 
// OUTPUT : The nth fibonacci  
// PURPOSE: Calculate the nth fibonacci for a given input
  int ret_val;
  static int nth_call=0;
  cout<< "Called with n: " << n << " \ttimes: "<<++nth_call << endl;
  if (n < 0) {                                  // ERROR!
    cout << "ERROR: Fibonacci numbers start at 0.\n";
    ret_val = -1;                
  } else if (n == 1 || n == 2) {                // base cases
    ret_val = n;
  } else {
    ret_val = 2*ournacci(n-1) + 3*ournacci(n-2);  // recursion
  }
  return ret_val;
} // end function fibonacci
