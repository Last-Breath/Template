#include <map>
#include <queue>
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
priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
int h[MAXN], pre[MAXN], dis[MAXN], lim[MAXN];
bool vis[MAXN];
int n, m, s, t, mcmf;
int Min(int x, int y) {
	return x < y ? x : y;
}
bool Dijkstra() {
	for (int i = 1; i <= n; i++) vis[i] = 0, pre[i] = 0, lim[i] = dis[i] = INF;
	dis[s] = 0, pq.push(make_pair(0, s));
	while (!pq.empty()) {
		int u = pq.top().second; pq.pop();
		if (vis[u]) continue; vis[u] = 1;
		for (int i = head[u]; i; i = edge[i].Next) {
			int v = edge[i].To;
			if (dis[v] > dis[u] + edge[i].Cost + h[u] - h[v] && edge[i].Cap) {
				pre[v] = i, lim[v] = min(lim[u], edge[i].Cap);
				dis[v] = dis[u] + edge[i].Cost + h[u] - h[v];
				pq.push(make_pair(dis[v], v));
			}
		}
	}
	for (int i = 1; i <= n; i++) if (dis[i] < INF) h[i] += dis[i];
	return dis[t] != INF;
}
int Update() {
	int now = t;
	while (now != s) {
		int i = pre[now];
		edge[i].Cap -= lim[t];
		edge[i ^ 1].Cap += lim[t];
		mcmf += lim[t] * edge[i].Cost;
		now = edge[i ^ 1].To;
	}
	return lim[t];
}
int EK() {
	int res = 0;
	while (Dijkstra()) res += Update();
	return res;
}
int main() {
	scanf("%d %d %d %d", &n, &m, &s, &t);
	for (int i = 1, u, v, w, c; i <= m; i++) {
		scanf("%d %d %d %d", &u, &v, &w, &c);
		Addedge(u, v, w, c);
	}
	printf("%d ", EK());
	printf("%d", mcmf);
	return 0;
}
