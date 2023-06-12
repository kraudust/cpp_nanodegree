#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

enum class State {kEmpty, kObstacle, kClosed, kPath, kStart, kFinish};

// directional deltas
const int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

/**
* @brief Takes a string of grid values (0's or 1's read from a file where 0 represents open and 1
* an obstacle) and converts it to a vector of State enums
*
* @param[in] line_cont:
*
* @return A vector of State enums
*/
std::vector<State> ParseLine(std::string line_cont)
{
  std::vector<State> board_row;
  std::istringstream board_row_stream(line_cont);
  char comma;
  int board_num;

  while (board_row_stream >> board_num >> comma) {
    if (board_num == 0) {
      board_row.push_back(State::kEmpty);
    } else if (board_num == 1) {
      board_row.push_back(State::kObstacle);
    }
  }
  return board_row;
}

/**
* @brief Reads a board file line by line and makes a vector of vectors of State enums, all rows must
* end in a comma for this to work properly
*
* @param[in] path: the path and file of the .board file
*
* @return A vector of vectors of State enums representing the cells either with or without obstacles
*/
std::vector<std::vector<State>> ReadBoardFile(std::string path)
{
  std::vector<std::vector<State>> board_vec;
  std::ifstream board_file;
  board_file.open(path);
  if (board_file) {
    std::string line;
    while (getline(board_file, line)) {
      board_vec.push_back(ParseLine(line));
    }
  }
  return board_vec;
}

/**
* @brief Returns true if node1 has a greater f-value than node2 and false otherwise
*
* @param[in] node1: the first node (format is x, y, g, h)
* @param[in] node2: the second node (format is x, y, g, h)
*
* @return True if first node has a greater f-value than the second node
*/
bool Compare(std::vector<int> node1, std::vector<int> node2)
{
  int f_node1 = node1[2] + node1[3];
  int f_node2 = node2[2] + node2[3];
  return f_node1 > f_node2;
}

/**
 * @brief Sort the two-dimensional vector of ints in descending order.
 * @param[in] v: pointer to the list of cells (nodes) to sort (format is x, y, g, h)
 */
void CellSort(std::vector<std::vector<int>> * v)
{
  std::sort(v->begin(), v->end(), Compare);
}

/**
* @brief Calculates the Manhatten distance between two points (x1,y1) and (x2,y2) (0,0 is top left)
*
* @param[in] x1: The x coordinate of point 1
* @param[in] y1: The y coordinate of point 1
* @param[in] x2: The x coordinate of point 2
* @param[in] y2: The y coordinate of point 2
*
* @return And int with the manhatten distance between the two points
*/
int Heuristic(int x1, int y1, int x2, int y2)
{
  return abs(x2 - x1) + abs(y2 - y1);
}

/**
* @brief Returns true if a cell is within bounds for the grid and not an obstacle, otherwise false
*
* @param[in] x: The x coordinate of the node
* @param[in] y: The y coordinate of the node
* @param[in] grid: A reference to the grid
*
* @return Returns true if a cell is within bounds for the grid and not an obstacle, otherwise false
*/
bool CheckValidCell(int x, int y, std::vector<std::vector<State>> & grid)
{
  // Check if cell is on the grid and not an obstacle
  if (x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size()) {
    return grid[x][y] == State::kEmpty;
  } else {
    return false;
  }
}

/**
* @brief Adds a node to the open vector with form (x, y, g, h)
*
* @param[in] x: The x coordinate of the node, x represents rows (0 at the top)
* @param[in] y: The y coordinate of the node, y represents columns (0 at left)
* @param[in] g: The g value of the node (or accumulated cost)
* @param[in] h: The h value (from heuristic function) for the node
*
*/
void AddToOpen(
  int x, int y, int g, int h, std::vector<std::vector<int>> & open_nodes,
  std::vector<std::vector<State>> & grid)
{
  std::vector<int> node_data{x, y, g, h};
  open_nodes.push_back(node_data);
  grid[x][y] = State::kClosed;
}

/**
* @brief Expand current nodes's neighbors and add them to the open list
*
* @param[in] current_node: Current node information (x, y, g, h)
* @param[in] goal: (x, y) goal coordinates
* @param[in] open_vec: vector of open nodes with same info listed in current node
* @param[in] grid: state information of the grid
*
*/
void ExpandNeighbors(
  std::vector<int> & current_node, int goal[2],
  std::vector<std::vector<int>> & open_vec, std::vector<std::vector<State>> & grid)
{
  // Get current node's data
  int x_cur = current_node[0];
  int y_cur = current_node[1];
  int g_cur = current_node[2];

  // Loop through current node's potential neighbors
  for (int i = 0; i < 4; ++i) {
    int x_new = delta[i][0] + x_cur;
    int y_new = delta[i][1] + y_cur;
    if (CheckValidCell(x_new, y_new, grid)) {
      int g_new = g_cur + 1;
      int h_new = Heuristic(x_new, y_new, goal[0], goal[1]);
      AddToOpen(x_new, y_new, g_new, h_new, open_vec, grid);
    }
  }
}

/**
* @brief Implementation of A* search algorithm
*
* @param[in] grid: The grid to search
* @param[in] start: An array with the start coordinates
* @param[in] goal: An array with the start coordinates
*
* @return grid containing open cells, path to goal, and obstacles
*/
std::vector<std::vector<State>> Search(
  std::vector<std::vector<State>> grid, int start[2], int goal[2])
{
  // Vector of open nodes
  std::vector<std::vector<int>> open_vec;
  // Initialize starting node
  AddToOpen(start[0], start[1], 0, Heuristic(start[0], start[1], goal[0], goal[1]), open_vec, grid);

  while (!open_vec.empty()) {
    // Sort the open list and get the current node
    CellSort(&open_vec);
    std::vector<int> current_node = open_vec.back();
    open_vec.pop_back();
    // Get the x and y values of the current node and set grid[x][y] to kpath
    int x = current_node[0];
    int y = current_node[1];
    grid[x][y] = State::kPath;

    // Check if we've reached the goal node
    if (x == goal[0] && y == goal[1]) {
      grid[start[0]][start[1]] = State::kStart;
      grid[x][y] = State::kFinish;
      return grid;
    }
    // If we're not done, expand search to current node's neighbors.
    ExpandNeighbors(current_node, goal, open_vec, grid);
  }

  // We'ver run out of new nodes to explore and haven't found a path
  std::cout << "No path found!\n";
  std::vector<std::vector<State>> result;
  return result;
}

/**
* @brief Converts State enums to either a 0 or mountain (obstacle) in a string for printing grid
*
* @param[in] state: The state to convert
*
* @return Either 0 string if empty space, or mountain if there is an obstacle, or car if path
*/
std::string CellString(State state)
{
  std::string return_str;
  switch (state) {
    case State::kObstacle:
      return_str = "⛰️   ";  // A mountain is "\u26F0   "
      break;
    case State::kPath:
      return_str = "🚗  ";
      break;
    case State::kStart:
      return_str = "🚦  ";
      break;
    case State::kFinish:
      return_str = "🏁 ";
      break;
    default:
      return_str = "0   ";
  }
  return return_str;
}

/**
* @brief Prints the grid in a nice format showing cell occupancyh
*
* @param[in] board: The grid to print
*/
void PrintBoard(std::vector<std::vector<State>> board)
{
  for (std::vector<State> row : board) {
    for (State col : row) {
      std::cout << CellString(col);
    }
    std::cout << '\n';
  }
}

int main()
{
  int init[2]{0, 0};
  int goal[2]{4, 5};
  std::vector<std::vector<State>> board;
  board = ReadBoardFile("1.board");
  std::vector<std::vector<State>> solution = Search(board, init, goal);
  PrintBoard(solution);
  return 0;
}
