/*  INF3105 - Structures de données et algorithmes
    Lab 11 -- Graphes / Représentations et algorithmes de base
    http://cria2.uqam.ca/INF3105/lab11/
*/
#if !defined(__GRAPHE_H__)
#define __GRAPHE_H__

#include <queue>
#include <stack>
#include <map>
#include <set>
#include <algorithm>
#include <iostream>

using namespace std;

template <class S,class A>
class Graphe{

private:
    struct Sommet
    {
        map<S,A> voisins;
        mutable bool visited = false;
        friend class Univers;
    };

    map<S, Sommet> sommets; 

public:
    void ajouterSommet(const S& s);
    void ajouterAreteOrientee(const S& s1, const S& s2, int p);
    void ajouterAreteNonOrientee(const S& s1, const S& s2, int p);
    friend class Univers;
};

template <class S, class A>
void Graphe<S,A>::ajouterSommet(const S& s){
    sommets[s]; // initialise le sommet par defaut
}

template <class S, class A>
void Graphe<S, A>::ajouterAreteNonOrientee(const S& s1, const S& s2, int p){
    ajouterAreteOrientee(s1,s2, p);
    ajouterAreteOrientee(s2,s1,p);
}

template <class S, class A>
void Graphe<S,A>::ajouterAreteOrientee(const S& s1, const S& s2, int p){
    sommets[s1].voisins[s2] = p;
}

#endif

