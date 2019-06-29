#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>// abs 要加库 cstdlib ， 否则CE! 
using namespace std;
long long typedef LL;
const int MAXN = 1E5 + 5;
int n,num1,lefNum,rigNum;//左边/右边 1的个数 
int A[2][MAXN];
int Num[2][MAXN][2];//第0/1个数组，前i个中0/1的个数 
int Pos[2][MAXN][2];//第0/1个数组，第i个0/1的位置。 
LL Sum[2][MAXN];//第0/1个数组，前i个中1的位置和 
LL ans = 1ll << 60;
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
	scanf("%d",&n);
	for(int i = n ; i >= 1 ; i --)	A[0][i] = read();
	for(int i = 1 ; i <= n ; i ++)	A[1][i] = read();
}
void Init()
{
	for(int i = 0 ; i < 2 ; i ++)
	{
		for(int j = 1 ; j <= n ; j ++)
		{
			Num[i][j][0] = Num[i][j - 1][0] , Num[i][j][1] = Num[i][j - 1][1];
			Num[i][j][A[i][j]] ++ , Pos[i][Num[i][j][A[i][j]]][A[i][j]] = j;
			
			Sum[i][j] = Sum[i][j - 1] + A[i][j] * j;
			if(A[i][j])	num1 ++;
		}
	}
	lefNum = Num[0][n][1] , rigNum = Num[1][n][1];
}
void Calc()
{
	int ok = (num1 - 1 - 2 * n) % 2;
	double k = (double)(num1 - 1 - 2 * n) / 2.0;
	for(int x = 0 ; x <= num1 ; x ++)//左边1的个数 
	{
		int y = num1 - x;
		
		if(ok == 1 && ((y - x) % 2) != 0)	continue;//若k为小数且y - x不为偶数，则一定不可行。存在负数，余数可能为负数！ 
		LL tar = (double)(y - x) * k; 
		LL a = LL(1 + x) * x / 2 , b = LL(n + n - x + 1) * x / 2;
		LL c = LL(1 + y) * y / 2 , d = LL(n + n - y + 1) * y / 2;
		
		if(a - d <= tar && tar <= b - c)	
		{
			int move = x - lefNum;
			LL step = 0 ,lefSum,rigSum;
			if(move >= 0)//从右往左移
			{
				int pos1 = Pos[0][move][0] , pos2 = Pos[1][move][1];
				step += LL(pos1 + pos1 - Num[0][pos1][1] + 1) * Num[0][pos1][1] / 2 - Sum[0][pos1];
				step += Sum[1][pos2] - LL(1 + move) * move / 2;
				step += LL(move) * move;
				lefSum = x * LL(n + 1) - (Sum[0][n] - Sum[0][pos1] + LL(1 + pos1) * pos1 / 2); 
				rigSum = Sum[1][n] - Sum[1][pos2];
				step += abs((lefSum - rigSum) - tar);
			}	
			else	
			{
				move = - move;
				//将move个从左边移到右边。
				int pos1 = Pos[0][move][1] , pos2 = Pos[1][move][0];
				step += Sum[0][pos1] - LL(1 + move) * move / 2;
				step += LL(pos2 + pos2 - Num[1][pos2][1] + 1) * Num[1][pos2][1] / 2 - Sum[1][pos2];
				step += LL(move) * move;
				lefSum = x * LL(n + 1) - (Sum[0][n] - Sum[0][pos1]);
				rigSum = LL(1 + pos2) * pos2 / 2 + Sum[1][n] - Sum[1][pos2];
				step += abs((lefSum - rigSum) - tar);
			}
			ans = min(ans,step);
		}
	}
	printf("%lld\n",ans);
}
int main()
{
	Read();
	Init();
	Calc();
	return 0;
}
