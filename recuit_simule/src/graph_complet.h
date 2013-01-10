#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <stdlib.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;


void sav_graph(std::string, int, int**);
void sav_res(std::string ,int ,int ,double ,int ,int ,std::string);
int** gene_graph(int ,int ,int);
int** copyMatrice(int** , int );
std::string cheminEtCout(int **, std::string, int &);
void permutationSegment(std::string&);
void acceptationRecuit(std::string& ,std::string& ,int&, int&, double tx, int ** );
int ** chargement(std::string, int &);
void displayChemin(std::string , std::string );
void displayCout(std::string , int);
void chargementParams();
int coutChemin(std::string, int ** );
void chargementParams(std::string ,int &,int &,double &,int &);

