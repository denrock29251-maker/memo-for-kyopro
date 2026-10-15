#include <bits/stdc++.h>
using namespace std;
#define rep(i, l, r) for (ll i = (l); i < (r); i++)
#define drep(i, l, r) for (long long i = (r) - 1; i >= l; i--)
#define nall(a) a.begin(), a.end()
using ll = long long;
// using lll = __int128; いらん
using P = pair<ll, ll>;
template <typename T>
using vc = vector<T>;
template <typename T>
using vvc = vc<vc<T>>;
template <typename T>
using vvvc = vc<vvc<T>>;
template <class T, class U>
inline bool chmax(T &a, const U &b)
{
  if (a < b)
  {
    a = b;
    return true;
  }
  return false;
}
template <class T>
ostream &operator<<(ostream &os, const vector<T> &V)
{
  for (auto a : V)
    os << a << ' ';
  return os;
}
bool kaibun(string &v)
{
  ll y = v.size();
  rep(i, 0, (y + 1) / 2)
  {
    if (v[i] != v[y - 1 - i])
    {
      return false;
    }
  }
  return true;
}
ll floor(ll x, ll m)
{
  ll r = (x % m + m) % m;
  return (x - r) / m;
  // 負の数の割り算をしたいときに使う
  //-7/2=-4になるこれだったら
}
ll cross(ll ax, ll ay, ll bx, ll by)
{
  // 二つのベクトルの外積を求める
  return ax * by - ay * bx;
  // これが0だったら平行
  // 原点->a->bの順にまわる
}
ll dot(ll ax, ll ay, ll bx, ll by)
{
  // ベクトルの内積を求める
  return ax * bx + ay * by;
  // これが0だったら垂直
}
bool ispoint(ll px, ll py, ll qx, ll qy, ll rx, ll ry, ll sx, ll sy)
{
  ll bigx = px - qx;
  ll bigy = py - qy;
  ll smallx = rx - sx;
  ll smally = ry - sy;
  ll vec = cross(bigx, bigy, smallx, smally);
  if (vec != 0)
    return true;
  else
  {
    ll tx = rx - px;
    ll ty = ry - py;
    if (cross(bigx, bigy, tx, ty) == 0)
      return true;
    return false;
  }
  // 2直線が交点を持つかを判定するヨ
}
bool isout_grid(ll i, ll j, ll h, ll w)
{
  // グリッド内ならfalseグリッド外ならtrue
  return (!(0 <= i && i < h && 0 <= j && j < w));
}
void Yes(bool a)
{
  if (a)
  {
    cout << "Yes" << "\n";
    return;
  }
  else
  {
    cout << "No" << "\n";
    return;
  }
}
bool compare(P &a, P &b)
{
  return a.second < b.second;

  // <で小さい順　>で大きい順
  // pairのsecondでソートする比較関数
  // >で大きい順　<で小さい順
  // sort(配列名.begin(),配列名.end(),compare)で使える
}
template <typename T>
ll LIS(vector<T> a)
{
  vector<ll> dp;
  rep(i, 0, a.size())
  {
    auto it = lower_bound(nall(dp), a[i]);
    if (it == dp.end())
    {
      dp.push_back(a[i]);
    }
    else
    {
      *it = a[i];
    }
  }
  return dp.size();
}
ll binary(ll n)
{ // n以下の数を探すみたいなやつ改造して
  ll l = 0;
  ll r = 1e9;
  ll mid;
  while (r - l > 1)
  {
    mid = (l + r) / 2;
    if (mid <= n)
    {
      l = mid;
    }
    else if (mid > n)
    {
      r = mid;
    }
  }
  return l;
}
ll infinity = 3e18; // long long の上限(約 9.22×10^18）
const int dx[] = {-1, 0, 1, 0, 1, 1, -1, -1};
const int dy[] = {0, 1, 0, -1, 1, -1, 1, -1};
const ulong MASK30 = (1UL << 30) - 1;
const ulong MASK31 = (1UL << 31) - 1;
const ulong MOD = (1UL << 61) - 1;
const ulong MASK61 = MOD;
// mod 2^61-1を計算する関数

ulong CalcMod(ulong x)
{
  // https://qiita.com/keymoon/items/11fac5627672a6d6a9f6
  ulong xu = x >> 61;
  ulong xd = x & MASK61;
  ulong res = xu + xd;
  if (res >= MOD)
    res -= MOD;
  return res;
}
// a*b mod 2^61-1を返す関数(最後にModを取る)
ulong Mul(ulong a, ulong b)
{
  ulong au = a >> 31;
  ulong ad = a & MASK31;
  ulong bu = b >> 31;
  ulong bd = b & MASK31;
  ulong mid = ad * bu + au * bd;
  ulong midu = mid >> 30;
  ulong midd = mid & MASK30;
  return CalcMod(au * bu * 2 + midu + (midd << 31) + ad * bd);
}
ulong base9;
// 基数の初期化 (乱数生成)
static void init_base()
{
  if (base9 != 0)
    return;
  mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
  // 129 以上 MOD-1 未満のランダムな奇数を生成
  uniform_int_distribution<ulong> dist(129, MOD - 2);
  base9 = dist(rng) | 1;
}
const ll baseSize = 2e6;
bool basepow;
vector<ulong> prebase(baseSize);
void preparebase()
{
  init_base();
  prebase[0] = 1;
  rep(i, 1, baseSize) prebase[i] = Mul(prebase[i - 1], base9);
  basepow = true;
}
ulong Add(ulong a, ulong b)
{
  a += b;
  if (a >= MOD)
    a -= MOD;
  return a;
}
ulong Sub(ulong a, ulong b) { return a >= b ? a - b : a + MOD - b; }
struct RollingHash
{
  vector<ulong> h; // h[i] = s[0..i) のハッシュ
  RollingHash(const string &s)
  {
    if (!basepow)
      preparebase();
    int n = s.size();
    h.assign(n + 1, 0);
    rep(i, 0, n)
        h[i + 1] = Add(Mul(h[i], base9), (ulong)(unsigned char)s[i]);
  }
  // 部分文字列 [l, r) のハッシュ
  ulong get(int l, int r) const
  {
    return Sub(h[r], Mul(h[l], prebase[r - l]));
  }
};
// mapは必ずfirstとsecond
long double kyori(ll x1, ll y1, ll x2, ll y2)
{
  ll t = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
  long double a = sqrt(t);
  return a;
}
bool isprime(ll n)
{ // 高速な素数判定
  for (ll i = 2; i * i <= n; i++)
  {
    if (n % i == 0)
    {
      return false;
    }
  }
  return true;
}
long long modpow(long long a, long long n, long long mod)
{ // 高速な累乗の余り
  long long res = 1;
  while (n > 0)
  {
    if (n & 1)
      res = res % mod * a % mod;
    a = a % mod * a % mod;
    n >>= 1;
  }
  return res;
}
const ll mod = 998244353;
// const ll mod = 1000000007;
// ここのmodは組み合わせ計算二も影響が出る
const int MaxSize = 500002;
vector<ll> fac(MaxSize); // n!(mod M)
vector<ll> ifac(MaxSize);
ll comb(ll a, ll b) // 組み合わせの計算初期化してから使う
{
  if (a < 0 || b < 0)
    return 0;
  if (a == 0 && b == 0)
    return 1;
  if (a < b)
    return 0;
  ll cur = ifac[a - b] * ifac[b] % mod;
  // 逆元だから乗算
  return cur * fac[a] % mod;
}
ll comb_large_n(ll a, ll b) // Nのみが大きいときのnCkに対応　計算量はO(K)
{
  if (a < 0 || b < 0 || a < b)
    return 0;
  if (b == 0)
    return 1;

  ll num = 1;
  for (ll i = 0; i < b; i++)
  {
    num = num * ((a - i) % mod) % mod;
  }
  return num * ifac[b] % mod; // 前処理した ifac[b] を再利用！
}
void preparecomb() // 3e5まで対応 階乗をあらかじめ計算しておく
{
  fac[0] = 1;
  ifac[0] = 1;
  rep(i, 0, MaxSize)
  {
    fac[i + 1] = fac[i] * (i + 1) % mod;
    ifac[i + 1] = ifac[i] * modpow(i + 1, mod - 2, mod) % mod;
  }
}
struct edge
{
  ll cost;
  ll u;
  ll v;
  edge(ll a, ll b, ll c) : cost(a), u(b), v(c) {}
};
struct edgecompare
{
  bool operator()(const edge &a, const edge &b) const
  {
    return a.cost > b.cost; // min-heapにするので不等号は>向き
  }
};
void cincout()
{
  ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  cout << fixed << setprecision(15);
}
vector<ll> normalize(const string &str)
{
  map<ll, ll> char_to_id;
  vector<ll> res;
  int next_id = 0;

  for (char c : str)
  {
    if (!char_to_id.count(c))
    {
      char_to_id[c] = next_id++;
    }
    res.push_back(char_to_id[c]);
  }
  return res;
}
bool isIsomorphic(const string &s, const string &t) // 文字列が同値がどうか判定する
{
  if (s.size() != t.size())
    return false;
  // 正規化した数列が一致するか比較
  return normalize(s) == normalize(t);
}
vector<ll> optimizedSieve(ll n)
{
  vector<ll> primes;
  vector<bool> prime(n + 1, true);
  prime[0] = prime[1] = false;
  for (ll p = 2; p * p <= n; p++)
  {
    if (prime[p])
    {
      for (ll i = p * p; i <= n; i += p)
        prime[i] = false;
    }
  }
  for (ll p = 2; p <= n; p++)
  {
    if (prime[p])
      primes.push_back(p);
  }
  return primes;
}
char trans(char a)
{
  return a ^ 32;
}
vector<ll> vals(const vector<ll> &a) // 座圧　出来てるかは不明　log n
{
  auto b = a;
  sort(nall(b));
  b.erase(unique(nall(b)), b.end());
  vector<ll> ans(a.size());
  rep(i, 0, a.size())
  {
    ans[i] = lower_bound(nall(b), a[i]) - b.begin();
  }
  return ans;
}
vector<P> mergesegment(vector<P> &d) // 重複がないように区間を結合するやつ mexとかやりたいならライブラリを引っ張ろう
{
  if (d.empty())
    return d;
  vector<P> qq;
  sort(nall(d));
  P now = {-1, -1};
  bool before = false;
  rep(j, 0, d.size())
  {
    if (now.second >= d[j].first)
    {
      before = true;
      now.second = max(now.second, d[j].second);
    }
    else
    {
      if (now.first != -1)
      {
        qq.push_back(now);
        before = false;
      }
      now = d[j];
    }
  }
  qq.push_back(now);
  return qq;
}
struct Tri
{
  // 考え方としてはtrie木を作る
  // 木構造をDFSでなんやかんやする
  struct Node
  {
    map<char, int> to; // 次の文字への遷移（枝）
    int cnt;           // ここでピタッと終わる文字列の個数
    Node() : cnt(0) {}
  };
  vector<Node> d;
  Tri() : d(1) {}; // 0番目は根となるノード　DFSとかをするときに除外しないといけない
  void add(const string &s)
  {
    int v = 0;
    for (char c : s)
    {
      if (!d[v].to.count(c))
      {
        d[v].to[c] = d.size();
        d.push_back(Node());
      }
      v = d[v].to[c];
    }
    d[v].cnt++;
  }
  ll ans;
  int dfs(int v)
  {
    int res = d[v].cnt;
    for (auto p : d[v].to)
    {
      res += dfs(p.second);
    }
    if (v)
      ans += res * ll(res - 1) / 2;
    return res;
  }
  ll solve()
  {
    ans = 0;
    dfs(0);
    return ans;
  }
};
ll getroot(const vector<vector<ll>> &g)
{
  vector<ll> dist(g.size(), -1);
  dist[0] = 0;
  auto f = [&](auto f, ll v, ll cnt) -> void
  {
    cnt++;
    for (auto a : g[v])
    {
      if (dist[a] != -1)
        continue;
      dist[a] = cnt;
      f(f, a, cnt);
    }
    return;
  };
  f(f, 0, 0);
  auto u = max_element(nall(dist)) - dist.begin();
  return u;
}
tuple<vector<ll>, vector<ll>, vector<ll>> euler_tour(vector<vector<ll>> &gragh, const ll &root)
{
  ll N = gragh.size();
  // 根が分かっているときに使える
  //  Euler Tour
  vc<ll> in(N), out(N), tour;
  {
    auto dfs = [&](auto &dfs, int v, int par) -> void
    {
      in[v] = tour.size();
      tour.emplace_back(v);
      for (int w : gragh[v])
      {
        if (w != par)
          dfs(dfs, w, v);
      }
      out[v] = tour.size();
    };
    dfs(dfs, root, -1);
  }
  return {in, out, tour};
}
vector<ll> dijkstra(const vector<vector<pair<int, ll>>> &g, int s)
{
  vector<ll> dist(g.size(), LLONG_MAX);
  priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
  dist[s] = 0;
  pq.push({0, s});
  while (!pq.empty())
  {
    auto [d, v] = pq.top();
    pq.pop();
    if (dist[v] < d)
      continue;
    for (auto [u, w] : g[v])
    {
      if (dist[u] > d + w)
      {
        dist[u] = d + w;
        pq.push({dist[u], u});
      }
    }
  }
  return dist;
}
//    問題を言い換えてみる？
//    何が分かればいい？
//    どう更新するか
// 大事なことなので何度も言います.優先度付きキューを使うときは降順昇順、値の順番に気を付ける・・
#include <atcoder/all>
using namespace atcoder;
using mint = modint998244353;
struct F
{
  ll sum;
  ll len;
};
ll op(ll a, ll b)
{
  return min(a, b);
}
ll e()
{
  return infinity;
}
ll mapping(ll f, ll x)
{
  return f + x;
}
ll composition(ll f, ll g)
{
  return f + g;
}
ll id()
{
  return 0;
}

int main()
{
  ll n, k;
  cin >> n >> k;
  preparecomb();
  vector<mint> a(n);
  mint s = 0;
  rep(i, 0, n)
  {
    ll c;
    cin >> c;
    a[i] = c;
    s += c;
  }
  mint conbi;
  mint conbi2;
  if (k >= 2)
  {
    conbi = comb(n - 1, k - 1);
    conbi2 = comb(n - 2, k - 2);
  }
  else if (k >= 1)
  {
    conbi = comb(n - 1, k - 1);
    conbi2 = 0;
  }
  mint ans = 0;
  mint s2 = 0;
  rep(i, 0, n)
  {
    s2 += a[i] * a[i];
  }
  ans += s2 * conbi;
  ans += (s * s - s2) * conbi2;
  // ここを高速化したい
  cout << ans.val() << endl;
}
