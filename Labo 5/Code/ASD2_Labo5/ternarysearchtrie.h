#ifndef TERNARYSEARCHTRIEBIS_H
#define TERNARYSEARCHTRIEBIS_H

#include <algorithm>

class TernarySearchTrie {
private:
    struct Node {
    public:
        char value;
        Node* right;  // sous arbre avec des cles plus grandes
        Node* center;
        Node* left;   // sous arbre avec des cles plus petites
        int nodeHeight; // hauteur du sous-arbre dont ce noeud est la racine.
        bool isEnd;
        Node(char value) : value(value), right(nullptr), center(nullptr), left(nullptr), nodeHeight(0), isEnd(false) { }
    };

    //
    // Racine de l'arbre.
    //
    Node* root;
    size_t _size;

    // HELPER: Methode aide pour le methodes d'effacement. Efface del et retourne ret.
    Node* deleteAndReturn( Node* del, Node* ret);

    // HELPER: Mise à jour de la hauteur d'un sous-arbre à partir des hauteurs de ses enfants
    void updateNodeHeight(Node* x);

private:
    //
    // AVL: rotation droite avec mise à jour des tailles et hauteurs
    //
    Node* rotateRight(Node* x);
    //
    // AVL: rotation gauche avec mise à jour des tailles et hauteurs
    //
    Node* rotateLeft(Node* x);

    //
    // Constructeur. La racine est vide
    //
public:
    TernarySearchTrie();

    //
    // Destructeur.
    //
public:
    ~TernarySearchTrie();

private:
    void deleteSubTree(Node* x);

    //
    // Nombre d'elements
    //
public:
    size_t size() const;


    //
    // Insertion d'une chaine
    //
public:
    void put( const char* key);

private:
    Node* put(Node* x, const char* str);

    int balance(Node* x);

    Node* restoreBalance(Node* x);

public:
    bool contains(const char* key) const;
private:
    bool contains(Node* x,  const char* key ) const;

    //
    // Profondeur de l'arbre.
    //
public:
    int height();
private:
    int height(Node* x);

    //
    // Efface l'element de cle key
    //
public:

    void deleteElement( const char* key);

private:
    Node* deleteElement( Node* x, const char* key);

public:
    template < typename Fn >
    void visitInOrder ( Fn f) {
        if ( root != nullptr)
            visitInOrder(root,f);
    }

private:
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
