#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct Robot{
    ll pos;int id;
    bool operator<(const Robot& other) const{
        return pos<other.pos;}};
int NN;
vector<int> tree;
void build(int node, int start, int end, vector<int>& ids){
    if (start==end){
        tree[node]=ids[start];
        return;}
    int mid = (start+end)/2;
    build(2*node, start, mid, ids);build(2*node+1, mid+1, end, ids);tree[node]=max(tree[2*node], tree[2*node+1]);}
int find_rightmost(int node, int nstart, int nend, int ql, int qr, int val){
    if (ql>nend || qr<nstart || tree[node]<=val) return-1;
    if (nstart==nend) return nstart;
    int mid=(nstart+nend)/2;int res=find_rightmost(2*node+1, mid+1, nend, max(ql, mid+1), qr, val);
    if (res!=-1) return res;
    return find_rightmost(2*node, nstart, mid, ql, min(qr, mid), val);}
int main(){
    ifstream fin("pay_off_input.txt");
    ofstream fout("testoutput.txt");
    int T;
    fin>>T;
    tree.resize(4*200005);
    for (int cas=1; cas<=T; cas++) {
        int N,Q;ll L;
        fin >>N>>Q>>L;
        vector<ll> X(N+1);
        for (int i=1; i<=N; i++) fin>>X[i];
        vector<Robot> sorted_robs(N);
        for (int i=0; i<N; i++) {
            sorted_robs[i].pos=X[i+1];sorted_robs[i].id=i+1;}
        sort(sorted_robs.begin(), sorted_robs.end());
        vector<int> sorted_ids(N);
        for (int i=0; i<N; i++) sorted_ids[i] = sorted_robs[i].id;
        NN=N;
        build(1,0,N-1, sorted_ids);
        set<ll> walls;
        walls.insert(1);walls.insert(L);
        ll total_sum=0;
        for (int q=0; q<Q; q++){
            int type;
            fin>>type;
            if (type==1){
                ll x;fin>>x;walls.insert(x);
            } else{
                int rr;ll ss;fin>>rr>>ss;ll xr=X[rr];
                auto it=walls.lower_bound(xr);ll bb=*it;it--;
                ll aa=*it;ll ww=bb-aa;ll pr=xr-aa;ll perr=2LL*ww;ll kkk=ss/perr;ll mmm=ss%perr;Robot low_dummy={aa+1,-1};
                auto lit = lower_bound(sorted_robs.begin(), sorted_robs.end(), low_dummy);
                int ll_idx = lit - sorted_robs.begin();Robot high_dummy = {bb, -1};
                auto hit = lower_bound(lit, sorted_robs.end(), high_dummy);
                int hh_idx = hit - sorted_robs.begin();
                if (ll_idx >= hh_idx) {
                    total_sum += 0;continue;}
                vector<pair<double, int>> candidates;
                ll upper_1 = 2LL * mmm-pr;
                if (upper_1 >= 1){
                    ll uu1 = min(upper_1, ww - 1);
                    ll target_pos1 = aa + uu1;Robot tp1 = {target_pos1 + 1, -1};
                    auto it1 = lower_bound(sorted_robs.begin() + ll_idx, sorted_robs.begin() + hh_idx, tp1);
                    int right1 = (it1 - sorted_robs.begin()) - 1;
                    if (right1 >= ll_idx) {
                        int k1 = find_rightmost(1, 0, NN - 1, ll_idx, right1, rr);
                        if (k1 != -1) {
                            ll pj = sorted_robs[k1].pos - aa;double rho = 0.5 * (pr + pj);
                            if (rho <= mmm + 1e-10) {
                                double tt = kkk * 1.0 * perr + rho;candidates.push_back({tt, sorted_robs[k1].id});}}}}
                double temp2 = mmm - 1.0 * ww;
                if (temp2 >= 0) {
                    double temp_upper = 2.0 * temp2 - pr;ll upper_2 = (ll)floor(temp_upper + 1e-10);
                    if (upper_2 >= 1) {
                        ll uu2 = min(upper_2, ww - 1LL);ll target_pos2 = aa + uu2;
                        Robot tp2 = {target_pos2 + 1, -1};
                        auto it2 = lower_bound(sorted_robs.begin() + ll_idx, sorted_robs.begin() + hh_idx, tp2);
                        int right2 = (it2 - sorted_robs.begin()) - 1;
                        if (right2 >= ll_idx) {
                            int k2 = find_rightmost(1, 0, NN - 1, ll_idx, right2, rr);
                            if (k2 != -1) {
                                ll pj = sorted_robs[k2].pos - aa;double rho = 0.5 * (pr + pj) + ww;
                                if (rho <= mmm + 1e-10) {
                                    double tt = kkk * 1.0 * perr + rho;candidates.push_back({tt, sorted_robs[k2].id});}}}}}
                int right_max = hh_idx - 1;
                if (right_max >= ll_idx && kkk > 0) {
                    int kf = find_rightmost(1, 0, NN - 1, ll_idx, right_max, rr);
                    if (kf != -1) {
                        ll pj = sorted_robs[kf].pos - aa;double rho = 0.5 * (pr + pj) + ww;double tt = (kkk - 1.0) * perr + rho;
                        if (tt <= ss + 1e-10 && tt >= 0) {
                            candidates.push_back({tt, sorted_robs[kf].id});}}}
                if (candidates.empty()){
                    total_sum += 0;
                } else {
                    sort(candidates.begin(), candidates.end(), [](const pair<double, int>& a, const pair<double, int>& b) {
                        if (fabs(a.first - b.first) > 1e-9) return a.first < b.first;return a.second < b.second;});
                    total_sum += candidates.back().second;}}}
        fout << "Case #" << cas << ": " << total_sum << endl;}
    fin.close();fout.close();
    return 0;}
