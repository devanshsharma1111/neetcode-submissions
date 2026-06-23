class Solution {
public:
    vector<int> toposort(vector<vector<int>>& adjl, vector<bool>& exists) {
        int n = adjl.size();

        vector<int> indegree(n, 0);

        for (int i = 0; i < n; i++) {
            for (auto it : adjl[i]) {
                indegree[it]++;
            }
        }

        queue<int> q;

        for (int i = 0; i < n; i++) {
            if (exists[i] && indegree[i] == 0)
                q.push(i);
        }

        vector<int> topo;

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            topo.push_back(node);

            for (auto it : adjl[node]) {
                indegree[it]--;

                if (indegree[it] == 0)
                    q.push(it);
            }
        }

        return topo;
    }

    string foreignDictionary(vector<string>& words) {
        vector<vector<int>> adjl(26);
        vector<bool> exists(26, false);
        int uniqueCount = 0;

        for (const string& w : words) {
            for (char c : w) {
                if (!exists[c - 'a']) {
                    exists[c - 'a'] = true;
                    uniqueCount++;
                }
            }
        }

        for (int i = 0; i < words.size() - 1; i++) {
            string s1 = words[i];
            string s2 = words[i + 1];

            int len = min(s1.size(), s2.size());

            if (s1.size() > s2.size() &&
                s1.substr(0, len) == s2.substr(0, len))
                return "";

            for (int j = 0; j < len; j++) {
                if (s1[j] != s2[j]) {
                    adjl[s1[j] - 'a'].push_back(s2[j] - 'a');
                    break;
                }
            }
        }

        vector<int> ans = toposort(adjl, exists);

        if (ans.size() < uniqueCount) return "";

        string str="";
        for (auto it : ans) {
            str += char(it + 'a');
        }

        return str;
    }
};