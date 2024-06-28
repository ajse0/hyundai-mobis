#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;  // Number of cars

    // Initialize arrays to store car velocity and durability (v, w)
    int v[n], w[n];
    for (int i = 0; i < n; ++i) {
        cin >> v[i] >> w[i];
    }

    // Sort cars by velocity (v) in ascending order (using bubble sort)
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (v[j] > v[j + 1]) {
                // Swap v[j] and v[j + 1]
                int temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;

                // Swap w[j] and w[j + 1] accordingly
                temp = w[j];
                w[j] = w[j + 1];
                w[j + 1] = temp;
            }
        }
    }

    // Initialize the maximum durability (w_max) encountered so far
    int w_max = 0;
    int total_crossed_cars = 0;

    // Iterate through the sorted cars
    for (int i = 0; i < n; ++i) {
        // Update w_max if the current car's durability (w) is greater
        w_max = max(w_max, w[i]);
        if (w[i] == w_max) {
            total_crossed_cars++;
        }
    }

    cout << total_crossed_cars << endl;

    return 0;
}
