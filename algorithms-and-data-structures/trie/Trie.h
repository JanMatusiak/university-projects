#ifndef TRIE_H
#define TRIE_H

class Trie {
private:

    static constexpr int EMPTY = -1; // when there is no value, the key is -1

    struct Node { // each Trie node stores the key and the pointer to the array of child-nodes
        int key = EMPTY; // since all legitimate keys are non-negative integers
        Node** kids = nullptr; // until the node gains children, the array is nullptr
    };

    int n, k;
    Node* root;

    Node* make_root(); // create root and allocate its n-sized children array
    Node* make_node(); // to create ordinary nodes during insertion
    void destroy_subtree(Node* node); // helper recursive function to free memory
    void print_node(const Node* node) const;
    // helper functions for removal
    void prune_empty_children(Node* node);
    Node* find_leftmost_leaf(Node* node, Node** out_parent, int* out_index);

public:
    Trie(int n, int k);
    ~Trie();

    // basic Trie operations
    Node* find(int* x) const;
    bool insert(int* x);
    bool remove(int* x);
    void print() const;
};

#endif // TRIE_H
