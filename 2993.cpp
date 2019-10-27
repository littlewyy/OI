#include<bits/stdc++.h>
using namespace std;
const int MAXN = 35 , MAXM = 2005 , MAXS = 2E5 + 5 , inf = 0x7fffffff;
int n,ori,g,all,type,cur = -1;
int Head[MAXN * 2],Color[MAXN * 2],Num[MAXN * 2][2];
int Cnt[MAXN][MAXN],Weight[MAXN * 2],Suf[MAXN * 2],X[MAXN * 2],Y[MAXN * 2],Cur[MAXN * 2];
int f[MAXS][MAXN];
char S[MAXN][MAXN];
struct wyy
{
	int to,next;
}Edge[MAXM];
void Add(int from,int to)
{
	Edge[++ cur].to = to;
	Edge[cur].next = Head[from];
	Head[from] = cur;
	
	Edge[++ cur].to = from;
	Edge[cur].next = Head[to];
	Head[to] = cur;
}
void Read()
{
	scanf("%d",&n);
	memset(Head,-1,sizeof(Head));
	for(int i = 1 ; i <= n ; i ++)	
	{
		scanf("%s",S[i] + 1);
		for(int j = 1 ; j <= n ; j ++)
		{
			if(S[i][j] == '1')
				Add(i,j + n) , ori ++;
		}
	}
}
void DFS(int x)
{
	Color[x] = g;
	for(int h = Head[x] ; h != -1 ; h = Edge[h].next)
	{
		int y = Edge[h].to;
		if(Color[y])	continue;
		DFS(y);
	}
}
void GetBlock()
{
	for(int i = 1 ; i <= 2 * n ; i ++)
	{
		if(!Color[i])
		{
			g ++;
			DFS(i);
		}
	}
	for(int i = 1 ; i <= n ; i ++)	Num[Color[i]][0] ++;
	for(int i = n + 1 ; i <= 2 * n ; i ++)	Num[Color[i]][1] ++;
	for(int i = 1 ; i <= g ; i ++)
	{
		int x = Num[i][0] , y = Num[i][1];
		Cnt[x][y] ++;//种类(x,y)的个数 
	}
	for(int i = 0 ; i <= n ; i ++)
	{
		for(int j = 0 ; j <= n ; j ++)
		{
			if(Cnt[i][j])//该组合数目大于0 
			{
				type ++;
				Weight[type] = Cnt[i][j] + 1;//进制位 
				X[type] = i , Y[type] = j;//(x,y)
			}
		}
	}
	Suf[type + 1] = 1; 
	for(int i = type ; i >= 1 ; i --)	Suf[i] = Suf[i + 1] * Weight[i];
	all = Suf[1];
}
void Split(int x,int &sumx,int &sumy)
{
	int temp = x;
	sumx = sumy = 0;
	for(int i = 1 ; i <= type ; i ++)
	{
		Cur[i] = x / Suf[i + 1];
		sumx += Cur[i] * X[i];//这个集合的x之和 
		sumy += Cur[i] * Y[i];//这个集合的y之和 
		x %= Suf[i + 1];
	}
}
void Dp()
{
	for(int s = 0 ; s < all ; s ++)
		for(int i = 0 ; i <= n ; i ++)	
			f[s][i] = inf;//f[s][i]：有i个x已在完全二分图中 
	f[0][0] = 0;
	for(int s = 0 ; s < all ; s ++)
	{
		int sumx,sumy;
		Split(s,sumx,sumy);
		for(int i = 0 ; i <= n ; i ++)
		{
			if(f[s][i] == inf)	continue;
			for(int j = 1 ; j <= type ; j ++)	
			{
				if(Cur[j] + 1 < Weight[j])//还有空位   
				{
					int onx = sumx - i , ony = sumy - i;//未匹配的x,y个数 
					int curx = X[j] , cury = Y[j] , ns = s + Suf[j + 1];//新状态  
					if(onx + curx == ony + cury)	f[ns][i + onx + curx] = min(f[ns][i + onx + curx],f[s][i] + (onx + curx) * (onx + curx));//组成大小为 onx + curx的新联通块   
					else	f[ns][i] = min(f[ns][i],f[s][i]);//没有组成新联通块，没有新代价 
				}
			}
		}
	}
	printf("%d\n",f[all - 1][n] - ori);
}
int main()
{
	freopen("2993.in","r",stdin);
	freopen("2993.out","w",stdout);
	Read();
	GetBlock();
	Dp();	
	return 0;
}
