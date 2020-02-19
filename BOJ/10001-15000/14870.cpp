#include <bits/stdc++.h>
int N;
long long sum;
struct data
{
	long long seg[1510]; int lazy[4096];
	data() { int i; for(i=0; i<1510; i++) seg[i]=0; for(i=0;i<4006;i++) lazy[i]=0;}
	void scan() {
		int i;
		for (i=1; i<=N; i++) scanf("%lld",&seg[i]);
	}
	long long val(int a) {
		long long ret=seg[a];
		a+=2047;
		while(a) ret+=(long long)lazy[a], a/=2;
		return ret;
	}
	void gadd(int a, int b, int val) {
		if (a>b) return ;
		if (a%2) lazy[a]+=val, a++;
		if (b%2==0) lazy[b]+=val, b--;
		gadd(a/2,b/2,val);
	}
	void add(int a, int b, int val) {
		a+=2047, b+=2047;
		gadd(a,b,val);
	}
};
data SegTree[1510];
int main()
{
	//freopen("input.txt", "r", stdin);
	scanf("%d", &N);
	int i, j, k, l, m;
	for (i=1; i<=N; i++) for(j=1; j<=N; j++) {scanf("%lld", &SegTree[i].seg[j]);}
	for (i=1; i<=N; i++) for (j=1; j<=N; j++) SegTree[i].seg[j]+=std::max(SegTree[i-1].seg[j],SegTree[i].seg[j-1]), sum+=SegTree[i].seg[j];
	printf("%lld\n", sum);
	char imsi; int x, y;
	for (i=0; i<N; i++) {
		scanf(" %c %d %d", &imsi, &x, &y);
		if (imsi=='U') {
			j=y+1;
			while(j<=N&&SegTree[x].val(j-1)>=SegTree[x-1].val(j))j++;
			sum+=(long long)(j-y);
			m=y;
			SegTree[x].add(y,j-1,1);
			for (k=x+1; k<=N&&m<j; k++) {
				while(m<j&&SegTree[k].val(m-1)>=SegTree[k-1].val(m))m++;
				while(m<j&&j<=N&&SegTree[k].val(j-1)>=SegTree[k-1].val(j))j++;
				SegTree[k].add(m,j-1,1);
				sum+=(long long)j-m;
			}
		}
		else if (imsi=='D') {
			j=y+1;
			while(j<=N&&SegTree[x].val(j-1)>SegTree[x-1].val(j))j++;
			sum-=(long long)(j-y);
			m=y;
			SegTree[x].add(y,j-1,-1);
			for (k=x+1; k<=N&&m<j; k++) {
				while(m<j&&SegTree[k].val(m-1)>=SegTree[k-1].val(m)+1)m++;
				while(m<j&&j<=N&&SegTree[k].val(j-1)>SegTree[k-1].val(j))j++;
				SegTree[k].add(m,j-1,-1);
				sum-=(long long)(j-m);
			}
		}
		printf("%lld\n", sum);
	}
	return 0;
}