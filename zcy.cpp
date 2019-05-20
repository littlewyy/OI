#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
using namespace std;
const int MAXN = 2E5 + 5 , inf = 0x7fffffff;
int n,cur = -1 , ans = 0;
int Q[MAXN],Head[MAXN],Vis[MAXN];
int f[MAXN][5];
struct wyy
{
	int to,next;
}Edge[2*MAXN];
void Add(int from,int to)
{
	Edge[++cur].to = to;
	Edge[cur].next = Head[from];
	Head[from] = cur;
	
	Edge[++cur].to = from;
	Edge[cur].next = Head[to];
	Head[to] = cur;
}
void Read()
{
	scanf("%d",&n);
	memset(Head,-1,sizeof(Head));
	for(int i = 1 ; i < n ; i ++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		Add(x,y);
	}
}
//BFSģ�����
void Calc()
{
	int head = 1 , tail = 1;
	Q[1] = 1 , Vis[1] = 1;
	while(head <= tail)
	{
		int x = Q[head++];
		bool ok = false;
		for(int h = Head[x] ; h != -1 ; h = Edge[h].next)
		{
			int y = Edge[h].to;
			if(Vis[y])	continue;
			ok = true , Q[++ tail] = y , Vis[y] = 1;//�洢���ڵ� 
		}
		if(!ok)	f[x][2] = inf;	else	f[x][2] = 0;
		f[x][0] = 0 , f[x][1] = 1;
	}
	memset(Vis,0,sizeof(Vis));
	for(int i = tail ; i >= 1 ; i --)
	{
		int x = Q[i] , ok = false , mina = inf;
		Vis[x] = 1;
		for(int h = Head[x] ; h != -1 ; h = Edge[h].next)
		{
			int y = Edge[h].to;
			if(!Vis[y])	continue;//��������x�Ĳ��Ƕ��� 
			f[x][0] += min(f[y][1] , f[y][2]);
			f[x][1] += min(min(f[y][0] , f[y][1]) , f[y][2]);
			f[x][2] += min(f[y][1],f[y][2]);
			if(f[y][1] < f[y][2])	ok = true;
			else	mina = min(mina , f[y][1] - f[y][2]);
		}
		if(mina != inf && ok==false)	f[x][2] += mina;
	}
	//ʵ���ϣ�����1��1�����ĵ㶼����Ҫ1�Ĵ���
	for(int h = Head[1] ; h != -1 ; h = Edge[h].next)
	{
		int x = Edge[h].to;
		ans += min(f[x][1] - 1 , min(f[x][0] , f[x][2]));
	} 
	printf("%d\n",ans);
} 
int main()
{
	freopen("zcy.in","r",stdin);
	freopen("zcy.out","w",stdout);
	Read();
	Calc();
	return 0;
}
