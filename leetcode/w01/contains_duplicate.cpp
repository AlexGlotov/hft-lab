class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> nums_set;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums_set.find(nums[i]) != nums_set.end())
            {
                return true;
            } else {
                nums_set.insert(nums[i]);
            }
        }
        return false;
    }
};
