#include<iostream>

#include"Row.h"

bool functionCompare(pair<int, int> a, pair<int, int> b) {
	int r = a.first;
	int k = b.first;
	if (r == k) {
		return a.second > b.second;
	}
	int judge = 0;
	while (r && k) {
		if (r > 0 && k == 0) {
			return false;
		}
		if (r == 0 && k > 0) {
			return true;
		}
		int j = r % 2;
		int i = k % 2;
		if (j > i) {
			return false;
		}
		else if(j < i){
			return true;
		}
		r = r >> 1;
		k = k >> 1;
	}
	return true;
	
}


int main() {
	clock_t start, end;
	double totaltime;
	start = clock();
	DataBase database;
	//cout << database.rowNumber << " " << database.attributeNumber << endl;
	//vector<int> h;
	//h.push_back(1);
	//h.push_back(2);
	//cout << (2 | 3120) << endl;
	//cout << database.partition[2].size()<< endl;
	//unordered_map<int, vector<int>> g;
	//cout << g[1].size() << endl;
	database.TANE();

	end = clock();
	totaltime = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "Ê±¼äÎª" << totaltime << "Ãë" << endl;
	ofstream my_out;
	my_out.open("result.txt", ios::out);
	for (int i = 0; i < database.result_number; i++) {
		for (int j = 0; j < database.result_number - i - 1; j++) {
			if (functionCompare(database.result[j], database.result[j + 1])) {
				pair<int, int> temp = make_pair(0, 0);
				temp = database.result[j];
				database.result[j] = database.result[j + 1];
				database.result[j + 1] = temp;
			}
		}
	}
	for (int i = 0; i < database.result_number; i++) {
		database.functionResult(database.result[i].first, database.result[i].second, my_out);
	}
	my_out.close();
	//cout << database.partition[1 | 16].size() << endl;
	//cout << database.combine(1, 16).size() << endl;
	//cout << database.combine(16, 1).size() << endl;
	//database.combine(2 | 16, 1);
	//cout << database.partition[1|16].size() << " * " << database.partition[1].size() << " * "<<database.partition[16].size() << endl;
	//database.generate_next();
	//database.generate_next();
	//database.generate_next();
	//database.generate_next();
	//database.generate_next();
	//cout << database.L_real.size() << endl;
	

	
	system("pause");
	return 0;
}