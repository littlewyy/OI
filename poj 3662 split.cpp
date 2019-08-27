#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1E3 + 5 , MAXM = 1E4 + 5 , inf = 0x3f3f3f3f;
int n,m,k,cur;
int Head[MAXN];
int Dis[MAXN][MAXN];//Dis(i,j):到达i，使用j次免费，的最小花费。 
int Vis[MAXN][MAXN];
queue< pair<int,int> >Q;
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
void Spfa()
{
	memset(Dis,0x3f,sizeof(Dis));
	memset(Vis,0,sizeof(Vis));
	Dis[1][0] = 0 , Vis[1][0] = 1;
	Q.push(make_pair(1,0));
	while(!Q.empty())
	{
		pair<int,int> cur = Q.front();
		int x = cur.first , num = cur.second;
		Q.pop();Vis[x][num] = 0;//出队，标记已出。 
		for(int h = Head[x] ; h != -1 ; h = Edge[h].next)
		{
			int y = Edge[h].to , val = Edge[h].val;
			//使用免费服务，则花费不变。 
			if(num < k)
			{
				if(Dis[x][num] < Dis[y][num + 1])
				{
					Dis[y][num + 1] = Dis[x][num];
					if(!Vis[y][num + 1])	
					{
						Q.push(make_pair(y,num + 1));
						Vis[y][num + 1] = 1;
					}
				}
			}
			//不使用免费服务
			int temp = max(Dis[x][num],val);
			if(temp < Dis[y][num])
			{
				Dis[y][num] = temp;
				if(!Vis[y][num])	
				{
					Q.push(make_pair(y,num));
					Vis[y][num] = 1;
				}
			} 
		}
	}
	int ans = inf;
	for(int i = 0 ; i <= k ; i ++)	ans = min(ans,Dis[n][i]);
	if(ans != inf)	printf("%d\n",ans);
	else	printf("-1\n");
}
int main()
{
	freopen("poj 3662.in","r",stdin);
	freopen("poj 3662.out","w",stdout);
	Read();
	Spfa();
	return 0;
}
