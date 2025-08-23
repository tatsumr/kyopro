vector<int> Manacher(string s) {
    int n = s.size(), i = 0, j = 0;
    vector<int> r(n);
    while (i < n) {
        while (i - j >= 0 && i + j < n && s[i - j] == s[i + j]) {
            j++;
        }
        r[i] = j;
        int k = 1;
        while (i - k >= 0 && k + r[i - k] < j) {
            r[i + k] = r[i - k];
            k++;
        }
        i += k;
        j -= k;
    }
    return r;
}
