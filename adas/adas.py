import heapq

def calculate_risk_score(grid, W, H):
    risk_score = 0
    visited = set()
    pq = [(0, 0, 0)]  # (risk_score, x, y)
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]

    while pq:
        risk, x, y = heapq.heappop(pq)
        if (x, y) in visited:
            continue
        visited.add((x, y))

        # Increment risk for each adjacent 'P-' cell
        for dx, dy in directions:
            nx, ny = x + dx, y + dy
            # Check boundaries before accessing grid elements
            if 0 <= nx < W and 0 <= ny < H: 
                if grid[nx][ny] == 'P-': 
                    risk_score += 1 # Increment risk directly for each 'P-'

        # Add adjacent points to the queue
        for dx, dy in directions:
            nx, ny = x + dx, y + dy
            if 0 <= nx < W and 0 <= ny < H and (nx, ny) not in visited:
                heapq.heappush(pq, (risk, nx, ny))

    return risk_score

# Example usage
W, H = 4, 4 # Adjusted dimensions to match the grid
grid = [
    ['P-', '.', '.', '.'],
    ['P-', 'P-', 'P-', 'P-'],
    ['.', '.', '.', 'S'],
    ['.', 'E', 'P-', '.']
]

result = calculate_risk_score(grid, W, H)
print("Risk Score:", result)
