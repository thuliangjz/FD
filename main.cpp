#include<iostream>

#include"Row.h"




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
	

	
	//system("pause");
	return 0;
}