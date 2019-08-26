#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1E5 + 5;
int n,m;
multiset<int>S;
struct mach
{
	int x,y;
	bool operator < (const mach &t)const
	{
		return x > t.x;
	}
}Mach[MAXN];
struct task
{
	int a,b;
	bool operator < (const task &t)const
	{
		if(a == t.a)	return b > t.b;
		else	return a > t.a;
	}
}Task[MAXN];
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
	n = read() , m = read();
	for(int i = 1 ; i <= n ; i ++)	Mach[i].x = read() , Mach[i].y = read();
	for(int i = 1 ; i <= m ; i ++)	Task[i].a = read() , Task[i].b = read();
	sort(Mach + 1 , Mach + 1 + n);
	sort(Task + 1 , Task + 1 + m);
}
void Calc()
{
	int j = 1 , num = 0;
	long long ans = 0;
	for(int i = 1 ; i <= m ; i ++)
	{
		int a = Task[i].a , b = Task[i].b;
		while(Mach[j].x >= a)	
		{
			S.insert(Mach[j].y);
			j ++;
		}
		multiset<int>::iterator it = S.lower_bound(b);
		if(it != S.end())	
		{
			num ++;
			ans += 500 * a + 2 * b;
			S.erase(it);
		}
	}
	printf("%d %lld\n",num,ans);
}
int main()
{
	freopen("hdu 4864.in","r",stdin);
	freopen("hdu 4864.out","w",stdout);
	Read();
	Calc();
	return 0;
}
