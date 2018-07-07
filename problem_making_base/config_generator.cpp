#include <bits/stdc++.h>
using namespace std;

int main () {
	printf("input points for each test: ");
	int points = -1;
	scanf("%d", &points);
	printf("input time limit, can be floating number: ");
	double time_limit;
	scanf("%lf", &time_limit);
	printf("input memory limit(mb) : ");
	int mb;
	scanf("%d", &mb);

	printf("input file name: ");
	string data;
	cin >> data;
	printf("input the filename interval: ");
	int L, R;
	scanf("%d%d", &L, &R);

	ofstream fout;
	stringstream ss;
	string data_num;
	fout.open("config");
	//printf("-p %d -t %.2f -m %d\n", points, time_limit, mb * 1024);
	fout << "-p " << points <<" -t " << time_limit << " -m " << mb*1024 <<endl;
	for (int i = L; i <= R; i++) {
		ss.clear();
		ss << i;
		ss >> data_num;
		fout <<"test " << data+data_num+".in" << " " << data+data_num+".out";
		fout << endl;
	}
	fout.close();
	return 0;
}
