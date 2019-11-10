#include<algorithm>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int MAXN = 1E4 + 5;
int n,ans;
priority_queue<int>Q;
struct wyy
{
	int d,lim,type;
}A[MAXN];
bool cmp(wyy x,wyy y)
{
	return x.d < y.d;
}
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
	n = read();
	for(int i = 1 ; i <= n ; i ++)
	{
		A[i].d = read();
		A[i].lim = read();
		A[i].type = 0;
	}
	int l = read() , p = read();
	for(int i = 1 ; i <= n ; i ++)	A[i].d = l - A[i].d;
	n ++ , A[n].d = 0 , A[n].type = 0 , A[n].lim = p;
	n ++ , A[n].d = l , A[n].type = 1 , A[n].lim = 0;
	sort(A + 1 , A + 1 + n , cmp);
//	for(int i = 1 ; i <= n ; i ++)
//		printf("%d %d %d\n",A[i].d,A[i].type,A[i].lim);
}
void Calc()
{
	int ans = 0 , left = 0;
	for(int i = 1 ; i <= n ; i ++)//能到达第i站 
	{
		if(A[i].type == 1)	break;
		Q.push(A[i].lim);
		if(left < A[i + 1].d - A[i].d)
		{
			while(!Q.empty())
			{
				int x = Q.top();Q.pop();
				left += x;
				if(i > 1)	ans ++;
				if(left >= A[i + 1].d - A[i].d)	break;
			}
			if(left < A[i + 1].d - A[i].d)
			{
				printf("-1\n");
				return;
			}
		}		
		left -= A[i + 1].d - A[i].d;
		//printf("%d\n",left);
	}
	printf("%d\n",ans);
}
int main()
{
	freopen("poj 2431.in","r",stdin);
	freopen("poj 2431.out","w",stdout);
	Read();
	Calc();
	return 0;
}
