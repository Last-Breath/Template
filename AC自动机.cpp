#include <queue>
#include <cstdio>
#include <string>
#include <iostream>
using namespace std;
const int MAXN = 1e6 + 5;
queue<int> que;
struct Node {
	int son[26], fail, cnt;
	#define New ++tot
};
Node tr[MAXN];
int tot;
void Insert(string str) {
	int pos = 0;
	for (int i = 0, siz = str.size(); i < siz; i++) {
		int h = str[i] - 'a';
		if (!tr[pos].son[h]) tr[pos].son[h] = New;
		pos = tr[pos].son[h];
	}
	tr[pos].cnt++;
}
void Get_Fail() {
	for (int i = 0; i < 26; i++) if (tr[0].son[i]) que.push(tr[0].son[i]);
	while (!que.empty()) {
		int pos = que.front(); que.pop();
		for (int i = 0; i < 26; i++) {
			if (tr[pos].son[i]) {
				tr[tr[pos].son[i]].fail = tr[tr[pos].fail].son[i];
				que.push(tr[pos].son[i]);
			}
			else tr[pos].son[i] = tr[tr[pos].fail].son[i];
		}
	}
}
int Query(string str) {
	int res = 0, pos = 0;
	for (int i = 0, siz = str.size(); i < siz; i++) {
		int h = str[i] - 'a';
		pos = tr[pos].son[h];
		for (int v = pos; v && ~tr[v].cnt; v = tr[v].fail) res += tr[v].cnt, tr[v].cnt = -1;
	}
	return res;
}
string s, t;
int n;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		cin >> s;
		Insert(s);
	}
	Get_Fail();
	cin >> t;
	printf("%d", Query(t));
	return 0;
}
