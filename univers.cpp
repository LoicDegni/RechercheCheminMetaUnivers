
#include "univers.h"


void Univers::ajouterCellule(const Coordonnees& c) {
    for(unsigned int i =0; i< C; i++){
        Coordonnees temp = c;
        temp.u = i;
        cellules[i].ajouterSommet(temp);
    }
}

void Univers::plusCourtChemin(unsigned int x_depart, unsigned int y_depart, unsigned int couleur_depart, unsigned int x_destination, unsigned int y_destination) 
{
    bool trouve = false;
    agent_state state;
    state.current_univers = couleur_depart;
    Monceau<Arete> pq;
    Arete current;
    unordered_map<unsigned int,unsigned int> distance;
    Coordonnees c_temp = entree.at(x_depart + y_depart*N);

    for(unsigned int i = 0; i< C; i++){
        for(auto&  sommet: cellules[i].sommets){
            distance[sommet.first.id +(N_total*i)] = numeric_limits<int>::max();
        }
    }

    distance[c_temp.id +(N_total*couleur_depart)] = 0;
    Arete depart(c_temp, -1, distance[c_temp.id + (N_total*couleur_depart)], couleur_depart, N_total);
    pq.inserer(depart);

    while(!pq.estVide()){
        current = pq.minimum();
        state.insert(current);

        if(current.coordonnees.c != state.current_univers) 
        {
            pq.inserer(Arete(current.coordonnees, current.identifiant, current.distance + 10 ,current.coordonnees.c, N_total));
            distance[current.coordonnees.id + (N_total*current.coordonnees.c)] = current.distance + 10;
        }

        pq.enleverMinimum();

        if(distance[current.coordonnees.id +(N_total*current.univers)] == numeric_limits<int>::max()){
            cout << "Il n'existe pas de chemin vers ce sommet.\n" << endl;
            break;
        }
        if(current.coordonnees.id == (x_destination + N*y_destination)) {
            trouve = true;
            break;
        } 

        Graphe<Coordonnees,int> temp = cellules[state.current_univers];
        for(const auto& sommet: temp.sommets[current.coordonnees].voisins){
            if(sommet.second + current.distance < distance.at(sommet.first.id + (N_total*state.current_univers) ) ){
                distance.at(sommet.first.id + (N_total*state.current_univers) ) = sommet.second + current.distance;
                Arete add(sommet.first, current.identifiant, distance.at(sommet.first.id + (N_total*state.current_univers) ), state.current_univers, N_total );
                pq.inserer(Arete(add));
            }
        }
    }
    if(trouve)
    {
        vector<char> chemin;
        unsigned int distance_finale = state.chemin.at(current.identifiant).distance;
        int enfant = state.chemin.at(current.identifiant).identifiant;
        int precedant = state.chemin.at(enfant).parent;
        
        do{
            if(state.chemin.at(enfant).distance - state.chemin.at(precedant).distance == 10){
            chemin.push_back('c');
            }else if(state.chemin.at(enfant).distance - state.chemin.at(precedant).distance == 1){
            if(state.chemin.at(enfant).coordonnees.x < state.chemin.at(precedant).coordonnees.x){
                chemin.push_back('d');
            }else if(state.chemin.at(enfant).coordonnees.y < state.chemin.at(precedant).coordonnees.y){
                chemin.push_back('h');
            }else if(state.chemin.at(enfant).coordonnees.x > state.chemin.at(precedant).coordonnees.x){
                chemin.push_back('g');
            }else if(state.chemin.at(enfant).coordonnees.y > state.chemin.at(precedant).coordonnees.y){
                chemin.push_back('b');
            }
        }
        enfant = precedant;
        precedant = state.chemin.at(precedant).parent;
        }while(precedant != -1);

        for (auto it = chemin.rbegin(); it != chemin.rend(); ++it) 
            cout << *it << " ";
        cout << distance_finale << "\n" << endl;
    }
} 


    
bool Univers::estAccessible(unsigned int couleurUnivers, const Coordonnees& c)
{
    return couleurUnivers != c.c;
}


istream& operator >> (istream& is, Univers& univers) {
	is >> univers.N; 		// Nombre de ligne et de colonnes
	is >> univers.C; 		// Nombre de couleurs
    univers.N_total = univers.N * univers.N;

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
    for(unsigned int a = 0; a < univers.C; a++){
        for(unsigned int i = 0; i < univers.N_total; i++){
            //Verifie si on est pas sur derniere ligne
            if(univers.N_total - i > univers.N){
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
	return is;
}

