#include <iostream>
#include <sstream>
#include <string>
#include "Tree.h"

struct Node {
    int key;
    Node *left;
    Node *right;

    Node(int k, Node *l = nullptr, Node *r = nullptr) {
        this->key = k;
        this->left = l;
        this->right = r;
    }
};


// Construtor
Tree::Tree(std::string serial) {
    _root = nullptr;
    std::stringstream ss(serial);
    _serializeTree(ss, &_root);
}


void Tree::_serializeTree(std::stringstream& ss, Node **node) {
    std::string value;
    ss >> value;
    if(value == "#") // filho == nullptr
        return;
    int key = std::stoi(value);
    *node = new Node(key);
    _serializeTree(ss, &((*node)->left));
    _serializeTree(ss, &((*node)->right));
}


Tree::~Tree() {
    _root = _clear(_root);
}


Node *Tree::_clear(Node *node) {
    if(node != nullptr) { // caso geral: vamos liberar essa arvore
        node->left = _clear(node->left);
        node->right = _clear(node->right);
        delete node;
    }
    return nullptr;
}

void Tree::preorder() {
    _preorder(_root);
}

void Tree::_preorder(Node *node) {
    if(node != nullptr) { // Caso Geral
        std::cout << node->key << " ";
        _preorder(node->left);
        _preorder(node->right);
    }
}

void Tree::inorder() {
    _inorder(_root);
}

void Tree::_inorder(Node *node) {
    if(node != nullptr) { // Caso Geral
        _inorder(node->left);
        std::cout << node->key << " ";
        _inorder(node->right);  
    }
}

void Tree::bshow(){
    _bshow(_root, "");
}

void Tree::_bshow(Node *node, std::string heranca) {
    if(node != nullptr && (node->left != nullptr || node->right != nullptr))
        _bshow(node->right , heranca + "r");
    for(int i = 0; i < (int) heranca.size() - 1; i++)
        std::cout << (heranca[i] != heranca[i + 1] ? "│   " : "    ");
    if(heranca != "")
        std::cout << (heranca.back() == 'r' ? "┌───" : "└───");
    if(node == nullptr){
        std::cout << "#" << std::endl;
        return;
    }
    std::cout << node->key << std::endl;
    if(node != nullptr && (node->left != nullptr || node->right != nullptr))
        _bshow(node->left, heranca + "l");
}


int Tree::count_leaves() { // TODO
    return _count_leaves(_root);
}

// Conta o número de nós de folhas da árvore
int Tree::_count_leaves(Node *node) { // TODO
    int cont = 0; // contador para guardar a quantidade de folhas
    if (node == nullptr) { // Caso que
        return 0; // retorno 0, pois não há folhas, ou poderia retornar o contador, pois ainda está zerado
    }
    else {
        if (node->left == nullptr && node->right == nullptr) { // Se a subárvore da esquerda e direita forem nulas
            cont++; // incremento o contador, pois é uma folha
        }
    }
    cont += _count_leaves(node->left); // chamo a função recursivamente para a subárvore da esquerda
    cont += _count_leaves(node->right); // chamo a função recursivamente para a subárvores da direita
    return cont; // retorno o contador
}

void Tree::delete_leaves() { // TODO
    _delete_leaves(_root);
}

// Função recursiva que exclui todas as folhas da árvore
Node* Tree::_delete_leaves(Node *node) { // TODO
    if (node == nullptr) { // Caso base
        return nullptr; // retorno nullptr, por estar excluindo os nós
    }
    else {
        if (node->left == nullptr && node->right == nullptr) { // Se a subárvore da esquerda e direita forem nulas
            delete node; // apenas deleta, pois eu quero excluir TODOS os nós
            return nullptr; // retorno nullptr, por estar excluindo
        }
    }
    node->left = _delete_leaves(node->left); // chamo a função recursivamente para a subárvore da esquerda
    node->right = _delete_leaves(node->right); // chamo a função recursivamente para a subárvores da direita
    return node; // retorno o nó atualizado
}

void Tree::delete_leaves_with_value(int key) { // TODO
    _delete_leaves_with_value(key, _root);
}

// Função recursiva que apaga todas as folhas de uma árvore
// que tenham a chave igual a um valor dado
Node* Tree::_delete_leaves_with_value(int key, Node *node) { // TODO
    if (node == nullptr) { // Caso base
        return nullptr; // retorno nullptr, por estar excluindo os nós
    }
    else {
        if (node->left == nullptr && node->right == nullptr) { // Se a subárvore da esquerda e direita forem nulas
            if (node->key == key) { // e a chave for == a chave que foi passada
                delete node; // deleto o nó
                return nullptr; // retorno nullptr, por estar excluindo
            }
        }
    }
    node->left = _delete_leaves_with_value(key, node->left); // chamo recursivamente para a esquerda
    node->right = _delete_leaves_with_value(key, node->right); // chamo recursivamente para a direita
    return node; // retorno o nó atualizado
}


