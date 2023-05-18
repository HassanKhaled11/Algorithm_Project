#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

vector<pair<int, int>> coin_pairing(int n) {
    if (n % 2 == 1) {
        cout << "No solution exists" << endl;
        return {};
    }
    
    vector<pair<int, int>> pairs;
    unordered_set<int> unpaired_indices;
    for (int i = 0; i < n; i++) {
        unpaired_indices.insert(i);
    }
    
    for (int i = 0; i < n; i += 2) {
        if (unpaired_indices.find(i) == unpaired_indices.end()) {
            // the coin at i is already paired, skip it
            continue;
        }
        
        // find the closest unpaired coin to the right
        int j = i+1;
        while (j < n && unpaired_indices.find(j) == unpaired_indices.end()) {
            j++;
        }
        
        if (j < n) {
            // pair the coins at i and j
            pairs.push_back({i, j});
            unpaired_indices.erase(i);
            unpaired_indices.erase(j);
        } else {
            // no unpaired coin to the right, find one to the left
            j = i-1;
            while (j >= 0 && unpaired_indices.find(j) == unpaired_indices.end()) {
                j--;
            }
            
            if (j >= 0) {
                // pair the coins at i and j
                pairs.push_back({j, i});
                unpaired_indices.erase(i);
                unpaired_indices.erase(j);
            } else {
                // no unpaired coin found, terminate pairing
                break;
            }
        }
    }
    
    if (pairs.size() == n/2) {
        return pairs;
    } else {
        cout << "No solution exists" << endl;
        return {};
    }
}

int main() {
    int n = 6;
    vector<pair<int, int>> pairs = coin_pairing(n);
    for (auto p : pairs) {
        cout << "(" << p.first << ", " << p.second << ")" << endl;
    }
    return 0;
}