#pragma once

#include <iostream>
#include "list.h"


class binaryTree {

    struct node {
        int data;
        node* left;
        node* right;
    };

    node* root;

    node* makeEmpty(node* t) {
        if (t == nullptr)
            return nullptr;
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        return nullptr;
    }

    node* insert(int x, node* t)
    {
        if (t == nullptr)
        {
            t = new node;
            t->data = x;
            t->left = t->right = nullptr;
        }
        else if (x < t->data)
            t->left = insert(x, t->left);
        else if (x > t->data)
            t->right = insert(x, t->right);
        return t;
    }

    node* findMin(node* t)
    {
        if (t == nullptr)
            return nullptr;
        else if (t->left == nullptr)
            return t;
        else
            return findMin(t->left);
    }

    node* findMax(node* t) {
        if (t == nullptr)
            return nullptr;
        else if (t->right == nullptr)
            return t;
        else
            return findMax(t->right);
    }

    node* remove(int x, node* t) {
        node* temp;
        if (t == nullptr)
            return nullptr;
        else if (x < t->data)
            t->left = remove(x, t->left);
        else if (x > t->data)
            t->right = remove(x, t->right);
        else if (t->left && t->right)
        {
            temp = findMin(t->right);
            t->data = temp->data;
            t->right = remove(t->data, t->right);
        }
        else
        {
            temp = t;
            if (t->left == nullptr)
                t = t->right;
            else if (t->right == nullptr)
                t = t->left;
            delete temp;
        }

        return t;
    }

    void inorder(node* t) {
        if (t == nullptr)
            return;
        inorder(t->left);
        std::cout << t->data << " ";
        inorder(t->right);
    }

    node* find(node* t, int x) {
        if (t == nullptr)
            return nullptr;
        else if (x < t->data)
            return find(t->left, x);
        else if (x > t->data)
            return find(t->right, x);
        else
            return t;
    }

public:
    binaryTree() {
        root = nullptr;
    }

    ~binaryTree() {
        root = makeEmpty(root);
    }

    void makeEmpty() {
        root = makeEmpty(root);
    }

    void insert(int x) {
        root = insert(x, root);
    }

    void remove(int x) {
        root = remove(x, root);
    }

    void display() {
        inorder(root);
        std::cout << std::endl;
    }
    int search(int x) {
        node* searched = find(root, x);
        if (searched == nullptr) return -1;
        return searched->data;
    }
    void searchLeaf(int x) {
        node* searched = find(root, x);
        inorder(searched);
        std::cout << std::endl;
    }
    int maxValue() {
        node* max = findMax(root);
        return max->data;
    }
    int minValue() {
        node* min = findMin(root);
        return min->data;
    }
    list<int> convertToList() {
        list<int> convert;
        while (root != nullptr) {
            convert.push_back(minValue());
            remove(minValue());
        }
        return convert;
    }
};