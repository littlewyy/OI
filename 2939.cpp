#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
using namespace std;
const int MAXB = 25 , MAXC = 105;
long long typedef LL;
int T,nbit,num;
int A[MAXB],C[MAXB];
bool f[MAXB][MAXB][MAXB];
pair<int,int>g[MAXC];
struct wyy{int d[3];}cur;
vector<wyy>t[5];
vector<int>Tmp;
LL n;
//��ⲻ��գ���������ڡ�
LL read()
{
	char ch = getchar();
	LL w = 0;
	while(ch < '0' || ch > '9')	ch = getchar();
	while(ch >= '0' && ch <= '9')	
	{
		w = w * 10 + ch - '0';
		ch = getchar();
	}
	return w;
} 
void Init()
{
	n = read() , nbit = 0;//�����գ��������±�һ�� 
	LL temp = n;
	while(temp)
	{
		int x = temp % 10;
		A[++ nbit] = x;
		temp /= 10;
	}
}
void dfsT(int c,int x,int lim)
{
	if(c == lim)//�����ﵽ 
	{
		wyy cur;
		for(int i = 0 ; i < lim ; i ++) cur.d[i] = Tmp[i];//�����ѹ��һ�� 
		t[lim].push_back(cur);//������ 
		return;
	}
	if(x > num)	return;
	Tmp.push_back(x);//Ŀǰ�ռ����ģ���¼��ϵ��±꣩ 
	dfsT(c + 1,x + 1,lim);
	Tmp.pop_back();
	dfsT(c,x + 1,lim);
}
void getCmb()
{
	for(int i = 0 ; i <= 9 ; i ++)
		for(int j = i ; j <= 9 ; j ++)
			g[++ num] = make_pair(i,j);
	for(int i = 1 ; i <= 3 ; i ++)
		dfsT(0,1,i); //�ռ�i������� 
}
void DFS(int c,int lim,int s,int had,int bit)
{
	if(c == lim)
	{
		int up = had / 10;
		had -= up * 10;
		if(had == A[bit])
		{
			for(int i = s ;  ; i = (i - 1) & s)
			{
				f[bit + 1][up][i] = 1;
				if(i == 0)	break;
			}
		}
		return;
	}
	if(s & (1 << c))	
	{
		pair<int,int> tmp = g[cur.d[c]];
		int x = tmp.first , y = tmp.second;
		DFS(c + 1,lim,s,had + x,bit);
		DFS(c + 1,lim,s,had + y,bit);
	}
	else	DFS(c + 1,lim,s,had,bit);
}
bool Dp(int lim)//��ϸ���Ϊlim 
{
	memset(f[1],0,sizeof(f[1]));
	
	int maxs = (1 << lim) - 1;	
	f[1][0][maxs] = 1;
	for(int i = 1 ; i <= nbit ; i ++)
	{
		int ok = 0;
		memset(f[i + 1],0,sizeof(f[i + 1]));
		
		for(int had = 0 ; had <= lim - 1 ; had ++)//��λ���λ = ���ĸ��� - 1 
		{
			for(int s = 0 ; s <= maxs ; s ++)
			{
				if(!f[i][had][s])	continue;	
				else	ok = 1;			
				DFS(0,lim,s,had,i);//��d[0]~d[lim-1] 
			}
		}
		if(!ok)	return false;//��֦ 
	}
	for(int s = 0 ; s <= maxs ; s ++)	
		if(f[nbit + 1][0][s])	
			return true;
	return false;
}
bool Judge(int lim)
{
	int size = t[lim].size();
	for(int i = 0 ; i < size ; i ++)
	{
		cur = t[lim][i];//ö��ѡ�����ϡ� cur.d[0] ~ cur.d[lim - 1]:ȡ��lim����ϡ� 
		if(Dp(lim))
			return true;
	}
	return false;
}
void Calc()
{
	int i;
	for(i = 1 ; i <= 3 ; i ++)
		if(Judge(i))	break;
	printf("%d\n",i);//3��������Ի��������� 
}
int main()
{
	freopen("2939.in","r",stdin);
	freopen("2939.out","w",stdout);
	getCmb();
	T = read();
	while(T --)
	{
		Init();
		Calc();
	}
	return 0;
}
//Ĥ��һ��˶�ܵĳ���д������Ȼ���Լ�д���ˡ��������Ҫ�����飻����ѡx�������Ӧ����Ԥ������������ 
