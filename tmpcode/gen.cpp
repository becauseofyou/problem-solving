#include <bits/stdc++.h>
using namespace std;


int main() {
	srand(time(NULL));
	int n = 10;
	cout<<n<<endl;
	for (int i = 0; i < n; i++) {
		cout << random() << " ";
	}
	cout << endl;
	for (int i = 1; i < n; i++) {
		cout<< i + 1 << " " << random() % i + 1 << endl;
	}
	return 0;
}
