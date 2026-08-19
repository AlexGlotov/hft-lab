class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> dict;
        for (int i = 0; i < strs.size(); i++)
        {
            string lit = strs[i];
            sort(lit.begin(), lit.end());
            dict[lit].push_back(strs[i]);
        }
        vector<vector<string>> ans;
        for (const auto& [key, value] : dict)
            ans.push_back(value);
        return ans;
    }
};
