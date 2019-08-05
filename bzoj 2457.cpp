#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int MAXN = 2E5 + 5;
int n;
struct wyy
{
	int num,id;
}A[MAXN];
void Read()
{
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i ++)	
	{
		scanf("%d",&A[i].num);
		A[i].id = i;
	}
}
bool cmp(wyy x,wyy y)
{
	if(x.num == y.num)	return x.id < y.id;
	return x.num < y.num;
}
void Calc()
{
	sort(A + 1 , A + 1 + n , cmp);

	A[n + 1].num = -1;
	
	int ans = 0,ok,std;
	for(int i = 1 ; i <= n ; )
	{
		int j = i;
		while(A[j].num == A[i].num)	j ++;
		if(i == 1)	
		{
			ans = 1;
			ok = 0 , std = A[1].id;
		}
		else
		{
			if(ok == 0)	//原本递减 
			{
				if(A[j - 1].id < std)	std = A[i].id;
				else	ok = 1 , std = A[j - 1].id;
			}
			else	  //原本递增 
			{
				if(A[i].id < std)	ans ++ , ok = 0 , std = A[i].id;
				else	std = A[j - 1].id;
			}
		}
		i = j;
	}
	printf("%d\n",ans);
}
int main()
{
	freopen("bzoj 2457.in","r",stdin);
	freopen("bzoj 2457.out","w",stdout);
	Read();
	Calc();
	return 0;
}
