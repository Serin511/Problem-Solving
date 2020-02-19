#include <bits/stdc++.h>
#define fi first
#define se second
#define ryan bear
#define all(V) ((V).begin()), ((V).end())
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef long double ld;
typedef vector<int> vim;
typedef vector<ll> vlm;

struct dat {
	int x, y, ty; ll d;
	bool operator <(const dat &r)const{ return d>r.d; }
};

int xx[]={1, -1, 0, 0}, yy[]={0, 0, 1, -1};

int H, W, N;
ll A, B, C;
int D1[510][510]; ll D2[510][510][5];
int S[100010], T[100010];
pii stk[500010]; int tp;
int chk[510][510];

bool pos(int x, int y) { return (0<=x&&x<=H&&0<=y&&y<=W); }

priority_queue<dat> pq;
void push_pq(int x, int y, int ty, ll d) {
	if (!pos(x, y)) return ;
	if (D2[x][y][ty]>d) { D2[x][y][ty]=d; pq.push({x, y, ty, d}); }
}

int main() {
	scanf("%d %d %lld %lld %lld %d", &H, &W, &A, &B, &C, &N);
	for (int i=0; i<=H; i++) for (int j=0; j<W; j++) D1[i][j]=(1<<30);
	for (int i=1; i<=N; i++) {
		scanf("%d %d", &S[i], &T[i]);
		stk[tp++]={S[i], T[i]};
		D1[S[i]][T[i]]=0;
		chk[S[i]][T[i]]=1;
	}
	
	pii pl;
	for (int i=0; i<tp; i++) {
		pl=stk[i];
		for (int j=0; j<4; j++) if (pos(pl.fi+xx[j], pl.se+yy[j]) && !chk[pl.fi+xx[j]][pl.se+yy[j]]) {
			stk[tp++]={pl.fi+xx[j], pl.se+yy[j]};
			D1[pl.fi+xx[j]][pl.se+yy[j]]=D1[pl.fi][pl.se]+1;
			chk[pl.fi+xx[j]][pl.se+yy[j]]=1;
		}
	}
	
	for (int i=0; i<=H; i++) for (int j=0; j<=W; j++) for (int k=0; k<5; k++) D2[i][j][k]=(1ll<<60);
	push_pq(S[1], T[1], 4, 0);

	while (!pq.empty()) {
		auto dt=pq.top(); pq.pop();
		if (D2[dt.x][dt.y][dt.ty]!=dt.d) continue;
		if (dt.ty==4) for (int i=0; i<4; i++) push_pq(dt.x, dt.y, i, dt.d+B), push_pq(dt.x+xx[i], dt.y+yy[i], 4, dt.d+C);
		else push_pq(dt.x+xx[dt.ty], dt.y+yy[dt.ty], dt.ty, dt.d+A), push_pq(dt.x, dt.y, 4, dt.d+D1[dt.x][dt.y]*C);
	}
	printf("%lld\n", D2[S[N]][T[N]][4]);
	return 0;
}