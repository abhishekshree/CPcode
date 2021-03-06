#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <bitset>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mod = 666013;
const int mxn = 3000;
int n, m;
int a[mxn], it[mxn];
vector<int> g[mxn];
bitset<mxn> dp[mxn], s[mxn], f;
int ans[mxn][mxn];

int main(){
	freopen("casute.in", "r", stdin);
	freopen("casute.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	for(int i = 0; i < n; i++){
		cin >> a[i];
		it[i] = i;
		dp[i][i] = 1;
		for(int j = i + 1; j < n; j++) s[i][j] = 1;
	} 
	
	for(int i = 0; i < m; i++){
		int u, v;
		cin >> u >> v;
		g[--u].push_back(--v);
	}
	
	sort(it, it + n, [&](int x, int y){
		return a[x] < a[y];
	});
	
	for(int i = 0; i < n; i++){
		int x = it[i];
		for(int j : g[x]) dp[j] |= dp[x];
		for(int j = dp[x]._Find_first(); j < n; j = dp[x]._Find_next(j)){
			f = dp[x] & s[j];
			for(int l = f._Find_first(); l < n; l = f._Find_next(l)){
				ans[j][l] = x + 1, s[j][l] = 0;
			}
		}
	}
	
	ll ret = 0;
	for(ll i = n - 1, x = 1; ~i; i--)
	for(int j = n - 1; j > i; j--){
		(ret += x * ans[i][j]) %= mod;
		(x *= n + 1) %= mod;
	}
	
	cout << ret << endl;

	return 0;
}