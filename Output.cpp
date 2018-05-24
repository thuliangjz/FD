#include "Output.h"
#include<algorithm>

bool FDComp(pair<bitset, bitset>a, pair<bitset,bitset> b){
    return a.first < b.first || (a.first == b.first && a.second < b.second); 
}

void OutputInDictOrder(vector<pair<bitset, bitset>> &fds , ostream& out){
    //生成从索引到字符的对应
    std::string s_map_idx_char;
    for(int i = 0; i < 26; ++i){
        s_map_idx_char.push_back('A' + i);
    }

    std::sort(fds.begin(), fds.end(), FDComp);
    for(auto fd : fds){
        for(int i = 0; i < sizeof(bitset) * 8; ++i){
            if(fd.first & (1 << i)){
                out<<s_map_idx_char[i];
            }
        }
        out<<"->";
        for(int i = 0; i < sizeof(bitset) * 8; ++i){
            if(fd.second & (1 << i)){
                out<<s_map_idx_char[i];
                break;
            }
        }
        out<<std::endl;
    }
}

void TestOutPutInDict(){
    using std::make_pair;
    vector<pair<bitset, bitset>> v;
    v.push_back(make_pair(1, 2));
    v.push_back(make_pair(6, 16));
    v.push_back(make_pair(5, 4));
    v.push_back(make_pair(20, 8));
    v.push_back(make_pair(10, 8));
    OutputInDictOrder(v, std::cout);
}