/**
 * @author Talha Rahman
 * Course: CSCI-135
 * Instructor: Maryash
 * Project 3
 */

// This program is used to control the movement of 
// the dwarves, such as getting them to walk around
// in addition it can also control which trees they cut
// and a few other stuff.
#include <cstdlib>
#include <cmath>
#include "bot.h"
using std::to_string;

const int MAX_ROWS = 40;
const int MAX_COLS = 40;
const int MAX_NUM = 10;

int ROWS;  // global variables
int COLS;
int NUM;

// For debugging
// std::ofstream file("report.txt");
// std::string output = "";

/* onStart: 
An Initialization procedure called at the start of the game.
You can use it to initialize certain global variables, or do 
something else before the actual simulation starts.
Parameters:
    rows: number of rows
    cols: number of columns
    num:  number of dwarfs
    log:  a cout-like log */

void onStart(int rows, int cols, int num, std::ostream &log) {
  log << "Start!" << std::endl; // Print a greeting message

  ROWS = rows; // Save values in global variables
  COLS = cols;
  NUM = num;
}

/* onAction: 
A procedure called each time an idle dwarf is choosing 
their next action.
Parameters:
    dwarf:   dwarf choosing an action
    day:     day (1+)
    hours:   number of hours in 24-hour format (0-23)
    minutes: number of minutes (0-59)
    log:     a cout-like log  */

void onAction(Dwarf &dwarf, int day, int hours, int minutes, std::ostream &log) {
  // Get current position of the dwarf
  int r = dwarf.row();
  int c = dwarf.col();
  Dir dir;

  // Checks for any adjacent trees
  if (isNextToTree(dwarf, dir) ){
    log << "Dwarf " << dwarf.name() << " - Chopping Tree at (" << r << "," << c << ")\n";
    dwarf.start_chop(dir);
    return;
  } 

  // pair.first == true if a tree was found nearby
  auto pair = lookForNearestTree(dwarf);

  if (pair.first) {
    // pair.second is the Point of the nearest Tree
    r = pair.second.x;
    c = pair.second.y;
    log << "Dwarf " << dwarf.name() << " - Tree found. Walking to (" << r << "," << c << ")\n";
    dwarf.start_walk(r, c);
    return;
  } else {
    // if no tree was found just go to a random spot
    goToRandomPosition(dwarf, log);
    return;
  }

}

void goToRandomPosition(Dwarf& dwarf, std::ostream& log) {
  int rr = rand() % ROWS; 
  int cc = rand() % COLS;
  log << "Dwarf " << dwarf.name() << " - Randomly walking to (" << rr << "," << cc << ")\n";
  dwarf.start_walk(rr, cc);
}

bool isNextToTree(Dwarf& dwarf, Dir& dir) {
  // Returns true if place is a tree. Else false.
  auto isTree( [] (Place p) -> bool
    { return p == PINE_TREE || p == APPLE_TREE; }
  );

  const int R = dwarf.row();
  const int C = dwarf.col();

  if (isTree(dwarf.look(R, C + 1))) { // Checks East
    dir = EAST;
    return true;
  }

  if (isTree(dwarf.look(R, C - 1))) { // Checks West
    dir = WEST;
    return true;
  }

  if (isTree(dwarf.look(R - 1, C))) { // Checks North
    dir = NORTH;
    return true;
  }

  if (isTree(dwarf.look(R + 1, C))) { // Checks South
    dir = SOUTH;
    return true;
  }

  return false;
}

bool isValidSpace(const int& r, const int& c) {
  if ((r < 0 || c < 0) or (r >= ROWS || c >= COLS)) 
    return false;
  return true; 
}


/**
 *   1 2 3 4 5   D = Dwarf. (row, col)
 * 1 X X X X X   Algo will check nearby tiles for Tree
 * 2 X X X X X   Order of checking: 
 * 3 X X D X X   (2,2) -> (3, 2) -> (4, 2)
 * 4 X X X X X   (4, 3) -> (4, 4) -> (3, 4)
 * 5 X X X X X   (2, 4) -> (2, 3) -> (2, 2)
 *               Will repeat this type of search at (1,1) and so forth
 */ 

std::pair<bool, Point> lookForNearestTree(Dwarf& dwarf) {
  // Returns true if place is a tree. Else false.
  auto isTree( [] (Place p) -> bool
    { return p == PINE_TREE || p == APPLE_TREE; }
  );

  // will hold Points that point to nearby trees
  std::list<Point> list;
  bool found = false;

  int startR = dwarf.row();
  int startC = dwarf.col();

  int size = std::max(ROWS, COLS);

  // worst case algorithm repeats max(ROS, COLS)
  for (int i = 1; i < size; ++i) {
    // (r, c) is a point north-west of the dwarf
    int r = startR - i;
    int c = startC - i;

    // checks from top-left to bottom-left
    for(; r < startR + i; ++r) {
      // skips if (r, c) not a valid position on map
      if(!isValidSpace(r, c)) continue;
      
      if (isTree(dwarf.look(r, c))) {
        auto pair = checkForAdjacentSpace(dwarf, r, c);
        if (pair.first) {
          list.push_back(pair.second);
          found = true;
        }
      }
    }

    // checks from bottom-left to bottom-right
    for(; c < startC + i; ++c) {
      if(!isValidSpace(r, c)) continue;
      
      if (isTree(dwarf.look(r, c))) {
        auto pair = checkForAdjacentSpace(dwarf, r, c);
        if (pair.first) {
          list.push_back(pair.second);
          found = true;
        }
      }
    }

    // checks from bottom-right to top-right
    for(; r > startR - i; --r) {
      if(!isValidSpace(r, c)) continue;
      
      if (isTree(dwarf.look(r, c))) {
        auto pair = checkForAdjacentSpace(dwarf, r, c);
        if (pair.first) {
          list.push_back(pair.second);
          found = true;
        }
      }
    }

    // checks from top-right to top-left
    for(; c > startC - i; --c) {
      if(!isValidSpace(r, c)) continue;
      
      if (isTree(dwarf.look(r, c))) {
        auto pair = checkForAdjacentSpace(dwarf, r, c);
        if (pair.first) {
          list.push_back(pair.second);
          found = true;
        }
      }
    }
  }

  if (found) {
    return std::make_pair(true, calcNearestPointToDwarf(dwarf, list));
  } else {
    // file << output << "\n"; // for debugging
    return std::make_pair(false, Point{});
  }
}

std::pair<bool, Point> checkForAdjacentSpace(Dwarf& dwarf, const int& r, const int& c) {
  std::list<Point> list;
  bool found = false;
  
  if (dwarf.look(r - 1, c) == EMPTY ){ // NORTH
    list.push_back(Point(r - 1, c));
    found = true;
  }
  if (dwarf.look(r, c + 1) == EMPTY) { // EAST
    list.push_back(Point(r, c + 1));
    found = true;
  }
  if (dwarf.look(r + 1, c) == EMPTY) { // SOUTH
    list.push_back(Point(r + 1, c));
    found = true;
  }
  if (dwarf.look(r, c - 1) == EMPTY) { // WEST
    list.push_back(Point(r, c - 1));
    found = true;
  }
  
  // If multiple empty spots were found, return only the closest
  if (found) {
    Point nearestPoint = calcNearestPointToDwarf(dwarf, list);
    return std::make_pair(true, Point{nearestPoint.x, nearestPoint.y});
  }
  
  return std::make_pair(false, Point{});
}

Point calcNearestPointToDwarf(Dwarf& dwarf, const std::list<Point>& list) {
  Point nearestPoint;
  int distance = INT32_MAX;

  for(auto& point : list) {
    int currentDist = abs(dwarf.row() - point.x) + abs(dwarf.col() - point.y);

    // if the current Point is closer than the previous closest distance
    // then we set this Point as the nearestPoint
    if (currentDist < distance) {
      nearestPoint = point;
      distance = currentDist;
    }
  }

  return nearestPoint;
}