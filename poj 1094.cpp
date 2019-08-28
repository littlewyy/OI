//#include<bits/stdc++.h>
#include<cstring>
#include<iostream>
#include<cstdio>
using namespace std;
const int MAXN = 50 , MAXM = 2500;
int n,m;
int f[MAXN][MAXN],U[MAXM],V[MAXM];
int Q[MAXN],In[MAXN];
char S[5];
void Read()
{
	for(int i = 1 ; i <= m ; i ++)
	{
		scanf("%s",S + 1);
		int x = S[1] - 'A' + 1 , y = S[3] - 'A' + 1;
		U[i] = x , V[i] = y;
	}
}
void Floyd(int last)
{
	memset(f,0,sizeof(f));
	for(int i = 1 ; i <= n ; i ++)	f[i][i] = 1;
	for(int i = 1 ; i <= last ; i ++)	f[U[i]][V[i]] = 1;
	
	for(int k = 1 ; k <= n ; k ++)
		for(int i = 1 ; i <= n ; i ++)
			for(int j = 1 ; j <= n ; j ++)
				f[i][j] |= (f[i][k] & f[k][j]);
}
int Check()
{
	for(int i = 1 ; i <= n ; i ++)
	{
		for(int j = i + 1 ; j <= n ; j ++)
		{
			if(f[i][j] && f[j][i])	
				return 1;
		}
	}
	for(int i = 1 ; i <= n ; i ++)
	{
		for(int j = i + 1 ; j <= n ; j ++)
		{
			if(f[i][j] == 0 && f[j][i] == 0)	
			{
				printf("Sorted sequence cannot be determined.\n");
				return -1;
			}
		}
	}
	return 2;
}
bool CheckI()
{
	for(int i = 1 ; i <= n ; i ++)
	{
		for(int j = i + 1 ; j <= n ; j ++)
		{
			if(f[i][j] && f[j][i])	
				return true;
		}
	}
	return false;
}
bool CheckL()
{	
	for(int i = 1 ; i <= n ; i ++)
	{
		for(int j = i + 1 ; j <= n ; j ++)
		{
			if(f[i][j] == 0 && f[j][i] == 0)	
				return false;
		}
	}
	return true;
}
void CalcLegal(int t)
{
	printf("Sorted sequence determined after %d relations: ",t);
	memset(In,0,sizeof(In));
	for(int i = 1 ; i <= n ; i ++)
	{
		for(int j = 1 ; j <= n ; j ++)
		{
			if(i == j)	continue;
			if(f[j][i])	In[i] ++;
		}
	}
	int head = 1 , tail = 0;
	for(int i = 1 ; i <= n ; i ++)	if(!In[i])	Q[++ tail] = i;
	while(head <= tail)
	{
		int x = Q[head ++];
		char cur = x + 'A' - 1;
		putchar(cur);
		for(int i = 1 ; i <= n ; i ++)
		{
			if(x == i)	continue;
			if(f[x][i])	
			{
				f[x][i] = 0 , In[i] --;
				if(In[i] == 0)	Q[++ tail] = i;
			}
		}
	}
	printf(".\n");
}
int main()
{
	freopen("poj 1094.in","r",stdin);
	freopen("poj 1094.out","w",stdout);
	while(1)
	{
		scanf("%d%d",&n,&m);
		if(n == 0 && m == 0)	break;
		Read();
		for(int i = 1 ; i <= m + 1; i ++)
		{
			if(i == m + 1)	printf("Sorted sequence cannot be determined.\n");	
			Floyd(i);
			if(CheckI())	
			{
				printf("Inconsistency found after %d relations.\n",i);
				break;
			}
			else	
			{
				if(CheckL())	
				{
					CalcLegal(i);
					break;
				} 
			}
		}
	}
	return 0;
}
