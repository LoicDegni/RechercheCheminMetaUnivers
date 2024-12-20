
#include "univers.h"


void Univers::ajouterCellule(const Coordonnees& c) {
    for(int i =0; i< N; i++)
        cellules[i].ajouterSommet(c);
}

void Univers::plusCourtChemin(unsigned int x_depart, unsigned int y_depart, unsigned int couleur_depart, unsigned int x_destination, unsigned int y_destination) {
    agent_state state;
    state.current_univers = couleur_depart;
    priority_queue<Arete> pq;
    unordered_map<Coordonnees, int> distance;
    Coordonnees c_temp = entree.at(x_depart + y_depart*N);
    for(int i = 0; i< N; i++){
        for(auto&  sommet: cellules[i]){
            distance[sommet.first] = numeric_limits<int>::max();
        }
    }
    distance[c_temp] = 0;
    pq.push(Arete(c_temp,distance[c_temp], c_temp.c));

    while(!pq.empty()){
        Arete current = pq.top();
        state.current_univers = current.univers;
        for(int i = 0; i < N; i++){
            if(i != current.univers) pq.push(Arete(current.c, 10, i));
        }
        pq.pop();

        if(distance[current.c] == numeric_limits<int>::max()) break;
        if(current.c.id == (x_destination + N*y_destination)) {
            //Condition de sortie
        } 

        Graphe<Coordonnees,int> temp = cellules[state.current_univers];
        for(const auto& sommet: temp.sommets[current.c].voisins){
            if(sommet.second + current.distance < distance[sommet.first]){
                distance[sommet.first] = sommet.second + current.distance;
                pq.push(Arete(c_temp,distance[c_temp], c_temp.c));
            }
        }
    }
}

bool Univers::estAccessible(int couleurUnivers, const Coordonnees& c)
{
    return couleurUnivers != c.c;
}


istream& operator >> (istream& is, Univers& univers) {
	is >> univers.N; 		// Nombre de ligne et de colonnes
	is >> univers.C; 		// Nombre de couleurs

	assert(univers.N > 0);
	assert(univers.C > 0);

    unsigned int couleur, id;
	for(unsigned int y = 0; y<univers.N; y++) {
		for(unsigned int x = 0; x<univers.N; x++) {
			is >> couleur;
            id = (x + y*univers.N);
            Coordonnees cellule(id, x, y, couleur);
            univers.ajouterCellule(cellule);
            univers.entree[id] = cellule;
		}
	}
    unsigned int nbElements = univers.N * univers.N;

    for(unsigned int a = 0; a < univers.C; a++){
        for(unsigned int i = 0; i < nbElements; i++){
            //Verifie si on est pas sur derniere ligne
            if(nbElements - i > univers.N){
                if(univers.estAccessible(a, univers.entree.at(i + univers.N) ) ){
                    univers[a].ajouterAreteOrientee(univers.entree.at(i), univers.entree.at(i+ univers.N), 1);
                }
            }
            //Verifie si on est pas sur premiere ligne
            if(i > univers.N){
                if(univers.estAccessible(a, univers.entree.at(i - univers.N) )){
                    univers[a].ajouterAreteOrientee(univers.entree.at(i), univers.entree.at(i - univers.N), 1);
                }
            }
            //Verifie on est pas a la premiere case d'une ligne
            if(i % univers.N > 0){
                if(univers.estAccessible(a, univers.entree.at(i-1))){
                    univers[a].ajouterAreteOrientee(univers.entree.at(i), univers.entree.at(i-1), 1);
                }
            }
            //verifie si on est pas a la derniere case d'une ligne
            if((i + 1)% univers.N > 0){
                if(univers.estAccessible(a, univers.entree.at(i + 1))){
                    univers[a].ajouterAreteOrientee(univers.entree.at(i), univers.entree.at(i+1), 1);
                }
            }
        }
    }
    //univers[1].afficherVoisin(entree.at(0));
	return is;
}


ostream& operator <<(ostream& os, Univers& univers) { 
    for(const auto& [couleur,cellulec]: univers.cellules){
        cout << "couleur: " << couleur << " ";
        cellulec.afficherCellules();
    }
    return os;
}

