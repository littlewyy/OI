#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3E5 + 5;
int n,m,q,k,cur = -1;
int Degree[MAXN],Tag[MAXN];
int ReHead[MAXN],Head[MAXN];
int Ori[MAXN],Given[MAXN];
struct wyy
{
	int to,next;
}Edge[2 * MAXN],ReEdge[2 * MAXN];
int read()
{
	char ch = getchar();int w = 0 , sym = 1;
	while(ch != '-' && (ch < '0' || ch > '9'))	ch = getchar();
	if(ch == '-')	sym = -1 , ch = getchar();
	while(ch >= '0' && ch <= '9')
	{
		w = w * 10 + ch - '0';
		ch = getchar();
	}
	return w * sym;
}
void Add(int from,int to)
{
	Edge[++ cur].to = to;
	Edge[cur].next = Head[from];
	Head[from] = cur;
	
	Edge[++ cur].to = from;
	Edge[cur].next = Head[to];
	Head[to] = cur;
}
void ReAdd(int from,int to)
{
	ReEdge[++ cur].to = to;
	ReEdge[cur].next = ReHead[from];
	ReHead[from] = cur;
}
void Read()
{
	n = read() , m = read() , q = read();
	memset(Head,-1,sizeof(Head));
	for(int i = 1 ; i <= m ; i ++)
	{
		int u = read() , v = read();
		Degree[u] ++ , Degree[v] ++;
		Add(u,v);
	}
}
void Rebuild()
{
	k = sqrt(2 * m), cur = -1;
	memset(ReHead,-1,sizeof(ReHead));
	for(int i = 1 ; i <= n ; i ++)
	{
		if(Degree[i] > k)
		{
			for(int h = Head[i] ; h != -1 ; h = Edge[h].next)
			{
				int to = Edge[h].to;
				ReAdd(to,i);
			}
		}
	}
}
void Calc()
{
	memset(Tag,-1,sizeof(Tag));
	while(q --)
	{
		int type = read() , x = read();
		if(!type)//—ØŒ °£ 
		{
			int curAns = Ori[x] + Given[x];
			for(int h = ReHead[x] ; h != -1 ; h = ReEdge[h].next)
			{
				int to = ReEdge[h].to;
				//‘§∑¿÷ÿ±ﬂ
				if(Tag[to] != q)
				{
					curAns += Ori[to];
					Tag[to] = q;
				} 				
			}
			printf("%d\n",curAns);
		}
		else
		{
			int y = read();
			Ori[x] += y;
			if(Degree[x] <= k)
			{				
				for(int h = Head[x] ; h != -1 ; h = Edge[h].next)
				{
					int to = Edge[h].to;
					if(Tag[to] != q)
					{
						Given[to] += y;
						Tag[to] = q;
					}
				}
			}
		}
	}
}
int main()
{
	freopen("2935.in","r",stdin);
	freopen("2935.out","w",stdout);
	Read();
	Rebuild();
	Calc();
	return 0;
}
