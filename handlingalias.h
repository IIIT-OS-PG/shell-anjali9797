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

map<string,string> a;

void handle_alias(string t)
{
	t=t.substr(6);
	char ch=t[0];
	string lhs="";//for left part of alias
	string rhs="";//for right part of alias
	int i=0;
	while(ch!='=')
	{
		lhs+=ch;
		i++;
		ch=t[i];
	}
	//now dealing with the rhs of alias
	i++;i++;
	ch=t[i];
	int j=t.length()-2;

	while(i<j)
	{
		rhs+=ch;
		i++;
		ch=t[i];
	}
	a[lhs]=rhs;//value inserted in map

}
/*int main()
{

	handle_alias("alias ll='ls -l'.");
	handle_alias("alias lk='ls -a'.");
	handle_alias("alias lp='ls -oooo'.");
	handle_alias("alias ljkl='ls -l | grep .txt'.");
	map<string,string>::iterator itr;
	for(itr=a.begin();itr!=a.end();itr++)
	{
		cout << '\t' << itr->first 
             << '\t' << itr->second << '\n'; 
	}


	return 0;
}*/