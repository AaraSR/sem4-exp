class Solution {
public:
    long long maximumSubarraySum(vector<int>& nums, int k) {
        int i = 0;
        int j = k - 1;
        int sum = 0, max_sum = 0;

        for (auto it = nums.begin(), it != nums.end() - (k - 1), ++it) {
            sum = sum - nums[i++] + nums[++j];
        }
    }
};