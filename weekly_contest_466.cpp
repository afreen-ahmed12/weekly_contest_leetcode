###solution1

##Q1. Minimum Operations to Equalize Array

class Solution {
public:
    int minOperations(vector<int>& nums) {
        for(auto x : nums) {
            if(x != nums[0]) return 1;
        } 
        return 0;
    }
};  

##Q2. Minimum Operations to Transform String

class Solution {
public:
    int minOperations(string s) {
        int mx=0;
        for (auto &x : s){
            if(x=='a') continue;
            mx = max(int ('z'- x )+1,mx);
        }
        return mx;
    }
};



###Q3. Count Bowl Subarrays



class Solution {
vector<int> next_geq_right(vector<int>& a) {
	int n = a.size();
	vector<int> res(n, -1);
	stack<int> st;
	for(int i = 0; i < n; i++) {
		while(!st.empty() && a[i] >= a[st.top()]) { res[st.top()] = i; st.pop(); }
		st.push(i);
	}
	return res;
}
vector<int> next_geq_left(vector<int>& a) {
	int n = a.size();
	vector<int> res(n, -1);
	stack<int> st;
	for(int i = 0; i < n; i++) {
		while(!st.empty() && a[st.top()] < a[i]) st.pop();
		if(!st.empty()) res[i] = st.top();
		st.push(i);
	}
	return res;
}
public:
    long long bowlSubarrays(vector<int>& nums) {
        int n = nums.size();
        vector<int> geql = next_geq_left(nums), geqr = next_geq_right(nums);

        int cnt = 0;
        for(int i = 0; i < n; i++) {
            if(geql[i] != -1 && geql[i] < i - 1) cnt++;
            if(geqr[i] != -1 && nums[i] != nums[geqr[i]] && geqr[i] > i + 1) cnt++;
        }
        return cnt;
    }
};




###Q4. Count Binary Palindromic Numbers


class Solution {
    using ll = long long;
public:
    ll palin(ll val, int b) {
        val = (val<<(b/2));
        for(int i = 0; i < b/2; i++) {
            if(val & (1ll<<(b-i-1))) val |= (1ll<<i);
        }
        return val;
    }
    int countBinaryPalindromes(ll n) {
        if(n == 0) return 1;
        int bc = 64 - __builtin_clzll(n);
        int ans = 1;

        for(int b = 1; b < bc; b++) {
            ans += (1ll<<((b+1)/2))/2;
        }

        ll l = (1ll << ((bc-1)/2)), r = (1ll << ((bc+1)/2))-1, best = 0;
        while(l <= r) {
            ll mid = (l+r)/2;
            if(palin(mid, bc) <= n) {
                best = max(best, mid);
                l = mid + 1;
            }
            else r = mid - 1;
        }

        if(best) ans += best - (1ll << ((bc-1)/2)) + 1;
        
        return ans;
    }
};


