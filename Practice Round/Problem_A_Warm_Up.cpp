#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
int main() {
    string inputFilePath = "warm_up_input.txt"; 
    string outputFilePath = "testoutput.txt";
    ifstream inputFile(inputFilePath);
    if (!inputFile) {
        cerr << "Erroropening inputfile."<< endl;
        return 1;}
    ofstream outputFile(outputFilePath);
    if (!outputFile) {
        cerr << "Error openingoutputfile."<< endl;
        return 1;}
    int T;
    inputFile >> T;
    for (int t = 0; t < T; t++) {
        int N;
        inputFile >> N;
        vector<int> A(N), B(N);
        for (int i = 0; i < N; i++) {
            inputFile >> A[i];}
        for (int i = 0; i < N; i++) {
            inputFile >> B[i];}
        bool possible = true;
        for (int i = 0; i < N; i++) {
            if (A[i] > B[i]) {
                possible = false;}}
        if (possible) {
            vector<int> freq(N + 1, 0);
            for (int i = 0; i < N; i++) {
                freq[A[i]]++;}
            for (int i = 0; i < N; i++) {
                if (freq[B[i]] == 0) {
                    possible = false;
                    break;}}}
        if (!possible) {
            outputFile << "Case #" << t + 1 << ": -1" << endl;
            continue;}
        vector<int> source(N + 1, 0);
        for (int i = 0; i < N; i++) {
            int temp = A[i];
            if (source[temp] == 0) {
                source[temp] = i + 1;}}
        vector<vector<int>> needs(N + 1);
        for (int i = 0; i < N; i++) {
            if (A[i] < B[i]) {
                needs[B[i]].push_back(i + 1);}}
        vector<pair<int, int>> operations;
        for (int tt = 1; tt <= N; tt++) {
            if (!needs[tt].empty()) {
                int src = source[tt];
                for (int idx : needs[tt]) {
                    operations.push_back({src, idx});}}}
        outputFile << "Case #" << t + 1 << ": " << operations.size() << endl;
        for (const auto& op : operations) {
            outputFile << op.first << " " << op.second << endl;}}
    inputFile.close();
    outputFile.close();
    return 0;}
