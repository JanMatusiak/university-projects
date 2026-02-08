#include "Structs.h"
#include "BinaryHeap.h"
#include <cstdlib>
#include <cstdio>
#include <climits>

int calculate_step(int start_height, int dest_height){
    return (start_height > dest_height) ? 1 : (dest_height - start_height + 1);
}

int lift_step(Lift* lift, int time){
    if(lift->departure_time == 0 || time % lift->departure_time == 0) return lift->travel_time;
    return lift->travel_time + lift->departure_time - time % lift->departure_time;
}

int shortest_time(Map map, int start, int goal, Lift* lifts, int lift_num, int *first, int *next){
    int number_of_vertices = map.rows * map.columns;
    int *times = (int*)malloc(number_of_vertices * sizeof(int)); // we create an array which will store best known times to reach each vertex
    for(int i = 0; i < number_of_vertices; i++) times[i] = INT_MAX; // at first each best time is the largest possible integer 

    BinaryHeap priority_queue(number_of_vertices + lift_num + 8); // we create a priority queue with specific, sufficient capacity
    times[start] = 0; // in Djikstra Algorithm, first node gets the time 0
    priority_queue.push(start, 0);

    // possible directions to move
    int dx[4] = {0, 1, 0, -1}; 
    int dy[4] = {-1, 0, 1, 0};

    while(!priority_queue.empty()){
        int vertex, time;
        priority_queue.pop_min(vertex, time);
        if(time != times[vertex]) continue; // we do not process new time if we already know the best possible time to reach the vertex 
        if(vertex == goal){
            int answer = times[vertex];
            free(times);
            return answer;
        }

        int current_x = vertex % map.columns;
        int current_y = vertex / map.columns;


        for(int i = 0; i < 4; i++){ // we iterate through the neighbours
            int new_x = current_x + dx[i];
            int new_y = current_y + dy[i];
            if(new_x < 0 || new_x >= map.columns || new_y < 0 || new_y >= map.rows) continue; // skip if out of bounds
            int new_vertex = new_y * map.columns + new_x; // convert the 2D coordinates to one integer index
            int step = calculate_step(map.terrain[current_y][current_x], map.terrain[new_y][new_x]);
            if(time + step < times[new_vertex]){ // if new time is better than what is already stored in best times we switch it
                times[new_vertex] = time + step;
                priority_queue.push(new_vertex, times[new_vertex]); // then we push this new time on the heap
            }
        }

        for(int e = first[vertex]; e != -1; e = next[e]){ // we iterate through the all the lifts that start at the current vertex
            int new_vertex = lifts[e].d_y * map.columns + lifts[e].d_x; // convert the 2D coordinates of the destination to one integer index
            int step = lift_step(&lifts[e], time);
            if(time + step < times[new_vertex]){ // if new time is better than what is already stored in best times we switch it
                times[new_vertex] = time + step;
                priority_queue.push(new_vertex, times[new_vertex]); // then we push this new time on the heap
            }
        }
    }

    int answer = times[goal];
    free(times);
    return answer;
}

int main(){
    Map map;
    int start_x, start_y; 
    int dest_x, dest_y;
    int lift_num;

    scanf("%d %d %d %d %d %d %d", &map.columns, &map.rows, &start_x, &start_y, &dest_x, &dest_y, &lift_num);
    Lift *lifts = lift_num ? static_cast<Lift*>(malloc(lift_num * sizeof(Lift))) : nullptr; // array of lift objects 
    for(int i = 0; i < lift_num; i++){
        scanf("%d %d %d %d %d %d", &lifts[i].s_x, &lifts[i].s_y, &lifts[i].d_x, &lifts[i].d_y, &lifts[i].travel_time, &lifts[i].departure_time);
    }

    map.terrain = (int**)malloc(map.rows * sizeof *map.terrain);
    for(int i = 0; i < map.rows; i++){
        map.terrain[i] = (int*)malloc(map.columns * sizeof *map.terrain[i]);
        for(int j = 0; j < map.columns; j++){
            scanf("%d", &map.terrain[i][j]);
        }
    }

    int number_of_vertices = map.rows * map.columns;
    int* first = (int*)malloc(number_of_vertices * sizeof(int)); // first[v] will store the index of the first lift that starts at vertex v
    int* next = lift_num ? (int*)malloc(lift_num * sizeof(int)) : nullptr; // next[i] will be the index of the next lift that starts at the same vertex as lift i
    for(int v = 0; v < number_of_vertices; v++) first[v] = -1;  // -1 means that no lift starts there
    for(int i = 0; i < lift_num; i++){
        int v = lifts[i].s_y * map.columns + lifts[i].s_x; // vertex of the lift
        next[i] = first[v]; // old first lift becomes the next lift
        first[v] = i; // lift i is now first in the list
    }

    int start = start_y * map.columns + start_x;
    int goal = dest_y * map.columns + dest_x;

    int answer = shortest_time(map, start, goal, lifts, lift_num, first, next);
    printf("%d\n", answer);

    for(int i = 0; i < map.rows; ++i){
        free(map.terrain[i]);
    }
    free(map.terrain);
    free(first);
    if(next) free(next);
    if(lifts) free(lifts);

    return 0;
}