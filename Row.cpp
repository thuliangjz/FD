#include"Row.h"
#include<iostream>
#include<set>


Row::Row(char* context, int i) {

	int count = 0;
	index = i;
	char* buf = NULL;
	char *block = NULL;
	int j;
	char* temp = strtok(context, "," );
	/*
	while (temp) {
		j = 0;
		attribute[count] = new char[100];
		for (j = 0; j < strlen(temp); j++) {
			attribute[count][j] = temp[j];
		}
		attribute[count][j] = '\0';
		temp = strtok_s(NULL, ",", &buf);

		count++;


	}*/
	j = 0;
	attribute[count] = new char[100];
	for (j = 0; j < strlen(temp); j++) {
		attribute[count][j] = temp[j];
	}
	attribute[count][j] = '\0';
	
	while (temp) {
		
		temp = strtok(NULL, ",");
		if (temp == NULL) {
			break;
		}
		if (temp[0] == ' ') {
			strcat(attribute[count], temp);
		}
		else {
			count++;
			j = 0;
			attribute[count] = new char[100];
			for (j = 0; j < strlen(temp); j++) {
				attribute[count][j] = temp[j];
			}
			attribute[count][j] = '\0';
		}
		  
	}
	attributeNumber = count + 1;
	//cout << attributeNumber << endl;
}



DataBase::DataBase() {
	out.open("output_3.txt", ios::out);
	memset(T, 0, sizeof(int) * 100000);
	unordered_map<string, vector<int>> my_map[20];
	nowIndex = 1;
	//S.push_back(empty);
	ifstream in("data.txt", ifstream::in);
	string s;
	int count = 0;
	while (getline(in, s)) {
		Row temp = Row(const_cast<char*>(s.c_str()), count);
		
		for (int i = 0; i < temp.attributeNumber; i++) {
			string name = temp.attribute[i];
			my_map[i][name].push_back(count + 1);
		}

		wholeDataset.push_back(temp);
		count++;
	}

	for (int i = 0; i < wholeDataset[0].attributeNumber; i++) {
		if (partition[1 << i].size() == 0)
			partition[1 << i].push_back(empty);
		for (auto u : my_map[i]) {
			if(u.second.size() >= 2)
			   partition[1 << i].push_back(u.second);
		}
	}
	
	attributeNumber = wholeDataset[0].attributeNumber;

	total_length = attributeNumber;
	rowNumber = wholeDataset.size();
	int all = (1<<attributeNumber) - 1;
	L.push_back(empty);
	for (int i = 0; i < attributeNumber; i++) {
		vector<int> temp;
		temp.push_back(0);
		temp.push_back(i + 1);
		L.push_back(temp);
		binary_number[i + 1] = 1 << i;
		L_real.insert(1 << i);
		L_test.push_back(1 << i);
		C[1 << i] = all;
	}
	C[0] = all;

	whole = (1 << attributeNumber) - 1;


}






vector<vector<int>> DataBase::combine(int x, int y) {
	int aim = x | y;
	partition[aim].clear();
	int i, j, t;
	if (partition[aim].size() == 0) {
		partition[aim].push_back(empty);
	}
	
	for (i = 1; i < partition[x].size(); i++) {
		for (t = 0; t < partition[x][i].size(); t++) {
			T[partition[x][i][t]] = i;
		}
	}
	for (i = 1; i < partition[y].size(); i++) {
		for (j = 0; j < partition[y][i].size(); j++) {
			int u = partition[y][i][j];
			if (T[u] > 0) {
				/*
				if (S.size() >= T[u]) {
					vector<int> temp;
					temp.push_back(u);
					S.push_back(temp);
				}
				else*/
				S[T[u]].push_back(u);

			}
		}
		for (t = 0; t < partition[y][i].size(); t++) {
			int v = partition[y][i][t];
			if (S[T[v]].size() >= 2) {
				partition[aim].push_back(S[T[v]]);
			}
			S[T[v]].clear();
		}
	}
	memset(T, 0, sizeof(int) * 100000);
	/*
	for (i = 1; i < partition[x].size(); i++) {
		for (j = 0; j < partition[x][i].size(); j++) {
			int m = partition[x][i][j];
			T[m] = 0;
		}
	}*/
	return partition[aim];
}

int DataBase::countSet(vector<int>&aim) {
	int r = 0;
	for (int i = 1; i < aim.size(); i++) {
		r = r | (1 << aim[i] - 1);
	}
	return r;

}

int DataBase::remove(int aim, int x, int r) {
	int m = r - x;
	int count = 0;
	int g = aim;
	while (m > 0) {
		if(m % 2 == 1)
		   g = g &(~(g & (1 << count)));
		m = m >> 1;
		count += 1;
	}
	return g;
}

void DataBase::computDependency() {
	for (int z = 1; z < L.size(); z++) {

		int r = binary_number[z];
		int o = whole;
		if (delete_judge[r] > 0) {
			continue;
		}
		for (int i = 1; i < L[z].size(); i++) {
			int k = 1 << (L[z][i] - 1);
			//o = o & C[r&(~(r&k))];
			o = o & C[r - k];
		}
		C[r] = o;
	}
	for (int z = 1; z < L.size(); z++) {
		int p = binary_number[z];
		if (delete_judge[binary_number[z]] > 0) {
			continue;
		}
		int temp = binary_number[z] & C[binary_number[z]];
		int count = 1;
		while (temp > 0) {
			int j = temp % 2;
			if (j == 1) {
				int y = (1 << (count - 1));

				int m = p & (~(p&y));
				int n = m | y;
				
				if (partition[m].size() == 1 || partition[p].size() == 1) {
					if (partition[n].size() == 0) {
						partition[n].push_back(empty);
					}
			
				}
	
				if (partition[n].size() == 0) {
					if(partition[m].size() < partition[y].size())
					   combine(m, y);
					else {
						combine(m, y);
					}
				}
				
				
				if (partition[m].size() == partition[n].size()) {

					//out << m << "->" << y << "\n";
					//cout << m << "->" << y << endl;
					functionResult(m, y);
					//C[p] = C[p]&(~(C[p]&y));
					C[p] = C[p] - y;
					C[p] = remove(C[p], p, whole);

				}



			}

			temp = temp >> 1;
			count++;

		}
	}

}

void DataBase::functionResult(int m, int n) {
	int r = m;
	int k = n;
	int count = 0;
	while (r) {
		int j = r % 2;
		if (j == 1) {
			out << (count + 1) << " ";
		}
		r = r >> 1;
		count++;
	}
	count = 0;
	out << "-> ";
	while (k) {
		int j = k % 2;
		if (j == 1) {
			out << (count + 1) << " ";
		}
		k = k >> 1;
		count++;
	}
	out << endl;
}


vector<vector<int>> DataBase::generateNext() {
	L_new.clear();
	L_new.push_back(empty);
	A.push_back(0);
	B.push_back(0);
	block_start.push_back(0);
	vector<int>block;
	block.push_back(0);
	int k = 0;
	int y = 0;
	int current_block_start = 0;
	if (nowIndex == 1) {
		for(int i = 0; i < L.size(); i++)
		   block_start.push_back(1);
	}
	
	for (int i = 1; i < L.size(); i++) {
		current_block_start = k + 1;
		int m = countSet(L[i]);
		if (delete_judge[m] > 0) {

			continue;
		}

		for (int j = i + 1; (block_start[j] == block_start[i] && j < L.size()); j++) {

			for (int x = 1; x <= nowIndex; x++) {

				A.push_back(L[i][x]);
			}

			A.push_back(L[j][nowIndex]);

			int judge = 0;
			
			k = k + 1;

			binary_number[L_new.size()] = countSet(A);
			L_new.push_back(A);

			block.push_back(current_block_start);
			A.clear();
			A.push_back(0);
			B.clear();
			B.push_back(0);

		}
	
		
	}

	A.clear();
	B.clear();
	block_start.clear();
	block_start.assign(block.begin(), block.end());
	L.clear();
	L.assign(L_new.begin(), L_new.end());
	
	nowIndex++;

	return L_new;
}


void DataBase::prune() {

	for (int z = 1; z < L.size(); z++) {
		int x = binary_number[z];
		if (delete_judge[x] > 0) {
			continue;
		}
		if (C[x] == 0) {
			delete_judge[x] = 1;			
		}
		
	}
}

void DataBase::TANE() {
	clock_t start, end;
	double total;
	while (L.size() > 1) {
		//start = clock();
		computDependency();
		end = clock();
		//total = (double)(end - start) / CLOCKS_PER_SEC;
		//cout << "compute time" << total << "Ãë" << endl;
		//start = clock();
		prune();
		//end = clock();
		//total = (double)(end - start) / CLOCKS_PER_SEC;
		//cout << "pruning" << total << "Ãë" << endl;
		//start = clock();
		generateNext();
		//end = clock();
		//total = (double)(end - start) / CLOCKS_PER_SEC;
		//cout << "generateNext time" << total << "Ãë" << endl;

	}
	out.close();
}


