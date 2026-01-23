#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

bool PreferNew(vector<vector<int>> &Array, int n, int s, int h1, int h2) {
    for (int i = 0; i < n; i++) {
        if(Array[s][i] - 1 == h2) {
            return true;
        }
        if(Array[s][i] - 1 == h1) {
            return false;
        }
    }
    return false;
}

vector<int> GaleShapely(int n, vector<vector<int>> &Hosp, vector<vector<int>> &Stu) {
    vector<int> StuAssignment(n, -1);
    vector<int> HospAssigned(n, 0);
    
    bool UnAssigned = any_of(HospAssigned.begin(), HospAssigned.end(), [](int i){ return i == 0; });

    while (UnAssigned) {
        int h;
        for (h = 0; h < n; h++) {
            if (HospAssigned[h] != 1) {
                break;
            }
        }

        for (int i = 0; (i < n) && (HospAssigned[h] != 1); i++) {
            int s = Hosp[h][i] - 1;
            if (StuAssignment[s] == -1) {
                StuAssignment[s] = h;
                HospAssigned[h] = 1;
                UnAssigned = any_of(HospAssigned.begin(), HospAssigned.end(), [](int i){ return i == 0; });
            }
            else {
                int h2 = StuAssignment[s];
                if (!PreferNew(Stu, n, s, h, h2)) {
                    StuAssignment[s] = h;
                    HospAssigned[h] = 1;
                    HospAssigned[h2] = 0;
                }
            }

        }
        UnAssigned = any_of(HospAssigned.begin(), HospAssigned.end(), [](int i){ return i == 0; });
    }
    return StuAssignment;

}


int main() {
    vector<vector<int>> stuPrefer = { {1, 2, 3}, {2, 3, 1}, {3, 1, 2} };
    vector<vector<int>> hospPrefer = { {1, 2, 3}, {2, 3, 1}, {3, 1, 2} };

    vector<int> wPartner = GaleShapely(3, hospPrefer, stuPrefer);
    cout << "Woman   Man" << endl;
    int N = 3;
    for (int i = 0; i < N; i++)
        cout << i << " " << wPartner[i] << endl;
    return 0;
}