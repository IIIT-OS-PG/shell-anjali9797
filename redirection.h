#ifndef dehra
#define dehra

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

int parsecommandd(char *cmd, char **com)
{
	int n=-1;
	int i=0;
	com[0]=strtok(cmd," ");
	while(com[i]!=NULL)
	{
		i++;
		com[i]=strtok(NULL," ");
	}
	return i;
}//separating the tokens of the file

int parsecommand2(char *cmd, char **com)
{
	int n=-1;
	int i=0;
	com[0]=strtok(cmd,">");
	while(com[i]!=NULL)
	{
		i++;
		com[i]=strtok(NULL,">");
	}
	return i;
}

int parsecommand3(char *cmd, char **com)
{
	int n=-1;
	int i=0;
	com[0]=strtok(cmd,">>");
	while(com[i]!=NULL)
	{
		i++;
		com[i]=strtok(NULL,">>");
	}
	return i;
}


void redirect1(char **com,int flag)//taking command for testing
{
	//to parse the command on the basis of > / >> close(1);//closing stdout
	//cout<<"first"<<endl;
	//cout<<com[1]<<endl;
	 int fd;

	//cout<<flag<<endl;
	if(flag==1)
	{ 
       //cout<<"ye na"<<endl;
      //cout<<"jk"<<endl;
		char *in[1024];
    int k=parsecommandd(com[1] , in);
    //cout<<in[0]<<endl;
       fd=open(in[0],O_CREAT | O_WRONLY, 0777);
       close(1);//closing stdout
       dup2(fd,1);
      char *inp[1024];
    k=parsecommandd(com[0] , inp);
    fflush(stdout);
    if(execvp(inp[0],inp)==-1)
    	printf("Command not executed!");
    fflush(stdout);
       close(fd);     

	}
	fflush(stdout);
	if (flag==2)
	{  char *in[1024];
    int k=parsecommandd(com[1] , in);
       close(1);//closing stdout
       int fd;
       fd=open(in[0],O_CREAT | O_APPEND | O_WRONLY, 0777);
       dup2(fd,0);
       //execvp(com[0],com[loc]);
       char *inp[1024];
    k=parsecommandd(com[0] , inp);
    fflush(stdout);
    if(execvp(inp[0],inp)==-1)
    	printf("Command not executed!");
    fflush(stdout);
       close(fd);     
	}


}

/*int main()
{
	char cmd[1024];
	char *params[12];
	char *argv1[12]={0};
	char *argv2[12]={0};
	int k,y,x;
	int f=1;
	while(1){
		printf("$");//prompt print call
		//read command
		scanf(" %[^\n]%*c",cmd);
		int j=parsecommand2(cmd,params);//separating by >
		redirect1(params,2);
	}

            
     // end while
    return 0;
	
}*/
#endif