import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int n = scanner.nextInt();  // Number of cars

        // Initialize arrays to store car velocity and durability (v, w)
        int[] v = new int[n];
        int[] w = new int[n];
        for (int i = 0; i < n; ++i) {
            v[i] = scanner.nextInt();
            w[i] = scanner.nextInt();
        }

        // Sort cars by velocity (v) in ascending order (using bubble sort)
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - i - 1; ++j) {
                if (v[j] > v[j + 1]) {
                    // Swap v[j] and v[j + 1]
                    int tempV = v[j];
                    v[j] = v[j + 1];
                    v[j + 1] = tempV;

                    // Swap w[j] and w[j + 1] accordingly
                    int tempW = w[j];
                    w[j] = w[j + 1];
                    w[j + 1] = tempW;
                }
            }
        }

        // Initialize the maximum durability (wMax) encountered so far
        int wMax = 0;
        int totalCrossedCars = 0;

        // Iterate through the sorted cars
        for (int i = 0; i < n; ++i) {
            // Update wMax if the current car's durability (w) is greater
            wMax = Math.max(wMax, w[i]);
            if (w[i] == wMax) {
                totalCrossedCars++;
            }
        }

        System.out.println(totalCrossedCars);
    }
}
