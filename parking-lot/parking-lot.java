import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

class Section {
    List<Integer> row = new ArrayList<>();
    List<Integer> col = new ArrayList<>();
}

public class ParkingLotSections {

    // Initialize a section
    static void initSection(Section section) {
        section.row.clear();
        section.col.clear();
    }

    // Add a spot to the section
    static void addSpot(Section section, int row, int col) {
        section.row.add(row);
        section.col.add(col);
    }

    // Depth-first search to find a section
    static void dfs(int row, int col, int N, int M, int[][] parkingLot,
                    Section currentSection, boolean[][] visited) {
        if (row < 0 || row >= N || col < 0 || col >= M || visited[row][col] || parkingLot[row][col] == 1) {
            return;
        }

        visited[row][col] = true;
        addSpot(currentSection, row, col);

        // Explore neighboring spots
        dfs(row + 1, col, N, M, parkingLot, currentSection, visited);
        dfs(row - 1, col, N, M, parkingLot, currentSection, visited);
        dfs(row, col + 1, N, M, parkingLot, currentSection, visited);
        dfs(row, col - 1, N, M, parkingLot, currentSection, visited);
    }

    // Find parking sections
    static int findParkingSections(int[][] parkingLot) {
        int N = parkingLot.length;
        int M = parkingLot[0].length;
        boolean[][] visited = new boolean[N][M];
        List<Section> sections = new ArrayList<>();
        int maxScore = 0;

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (parkingLot[i][j] != 1 && !visited[i][j]) {
                    sections.add(new Section());
                    initSection(sections.get(sections.size() - 1));
                    dfs(i, j, N, M, parkingLot, sections.get(sections.size() - 1), visited);

                    // Calculate score for this section
                    int score = 0;
                    for (int k = 0; k < sections.get(sections.size() - 1).row.size(); ++k) {
                        int r = sections.get(sections.size() - 1).row.get(k);
                        int c = sections.get(sections.size() - 1).col.get(k);
                        score += (parkingLot[r][c] == 0) ? 1 : -2;
                    }
                    maxScore = Math.max(maxScore, score);
                }
            }
        }

        return maxScore;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter N (rows) and M (columns): ");
        int N = scanner.nextInt();
        int M = scanner.nextInt();

        // Constraints: 1 <= N, M <= 2000
        if (N < 1 || M < 1 || N > 2000 || M > 2000) {
            System.out.println("Invalid input. N and M must be between 1 and 2000.");
            return;
        }

        int[][] parkingLot = new int[N][M];
        System.out.println("Enter 0 for empty, 1 for occupied, 2 for accessible:");
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                parkingLot[i][j] = scanner.nextInt();
            }
        }

        int highestScore = findParkingSections(parkingLot);
        System.out.println("Highest score: " + highestScore);
    }
}
