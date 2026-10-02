// debug << x << "\n";
// debug.table(S, "") 

struct DebugStream {
    ostream& os;

    DebugStream(ostream& _os = cerr) : os(_os) {}

    // int
    DebugStream& operator<<(int x) {
        if (x == INF) os << "INF";
        else os << x;
        return *this;
    }
    
    // long long
    DebugStream& operator<<(long long x) {
        if (x == LINF) os << "LINF";
        else os << x;
        return *this;
    }

    // pair
    template <class T, class U>
    DebugStream& operator<<(const pair<T, U>& p) {
        *this << '{' << p.first << ", " << p.second << '}';
        return *this;
    }

    // vector
    template <class T>
    DebugStream& operator<<(const vector<T>& v) {
        *this << '{';
        for (int i = 0; i < (int)v.size(); ++i) {
            if (i) *this << ", ";
            *this << v[i];
        }
        *this << '}';
        return *this;
    }

    // set
    template <class T>
    DebugStream& operator<<(const set<T>& s) {
        *this << '{';
        for (auto it = s.begin(); it != s.end(); ++it) {
            if (it != s.begin()) *this << ", ";
            *this << *it;
        }
        *this << '}';
        return *this;
    }

    // map
    template <class K, class V>
    DebugStream& operator<<(const map<K, V>& m) {
        *this << '{';
        for (auto it = m.begin(); it != m.end(); ++it) {
            if (it != m.begin()) *this << ", ";
            *this << *it;
        }
        *this << '}';
        return *this;
    }

    // その他
    template <class T>
    DebugStream& operator<<(const T& x) {
        os << x;
        return *this;
    }
    
    template <class T>
    void table(const vector<vector<T>>& a, string sep = " ") {
        for (const auto& row : a) {
            for (int j = 0; j < (int)row.size(); ++j) {
                if (j) os << sep;
                *this << row[j];
            }
            os << '\n';
        }
    }
} debug;
