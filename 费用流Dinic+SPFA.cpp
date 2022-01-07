#include <deque>
#include <cstdio>
using namespace std;
const int MAXN = 5e3 + 5;
const int MAXM = 5e4 + 5;
const int INF = 0x7f7f7f7f;
struct Edge { int To, Cap, Cost, Next; };
Edge edge[MAXM << 1];
int head[MAXN], tot = 1;
void Addedge(int u, int v, int w, int c) {
	edge[++tot].Next = head[u], edge[tot].To = v, edge[tot].Cap = w, edge[tot].Cost = c, head[u] = tot;
	edge[++tot].Next = head[v], edge[tot].To = u, edge[tot].Cap = 0, edge[tot].Cost = -c, head[v] = tot;
}
deque<int> dq;
int dis[MAXN];
bool inque[MAXN], vis[MAXN];
int n, m, s, t, mcmf;
int Min(int x, int y) {
	return x < y ? x : y;
}
bool SPFA() {
	for (int i = 1; i <= n; i++) dis[i] = INF;
	dis[t] = 0, inque[t] = 1, dq.push_back(t);
	while (!dq.empty()) {
		int u = dq.front(); dq.pop_front(), inque[u] = 0;
		for (int i = head[u]; i; i = edge[i].Next) {
			int v = edge[i].To;
			if (dis[v] > dis[u] - edge[i].Cost && edge[i ^ 1].Cap) {
				dis[v] = dis[u] - edge[i].Cost;
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
	for (int i = head[u]; i && rest; i = edge[i].Next) {
		int v = edge[i].To;
		if (!vis[v] && dis[v] == dis[u] - edge[i].Cost && edge[i].Cap) {
			int del = dfs(v, Min(edge[i].Cap, rest));
			edge[i].Cap -= del, edge[i ^ 1].Cap += del, rest -= del;
			mcmf += del * edge[i].Cost;
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
	scanf("%d %d %d %d", &n, &m, &s, &t);
	for (int i = 1, u, v, w, c; i <= m; i++) {
		scanf("%d %d %d %d", &u, &v, &w, &c);
		Addedge(u, v, w, c);
	}
	printf("%d ", Dinic());
	printf("%d", mcmf);
	return 0;
}
