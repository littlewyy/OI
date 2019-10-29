#include<bits/stdc++.h>
using namespace std;
long long typedef LL;
const int MAXN = 5E4 + 5 , MAXL = 25;
const LL inf = 1ll << 60;
int n,m,dfn,tail,cur = -1;
int Head[MAXN],Num[MAXN],Q[MAXN];
int Jump[MAXN][MAXL],Dfn[MAXN],Rev[MAXN],L[MAXN],R[MAXN],Need[MAXN];
LL Diff[MAXN],Act[MAXN];
LL Dis[MAXN][MAXL];
bool Vis[MAXN],VisL[MAXN];
multiset<LL>S[MAXN],Ava;
struct wyy
{
	int to,next,val;
}Edge[MAXN * 2];
void Add(int from,int to,int val)
{
	Edge[++ cur].to = to;
	Edge[cur].next = Head[from];
	Edge[cur].val = val;
	Head[from] = cur;
	
	Edge[++ cur].to = from;
	Edge[cur].next = Head[to];
	Edge[cur].val = val;
	Head[to] = cur;
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
	n = read();
	memset(Head,-1,sizeof(Head));
	for(int i = 1 ; i < n ; i ++)	
	{
		int x = read() , y = read() , val = read();
		Add(x,y,val);
	}
	m = read();
	for(int i = 1 ; i <= m ; i ++)
	{
		int x = read();
		Num[x] ++;//军队个数 
	}
}
void DFS(int x,int fa)
{
	Dfn[x] = L[x] = R[x] = ++dfn;
	Rev[dfn] = x;
	if(fa == 1)	Vis[x] = 1 , Q[++ tail] = x;
	for(int i = 1 ; i <= 20 ; i ++)
	{
		int mid = Jump[x][i - 1];
		Jump[x][i] = Jump[mid][i - 1];
		Dis[x][i] = Dis[x][i - 1] + Dis[mid][i - 1];
	}
	int son = 0;
	for(int h = Head[x] ; h != -1 ; h = Edge[h].next)
	{
		int y = Edge[h].to , val = Edge[h].val;
		if(y == fa)	continue;
		son ++;
		Jump[y][0] = x , Dis[y][0] = val;
		DFS(y,x);		
		R[x] = max(R[x],R[y]);
	}
	if(son == 0)	VisL[x] = 1;
	//printf("%d %d %d %d\n",x,Dfn[x],L[x],R[x]);
}
bool Check(LL len)
{
	int need = 0;Ava.clear();//可用 
	for(int i = 1 ; i <= n ; i ++)	Diff[i] = 0;//被覆盖次数 
	for(int i = 1 ; i <= tail ; i ++)	S[Q[i]].clear();
	for(int i = 1 ; i <= n ; i ++)
	{
		LL temp = len , x = i;//temp:剩余的跳跃长度  x:当前跳到的点
		if(!Num[i])	continue; //当前点上没有军队 
		for(int j = 20 ; j >= 0 ; j --)
		{
			if(Jump[x][j] > 1 && Dis[x][j] <= temp)	
			{
				temp -= Dis[x][j];
				x = Jump[x][j];
			}
		} 
		if(Vis[x])//如果是儿子 
		{
			LL left = temp - Dis[x][0];
			if(left <= 0)	Diff[L[x]] += Num[i] , Diff[R[x] + 1] -= Num[i];//到不了根的留在原地  
			else
			{
				for(int j = 1 ; j <= Num[i] ; j ++)
					S[x].insert(left);//存储到达根之后的剩余长度 
			}			
		}
		else	Diff[L[x]] += Num[i] , Diff[R[x] + 1] -= Num[i];//不包含子树根 
	}
	//注意：基于dfn进行增减！而不是点 
	for(int i = 1 ; i <= n ; i ++)	Act[i] = Act[i - 1] + Diff[i];//该点被实际覆盖的次数 
	for(int i = 1 ; i <= tail ; i ++)
	{
		int ok = 0 , x = Q[i];
		for(int j = L[x] ; j <= R[x] ; j ++)//j为枚举的时间戳  
		{
			int node = Rev[j];
			if(VisL[node] == 1 && Act[j] == 0)//若该子树内的某叶子结点未被覆盖 
			{
				ok = 1;
				break;
			}
		}
		if(ok == 0)//x以下的叶子均已覆盖 
		{
			multiset<LL>::iterator it;//该点上全为自由点 
			for(it = S[x].begin() ; it != S[x].end() ; it ++)	Ava.insert(*it);
		}
		else
		{
			int size = S[x].size();//军队数目 
			if(size == 0)	Need[++ need] = x;//需要救援  
			else	
			{
				multiset<LL>::iterator it = S[x].begin();
				//S[x].erase(it);//注意：如果删除*it，是删去值等于*it的所有点！想清楚删值还是删单点 
				if((*it) <= Dis[x][0])	S[x].erase(it);//由it驻扎x 
				else	Need[++ need] = x;
				for(it = S[x].begin() ; it != S[x].end() ; it ++)	Ava.insert(*it);
			}
		}
	}
	for(int i = 1 ; i <= need ; i ++)
	{
		int x = Need[i];
		LL dis = Dis[x][0];
		multiset<LL>::iterator it = Ava.lower_bound(dis);
		if(it == Ava.end())	return false;
		else	Ava.erase(it);//删单点！用地址! 
	}
	return true;
}
void getMin()
{
	//printf("%lld\n",inf);
	LL lo = -1 , hi = inf;
	while(lo + 1 < hi)
	{
		LL mid = (lo + hi) >> 1;
		if(Check(mid))	hi = mid;
		else	lo = mid;
	}
	printf("%lld\n",hi);
}
void Calc()
{
	DFS(1,0);
	if(m < tail)	printf("-1\n");
	else	getMin();
}
int main()
{
	freopen("luogu 1084.in","r",stdin);
	freopen("luogu 1084.out","w",stdout);
	//clock_t x = clock();
	Read();
	Calc();
	//clock_t y = clock();
	//注意最后要删掉。可能编译不了。
	//printf("%lf\n",(double)(y - x) / CLOCKS_PER_SEC);
	return 0;
}
