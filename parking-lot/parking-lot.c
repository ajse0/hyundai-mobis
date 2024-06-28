#include <stdio.h>
#include <stdlib.h>

#define MAX_N 2000
#define MAX_M 2000

// Structure to store a section
struct Section {
    int row[MAX_N * MAX_M];
    int col[MAX_N * MAX_M];
    int size;
};

// Initialize a section
void init_section(struct Section *s) {
    s->size = 0;
}

// Add a spot to the section
void add_spot(struct Section *s, int r, int c) {
    s->row[s->size] = r;
    s->col[s->size] = c;
    s->size++;
}

// Depth-first search to find a section
void dfs(int row, int col, int N, int M, int parking_lot[N][M], struct Section *current_section, int visited[N][M]) {
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
void find_parking_sections(int N, int M, int parking_lot[N][M]) {
    int visited[MAX_N][MAX_M] = {0}; // Initialize visited array to zeros
    struct Section *sections = malloc(MAX_N * MAX_M * sizeof(struct Section));
    int num_sections = 0;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (parking_lot[i][j] != 1 && !visited[i][j]) {
                init_section(&sections[num_sections]);
                dfs(i, j, N, M, parking_lot, &sections[num_sections], visited);
                num_sections++;
            }
        }
    }

    // Find the section with the highest score
    int max_score = 0;
    for (int i = 0; i < num_sections; ++i) {
        int score = 0;
        for (int j = 0; j < sections[i].size; ++j) {
            int r = sections[i].row[j];
            int c = sections[i].col[j];
            score += (parking_lot[r][c] == 0) ? 1 : -2;
        }
        if (score > max_score) {
            max_score = score;
        }
    }

    printf("Highest score: %d\n", max_score);

    // Free dynamically allocated memory
    free(sections);
}

int main() {
    int N, M;
    printf("Enter N (rows) and M (columns): ");
    scanf("%d %d", &N, &M);

    int parking_lot[N][M];
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            scanf("%d", &parking_lot[i][j]);
        }
    }

    find_parking_sections(N, M, parking_lot);

    return 0;
}
