#include <iostream>
#include <sstream>
#include <string>
#include <climits>
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
    _clear(_root);
}

Node *Tree::_clear(Node *node) {
    if(node != nullptr) { // caso geral: vamos liberar essa arvore
        node->left = _clear(node->left);
        node->right = _clear(node->right);
        delete node;
    }
    return nullptr;
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

int Tree::sum_keys() { // TODO
    return _sum_keys(_root);
}

int Tree::_sum_keys(Node *node) { // TODO
    if(node == nullptr) {
        return 0;
    }
    int soma = node->key + _sum_keys(node->left) + _sum_keys(node->right);
    return soma;
}

// Para fazer essa funcao, suponha que as arvores dos testes nunca serao vazias,
// assim, sempre havera um menor valor de chave a ser retornado
int Tree::min_key() { // TODO
    return _min_key(_root);
}

// Supoe que o ponteiro recebido sempre eh diferente de nullptr
//Escreva uma função que devolva o valor da menor chave de uma árvore binária.

int Tree::_min_key(Node *node) { // TODO
    // Caso base: nó é uma folha, retorna a chave do nó
    if (node->left == nullptr && node->right == nullptr) {
        return node->key;
    }

    // Caso recursivo: calcula os menores valores nas subárvores esquerda e direita
    int min = node->key; // Inicializa o mínimo com a chave do nó atual

    if (node->left != nullptr) {
        int min_esq = _min_key(node->left); // Calcula o menor valor na subárvore esquerda
        if (min_esq < min) {
            min = min_esq; // Atualiza o mínimo se o menor valor na subárvore esquerda for menor que o mínimo atual
        }
    }

    if (node->right != nullptr) {
        int min_dir = _min_key(node->right); // Calcula o menor valor na subárvore direita
        if (min_dir < min) {
            min = min_dir; // Atualiza o mínimo se o menor valor na subárvore direita for menor que o mínimo atual
        }
    }
    return min; // Retorna o menor valor encontrado

}

int Tree::total_internal_nodes() { // TODO
    return _total_internal_nodes(_root);
}
// Escreva uma função que conte o número de nós internos de uma árvore binária.
int Tree::_total_internal_nodes(Node *node) { // TODO
    if (node == nullptr || (node->left == nullptr && node->right == nullptr)) {
        return 0;
    }
    else {
        return 1 + _total_internal_nodes(node->left) + _total_internal_nodes(node->right);
    }
}

int Tree::um_filho() { // TODO
    return _um_filho(_root);
}
// Escreva uma função que retorne a quantidade de nós de uma árvore binária que possuem apenas um filho.
int Tree::_um_filho(Node *node) { // TODO
    if (node == nullptr) {
        return 0;
    } 
    else {
        int cont = 0;
        if (node->left != nullptr && node->right == nullptr) {
            cont = 1;
        } else if (node->left == nullptr && node->right != nullptr) {
            cont = 1;
        }
        cont += _um_filho(node->left);
        cont += _um_filho(node->right);
        return cont;
    }
}