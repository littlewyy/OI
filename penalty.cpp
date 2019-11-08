#include<bits/stdc++.h>
using namespace std;
long long typedef LL;
const int MAXN = 1E5 + 5;
int n,k,ans,cur = -1;
int Head[MAXN],Left[MAXN],Q[MAXN];
struct wyy
{
	int to,next;
}Edge[MAXN * 2];
void Add(int from,int to)
{
	Edge[++ cur].to = to;
	Edge[cur].next = Head[from];
	Head[from] = cur;
	
	Edge[++ cur].to = from;
	Edge[cur].next = Head[to];
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
	n = read() , k = read();
	memset(Head,-1,sizeof(Head));
	for(int i = 1 ; i < n ; i ++)
	{
		int x = read() , y = read();
		Add(x,y);
	}
}
void DFS(int x,int fa,int lim)
{
	Left[x] = 1;
	for(int h = Head[x] ; h != -1 ; h = Edge[h].next)
	{
		int y = Edge[h].to;
		if(y == fa)	continue;
		DFS(y,x,lim);		
	}
	int tail = 0;
	for(int h = Head[x] ; h != -1 ; h = Edge[h].next)
	{
		int y = Edge[h].to;
		if(y == fa)	continue;
		Q[++ tail] = Left[y];
	}
	sort(Q + 1 , Q + 1 + tail);
	int i = 0;
	while(i < tail && Left[x] + Q[i + 1] <= lim)
	{
		i ++;
		Left[x] += Q[i];
	}
	ans += tail - i;
}
int getNum(int lim)
{
	ans = 0;
	DFS(1,0,lim);
	return ans;
}
void Calc()
{
	//求解最小化最大联通块大小
	int lo = 0 , hi = n + 1;
	while(lo + 1 < hi)
	{
		int mid = (lo + hi) >> 1;
		if(getNum(mid) > k)	lo = mid;
		else	hi = mid;
	} 
	printf("%lld\n",LL(k + 1) * hi - n);
}
int main()
{
	freopen("penalty.in","r",stdin);
	freopen("penalty.out","w",stdout);
	Read();
	Calc();
	return 0;
}
