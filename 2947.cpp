#include<bits/stdc++.h>
using namespace std;
long long typedef LL;
const int MAXN = 2E5 + 5;
const LL inf = 1ll << 60;
LL n,a,b,c,d;
LL A[MAXN],f[MAXN];
LL Tree[4 * MAXN];
int Stack[MAXN];
LL read()
{
	char ch = getchar();
	LL w = 0 , f = 1;
	while(ch != '-' && (ch < '0' || ch > '9'))	ch = getchar();
	if(ch == '-')	f = -1 , ch = getchar();
	while(ch >= '0' && ch <= '9')	
	{
		w = w * 10 + ch - '0';
		ch = getchar();
	}
	return w * f;
}
void Read()
{
	n = read();
	a = read() , b = read() , c = read() , d = read();
	for(int i = 1 ; i <= n ; i ++)	A[i] = read();
}
void Update(int x,int l,int r,int d,LL v)
{
	if(l == d && r == d)	
	{
		Tree[x] = v;
		return;
	}
	int mid = (l + r) >> 1 , ls = x << 1 , rs = ls | 1;
	if(d <= mid)	Update(ls,l,mid,d,v);
	else	Update(rs,mid + 1,r,d,v);
	Tree[x] = max(Tree[ls],Tree[rs]);
}
LL getMax(int x,int l,int r,int s,int t)
{
	if(s <= l && r <= t)	return Tree[x];
	int mid = (l + r) >> 1 , ls = x << 1 , rs = ls | 1;
	LL maxa = -inf;
	if(s <= mid)	maxa = max(maxa,getMax(ls,l,mid,s,t));
	if(t > mid)	maxa = max(maxa,getMax(rs,mid + 1,r,s,t));
	return maxa;
}
LL getW(LL x)
{
	LL cur = 0;
	cur += a * x * x * x;
	cur += b * x * x;
	cur += c * x;
	cur += d;
	return cur;
}
LL max(LL a,LL b)
{
	if(a > b)	return a;
	return b;
}
void Dp()
{
	for(int i = 1 ; i <= n ; i ++)	f[i] = -inf;
	for(int i = 1 ; i <= 4 * n ; i ++)	Tree[i] = -inf;
	
	int Stop = 0;
	for(int i = 1 ; i <= n ; i ++)
	{
		while(Stop && A[Stack[Stop]] >= A[i])	Stop --;
		
		if(Stop)
		{
			int pos = Stack[Stop];
			
			LL part = getMax(1,1,n,pos,i - 1) + getW(A[i]);
			f[i] = max(f[pos],part);
			
			Stack[++ Stop] = i;
		}
		else	
		{
			f[i] = getW(A[i]);
			if(i > 1)	f[i] += max(0,getMax(1,1,n,1,i - 1));
			Stack[++ Stop] = i;
		}
		Update(1,1,n,i,f[i]);//‘ÿ»Îœﬂ∂Œ ˜ 
	}
	printf("%lld\n",f[n]);
}
int main()
{
	freopen("2947.in","r",stdin);
	freopen("2947.out","w",stdout);
	Read();
	Dp();
	return 0;
}
