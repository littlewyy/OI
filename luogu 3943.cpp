#include<bits/stdc++.h>
using namespace std;
const int MAXN = 4E4 + 5 , MAXM = 70 , MAXK = 20 , MAXS = 1E6 + 5 , inf = 0x7ffffff;
int n,k,m,cur,num;
int A[MAXN],D[MAXN],Id[MAXN],L[MAXM],Dis[MAXN],Q[MAXN];
int Cost[MAXK][MAXK],Pos[MAXK];
int f[MAXS],Vis[MAXS];
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
	n = read() , k = read() , m = read();
	for(int i = 1 ; i <= k ; i ++)	
	{
		int pos = read();
		A[pos] = 1;
	}
	for(int i = 1 ; i <= n + 1 ; i ++)	
	{
		D[i] = A[i] ^ A[i - 1];
		if(D[i] == 1)	
		{
			Pos[++ num] = i;//第num个1的位置 
			Id[i] = num;
		}
	}
	for(int i = 1 ; i <= m ; i ++)	L[i] = read();
}
void BFS(int src)
{
	int head = 1 , tail = 1 , id = Id[src];
	memset(Dis,-1,sizeof(Dis));
	Q[head] = src , Dis[src] = 0;
	while(head <= tail)
	{
		int x = Q[head ++];
		
		/*for(int h = Head[x] ; h != -1 ; h = Edge[h].next)
		{
			int y = Edge[h].to;
			if(Dis[y] == -1)	//BFS写炸了。不能到达应置为-1，不能与距离为0相混淆。 
			{
				Dis[y] = Dis[x] + 1;
				Q[++ tail] = y;
				if(D[y] == 1)	Cost[id][Id[y]] = Dis[y];		
			}	
		}*/
		for(int i = 1 ; i <= m ; i ++)
		{
			int y = x - L[i];
			if(y >= 1)	
			{
				if(Dis[y] == -1)	//BFS写炸了。不能到达应置为-1，不能与距离为0相混淆。 
				{
					Dis[y] = Dis[x] + 1;
					Q[++ tail] = y;
					if(D[y] == 1)	Cost[id][Id[y]] = Dis[y];		
				}	
			}
			y = x + L[i];
			if(y <= n + 1)
			{
				if(Dis[y] == -1)	//BFS写炸了。不能到达应置为-1，不能与距离为0相混淆。 
				{
					Dis[y] = Dis[x] + 1;
					Q[++ tail] = y;
					if(D[y] == 1)	Cost[id][Id[y]] = Dis[y];		
				}	
			}
		}
	}
}
void getDis()
{
	/*memset(Head,-1,sizeof(Head));
	for(int i = 1 ; i <= n + 1 ; i ++)
	{
		for(int j = 1 ; j <= m ; j ++)
		{
			int x = i + L[j];
			if(x <= n + 1)	Add(i,x);//双向边 
		}
	}*/
	//此处没有必要先连边，BFS时直接访问即可。两倍大常数啊。 
	for(int i = 1 ; i <= num ; i ++)
		for(int j = 1 ; j <= num ; j ++)
			Cost[i][j] = inf;
	for(int i = 1 ; i <= num ; i ++)
	{
		int x = Pos[i];
		BFS(x);
	}
}
/*void Dp()
{
	//最终目标：f[s]
	f[0] = 0;
	for(int s = 1 ; s <= maxs ; s ++)	f[s] = inf;
	for(int s = 1 ; s <= maxs ; s ++)
	{
		for(int fir = 0 ; fir < num ; fir ++)
		{
			if((1 << fir) & s)
			{
				for(int next = fir + 1 ; next < num ; next ++)
				{
					if((1 << next) & s)//注意处理两者不能消去的情况，Cost = inf  
						f[s] = min(f[s],f[s ^ (1 << fir) ^ (1 << next)] + Cost[fir + 1][next + 1]);
				}
				break;
			}
		}
	} 
	printf("%d\n",f[maxs]);
}*/
int DFS(int s)
{
	if(Vis[s])	return f[s];
	Vis[s] = 1;
	int fir = 0;
	while(((1 << fir) & s) == 0)	fir ++;
	for(int next = fir + 1 ; next < num ; next ++)
	{
		if((1 << next) & s)	
			f[s] = min(f[s],DFS(s ^ (1 << fir) ^ (1 << next)) + Cost[fir + 1][next + 1]);
	}
	return f[s];
}
void Dp()
{
	int maxs = (1 << num) - 1;
	for(int s = 1 ; s <= maxs ; s ++)	f[s] = inf;
	f[0] = 0 , Vis[0] = 1;
	printf("%d\n",DFS(maxs));
}
int main()
{
	freopen("luogu 3943.in","r",stdin);
	freopen("luogu 3943.out","w",stdout);
	Read();
	getDis();
	//Dp();循环实现状压，速度较慢
	//状压使用记忆化搜索，会提高效率
	Dp();
	return 0;
}
