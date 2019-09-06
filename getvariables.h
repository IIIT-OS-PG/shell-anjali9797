#ifndef dehjk
#define dehjk

#include <stdlib.h>   
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include<fcntl.h>
#include <sys/wait.h>
#include<bits/stdc++.h>
using namespace std;

// the info that we require to read from the anjali.rc
vector<string> details(5);// to store 1.user 2.path 3.home 4.hostname 5.PS1

void setinfo()
{
	//get the uid of the required user to set the required data accordingly
	uid_t userr=getuid();
	int f1;//file descriptors for the files to open and read
	f1=open("anjali.rc",O_RDONLY);
	//vector<string> details(5);// to store 1.user 2.path 3.home 4.hostname 5.PS1
	//we can read character by character so that it is easy for us to parse the file and extract the relevant information
	// 6th sept 00:56 3 days :(
	char buffer;
	//string temp="";
	int n=0;
	int i=0;
	char temp[1024];
	string line="";
	//reading the required data from anjali.rc
	while((n = read(f1,&buffer,1))>0)
	{
		if(buffer!='\n')
		{
          line+=buffer;
		}
		else
		{
			//implies the character is \n that is the line has been read
			//converting string to character array
			char cstr[line.size() + 1];
	line.copy(cstr, line.size() + 1);
	cstr[line.size()] = '\0';
	line="";//reinitialising line for reading the next data
	char *com[7];//we have seven values in total to be extracted
			int j=0;
	com[0]=strtok(cstr,":");
			while(com[j]!=NULL)
	{
		j++;
		com[j]=strtok(NULL,":");
	}
	//1 is username 2 is passwd 3 is userID 4 is groupID 5 is userid info 6 is home 7 is command shell
	if(userr==stoi(com[2]))
	{
		details[0]=com[0];//username
		cout<<details[0]<<"\n";
		
		details[2]=com[5];//home
		cout<<details[2]<<"\n";
        break;
	}//end if



		}//else
	}//while
	close(f1);//closing filedescriptor
	int fd2;//file descriptor to open the second file for reading
	fd2=open("/etc/hostname",O_RDONLY);
	while((n=read(fd2,&buffer,1))>0)
	{
		if(buffer!='\n')
		{
          line+=buffer;
		}
		else
		{
			details[3]=line;
			cout<<details[3]<<"\n";
			break;
		}
	}
	close(fd2);
	line="";//reinitializing line
	//file descriptor to open the third file for reading the path i.e the /etc/environment form there we will get the path
	int fd3;//file descriptor to open the third file
	fd3=open("/etc/environment",O_RDONLY);
	int flag=0;
	while((n=read(fd3,&buffer,1))>0)
	{
		if(buffer!='\n')
		{ if(buffer=='"'&&flag==0)
          {line+=buffer;
          	flag=1;
		}
		else if(buffer!='"')
			line+=buffer;
	}
		else
		{   int ll=line.length()-2;
			details[2]=line.substr(6);
			cout<<details[2]<<"\n";
			break;
		}
	}



	//



}


#endif
