#ifndef histal
#define histal

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

void createhistory()
{
	int f1;
	f1=open("hist.txt", O_CREAT | O_WRONLY, 0777);
	close(f1);
}

void addrecord(char *p)
{
	int f1;
	f1=open("hist.txt", O_CREAT | O_APPEND | O_WRONLY, 0777);
	 write(f1,p,1024);
	 //char ch;
	 //ch='\n';
	 //write(f1,ch,1);
	 close(f1);
}
void display()
{
	int f1;
	int n;
	f1=open("hist.txt", O_RDONLY);
	char buffer;
	while((n = read(f1,&buffer,1))>0)
	{
		cout<<buffer;
	}
}
#endif

