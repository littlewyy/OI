#include<bits/stdc++.h>
using namespace std;
long long typedef LL;
const int MAXN = 3E5 + 5;
int n,m,stamp,cur = -1;
int Head[MAXN],Dfn[MAXN],MaxD[MAXN],Legal[MAXN];
int Tree[2][MAXN];
LL ans;
struct tmp
{
	int root,x;
};
vector<tmp>Q[MAXN],Qr[MAXN];
vector<int>Ext[MAXN],Rev[MAXN];
struct wyy
{
	int to,next;
}Edge[2 * MAXN];
void Add(int from,int to)
{
	Edge[++ cur].to = to;
	Edge[cur].next = Head[from];
	Head[from] = cur;
	
	Edge[++ cur].to = from;
	Edge[cur].next = Head[to];
	Head[to] = cur;
}
void DFS(int x,int fa)
{
	Dfn[x] = ++ stamp , MaxD[x] = Dfn[x];
	for(int h = Head[x] ; h != -1 ; h = Edge[h].next)
	{
		int y = Edge[h].to;
		if(y == fa)	continue;
		DFS(y,x);
		MaxD[x] = max(MaxD[x],MaxD[y]);
	}
	Q[MaxD[x]].push_back((tmp){x,Dfn[x]});//在末尾处统计 
	Qr[Dfn[x]].push_back((tmp){x,MaxD[x]});//在开头处统计 
}
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
void Read()
{
	n = read() , m = read();
	memset(Head,-1,sizeof(Head));
	for(int i = 1 ; i < n ; i ++)
	{
		int x = read() , y = read();
		Add(x,y);
	}	
	DFS(1,0);
	for(int i = 1 ; i <= m ; i ++)
	{
		int x = read() , y = read();
		if(Dfn[x] > Dfn[y])	swap(x,y);
		x = Dfn[x] , y = Dfn[y]; 
		Ext[y].push_back(x);//记在结尾 
		Rev[x].push_back(y);//记在开头  
	}
}
void Update(int x,int type)
{
	for(;x <= n ; x += x & -x)	
		Tree[type][x] ++;
}
int Ask(int x,int type)
{
	int nans = 0;
	for(;x;x -= x & -x)
		nans += Tree[type][x];
	return nans;
}
void Calc()
{
	//以结尾为坐标建vector 
	for(int i = 1 ; i <= n ; i ++)
	{
		int size = Ext[i].size();
		for(int j = 0 ; j < size ; j ++)
		{
			int x = Ext[i][j];//x为开头，i为结尾 
			Update(i,0);//0为结尾 
			Update(x,1);//1为开头 
		}
		size = Q[i].size();
		for(int j = 0 ; j < size ; j ++)
		{
			tmp temp = Q[i][j];
			int x = temp.x , rt = temp.root;
			Legal[rt] += Ask(x - 1,1) - Ask(x - 1,0);
		}
	}
	//以开头为坐标建vector 
	memset(Tree,0,sizeof(Tree));
	for(int i = n ; i >= 1 ; i --)
	{
		int size = Rev[i].size();
		for(int j = 0 ; j < size ; j ++)
		{
			int x = Rev[i][j];
			//i为开头，x为结尾。0存结尾,1存开头 
			Update(x,0);//x为结尾 
			Update(i,1);
		}
		size = Qr[i].size();
		for(int j = 0 ; j < size ; j ++)
		{
			tmp temp = Qr[i][j];
			int x = temp.x , rt = temp.root;
			//结尾在外 - 开头在外 
			Legal[rt] += (Ask(n,0) - Ask(x,0)) - (Ask(n,1) - Ask(x,1));
		}
	}	
//	for(int i = 1 ; i <= n ; i ++)	printf("%d ",Dfn[i]);
//	printf("\n");
	for(int i = 2 ; i <= n ; i ++)//忽略i = 1，整个树没有断边 
	{
	//	printf("%d ",Legal[i]);
		if(Legal[i] == 0)	ans += m;
		else	if(Legal[i] == 1)	ans ++;
	}
	//printf("\n");
	printf("%lld\n",ans);
}
int main()
{
	freopen("2989.in","r",stdin);
	freopen("2989.out","w",stdout);
	Read();	
	Calc();
	//printf("%lld\n",ans);
	return 0;
}
