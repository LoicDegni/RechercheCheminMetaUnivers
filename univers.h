#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <queue>
#include <string>
#include <cstdlib>
#include <cassert>
#include <fstream>
#include "graphe.h"
#include "coordonnees.h"
using namespace std;


class Univers
{
    struct agent_state{
        vector<char> chemin;
        unsigned int current_univers;
    };
    struct Arete{
        Arete(Coordonnees _c, int _d, int _u): c(_c), distance(_d), univers(_u){};
        Coordonnees c;
        int distance;
        int univers;
    };

	unsigned int N; 	// Nombre de ligne et nombre de colonnes
	unsigned int C; 	// Nombre de couleur


    unordered_map<int, Graphe<Coordonnees, int> > cellules; 
    unordered_map<int, Coordonnees> entree;
public:
	Univers()  {}
	~Univers() {}

    void Univers::ajouterCellule(const Coordonnees& c);
    void ajouterArete(const int a, const int b);
	void plusCourtChemin(unsigned int x_depart, unsigned int y_depart, unsigned int couleur_depart, unsigned int x_destination, unsigned int y_destination);
    bool estAccessible(int couleurUnivers, const Coordonnees&);

    Graphe<Coordonnees, int>& operator[](Coordonnees a)
    {
        return cellules[a.c];
    }
    Graphe<Coordonnees, int>& operator[](int b)
    {
        return cellules[b];
    }
	friend istream& operator >> (istream& is, Univers& univers);
    friend ostream& operator << (ostream& os, Univers& univers);
};

