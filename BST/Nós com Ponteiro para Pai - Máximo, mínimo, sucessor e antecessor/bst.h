#ifndef BST_H
#define BST_H
#include <iostream>
#include <string>
#include <stack>
#include <climits>
using namespace std;

/*****************************
 * Definicao do struct Node
 *****************************/
struct Node
{
    int key;
    Node *left;
    Node *right;
    Node *parent;

    // Construtor
    Node(int k, Node *l = nullptr, Node *r = nullptr, Node *p = nullptr)
    {
        this->key = k;
        this->left = l;
        this->right = r;
        this->parent = p;
    }
    // Destrutor
    ~Node()
    {
        cout << "Node removed: " << this->key << endl;
    }
};

/************************
 * Declaracao da classe
 ************************/
class BST
{
public:
    BST();
    BST(int k);
    void bshow();
    bool add(int k);
    int minimum();          // ---> Implementar
    int maximum();          // ---> Implementar
    int predecessor(int k); // ---> Implementar
    int successor(int k);   // ---> Implementar
    ~BST();

private:
    Node *root;
    void bshow(Node *node, std::string heranca);
    Node *minimum(Node *node);     // ---> Implementar
    Node *maximum(Node *node);     // ---> Implementar
    Node *successor(Node *node);   // ---> Implementar
    Node *predecessor(Node *node); // ---> Implementar
    Node *clear(Node *node);
    Node *search(int k);
};

/*****************************
 * Implementacao da classe
 *****************************/
// Construtor
BST::BST()
{
    root = nullptr;
}

// Construtor
BST::BST(int k)
{
    root = new Node(k);
}

void BST::bshow()
{
    bshow(root, "");
}

void BST::bshow(Node *node, std::string heranca)
{
    if (node != nullptr && (node->left != nullptr || node->right != nullptr))
        bshow(node->right, heranca + "r");
    for (int i = 0; i < (int)heranca.size() - 1; i++)
        std::cout << (heranca[i] != heranca[i + 1] ? "│   " : "    ");
    if (heranca != "")
        std::cout << (heranca.back() == 'r' ? "┌───" : "└───");
    if (node == nullptr)
    {
        std::cout << "#" << std::endl;
        return;
    }
    std::cout << node->key << std::endl;
    if (node != nullptr && (node->left != nullptr || node->right != nullptr))
        bshow(node->left, heranca + "l");
}

Node *BST::clear(Node *node)
{
    if (node != nullptr)
    {
        node->left = clear(node->left);
        node->right = clear(node->right);
        delete node;
    }
    return nullptr;
}

BST::~BST()
{
    root = clear(root);
}

// Funcao publica 'add'
// Esta funcao deve obrigatoriamente ser iterativa.
// Esta funcao adiciona um no com chave k na arvore e:
// (1) devolve true em caso de sucesso;
// (2) devolve false caso contrario.
// Lembre-se que nao podem haver chaves repetidas na nossa arvore.
bool BST::add(int k)
{
    // TODO: adicione aqui o codigo feito no exercicio anterior
    //  Código do primeiro exercício
    if (root == nullptr)
    {                       // se a árvore estiver vazia
        root = new Node(k); // adiciono o novo nó na cabeça da árvore
        return true;        // caso de sucesso
    }
    Node *aux = root; // nó auxiliar para percorrer a árvore
    while (aux != nullptr)
    { // enquanto não chegar no fim da árvore
        if (aux->key == k)
        {
            return false;
        } // se a chave ja existir, retorna falso, caso sem sucesso
        if (aux->key > k)
        { // se a chave do nó auxiliar for maior que a chave
            if (aux->left == nullptr)
            {                            // caminho para a esquerda pois é uma BST
                aux->left = new Node(k); // adiciono o novo nó na esquerda
                return true;             // caso de sucesso
            }
            else
            {
                aux = aux->left; // senão, percorro a árvore para a esquerda
            }
        }
        else
        {
            if (aux->right == nullptr)
            {                             // se a direita for nula, adiciono o novo nó na direita
                aux->right = new Node(k); // pecorro a subarvore para a direita
                return true;              // caso de sucesso
            }
            else
            {
                aux = aux->right; // senão, percorro a árvore para a direita
            }
        }
    }
    return false; // caso não seja possível adicionar o nó retorna falso
}

// Funcao privada 'search'
// Esta funcao devolve o ponteiro para o no que
// contem a chave k se ela existir na arvore;
// caso contrario, devolve nullptr;
Node *BST::search(int k)
{
    // TODO: adicione aqui o codigo feito no exercicio anterior
    Node *aux = root; // aux aponta para a raiz da arvore

    while (aux != nullptr)
    { // percorre a arvore ate encontrar um no folha
        if (k < aux->key)
        { // se a chave k for menor que a chave do no aux
            aux = aux->left;
        }
        else if (k > aux->key)
        { // se a chave k for maior que a chave do no aux
            aux = aux->right;
        }
        else
        {
            return aux;
        }
    }
    return nullptr; // se chegar até aqui, a chave não existe na arvore
}

// Funcao publica (obrigatoriamente iterativa)
// Devolve o menor valor de chave da arvore.
int BST::minimum()
{
    return minimum(root)->key;
}

// Funcao privada (obrigatoriamente iterativa)
// Recebe como argumento o ponteiro para a raiz de uma arvore
// e devolve o ponteiro para o no com a menor chave na arvore.
// Se a arvore for vazia, devolve nullptr
Node *BST::minimum(Node *node)
{
    Node *aux = root;
    while (aux != nullptr && aux->left != nullptr) {
        if (aux->left == nullptr) { return aux; }
        else { aux = aux->left; }
    }
    return aux;
}

// Funcao publica (obrigatoriamente iterativa)
// Devolve o maior valor de chave da arvore
int BST::maximum()
{
    return maximum(root)->key;
}

// Funcao privada (obrigatoriamente iterativa)
// Recebe como argumento o ponteiro para a raiz de uma arvore
// e devolve o ponteiro para o no com a maior chave na arvore.
// Se a arvore for vazia, devolve nullptr
Node *BST::maximum(Node *node)
{
    Node *aux = root;
    while (aux != nullptr && aux->right != nullptr) {
        if (aux->right == nullptr) { return aux; }
        else { aux = aux->right; }
    }
    return aux;
}

// Funcao publica (obrigatoriamente iterativa)
// Recebe um inteiro k como argumento e:
// (1) devolve INT_MAX se a chave k nao esta presente na arvore ou
// se k esta presente na arvore mas nao tem sucessor
// (2) caso contrario, devolve o valor inteiro da
// chave sucessora de k quando esta existe
int BST::successor(int k)
{
    Node *aux = successor(search(k)); // chamo a função search para encontrar o nó com a chave k
    if (aux != nullptr) { return aux->key; } // se não for nula, retorno o sucessor da chave
    // qualquer outro caso, INT_MAX
    return INT_MAX;
}

// Funcao privada (obrigatoriamente iterativa)
// Recebe um ponteiro para um Node e:
// (1) devolve nullptr quando node nao tem sucessor; ou
// (2) caso contrario, devolve o ponteiro para o no sucessor de node.
Node *BST::successor(Node *node)
{

    if (node == nullptr) { return nullptr; } // se o nó não existir, não tem sucessor 

    if (node->right != nullptr) {
        Node *minNode = node->right;
        while (minNode != nullptr && minNode->left != nullptr) {
            if (minNode->left == nullptr) { return minNode; }
            else { minNode = minNode->left; }
        }
        return minNode;
    }
    Node *auxNode = root; // para percorrer a árvore
    Node *aux = nullptr; // nó auxiliar
    while ( auxNode != node ) {
        // encontrando o menor antes
        if (auxNode->key < node->key) { auxNode = auxNode->right; }
        else { aux = auxNode; auxNode = auxNode->left; }
    }
    return aux;
    
}

// Funcao publica (obrigatoriamente iterativa)
// Recebe um inteiro k como argumento e:
// (1) devolve INT_MIN se a chave k nao esta presente na arvore ou
// se k esta presente na arvore mas nao tem antecessor;
// (2) caso contrario, devolve o valor inteiro da chave
// antecessora de k quando esta existe.
int BST::predecessor(int k)
{
    Node *aux = predecessor(search(k)); // chamo a função search para encontrar o nó com a chave k
    if (aux != nullptr) { return aux->key; } // se não for nulo, chamo o antecessor da chave de search
    return INT_MIN; 
}

// Funcao privada (obrigatoriamente iterativa)
// Recebe um ponteiro para um Node e:
// (1) devolve nullptr quando node nao tem antecessor; ou
// (2) caso contrario, devolve o ponteiro para o no antecessor de node.
Node *BST::predecessor(Node *node)
{
    // função oposta a função anterior
    if (node == nullptr) { return nullptr; } // se o nó não existir
    
    // mesma lógica da função anterior, buscando o antecessor
    Node *auxNode = root; // para percorrer a árvore
    Node *aux = nullptr; // nó auxiliar
    while ( auxNode != node ) {
        // encontrando o menor antes
        if (auxNode->key > node->key) { auxNode = auxNode->left; }
        else { aux = auxNode; auxNode = auxNode->right; }
    }
    return aux;
    
}

#endif