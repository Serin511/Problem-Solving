#include <bits/stdc++.h>

using namespace std;

struct FragmentedTree {
	const int SQ = 400;

	struct Fragment {
		int n, p, t;
		vector<int> nodes;
		Fragment(int u, int n) : p(-1), t(u), n(n), {}
		void add(int u) {
			nodes.push_back(u);
			if (u>n) return ;
		}
		ll get() {}
		void init() {}
	};

	int n;
	vector<vector<int>> org, adj, subAdj;
	vector<Fragment> frags;
	vector<int> dep, fragPos, fragPar;
	FragmentedTree(int n): n(n), org(n+1), adj(n+1) {}
	
	void addEdge(int u, int v) {
		org[u].push_back(v);
		org[v].push_back(u);
	}

	int makeNode(int u, const vector<int> &im) {
		fragPos.push_back(-1);
		fragPar.push_back(u);
		dep.push_back(u<0?0:dep[u]+1);
		int num=adj.size();
		adj.push_back(im);
		return num;
	}

	void makeFragment(int u, Fragment &fr) {
		if (fragPos[u]!=-1) return ;
		fragPos[u]=frags.size()-1;
		fr.add(u);
		for (int v:adj[u]) makeFragment(v, fr);
	}

	void build(int rt=1) {
		dep=vector<int>(n+1);

		{
			queue<array<int, 2>> q;
			q.push({rt, -1});
			while (q.size()) {
				auto [u, p]=q.front();
				q.pop();
				for (int v:org[u]) if (v!=p) q.push({v, u}), dep[v]=dep[u]+1;
			}
		}

		fragPos=fragPar=vector<int>(n+1, -1);

		adj=org;

		vector<int> ord(n);
		iota(ord.begin(), ord.end(), 1);
		sort(ord.begin(), ord.end(), [&](int x, int y) {
			return dep[x]>dep[y];
		});

		vector<int> sz(n+1);
		for (int u:ord) {
			sz[u]=1;
			int sum=0;
			vector<int> im, ch;
			for (int v:adj[u]) if (dep[u]<dep[v]) sz[u]+=sz[v];
			for (int v:adj[u]) if (dep[u]<dep[v]) {
				sum+=sz[v];
				im.push_back(v);
				if (sum>SQ) {
					int nd=makeNode(u, im);
					im.clear();
					ch.push_back(nd);
					frags.emplace_back(nd, n);
					makeFragment(nd, frags.back());
					sz[u]-=sum;
					sum=0;
				}
			}
			adj[u]=im;
			for (int i:ch) adj[u].push_back(i);
		}

		int nd=makeNode(-1, vector<int>({rt}));
		frags.emplace_back(nd, n);
		makeFragment(nd, frags.back());

		subAdj=vector<vector<int>>(frags.size());
		for (int i=0; auto &fr:frags) {
			fr.init();
			if (fragPar[fr.t]==-1) continue;
			fr.p=fragPos[fragPar[fr.t]];
			subAdj[fr.p].push_back(i);
			i++;
		}
	}

	int leader(int u) { return frags[fragPos[u]].t; }
};