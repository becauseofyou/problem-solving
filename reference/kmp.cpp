namespace kmp {
	std::vector<int> get_fail(const std::string s) {
		std::vector <int> fail;
		fail.resize(SIZE(s), -1);
		for (int i = 1, j = -1; i < SIZE(s); i++) {
			while (j >= 0 && s[j + 1] != s[i]) {
				j = fail[j];
			}
			if (s[j + 1] == s[i]) { // matched
				++j;
				fail[i] = j;
			} else { //no match
				fail[i] = -1;
			}
		}
		return fail;
	}

	int match_count(const std::string pattern, const std::string text) {
		std::vector <int> fail = get_fail(pattern);	
		int ret = 0, j = -1;
		rep (i, SIZE(text)) {
			while (j >= 0 && pattern[j + 1] != text[i]) {
				j = fail[j];
			}
			if (pattern[j + 1] == text[i]) {
				++j;
			}
			if (j + 1 == SIZE(pattern)) {
				ret++;
				j = fail[j];
			}
		}
		return ret;
	}
}