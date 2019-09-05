#ifndef deqqii
#define deqqii

#include <stdlib.h>   
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<bits/stdc++.h>
using namespace std;
int parsecommand(char *cmd, char **com)
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

int parsecommand1(char *cmd, char **com)
{
	int n=-1;
	int i=0;
	com[0]=strtok(cmd,"|");
	while(com[i]!=NULL)
	{
		i++;
		com[i]=strtok(NULL,"|");
	}
	return i;
}
int executecomm(char **p)
{
	pid_t pid=fork();//fork process
	if(pid==-1)
	{
		//error
		printf("error fork!!\n");
		return 1;
	}
	else if(pid==0)//u r in child
	{
		execvp(p[0],p);
		printf("UNknown Command \n");

	}
	else
	{
		int childstatus;
		waitpid(pid,&childstatus,0);
		return 1;
	}
}
int execpipe(char **pipess)
{   
	int p[2];
	int fdd=0;
	pid_t pid;
	while(*pipess !=NULL)
	{
		pipe(p);
		pid = fork();//creating a child process
		if(pid==-1)
	{
		printf("Error fork!\n");
		return 1;
	
	}
	else if(pid ==0)//child has been created
  {
    dup2(fdd,0);
    if(*(pipess + 1) !=NULL)
    	dup2(p[1],1);
    close(p[0]);
    close(p[1]);
    char *inp[1024];
    int k=parsecommand(pipess[0] , inp);
    /// to check for exception commands like redirection chdir etc
    if(execvp(inp[0],inp)==-1)
    	printf("Command not executed!");
    return 1;
   }
   else
   {
   	wait(NULL);
   	close(p[1]);
   	fdd=p[0];
   	pipess++;
   }	}

}
/*if(pid==-1)
	{
		printf("Error fork!\n");
		return 1;
	}
	if(pid==0)
	{
		close(fds[1]);
		dup2(fds[0],0);
		execvp(argv2[0],argv2);
		return 0;
     }
     else
     {
     	close(fds[0]);
     	dup2(fds[1],1);
     	execvp(argv1[0],argv1);
     	char *error=strerror(errno);
     	return 0;
     }*/
/*
int main()
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
		int j=parsecommand(cmd,params);
		//checking for pipes
		if (strcmp(params[0], "exit") == 0) break; //exit   
        for (k=0; k <j; k++) {     
            if (strcmp(params[k], "|") == 0) {    
                f = 0; y = k;      
              // printf("pipe found\n");
               break;
            }               
        }//loop for finding pipe
         if (f==0) {
            for (x=0; x<k; x++) {    
               argv1[x]=params[x];
            }     
            int z = 0;     
            for (x=k+1; x< j; x++) { 
                  
                argv2[z]=params[x];
                z++;
            }
             
            if (execpipe(argv1, argv2) == 0) 
            	{  
                	break;
            		}
            		}    
          else if (f==1) {     
             if (executecomm(params) == 0) break;
         }
    } // end while
    return 0;
	
}
*/
#endif