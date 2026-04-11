#include<iostream>
#include<vector>
using namespace std;

vector<int> buildLPS(string pattern) {
        int m = pattern.length();
        vector<int> lps(m, 0);
        int len = 0;
        int i = 1;
        
        while (i < m) {
            if (pattern[i] == pattern[len]) {
                len++;
                lps[i] = len;
                i++;
            } else {
                if (len != 0) {
                    len = lps[len - 1];
                } else {
                    lps[i] = 0;
                    i++;
                }
            }
        }
        return lps;
    }
vector<int> searchPattern(string txt, string pat) {
    vector<int> result;
    int n = txt.length();
    int m = pat.length();
    
    if (m > n) return result;
    
    vector<int> lps = buildLPS(pat);
    int i = 0;
    int j = 0;
    
    while (i < n) {
        if (txt[i] == pat[j]) {
            i++;
            j++;
        }
        
        if (j == m) {
            result.push_back(i - j);
            j = lps[j - 1];
        } else if (i < n && txt[i] != pat[j]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    
    return result;
}

int main() {
    
    string txt = "aabaacaadaabaaba";
    string pat = "aaba";
    cout << "Text: " << txt << ", Pattern: " << pat << endl;
    cout << "Output: ";
    vector<int> res = searchPattern(txt, pat);
    for (int idx : res) {
        cout << idx << " ";
    }
    cout << endl;
    
    return 0;
}