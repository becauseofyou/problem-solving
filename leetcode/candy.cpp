class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = (int)ratings.size();
        vector <int> a(n);
        a[0] = 1;
        for (int i = 1; i < n; i++) {
            if (ratings[i] <= ratings[i - 1]) {
                a[i] = 1;
            }
            if (ratings[i] > ratings[i - 1]) {
                a[i] = a[i - 1] + 1;
            }
        }

        for (int i = n - 2; i >= 0; i--) {
            if (ratings[i] > ratings[i + 1]) {
                a[i] = max(a[i], a[i + 1] + 1);
            }
        }
        return accumulate(a.begin(), a.end(), 0);
    }
};
