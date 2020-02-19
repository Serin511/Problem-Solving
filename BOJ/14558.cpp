#include <bits/stdc++.h>
#define em emplace
using namespace std;
typedef long long ll;

int N, M; ll J[100010];
set<ll> A, S; map<ll, int> mp;

ll F[1<<17];
void upd(int t, ll v) { while (t<=N) F[t]+=v, t+=t&-t; }
int srh(ll v) {
	for (int r=0, i=16; i>=0; i--) {
		if ((r|1<<i)>N) continue;
		if (F[r|1<<i]==v) return r|1<<i;
		if (F[r|1<<i]<v) r|=1<<i, v-=F[r];
	}
	return -1;
}

bool ub(ll now, ll L) {
	auto k=S.upper_bound(now);
	if (k!=S.end()&&*k<now+L) return true;
	return false;
}

void solve(int in, ll now) {
	if (in==N+1) return ;
	ll L=*A.rbegin(); A.erase(L);

	if (S.find(now+L)!=S.end()) {
		if (*S.upper_bound(now)==now+L) {
			J[in]=L; upd(in, L); solve(in+1, now+L);
			swap(J[in], J[in+1]);
			upd(in, J[in]-L); upd(in+1, L-J[in]);
			return ;
		}
		for (auto &i:A) if (S.find(now+i)==S.end()&&S.find(now+i+L)==S.end()) {
			J[in]=i; J[in+1]=L; upd(in, i); upd(in+1, L); A.erase(i);
			solve(in+2, now+i+L); return ;
		}
	}

	if (ub(now, L)) {
		J[in]=L; upd(in, L); solve(in+1, now+L);
		return ;
	}
	auto k=S.upper_bound(now);
	ll ign=(k==S.end()?0:*k);
	S.erase(ign);
	J[in]=L; upd(in, L); solve(in+1, now+L);
	int x=srh(ign); if (x!=-1) {
		swap(J[in], J[x+1]);
		upd(in, J[in]-J[x+1]); upd(x+1, J[x+1]-J[in]);
	}
}

int main() {
	scanf("%d %d", &N, &M);
	ll im=0, a;
	for (int i=1; i<=N; i++) scanf("%lld", &a), mp[a]=i, im+=a, A.em(a);
	for (int i=1; i<=M; i++) scanf("%lld", &a), S.em(a);
	if (S.find(im)!=S.end()) { puts("-1"); return 0; }
	solve(1, 0);
	for (int i=1; i<=N; i++) printf("%d ", mp[J[i]]); puts("");
	return 0;
}