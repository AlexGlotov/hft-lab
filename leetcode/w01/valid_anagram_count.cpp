class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.size() != t.size())
            return false;

        vector<int> abc(26);
        for (int i = 0; i < s.size(); i++)
            abc[s[i] - 'a']++;
        for (int i = 0; i < t.size(); i++)
            abc[t[i] - 'a']--;
        for (int i = 0; i < 26; i++)
            if (abc[i] != 0) return false;
        return true;
    }
};
