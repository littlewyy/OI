#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int MAXN = 1E4 + 5;
int n,ans;
struct wyy
{
	int d,p;
}A[MAXN];
priority_queue<int>Q;
bool cmp(wyy x, wyy y)
{
	return x.d > y.d;//根据保质期从大到小排序 
}
void Init()
{
	while(!Q.empty())	Q.pop();
	ans=0;
}
void Read()
{
	for (int i = 1 ; i <= n ; i ++)	scanf("%d%d" , &A[i].p , &A[i].d);
}
void Print()
{
	sort(A + 1 , A + 1 + n , cmp);	
	int st = 1;
	for(int i = A[1].d ; i >= 1 ; i --)
	{
		while(st <= n && A[st].d >= i)	Q.push(A[st ++].p);
		if(!Q.empty())
		{
			ans += Q.top();
			Q.pop();
		}		
	}
	printf("%d\n",ans);
}
void Calc()
{
	Init();
	Read();
	Print();
}
int main()
{
	freopen("UVa 1316.in","r",stdin);
	freopen("UVa 1316.out","w",stdout);	
	while(scanf("%d",&n) != EOF)	Calc();
	return 0;
}
