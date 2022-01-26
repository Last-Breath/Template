#include <cstdio>
#include <string>
#include <iostream>
using namespace std;
const int MAXN = 1e6 + 5;
int ed[MAXN], sa[MAXN], lst[MAXN], now[MAXN], tmp[MAXN << 1];
string s;
void Init(int x, int y) {
	for (int i = 1; i <= y; i++) ed[i] = 0;
	for (int i = 1; i <= x; i++) ed[lst[i]]++;
	for (int i = 2; i <= y; i++) ed[i] += ed[i - 1];
}
void Fill_Bkt(int x) {
	for (int i = x; i >= 1; i--) {
		sa[ed[lst[now[i]]]] = now[i];
		ed[lst[now[i]]]--;
	}
}
void Get_SA(int x, int y) {
	for (int i = 1; i <= x; i++) {
		lst[i] = s[i - 1];
		now[i] = i;
	}
	Init(x, y);
	Fill_Bkt(x);
	for (int len = 1; len < x; len <<= 1) {
		int id = 0, cnt = 1;
		Init(x, y);
		for (int i = x - len + 1; i <= x; i++) now[++id] = i;
		for (int i = 1; i <= x; i++) if (sa[i] > len) now[++id] = sa[i] - len;
		Fill_Bkt(x);
		for (int i = 1; i <= x; i++) tmp[i] = lst[i];
		lst[sa[1]] = 1;
		for (int i = 2; i <= x; i++) {
			if (tmp[sa[i]] != tmp[sa[i - 1]] || tmp[sa[i] + len] != tmp[sa[i - 1] + len]) cnt++;
			lst[sa[i]] = cnt;
		}
		y = cnt;
	}
}
int main() {
	cin >> s;
	Get_SA(s.size(), 'z');
	for (int i = 1, siz = s.size(); i <= siz; i++) printf("%d ", sa[i]);
	return 0;
}
