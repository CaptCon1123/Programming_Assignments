#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>
#include <chrono>
#include <random>
#include <numeric>
using namespace std;

// TASK A -----------------------------------------------------------------
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

vector<int> GaleShapely(int n, vector<vector<int>>& Hosp, vector<vector<int>>& Stu) {
    //to avoid potential issues with nextIndex[h] when n == 0
    if(n == 0) return {};
    vector<int> StuAssignment(n, -1);
    vector<int> HospAssigned(n, 0);
    // next position in Hosp[h]'s preference list to propose
    vector<int> nextIndex(n,0);
    
    bool UnAssigned = any_of(HospAssigned.begin(), HospAssigned.end(), [](int i){ return i == 0; });

    while (UnAssigned) {
        int h;
        for (h = 0; h < n; h++) {
            if (HospAssigned[h] != 1) {
                break;
            }
        }
        if (h == n) break;
        if (nextIndex[h] >= n) {        
            HospAssigned[h] = 1;    // marked as done to avoid infinite loop
            continue;
        }
        for (int i = nextIndex[h]; (i < n) && (HospAssigned[h] != 1); i++) {
            int s = Hosp[h][i] - 1;
            nextIndex[h] = i + 1;
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

// TASK B ----------------------------------------------------------------------------------------------
// Build inverse preference ranks, lower is better
 vector<vector<int>> BuildRank(const vector<vector<int>>& pref) {
    int n = (int)pref.size();
    vector<vector<int>> rank(n, vector<int>(n, -1));
    for (int i = 0; i < n; i++) {
        if ((int)pref[i].size() != n) return {}; 
        for (int pos = 0; pos < n; pos++) {
            int v = pref[i][pos] - 1;            
            if (v < 0 || v >= n) return {};      
            if (rank[i][v] != -1) return {};     
            rank[i][v] = pos;
        }
    }
    return rank;
}

bool VerifyMatching(int n, const vector<vector<int>>& HospPref, const vector<vector<int>>& StuPref, const vector<int>& StuAssignment, string& message){
    // empty
    if(n == 0){
        if(!HospPref.empty() || !StuPref.empty() || !StuAssignment.empty()){
            message = "INVALID: n = 0 but somehow preference/matching arrays are not empty.";
            return false;
        }
        message = "VALID STABLE";
        return true;
    }    
    // make sure sizes are correct
    if((int)HospPref.size() != n || (int)StuPref.size() != n || (int)StuAssignment.size() != n){
        message = "INVALID: array sizes do not match n.";
        return false;
    }
    // rank tables
    auto HospRank = BuildRank(HospPref);
    auto StuRank = BuildRank(StuPref);
    if(HospRank.empty() || StuRank.empty()){
        message = "INVALID: preference lists are not permutations of 1...n (either duplicates or not in range).";
        return false;
    }
    // Check validity
    // each student matched to exactly one hospital & each hospital matched exactly once
    vector<int> seenStudent(n, 0);
    vector<int> stuToHosp(n, -1);
    for (int h = 0; h < n; h++) {
        int s = StuAssignment[h];
        if (s < 0 || s >= n) {
            message = "INVALID: hospital " + to_string(h + 1) + " matched to out-of-range student.";
            return false;
        }
        if (seenStudent[s]) {
            message = "INVALID: student " + to_string(s + 1) + " matched to multiple hospitals.";
            return false;
        }
        seenStudent[s] = 1;
        stuToHosp[s] = h;
    }
    // Check for unstable pairs
    for (int h = 0; h < n; h++) {
        int sCurrent = StuAssignment[h];
        for (int pos = 0; pos < HospRank[h][sCurrent]; pos++) {
            int s = HospPref[h][pos] - 1;          // preferred student
            int hCurrentForS = stuToHosp[s];       // s's current hospital

            if (StuRank[s][h] < StuRank[s][hCurrentForS]) {
                message = "Unstable: blocking pair found: (hospital " + to_string(h + 1) +
                          ", student " + to_string(s + 1) + ").";
                return false;
            }
        }
    }
    message = "VALID STABLE";
    return true;
}

// TASK C ----------------------------------------------------------------------------
// Generate random preference lists (a row is a random permutation of 1..n)
vector<vector<int>> RandomPrefs(int n, mt19937 &rng) {
    vector<vector<int>> pref(n, vector<int>(n));
    vector<int> base(n);
    iota(base.begin(), base.end(), 1);
    for (int i = 0; i < n; i++) {
        pref[i] = base;
        shuffle(pref[i].begin(), pref[i].end(), rng);
    }
    return pref;
}

// MAIN -----------------------------------------------------------------------------------------------
int main(int argc, char** argv) {
    // untie cin
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // what mode (task)
    string mode = "match";
    if(argc >= 2) mode = argv[1];
    //Measure running time (TASK C)
    if(mode == "measure"){
        mt19937 rng(123456);
        vector<int> ns = {1,2,4,8,16,32,64,128,256,512};
        cout << "n,matcher_us,verifier_us\n";
        for (int n : ns) {
            auto hospPrefer = RandomPrefs(n, rng);
            auto stuPrefer  = RandomPrefs(n, rng);
            using clk = chrono::high_resolution_clock;
        // time matcher
            auto t0 = clk::now();
            vector<int> StuAssignment = GaleShapely(n, hospPrefer, stuPrefer);
            auto t1 = clk::now();
            long long matcher_us = chrono::duration_cast<chrono::microseconds>(t1 - t0).count();
        // convert to hospToStu for verifier
            vector<int> hospToStu(n, -1);
            for (int s = 0; s < n; s++) {
                int h = StuAssignment[s];
                if (h >= 0 && h < n) hospToStu[h] = s;
            }
        // time verifier
            string msg;
            auto t2 = clk::now();
            (void)VerifyMatching(n, hospPrefer, stuPrefer, hospToStu, msg);
            auto t3 = clk::now();
            long long verifier_us = chrono::duration_cast<chrono::microseconds>(t3 - t2).count();
            cout << n << "," << matcher_us << "," << verifier_us << "\n";
        }
        return 0;
    }
    int n;
    if (!(cin >> n)) {
        cout << "INVALID: missing n (empty file or unreadable input).\n";
        return 0;
    }
    if (n < 0) {
        cout << "INVALID: n must be nonnegative.\n";
        return 0;
    }
    vector<vector<int>> hospPrefer(n, vector<int>(n));
    vector<vector<int>> stuPrefer(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!(cin >> hospPrefer[i][j])) {
                cout << "INVALID: could not read hospital preference lists.\n";
                return 0;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!(cin >> stuPrefer[i][j])) {
                cout << "INVALID: could not read student preference lists.\n";
                return 0;
            }
        }
    }
    //Create stable matchings (TASK A)
    if (mode == "match") {
        vector<int> StuAssignment = GaleShapely(n, hospPrefer, stuPrefer);
        // Convert to assignment output format that was specified
        vector<int> hospToStu(n, -1);
        for (int s = 0; s < n; s++) {
            int h = StuAssignment[s];
            if (h >= 0 && h < n) hospToStu[h] = s;
        }
        for (int h = 0; h < n; h++) {
            cout << (h + 1) << " " << (hospToStu[h] + 1) << "\n";
        }
        return 0;
    }
    //verify matchings (TASK B)
    if(mode == "verify"){
        vector<int> hospToStu(n, -1);
        vector<int> seenHosp(n, 0);
        for (int k = 0; k < n; k++) {
            int i, j;
            if (!(cin >> i >> j)) {
                cout << "INVALID: missing matching lines (expected " << n << " pairs).\n";
                return 0;
            }
            if (i < 1 || i > n || j < 1 || j > n) {
                cout << "INVALID: matching contains out-of-range index.\n";
                return 0;
            }
            if (seenHosp[i - 1]) {
                cout << "INVALID: hospital " << i << " appears multiple times in matching.\n";
                return 0;
            }
            seenHosp[i - 1] = 1;
            hospToStu[i - 1] = j - 1;
        }

        string msg = "womp womp";
        bool ok = VerifyMatching(n, hospPrefer, stuPrefer, hospToStu, msg);
        cout << msg << "\n";
        return ok ? 0 : 0;
    }    
    // incorrect mode
    cout << "INVALID: unknown mode. Use './program ' and then 'verify' 'match' or 'measure'";
    return 0;
}