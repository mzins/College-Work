//Madelaine Zinser
//CSI 330
//Use heap class that determines the average wait time implemented
//with a priority queue
//11/30/15

#include <iostream>
#include "/lib/330/heap.h"
#include "/lib/330/queue.h"
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

class Customer{
  public:
    int custnum;
    float dur, arrvtime;
    float priority;
    bool operator > (const Customer &right){
      bool status=false;
      if(priority > right.priority)
        status=true;
      return status;
    }//end operator
    bool operator < (const Customer &right){
      bool status=false;
      if(priority < right.priority)
        status=true;
      return status;
    }//end operator
};//end class


int main()
{
  string filename, inputfilename;
  ifstream fin;
  Heap <Customer> h;
  Queue <Customer> q;
  Customer c, tmp;
  const bool DEBUG=true;
  int custnum, dur, arrvtime, priority;
  int time=0, wait=0, wait_total=0, counter=0;
  double average=0.0;

  while(!fin.is_open()){
    cout<<"Input filename: ";
    getline(cin, inputfilename);
    fin.open(inputfilename.c_str(), ios::in | ios::binary);
  }//endwhile

  while(fin>>custnum>>arrvtime>>dur>>priority){
    c.custnum=custnum;
    c.arrvtime=arrvtime;
    c.dur=dur;
    c.priority=priority*10000+(10000-custnum);
    q.enqueue(c);
  }//end while

  tmp=q.getFront();
  for(int tme=0; !q.empty(); tme++){
    while(!q.empty() && tmp.arrvtime>=tme){
      tmp=q.dequeue();
      h.insertHeap(tmp);
      if(!q.empty())
        tmp=q.getFront();
    }//end while
  }//end for

  Customer temp;
  while(!h.empty()){
    h.deleteHeap(c);
    temp=c;
    DEBUG && cout << "first customer is "<<c.custnum<<endl;
    if(time>=c.arrvtime){
      DEBUG && cout<< "Inside if statement\n";
      //h.deleteHeap(c);
      DEBUG && cout<<"d.h Cust number " << c.custnum << endl;
      wait=time-c.arrvtime;
      DEBUG && cout<<"wait is "<<wait<<endl;
      wait_total+=wait;
      DEBUG && cout<<"wait total is "<<wait_total<<endl;
      time+=c.dur;
      DEBUG && cout<<"time is "<<time<<endl;
      counter++;
      DEBUG && cout<<"count is "<<counter<<endl;
    }//end if
    else{
      DEBUG && cout<<"Inside else\n";
      time++;
      h.insertHeap(temp);
      DEBUG && cout<<"Inserting "<<temp.custnum<<endl;
      DEBUG && cout<<"time is "<<time<<endl;
    }//end else
  }//end while

  average=(double) wait_total/counter;
  cout<<fixed<<showpoint<<setprecision(1);
  cout<<"Average wait time is "<<average<<endl;

}//end main()









