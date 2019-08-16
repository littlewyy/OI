#include<bits/stdc++.h>
using namespace std;
long long typedef LL;
const int MAXN = 1E6 + 5;
const LL mod = 998244353;
LL n,m,diff,legal;
char S[MAXN];
LL getPow(int x,LL times)
{
	if(times == 0)	return 1 % mod;
	LL half = getPow(x,times >> 1);
	LL temp = half * half % mod;
	if(times & 1ll)	temp = temp * x % mod;
	return temp;
}
int main()
{
	freopen("2937.in","r",stdin);
	freopen("2937.out","w",stdout);
	scanf("%lld",&n);
	scanf("%s",S + 1);
	m = strlen(S + 1);
	diff = n - m;
	if(diff == 0)	legal = 1;//长度相同，无论如何不可 
	else	legal = (getPow(26,diff - 1) * 25 % mod * m % mod + getPow(26,diff)) % mod; 
	printf("%lld\n",(getPow(26,n) - legal + mod) % mod);
	return 0;
}
