struct Trie {
    struct Node {
        int from;
        vector<int> to;
        int cnt;
        
        Node() : from(-1), to(26, -1), cnt(0) {}
    };
    
    vector<Node> nodes;
    
    Trie() : nodes(1) {}
    
    void add(string s) {
        int i = 0;
        nodes[i].cnt++;
        for (char c : s) {
            int x = c - 'a';
            if (nodes[i].to[x] == -1) {
                nodes[i].to[x] = nodes.size();
                nodes.emplace_back(Node());
                nodes.back().from = i;
            }
            i = nodes[i].to[x];
            nodes[i].cnt++;
        }
    }
    
    void debug(int i = 0) {
        for (int j = 0; j < 26; j++) {
            if (nodes[i].to[j] != -1) {
                cerr << i << " -> " << (char)(j + 'a') << ", " << nodes[i].to[j] << endl;
            }
        }
        for (int j = 0; j < 26; j++) {
            if (nodes[i].to[j] != -1) {
                debug(nodes[i].to[j]);
            }
        }
        if (i == 0) {
            for (int i = 0; i < (int)nodes.size(); i++) {
                cerr << nodes[i].cnt << " ";
            }
            cerr << endl;
        }
    }
};
