QUESTION1  RESTORE FISHING ORDER

class Solution {
public:
    vector<int> recoverOrder(vector<int>& order, vector<int>& friends) {
        int n = order.size();

        vector <bool> f(n+1);
        vector <int> ans;
        for(int i = 0 ; i < friends.size() ; i++) f[friends[i]] = true;
        for(int i = 0 ; i < order.size() ; i++) if(f[order[i]]) ans.push_back(order[i]);

        return ans;
    }
};



QUESTION2    Balanced K-Factor Decomposition



class Solution {
public:
    static const int N = 1e5+1;
    vector <int> div;
    vector <int> ans;
    int K;
    int val = 1e9;
    void brute(int n, int k, int last, vector <int> &cur)
    {
        if(k == 0)
        {
            vector <int> temp = cur;
            int ctemp = temp[temp.size() - 1] - temp[0];
            if(ctemp <= val)
            {
                val = ctemp;
                ans = temp;
            }
            return;
        }
        if(k == 1)
        {
            if(n < last) return;
            cur.push_back(n);
            brute(1, 0, n, cur);
            cur.pop_back();
            return ;
        }
        int ind = lower_bound(div.begin(), div.end(), last) - div.begin();
        for(int i = ind ; i < div.size() ; i++)
        {
            int d = div[i];
            if(n % d != 0) continue;
            cur.push_back(d);
            brute(n/ d, k-1, d, cur);
            cur.pop_back();
        }
        
    }
    vector<int> minDifference(int n, int k) {

        K  = k;
        for(int i = 1 ; i*i <= n ; i++) 
        {
            if(i*i == n)
            {
                div.push_back(i);
                continue;
            }
            if((n % i) == 0)
            {
                div.push_back(i);
                div.push_back(n/i);
            }
        }

        sort(div.begin(), div.end());

        vector <int> cur = {};
        brute(n, k, 0, cur);

        return ans;
    }
};




QUESTION3   Maximum Product of Two Integers With No Common Bits



Q4. Sum of Beautiful Subsequences


class Solution {
public:
    static const int MOD = 1000000007;
    class FenwickTree 
    {
    private:
        vector<long long> bit;
        int size;
    public:
        FenwickTree(int n) 
        {
            size = n;
            bit.assign(n + 1, 0);
        }
        void update(int idx, long long delta) 
        {
            for (; idx <= size; idx += idx & -idx) 
            {
                bit[idx] = (bit[idx] + delta) % MOD;
            }
        }
        long long query(int idx) {
            long long sum = 0;
            for (; idx > 0; idx -= idx & -idx) 
            {
                sum = (sum + bit[idx]) % MOD;
            }
            return sum;
        }
    };
    int totalBeauty(vector<int>& nums) 
    {
        int n = nums.size();
        int mx = *max_element(nums.begin(), nums.end());
        vector<vector<int>> seq(mx+1);
        for(int x: nums)
        {
            for(int d=1; 1LL*d*d<=x; ++d)
            {
                if(x%d==0){
                    seq[d].push_back(x/d);
                    int d2 = x/d;
                    if(d2!=d) seq[d2].push_back(x/d2);
                }
            }
        }
        vector<long long> exact(mx+1,0);
        long long ans = 0;
        for(int g=mx; g>=1; g--)
        {
            auto &v = seq[g];
            if(!v.empty())
            {
                vector<int> comp = v;
                sort(comp.begin(), comp.end());
                // comp.erase(unique(comp.begin(), comp.end()), comp.end());
                FenwickTree bit((int)comp.size());
                for(int val: v)
                {
                    int r = int(lower_bound(comp.begin(), comp.end(), val) - comp.begin()) + 1;
                    long long cur = (1 + bit.query(r-1)) % MOD;
                    bit.update(r, cur);
                }
                long long cntg = bit.query((int)comp.size());
                long long sub = 0;
                for(int k=g*2; k<=mx; k+=g)
                {
                    sub += exact[k];
                    if(sub>=MOD) sub-=MOD;
                }
                long long ex = (cntg - sub) % MOD;
                if(ex<0) ex += MOD;
                exact[g] = ex;
                ans = (ans + ex * g) % MOD;
            }
        }
        return (int)ans;
    }
};


