#include "graph_complet.h"
using namespace std;

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while(std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    return split(s, delim, elems);
}

int** copyMatrice(int ** matrice, int nb_sommet){
    int ** new_matrice = NULL;
    new_matrice = new int * [nb_sommet];
    for (int i=0; i<nb_sommet; ++i) {
        new_matrice [i] = new int [nb_sommet];
    }
    for (int i=0; i<nb_sommet; ++i) {
        for (int j=0; j<nb_sommet; ++j) {
            new_matrice[i][j] = matrice[i][j];
        }
    }
    return new_matrice;
}

/*
 void sav_graph(std::string out_file, int nb_sommet, int** matrice){
 std::string monFichier="./resultats/"+out_file;
 ofstream fichier(monFichier.c_str(), ios::out|ios::trunc);  // ouverture en écriture
 cout << "sav in " << out_file<< endl;
 if(fichier)
 {
 fichier << nb_sommet <<endl;
 for(int i=0; i<nb_sommet; ++i){
 for(int j=0; j<nb_sommet; ++j){
 fichier << matrice[i][j]<<" ";
 }
 fichier << endl;
 }
 fichier.close();
 }
 else
 cerr << "Impossible d'ouvrir le fichier !" << endl;
 }
 
 int ** gene_graph(int nb_sommet,int min, int max){
 int** matrice = NULL ;
 
 //on declare la matrice
 matrice = new int * [nb_sommet];
 for (int i=0; i<nb_sommet; ++i) {
 matrice [i] = new int [nb_sommet];
 }
 
 //on ajout les couts des distances entre le villes
 for(int i=0; i<nb_sommet; ++i){
 for(int j=0; j<nb_sommet; ++j){
 if(i!=j){
 matrice[i][j]=rand()%((max+1)-min) +min;
 }else{
 matrice[i][j]=0;
 }
 }
 }
 return matrice;
 }
 */

std::string cheminEtCout(int** matrice, std::string out_file, int &nb_sommet){
    int num_ville=0;
    int indice_j;
    int sumCout=0;
    int cout=0;
    int coutTmp=-1;
    int nb_ville_res=nb_sommet;
    int i=0;
    std::string chemin="";
    
    std::cout << "calcul du chemin"<<endl;
    //on boucle afin de marquer toutes les villes
    while (nb_ville_res>0) {
        std::stringstream ss;
        std::string ville;
        ss << i;
        ss >> ville;
        
        chemin=chemin+ville+" ";
        for(int j=0;j<nb_sommet;j++){
            //on regarde les villes accesible
            if(i!=j && i!=-1 && j!= -1){
                //si le cout est minimale
                if(coutTmp==-1 || (coutTmp > matrice[i][j] && matrice[i][j]!=-1)){
                    coutTmp=matrice[i][j];
                    indice_j=j;
                }
            }
        }
        //on marque la ville comme deja passé
        for(int j=0;j<nb_sommet;j++){
            matrice[i][j]=-1;
        }
        for(int k=0;k<nb_sommet;k++){
            matrice[k][i]=-1;
        }
        //std::cout << "indice "<<indice_j <<" cout "<<coutTmp<<endl;
        i=indice_j;
        //maj du cout du chemin minimal
        cout=cout+coutTmp;
        coutTmp=-1;
        
        //on decremente le nombre de ville restantes a parcourir
        nb_ville_res--;
    }
    return chemin;
}

void permutationSegment(std::string &chemin){
    
    int nbSommet;
    int indice;
    std::string tmp;
    std::vector<std::string> path = split(chemin,' ');
    std::vector<std::string>::iterator it;
    nbSommet=path.size();
    
    //on permute 2 villes aleatoirement
    indice=rand()%(nbSommet);
    //cout << "indice " <<indice <<endl;
    if(indice==nbSommet-1){
       tmp = path.at(indice);
       path.at(indice) = path.at(indice-1);
       path.at(indice - 1) = tmp;
    }else{
        tmp = path.at(indice);
        path.at(indice) = path.at(indice+1);
        path.at(indice + 1) = tmp;
    }
    
    chemin="";
    
    //on recontruir le chemin
    for (it = path.begin() ; it < path.end(); it++)
    {
        chemin=chemin+(*it)+" ";
    }
}

void acceptationRecuit(std::string &bestChemin,std::string &chemin ,int &Tmax, int &Tmin, double tx, int** matrice){
    int coutBest = coutChemin(bestChemin, matrice);
    int coutCheminCourant = coutChemin(chemin, matrice);
    
    //si le recuit est accepter en fonction de notre tx alors  bestChemin = chenin et on baise la temperature
    //if(tx < exp(1/(Tmax*(coutBest-coutCheminCourant)){
    if(coutBest-coutCheminCourant>0){
        bestChemin = chemin;
        std::cout << "new cout "<< coutCheminCourant << " - chemin -> " << chemin <<endl;
        Tmax-1;
    }else{
        //sinon on garde le meilleur chemin
        chemin = bestChemin;
    }
    
}
//calcul le cout d'un chemin
int coutChemin(std::string chemin, int** matrice){
    int cout=0;
    int etapeD;
    int etapeA;
    std::vector<std::string> path = split(chemin,' ');
    std::vector<std::string>::iterator it;
    for (it = path.begin() ; it < path.end()-1; it++)
    {
        std::stringstream ssD;
        std::stringstream ssA;
        
        ssD << *it;
        ssD >> etapeD;
        
        ssA << path.at(it - path.begin()+1);
        ssA >> etapeA;
        
        cout = cout + matrice[etapeD][etapeA];
    }
    return cout;
}

void displayChemin(std::string out_file, std::string ville){
    std::string monFichier="./resultats/"+out_file;
    ofstream fichier(monFichier.c_str(), ios::out|ios::app);  // ouverture en écriture
    
    if(fichier)
    {
        fichier << ville << " - " ;
    }
    else
        cerr << "Impossible d'ouvrir le fichier !" << endl;
}

void displayCout(std::string out_file, int cout){
    std::string monFichier="./resultats/"+out_file;
    ofstream fichier(monFichier.c_str(), ios::out|ios::app);  // ouverture en écriture
           
    if(fichier)
    {
        fichier << endl <<" Cout du trajet "<<cout <<endl;
    }
    else
        cerr << "Impossible d'ouvrir le fichier !" << endl;
}

int ** chargement(std::string int_file,int &nb_sommet){
    //ouverture du fichier en lecture
    std::ifstream text;
    text.open(int_file.c_str());
    
    //declaration des variables
    int indice_i=0;
    int indice_j=0;
    int cout;
    int** matrice = NULL ;
    
    std::cout << "chargement du graph complet" <<endl;
    //si le fichier est ouvert ..
    if(text.is_open())
    {
        //tant qu'il y a des lignes
        while(text.good())
        {
            std::string line = "";
            //on recupere chaque ligne du fichier
            getline(text, line);
            if(line.length() != 0)
            {
                //on recupere les arguments de la ligne
                std::vector<std::string> x = split(line, ' ');
                std::vector<std::string>::iterator it;
                //on parcour les différents elements
                if(x.size()>1){
                    indice_j=0;
                    for (it = x.begin() ; it < x.end(); it++)
                    {
                        // on caste les arguemnts :  string to int
                        std::stringstream ss;
                        ss << *it;
                        ss >> cout;
                        //on remplie la matrice
                        matrice[indice_i][indice_j] = cout;
                        indice_j++;
                    }
                    indice_j=0;
                    indice_i++;
                }else{
                    std::stringstream ss;
                    it = x.begin() ;
                    ss << *it;
                    ss >> nb_sommet;
                    //on initialise la matrice
                    matrice = new int * [nb_sommet];
                    for (int i=0; i<nb_sommet; ++i) {
                        matrice [i] = new int [nb_sommet];
                    }
                }
            }
        }
        //on ferme le fichier
        text.close();
    }else{
        std::cout << "can't open the file" <<endl;
    }
    return matrice;
}
void sav_res(std::string out_File,int Tmax,int Tmin,double tx,int iteration,int cout,std::string bestChemin){
    std::string monFichier="./resultats/"+out_File;
    ofstream fichier(monFichier.c_str(), ios::out|ios::app);  // ouverture en écriture
    
    if(fichier)
    {
        fichier << "--------------------------------------------------------------------" <<endl;
        fichier << "Tmax	Tmin    coefficient     nb_iter_max     cout_min      chemin" <<endl;
        fichier << "--------------------------------------------------------------------" <<endl;
        fichier << Tmax <<"\t   ";
        fichier << Tmin <<"\t   ";
        fichier << tx <<"\t   ";
        fichier << iteration <<"\t   ";
        fichier << cout <<"\t   ";
        fichier << bestChemin <<endl;
        fichier.close();
    }
    else
        cerr << "Impossible d'ouvrir le fichier !" << endl;
}
void chargementParams(std::string param_file,int &Tmax,int &Tmin,double &tx,int &iteration){
    std::ifstream text;
    text.open(param_file.c_str());
    if(text.is_open())
    {
        cout << "reding the file" << endl;
        while(text.good())
        {
            std::string line = "";
            //on recupere chaque ligne du fichier
            getline(text, line);
            if(line.length() != 0)
            {
                std::string name;
                std::vector<std::string> previous;
                int cost;
                int nbNext;
                //on recupere les arguments de la ligne
                cout << line << endl;
                std::vector<std::string> x = split(line, ' ');
                std::vector<std::string>::iterator it;
                
                //on parcour les différents elements
                for (it = x.begin() ; it < x.end(); it++)
                {
                    if(it - x.begin() == 0)
                    {
                        //nunber of @param
                        std::stringstream ss;
                        //cast the char to int
                        ss << *it;
                        ss >> Tmax;
                    }
                    else if(it - x.begin() == 1)
                    {
                        //cost of the tache
                        std::stringstream ss;
                        //cast the char to int
                        ss << *it;
                        ss >> Tmin;
                    }
                    else if(it - x.begin() == 2)
                    {
                        //nunber of @param
                        std::stringstream ss;
                        //cast the char to int
                        ss << *it;
                        ss >> tx;
                    }
                    else if(it - x.begin() == 2)
                    {
                        //nunber of @param
                        std::stringstream ss;
                        //cast the char to int
                        ss << *it;
                        ss >> iteration;
                    }
                }
            }
        }//end of file
        //we close the file
        text.close();
    }else{
        cout << "can't open the file" <<endl;
    }
}
