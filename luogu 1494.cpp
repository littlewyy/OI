#include<bits/stdc++.h>
using namespace std;
long long typedef LL;
const int MAXN = 5E4 + 5;
int n,q,bl;
int A[MAXN];
LL Cnt[MAXN];
struct wyy
{
	int id,l,r;
	LL ans;
}Q[MAXN];
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
bool cmp(wyy a,wyy b)
{
	return a.l < b.l;
}
void Read()
{
	n = read() , q = read();
	for(int i = 1 ; i <= n ; i ++)	A[i] = read(); 
	for(int i = 1 ; i <= q ; i ++)
	{
		Q[i].id = i;
		Q[i].l = read() , Q[i].r = read();
	}
	sort(Q + 1 , Q + 1 + q , cmp);//按照左端点排序 
}
bool cmp2(wyy a,wyy b)
{
	return a.r < b.r;
}
void getBlock()
{
	bl = sqrt(n);
	for(int i = 1 , end = i ; i <= q ; i = end + 1) 
	{
		while(end + 1 <= q && Q[end + 1].l - Q[i].l <= bl)	end ++;
		sort(Q + i , Q + end + 1, cmp2);//sort函数写到尾指针下一个! 
				
		memset(Cnt,0,sizeof(Cnt));
		int l = Q[i]. l , r = Q[i].r;
		LL ans = 0;
		for(int j = l ; j <= r ; j ++)
			ans -= Cnt[A[j]] * (Cnt[A[j]] - 1) / 2 , 
			Cnt[A[j]] ++ , 
			ans += Cnt[A[j]] * (Cnt[A[j]] - 1) / 2;
		Q[i].ans = ans;
			
		for(int j = i + 1 ; j <= end ; j ++)
		{
			int nl = Q[j].l , nr = Q[j].r;
			int ll = Q[j - 1].l , lr = Q[j - 1].r;
			if(nl > ll)	
			{
				for(int k = ll ; k < nl ; k ++)
				{
					ans -= Cnt[A[k]] * (Cnt[A[k]] - 1) / 2 , 
					Cnt[A[k]] -- , 
					ans += Cnt[A[k]] * (Cnt[A[k]] - 1) / 2;
				}
			}
			else
			{
				for(int k = nl ; k < ll ; k ++)
				{
					ans -= Cnt[A[k]] * (Cnt[A[k]] - 1) / 2 , 
					Cnt[A[k]] ++ , 
					ans += Cnt[A[k]] * (Cnt[A[k]] - 1) / 2;
				}
			}
			for(int k = lr + 1 ; k <= nr ; k ++)	
			{
				ans -= Cnt[A[k]] * (Cnt[A[k]] - 1) / 2 , 
				Cnt[A[k]] ++;
				ans += Cnt[A[k]] * (Cnt[A[k]] - 1) / 2;
			}
			Q[j].ans = ans;
		}
	}
}
bool cmp3(wyy a,wyy b)
{
	return a.id < b.id;
}
LL getGcd(LL x,LL y)
{
	while(y)
	{
		LL c = x % y;
		x = y;
		y = c;
	}
	return x;
}
void Print()
{
	sort(Q + 1 , Q + 1 + q , cmp3);
	for(int i = 1 ; i <= q ; i ++)
	{
		//printf("%d ",Q[i].id);
		LL x = Q[i].ans , y = LL(Q[i].r - Q[i].l + 1) * (Q[i].r - Q[i].l) / 2;//注意强制转换。否则运算中爆炸 
		if(x == 0)	printf("0/1\n");
		else	
		{
			LL gcd = getGcd(x,y);
			x /= gcd , y /= gcd;
			printf("%lld/%lld\n",x,y);
		}
	}
}
int main()
{
	freopen("luogu 1494.in","r",stdin);
	freopen("luogu 1494.out","w",stdout);
	Read();
	getBlock();
	Print();
	return 0;
}
