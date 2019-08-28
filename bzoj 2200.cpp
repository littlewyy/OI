#include<bits/stdc++.h>
using namespace std;
long long typedef LL;
const int MAXN = 3E4 + 5 , MAXM = 5e4 + 5;
const LL inf = 1ll << 60;
int n,m1,m2,cur,g,root;
int Head[MAXN],U[MAXM],V[MAXM],Val[MAXM],Vis[MAXN];
int Belong[MAXN],In[MAXN];
LL Dis[MAXN];
vector<int>Node[MAXN];
queue<int>Qw;
struct q
{
	int x;
	LL dis;
	bool operator < (const q &y)const
	{
		return dis > y.dis;
	}
};
priority_queue<q>Q;
struct wyy
{
	int to,next,val;
}Edge[4 * MAXM];
void Add(int from,int to,int val)
{
	Edge[++ cur].to = to;
	Edge[cur].val = val;
	Edge[cur].next = Head[from];
	Head[from] = cur;
}
int read()
{
	char ch = getchar();int w = 0 , f = 1;
	while(ch != '-' && (ch < '0' || ch > '9'))	ch = getchar();
	if(ch == '-')	f = -1 , ch = getchar();
	while(ch >= '0' && ch <= '9')	
	{
		w = w * 10 + ch - '0';
		ch = getchar();
	}
	return w * f;
}
void Read()
{
	n = read() , m1 = read() , m2 = read() , root = read();
	memset(Head,-1,sizeof(Head));
	for(int i = 1 ; i <= m1 ; i ++)
	{
		int x = read() , y = read() , val = read();
		Add(x,y,val);//单向边 
		Add(y,x,val);
	}
	for(int i = 1 ; i <= m2 ; i ++)
	{
		U[i] = read();
		V[i] = read();
		Val[i] = read();
	}
}
void DFS(int x,int bel)
{
	Belong[x] = bel;
	Node[bel].push_back(x);
	for(int h = Head[x] ; h != -1 ; h = Edge[h].next)
	{
		int y = Edge[h].to;
		if(!Belong[y])	DFS(y,bel);
	}
}
void getId()
{
	memset(Belong,0,sizeof(Belong));
	for(int i = 1 ; i <= n ; i ++)
	{
		if(!Belong[i])
			DFS(i,++ g);
	}
}
void reAdd()
{
	for(int i = 1 ; i <= m2 ; i ++)
	{
		Add(U[i],V[i],Val[i]);
		In[Belong[V[i]]] ++;//入度 
	}		
}
void getAns()
{
	for(int i = 1 ; i <= n ; i ++)	Dis[i] = inf , Vis[i] = 0;
	Dis[root] = 0;
	for(int i = 1 ; i <= g ; i ++)	
		if(In[i] == 0)
			Qw.push(i);
	while(!Qw.empty())
	{
		int gr = Qw.front();Qw.pop();
		int size = Node[gr].size();
		for(int i = 0 ; i < size ; i ++)
		{
			int x = Node[gr][i];
			Q.push((q){x,Dis[x]});
		}
		while(!Q.empty())
		{
			q cur = Q.top();Q.pop();
			int x = cur.x;
			if(Vis[x])	continue;Vis[x] = 1;
			LL dis = cur.dis;
			for(int h = Head[x] ; h != -1 ; h = Edge[h].next)
			{
				int y = Edge[h].to , val = Edge[h].val;
				if(dis != inf && dis + val < Dis[y])	
				{
					Dis[y] = dis + val;
					if(Belong[x] == Belong[y])	Q.push((q){y,Dis[y]});
				}					
				if(Belong[x] != Belong[y])	
				{
					In[Belong[y]] --;
					if(!In[Belong[y]])
						Qw.push(Belong[y]);
				}				
			}
		}
	}
	for(int i = 1 ; i <= n ; i ++)
	{
		if(Dis[i] == inf)	printf("NO PATH\n");
		else	printf("%lld\n",Dis[i]);
	}
}
int main()
{
	freopen("bzoj 2200.in","r",stdin);
	freopen("bzoj 2200.out","w",stdout);
	Read();
	getId();
	reAdd();
	getAns();
	return 0;
}
