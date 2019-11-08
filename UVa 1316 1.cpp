#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int MAXN = 1E4+5;
int n,ans;
priority_queue<int>Q;//Ð¡¸ù¶Ñ£¬ÓÃ¸ºÊý´æ 
struct wyy
{
	int p,d;
}A[MAXN];
void Init()
{
	while(!Q.empty())	Q.pop();
	ans = 0;
}
void Read()
{
	for (int i = 1 ; i <= n ; i ++)	scanf("%d%d" , &A[i].p , &A[i].d);
}
bool cmp(wyy a , wyy b)
{
	return a.d < b.d;
}
void Print()
{
	sort(A + 1 , A + 1 + n , cmp);
	int instack = 0;
	for(int i = 1 ; i <= n; i++)
	{
		if(instack < A[i].d	)	Q.push(- A[i].p) , instack ++ , ans += A[i].p;
		else	
		{
			int last = - Q.top();
			if(last < A[i].p)
			{
				ans -= last , Q.pop();
				Q.push(- A[i].p) , ans += A[i].p ;
			}
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
