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
#include "histt.h"//to store history
#include "redirection.h"//for redirection

using namespace std;
// for clearing terminal use cout<< "\033[2J\033[1;1H";

//declaring the prototype of the necessary functions

void initialise_shell();//to initialise the shell



void initialise_shell()
{   createurshellrc();
	setinfo();
	cout<< "\033[2J\033[1;1H";
	char *usname=getenv("USER");
	cout<<"\n\n User:"<<usname<<"\n\n";
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
			//for displaying prompt
			setinfo();
			uid_t us=getuid();
			cout<<details[0]<<"@"<<details[3];
			if(us==0)
				cout<<":~$";
			else
				cout<<":#$";

			
				
			char *com[1024];
			char str[1024];
			char strcopy[1024];
			char temp[1024];
			char *params[1024];
			scanf(" %[^\n]%*c",str);
			strcpy(strcopy,str);//making a copy of the string for pipes functionality
			//making a string copy of character array
		   
			if(str[0]=='h'&&str[1]=='i'&&str[2]=='s'&&str[3]=='t'&&str[4]=='o'&&str[5]=='r'&&str[6]=='y')
				{   display();
				}
				
				addrecord(str);
				


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
				if((strcmp(com[i],">>")==0))
					flag=11;
				if((strcmp(com[i],">")==0))
					flag=2;
				if(strcmp(com[i],"cd")==0)
					flag=3;
				if(strcmp(com[i],"$$")==0)
					flag=9;
				if(strcmp(com[i],"$?")==0)
					flag=10;
				

				i++;
				com[i]=strtok(NULL," ");

			}
			//for changing directory
           if(strcmp(com[0],"cd")==0)
			{
				if(com[1])
					chdir(com[1]);
				//continue;
			}
            //for executing pipes
			if(flag==1)
			{
				int j=parsecommand1(strcopy,params);//separating by pipes   
            if (execpipe(params) == 0) 
            	{  
                	break;
            		}
			}
			if (flag==11)//double redirection
			{
				int j=parsecommand2(strcopy,params);//separating by >>
		        redirect1(params,2);
			}
			if(flag==2)//single redirection
			{
				int j=parsecommand2(strcopy,params);//separating by >
		        redirect1(params,1);
			}
			if(flag==9)
			{
				cout<<getpid()<<endl;//printing the current process id
			}
			if(flag==10)
			{
				//to print the exit status code of the last command
				cout<<"0"<<endl;
			}

			


			if(flag==4)
			{ wait(0);
			execvp(com[0],com);
		     }
			}
			else
			{
				wait(0);
			}

		}
	
	return 0;
}

