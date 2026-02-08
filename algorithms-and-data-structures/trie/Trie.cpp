#include "Trie.h"
#include <stdio.h>

Trie::Trie(int n, int k) : n(n), k(k) {
    root = make_root();
}

Trie::~Trie() {
    destroy_subtree(root);
}

Trie::Node* Trie::make_root() {
    Node* r = new Node;
    r->key = EMPTY;
    r->kids = new Node*[n]();
    return r;
}

Trie::Node* Trie::make_node() {
    Node* node = new Node;
    node->key = EMPTY;
    node->kids = nullptr;
    return node;
}

void Trie::destroy_subtree(Node* node) {
    if (!node) return;
    int rows = (node == root ? n : k); // only root has n children, nodes at deeper levels have at most k nodes
    if (node->kids) {
        for (int i = 0; i < rows; i++){
            destroy_subtree(node->kids[i]); 
        }
        delete[] node->kids;
    }
    delete node;
}

void Trie::print_node(const Node* node) const {
    if (!node) return;
    if (node->key != EMPTY){
        printf("%d ", node->key);
    }

    int rows = (node == root ? n : k);
    for (int i = 0; i < rows; i++){
        if (node->kids && node->kids[i]){
            print_node(node->kids[i]);
        }
    }
}

void Trie::prune_empty_children(Node* node) { // if after deletion the parent node has no children, we can free the array
    if (!node->kids) return;
    int rows = (node == root ? n : k);
    for (int i = 0; i < rows; i++){
        if (node->kids[i]) return;
    }
    delete[] node->kids;
    node->kids = nullptr;
}

Trie::Node* Trie::find_leftmost_leaf(Node* node, Node** out_parent, int* out_index) { // DFS for the leftmost leaf in this subtree
    if (!node || !node->kids) return nullptr;
    int rows = (node == root ? n : k);
    for (int i = 0; i < rows; i++) {
        Node* child = node->kids[i];
        if (!child) continue;
        bool has_kids = (child->kids != nullptr);
        if (!has_kids) { // we found the leaf
            *out_parent = node; // we record its parent
            *out_index = i; // and the index in its parent's kids array 
            return child;
        }
        Node* leaf = find_leftmost_leaf(child, out_parent, out_index); // if the node had kids, we recursively call the function again
        if (leaf) return leaf;
    }
    return nullptr;
}

Trie::Node* Trie::find(int* x) const { // we find and return the node with the key that was passed
    if (root->key == *x) return root;

    int size = n;
    int div = *x;
    Node* current = root;

    while (true) {
        int row = div % size;
        div /= size;

        if (!current->kids || !current->kids[row]){
            return nullptr;
        }

        current = current->kids[row];

        if (current->key == *x){
            return current;
        }

        if (current->key == EMPTY){
            return nullptr;
        }

        size = k;
    }
}

bool Trie::insert(int* x) {
    if (find(x)) { // first we check if x already exists
        printf("%d exist\n", *x);
        return false;
    }
    if (root->key == EMPTY) {
        root->key = *x; // if root is empty, x goes to the root
        return true;
    }
    int size = n; // number of children at current depth
    int div = *x; 
    Node* current = root;

    while (true) {
        int row = div % size; // we calculate the index for x
        div /= size; 

        if (!current->kids){
            current->kids = new Node*[size](); // we create the array of nodes if it does not exist yet
        }

        if (!current->kids[row]){
            current->kids[row] = make_node(); // we make a node if it does not exist yet
        }

        current = current->kids[row];

        if (current->key == EMPTY) { 
            current->key = *x; 
            return true;
        }
        size = k; // new size - always k at further levels
    }
}

bool Trie::remove(int* x) {
    if (!root) {
        printf("%d not exist\n", *x);
        return false;
    }

    if (root->key == *x) { // case 1: key stored at the root
        if (!root->kids) { 
            root->key = EMPTY;
            return true;
        }
        Node* parent1 = nullptr; 
        int index1 = -1;
        Node* leaf1 = find_leftmost_leaf(root, &parent1, &index1); // if root has kids, we search for the leftmost leaf of the entire tree 
        if (!leaf1) { 
            delete[] root->kids;
            root->kids = nullptr;
            root->key  = EMPTY;
            return true;
        }
        root->key = leaf1->key; // leaf key is now at the root
        delete leaf1; 
        parent1->kids[index1] = nullptr; // we unlink the leaf from its parent
        prune_empty_children(parent1); // if parent's array is now empty, we delete it
        return true;
    }

    // case 2: key stored elsewhere in the trie - we have to find it
    Node* current = root;
    Node* parent2 = nullptr;
    int index2 = -1; // remembers which index the node we are looking for had in its parent->kids array
    int div = *x;
    int rows = n;

    while (true) {
        int row = div % rows;
        div /= rows;

        if (!current->kids || !current->kids[row]) { // such key does not exist
            printf("%d not exist\n", *x);
            return false;
        }
        parent2 = current;
        index2 = row;
        current = current->kids[row];

        if (current->key == *x) break; // we found the node to remove
        if (current->key == EMPTY) {
            printf("%d not exist\n", *x);
            return false;
        }
        rows = k;
    }

    if (!current->kids) { // case 2A: the node we found is a leaf - we delete it
        delete current;
        parent2->kids[index2] = nullptr; 
        prune_empty_children(parent2); // if parent's array is now empty, we delete it
        return true;
    }

    // case 2B: the node has its own kids, so we swap it with the leftmost leaf of its subtree
    Node* parent3 = nullptr;
    int index3 = -1;
    Node* leaf3 = find_leftmost_leaf(current, &parent3, &index3);
    current->key = leaf3->key; // leaf key is now the node's key
    delete leaf3;
    parent3->kids[index3] = nullptr;
    prune_empty_children(parent3);
    return true;
}

void Trie::print() const {
    print_node(root);
    putchar('\n');
}
