#ifndef ROW_H
#define ROW_H
#include<string.h>
#include<vector>
#include<fstream>
#include<string>
#include<time.h>
#include<algorithm>
#include<set>
#include<map>

#include<unordered_map>
using namespace std;

class Row {
public:
	Row(){
		attributeNumber = 0;
	}
	Row(char* context, int i);
	~Row(){}
public:
	char* attribute[17];
	int index;
	int attributeNumber;
	

};


class DataBase {

public:
	DataBase();

public:
	vector<Row> wholeDataset;
	vector<vector<int>> L;
	set<int> L_real;
	vector<int> L_test;
	ofstream out;
	int attributeNumber;
	int rowNumber;
	int nowIndex;
	int whole;
	vector<int> block_start;
	vector<vector<int>> partition[1 << 15];
	vector<int> A;
	vector<int> B;
	unordered_map<int, int> C;
	unordered_map<int, int> delete_judge;
	unordered_map<int, vector<int>>S;
	//vector<vector<int>>S;
	//unordered_map<int, int>T;
	int T[100000];
	set<int> situation;
	int total_length;
	unordered_map<int, int> binary_number;
	vector<vector<int>> L_new;
	vector<int>empty;


public:
	vector<vector<int>> generateNext();
	void functionResult(int m, int n);
	vector<vector<int>> combine(int, int);
	void computDependency();
	int countSet(vector<int>&);
	int remove(int aim, int x, int r);
	void prune();
	void TANE();

};





#endif