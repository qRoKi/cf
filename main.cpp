#include <bits/stdc++.h>
                                                   
#define forn(i, n) for (int i = 0; i < int(n); i++)
#define for1(i, n) for (int i = 1; i < int(n); i++)
#define nfor(i, n) for (int i = int(n) - 1; i >= 0; i--)
#define forr(i, n) for (int i = int(n) - 1; i >= 0; i--)
#define fore(i, l, r) for (int i = int(l); i < int(r); i++)
#define forft(i, l, r) for (int i = int(l); i < int(r); i++)
#define correct(x, y, n, m) (0 <= (x) && (x) < (n) && 0 <= (y) && (y) < (m))
#define all(a) (a).begin(), (a).end()
#define sz(a) int((a).size())
#define pb(a) push_back(a)
#define mp(x, y) make_pair((x), (y))
#define ms(a, v) memset(a, v, sizeof(a))
#define x first
#define y second
#define X first
#define Y second
#define ft first
#define sc second

using namespace std;

typedef long long li;
typedef long double ld;
typedef pair<int, int> pt;

template<typename X> inline X abs(const X& a) { return a < 0? -a: a; }
template<typename X> inline X sqr(const X& a) { return a * a; }

const int INF = int(1e9);
const li INF64 = li(1e18);
const ld EPS = 1e-9, PI = 3.1415926535897932384626433832795;

int n, k;
const int N = 2005;
int x[N], y[N], z[N], w[N];

inline bool read() {
	cin >> n >> k;
	forn (i, n)
		cin >> x[i] >> y[i] >> z[i] >> w[i];
	return true;
}

vector<int> g[N];

int dist(int i, int j) {
	return abs(x[i] - x[j]) + abs(y[i] - y[j]) + abs(z[i] - z[j]);
}

bool used[N];
int mt[N];

bool kuhn(int v) {
	used[v] = true;
	for (int to : g[v]) {
		if (mt[to] == -1 || !used[mt[to]] && kuhn(mt[to])) {
			mt[to] = v;
			return true;
		}
	}
	return false;
}

int maxmt() {
	int f = 0;
	memset(mt, -1, sizeof mt);
	forn (i, n) {
		int s = x[i] + y[i] + z[i];
		if (s & 1)
			continue;
		memset(used, false, sizeof used);
		f += kuhn(i);
	}
	return f;
}

bool ok(int mid) {
	forn (i, N)
		g[i].clear();
	forn (i, n) {

		int bt = w[i];		
		
		forn (j, n) {
			if (w[i] + w[j] >= mid && dist(i, j) == 1) {
				g[i].pb(j);
				bt = max(bt, w[i] + w[j]);
			}
		}
		if (bt < mid)
			return false;
	}
	int f = maxmt();
	return n - 2 * f <= k - f;
}

bool fin[N];

void print(int val) {
	if (val % 2 == 0)
		cout << val / 2 << ' ';
	else {
		printf("%.1f ", double(val / 2.0));
	}
}

inline void solve() {
	int l = 0, r = INF;
	while(!ok(l)) {
		cout << -1 << endl;
		return;
	}
	while(r - l > 1) {
		int mid = (r + l) >> 1;
		if (ok(mid))
			l = mid;
		else
			r = mid;
	}	

	ok(l);
	int f = 0;
	forn (i, n) {
		int s = x[i] + y[i] + z[i];
		if (s % 2 == 0 || mt[i] == -1)
			continue;
		fin[i] = fin[mt[i]] = true;	
		f++;
	}
	cout << f + (n - 2 * f) << ' ' << l << endl;
	forn (i, n) {
		int s = x[i] + y[i] + z[i];
		if (s % 2 == 0 || mt[i] == -1)
			continue;
		int j = mt[i];
		print(x[i] + x[j]);
		print(y[i] + y[j]);
		print(z[i] + z[j]);
		cout << endl;
	}
	
	forn (i, n) {
		if (fin[i])
			continue;
		int j = i;
		forn (t, n) {
			if (dist(i, t) == 1 && (j == i || w[t] > w[j]))
				j = t;
		}
	
		print(x[i] + x[j]);
		print(y[i] + y[j]);
		print(z[i] + z[j]);
		cout << endl;
	}
}

#define TASKNAME "starbugs"

int main() {
#ifdef SU2_PROJ
	assert(freopen("input.txt", "rt", stdin));
	assert(freopen("output.txt", "wt", stdout));
#else
	assert(freopen(TASKNAME".in", "rt", stdin));
	assert(freopen(TASKNAME".out", "wt", stdout));
#endif

	srand(time(NULL));

	cout << setprecision(10) << fixed;
	cerr << setprecision(5) << fixed;

	read();
	solve();

#ifdef SU2_PROJ
	cerr << "Time: " << clock() << endl;
#endif
	
	return 0;
}
