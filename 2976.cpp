#include<bits/stdc++.h>
using namespace std;
long long typedef LL;
const int MAXN = 5E5 + 5;
int n,p,q,root,cur = -1;
int Head[MAXN * 2],In[MAXN * 2];
LL f[MAXN * 2];
char S[MAXN];
priority_queue<int>Q[MAXN * 2];
struct wyy
{
	int to,next;
}Edge[2 * MAXN];
int read()
{
	char ch = getchar();int w = 0;
	while(ch < '0' || ch > '9')	ch = getchar();
	while(ch >= '0' && ch <= '9')	
	{
		w = w * 10 + ch - '0';
		ch = getchar();
	}
	return w;
}
void Add(int from,int to)
{
	Edge[++ cur].to = to;
	Edge[cur].next = Head[from];
	Head[from] = cur;
}
void Read()
{
	n = read() , p = read() , q = read();
	char ch = getchar();
	while(ch != '+' && ch != '*')	ch = getchar();
	for(int i = 1 ; i < n ; i ++)	S[i] = ch , ch = getchar();
	memset(Head,-1,sizeof(Head));
	for(int i = 1 ; i <= 2 * n - 2 ; i ++)
	{
		int u = read() , v = read();
		Add(u,v);
		In[v] ++; 
	}
}
void Solve(int x)
{
	int ext;
	if(S[x] == '+')	ext = p;else	ext = q;
	while(Q[x].size() > 1)//Ð¡¸ù¶Ñ 
	{
		int mina = - Q[x].top();Q[x].pop();
		int seca = - Q[x].top();Q[x].pop();
		int newn = seca + ext;
		Q[x].push(- newn);
	}
	f[x] = -Q[x].top();
}
void DFS(int x,int rt,int fa)
{
	if(x >= n)
	{
		Q[fa].push(0);
		return;
	}
	for(int h = Head[x] ; h != -1 ; h = Edge[h].next)
	{
		int y = Edge[h].to;
		if(y < n && S[y] == S[x])	DFS(y,rt,x);
		else	DFS(y,y,x);
	}
	if(x == rt)	
	{
		Solve(x);
		if(fa)	Q[fa].push(-f[x]);
	}
	else
	{
		while(!Q[x].empty())
		{
			int tmp = Q[x].top();
			Q[rt].push(tmp);
			Q[x].pop();
		}
	}
}
void Calc()
{
	for(int i = 1 ; i < n ; i ++)	if(In[i] == 0)	root = i;
	DFS(root,root,0);
	printf("%lld\n",f[root]);	
}
int main()
{
	freopen("2976.in","r",stdin);
	freopen("2976.out","w",stdout);
	Read();
	Calc();
	return 0;
}
