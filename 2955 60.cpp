#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3E6 + 5;
int n,m,cur = -1;
int Head[MAXN],Cnt[MAXN];
int t[MAXN];
set<int>S[MAXN];
long long ans = 0;
struct wyy
{
	int to,next;
}Edge[MAXN];
void Add(int x,int y)
{
	Edge[++ cur].to = y; 
	Edge[cur].next = Head[x];
	Head[x] = cur;
}
int read()
{
	char ch = getchar();
	int w = 0;
	while(ch < '0' || ch > '9')	ch = getchar();
	while(ch >= '0' && ch <= '9')
	{
		w = w * 10 + ch - '0';
		ch = getchar();
	}
	return w;
}
void Read()
{
	n = read() , m = read();
	memset(Head,-1,sizeof(Head));
	for(int i = 1 ; i <= n ; i ++)
	{
		int fa = read();
		Add(fa,i);
	}
	for(int i = 1 ; i <= m ; i ++)
	{
		int tar = read();
		Cnt[tar] ++;
	}
	for(int i = 0 ; i <= n ; i ++)	t[i] = i;//指向的set指针。 
}
void DFS(int x)
{
	S[t[x]].insert(-x);//变成负数，即可从大到小排列。 
	for(int h = Head[x] ; h != -1 ; h = Edge[h].next)
	{
		int y = Edge[h].to;
		DFS(y);
		if(S[t[y]].size() < S[t[x]].size())//子树合并上来。 
		{
			set<int>::iterator it;
			for(it = S[t[y]].begin() ; it != S[t[y]].end() ; it ++)	S[t[x]].insert(*it);
			while(S[t[y]].size() > 0)	S[t[y]].erase(S[t[y]].begin()); 
		}
		else
		{
			set<int>::iterator it;
			for(it = S[t[x]].begin(); it != S[t[x]].end() ; it ++)		S[t[y]].insert(*it);
			while(S[t[x]].size() > 0)	S[t[x]].erase(S[t[x]].begin());
			t[x] = t[y];
		}
	}
	int num = 0;
	set<int>::iterator it;
	for(it = S[t[x]].begin() ; it != S[t[x]].end() ; it ++)	
	{
		if(num == Cnt[x])	break;
		ans += (*it);	
		num ++;
		//S[t[x]].erase(*it);	
		//不能边做边删.	否则会出大问题。 
	}
	for(int i = 1 ; i <= num ; i ++)
		S[t[x]].erase(S[t[x]].begin());
}
int main()
{
	freopen("2955.in","r",stdin);
	freopen("2955.out","w",stdout);
	Read();
	DFS(0);
	printf("%lld\n",-ans);
	return 0;
}
