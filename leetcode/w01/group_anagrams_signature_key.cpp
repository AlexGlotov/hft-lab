class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> dict;
        for (const auto& str : strs)
        {
            string key(26, '0');
            for (const auto& lit : str)
                key[lit - 'a']++;
            dict[key].push_back(str);
        }

        vector<vector<string>> ans;
        for (const auto& [key, value] : dict)
            ans.push_back(value);
        return ans;
    }
};
