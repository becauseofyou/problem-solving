template <class T>
std::vector<pii> domain(std::vector <T> a) {
	a.push_back(std::numeric_limits<T>::min());
	std::stack <pii> stack; // value, position
	std::vector <pii> result(SIZE(a));
	stack.push({std::numeric_limits<T>::min(), -1});
	rep(i, SIZE(a)) {
		int right = i - 1, left = -1;
		while (!stack.empty() && stack.top().fi > a[i]) {
			pii top = stack.top();
			stack.pop();
			left = stack.top().se + 1;
			result[top.se] = mp(left, right);
		}
		stack.push({a[i], i});
	}
	return result;
}
