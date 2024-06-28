def main():
    n = int(input())  # Number of cars
    cars = []  # List to store car velocity and durability (v, w)

    for _ in range(n):
        v, w = map(int, input().split())
        cars.append((v, w))

    # Sort cars by velocity (v) in ascending order
    cars.sort(key=lambda x: x[0])

    # Initialize the maximum durability (w_max) encountered so far
    w_max = 0
    total_crossed_cars = 0

    # Iterate through the sorted cars
    for v, w in cars:
        # Update w_max if the current car's durability (w) is greater
        w_max = max(w_max, w)
        if w == w_max:
            total_crossed_cars += 1

    print(total_crossed_cars)

if __name__ == "__main__":
    main()
