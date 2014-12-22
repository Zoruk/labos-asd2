#ifndef STRINGTERNARYSEARCHTRIE_H
#define STRINGTERNARYSEARCHTRIE_H

#include <string>

class TernarySearchTrie
{
private:
    struct Node {
    public:
        char value;
        Node* right;  // sous arbre avec des cles plus grandes
        Node* center;
        Node* left;   // sous arbre avec des cles plus petites
        bool isEnd;   // un mot se termine sur cd noeud
        //size_t nodeSize; // taille du sous-arbre dont ce noeud est la racine.
        //size_t nodeHeight; // hauteur du sous-arbre dont ce noeud est la racine.
        Node(char value) : value(value),
            right(nullptr), center(nullptr), left(nullptr),
            isEnd(false) /*, nodeHeight(0)*/
        { }
        ~Node() { if (right) delete right; if (center) delete center; if (left) delete left; }
    };

    Node* root;
    Node* insert(Node* node, const char* str);
    Node* remove(Node* node, const char* str);

    bool contain(const Node* node, const char* str) const;

public:
    TernarySearchTrie();
    ~TernarySearchTrie() {if (root) delete root; }

    void insert(std::string str);
    bool contain(const std::string str) const;
};

#endif // STRINGTERNARYSEARCHTRIE_H
