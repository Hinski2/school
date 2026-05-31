#pragma once 

#include <cstdlib>
#include <utility>
namespace data_structures {

template<typename T>
class Treap {
    class Node {
        T key;
        int priority;
        Node *left, *right; 

        static std::pair<Node*, Node*> split(Node *t, const T& piv);
        static Node* merge(Node *l, Node *r);

    public:
        Node(T key, Node* left, Node* right, int priority = std::rand()):
            key{key}, priority{priority}, left{nullptr}, right{nullptr} {}

        static  
    };

    Node *root;
    public:
};

}
