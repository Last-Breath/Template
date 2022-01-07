#include <deque>
#include <cstdio>
#include <vector>
using namespace std;
#define INF 0x7f7f7f7f
#define Min(a, b) ((a) < (b) ? (a) : (b))
void Read(int &n) {
	n = 0;
	char ch = getchar();
	while  (ch < '0' || ch > '9') {
		ch = getchar();
	}
	while  (ch >= '0' && ch <= '9') {
		n = (n << 1) + (n << 3) + (ch ^ 48);
		ch = getchar();
	}
}
const int MAXN = 5e3 + 5;
struct Node { int To, Cap, Cost, Rev; };
vector<Node> vec[MAXN];
deque<int> dq;
int dis[MAXN], cur[MAXN];
bool inque[MAXN], vis[MAXN];
int n, m, s, t, cst;
void Addedge(int u, int v, int w, int c) {
	int ru = vec[u].size();
	int rv = vec[v].size();
	vec[u].push_back({v, w, c, rv});
	vec[v].push_back({u, 0, -c, ru});
}
bool SPFA() {
	for (int i = 1; i <= n; i++) dis[i] = INF;
	dis[t] = cur[t] = 0, inque[t] = 1, dq.push_back(t);
	while (!dq.empty()) {
		int u = dq.front(); dq.pop_front();
		inque[u] = 0;
		for (int i = 0, siz = vec[u].size(); i < siz; i++) {
			int v = vec[u][i].To;
			if (dis[v] > dis[u] - vec[u][i].Cost && vec[v][vec[u][i].Rev].Cap) {
				dis[v] = dis[u] - vec[u][i].Cost; cur[v] = 0;
				if (!inque[v]) {
					if (!dq.empty() && dis[v] < dis[dq.front()]) dq.push_front(v);
					else dq.push_back(v);
				}
				inque[v] = 1;
			}
		}
	}
	return dis[s] != INF;
}
int dfs(int u, int flow) {
	if (!flow || u == t) return flow;
	int rest = flow;
	vis[u] = 1;
	for (int i = cur[u], siz = vec[u].size(); i < siz && rest; i++) {
		int v = vec[u][i].To; cur[u] = i;
		if (!vis[v] && dis[v] == dis[u] - vec[u][i].Cost && vec[u][i].Cap) {
			int del = dfs(v, Min(vec[u][i].Cap, rest));
			rest -= del;
			cst += del * vec[u][i].Cost;
			vec[u][i].Cap -= del;
			vec[v][vec[u][i].Rev].Cap += del;
		}
	}
	vis[u] = 0;
	return flow - rest;
}
int Dinic() {
	int res = 0, flow;
	while (SPFA()) while ((flow = dfs(s, INF))) res += flow;
	return res;
}
int main() {
	Read(n); Read(m); Read(s); Read(t);
	for (int i = 1, u, v, w, c; i <= m; i++) {
		Read(u); Read(v); Read(w); Read(c);
		Addedge(u, v, w, c); 
	}
	printf("%d ", Dinic());
	printf("%d", cst);
	return 0;
}
