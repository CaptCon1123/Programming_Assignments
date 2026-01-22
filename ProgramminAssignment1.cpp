#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

int GaleShapely(int n, int L1[], int L2[]) {
    vector<int> AssignedList(n, -1);
    vector<int> AlreadyAssigned(n, 0);
    
    bool UnAssigned = any_of(AlreadyAssigned.begin(), AlreadyAssigned.end(), [](int i){ return i == 0; });

    while (UnAssigned) {
        int t;
        for (t = 0; t < n; t++) {
            if (!free[t]) {
                break;
            }
        }

    }

}


bool PreferNew(vector<int> &Array, int c1, int c2) {
    int n = Array.size();
    for (int i = 0; i < n; i++) {
        if(Array[i] == c2) {
            return true;
        }
        if(Array[i] == c1) {
            return false;
        }
    }
}
