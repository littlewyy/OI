#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
using namespace std;
const int MAXN = 2E4 + 5,inf = 0x7fffffff;
int n,m;
int *x,*y;
int S[MAXN],Ori[MAXN],Cnt[MAXN];//注意cnt不能开字符集大小，而应开字符串长度。因为排名小于等于n 
int Tmp1[MAXN],Tmp2[MAXN],SA[MAXN],Height[MAXN];
void Read()
{
	for(int i = 1 ; i <= n ; i ++)	scanf("%d",&Ori[i]);
	for(int i = 1 ; i < n ; i ++)	S[i] = Ori[i] - Ori[i + 1] + 88;
}
void Sort()
{
	x = Tmp1 , y = Tmp2;
	n -- , m = 0;
	for(int i = 1 ; i <= n ; i ++)	x[i] = S[i] , m = max(m,x[i]);
	
	memset(Cnt,0,sizeof(Cnt));
	for(int i = 1 ; i <= n ; i ++)	Cnt[x[i]] ++;
	for(int i = 1 ; i <= m ; i ++)	Cnt[i] += Cnt[i - 1];
	for(int i = n ; i >= 1 ; i --)	SA[Cnt[x[i]] --] = i;
	
	for(int L = 1 ; (L << 1) <= n ; L <<= 1)
	{
		int p = 0;
		for(int i = n - L + 1 ; i <= n ; i ++)	y[++ p] = i;
		for(int i = 1 ; i <= n ; i ++)	if(SA[i] > L)	y[++ p] = SA[i] - L;
		
		memset(Cnt,0,sizeof(Cnt));
		for(int i = 1 ; i <= n ; i ++)	Cnt[x[y[i]]] ++;
		for(int i = 1 ; i <= m ; i ++)	Cnt[i] += Cnt[i - 1];
		for(int i = n ; i >= 1 ; i --)	SA[Cnt[x[y[i]]] --] = y[i];
		
		swap(x,y);
		x[SA[1]] = 1;
		for(int i = 2 ; i <= n ; i ++)
		{
			if(y[SA[i]] == y[SA[i - 1]] && y[SA[i] + L] == y[SA[i - 1] + L])	x[SA[i]] = x[SA[i - 1]];
			else	x[SA[i]] = x[SA[i - 1]] + 1;
		}
		m = x[SA[n]];
	}
}
void getHeight()
{
	for(int i = 1 , k = 0 ; i <= n ; i ++)
	{
		if(k > 0)	 k --;
		while(S[i + k] == S[SA[x[i] - 1] + k])	k ++;
		Height[x[i]] = k;
	}
	/*for(int i = 1 ; i <= n ; i ++)	printf("%d ",SA[i]);
	printf("\n");*/
//	for(int i = 1 ; i <= n ; i ++)	printf("%d ",Height[i]);
//	printf("\n");
}
bool Check(int mid)
{
	//最大SA - 最小SA 要达到  mid + 1 , mid 才可行。
	//mid表示差分数组的长度。 
	int mina = 0 , maxa = inf;
	for(int i = 2 ; i <= n ; i ++)
	{
		if(Height[i] < mid)	maxa = 0 , mina = inf;
		else
		{
			maxa = max(maxa,SA[i]);
			mina = min(mina,SA[i]);
			maxa = max(maxa,SA[i - 1]);
			mina = min(mina,SA[i - 1]);
			if(maxa - mina >= mid + 1)	return true;
		}
	}
	return false;
}
void Calc()
{
	int lo = 0 , hi = n / 2 + 1;
	while(lo + 1 < hi)
	{
		int mid = (lo + hi) >> 1;
		if(Check(mid))	lo = mid;
		else	hi = mid;
	} 
	if(lo + 1 >= 5)	printf("%d\n",lo + 1);
	else	printf("0\n");
}
int main()
{
	freopen("2923.in","r",stdin);
	freopen("2923.out","w",stdout);
	while(1)
	{
		scanf("%d",&n);
		if(n == 0)	break;
		Read();
		Sort();
		getHeight();
		Calc();
	}
	return 0;
}
