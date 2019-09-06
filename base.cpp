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
#include "pipeexec.h"
#include "createownshell.h"
#include "getvariables.h"

using namespace std;
// for clearing terminal use cout<< "\033[2J\033[1;1H";

//declaring the prototype of the necessary functions

void initialise_shell();//to initialise the shell
//int readinput(char *str);//to readinput
//void printcurrent();//to print current directory
//void execommand(char **parsed);//to execute the command

void initialise_shell()
{   createurshellrc();
	setinfo();
	cout<< "\033[2J\033[1;1H";
	cout<<"\n\n\n***************************************************";
	cout<<"\n\nWelcome to myshell\n";
	char *usname=getenv("USER");
	cout<<"\n\n User is:"<<usname<<"\n\n";
	sleep(1);	

}
int main()
{   setinfo();
	int execFlag=0;
	initialise_shell();
	char buf[4096];
	pid_t id;
	int status;
	cout<<"%%";
	while(1)
	{
		id=fork();//creating child process
		if(id==0)//i.e the given process is a child process
		{
			int i=0;
			cout<<"Prompt$";
			char *com[1024];
			char str[1024];
			char strcopy[1024];
			char temp[1024];
			char *params[1024];
			scanf(" %[^\n]%*c",str);
			strcpy(strcopy,str);//making a copy of the string for pipes functionality

			com[0]=strtok(str," ");
			//in this loop we will also check for pipes , io redirection , cd
			//store flag =1 for pipe flag=2 for io redirection flag=3 for cd flag=4 for normal command execution
			int flag=4;
			while(com[i]!=NULL)
			{
				if(strcmp(com[i],"|")==0)
					{flag=1;
						//cout<<"pipe found!";
					}
				if((strcmp(com[i],">>")==0)||(strcmp(com[i],">")==0))
					flag=2;
				if(strcmp(com[i],"cd")==0)
					flag=3;
				i++;
				com[i]=strtok(NULL," ");

			}
			if(flag==1)
			{
				int j=parsecommand1(strcopy,params);//separating by pipes   
            if (execpipe(params) == 0) 
            	{  
                	break;
            		}
			}
			if (flag==3)
			{
				
			}

			if(flag==4)
			{ wait(0);
			execvp(com[0],com);}
			}
			else
			{
				wait(0);
			}

		}
	
	return 0;
}

