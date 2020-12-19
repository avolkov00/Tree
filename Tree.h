#pragma once
#include <memory>
#include <iostream>

class Tree {
    struct Node {
        int value;
        std::weak_ptr<Node> parent;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
    };

    std::shared_ptr<Node> start;


    void insert(std::shared_ptr<Node>& parent, std::shared_ptr<Node>& node, int value) {
        if (!node.get()) {
            node = std::make_shared<Node>();
            node->parent = parent;
            node->value = value;
            return;
        }
        if (node->value < value) {
            insert(node, node->right, value);
        }
        else {
            insert(node, node->left, value);
        }
    }

    std::shared_ptr<Node>& findMinValue(std::shared_ptr<Node>& node) {
        
        std::shared_ptr<Node> bufNode = node;
        int value = bufNode->value;
        std::shared_ptr<Node> result;

        while (bufNode.get()) {
            if (bufNode->value < value) {
                value = bufNode->value;
                result = bufNode;
            }
            bufNode = bufNode->left;
        }

        return result;
    }

    void remove(std::shared_ptr<Node>& node, int value) {
        if (!node.get()) {
            return;
        }

        if (node->value == value) {
            if (node->right.get() == nullptr || node->left.get() == nullptr) {
                if (node->right.get() != nullptr) {
                    node = node->right;
                }
                else {
                    node = node->left;
                }
            }
            else {
                std::shared_ptr<Node> changed = findMinValue(node->right);
                node->value = changed->value;
                node->parent = changed->parent;
            }
        }
        else {
            if (node->value > value) {
                remove(node->left, value);
            }
            else {
                remove(node->right, value);
            }
        }
    }

public:

    void insert(int value) {
        if (!start.get()) {
            start = std::make_shared<Node>();
            start->value = value;
            return;
        }

        insert(start, start, value);
    }

    void remove(int value) {
        remove(start, value);
    }

    bool find(int value) {
        std::shared_ptr<Node> bufNode = start;

        while (bufNode.get()) {
            if (bufNode->value == value) {
                return true;
            }
            else if (bufNode->value > value) {
                bufNode = bufNode->left;
            }
            else {
                bufNode = bufNode->right;
            }
        }
        return false;
    }

};