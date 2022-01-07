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
int dis[MAXN], nxt[MAXN], lim[MAXN];
bool inque[MAXN];
int n, m, s, t, mcmf;
int Min(int x, int y) {
	return x < y ? x : y;
}
bool SPFA() {
	for (int i = 1; i <= n; i++) dis[i] = INF, lim[i] = INF;
	dis[t] = 0, inque[t] = 1, dq.push_back(t);
	while (!dq.empty()) {
		int u = dq.front(); dq.pop_front(), inque[u] = 0;
		for (int i = head[u]; i; i = edge[i].Next) {
			int v = edge[i].To;
			if (dis[v] > dis[u] - edge[i].Cost && edge[i ^ 1].Cap) {
				dis[v] = dis[u] - edge[i].Cost, nxt[v] = i ^ 1, lim[v] = min(lim[u], edge[i ^ 1].Cap);
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
int Update() {
	int now = s;
	while (now != t) {
		int i = nxt[now];
		edge[i].Cap -= lim[s];
		edge[i ^ 1].Cap += lim[s];
		mcmf += lim[s] * edge[i].Cost;
		now = edge[i].To;
	}
	return lim[s];
}
int EK() {
	int res = 0;
	while (SPFA()) res += Update();
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
