#include<iostream>

#include"Row.h"




int main() {
	clock_t start, end;
	double totaltime;
	start = clock();
	DataBase database;
	database.TANE();
	end = clock();
	totaltime = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "total time" << totaltime << "" << endl;
	return 0;
}