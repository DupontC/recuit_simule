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
    int nb_sommet;
    int max;
    int min;
    std::string out_file;
    if(argc<6){
       std::stringstream ss1;
       std::stringstream ss2;
       std::stringstream ss3;
        
       ss1 << argv[1];
       ss1 >> nb_sommet;
       ss2 << argv[2];
       ss2 >> min;
       ss3 << argv[3];
       ss3 >> max;
       out_file=argv[4];
       
       cout << "sommets : "<< nb_sommet <<endl;
       cout << "min :"<< min <<endl;
       cout << "max :"<< max <<endl;
       cout << "out file :"<< out_file <<endl;
       int **matrice = gene_graph(nb_sommet,min,max);
       sav_graph(out_file, nb_sommet,matrice);
       
    }else{
        cout << "pas assez d'argument" <<endl;
    }
    return 1;
}