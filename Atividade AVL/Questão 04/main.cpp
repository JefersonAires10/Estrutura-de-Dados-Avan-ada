#include <iostream>
#include "avl.h"
using namespace std;

int main() {

    system("chcp 65001 > nul");

    avl_tree *t1 = new avl_tree;
    avl_tree *t2 = new avl_tree;

    for(int i = 30; i <= 45; i++) {
        t1->add(i);
    }

    for(int i = 46; i <= 60; i++) {
        t2->add(i);
    }

    cout << endl;
    cout << "=======================================" << endl;
    cout << "Arvore 1:" << endl;
    t1->bshow();
    cout << "=======================================" << endl;
    cout << "Arvore 2:" << endl;
    t2->bshow();
    cout << "=======================================" << endl;
    avl_tree *t3 = t1->mergeTrees(t1->getRoot(), t2->getRoot());
    cout << "Arvore 3:" << endl;
    t3->bshow();
    cout << "========================================" << endl;

}