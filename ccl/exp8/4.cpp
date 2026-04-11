#include<iostream>
#include<vector>
using namespace std;

const long long BASE = 31;
const long long MOD = 1000000007;

vector<int> rabinKarp(string text, string pattern) {
    vector<int> result;
    int n = text.length();
    int m = pattern.length();
    
    if (m > n) return result;
    
    long long patternHash = 0;
    long long textHash = 0;
    long long basePower = 1;
    
    for (int i = 0; i < m - 1; i++) {
        basePower = (basePower * BASE) % MOD;
    }
    
    for (int i = 0; i < m; i++) {
        patternHash = (patternHash * BASE + pattern[i]) % MOD;
        textHash = (textHash * BASE + text[i]) % MOD;
    }
    
    for (int i = 0; i <= n - m; i++) {
        if (patternHash == textHash) {
            bool match = true;
            for (int j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                result.push_back(i);
            }
        }
        
        if (i < n - m) {
            textHash = (BASE * (textHash - text[i] * basePower % MOD + MOD) % MOD + text[i + m]) % MOD;
        }
    }
    
    return result;
}

int main() {

    string text = "aabaacaadaabaaba";
    string pattern = "aaba";
    
    cout << "Text: " << text << ", Pattern: " << pattern << endl;
    cout << "Output: ";
    
    vector<int> res = rabinKarp(text, pattern);
    for (int idx : res) {
        cout << idx << " ";
    }
    
    cout << endl;
    
    return 0;
}