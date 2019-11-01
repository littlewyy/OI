#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005 , MAXM = 2E6 + 5;
int n,notM,dfn,Stop,cur,g;
int Head[MAXN],Dfn[MAXN],Low[MAXN],Stack[MAXN],Color[MAXN],Tag[MAXN];
bool Vis[MAXN][MAXN],Save[MAXN],ok;
vector<int>Node[MAXN];
struct wyy
{
	int to,next;
}Edge[MAXM];
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
void Init()
{
	memset(Vis,0,sizeof(Vis));
	memset(Head,-1,sizeof(Head));
	memset(Dfn,0,sizeof(Dfn));
	memset(Save,0,sizeof(Save));
	memset(Tag,0,sizeof(Tag));//全清大法好！不然容易漏掉！多测不清空爆零见祖宗  
	memset(Color,0,sizeof(Color));
	//vector也要清空！
	for(int i = 1 ; i <= n ; i ++)	Node[i].clear(); 
	cur = -1 , g = 0 , Stop = 0 , dfn = 0;
}
void Read()
{
	for(int i = 1 ; i <= notM ; i ++)
	{
		int x = read() , y = read();
		Vis[x][y] = Vis[y][x] = 1;
	}
	for(int i = 1 ; i <= n ; i ++)
	{
		for(int j = 1 ; j <= n ; j ++)
		{
			if(i == j)	continue;
			if(!Vis[i][j])	Add(i,j);
		}
	}
}
void Tarjan(int x,int root)//注意规范：孤立点本身就是点双 
{
	Dfn[x] = Low[x] = ++ dfn;
	Stack[++ Stop] = x;
	if(x == root && Head[x] == -1)	
	{
		g ++;
		Node[g].push_back(x);
	}
	for(int h = Head[x] ; h != -1 ; h = Edge[h].next)
	{
		int y = Edge[h].to;
		if(!Dfn[y])	
		{
			Tarjan(y,root);
			//不论访问哪种点，别忘了更新Low[x]
			Low[x] = min(Low[x],Low[y]); 
			if(Low[y] >= Dfn[x])//x是割点。 
			{
				g ++;
				while(1)
				{
					int node = Stack[Stop --];
					Node[g].push_back(node);
					if(node == y)	break;
				}
				Node[g].push_back(x);
			} 
		}
		else	Low[x] = min(Low[x],Dfn[y]);
	}
}
void DFS(int x,int id)
{
	if(ok)	return;
	for(int h = Head[x] ; h != -1 ; h = Edge[h].next)
	{
		int y = Edge[h].to;
		if(Tag[y] != id)	continue;//不是该点双内点 
		if(Color[y] == -1)	Color[y] = Color[x] ^ 1 , DFS(y,id);
		else	
		{
			if(Color[y] == Color[x])
			{
				ok = 1;
				return;
			}
		}	
	}
}
void Calc()
{
	//无向图求点双
	for(int i = 1 ; i <= n ; i ++)	
		if(!Dfn[i])
			Tarjan(i,i); 
	for(int i = 1 ; i <= g ; i ++)
	{
		int size = Node[i].size();
		for(int j = 0 ; j < size ; j ++)	Tag[Node[i][j]] = i , Color[Node[i][j]] = -1;
		Color[Node[i][0]] = 0 , ok = 0;
		DFS(Node[i][0],i);
		if(ok)	
		{
			for(int j = 0 ; j < size ; j ++)	
				Save[Node[i][j]] = 1;
		}
	}
	int ans = 0;
	for(int i = 1 ; i <= n ; i ++)
	{
		if(!Save[i])
			ans ++;
	}
	printf("%d\n",ans);
}
int main()
{
	freopen("AcW 365.in","r",stdin);
	freopen("AcW 365.out","w",stdout);
	while(1)
	{
		n = read() , notM = read();
		if(n == 0 && notM == 0)	break;
		Init();
		Read();
		Calc();
	}
	return 0;
}
