#include <iostream>
using namespace std;
int main ()
{
    int i, PC=0, op=21, opand, pow, car, j, mem, mm[256][8], ACC[5], MDR[8], MAR[8], IR[8], ADD;
    cout<<"0-HALT"<<endl;
    cout<<"1-LDIM"<<endl;
    cout<<"2-Store Direct"<<endl;
    cout<<"3-LDID"<<endl;
    cout<<"4-Store Indirect"<<endl;
    cout<<"5-Add"<<endl;
    cout<<"6-CMPE"<<endl;
    cout<<"7-JMPNE"<<endl;
    cin>>op;
    while (op!=0)
    {
          i=2;
          while (i>=0)
          {
                mm[PC][i]=op%2;
                op=op/2;
                i=i-1; 
          }
          cout<<"Enter a number between 0-15"<<endl;
          cin>>opand;
          i=7;
          while (i>=3)
          {
                mm[PC][i]=opand%2;
                opand=opand/2;
                i=i-1;
          }
          while (op==3 || op==4)
          {
                cout<<"Enter a Number 0-255"<<endl;
                cin>>ADD;
                if (i>=0)
                {
                         mm[opand][i]=ADD%2;
                         ADD=ADD/2;
                         i=i-1;
                }
          }
          PC=PC=1;
    
    cout<<"Enter 1 to print memory."<<endl;
    cin>>mem;
    PC=0;
    while (PC<255)
    {
          cout<<endl<<PC<<":"<<endl;
          i=0;
          while (i<8)
          {
                cout<<mm[PC][i];
                i=i+1;
          }
          PC=PC+1;
    }
    while (mm[PC][0]+mm[PC][2]!=0)
    {
          for (i=0;i<8;i=i+1)
          {
              MDR[i]=mm[PC][i];
          }
          for (i=0;i<8;i=i+1)
          {
              IR[i]=MDR[i];
          }
          i=2;
          pow=1;
          op=0;
          while (i>=0)
          {
                op=op+IR[i]*pow;
                pow=pow*2;
                i=i-1;
          }
    }
}
    if (op==0)
    {
          cout<<"Press any key to continue."<<endl;
    }    
    else if (op==1)
    {
         for (i=0;i<8;i=i+1)
         {
             MDR[i]=mm[ADD][i];
         }
         for (i=0;i<5;i=i+1)
         {
             ACC[i]=MDR[i+3];
         }
    }
    else if (op==2)
    {
         i=7;
         pow=1;
         ADD=0;
         while (i>=3)
         {
               ADD=ADD+IR[i]*pow;
               pow=pow*2;
               i=i-1;
         }
         i=0;
         while (i<5)
         {
               MDR[i+3]=ACC[i];
               i=i+1;
         }
         for (i=0;i<5;i=i+1)
         {
             mm[ADD][i]=MDR[i];
         }
    }
    else if (op==3)
    {
         i=7;
         pow=1;
         ADD=0;
         while (i>=3)
         {
               ADD=ADD+IR[i]*pow;
               pow=pow*2;
               i=i-1;
         }
         for (i=0;i<=8;i=i+1)
         {
             MAR[i]=mm[ADD][i];
         }
         i=7;
         pow=1;
         ADD=0;
         while (i>=0)
         {
               ADD=ADD+MAR[i]*pow;
               pow=pow*2;
               i=i-1;
         }
         for (i=0;i<8;i=i+1)
         {
             MDR[i]=mm[ADD][i];
         }
         for (i=0;i<5;i=i+1)
         {
             ACC[i]=MDR[i+3];
         }
    }
    else if (op==4)
    {
         i=7;
         ADD=0;
         pow=1;
         while (i>=3)
         {
               ADD=ADD+IR[i]*pow;
               pow=pow*2;
               i=i-1;
         }
         for (i=0; i<8; i=i+1)
         {
             MAR[i]=mm[ADD][i];
         }
         i=7;
         ADD=0;
         pow=1;
         while (i>=0)
         {
               ADD=ADD+MAR[i]*pow;
               pow=pow*2;
               i=i-1;
         }
         i=7;
         ADD=0;
         pow=1;
         while (i>=3)
         {
               ADD=ADD+IR[i]*pow;
               pow=pow*2;
               i=i-1;
         }
         for (i=0;i<5;i=i+1)
         {
             MDR[i+3]+ACC[i];
         }
         for (i=0;i<5;i=i+1)
         {
             mm[ADD][i]=MDR[i];
         }
    }
    else if (op==5)
    {
         car=0;
         for (i=4; i>0;i=i-1)
         {
             ACC[i]=IR[i+3]+ACC[i]+car;
             if (ACC[i]==0||ACC[i]==1)
             {
                  car=0;
             }
             else if (ACC[i]==2)
             {
                  ACC[i]=0;
                  car=1;
             }
             else if (ACC[i]==3)
             {
                  ACC[i]=1;
                  car=1;
             }
         }
    }
    else if (op==6)
    {
         j=0;
         for (i=0;i<=4;i=i+1)
         {
             ACC[i]=MDR[i+3];
             j=j+1;
         }
         for (i=0;i<=4;i=i+1)
         {
             ACC[i]=0;
         }
         if (j==5)
         {
             ACC[4]=1;
         }
    }
    else if (op==7)
    {
         j=0;
         i=0;
         while (i<=4)
         {
             if (ACC[i]==0)
             {
                j=j+1;
                i=i+1;
             }
         }
         if (j==5)
         {
             i=3;
             while (i<=7)
             {
                   ACC[i]=MDR[i];
                   i=i+1;        
             }
         }
         cout<<"Enter 1 to print memory."<<endl;
         cin>>mem;
         PC=0;
         while (PC<255)
         {
               cout<<endl<<PC<<":"<<endl;
               i=0;
               while(i<8)
				    {
					    cout<<mm[PC][i];
					    i=i+1;
			         }
				      PC=PC+1;
         }
         PC=PC+1;
    }
    
    
             
         
        
    
    
    
    
    
    
    
    
    return 0;
}
