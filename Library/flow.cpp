#include <bits/stdc++.h>

using namespace std;

namespace flow {
	namespace {
		const int INF = 1e9 + 5;
		const long long INF_LL = 1e18 + 5;
		
		bool dinic_dfs(int u, int ter, int mn, vector<vector<tuple<int, int, int>>> &graph, vector<int> &start, vector<int> &dst) {
			if (!mn) return 0;
			if (u==ter) return 1;
			for (int &i=start[u]; i<graph[u].size(); i++) {
				auto [v, cap, rev]=graph[u][i];
				if (dst[u]+1==dst[v]&&cap>=mn&&dinic_dfs(v, ter, mn, graph, start, dst)) {
					get<1>(graph[u][i])-=mn;
					get<1>(graph[v][rev])+=mn;
					return 1;
				}
			}
			return 0;
		}
		
		int hk_dfs(int u, vector<vector<int>> &adj, vector<int> &con, vector<int> &dst) {
			for (auto &i:adj[u]) if (con[i]==-1||(dst[con[i]]==dst[u]+1&&hk_dfs(con[i], adj, con, dst))) {
				con[i]=u;
				con[u]=i;
				return 1;
			}
			return 0;
		}
	}

	long long Dinic(int s, int t, vector<vector<pair<int, int>>> &adj) {
		if (s==t) return 0;
		
		int n=adj.size();

		vector<vector<tuple<int, int, int>>> graph(n);
		for (int i=0; i<n; i++) for (auto &j:adj[i])
			graph[i].emplace_back(j.first, j.second, graph[j.first].size()),
			graph[j.first].emplace_back(i, 0, graph[i].size()-1);
		
		vector<int> start(n), dst(n), stk(n);
		long long rt=0;

		auto bfs = [&](int b) {
			fill(dst.begin(), dst.end(), INF);
			int tp=1;
			stk[0]=s;
			dst[s]=0;
			for (int j=0; j<tp; j++) for (auto &i:graph[stk[j]]) if (get<1>(i)>=b&&dst[get<0>(i)]==INF)
				stk[tp++]=get<0>(i), dst[get<0>(i)]=dst[stk[j]]+1;
			return dst[t]!=INF;
		};

		for (int i=30; i>=0; ) {
			if (!bfs(1<<i)) { i--; continue; }
			fill(start.begin(), start.end(), 0);
			int fl;
			while (fl=dinic_dfs(s, t, 1<<i, graph, start, dst)) rt+=(1<<i);
		}

		return rt;
	}

	pair<long long, long long> MCMF(int s, int t, vector<vector<tuple<int, int, int>>> &adj) {
		int n=adj.size();

		struct edge { int v, c, i, l; };
		vector<vector<edge>> graph(n);
		for (int i=0; i<n; i++) for (auto &j:adj[i]) {
			auto [u, cap, l]=j;
			graph[i].push_back({u, cap, graph[u].size(), l});
			graph[u].push_back({i, 0, graph[i].size()-1, -l});
		}

		long long flow=0, cost=0;
		vector<long long> dst(n), lst(n);
		while (1) {
			fill(dst.begin(), dst.end(), INF_LL);
			fill(lst.begin(), lst.end(), -1);

			deque<int> stk;
			stk.emplace_back(s);
			dst[s]=0;
			vector<int> in(n);
			in[s]=1;

			while (stk.size()) {
				int u=stk.front();
				stk.pop_front();
				in[u]=0;
				for (auto &e:graph[u]) {
					if (e.c&&dst[u]+e.l<dst[e.v]) {
						dst[e.v]=dst[u]+e.l;
						lst[e.v]=e.i;
						if (!in[e.v]) {
							in[e.v]=1;
							if (stk.size()&&dst[e.v]<dst[stk.front()]) stk.emplace_front(e.v);
							else stk.emplace_back(e.v);
						}
					}
				}
			}
			
			if (lst[t]==-1) break;

			int fl=INF;
			for (int i=t; lst[i]!=-1; i=graph[i][lst[i]].v) fl=min(fl, graph[graph[i][lst[i]].v][graph[i][lst[i]].i].c);
			for (int i=t; lst[i]!=-1; i=graph[i][lst[i]].v) {
				auto &e=graph[i][lst[i]];
				e.c+=fl;
				graph[e.v][e.i].c-=fl;
				cost-=fl*e.l;
			}
			flow+=fl;
		}

		return {flow, cost};
	}

	int Hopcroft_Karp(int n, int m, vector<vector<int>> &adj) {
		int rt=0;
		vector<int> con(n+m, -1), dst(n);

		while (1) {
			fill(dst.begin(), dst.end(), INF);
			vector<int> stk;
			for (int i=0; i<n; i++) if (con[i]==-1) stk.emplace_back(i), dst[i]=0;
			for (int j=0; j<stk.size(); j++) for (auto &i:adj[stk[j]]) if (con[i]!=-1&&dst[con[i]]==INF)
				stk.emplace_back(con[i]), dst[con[i]]=dst[stk[j]]+1;
			
			int fl=0;
			for (int i=0; i<n; i++) if (con[i]==-1&&hk_dfs(i, adj, con, dst)) fl++;
			
			if (!fl) break;
			rt+=fl;
		}

		return rt;
	}
};

int main() {
	cin.tie(0)->sync_with_stdio(0);

	return 0;
}
