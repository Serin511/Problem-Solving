#include <bits/stdc++.h>
#define fi first
#define se second
#define ryan bear
#define rev(p) p={p.se,p.fi}
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef long double ld;

int n, k;
ll ans;
ll s[100010], c[100010];
set<pll> S1, S2;
void f()
{
	pll p1=*S1.begin(); ans+=p1.fi;
	set<pll>::iterator it=S2.lower_bound({p1.se, p1.fi});
	if (it==S2.begin()) {
		if (next(it)==S2.end()) return ;
		rev(p1); pll p2=*next(it);
		S2.erase(p1); S2.erase(p2);
		rev(p1); rev(p2);
		S1.erase(p1); S1.erase(p2);
		return ;
	}
	if (next(it)==S2.end()) {
		rev(p1); pll p2=*prev(it);
		S2.erase(p1); S2.erase(p2);
		rev(p1); rev(p2);
		S1.erase(p1); S1.erase(p2);
		return ;
	}
	pll p2=(*prev(it)), p3=(*next(it));
	rev(p1); S2.erase(p1); S2.erase(p2); S2.erase(p3);
	rev(p1); rev(p2); rev(p3);
	S1.erase(p1); S1.erase(p2); S1.erase(p3);
	S1.insert({p2.fi+p3.fi-p1.fi, p2.se});
	S2.insert({p2.se, p2.fi+p3.fi-p1.fi});
}

int main()
{
	scanf("%d %d", &n, &k);
	int i;
	for (i=0; i<n; i++) scanf("%d", &s[i]);
	sort(s,s+n);
	for (i=0; i<n-1; i++) c[i]=s[i+1]-s[i];
	for (i=0; i<n-1; i++) {
		S1.insert({c[i], i});
		S2.insert({i, c[i]});
	}
	for (i=0; i<k; i++) f();
	printf("%lld\n", ans);
	return 0;
}