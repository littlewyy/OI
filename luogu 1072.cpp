#include<bits/stdc++.h>
using namespace std;
long long typedef LL;
int T;
LL a0,a1,b0,b1;
LL Gcd(LL a,LL b)
{
	while(b)
	{
		LL c = a % b;
		a = b;
		b = c;
	}
	return a;
}
int main()
{
	freopen("luogu 1072.in","r",stdin);
	freopen("luogu 1072.out","w",stdout);
	scanf("%d",&T);
	while(T --)
	{
		scanf("%lld %lld %lld %lld",&a0,&a1,&b0,&b1);
		//xΪb1��������a1�ı���
		/*for(LL x = a1 ; (x * x) <= b1 ; x += a1)
		{
			if((b1 % x) != 0)	continue;//ö��С�ڵ��ڸ���b1������ 
			if(Gcd(x / a1 , p) == 1 && Gcd(b1 / x , q) == 1)	
			{
				ans ++;
				printf("%lld\n",x);
			}
			LL y = b1 / x;
			if((x * x) != b1 && ((b1 / x) % a1) == 0 && Gcd(b1 / x / a1 , a0 / a1) == 1 && Gcd(x , b1 / b0) == 1)
			{
				ans ++;
				printf("%lld\n",b1 / x);
			}			
		}*/
		//�����ص����⣺���Ӧö��b1��������ֻö�ٳ���С�ڸ���n���ڵġ�
		//ע��x��b1 / x��a1�Ƿ� ����û��ֱ����ϵ����ö������ʱ����ֱ��ö��a1�ı�����
		//����x��b1��������x����a1�ı�������b1 / x��a1�ı�������ͼ��������ˡ�
		//�Ժ��ܲ�Ͷ���Ȳ�Ͷ����Ͷ��֮ǰ������Ƿ�ȼۡ�
		LL ans = 0 , p = a0 / a1 , q = b1 / b0;
		for(LL x = 1 ; x * x <= b1 ; x ++)
		{
			if((b1 % x) != 0)	continue;//ö��С�ڵ��ڸ���b1������ 
			if(x % a1 == 0 && Gcd(x / a1 , p) == 1 && Gcd(b1 / x , q) == 1)	ans ++;
			LL y = b1 / x;
			if(x != y && y % a1 == 0 && Gcd(y / a1 , p) == 1 && Gcd(b1 / y , q) == 1)				
				ans ++;	
		}
		printf("%lld\n",ans);
	}	
	return 0;
}
