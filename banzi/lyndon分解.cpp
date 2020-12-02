vector<string> duval(string const& s) {
  int n = s.size(), i = 0;
  vector<string> factorization;
  while (i < n) {
    int k = i + 1, j = i;
    while (k < n && s[j] <= s[k]) {
      if (s[j] < s[k])
        j = i;
      else
        j++;
      k++;
    }
    while (i <= j) {
      factorization.push_back(s.substr(i, k - j));
      i += k - j;
    }
  }
  return factorization;
}