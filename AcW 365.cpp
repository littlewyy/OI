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
	memset(Tag,0,sizeof(Tag));//ȫ��󷨺ã���Ȼ����©������ⲻ��ձ��������  
	memset(Color,0,sizeof(Color));
	//vectorҲҪ��գ�
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
void Tarjan(int x,int root)//ע��淶�������㱾����ǵ�˫ 
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
			//���۷������ֵ㣬�����˸���Low[x]
			Low[x] = min(Low[x],Low[y]); 
			if(Low[y] >= Dfn[x])//x�Ǹ�㡣 
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
		if(Tag[y] != id)	continue;//���Ǹõ�˫�ڵ� 
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
	//����ͼ���˫
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
