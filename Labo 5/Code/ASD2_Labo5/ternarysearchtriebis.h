#ifndef TERNARYSEARCHTRIEBIS_H
#define TERNARYSEARCHTRIEBIS_H

#include <algorithm>

class TernarySearchTrieBis {
private:

    //
    // Noeux de l'arbre. contient une cle, une valeur, et les liens vers les
    // sous-arbres droit et gauche.
    //
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
    Node* deleteAndReturn( Node* del, Node* ret) {
        delete del;
        return ret;
    }

    // HELPER: Mise à jour de la hauteur d'un sous-arbre à partir des hauteurs de ses enfants
    void updateNodeHeight(Node* x) {
        x->nodeHeight = std::max(height(x->right), height(x->left)) + 1;
    }

private:
    //
    // AVL: rotation droite avec mise à jour des tailles et hauteurs
    //
    Node* rotateRight(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        y->right = x;

        updateNodeHeight(x);
        updateNodeHeight(y);
        return y;
    }

    //
    // AVL: rotation gauche avec mise à jour des tailles et hauteurs
    //
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;

        updateNodeHeight(x);
        updateNodeHeight(y);
        return y;
    }


    //
    // Constructeur. La racine est vide
    //
public:
    TernarySearchTrieBis() : root(nullptr), _size(0) { }


    //
    // Destructeur.
    //
public:
    ~TernarySearchTrieBis() {
        deleteSubTree( root );
    }
private:
    void deleteSubTree(Node* x) {
        if( x == nullptr) return;
        deleteSubTree( x->right );
        deleteSubTree( x->left );
        deleteSubTree( x->center );
        delete x;
    }

    //
    // Nombre d'elements
    //
public:
    int size() const {
        return _size;
    }

    //
    // Insertion d'une paire cle / valeur.
    //
public:
    void put( const char* key) {
        root = put(root, key);
    }

private:
    Node* put(Node* x, const char* str) {
        if (!*str) {
            return x;
        }

        if (x == nullptr) {
            x = new Node(*str);
            ++str;
            if (*str)
                x->center = put(nullptr, str);
            else if (!x->isEnd) {
                x->isEnd = true;
                _size++;
            }
        }
        else if (*str < x->value) {
            x->left = put(x->left, str);
        } else if (*str > x->value) {
            x->right = put(x->right, str);
        } else {
            ++str;
            if (!*str) {
                if (!x->isEnd) {
                    x->isEnd = true;
                    _size++;
                }
            }
            else
                x->center = put(x->center, str);
        }

        return restoreBalance(x);
    }

    //
    // AVL: calcul et restoration de l'équilibre d'un noeud.
    //
    int balance(Node* x) {
        if(x==nullptr) return 0;
        return height(x->left) - height(x->right);
    }
    Node* restoreBalance(Node* x) {

        if(balance(x) < -1) // left < right-1
        {
            if (balance(x->right)>0)
                x->right = rotateRight( x->right );
            x = rotateLeft(x);
        }
        else if( balance(x) > 1) // left > right+1
        {
            if ( balance(x->left) < 0 )
                x->left = rotateLeft( x->left );
            x = rotateRight(x);
        }
        else updateNodeHeight(x);
        return x;
    }


public:



    bool contains(Node* x,  const char* key ) const {
        if(!x)
            return false;
        if (*key < x->value) {
            return contains(x->left, key);
        } else if (*key > x->value) {
            return contains(x->right, key);
        } else {
            ++key;
            if (!*key) {
                return x->isEnd;
            }
            return contains(x->center, key);
        }
    }

    bool contains( const char* key ) const {
        return contains(root, key);
    }


    //
    // Profondeur de l'arbre.
    //
public:
    int height()
    {
        return height(root);
    }
private:
    int height(Node* x) {
        if ( x == nullptr )
            return -1;
        return x->nodeHeight;
    }

    //
    // Efface l'element de cle key
    //
public:

    void deleteElement( const char* key) {
        root = deleteElement( root, key );
    }

private:
    Node* deleteElement( Node* x, const char* key) {
        if (!*key)
            return x;

        if (x == nullptr)
            return nullptr;

        if (*key < x->value) {
            x->left = deleteElement(x->left, key);
        } else if (*key > x->value) {
            x->right = deleteElement(x->right, key);
        } else { // *key == x->value
            ++key;
            if (!*key) { // fin de la chaine
                if (x->isEnd) {
                    x->isEnd = false;
                    --_size;
                }
            } else {
                x->center = deleteElement(x->center, key);
            }
        }

        if (x->center == nullptr) {
            // Hum how to do ?
        }

        return restoreBalance(x);
        /*
        if ( x == nullptr )
            return nullptr; // element pas trouve.

        if ( key < x->value )
            x->left = deleteElement( x->left, key );
        else if ( key > x->value )
            x->right = deleteElement( x->right, key );
        else { // x->key == key
            if ( x->right == nullptr )
                return deleteAndReturn(x,x->left);
            if ( x->left == nullptr )
                return deleteAndReturn(x,x->right);

            Node* y = min(x->right);
            x->value = y->value;
            x->value = y->value;
            x->right = deleteMin(x->right);
        }
        return restoreBalance(x);
        */
    }

    //
    // Visite de l'arbre par ordre croissant de cle
    //
public:
    template < typename Fn >
    void visitInOrder ( Fn f) {
        if ( root != nullptr)
            visitInOrder(root,f);
    }
private:
    template < typename Fn >
    void visitInOrder ( Node* x, Fn f) {
        if ( x->left != nullptr)
            visitInOrder(x->left,f);

        if (x->center != nullptr)
            visitInOrder(x->center, f);

        f( x->value, x->value );

        if ( x->right != nullptr)
            visitInOrder(x->right,f);
    }
};

#endif // TERNARYSEARCHTRIEBIS_H
