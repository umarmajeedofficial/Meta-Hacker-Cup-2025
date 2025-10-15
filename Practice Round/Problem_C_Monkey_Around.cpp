#include <bits/stdc++.h>
using namespace std;
int main() {
    freopen("monkey_around_input.txt", "r", stdin);
    freopen("testoutput.txt", "w", stdout);
    int T;
    scanf("%d",&T);
    for (int cas=1; cas<=T; cas++) {
        int n;
        scanf("%d",&n);
        vector<int> a(n);
        for (int i=0; i<n; i++) {
            scanf("%d", &a[i]);}
        vector<int> ks,rs;
        int pos=0;
        while (pos<n) {
            int m=a[pos];
            int len1=1;
            int jj=pos+1;
            while (jj<n && a[jj]==a[jj-1]+1) {
                len1++;
                jj++;}
            int tot_len;
            if (m==1) {
                tot_len=len1;
            } else{
                tot_len=0;
                if (jj<n && a[jj]==1) {
                    int sec_len = m-1;
                    bool ok=true;
                    int sec_pos=jj;
                    for (int t=1; t<sec_len; t++) {
                        sec_pos++;
                        if (sec_pos >= n || a[sec_pos] != t+1) {
                            ok = false;
                            break;}}
                    if (ok && (sec_len==0 || sec_pos==jj+sec_len-1)) {
                        tot_len = len1+sec_len;}}}
            ks.push_back(tot_len);
            rs.push_back(m-1);
            pos += tot_len;}
        int R = ks.size();
        vector<long long> ss(R);
        ss[R-1] = rs[R-1];
        for (int i=R-2; i>=0; i--) {
            long long target = ss[i+1];
            long long resd = rs[i];
            long long md = ks[i];
            long long s;
            if (resd>=target) {
                s = resd;
            }else{
                long long diff=target-resd;
                long long t=(diff+md-1LL)/md;
                s=resd+t*md;}
            ss[i]=s;}
        long long total_S=ss[0];
        long long M=(long long)R+total_S;
        printf("Case #%d: %lld\n",cas,M);
        for (int ii=0; ii<R; ii++) {
            printf("1 %d\n", ks[ii]);
            long long num_twos;
            if (ii<R-1) {
                num_twos = ss[ii]-ss[ii+1];
            } else {
                num_twos = ss[ii];}
            for (long long tt=0; tt<num_twos; tt++) {
                printf("2\n");}}}
    return 0;}
