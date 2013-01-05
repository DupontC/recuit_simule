#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <stdlib.h>
#include "graph_complet.h"

using namespace std;
int main(int argc, char** argv) {
    std::string int_file;
    std::string out_file;
    int nb_sommet;
    
    if(argc<4){
        int_file = argv[1];
        out_file = argv[2];
        
        int **matrice = chargement(int_file, nb_sommet);
        cheminEtCout(matrice, out_file, nb_sommet);
        
    }else{
        cout << "pas assez d'argument" <<endl;
    }
    return 1;
}