#include <iostream>
#include <stack>
#include "node.h"
#include "avl.h"
using namespace std;

// retorna a altura do nó.
// se a arvore for vazia ela tem altura 0
// caso contrario, retorna o valor que está no campo height
int avl_tree::height(Node *node) {
    return (node == nullptr) ? 0 : node->height;
}

int avl_tree::balance(Node *node) {
    return height(node->right) - height(node->left);
}

Node* avl_tree::rightRotation(Node *p) {
    Node *u = p->left;
    p->left = u->right;
    u->right = p;
    // recalcular as alturas de p e de u
    p->height = 1 + max(height(p->left),height(p->right));
    u->height = 1 + max(height(u->left),height(u->right));
    return u;
}

Node* avl_tree::leftRotation(Node *p) {
    Node *u = p->right;
    p->right = u->left;
    u->left = p;
    // recalcular as alturas de p e de u
    p->height = 1 + max(height(p->right),height(p->left));
    u->height = 1 + max(height(u->left),height(u->right));
    return u;
}

// função pública que recebe uma chave e a insere
// somente se ela não for repetida

void avl_tree::add(int key) {
    root = add(root, key);
}

// Função completamente iterativa que insere uma chave na árvore
// e retorna o ponteiro para a raiz da árvore
// PROVA DE COMPLEXIDADE - INFORMAL
/*
    A busca pelo o local no qual vou inserir o nó é feita da raíz, até a folha.
    esse caminho tem um tamanho proporcional à altura da árvore, que é O(log n).
    assim, a complexidade da busca é O(log n). Depois que o nó é inserido, caso seja necessário 
    corrigir o balanceamento, fazemos isso subindo do nó inserido, até a raíz.
    verificando se o fator de balanceamento de cada nó está fora de [-1, 0, +1].
    Caso esteja, fazemos as rotações necessárias para corrigir o balanceamento.
    Como a altura da árvore é O(log n), o número de nós que precisam ser verificados e o número 
    de rotações que precisam ser realizadas também é O(log n).
*/
Node* avl_tree::add(Node *p, int key) {
    stack<Node*> stack; // pilha para guardar os nós percorridos

    if (p == nullptr) { return new Node(key); } // se a árvore for vazia, insiro o nó na raiz
    
    Node *current = p; // nó atual
    while (current != nullptr) { // enquanto não chegar na folha
        stack.push(current); // empilho o nó atual
        if (current->key == key) { return p; } // se a chave já existir, não insiro
        else if (current->key < key) { // se a chave for maior que a chave do nó atual
            current = current->right; // vou para a subárvore direita
        }
        else { current = current->left; } // se a chave for menor que a chave do nó atual, vou para a subárvore esquerda
    }
    
    Node* newNode = new Node(key); // crio o novo nó
    current = stack.top(); // pego o nó atual
    if (current->key < key) { current->right = newNode; } // insiro o novo nó na subárvore correta
    else { current->left = newNode; } // caso não seja inserido na subárvore direita, insiro na subárvore esquerda

    while (!stack.empty()) { // enquanto a pilha não estiver vazia
        current = stack.top(); // pego o nó atual
        current = fixup_node(current, key); // corrijo o balanceamento do nó atual
        stack.pop(); // desempilho o nó atual

        if (!stack.empty()) { // se a pilha não estiver vazia
            Node* parent = stack.top(); // pego o nó pai do nó atual
            if (parent->key < key) { parent->right = current; } // atualizo o ponteiro do nó pai para o nó atual
            else { parent->left = current; } // caso não seja a subárvore direita, atualizo o ponteiro da subárvore esquerda
        }
        else { p = current; } // atualiza a raiz
    }
    return p; // retorna a raiz
}

Node* avl_tree::fixup_node(Node *p, int key) {
    // recalcula a altura de p
    p->height = 1 + max(height(p->left),height(p->right));

    // calcula o balanço do p
    int bal = balance(p);

    if(bal >= -1 && bal <= 1) {
        return p;
    }

    if(bal < -1 && key < p->left->key) {
        p = rightRotation(p);
    }
    else if(bal < -1 && key > p->left->key) {
        p->left = leftRotation(p->left);
        p = rightRotation(p);
    }
    else if(bal > 1 && key > p->right->key) {
        p = leftRotation(p);
    }
    else if(bal > 1 && key < p->right->key) {
        p->right = rightRotation(p->right);
        p = leftRotation(p);
    }
    return p;
}

void avl_tree::clear() {
    root = clear(root);
}

Node *avl_tree::clear(Node *node) {
    if(node != nullptr) {
        node->left = clear(node->left);
        node->right = clear(node->right);
        delete node;
    }
    return nullptr;
}

avl_tree::~avl_tree() {
    clear();
}

void avl_tree::bshow() const {
    bshow(root, "");
}

void avl_tree::bshow(Node *node, std::string heranca) const {
    if(node != nullptr && (node->left != nullptr || node->right != nullptr))
        bshow(node->right , heranca + "r");
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
        bshow(node->left, heranca + "l");
}