#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <queue>
#include <string>
#include <cstdlib>
#include <cassert>
#include <fstream>
#include <functional>
#include <unordered_map>
#include <limits>
#include "graphe.h"
#include "coordonnees.h"
#include "monceau.h"
using namespace std;

class Univers
{
    unsigned int N; // Nombre de ligne et nombre de colonnes
    unsigned int C; // Nombre de couleur
    unsigned int N_total;

    struct Arete
    {
        Arete(){};
        Arete(Coordonnees _c, int _p, unsigned int _d, unsigned int _u, unsigned int _nb) : coordonnees(_c), parent(_p), distance(_d), univers(_u) 
        {

                identifiant = _c.id + (_nb * _u);
        };

        Coordonnees coordonnees;
        int parent;
        unsigned int distance;
        unsigned int univers;
        unsigned int identifiant;

        friend ostream &operator<<(ostream &os, const Arete &arete)
        {
            cout << arete.coordonnees << "\n" << endl;
            return os;
        }
        friend bool operator<(const Arete &a1, const Arete &a2)
        {
            return (a1.distance < a2.distance);
        }
    };

    struct agent_state
    {
        unordered_map<unsigned int, Arete> chemin;
        unsigned int current_univers;

        void insert(Arete &arete)
        {
            current_univers = arete.univers;
            chemin[arete.identifiant] = arete;
        }
    };

    unordered_map<int, Graphe<Coordonnees, int>> cellules;
    unordered_map<int, Coordonnees> entree;

public:
    Univers() {}
    ~Univers() {}

    void ajouterCellule(const Coordonnees &c);
    void plusCourtChemin(unsigned int x_depart, unsigned int y_depart, unsigned int couleur_depart, unsigned int x_destination, unsigned int y_destination);
    bool estAccessible(unsigned int couleurUnivers, const Coordonnees &);

    Graphe<Coordonnees, int> &operator[](Coordonnees a)
    {
        return cellules[a.c];
    }
    Graphe<Coordonnees, int> &operator[](int b)
    {
        return cellules[b];
    }
    friend istream &operator>>(istream &is, Univers &univers);
};
