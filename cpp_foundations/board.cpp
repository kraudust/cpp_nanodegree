#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

enum class State {kEmpty, kObstacle, kClosed, kPath};

/**
* @brief Takes a string of grid values (0's or 1's read from a file where 0 represents open and 1
* an obstacle) and converts it to a vector of State enums
*
* @param[in] line_cont:
*
* @return A vector of State enums
*/
std::vector<State> ParseLine(std::string line_cont){
  std::vector<State> board_row;
  std::istringstream board_row_stream(line_cont);
  char comma;
  int board_num;

  while(board_row_stream >> board_num >> comma) {
    if (board_num == 0){
      board_row.push_back(State::kEmpty);
    } else if (board_num == 1){
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
std::vector<std::vector<State>> ReadBoardFile(std::string path){
  std::vector<std::vector<State>> board_vec;
  std::ifstream board_file;
  board_file.open(path);
  if(board_file){
    std::string line;
    while(getline(board_file, line)){
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
bool Compare(std::vector<int> node1, std::vector<int> node2){
  int f_node1 = node1[2] + node1[3];
  int f_node2 = node2[2] + node2[3];
  return f_node1 > f_node2;
}

/**
 * @brief Sort the two-dimensional vector of ints in descending order.
 * @param[in] v: pointer to the list of cells (nodes) to sort (format is x, y, g, h)
 */
void CellSort(std::vector<std::vector<int>> *v) {
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
int Heuristic(int x1, int y1, int x2, int y2){
  return abs(x2 - x1) + abs(y2 - y1);
}

/**
* @brief Adds a node to the open vector with form (x, y, g, h)
*
* @param[in] x: The x coordinate of the node (0,0 is top left)
* @param[in] y: The y coordinate of the node (0,0 is top left)
* @param[in] g: The g value of the node (or accumulated cost)
* @param[in] h: The h value (from heuristic function) for the node
*
*/
void AddToOpen(int x, int y, int g, int h, std::vector<std::vector<int>> &open_nodes, 
               std::vector<std::vector<State>> &grid){
  std::vector<int> node_data{x, y, g, h};
  open_nodes.push_back(node_data);
  grid[x][y] = State::kClosed;
}

/**
* @brief Implementation of A* search algorithm
*
* @param[in] grid: The grid to search
* @param[in] start: An array with the start coordinates
* @param[in] goal: An array with the start coordinates
*
* @return TBD
*/
std::vector<std::vector<State>> Search(std::vector<std::vector<State>> grid, 
                                       int start[2], int goal[2]){
  // Vector of open nodes
  std::vector<std::vector<int>> open_vec;
  // Initialize starting node
  AddToOpen(start[0], start[1], 0, Heuristic(start[0], start[1], goal[0], goal[1]), open_vec, grid);

  while (!open_vec.empty()){
    // Sort the open list and get the current node
    CellSort(&open_vec);
    std::vector<int> current_node = open_vec.back();
    open_vec.pop_back();
    // Get the x and y values of the current node and set grid[x][y] to kpath
    int x = current_node[0];
    int y = current_node[1];
    grid[x][y] = State::kPath;

    // Check if we've reached the goal node
    if (x == goal[0] && y == goal[1]){
      return grid;
    }
      // If we're not done, expand search to current node's neighbors. TODO
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
* @return Either 0 string if empty space, or mountain if there is an obstacle
*/
std::string CellString(State state){
  std::string return_str;
  switch(state){
    case State::kEmpty:
      return_str = "0   ";
      break;
    case State::kObstacle:
      return_str = "⛰️   "; // A mountain is "\u26F0   "
      break;
  }
  return return_str;
}

/**
* @brief Prints the grid in a nice format showing cell occupancyh
*
* @param[in] board: The grid to print
*/
void PrintBoard(std::vector<std::vector<State>> board){
  for (std::vector<State> row: board){
    for (State col: row) {
      std::cout << CellString(col);
    }
    std::cout << '\n';
  }
}

int main() {
  int init[2]{0, 0};
  int goal[2]{4, 5};
  std::vector<std::vector<State>> board;
  board = ReadBoardFile("1.board");
  std::vector<std::vector<State>> solution = Search(board, init, goal);
  PrintBoard(solution);
  return 0;
}