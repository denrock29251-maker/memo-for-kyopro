#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif
#include <atcoder/all>
using namespace atcoder;
using mint = modint998244353;
using mint2 = modint1000000007;
#define rep(i, l, r) for(ll i = (l); i < (r); i++)
#define drep(i, l, r) for(long long i = (r) - 1; i >= l; i--)
#define nall(a) a.begin(), a.end()
using ll = long long;
//mapはマジで重いので制約が軽かったらvectorつかお!!
//inlineはマジで軽くなる
inline void add(ll i,vector<ll>&num,ll &len){
  num[i]++;
  if(num[i]%2==0){
    len++;
  }
}
inline void delete_(ll i,vector<ll>&num,ll &len){
  num[i]--;
  if(num[i]%2==1){
    len--;
  }
}
int main()
{
  ll n,q;
  cin>>n;
  vector<ll>a(n);
  rep(i,0,n)cin>>a[i];
  cin>>q;//クエリを受け取る位置は適宜変える必要がある
  ll B = max(1ll,(ll)(n/sqrt((double)q)));//幅
  //もしかしたら(n/sqrt(double)2*2.0/3.0)にすると定数倍早くなるかもしれない　
  const ll blocks = n/B+1;//個数
  vector<vector<tuple<ll,ll,ll>>>qs(blocks);
  rep(i,0,q){
    ll l,r;
    cin>>l>>r;
    //閉区間
    l--,r--;
    qs[l/B].push_back(make_tuple(i,l,r));
  }
  vector<ll>ans(q);
  ll left = 0,right = 0;
  vector<ll>num(2<<17);
  ll len = 0;
  rep(ind,0,blocks){
    if(ind%2==0){
      sort(qs[ind].rbegin(),qs[ind].rend(), [](const tuple<ll,ll,ll>& a, const tuple<ll,ll,ll>& b) {return get<2>(a) < get<2>(b);});
    }
    else{
        sort(qs[ind].begin(),qs[ind].end(), [](const tuple<ll,ll,ll>& a, const tuple<ll,ll,ll>& b) {return get<2>(a) < get<2>(b);});
    }
    for(auto [idx,l,r]:qs[ind]){
      while(right<=r){
        add(a[right],num,len);
        right++;
      }
      while(left>l){
        left--;
        add(a[left],num,len);
      }
      while(right>r+1){
        right--;
        delete_(a[right],num,len);
      }
      while(left<l){
        delete_(a[left],num,len);
        left++;
      }
      ans[idx] = len;
    }
  }
  rep(i,0,q){
    cout<<ans[i]<<'\n';
  }
}