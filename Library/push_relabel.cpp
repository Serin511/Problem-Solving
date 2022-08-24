// AC code for https://loj.ac/p/127 ; got 641ms

#include <bits/stdc++.h>

using namespace std;

struct HLPP {
	struct edge {
		int v, c, i;
	};

	int n, cnt;
	vector<vector<edge>> grp;
	vector<vector<int>> qu;
	vector<long long> in, out;
	vector<int> height;

	HLPP(int n) : n(n), cnt(0), grp(n), in(n), out(n), height(n), qu(2*n) {}

	void add_edge(int u, int v, int c) {
		if (u==v) return ;
		grp[u].push_back({v, c, (int)grp[v].size()});
		grp[v].push_back({u, 0, (int)grp[u].size()-1});
	}
	
	void inqueue(int u) {
		qu[height[u]].emplace_back(u);
	}

	int outqueue(int h) {
		int u=qu[h].back();
		qu[h].pop_back();
		return u;
	}

	void push(int u, int v, int i) {
		auto go=min(in[u]-out[u], 1ll*grp[u][i].c);
		assert(go>0);
		if (in[v]==out[v]) inqueue(v);
		in[v]+=go;
		out[u]+=go;
		grp[v][grp[u][i].i].c+=go;
		grp[u][i].c-=go;
	}

	int send(int h) {
		int u=outqueue(h), mn=2*n;
		if (height[u]!=h) return h;

		for (auto &e:grp[u]) if (in[u]>out[u]&&e.c) {
			if (height[u]==height[e.v]+1) push(u, e.v, grp[e.v][e.i].i);
			else mn=min(mn, height[e.v]+1);
		}

		if (in[u]>out[u]) {
			height[u]=mn;
			cnt++;
			if (mn<n) { inqueue(u); return mn; }
		}

		return h;
	}

	int global(int t) {
		cnt=0;
		for (auto &i:qu) i.clear();
		fill(height.begin(), height.end(), 2*n+1);
		
		queue<int> q;
		q.emplace(t);
		height[t]=0;

		int mx=0;

		while (q.size()) {
			int u=q.front();
			q.pop();
			int h=height[u]+1;

			for (auto &e:grp[u]) {
				if (grp[e.v][e.i].c&&h<height[e.v]) {
					q.emplace(e.v);
					height[e.v]=h;
					if (in[e.v]>out[e.v]) inqueue(e.v), mx=max(mx, h);
				}
			}
		}

		return mx;
	}

	long long flow(int s, int t) {
		height[s]=n;
		out[s]=out[t]=1e18;

		for (auto &e:grp[s]) if (e.c) {
			in[e.v]+=e.c;
			grp[e.v][e.i].c+=e.c;
			e.c=0;
			inqueue(e.v);
		}

		for (int hi=0; ;) {
			for (; qu[hi].empty(); hi--) if (hi==0) return in[t];
			hi=send(hi);
			if (cnt>=4*n) hi=max(hi, global(t));
		}
	}
};

int main() {
	cin.tie(0)->sync_with_stdio(0);

	int n, m, s, t;
	cin>>n>>m>>s>>t;
	HLPP sol(n+1);
	while (m--) {
		int u, v, c;
		cin>>u>>v>>c;
		sol.add_edge(u, v, c);
	}
	cout<<sol.flow(s, t);

	return 0;
}
