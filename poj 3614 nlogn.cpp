#include<bits/stdc++.h>//错了？回来再想想为什么 
using namespace std;
const int MAXN = 1E5 + 5;
int n,m;
int Node[MAXN];
struct wyy
{
	int l,r;
}A[MAXN];
struct wx
{
	int x,cnt;
}B[MAXN];
struct tmp
{
	int x,cnt;
	bool operator < (const tmp &y)const
	{
		return x < y.x;
	}
};
multiset<tmp>S;
//不要用set!用multiset!判断相同的原则是小于号的定义！小于号定义为第1维不同，那么只要第1维相同就不可以重复加入 
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
bool cmp(wyy x,wyy y)
{
	if(x.l == y.l)	return x.r < y.r;
	return x.l > y.l;
}
bool cmp2(wx x,wx y)
{
	return x.x > y.x; 
}
void Read()
{
	n = read() , m = read();
	for(int i = 1 ; i <= n ; i ++)	A[i].l = read() , A[i].r = read();
	for(int i = 1 ; i <= m ; i ++)	
	{
		int x = read() , cnt = read();
		B[i].x = x , B[i].cnt = cnt;
	}
	sort(A + 1 , A + 1 + n , cmp);//l从大到小，同l时r从小到大 
	sort(B + 1 , B + 1 + m , cmp2);//x从大到小 
//	for(int i = 1 ; i <= n ; i ++)	
//		printf("%d %d\n",A[i].l,A[i].r);
//	for(int i = 1 ; i <= m ; i ++)
//		printf("%d %d\n",B[i].x,B[i].cnt);
}
void Calc()
{
	int j = 0 , ans = 0;
	for(int i = 1 ; i <= n ; i ++)
	{
		while(j < m && B[j + 1].x >= A[i].l)
		{
			j ++;
			S.insert((tmp){B[j].x,B[j].cnt});
		}
		set<tmp>::iterator it = S.upper_bound((tmp){A[i].r,0});
		if(it != S.begin())
		{
			it --;
			tmp cur = *it;
			ans ++;
			cur.cnt --;
			S.erase(it);
			if(cur.cnt > 0)	S.insert(cur);
		}
	}
	printf("%d\n",ans);
}
int main()
{
	freopen("poj 3614.in","r",stdin);
	freopen("poj 3614.out","w",stdout);
	Read();
	Calc();
	return 0;
}
