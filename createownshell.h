#ifndef deqqaa
#define deqqaa

#include<bits/stdc++.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<signal.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>
using namespace std; 

//creating a file like bashrc FOR storing the required data from /etc/passwd
void createurshellrc()
{
	int f1,f2;//file descriptors
	int n=0;
	char buff[1024];//buffer for storing data
	f1=open("/etc/passwd",O_RDONLY);//opening the file \etc\passwd in readonly mode to read the data from it
	f2=open("anjali.rc", O_CREAT | O_WRONLY, 0777);//open the file or if it is already there then write the data in it 0777 denotes the permission set
	 while((n=read(f1, buff, 1024))>0)
     {  
      
     if(write(f2, buff, n)!=n)
        {
           exit(3);
        }
     }
     close(f2);
     close(f1);

}
#endif
