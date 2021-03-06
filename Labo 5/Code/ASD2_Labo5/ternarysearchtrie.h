#ifndef TERNARYSEARCHTRIEBIS_H
#define TERNARYSEARCHTRIEBIS_H

#include<list>
#include<string>

class TernarySearchTrie {
private:
    struct Node {
    public:
        char value;
        Node* right;  // sous arbre avec des cles plus grandes
        Node* center; //
        Node* left;   // sous arbre avec des cles plus petites
        int nodeHeight; // hauteur du sous-arbre dont ce noeud est la racine.
        bool isEnd;
        Node(char value) : value(value), right(nullptr), center(nullptr), left(nullptr), nodeHeight(0), isEnd(false) { }
        // On pourrais gerer la suppression en recursion ici au lieu de le faire via une fonction membre de TernarySearchTrie
        ~Node() {}
    };

    // Racine de l'arbre.
    Node* root;

    // On ne peux pas traiter la taille de la meme manière que ceux des arbres avl
    size_t _size;

public:
    TernarySearchTrie();
    ~TernarySearchTrie();

    void put(const std::string& s) { put(s.c_str()); }
    void put(const char* key);

    void deleteElement(const std::string& s) { deleteElement(s.c_str()); }
    void deleteElement(const char* key);
    int height();

    bool contains(const std::string& s) const { return contains(s.c_str()); }
    bool contains(const char* key) const;
    size_t size() const;

    std::list<std::string> search(const std::string& s, char wildcard = '*') const { return search(s.c_str(), wildcard); } // pas de copie double de la liste cat utilisation de && (optimisation c++11)
    std::list<std::string> search(const char* str, char wildcard = '*') const;

    template < typename Fn >
    void visitInOrder ( Fn f) {
        if ( root != nullptr)
            visitInOrder(root,f);
    }

private:
    int height(Node* x);
    bool contains(Node* x,  const char* key ) const;
    int balance(Node* x);

    Node* restoreBalance(Node* x);
    Node* rotateRight(Node* x);
    Node* rotateLeft(Node* x);
    Node* deleteElement( Node* x, const char* key);
    Node* put(Node* x, const char* str);

    void search(Node* node, std::string prev, std::list<std::string>& list, const char *str, char wildcard) const;

    void deleteSubTree(Node* x);

    // HELPER: Methode aide pour le methodes d'effacement. Efface del et retourne ret.
    Node* deleteAndReturn( Node* del, Node* ret);

    // HELPER: Mise à jour de la hauteur d'un sous-arbre à partir des hauteurs de ses enfants
    void updateNodeHeight(Node* x);

    template < typename Fn >
    void visitInOrder ( Node* x, Fn f) {
        if (x->left != nullptr)
            visitInOrder(x->left,f);

        if (x->center != nullptr)
            visitInOrder(x->center, f);

        f(x->value, x->value);

        if (x->right != nullptr)
            visitInOrder(x->right,f);
    }
};

#endif // TERNARYSEARCHTRIEBIS_H
