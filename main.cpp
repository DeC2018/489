#include <iostream>
#include <set>
#include <vector>
#include <utility>

using namespace std;

// Mock Robot class with room simulation
class Robot {
public:
    vector<vector<int>> room; // Simulated room grid
    int row, col; // Current position of the robot
    int dir; // Current direction of the robot (0: up, 1: right, 2: down, 3: left)

    Robot(vector<vector<int>> roomGrid, int startRow, int startCol) {
        room = roomGrid;
        row = startRow;
        col = startCol;
        dir = 0; // Start facing up
    }

    // Returns true if the cell in front is open and robot moves into the cell
    bool move() {
        int newRow = row;
        int newCol = col;

        // Calculate the new position based on the current direction
        if (dir == 0) newRow--;
        else if (dir == 1) newCol++;
        else if (dir == 2) newRow++;
        else if (dir == 3) newCol--;

        // Check if the new position is within bounds and is an empty cell
        if (newRow >= 0 && newRow < room.size() && newCol >= 0 && newCol < room[0].size() && room[newRow][newCol] == 1) {
            row = newRow;
            col = newCol;
            cout << "Robot moved to (" << row << ", " << col << ")." << endl;
            return true;
        }

        cout << "Robot hit a wall." << endl;
        return false;
    }

    // Robot will stay in the same cell after calling turnLeft/turnRight
    void turnLeft() {
        dir = (dir - 1 + 4) % 4; // Update direction
        cout << "Robot turned left. Now facing: " << dir << endl;
    }

    void turnRight() {
        dir = (dir + 1) % 4; // Update direction
        cout << "Robot turned right. Now facing: " << dir << endl;
    }

    // Clean the current cell
    void clean() {
        room[row][col] = 2; // Mark the cell as cleaned
        cout << "Robot cleaned cell (" << row << ", " << col << ")." << endl;
    }
};

class Solution {
public:
    Robot* robot;
    set<pair<int, int>> visited; // To keep track of visited cells
    vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; // Up, Right, Down, Left

    // Function to make the robot go back to the previous cell
    void goBack() {
        robot->turnRight();
        robot->turnRight();
        robot->move();
        robot->turnRight();
        robot->turnRight();
    }

    // Backtracking function to clean the room
    void backtrack(int row, int col, int d) {
        visited.insert({row, col}); // Mark the current cell as visited
        robot->clean(); // Clean the current cell

        // Explore all four directions
        for (int i = 0; i < 4; ++i) {
            int newD = (d + i) % 4; // Calculate the new direction
            int newRow = row + directions[newD].first;
            int newCol = col + directions[newD].second;

            // If the new cell is not visited and the robot can move there
            if (visited.find({newRow, newCol}) == visited.end() && robot->move()) {
                backtrack(newRow, newCol, newD); // Recurse into the new cell
                goBack(); // Go back to the previous cell
            }
            robot->turnRight(); // Turn right to try the next direction
        }
    }

    // Main function to start cleaning the room
    void cleanRoom(Robot* robot) {
        this->robot = robot;
        backtrack(0, 0, 0); // Start cleaning from cell (0, 0) facing direction 0 (up)
    }
};

int main() {
    // Define the room grid (1: empty, 0: wall)
    vector<vector<int>> room = {
        {1, 1, 1, 1, 1, 0, 1, 1},
        {1, 1, 1, 1, 1, 0, 1, 1},
        {1, 0, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1}
    };

    // Create a robot object with the room grid and starting position
    Robot robot(room, 1, 3);

    // Create a solution object
    Solution solution;

    // Start cleaning the room
    solution.cleanRoom(&robot);

    cout << "Robot cleaned all rooms." << endl;
    return 0;
}
