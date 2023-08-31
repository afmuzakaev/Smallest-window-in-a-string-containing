#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

string findSmallestWindow(string S, string P) {
    int n = S.length();
    int m = P.length();
    
    if (m > n) {
        return "-1";
    }
    
    unordered_map<char, int> freqP, freqS;
    for (char c : P) {
        freqP[c]++;
    }
    
    int count = 0; // count of characters matched so far
    int start = 0; // starting index of the current window
    int minLen = INT_MAX; // minimum length of valid window
    int minStart = 0; // starting index of the smallest window
    
    for (int i = 0; i < n; i++) {
        freqS[S[i]]++;
        
        if (freqP.find(S[i]) != freqP.end() && freqS[S[i]] <= freqP[S[i]]) {
            count++;
        }
        
        if (count == m) {
            // Try to minimize the window by moving the start pointer
            while (freqP.find(S[start]) == freqP.end() || freqS[S[start]] > freqP[S[start]]) {
                if (freqS[S[start]] > freqP[S[start]]) {
                    freqS[S[start]]--;
                }
                start++;
            }
            
            // Update the minimum window size and starting index
            int windowLen = i - start + 1;
            if (windowLen < minLen) {
                minLen = windowLen;
                minStart = start;
            }
        }
    }
    
    if (minLen == INT_MAX) {
        return "-1";
    }
    
    return S.substr(minStart, minLen);
}

int main() {
    string S = "timetopractice";
    string P = "toc";
    
    string result = findSmallestWindow(S, P);
    cout << "Output: " << result << endl;
    
    return 0;
}
