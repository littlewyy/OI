#include<bits/stdc++.h>
using namespace std;
long long typedef LL;
const int MAXN = 1E4 + 5;
const LL inf = 1ll << 60;
int n,m,cur = -1;
int Head[MAXN],Road[MAXN],Vis[MAXN],Q[MAXN];
LL Dis[MAXN];
struct wyy
{
	int to,next,val;
}Edge[4 * MAXN];
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
	Edge[cur].next = Head[from];
	Edge[cur].val = val;
	Head[from] = cur;
}
void Read()
{
	n = read() , m = read();
	memset(Head,-1,sizeof(Head));
	for(int i = 1 ; i <= m ; i ++)
	{
		int type = read() , a = read() , b = read() , c;
		if(type != 3)	c = read();
		if(type == 1)	Add(b,a,c);
		else	
		{
			if(type == 2)	Add(a,b,-c);
			else	
			{
				Add(a,b,0);
				Add(b,a,0);
			}
		}
	}
	//0向所有点连边
	for(int i = 1 ; i <= n ; i ++)	Add(0,i,0); 
}
bool Spfa()
{
	//求最长路，判断是否存在正环。若存在正环，则返回false。
	for(int i = 1 ; i <= n ; i ++)	Dis[i] = -inf; 
	Dis[0] = 0;
	
	int head,tail;
	head = tail = 0;
	Q[head] = 0 , Vis[0] = 1 , Road[0] = 0;
	while(head <= tail)
	{
		int x = Q[head % MAXN];
		if(Road[x] > n)	return false;//正环 
		head ++ , Vis[x] = 0;
		for(int h = Head[x] ; h != -1 ; h = Edge[h].next)
		{
			int y = Edge[h].to , val = Edge[h].val;
			if(Dis[x] + val > Dis[y])
			{
				Dis[y] = Dis[x] + val;
				Road[y] = Road[x] + 1;
				if(!Vis[y])
				{
					tail ++;
					Q[tail % MAXN] = y , Vis[y] = 1;
				}
			}
		}
	}
	return true;
}
int main()
{
	freopen("luogu 1993.in","r",stdin);
	freopen("luogu 1993.out","w",stdout);
	Read();
	if(Spfa())	printf("Yes\n");
	else	printf("No\n");
	return 0;
}
