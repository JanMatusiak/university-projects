#ifndef BINARYHEAP_H
#define BINARYHEAP_H

#include "Structs.h"
#include <cstdlib>

class BinaryHeap { // array that represents a complete binary tree
    HeapNode* array;
    int size; // current number of HeapNodes
    int capacity; // maximum possible number of HeapNodes

    // min-heap rule is: time(parent) <= time(child)
    inline static void swap(HeapNode& previousNode, HeapNode& newNode){
        HeapNode temp = previousNode;
        previousNode = newNode;
        newNode = temp;
    }

    inline void move_up(int i){
    // parent of a node at index i is at index (i-1)/2
    // left child of a node at index i is at index (2i + 1)
    // right child of a node at index i is at index (2i + 2)
        while(i && array[(i-1)/2].time > array[i].time){ // while time(parent) > time(child)
            swap(array[i], array[(i-1)/2]); // we swap the parent and the child
            i = (i - 1)/2; // we change the index to point at where the child is now
        }
    }
    inline void move_down(int i){
        while(1){
            int left = 2*i + 1;
            int right = 2*i + 2;
            int parent = i;
            if(left < size && array[parent].time > array[left].time) parent = left;
            if(right < size && array[parent].time > array[right].time) parent = right;
            if(parent == i) break; // we break if time(parent) <= time(child) or left/right >= size
            swap(array[i], array[parent]);
            i = parent;
        }
    }

    // disallowing copying 
    BinaryHeap(const BinaryHeap&) = delete;
    BinaryHeap& operator=(const BinaryHeap&) = delete;

public:
    explicit BinaryHeap(int capacity) : size(0), capacity(capacity){
        array = static_cast<HeapNode*>(malloc(capacity * sizeof(HeapNode))); // an array of HeapNode structs
    }
    
    ~BinaryHeap(){ free(array); }

    inline bool empty() const{
        return size == 0;
    }

    inline void push(int vertex, int time){
        array[size] = {vertex, time};
        move_up(size);
        size++;
    }

    inline bool pop_min(int& vertex, int& time){
        if(size == 0) return false;
        vertex = array[0].vertex;
        time = array[0].time;   
        if(--size){
            array[0] = array[size];
            move_down(0);
        }
    return true;
    }

} ;

#endif