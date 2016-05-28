#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
using namespace std;
int size=32,nop=0,pgs=10;   //size: size of each page
struct page		    //nop: no. of processes allocated.
{			    //pgs: no. of empty pages	
   int id;
   int pgno;
}mem[10];
class MemoryPag
{
   public: 
   void allocate(int id,int pgno)
   { 	int i=0;	
	while(mem[i].id!=0)
	{ 
	   i=random()%10;	//assigning a random empty frame
	}
	mem[i].id=id;
	mem[i].pgno=pgno+1;
	pgs--;
   
   }
   void deallocate(int id)
   {
	int i,flag=0;
	for(i=0;i<10;i++)
	{
	   if(mem[i].id==id)
	   {
		mem[i].id=0;
		flag=1;
		mem[i].pgno=0;
		pgs++;
		
	   }
	}
	if(flag==0)cout<<"Error:Process not found\n";
	else 
	{
	  nop--;
	}
   }
   void disp()
   {
	int i;	
	cout<<"No  ID  page no\n\n";		//Main memory display	
	for(i=0;i<10;i++)	
	{
	    cout<<i<<"   "<<mem[i].id<<"   "<<mem[i].pgno<<endl;
	}
	if(nop!=0)
	{
	   cout<<"Page Tables:\n";	
	   for(i=1;i<=10;i++)         //page table for process i.
	   {
	     
	  
	      int j;
	      for(j=0;j<10;j++)
	      {
		if(mem[j].id==i)
		{
		   cout<<"Page no:"<<mem[j].pgno<<" Frame no:"<<j<<" for process "<<i<<endl;
		}
	      
	      }
	      
	   }
   	   cout<<"\n";
	}	   
   }
	
};
int main()
{
   srand(time(NULL));
   
   MemoryPag m;
   cout<<"The initial memory:\n";
   m.disp();
   int c,s,id=1,nopg,frag;
   while(1)
   {
	cout<<"\nEnter choice:\n1>New process\n2>Deallocate\n3>Exit\n";
	cin>>c;
	switch(c)
	{
	   case 1: 
		cout<<"\nEnter size\n";		
		cin>>s;
		nopg=(s/size);       //calculating no. of pages required.                     
		if(nopg>pgs){cout<<"Error:Not enough memory";break;}   //checking for available memory
		else
		{
		if(s%size!=0)nopg++;      
		for(int i=0;i<nopg;i++)
		   m.allocate(id,i);
		frag=32-(s%size);
		if(frag!=32)cout<<frag<<" units of memory lost to internal fragmentation\n";   //checking for internal fragmentation
	  	nop++;
		m.disp();
		id++;		
		break;
		}
	   case 2:
		cout<<"Enter id of the process to deallocate\n";
		cin>>id;		
		m.deallocate(id);
		m.disp();
		break;
	   case 3:exit(0);
  	}
   }
}
