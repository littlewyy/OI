#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 5;
int n;
int Id[MAXN];
struct q
{
	int id,end;
	bool operator < (const q &t)const
	{
		return end > t.end;
	}
};
priority_queue<q>Q;
struct wyy
{
	int l,r,id;
}A[MAXN];
int read()
{
	char ch = getchar();
	int w = 0;
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
	for(int i = 1 ; i <= n ; i ++)	A[i].l = read() , A[i].r = read() , A[i].id = i;
}
bool cmp(wyy x,wyy y)
{
	return x.l < y.l;
}
void Calc()
{
	sort(A + 1 , A + 1 + n , cmp);
	int ans = 0;
	for(int i = 1 ; i <= n ; i ++)
	{
		//printf("%d %d\n",A[i].l,A[i].r);
		if(!Q.empty() && Q.top().end < A[i].l)	
		{
			int temp = Q.top().id;
			Q.pop();
			Q.push((q){temp,A[i].r});
			Id[A[i].id] = temp;//重排后id变化。 
		}
		else
		{
			++ ans;
			Q.push((q){ans,A[i].r});
			Id[A[i].id] = ans;
		}
	}
	printf("%d\n",ans);
	for(int i = 1 ; i <= n ; i ++)	printf("%d\n",Id[i]);
}
int main()
{
	freopen("poj 3190.in","r",stdin);
	freopen("poj 3190.out","w",stdout);
	Read();
	Calc();
	return 0;
}
