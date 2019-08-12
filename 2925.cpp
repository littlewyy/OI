#include<bits/stdc++.h>
using namespace std;
int q;
long long a,b;
int main()
{
	freopen("2925.in","r",stdin);
	freopen("2925.out","w",stdout);
	scanf("%d",&q);
	while(q --)
	{
		scanf("%lld%lld",&a,&b);
		printf("%lld\n",(b - a + 1) * (b - a) / 2);
	}
	return 0;
}
