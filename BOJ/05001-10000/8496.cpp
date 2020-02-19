#include <bits/stdc++.h>
#define fi first
#define se second
#define em emplace
#define eb emplace_back
#define sq(X) ((X)*(X))
#define all(V) (V).begin(), (V).end()
#define unq(V) (V).erase(unique(all(V)), (V).end())
using namespace std;
typedef long long ll;
typedef vector<ll> vlm;
typedef vector<int> vim;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

int N, M, Q, ans[100010], chk[100010], in[100010], cnt; vim V[100010];
vim adj[100010], rev[100010], use;

struct edge { int u, v, id; };
vector<edge> line;

int par[100010];
int get(int x) { return par[x]?(par[x]=get(par[x])):x; }
void Union(int x, int y) {
	x=get(x); y=get(y);
	if (x==y) return ;
	if (!(in[x]&&in[y])) cnt--;
	par[y]=x; in[x]+=in[y];
}

vim stk; int scc[100010]; int tp;
void dfs1(int now) {
	chk[now]=1;
	for (auto &i:adj[now]) if (!chk[i]) dfs1(i);
	stk.eb(now);
}
void dfs2(int now) {
	chk[now]=1; scc[now]=tp;
	for (auto &i:rev[now]) if (!chk[i]) dfs2(i);
}

void solve(int s, int e, vim &L) {
	if (s==e) {
		for (auto &i:V[s]) {
			in[get(i)]++;
			if (in[get(i)]==1) cnt--;
		}
		for (auto &i:L) {
			in[get(line[i].v)]--;
			if (in[get(line[i].v)]==0) cnt++;
		}
		for (auto &i:L) Union(line[i].u, line[i].v);
		ans[s]=cnt;
		return ;
	}

	vim X, Y, Z;
	int md=(s+e)/2;
	for (auto &i:L) (line[i].id<=md?X:Z).eb(i);

	for (auto &i:X) line[i].u=get(line[i].u), line[i].v=get(line[i].v);
	use.clear();
	for (auto &i:X) use.eb(line[i].u), use.eb(line[i].v);
	sort(all(use)); unq(use);
	for (auto &i:use) adj[i].clear(), rev[i].clear();
	for (auto &i:X) adj[line[i].u].eb(line[i].v), rev[line[i].v].eb(line[i].u);

	stk.clear();
	for (auto &i:use) chk[i]=0;
	for (auto &i:use) if (!chk[i]) dfs1(i);
	for (auto &i:use) chk[i]=0;
	tp=0; reverse(all(stk));
	for (auto &i:stk) if (!chk[i]) ++tp, dfs2(i);
	for (auto &i:X) (scc[line[i].u]==scc[line[i].v]?Y:Z).eb(i);
	solve(s, md, Y); solve(md+1, e, Z);
}

int main() {
	scanf("%d %d", &N, &M); cnt=N;
	line.resize(M);
	for (int i=0; i<M; i++) scanf("%d %d", &line[i].u, &line[i].v);
	scanf("%d", &Q);
	for (int i=0, u; i<Q; i++) {
		scanf("%d", &u);
		line[u-1].id=Q-i;
	}
	for (auto &i:line) V[i.id].eb(i.v);
	vim L;
	for (int i=0; i<M; i++) L.eb(i);
	solve(0, Q, L);
	for (int i=Q-1; i>=0; i--) printf("%d\n", ans[i]);
	return 0;
}