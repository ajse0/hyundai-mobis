def find_parking_sections(parking_lot):

    rows = len(parking_lot)
    cols = len(parking_lot[0])

    # Check if dimensions are within bounds
    if not (1 <= rows <= 2000 and 1 <= cols <= 2000):
        return "Invalid parking lot dimensions." 


    sections = []
    visited = set()

    def dfs(row, col, current_section):
        if (
            row < 0
            or row >= rows
            or col < 0
            or col >= cols
            or (row, col) in visited
            or parking_lot[row][col] == 1
        ):
            return

        visited.add((row, col))
        current_section.append((row, col))

        # Explore neighboring spots
        dfs(row + 1, col, current_section)
        dfs(row - 1, col, current_section)
        dfs(row, col + 1, current_section)
        dfs(row, col - 1, current_section)

    # Iterate over the parking lot and find sections
    for i in range(rows):
        for j in range(cols):
            if parking_lot[i][j] != 1:
                section = []
                dfs(i, j, section)
                score = sum(+1 if parking_lot[r][c] == 0 else -2 for r, c in section)
                sections.append((section, score))
    
    return sections

# Get parking lot size and data
N, M = map(int, input("Enter N (rows) and M (columns): ").split())
parking_lot = [list(map(int, input().split())) for _ in range(N)]

parking_sections = find_parking_sections(parking_lot)

# Find the section with the highest score
max_score = 0
for section, score in parking_sections:
    if score > max_score:
        max_score = score

print(max_score)  # Print the highest score
