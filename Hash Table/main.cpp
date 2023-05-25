#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include "Codification.h"
#include "HashTable.h"
using namespace std;

int main() 
{
    HashTable<std::string, float> ht (2, 1.0, 2.0, code_std_string);

    ht.add("atilio", 13);
    ht.add("erick", 14);
    ht.add("joana", 15);
    ht.add("atiio", 13);
    ht.add("eick", 14);
    ht.add("jana", 15);
    ht.add("alio", 13);
    ht.add("eck", 14);
    ht.add("ana", 15);

    ht.remove("jeferson");
    

    cout << ht.at("atilio") << endl;
    cout << ht.at("joana") << endl;
    cout << ht.at("erick") << endl;

}
