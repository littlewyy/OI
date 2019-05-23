#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
using namespace std;
const int MAXN = 2E5 + 5 , inf = 0x7fffffff;
int n,node,cur = -1;
int Q[MAXN],Head[MAXN],Fa[MAXN],Dep[MAXN],Pos[MAXN],Vis[MAXN],Legal[MAXN];
struct wyy
{
	int to,next;
}Edge[2*MAXN];
struct heap
{
	int id,dep;
}Heap[MAXN];
void Add(int from,int to)
{
	Edge[++cur].to = to;
	Edge[cur].next = Head[from];
	Head[from] = cur;
	
	Edge[++cur].to = from;
	Edge[cur].next = Head[to];
	Head[to] = cur;
}
int read()
{
	char ch = getchar();
	int w = 0;
	while(ch < '0' || ch > '9')	ch = getchar();
	while(ch >= '0' && ch <= '9')	
	{
		w = w * 10 + (int)(ch - '0');
		ch = getchar();
	}
	return w;
}
void Read()
{
	n = read();
	memset(Head,-1,sizeof(Head));
	for(int i = 1 ; i < n ; i ++)
	{
		int x,y;
		x = read() , y = read();
		Add(x,y);
	}
}
void Up(int x)
{
	while(x > 1)
	{
		if(Heap[x].dep > Heap[x >> 1].dep)	
		{
			swap(Heap[x],Heap[x >> 1]);//����������Ϣ 
			Pos[Heap[x].id] = x , Pos[Heap[x >> 1].id] = x >> 1;//���¸�ֵӳ�� 
			x >>= 1; 
		}
		else	break;
	}
}
void Down(int x)
{
	int son = x << 1;
	while(son <= node)
	{
		if((son | 1) <= node && Heap[son | 1].dep > Heap[son].dep)	son = son | 1;
		if(Heap[x].dep < Heap[son].dep)	
		{
			swap(Heap[x],Heap[son]);//����������Ϣ 
			Pos[Heap[x].id] = x , Pos[Heap[son].id] = son;//���¸�ֵӳ�� 
			x = son , son = x << 1;
		}
		else	break;
	}
}
void Insert(int x,int dep)
{
	Heap[++ node].id = x , Heap[node].dep = dep , Pos[Heap[node].id] = node;
	Up(node);
}
void DFS(int x,int fa)
{
	Insert(x,Dep[x]);
	for(int h = Head[x] ; h != -1 ; h = Edge[h].next)
	{
		int y = Edge[h].to;
		if(y == fa)	continue;
		Fa[y] = x , Dep[y] = Dep[x] + 1;
		DFS(y,x);
	}
}
void Extract()
{
	swap(Heap[1],Heap[node --]),Pos[Heap[1].id] = 1;
	Down(1); 
}
/*void Remove(int x)
{
	int pos = Pos[x];
	swap(Heap[pos],Heap[node --]),Pos[Heap[pos].id] = pos;
	Up(pos),Down(pos);
}*/
void Calc()
{
	int ans = 0;
	memset(Vis,0,sizeof(Vis));//�Ƿ�ѡ����� 
	memset(Legal,0,sizeof(Legal));//�Ƿ��Ѿ��Ϸ��� 
	while(Heap[1].dep > 2)
	{
		int x = Heap[1].id;
		Extract();//ȥ���Ѷ��� 
		if(Legal[x])	continue;//�ѺϷ������ò����� 
		
		x = Fa[x];//���Ϸ���ѡ���� 
		if(Vis[x])	continue;//�����ѱ�ѡ����������ظ� 
		ans ++ , Vis[x] = Legal[x] = 1;//�����ѺϷ��ұ�ѡ�� 
		
		for(int h = Head[x] ; h != -1 ; h = Edge[h].next)
		{
			int y = Edge[h].to;
			Legal[y] = 1;//ʹ���ڵ�Ϸ��� 
		}
	}
	printf("%d\n",ans);
}
int main()
{
	freopen("zcy.in","r",stdin);
	freopen("zcy.out","w",stdout);
	Read();
	DFS(1,0);
	Calc();
	return 0;
}
