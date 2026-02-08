#ifndef STRUCTS_H
#define STRUCTS_H

struct Map {
    int rows;
    int columns;
    int **terrain; // a 2D array of heights
} ;

struct Lift {
    int s_x, s_y; // start coordinates of the lift
    int d_x, d_y; // end coordinates of the lift
    int travel_time;
    int departure_time; // how often the lift departs
} ;

struct HeapNode { 
    int vertex; // integer converted from the 2D coordinates (current row * columns + current column)
    int time; // time necessary to reach each vertex
} ;

#endif