#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
//sb了，两个图，给cur/head/edge开两维即可。 
using namespace std;
long long typedef LL;
const int MAXN = 5E4 + 5 , MAXM = 1E5 + 5;
int n,m,t,Stop,dfn,g;
int Head[3][MAXN],T[2][MAXN],Stack[MAXN],Cur[3],Flag[MAXN];
int Dfn[MAXN],Low[MAXN],Degree[MAXN],Top[MAXN],Id[MAXN],Belong[MAXN];
LL W[2][MAXN],Pre[MAXN],Aft[MAXN],Maxa[4 * MAXN],PreMax[MAXN],AftMax[MAXN];
bool Instack[MAXN];
struct wyy
{
	int to,next;
}Edge[3][MAXM];
void Init()
{
	dfn = g = Stop = 0;
	memset(Head,-1,sizeof(Head));
	memset(T,0,sizeof(T));
	memset(W,0,sizeof(W));
	memset(Cur,-1,sizeof(Cur));
	memset(Dfn,0,sizeof(Dfn));
	memset(Instack,0,sizeof(Instack));
	memset(Flag,0,sizeof(Flag));
	memset(Maxa,0,sizeof(Maxa));//多测不清空，爆零见祖宗。具体：看代码清1次，对着上面的数组再检查。 
	memset(Degree,0,sizeof(Degree));
}
int read()
{
	char ch = getchar();int w = 0;
	while(ch < '0' || ch > '9')	ch = getchar();
	while(ch >= '0' && ch <= '9')	
	{
		w = w * 10 + (int)(ch - '0');
		ch = getchar();
	}
	return w;
}
void Add(int type,int x,int y)
{
	Edge[type][++ Cur[type]].to = y;
	Edge[type][Cur[type]].next = Head[type][x];
	Head[type][x] = Cur[type];
}
void Read()
{
	for(int i = 1 ; i <= n ; i ++)	W[0][i] = read();
	for(int i = 1 ; i <= n ; i ++)	T[0][i] = read();
	for(int i = 1 ; i <= m ; i ++)
	{
		int x,y;
		x = read() , y = read();
		Add(0,x,y);
	}
}
void Tarjan(int x)
{
	Dfn[x] = Low[x] = ++ dfn;
	Instack[x] = true , Stack[++ Stop] = x;
	//printf("%d ",x);
	
	for(int h = Head[0][x] ; h != -1 ; h = Edge[0][h].next)
	{
		int y = Edge[0][h].to;
		if(!Dfn[y])
		{
			Tarjan(y);
			Low[x] = min(Low[x],Low[y]);
		}
		else	if(Instack[y])	Low[x] = min(Low[x],Dfn[y]);
	}
	
	if(Dfn[x] == Low[x])
	{
		g ++;
		//缩点错了。不是Low[node]==Low[x]，而是node != x
		//重新研究缩点！  
		int node;
		do
		{
			node = Stack[Stop --]; 
			Instack[node] = false;
			Add(1,g,node);
			W[1][g] += W[0][node];
			if(T[0][node])	T[1][g] = 1;
			Belong[node] = g;
		}while(node != x);
	}
}
void Build()
{
	for(int i = 1 ; i <= n ; i ++)
		if(!Dfn[i])	
			Tarjan(i);
	
	for(int i = 1 ; i <= g ; i ++)
	{
		for(int h = Head[1][i] ; h != -1 ; h = Edge[1][h].next)
		{
			int x = Edge[1][h].to;
			for(int h = Head[0][x] ; h != -1 ; h = Edge[0][h].next)
			{
				int y = Edge[0][h].to;
				if(Belong[x] != Belong[y] && Flag[y] != i)
				{
					Flag[y] = i;
					Add(2,i,Belong[y]);
					Degree[Belong[y]] ++;
				}
			}
		}
	}
} 
void getTop()
{
	int head,tail;
	head = 1 , tail = 0;
	for(int i = 1 ; i <= g ; i ++)	if(!Degree[i])	Top[++ tail] = i , Id[i] = tail;
	while(head <= tail)
	{
		int x = Top[head ++];
		for(int h = Head[2][x] ; h != -1 ; h = Edge[2][h].next)
		{
			int y = Edge[2][h].to;
			Degree[y] --;
			if(!Degree[y])	Top[++ tail] = y , Id[y] = tail;
		}
	}
}
void getAftPre()
{
	for(int i = g ; i >= 1 ; i --)
	{
		int x = Top[i];
		if(T[1][x])	Aft[x] = W[1][x];	else	Aft[x] = -1;
		for(int h = Head[2][x] ; h != -1 ; h = Edge[2][h].next)
		{
			int y = Edge[2][h].to;
			if(Aft[y] != -1)	Aft[x] = max(Aft[x],Aft[y] + W[1][x]);
		}
	}
	for(int i = 1 ; i <= g ; i ++)	Pre[i] = W[1][i];
	for(int i = 1 ; i <= g ; i ++)	
	{
		int x = Top[i];
		for(int h = Head[2][x] ; h != -1 ; h = Edge[2][h].next)
		{
			int y = Edge[2][h].to;
			Pre[y] = max(Pre[y],Pre[x] + W[1][y]);
		}
	}
} 
void getMax()
{
	//PreMax[i]:拓扑序在i及以前的且可为终点的Pre最大值。 
	PreMax[0] = -1;
	for(int i = 1 ; i <= g ; i ++)
	{
		int x = Top[i];
		//注意限制条件： 终点必为可取点 
		//if(T[x][1])	PreMax[i] = max(PreMax[i - 1],Pre[x]);
		//前缀相关格式:先等于前1个，再跟当前答案比对。不然极易出错。 
		PreMax[i] = PreMax[i - 1];
		if(T[1][x])	 PreMax[i] = max(PreMax[i],Pre[x]);
	}
    //AftMax[i]:拓扑序在i及以后的Aft最大值。 
	AftMax[g + 1] = -1;
	for(int i = g ; i >= 1 ; i --)
	{
		int x = Top[i];
		AftMax[i] = max(AftMax[i + 1],Aft[x]);
	}
}
void PushDown(int x,int ls,int rs)
{
	Maxa[ls] = max(Maxa[ls],Maxa[x]);
	Maxa[rs] = max(Maxa[rs],Maxa[x]);
}
void Update(int x,int l,int r,int s,int t,LL val)
{
	if(s <= l && r <= t)	
	{
		Maxa[x] = max(Maxa[x],val);
		return;
	}
	int mid = (l + r) >> 1 , ls = x << 1 , rs = ls + 1;
	PushDown(x,ls,rs);
	if(s <= mid)	Update(ls,l,mid,s,t,val);
	if(t > mid)	Update(rs,mid + 1,r,s,t,val);
}
void getMatch()
{
	for(int i = 1 ; i <= g ; i ++)
	{
		for(int h = Head[2][i] ; h != -1 ; h = Edge[2][h].next)
		{
			int y = Edge[2][h].to;
			int st = Id[i] + 1 , end = Id[y] - 1;
			if(st <= end && Aft[y] != -1)	Update(1,1,g,st,end,Pre[i] + Aft[y]);
		}
	}
}
LL Query(int x,int l,int r,int d)
{
	if(l == d && r == d)	return Maxa[x];
	int mid = (l + r) >> 1 , ls = x << 1 , rs = ls + 1;
	PushDown(x,ls,rs);
	if(d <= mid)	return Query(ls,l,mid,d);
	else	return Query(rs,mid + 1,r,d);
}
void Q()
{
	LL mina = 1ll << 60;
	for(int i = 1 ; i <= n ; i ++)
	{
		int x = Belong[i];
		LL ans = -1;
		if(Aft[x] != -1)	ans = max(ans,Pre[x] + Aft[x] - 2 * W[1][x] + (W[1][x] - W[0][i]));	
		ans = max(ans,AftMax[Id[x] + 1]);//拓扑序在后 
		ans = max(ans,PreMax[Id[x] - 1]);	
		ans = max(ans,Query(1,1,g,Id[x]));//拓扑序的单点查询。
		mina = min(mina,ans);
	}
	printf("%lld\n",mina);
}
int main()
{
	freopen("map.in","r",stdin);
	//freopen("map wa.out","w",stdout);
	freopen("map.out","w",stdout); 
	scanf("%d",&t);
	while(t --)
	{
		scanf("%d%d",&n,&m);
		Init();
		Read();
		Build();
		getTop();
		getAftPre();
		getMatch();
		getMax();
		Q();
	}
	return 0;
}
