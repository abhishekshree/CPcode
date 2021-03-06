/*
  If you build a segment tree with the data, every valid segment will have it's two endpoints among the left and right child of some
node and use all elements between. Because we want as short a segment as possible, it is only beneficial to look at the closest 
elements of each type to the midpoint during a merge, and use two pointers to try O(k) possible positions based on how many elements
we use that are closest on left side and right side, and see if the two pointer answer is better than the answer of the left child 
and right child. This means we need to hold the closest elements to the left and right side of each node in the segment tree. This 
is easily done by first taking the best side from one child and then appending on elements not included in the first child that are
in the second child. Now you can perform updates in O(klgn) and print the best answer at the top node.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <array>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int inf = 0x3f3f3f3f;
const int mxn = 1 << 17, mxk = 50;
typedef array<int, mxk> A;
int n, k, q;
int a[mxn];
A vis;

struct T{
	int m, val;
	A v[2], f[2];
	
	void upd(int x){
		val = (m = !!~a[x]) >= k ? 1 : inf;
		for(int i = 0; i < 2; i++){
			v[i] = f[i] = A();
			if(m) v[i][0] = x, f[i][a[x]] = 1;
		}
	}
	
	T friend operator+(T &l, T &r){
		T rt, c[2] = {l, r};
		rt.val = inf;
		for(int i = 0; i < 2; i++){
			rt.val = min(rt.val, c[i].val);
			rt.v[i] = c[i].v[i], rt.f[i] = c[i].f[i], rt.m = c[i].m;
			for(int j = 0; j < c[!i].m; j++){
				int x = c[!i].v[i][j];
				if(!rt.f[i][a[x]]) rt.f[i][a[rt.v[i][rt.m++] = x]] = 1;
			}
		}
		
		vis = l.f[1];
		for(int i = l.m, j = 0, w = l.m; i; i--){
			if(i < l.m) w -= !(--vis[a[l.v[1][i]]]);
			for(; j < r.m && (j < 1 || w < k); j++) w += !(vis[a[r.v[0][j]]]++);
			if(w == k && j) rt.val = min(rt.val, r.v[0][j - 1] - l.v[1][i - 1] + 1);
		}
		
		return rt;
	}
} tr[mxn << 1];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k >> q;
	
	for(int i = 0; i < n; i++){
		cin >> a[i];
		a[i]--;
	}
	while(n & (n - 1)) a[n++] = -1;
	
	for(int i = 0; i < n; i++) tr[n + i].upd(i);
	for(int i = n - 1; i; i--) tr[i] = tr[i << 1] + tr[i << 1 | 1];
	
	while(q--){
		int t;
		cin >> t;
		if(!~-t){
			int x;
			cin >> x >> a[--x];
			a[x]--;
			tr[n + x].upd(x);
			for(int i = (n + x) >> 1; i; i >>= 1) tr[i] = tr[i << 1] + tr[i << 1 | 1];
		}else{
			int ret = tr[1].val;
			cout << (ret == inf ? -1 : ret)  << endl;
		}
	}

	return 0;
}
