#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
long long typedef LL;
const int MAXN = 1E5 + 5;
const LL inf = 1ll << 60;
int n,k;
int Pos[MAXN],Pre[MAXN],Next[MAXN],Vis[MAXN];
LL D[MAXN];
struct wyy
{
	int pos;
	LL val;
	bool operator <(const wyy &x)const
	{
		return val > x.val;
	}
};
priority_queue<wyy>Q;
void Read()
{
	scanf("%d%d",&n,&k);
	for(int i = 1 ; i <= n ; i ++)	
	{
		scanf("%d",&Pos[i]);
		if(i > 1)	D[i - 1] = Pos[i] - Pos[i - 1] , Q.push((wyy){i - 1 , D[i - 1]});
		Pre[i] = i - 1 , Next[i] = i + 1;
	}
	Pre[0] = 0 , Next[0] = 1;
	Pre[n] = n - 1 , Next[n] = n;
}
void Calc()
{
	LL ans = 0;
	D[0] = D[n] = inf;
	//why����Ȼ����n - 1Ϊ��Сֵ�������ѡn - 2��nһ�����š����ǻ�Ӱ�����
	//���������� ����˵2��ʱ�����岻���ˣ� 
	for(int i = 1 ; i <= k ; i ++)
	{
		wyy cur;
		while(!Q.empty())	
		{
			cur = Q.top();
			Q.pop();//����ɾȥ 
			if(!Vis[cur.pos])	break;
		}
		int pos = cur.pos;
		int pre = Pre[pos] , next = Next[pos];
		int ppre = Pre[pre] , nnext = Next[next];
		ans += D[pos];
		D[pos] = D[pre] + D[next] - D[pos] , Vis[pre] = Vis[next] = 1;//�ӳ�ɾ���� 
		Next[ppre] = pos , Pre[pos] = ppre , Next[pos] = nnext , Pre[nnext] = pos;
		Q.push((wyy){pos,D[pos]});
	}
	printf("%lld\n",ans);
}
int main()
{
	freopen("luogu 3620.in","r",stdin);
	freopen("luogu 3620.out","w",stdout);
	Read();
	Calc();
	return 0;
}
//�ö�Ҳ���Բ���ӳ�䣺�ӳ�ɾ�������Ȳ�ɾ������ȡ��Сֵʱ��ȡ�������ж��Ƿ��Ѿ���ɾ�� 
