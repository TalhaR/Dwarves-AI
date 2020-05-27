/**
 * @author Talha Rahman
 * Course: CSCI-135
 * Instructor: Maryash
 * Project 3
 */

#ifndef BOT_H
#define BOT_H

#include <iostream>
#include <list>
#include "dwarf.h"

/**
 * Simple struct to represent a 2D Point
 */
struct Point {
    int x;
    int y;

    Point() = default;
    Point(int x, int y) 
        : x(x), y(y) {}
};

/**
 * @brief Places the dwarf in a random position
 * @param dwarf Dwarf object
 * @param log std::ostream object for console output
 */
void goToRandomPosition(Dwarf& dwarf, std::ostream& log);

/**
 * @post modifies Dir d to point in direction of nearest Tree
 *       if method returns true
 * @param dwarf Dwarf object
 * @param d Dir that represents a direction
 * @return true if dwarf is next to a tree. False otherwise.
 */
bool isNextToTree(Dwarf& dwarf, Dir& d);

/**
 * @param r int representing row
 * @param c int representing col
 * @return true if (r,c) is a valid position on the map
 */
bool isValidSpace(const int& r, const int& c);

/**
 * @brief Uses BFS pathfinding to locate nearest tree
 * @param dwarf Dwarf object
 * @return true if a non-adjacent tree was found. False otherwise.
 */
std::pair<bool, Point> lookForNearestTree(Dwarf& dwarf);

/**
 * @param dwarf Dwarf object
 * @param r int representing the row
 * @param c int representing the col
 * @return std::pair<bool, Point> where bool is True if an 
 */
std::pair<bool, Point> checkForAdjacentSpace(Dwarf& dwarf, const int& r, const int& c);

/**
 * @param dwarf Dwarf object
 * @param list List of Points 
 * @brief checks all Points in list to see which is closest to the dwarf
 * @return Coordinates of the nearest empty spot
 */
Point calcNearestPointToDwarf(Dwarf& dwarf, const std::list<Point>& list);


void onStart(int rows, int cols, int num, std::ostream &log);
// onStart: Called at the start, if you want to initialize certain global
// variables, or make something else before the actual simulation starts.
//
// Parameters:
//
// rows: number of rows
// cols: number of columns
// num:  number of dwarfs
//
// log:  a cout-like log


void onAction(Dwarf &dwarf, int day, int hours, int minutes, std::ostream &log);
// onAction: Called each time a dwarf is idle and choosing their next action.
//
// Parameters:
//
// dwarf:   dwarf choosing an action
// day:     day (1+)
// hours:   number of hours in 24-hour format (0-23)
// minutes: number of minutes (0-59)
//
// log:     a cout-like log

#endif
