#include <iostream>
#include <vector>

using namespace std;

// Structure to store a section
struct Section {
    vector<int> row;
    vector<int> col;
};

// Initialize a section
void init_section(Section& s) {
    s.row.clear();
    s.col.clear();
}

// Add a spot to the section
void add_spot(Section& s, int r, int c) {
    s.row.push_back(r);
    s.col.push_back(c);
}

// Depth-first search to find a section
void dfs(int row, int col, const int N, const int M, const vector<vector<int>>& parking_lot,
         Section& current_section, vector<vector<int>>& visited) {
    if (row < 0 || row >= N || col < 0 || col >= M || visited[row][col] || parking_lot[row][col] == 1) {
        return;
    }

    visited[row][col] = 1;
    add_spot(current_section, row, col);

    // Explore neighboring spots
    dfs(row + 1, col, N, M, parking_lot, current_section, visited);
    dfs(row - 1, col, N, M, parking_lot, current_section, visited);
    dfs(row, col + 1, N, M, parking_lot, current_section, visited);
    dfs(row, col - 1, N, M, parking_lot, current_section, visited);
}

// Find parking sections
int find_parking_sections(const vector<vector<int>>& parking_lot) {
    const int N = parking_lot.size();
    const int M = parking_lot[0].size();
    vector<vector<int>> visited(N, vector<int>(M, 0));
    vector<Section> sections;
    int max_score = 0;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (parking_lot[i][j] != 1 && !visited[i][j]) {
                sections.emplace_back();
                init_section(sections.back());
                dfs(i, j, N, M, parking_lot, sections.back(), visited);

                // Calculate score for this section
                int score = 0;
                for (size_t k = 0; k < sections.back().row.size(); ++k) {
                    int r = sections.back().row[k];
                    int c = sections.back().col[k];
                    score += (parking_lot[r][c] == 0) ? 1 : -2;
                }
                max_score = max(max_score, score);
            }
        }
    }

    return max_score;
}

int main() {
    int N, M;
    cout << "Enter N (rows) and M (columns): ";
    cin >> N >> M;
    
    // Constraints: 1 <= N, M <= 2000
    if (N < 1 || M < 1 || N > 2000 || M > 2000) {
        cout << "Invalid input. N and M must be between 1 and 2000." << endl;
        return 1;
    }

    vector<vector<int>> parking_lot(N, vector<int>(M));
    cout << "Enter 0 for empty, 1 for occupied, 2 for accessible:\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> parking_lot[i][j];
        }
    }

    int highest_score = find_parking_sections(parking_lot);
    cout << "Highest score: " << highest_score << endl;

    return 0;
}
