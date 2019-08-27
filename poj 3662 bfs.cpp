#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005 , MAXM = 10005 , inf = 0x3f3f3f3f;
int n,m,k,cur;
int Head[MAXN],Dis[MAXN],Vis[MAXN];
deque<int>Q;
struct wyy
{
	int to,val,next;
}Edge[2 * MAXM];
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
void Add(int from,int to,int val)
{
	Edge[++ cur].to = to;
	Edge[cur].val = val;
	Edge[cur].next = Head[from];
	Head[from] = cur;
	
	Edge[++ cur].to = from;
	Edge[cur].val = val;
	Edge[cur].next = Head[to];
	Head[to] = cur;
}
void Read()
{
	n = read() , m = read() , k = read();
	memset(Head,-1,sizeof(Head)); 
	for(int i = 1 ; i <= m ; i ++)
	{
		int x = read() , y = read() , val = read();
		Add(x,y,val);
	}
}
int BFS(int mid)
{
	memset(Vis,0,sizeof(Vis));
	memset(Dis,0x3f,sizeof(Dis));
	Dis[1] = 0;Q.push_back(1);
	while(!Q.empty())
	{
		int x = Q.front();Q.pop_front();
		if(Vis[x])	continue;
		Vis[x] = 1;//已被扩展，即已确定。 
		for(int h = Head[x] ; h != -1 ; h = Edge[h].next)
		{
			int y = Edge[h].to , val = Edge[h].val;
			if(Vis[y]) continue;
			int tmp = (val > mid) ? 1 : 0;
			if(tmp)
			{
				if(Dis[x] + tmp < Dis[y])	
				{
					Dis[y] = Dis[x] + tmp;
					Q.push_back(y);
				}
			}
			else				
			{
				if(Dis[x] + tmp < Dis[y])
				{
					Dis[y] = Dis[x] + tmp;
					Q.push_front(y);
				}
			}
		}
	}
	return Dis[n];
}
void Calc()
{
	int lo,hi;
	lo = -1 , hi = 1e6;
	while(lo + 1 < hi)
	{
		int mid = (lo + hi) >> 1;
		if(BFS(mid) <= k)	hi = mid;
		else	lo = mid;
	}
	if(BFS(hi) <= k)	printf("%d\n",hi);
	else	printf("-1\n");
}
int main()
{
	freopen("poj 3662.in","r",stdin);
	freopen("poj 3662.out","w",stdout);
	Read();
	Calc();
	return 0;
}
