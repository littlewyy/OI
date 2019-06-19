#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int MAXN = 5E5 + 5;
int n,q;
int A[MAXN],Next[MAXN],Last[MAXN],Ans[MAXN],Maxa[MAXN * 4];
struct wyy
{
	int l,r,id;
}Q[MAXN];
int read()
{
	char ch = getchar();int w = 0;
	while(ch < '0' || ch > '9')	ch = getchar();
	while(ch >= '0' && ch <= '9')
	{
		w = w * 10 + (int)(ch - '0');
		ch = getchar();
	}
	return w;
}
void Read()
{
	n = read();
	for(int i = 1 ; i <= n ; i ++)	A[i] = read();
	q = read();
	for(int i = 1 ; i <= q ; i ++)	Q[i].l = read() , Q[i].r = read() , Q[i].id = i;
}
void getNext()
{
	for(int i = 1 ; i < MAXN ; i ++)	Last[i] = n + 1;//基于值域。 
	for(int i = n ; i >= 1 ; i --)
	{
		Next[i] = Last[A[i]];
		Last[A[i]] = i;
	}
	//for(int i = 1 ; i <= n ; i ++)	printf("%d ",Next[i]);
	//printf("\n");
}
bool cmp(wyy x,wyy y)
{
	return x.l < y.l;
}
void Update(int x,int l,int r,int d,int v)
{
	if(l == d && r == d)	
	{
		Maxa[x] = v;
		return;
	} 
	int mid = (l + r) >> 1 , ls = x << 1 , rs = ls | 1;
	if(d <= mid)	Update(ls,l,mid,d,v);
	else	Update(rs,mid + 1,r,d,v);
	Maxa[x] = max(Maxa[ls],Maxa[rs]);
}
int Query(int x,int l,int r,int s,int t)
{
	if(s <= l && r <= t)	return Maxa[x];
	int mid = (l + r) >> 1 , ls = x << 1 , rs = ls | 1 , ans = 0;
	if(s <= mid)	ans = max(ans,Query(ls,l,mid,s,t));
	if(t > mid)	ans = max(ans,Query(rs,mid + 1,r,s,t));
	return ans;
}
int getFir(int x,int l,int r,int s,int t,int std)
{
	if(l == r)	return l;
	int mid = (l + r) >> 1 , ls = x << 1 , rs = ls | 1 , ans = 0;
	if(s <= mid && Maxa[ls] > std)	//可能可行。
		ans = getFir(ls,l,mid,s,t,std);
	if(!ans && t > mid && Maxa[rs] > std)	
		ans = getFir(rs,mid + 1,r,s,t,std);
	return ans; 
}
void Calc()
{
	sort(Q + 1 , Q + 1 + q , cmp);
	//先处理首位
	memset(Last,0,sizeof(Last));
	for(int i = 1 ; i <= n ; i ++)
	{
		if(!Last[A[i]])	Update(1,1,n,i,Next[i]);
		Last[A[i]] = i;
	}
	Q[0].l = 1;
	for(int i = 1 ; i <= q ; i ++)
	{
		//printf("%d ",Q[i].id);
		for(int j = Q[i - 1].l ; j < Q[i].l ; j ++)
		{
			if(Next[j] >= Q[i].l && Next[j] <= n)
				Update(1,1,n,Next[j],Next[Next[j]]);
		}
		int maxa = Query(1,1,n,Q[i].l,Q[i].r);
		if(maxa <= Q[i].r)	Ans[Q[i].id] = 0;
		else	Ans[Q[i].id] = A[getFir(1,1,n,Q[i].l,Q[i].r,Q[i].r)];
		//任意1个：干脆求最左边1个，可以在求Maxa途中进行，也可以另起函数。 
	}
//	printf("\n");
	for(int i = 1 ; i <= q ; i ++)	printf("%d\n",Ans[i]);
}
int main()
{
	freopen("ycz.in","r",stdin);
	freopen("ycz.out","w",stdout);
	Read();
	getNext();
	Calc();
	return 0;
}
