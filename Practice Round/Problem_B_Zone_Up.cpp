#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <climits>
#include <fstream>
using namespace std;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
void bfs_from_objects(int R, int C, const vector<string>& grid, vector<vector<int>>& dist) {
    queue<pair<int, int>> q;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (grid[i][j] == '#') {
                dist[i][j] = 0;
                q.push({i, j});
            } else {
                dist[i][j] = INT_MAX;}}}
    while (!q.empty()) {
        pair<int, int> front = q.front();
        q.pop();
        int x = front.first;
        int y = front.second;
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < R && ny >= 0 && ny < C && dist[nx][ny] == INT_MAX) {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});}}}}
int findLargestSafeZone(int R, int C, int S, const vector<vector<int>>& dist) {
    int maxArea = 0;
    vector<vector<bool>> visited(R, vector<bool>(C, false));
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (dist[i][j] >= S + 1 && !visited[i][j]) {
                int area = 0;
                queue<pair<int, int>> q;
                q.push({i, j});
                visited[i][j] = true;
                while (!q.empty()) {
                    pair<int, int> front = q.front();
                    q.pop();
                    area++;
                    for (int k = 0; k < 4; k++) {
                        int nx = front.first + dx[k];
                        int ny = front.second + dy[k];
                        if (nx >= 0 && nx < R && ny >= 0 && ny < C && dist[nx][ny] >= S + 1 && !visited[nx][ny]) {
                            visited[nx][ny] = true;
                            q.push({nx, ny});}}}
                maxArea = max(maxArea, area);}}}
    return maxArea;}
int main() {
    ifstream inputFile("zone_in_input.txt");
    ofstream outputFile("testoutput.txt");
    int T;
    inputFile >> T;
    for (int t = 1; t <= T; t++) {
        int R, C, S;
        inputFile >> R >> C >> S;
        vector<string> grid(R);
        for (int i = 0; i < R; i++) {
            inputFile >> grid[i];}
        vector<vector<int>> dist(R, vector<int>(C));
        bfs_from_objects(R, C, grid, dist);
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                int wall_dist = min({i + 1, R - i, j + 1, C - j});
                dist[i][j] = min(dist[i][j], wall_dist);}}
        int largestSafeZone = findLargestSafeZone(R, C, S, dist);
        outputFile << "Case #" << t << ": " << largestSafeZone << endl;}
    inputFile.close();
    outputFile.close();
    return 0;}
