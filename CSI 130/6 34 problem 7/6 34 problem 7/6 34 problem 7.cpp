//Madelaine Zinser
//CSI 130
//Homework 6-34 problem 7

#include <iostream>
using namespace std;

struct CartProd{
	int a;
	int b;
};

int main ()
{
	int a[50]={0}, b[101]={0};
	int z=1, i=0, x=-50, j=0, k=0, l=0;
	int uni[500]={0}, inter[150]={0};
	int prime[15]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};
	int b3[5]={-2,-1,0,1,2};
	CartProd cp[80];

	for(i=0; i<50; i++)
	{
		a[i]=z;
		z=z+1;
	}

	for(j=0; j<101; j++)
	{
		b[j]=x;
		x=x+1;
	}
	
	//intersection
	for (i=0; i<50; i++)
	{
		for(j=0; j<101; j++)
		{
			if(a[i]==b[j])
			{
				inter[k]=a[i];
				k++;
			}
		}
	}
	
	//union
	for(i=0; i<50; i++)
	{
		for(j=0; j<101; j++)
		{
			if(a[i]!=b[j])
			{
				uni[l]=a[i];
				i++;
				l++;
				uni[l]=b[j];
				l++;
			}
			else if(a[i]==b[j])
			{
				uni[l]=a[i];
				i++;
				l++;
			}
			
		}
	}
	
	k=0;
	for(i=0; i<15; i++)
	{
		for(j=0; j<5; j++)
		{
			cp[k].a=prime[i];
			cp[k].b=b3[j];
			k++;
		}
	}


	//print


	cout<<"A: {";
	for(i=0; i<50; i++)
	{
		cout<<a[i]<<",";
	}
	cout<<"}"<<endl;


	cout<<endl<<"B: {";
	for (j=0; j<101; j++)
	{
		cout<<b[j]<<",";
	}
	cout<<"}";



	cout<<endl<<endl<<"Intersection: {";
	for(i=0; i < k; i++)
	{
		cout<<inter[i]<<",";
	}
	cout<<"}"<<endl;



	cout<<endl<<"Union: {";
		for (j=0; j<101; j++)
	{
		cout<<b[j]<<",";
	}
	cout<<"}"<<endl<<endl<<endl;


	cout<<endl<<"Cartesian Product: {";
	for(i=0; i<k; i++)
	{
		cout<<"("<<cp[i].a<<","<<cp[i].b<<")";
		if (i<k-1)
			cout<<",";
		else 
			cout<<"}"<<endl;
	}

	return 0;
}
