#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int MAXN = 3E5 + 5;
int n,d,xnum,ynum,cur,ans;
int X[2][MAXN],Y[2][MAXN],Head[2 * MAXN],Ori[2][2 * MAXN];
int Tree[4 * 2 * MAXN],Delay[4 * 2 * MAXN];
struct wyy
{
	int l,r,add,next;
}Tag[2 * MAXN];
void Add(int pos,int l,int r,int add)
{
	Tag[++ cur].l = l , Tag[cur].r = r , Tag[cur].add = add;
	Tag[cur].next = Head[pos];
	Head[pos] = cur;
}
int read()
{
	char ch = getchar();int w = 0;
	while(ch < '0' || ch > '9')	ch = getchar();
	while(ch >='0' && ch <= '9')	
	{
		w = w * 10 + ch - '0';
		ch = getchar();
	}
	return w;
}
void Read()
{
    n = read() , d = read();
	for(int i = 1 ; i <= n ; i ++)
	{
		int x,y;
		x = read() , y = read();
		X[0][i] = x - y - d , X[1][i] = x - y + 1, Y[0][i] = x + y - d , Y[1][i] = x + y;
		Ori[0][i] = X[0][i], Ori[1][i] = Y[0][i];
		Ori[0][i + n] = X[1][i] , Ori[1][i + n] = Y[1][i];
	}
	sort(Ori[0] + 1 , Ori[0] + 1 + 2 * n);
	sort(Ori[1] + 1 , Ori[1] + 1 + 2 * n);
	xnum = unique(Ori[0] + 1 , Ori[0] + 1 + 2 * n) - (Ori[0] + 1);
	ynum = unique(Ori[1] + 1 , Ori[1] + 1 + 2 * n) - (Ori[1] + 1);
	
	memset(Head,-1,sizeof(Head));
	for(int i = 1 ; i <= n ; i ++)
	{
		int pos1 = lower_bound(Ori[0] + 1 , Ori[0] + 1 + xnum , X[0][i]) - Ori[0] , 
		    pos2 = lower_bound(Ori[0] + 1 , Ori[0] + 1 + xnum , X[1][i]) - Ori[0] , 
		    pos3 = lower_bound(Ori[1] + 1 , Ori[1] + 1 + ynum , Y[0][i]) - Ori[1] , 
			pos4 = lower_bound(Ori[1] + 1 , Ori[1] + 1 + ynum , Y[1][i]) - Ori[1] ;
		Add(pos1,pos3,pos4,1);
		Add(pos2,pos3,pos4,-1);
	}
}
void PushDown(int x,int lson,int rson)
{
	Tree[lson] += Delay[x] , Delay[lson] += Delay[x];
	Tree[rson] += Delay[x] , Delay[rson] += Delay[x];
	Delay[x] = 0;
}
void Update(int x,int l,int r,int s,int t,int add)
{
	if(s <= l && r <= t)	
	{
		Tree[x] += add;
		Delay[x] += add;//传给子孙后代 
		return;
	}
	int mid = (l + r) >> 1 , lson = x << 1 , rson = lson | 1;
	PushDown(x,lson,rson);
	if(s <= mid)	Update(lson,l,mid,s,t,add);
	if(t > mid)	Update(rson,mid + 1,r,s,t,add);
	Tree[x] = max(Tree[lson],Tree[rson]);
}
void Calc()
{
	for(int i = 1 ; i <= xnum ; i ++)
	{
		for(int h = Head[i] ; h != -1 ; h = Tag[h].next)
			Update(1,1,ynum,Tag[h].l,Tag[h].r,Tag[h].add);
		ans = max(ans,Tree[1]);
	}
	printf("%d\n",ans);
}
int main()
{
	freopen("2911.in","r",stdin);
	freopen("2911.out","w",stdout);
	Read();
	Calc();
	return 0;
}
