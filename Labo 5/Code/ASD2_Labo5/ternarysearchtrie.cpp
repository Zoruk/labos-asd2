#include <algorithm>

#include "ternarysearchtrie.h"

TernarySearchTrie::Node* TernarySearchTrie::deleteAndReturn( Node* del, Node* ret) {
    delete del;
    return ret;
}

// HELPER: Mise à jour de la hauteur d'un sous-arbre à partir des hauteurs de ses enfants
void TernarySearchTrie::updateNodeHeight(Node* x) {
    x->nodeHeight = std::max(height(x->right), height(x->left)) + 1;
}

TernarySearchTrie::Node* TernarySearchTrie::rotateRight(Node* x) {
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
TernarySearchTrie::Node* TernarySearchTrie::rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;

    updateNodeHeight(x);
    updateNodeHeight(y);
    return y;
}


TernarySearchTrie::TernarySearchTrie() : root(nullptr), _size(0) { }

TernarySearchTrie::~TernarySearchTrie() {
    deleteSubTree(root);
}

void TernarySearchTrie::deleteSubTree(Node* x) {
    if( x == nullptr) return;
    deleteSubTree(x->right);
    deleteSubTree(x->left);
    deleteSubTree(x->center);
    delete x;
}

size_t TernarySearchTrie::size() const {
    return _size;
}

void TernarySearchTrie::put( const char* key) {
    root = put(root, key);
}

TernarySearchTrie::Node* TernarySearchTrie::put(Node* x, const char* str) {
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

int TernarySearchTrie::balance(Node* x) {
    if(x==nullptr) return 0;
    return height(x->left) - height(x->right);
}

TernarySearchTrie::Node* TernarySearchTrie::restoreBalance(Node* x) {

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




bool TernarySearchTrie::contains(Node* x,  const char* key ) const {
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

bool TernarySearchTrie::contains( const char* key ) const {
    return contains(root, key);
}


//
// Profondeur de l'arbre.
//
int TernarySearchTrie::height()
{
    return height(root);
}

int TernarySearchTrie::height(Node* x) {
    if ( x == nullptr )
        return -1;
    return x->nodeHeight;
}

//
// Efface l'element de cle key
//
void TernarySearchTrie::deleteElement( const char* key) {
    root = deleteElement( root, key );
}

TernarySearchTrie::Node* TernarySearchTrie::deleteElement( Node* x, const char* key) {
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

    // TODO delete un needed elements
    if (x->center == nullptr && !x->isEnd) {

    }

    return restoreBalance(x);
}
