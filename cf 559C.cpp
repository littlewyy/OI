#include<bits/stdc++.h>
using namespace std;
long long typedef LL;
const int MAXH = 1E5 + 5 , MAXN = 2005 , LIM = 2E5;
const LL mod = 1e9 + 7;
int h,w,n;
LL Fac[MAXH * 2],Inv[MAXH * 2];
LL f[MAXN];
struct wyy
{
	int x,y;
	bool operator < (const wyy &t)const
	{
		if(x == t.x)	return y < t.y;
		return x < t.x;
	}
}A[MAXN];
void Read()
{
	cin >> h >> w >> n;
	A[n + 1].x = h , A[n + 1].y = w;
	for(int i = 1 ; i <= n ; i ++)	cin >> A[i].x >> A[i].y;
	sort(A + 1 , A + n + 2);
}
LL getPow(LL x,LL times)
{
	LL ans = 1 , w = x;
	while(times)
	{
		if(times & 1)	ans = ans * w % mod;
		w = w * w % mod , times >>= 1;
	}
	return ans;
}
void Init()
{
	Fac[0] = 1;
	for(int i = 1 ; i <= LIM ; i ++)	Fac[i] = Fac[i - 1] * i % mod;
	Inv[LIM] = getPow(Fac[LIM],mod - 2);
	for(int i = LIM - 1 ; i >= 0 ; i --)	Inv[i] = Inv[i + 1] * (i + 1) % mod;
}
LL C(int x,int y)
{
	return Fac[x] * Inv[y] % mod * Inv[x - y] % mod;
}
void Dp()
{
	for(int i = 1 ; i <= n + 1 ; i ++)
	{
		int x = A[i].x , y = A[i].y;
		f[i] = C(x - 1 + y - 1 , x - 1);
		for(int j = 1 ; j < i ; j ++)
		{
			int lx = A[j].x , ly = A[j].y;
			if(ly > y)	continue;
			f[i] = (f[i] - f[j] * C(x - lx + y - ly , x - lx) % mod + mod) % mod;
		}
	}
	printf("%lld\n",f[n + 1]);
}
int main()
{
	freopen("cf 559C.in","r",stdin);
	freopen("cf 559C.out","w",stdout);
	Read();
	Init();
	Dp();
	return 0;
}
