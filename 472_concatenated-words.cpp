// Memory Limit exceeded
// for case ["a", "aa", "aaa", ...]
// trie is time consuming than hash on some special cases
class Solution {
private:
    class TrieTree {
    private:
        class TrieNode {
        public:
            TrieNode* next[26];
            bool have;
        public:
            TrieNode() {
                for (int i = 0; i != 26; ++i)
                    this->next[i] = NULL;
                this->have = false;
            }
        };
    private:
        TrieNode* root;
    public:
        TrieTree() {
            this->root = new TrieNode();
        }
        void insert(const string& s) {
            TrieNode* cur = root;
            for (auto c : s) {
                int idx = c - 'a';
                if (!cur->next[idx])
                    cur->next[idx] = new TrieNode();
                cur = cur->next[idx];
            }
            cur->have = true;
        }
        bool search(const string& s) {
            TrieNode* cur = root;
            for (auto c : s) {
                int idx = c - 'a';
                if (!cur->next[idx]) return false;
                cur = cur->next[idx];
            }
            return cur->have;
        }
    };
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        vector<string> result;
        TrieTree* tree = new TrieTree();
        int minLen = INT_MAX, maxLen = 0;
        for (auto word : words) {
            minLen = min(minLen, (int)word.size());
            maxLen = max(maxLen, (int)word.size());
            tree->insert(word);
        }
        for (auto word : words) {
            if (word.size() == minLen) continue;
            vector<bool> dp(word.size() + 1, false);
            dp[0] = true;
            for (int i = 1; i != word.size() + 1; ++i) {
                for (int j = minLen, pos = i - j; j != maxLen + 1 && pos >= 0; ++j, --pos) {
                    if (dp[pos] && tree->search(word.substr(pos, j))) {
                        dp[i] = true;
                        if (i == word.size() && pos != 0) result.push_back(word);
                        break;
                    }
                }
            }
        }
        return result;
    }
};

// hash set is ok
class Solution {
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        vector<string> result;
        int minLen = INT_MAX, maxLen = 0;
        unordered_set<string> st;
        for (auto word : words) {
            minLen = min(minLen, (int)word.size());
            maxLen = max(maxLen, (int)word.size());
            st.insert(word);
        }
        for (auto word : words) {
            if (word.size() == minLen) continue;
            vector<bool> dp(word.size() + 1, false);
            dp[0] = true;
            for (int i = 1; i != word.size() + 1; ++i) {
                for (int j = minLen, pos = i - j; j != maxLen + 1 && pos >= 0; ++j, --pos) {
                    if (dp[pos] && st.count(word.substr(pos, j))) {
                        dp[i] = true;
                        if (i == word.size() && pos != 0) result.push_back(word);
                        break;
                    }
                }
            }
        }
        return result;
    }
};
