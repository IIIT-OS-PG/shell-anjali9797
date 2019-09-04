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
// for clearing terminal use cout<< "\033[2J\033[1;1H";

//declaring the prototype of the necessary functions

void initialise_shell();//to initialise the shell
//int readinput(char *str);//to readinput
//void printcurrent();//to print current directory
//void execommand(char **parsed);//to execute the command

void initialise_shell()
{
	cout<< "\033[2J\033[1;1H";
	cout<<"\n\n\n***************************************************";
	cout<<"\n\nWelcome to myshell\n";
	char *usname=getenv("USER");
	cout<<"\n\n User is:"<<usname<<"\n\n";
	sleep(1);	

}
int main()
{
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
			char temp[1024];
			scanf(" %[^\n]%*c",str);
			com[0]=strtok(str," ");
			while(com[i]!=NULL)
			{
				i++;
				com[i]=strtok(NULL," ");
			}
			execvp(com[0],com);
			}
			else
			{
				wait(0);
			}

		}
	
	return 0;
}

