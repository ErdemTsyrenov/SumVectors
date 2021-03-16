//
//  main.cpp
//  AsyncSumVectors
//
//  Created by Эрдэм Цыренов on 30.01.2021.
//

#include <iostream>
#include <vector>
#include <future>
#include <algorithm>
#include <numeric>
#include "profile.h"
using namespace std;

int SumTwoVectorsSync(const vector<int>& v1, const vector<int>& v2){
    return accumulate(begin(v1), end(v1), 0) + accumulate(begin(v2), end(v2),0);
}

int SumTwoVectorsAsync(const vector<int>& v1, const vector<int>& v2){
    future<int> f = async([&v2]{
        return accumulate(begin(v2), end(v2), 0);
    });
    int result = accumulate(begin(v1), end(v1), 0);
    return result + f.get();
}

int main(int argc, const char * argv[]) {
    vector<int> v1(1e8, 1);
    vector<int> v2(1e8, 1);
    {LOG_DURATION("Sync computation")
        cout << SumTwoVectorsSync(v1, v2) << endl;
    }
    {LOG_DURATION("Async computation")
        cout << SumTwoVectorsAsync(v1, v2) << endl;
    }
    return 0;
}
