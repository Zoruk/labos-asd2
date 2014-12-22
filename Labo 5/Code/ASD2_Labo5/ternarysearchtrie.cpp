#include "ternarysearchtrie.h"

TernarySearchTrie::TernarySearchTrie() : root(nullptr)
{
}

TernarySearchTrie::Node* TernarySearchTrie::insert(Node* node, const char* str) {
    if (!*str) {
        return node;
    }
    if (!node) {
        node = new Node(*str);
        ++str;
        if (*str)
            node->center = insert(nullptr, str);
        else
            node->isEnd = true;
        return node;
    }

    if (*str < node->value) {
        node->left = insert(node->left, str);
    } else if (*str > node->value) {
        node->right = insert(node->right, str);
    } else {
        ++str;
        if (!*str)
            node->isEnd = true;
        else
            node->center = insert(node->center, str);
    }

    return node;
}

void TernarySearchTrie::insert(std::string str) {
    root = insert(root, str.c_str());
}

bool TernarySearchTrie::contain(const Node *node, const char *str) const {
    if(!node)
        return false;
    if (*str < node->value) {
        return contain(node->left, str);
    } else if (*str > node->value) {
        return contain(node->right, str);
    } else {
        ++str;
        if (!*str) {
            return node->isEnd;
        }
        return contain(node->center, str);
    }
}

bool TernarySearchTrie::contain(const std::string str) const {
    return contain(root, str.c_str());
}

TernarySearchTrie::Node* TernarySearchTrie::remove(Node *node, const char *str)
{
    if (!node) return nullptr;
    if (*str < node->value) {
        node->left = remove(node->left, str);
    } else if (*str > node->value) {
        node->right = remove(node->right, str);
    } else {
        ++str;
        if (!*str) {
            node->isEnd = false;
        }
        node->center = remove(node->center, str);
    }

    // IMPROVEMENT Possible here
    if (!node->isEnd && !node->center && !node->left && !node->right) {
        delete node;
        return nullptr;
    }

    return node;
}
