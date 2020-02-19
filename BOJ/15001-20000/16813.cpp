#include <bits/stdc++.h>
#define fi first
#define se second
#define ryan bear
#define sq(X) ((X)*(X))
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
#define unq(V) (V).erase(unique(all(V)), (V).end())
using namespace std;
typedef long long ll;
typedef vector<ll> vlm;
typedef vector<int> vim;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
const ll INF = (1ll<<60);
const int MAX = 1e9;

struct line {
	ll a, b;
	ll get(ll x) { return a*x+b; }
	line() {}
	line(ll A, ll B) { a=A, b=B; }
};

struct CHT {
	line L[4010]; int s, e;
	void upd(line v) {
		if (s<e && L[e-1].a==v.a && L[e-1].b>v.b) return ;
		while (s+1<e && (L[e-1].b<v.b || (L[e-2].b-v.b)*(L[e-1].a-L[e-2].a)<=(L[e-2].b-L[e-1].b)*(v.a-L[e-2].a)) ) e--;
		L[e++]=v;
	}
	ll get(ll x) {
		if (s==e) return -INF;
		while (s+1<e && L[s].get(x)<L[s+1].get(x)) s++;
		return L[s].get(x);
	}
}cht[4010];

struct song { int t; ll p, f; };

int N, T; ll ans;
vector<song> S;

int main() {
	scanf("%d %d", &N, &T);
	S.resize(N);
	for (auto &i:S) scanf("%d %lld %lld", &i.t, &i.p, &i.f);
	sort(all(S), [](song s1, song s2){ return s1.f<s2.f; });
	for (auto &i:S) {
		if (i.t>T) continue;
		for (int j=T-i.t; j; j--) {
			ll im=cht[j].get(i.f);
			if (im!=-INF) cht[j+i.t].upd(line(2*i.f, i.p-2*i.f*i.f+im));
			ans=max(ans, im-i.f*i.f+i.p);
		}
		cht[i.t].upd(line(2*i.f, i.p-i.f*i.f));
		ans=max(ans, i.p);
	}
	printf("%lld\n", ans);
	return 0;
}