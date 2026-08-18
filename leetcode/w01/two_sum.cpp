class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> search_nums;
        for (int i = 0; i < nums.size(); i++){
            if (search_nums.find(target - nums[i]) != search_nums.end())
            {
                return {search_nums[target - nums[i]], i};
            } else {
                search_nums[nums[i]] = i;
            }
        }
        return {};
    }
};
