489. Robot Room Cleaner
https://leetcode.com/problems/robot-room-cleaner/description/

Description:

You control a robot in a room represented by an m x n binary grid, where 0 is a wall and 1 is an empty cell.
The robot starts in an unknown location, guaranteed to be empty.
You don't have access to the grid, but you can move the robot through the provided Robot API.
The robot needs to clear the entire room (i.e. all empty cells).
It can move forward, turn left or right 90 degrees.
If the robot hits a wall, its obstacle sensor detects this and it stays on the current cell.
Develop an algorithm to clean an entire room using the following API:
/**
 * // This is the robot's control interface.
 * // You should not implement it, or speculate about its implementation
 * class Robot {
 *  public:
 *   // Returns true if the cell in front is open and robot moves into the cell.
 *   // Returns false if the cell in front is blocked and robot stays in the current cell.
 *   bool move();
 *
 *   // Robot will stay in the same cell after calling turnLeft/turnRight.
 *   // Each turn will be 90 degrees.
 *   void turnLeft();
 *   void turnRight();
 *
 *   // Clean the current cell.
 *   void clean();
 * };
 */

Example:

Input: room = [[1,1,1,1,1,0,1,1],[1,1,1,1,1,0,1,1],[1,0,1,1,1,1,1,1],[0,0,0,1,0,0,0,0],[1,1,1,1,1,1,1,1]], row = 1, col = 3
Output: Robot cleaned all rooms.
Explanation: All grids in the room are marked by either 0 or 1.
0 means the cell is blocked, while 1 means the cell is accessible.
The robot initially starts at the position of row=1, col=3.
From the top left corner, its position is one row below and three columns right.
