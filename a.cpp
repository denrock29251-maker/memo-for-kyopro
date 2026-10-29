// https://github.com/denrock29251-maker/memo-for-kyopro/tree/main
#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;
using mint = modint998244353;
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
struct point
{
    ll x, y;
};
long long cross(const point &a, const point &b)
{
    return a.x * b.y - a.y * b.x;
}
ll dot(ll ax, ll ay, ll bx, ll by)
{
    // ベクトルの内積を求める
    return ax * bx + ay * by;
    // これが0だったら垂直
}
// bool ispoint(ll px, ll py, ll qx, ll qy, ll rx, ll ry, ll sx, ll sy)
// {
//   ll bigx = px - qx;
//   ll bigy = py - qy;
//   ll smallx = rx - sx;
//   ll smally = ry - sy;
//   ll vec = cross(bigx, bigy, smallx, smally);
//   if (vec != 0)
//     return true;
//   else
//   {
//     ll tx = rx - px;
//     ll ty = ry - py;
//     if (cross(bigx, bigy, tx, ty) == 0)
//       return true;
//     return false;
//   }
//   // 2直線が交点を持つかを判定するヨ
// }
bool isout_grid(ll i, ll j, ll h, ll w)
{
    // グリッド内ならfalseグリッド外ならtrue
    return (!(0 <= i && i < h && 0 <= j && j < w));
}
inline void Yes(bool a)
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
using segmap_var = mint; // これは適宜変更する
struct SegmentMap
{
    struct N
    {
        ll r;
        ll num;
    };
    map<ll, N> m; // 区間の左端 -> 右端
    ll val;
    bool merge_adjacent;
    // merge_adjacent = true なら [l, c] と [c+1, r] を1つの区間にまとめる
    SegmentMap() : m(), val(0), merge_adjacent(true) {};
    auto begin() const { return m.begin(); }
    auto end() const { return m.end(); }
    size_t size() const { return m.size(); }
    bool empty() const { return m.empty(); }
    // i を含む区間を指すイテレータ。無ければ m.end()
    auto get(ll i) const
    {
        auto it = m.upper_bound(i);
        if (it == m.begin())
            return m.end();
        --it;
        if (it->second.r >= i)
            return it;
        return m.end();
    }
    // i と j が同じ区間に属しているか
    bool same(ll i, ll j) const
    {
        auto a = get(i);
        return a != m.end() && a == get(j);
    }
    // 区間 [l, r] を追加する (l <= r)。重なる区間(と、設定によって隣接する区間)は併合される
    segmap_var insert(ll l, ll r)
    {
        return insert(l, r, 0, [](ll l, ll r, ll num)
                      { return 0; });
    }
    // 状況に応じて関数や第三引数を入れられる挿入して増えた量を返す
    template <class Func>
    segmap_var insert(ll l, ll r, ll num, const Func &func)
    {
        segmap_var cur = 0;
        ll d = 0;
        if (merge_adjacent)
        {
            d = 1;
        }
        auto it = m.upper_bound(l);
        if (it != m.begin())
        {
            auto p = prev(it);
            if (p->second.r + d >= l)
            {
                l = p->first;
                r = max(r, p->second.r);
                val -= p->second.r - p->first + 1;
                cur -= func(p->first, p->second.r, p->second.num);
                it = m.erase(p); // it は元の it と同じ要素を指す
            }
        }
        while (it != m.end() && it->first <= r + d)
        {
            r = max(r, it->second.r);
            val -= it->second.r - it->first + 1;
            cur -= func(it->first, it->second.r, it->second.num);
            it = m.erase(it);
        }
        val += (r - l + 1);
        cur += func(l, r, num);
        m[l] = N{r, num};
        return -cur;
    }
    // 全ての区間から [l, r] と重なる部分を削除する (l <= r)
    segmap_var remove(ll l, ll r)
    {
        return remove(l, r, 0, [](ll l, ll r, ll num)
                      { return 0; });
    }
    // 消される量を返す
    template <class Func>
    segmap_var remove(ll l, ll r, ll num, const Func &func)
    {
        segmap_var cur = 0;
        // l より左から始まり、l にかかっている区間を先に処理する
        auto it = m.upper_bound(l);
        if (it != m.begin())
        {
            auto p = prev(it);
            // *p.secondだとだめらしい
            if (p->second.r >= l)
            {
                ll pl = p->first, pr = p->second.r;
                val -= p->second.r - p->first + 1;
                cur -= func(p->first, p->second.r, p->second.num);
                ll v = p->second.num;
                m.erase(p);
                if (pl < l)
                {
                    m[pl] = N{l - 1, v};
                    val += (l - 1) - pl + 1;
                    cur += func(pl, l - 1, v);
                }
                if (pr > r)
                {
                    m[r + 1] = N{pr, v};
                    val += pr - (r + 1) + 1;
                    cur += func(r + 1, pr, v);
                    return cur;
                }
            }
        }
        // l 以上 r 以下から始まる区間
        it = m.lower_bound(l);
        while (it != m.end() && it->first <= r)
        {
            ll cr = it->second.r;
            val -= it->second.r - it->first + 1;
            cur -= func(it->first, it->second.r, it->second.num);
            ll v = it->second.num;
            it = m.erase(it);
            if (cr > r)
            {
                m[r + 1] = N{cr, v};
                val += cr - (r + 1) + 1;
                cur += func(r + 1, cr, v);
                break;
            }
        }
        return cur;
    }
    ll mex(ll x = 0)
    {
        auto p = m.upper_bound(x);
        if (p == m.begin())
        {
            return x;
        }
        --p;
        if (p->second.r >= x && p->first <= x)
        {
            return p->second.r + 1;
        }
        else
        {
            return x;
        }
    }
    void debug()
    {
        for (auto p : m)
        {
            cout << '[' << p.first << ',' << p.second.r << ']';
        }
        cout << endl;
    }
    void debug_with_value()
    {
        for (auto p : m)
        {
            cout << '[' << p.first << ',' << p.second.r << ', 値は' << p.second.num << ']';
        }
        cout << endl;
    }
};
template <typename Func>
P binary(ll ok, ll ng, const Func &func)
{ // n以下の数を探すみたいなやつ改造して
    ll mid;
    while (ok + 1 < ng)
    {
        mid = (ok + ng) / 2;
        if (func(mid))
        {
            ok = mid;
        }
        else
        {
            ng = mid;
        }
    }
    return P{ok, ng};
}
ll infinity = 3e18; // long long の上限(約 9.22×10^18）
const int dx[] = {-1, 0, 1, 0, 1, 1, -1, -1};
const int dy[] = {0, 1, 0, -1, 1, -1, 1, -1};
const ulong MOD = (1ULL << 61) - 1;
ulong CalcMod(ulong x)
{
    ulong
        res = (x >> 61) + (x & MOD);
    if (res >= MOD)
        res -= MOD;
    return res;
}

ulong Mul(ulong a, ulong b)
{
    __uint128_t t = (__uint128_t)a * b;
    ulong res = (ulong)(t >> 61) + (ulong)(t & MOD);
    if (res >= MOD)
        res -= MOD;
    return res;
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
vector<ll> dijkstra(const vector<vector<pair<ll, ll>>> &g, int s)
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
int keta(ll t)
{
    return to_string(t).size();
}
map<ll, ll> disiver(ll k) // 素因数分解
{
    map<ll, ll> m;
    if (k <= 1)
    {
        m[k]++;
        return m;
    }
    while (k > 1)
    {
        bool t = true;
        for (ll i = 2; i * i <= k; i++)
        {
            if (k % i == 0)
            {
                k /= i;
                m[i]++;
                t = false;
                break;
            }
        }
        if (!t)
            continue;
        m[k]++;
        k /= k;
    }
    return m;
}
// atcoder公式解説より
bool cmp_arg(const point &a, const point &b)
{
    int asyougen = (a.y < 0 || (a.y == 0 && a.x < 0));
    int bsyougen = (b.y < 0 || (b.y == 0 && b.x < 0));
    if (asyougen != bsyougen)
        return asyougen < bsyougen;
    return cross(a, b) > 0;
}
void argument_sort(vector<point> &points)
{
    sort(points.begin(), points.end(), cmp_arg);
}
//    問題を言い換えてみる？
//    何が分かればいい？
//    どう更新するか
// 大事なことなので何度も言います.優先度付きキューを使うときは降順昇順、値の順番に気を付ける・・
// #include <atcoder/all>
// using namespace atcoder;
// using mint = modint998244353;
struct F
{
    ll x;
    ll cnt;
};
F op(F a, F b)
{
    return F{a.x + b.x, a.cnt + b.cnt};
}
F e()
{
    return F{0, 0};
}
struct s
{
    mint a, b;
};
F mapping(s f, F x)
{
    return F{0, 0};
}
s composition(s f, s g)
{
    return s{f.a + g.a, f.b + g.b};
}
s id()
{
    return s{0, 0};
}
ll target;
bool fun(ll t)
{
    return t < target;
}
int main()
{
    ll n, q;
    cin >> n >> q;
    vector<ll> a(n);
    rep(i, 0, n) cin >> a[i], a[i]--;
    const int D = 30;
    vector<vector<ll>> to(D, vector<ll>(n));
    vector<vector<ll>> sum(D, vector<ll>(n));
    rep(i, 0, n) to[0][i] = a[i];
    rep(i, 0, n) sum[0][i] = i + 1; // jにおける2^k個先の状態を取り出す
    rep(i, 0, D - 1) rep(j, 0, n)
    {
        to[i + 1][j] = to[i][to[i][j]];
        sum[i + 1][j] = sum[i][j] + sum[i][to[i][j]];
    }
    while (q--)
    {
        ll t, b;
        cin >> t >> b;
        b--;
        ll ans = 0;
        rep(i, 0, D) if ((t >> i & 1))
        {
            ans += sum[i][b];
            b = to[i][b];
        }
        cout << ans << endl;
    }
}
