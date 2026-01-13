#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

vector<string> split(const string& s, char delim) {
    vector<string> result;
    size_t start = 0;
    size_t end = s.find(delim);
    while (end != string::npos) {
        result.push_back(s.substr(start, end - start));
        start = end + 1;
        end = s.find(delim, start);
    }
    result.push_back(s.substr(start));
    return result;
}

int main() {
    int n;
    cin >> n;

    map<string, vector<string>> man_prefs;
    map<string, map<string, int>> woman_ranks;

    // Read men's preferences
    for (int i = 0; i < n; ++i) {
        string line;
        cin >> line;
        size_t colon = line.find(':');
        string name = line.substr(0, colon);
        string prefs_str = line.substr(colon + 1);
        man_prefs[name] = split(prefs_str, '>');
    }

    // Read women's preferences
    for (int i = 0; i < n; ++i) {
        string line;
        cin >> line;
        size_t colon = line.find(':');
        string name = line.substr(0, colon);
        string prefs_str = line.substr(colon + 1);
        vector<string> prefs = split(prefs_str, '>');
        map<string, int> rank_map;
        for (int j = 0; j < prefs.size(); ++j) {
            rank_map[prefs[j]] = j;
        }
        woman_ranks[name] = rank_map;
    }

    // Initialize data structures
    queue<string> free_men;
    for (const auto& pair : man_prefs) {
        free_men.push(pair.first);
    }

    map<string, string> women_engaged_to;
    map<string, string> men_engaged_to;
    map<string, int> next_proposal_index;

    // Gale-Shapley algorithm
    while (!free_men.empty()) {
        string m = free_men.front();
        free_men.pop();

        int idx = next_proposal_index[m];
        if (idx >= man_prefs[m].size()) continue;
        string w = man_prefs[m][idx];
        next_proposal_index[m]++;

        if (!women_engaged_to.count(w)) {
            women_engaged_to[w] = m;
            men_engaged_to[m] = w;
        }
        else {
            string current_m = women_engaged_to[w];
            if (woman_ranks[w][m] < woman_ranks[w][current_m]) {
                women_engaged_to[w] = m;
                men_engaged_to[m] = w;
                free_men.push(current_m);
                men_engaged_to.erase(current_m);
            }
            else {
                free_men.push(m);
            }
        }
    }

    // Collect and sort men's names
    vector<string> men;
    for (const auto& pair : man_prefs) {
        men.push_back(pair.first);
    }
    sort(men.begin(), men.end());

    // Output the results
    for (const string& m : men) {
        cout << "(" << m << "," << men_engaged_to[m] << ")" << endl;
    }

    return 0;
}