#include <iostream>
#include "node.h"
#include "avl.h"
using namespace std;

int main() {

    system("chcp 65001 > nul");

    avl_tree tree;

    for (int i = 0; i < 10; i++) {
        tree.add(i);
    }

    tree.bshow();

    return 0;
}