#include <bits/stdc++.h>
#define fi first
#define se second
#define ryan bear
#define all(V) ((V).begin()), ((V).end())
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ll,int> pli;
typedef long double ld;
typedef vector<int> vim;
typedef vector<ll> vlm;

int N, M, S, T, U, V;
ll minD;
vlm Sd, Td, Ud, Vd;
vim Gr[100010]; vlm C[100010];
vim G1[100010], G2[100010];
vim chk, ts1, ts2, loc1, loc2; vlm Um, Vm;
priority_queue<pli, vector<pli>, greater<pli> > pq; 

void TS1(int now) {
	chk[now]=1;
	for (int i:G1[now]) {
		if (!chk[i]) TS1(i);
	}
	ts1.push_back(now);
}

void TS2(int now) {
	chk[now]=1;
	for (int i:G2[now]) {
		if (!chk[i]) TS2(i);
	}
	ts2.push_back(now);
}

int main() {
	int im1, im2, im3;
	scanf("%d %d %d %d %d %d", &N, &M, &S, &T, &U, &V);
	for (int i=0; i<M; i++) {
		scanf("%d %d %d", &im1, &im2, &im3);
		Gr[im1].push_back(im2); C[im1].push_back((ll)im3);
		Gr[im2].push_back(im1); C[im2].push_back((ll)im3);
	}
	Sd.resize(N+1); Td.resize(N+1); Ud.resize(N+1); Vd.resize(N+1); chk.resize(N+1);
	
	fill(all(chk), 0); while(!pq.empty()) pq.pop(); 
	pq.push({0, S});
	while (!pq.empty()) {
		pli pi=pq.top(); pq.pop();
		if (chk[pi.se]) continue;
		chk[pi.se]=1; Sd[pi.se]=pi.fi;
		for (int i=0; i<Gr[pi.se].size(); i++) if (!chk[Gr[pi.se][i]]) pq.push({pi.fi+C[pi.se][i], Gr[pi.se][i]});
	}
	
	fill(all(chk), 0); while(!pq.empty()) pq.pop(); 
	pq.push({0, T});
	while (!pq.empty()) {
		pli pi=pq.top(); pq.pop();
		if (chk[pi.se]) continue;
		chk[pi.se]=1; Td[pi.se]=pi.fi;
		for (int i=0; i<Gr[pi.se].size(); i++) if (!chk[Gr[pi.se][i]]) pq.push({pi.fi+C[pi.se][i], Gr[pi.se][i]});
	}

	fill(all(chk), 0); while(!pq.empty()) pq.pop(); 
	pq.push({0, U});
	while (!pq.empty()) {
		pli pi=pq.top(); pq.pop();
		if (chk[pi.se]) continue;
		chk[pi.se]=1; Ud[pi.se]=pi.fi;
		for (int i=0; i<Gr[pi.se].size(); i++) if (!chk[Gr[pi.se][i]]) pq.push({pi.fi+C[pi.se][i], Gr[pi.se][i]});
	}

	fill(all(chk), 0); while(!pq.empty()) pq.pop(); 
	pq.push({0, V});
	while (!pq.empty()) {
		pli pi=pq.top(); pq.pop();
		if (chk[pi.se]) continue;
		chk[pi.se]=1; Vd[pi.se]=pi.fi;
		for (int i=0; i<Gr[pi.se].size(); i++) if (!chk[Gr[pi.se][i]]) pq.push({pi.fi+C[pi.se][i], Gr[pi.se][i]});
	}

	minD=Sd[T];

	for (int i=1; i<=N; i++) for (int j=0; j<Gr[i].size(); j++) if (minD==Sd[i]+Td[Gr[i][j]]+C[i][j]) {
		G1[i].push_back(Gr[i][j]);
		G2[Gr[i][j]].push_back(i);
	}


	fill(all(chk), 0); TS1(S);
	fill(all(chk), 0); TS2(T);
	reverse(all(ts1)); reverse(all(ts2));
	Um.resize(ts1.size()); Vm.resize(ts1.size()); loc1.resize(N+1); loc2.resize(N+1);
	for (int i=0; i<ts1.size(); i++) loc1[ts1[i]]=loc2[ts2[i]]=i;

	ll ans=Ud[V];
	fill(all(Um), (1ll<<60)); fill(all(Vm), (1ll<<60));
	for (int i=0; i<ts1.size(); i++) {
		Um[i]=min(Um[i], Ud[ts1[i]]); Vm[i]=min(Vm[i], Vd[ts1[i]]);
		ans=min(ans, min(Um[i]+Vd[ts1[i]], Vm[i]+Ud[ts1[i]]));
		for (int j:G1[ts1[i]]) {
			Um[loc1[j]]=min(Um[loc1[j]], Um[i]);
			Vm[loc1[j]]=min(Vm[loc1[j]], Vm[i]);
		}
	}
	fill(all(Um), (1ll<<60)); fill(all(Vm), (1ll<<60));
	for (int i=0; i<ts2.size(); i++) {
		Um[i]=min(Um[i], Ud[ts2[i]]); Vm[i]=min(Vm[i], Vd[ts2[i]]);
		ans=min(ans, min(Um[i]+Vd[ts2[i]], Vm[i]+Ud[ts2[i]]));
		for (int j:G2[ts2[i]]) {
			Um[loc2[j]]=min(Um[loc2[j]], Um[i]);
			Vm[loc2[j]]=min(Vm[loc2[j]], Vm[i]);
		}
	}

	printf("%lld\n", ans);
	return 0;
}