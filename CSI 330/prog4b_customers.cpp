//NAME: Madelaine Zinser
//DATE: 10/16/2015
//PURPOSE: Implement a Queue that tracks customers, duration for help
//and arrival time to determine the average wait time for all of the users

#include <iostream>
#include "/lib/330/queue.h"
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

//Struct to hold times for customers
struct Customer
{
  int arrival_time;
  int duration;
  int customer_number;
};

int main ()
{
  string filename, inputfilename;
  ifstream inputfile;
  Queue <Customer> q(100);
  Customer c;
  int time=0, wait=0, wait_total=0, counter=0;
  double average=0.0;
  bool DEBUG=true;
  while(!inputfile.is_open())
  {
    cout<<"Input filename: ";
    getline(cin, inputfilename);
    inputfile.open(inputfilename.c_str(), ios::in | ios::binary);
  }
  //While you can still input customer data, add object from struct to queue 
  while(inputfile>>c.customer_number>>c.arrival_time>>c.duration)
  {
    q.enqueue(c);
  }
  //while the queue is not empty calculate time data
  while(!q.empty())
  { //get first in line's data and save in struct object
    c=q.getFront();
    if(time>=c.arrival_time)
    {
      q.dequeue();
      wait=time-c.arrival_time;
      wait_total+=wait;
      time+=c.duration;
      counter++;
      DEBUG&&cout<<"\tTime is "<<time<<" wait is "<<wait<<" for customer "<<counter<<endl;
    }
    else
      time++;
  }
  average=(double) wait_total/counter;
  cout<<fixed<<showpoint<<setprecision(1);
  cout<<"Average wait time is "<<average<<endl;
 
  return 0;
}
