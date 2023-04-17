#ifndef BST_H
#define BST_H
#include <iostream>
#include <string>
#include <stack>
using namespace std;

/******************************
 * Definicao do struct Node
 ******************************/
struct Node {
    int key;
    Node *left;
    Node *right;
    Node *parent;

    // Construtor
    Node(int k, Node* l = nullptr, Node* r = nullptr, Node* p = nullptr) {
        this->key = k;
        this->left = l;
        this->right = r;
        this->parent = p;
    }
    // Destrutor
    ~Node() {
        cout << "Node removed: " << this->key << endl;
    }
};

/***********************************
 * Declaracao da classe
 ***********************************/
class BST {
public:
    BST();
    BST(int k);
    void bshow();
    bool add(int k);
    void preorder();  // --> Implementar
    void inorder();   // --> Implementar
    void clear();     // --> Implementar
    ~BST();
private:
    Node *root;
    void bshow(Node *node, std::string heranca);
};

/***********************************
 * Implementacao da classe
 ***********************************/
BST::BST() {
    root = nullptr;
}
 
BST::BST(int k) {
    root = new Node(k);
}

void BST::bshow(){
    bshow(root, "");
}

void BST::bshow(Node *node, std::string heranca) {
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

BST::~BST() {
    clear();
}

// Funcao publica 'add'
// Esta funcao deve obrigatoriamente ser iterativa.
// Esta funcao adiciona um no com chave k na arvore e: 
// (1) devolve true em caso de sucesso;
// (2) devolve false caso contrario.
// Lembre-se que nao podem haver chaves repetidas na nossa arvore.
bool BST::add(int k) {
    // Código do primeiro exercício
    if(root == nullptr) { // se a árvore estiver vazia 
        root = new Node(k); // adiciono o novo nó na cabeça da árvore
        return true; // caso de sucesso
    }
    Node *aux = root; // nó auxiliar para percorrer a árvore
    while(aux != nullptr) { // enquanto não chegar no fim da árvore
        if(aux->key == k) { return false; } // se a chave ja existir, retorna falso, caso sem sucesso
        if(aux->key > k) { // se a chave do nó auxiliar for maior que a chave
            if(aux->left == nullptr) { // caminho para a esquerda pois é uma BST
                aux->left = new Node(k); // adiciono o novo nó na esquerda
                return true; // caso de sucesso
            }
            else {
                aux = aux->left; // senão, percorro a árvore para a esquerda
            }
        }
        else {
            if(aux->right == nullptr) { // se a direita for nula, adiciono o novo nó na direita
                aux->right = new Node(k); // pecorro a subarvore para a direita
                return true; // caso de sucesso
            }
            else {
                aux = aux->right; // senão, percorro a árvore para a direita
            }
        }
    }
    return false; // caso não seja possível adicionar o nó retorna falso
}

// Funcao publica 'preorder'
// Percorre os nos da arvore em pre-ordem imprimindo os 
// valores das chaves. Dica: use a estrutura de dados pilha (stack)
void BST::preorder() {
    stack <Node*> nodePilha; // pilha de nós
    nodePilha.push(root); // adiciono a raíz da árvore na pilha    
    while (!(nodePilha.empty())) {
        Node* aux = nodePilha.top(); // nó auxiliar para percorrer a árvore
        nodePilha.pop(); // removo o nó da pilha
        if (aux != nullptr) {
            cout << aux->key << " "; // imprimo a chave do nó
            nodePilha.push(aux->right); // adiciono o nó da direita na pilha
            nodePilha.push(aux->left); // adiciono o nó da esquerda na pilha
        }
    }
}

// Funcao publica 'inorder'
// Percorre os nos da arvore em ordem simetrica imprimindo os 
// valores das chaves. Dica: use a estrutura de dados pilha (stack)
void BST::inorder() {
    stack <Node*> nodePilha; // pilha de nós
    Node* aux = root; // nó auxiliar para percorrer a árvore
    while (!(nodePilha.empty()) || aux != nullptr) {
        if (aux != nullptr) {
            nodePilha.push(aux); // adiciono o nó na pilha
            aux = aux->left; // percorro a subarvore para a esquerda
        }
        else {
            aux = nodePilha.top(); // nó auxiliar para percorrer a árvore
            nodePilha.pop(); // removo o nó da pilha
            cout << aux->key << " "; // imprimo a chave do nó
            aux = aux->right; // percorro a subarvore para a direita
        }
    }
}

// Funcao publica 'clear'
// Libera todos os nos da arvore deixando ela vazia.
// Dica: use a estrutura de dados pilha (stack)
void BST::clear() {
    stack <Node*> nodePilha; 
    Node *aux = root;
    while (!(nodePilha.empty()) || aux != nullptr) {
        while (aux != nullptr) {
            nodePilha.push(aux);
            aux = aux->left;
        }
        aux = nodePilha.top();
        nodePilha.pop();
        Node *nodeRight = aux->right;
        delete aux;
        aux = nodeRight;
    }
    root = nullptr;
}

#endif 