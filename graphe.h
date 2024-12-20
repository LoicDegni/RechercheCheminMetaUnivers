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

// Le type S est le type utilisé pour identifier les sommets
template <class S,class A>
class Graphe{

private:
    struct Sommet
    {
        map<S,A> voisins;
        //set<S> voisins; // ensemble des sommets accessibles via les arêtes sortantes du sommet.
                        // Cela est légèrement différent de la page 128 des notes de cours.
                        // C'est voulu, car ici les arêtes ne sont pas étiquetées par un poids (ex: distance).
                        // Pour attacher une étiquette, il suffirait de modifier pour : map<S, A> sortants;
        mutable bool visited = false; // mutable veut dit que je peux manipuler meme si const. on a le droit de modifier visited. meme si ref const
        friend class Univers;
    };

    map<S, Sommet> sommets; // identification --> sommet
    void reinitVisited() const;  

public:
    // Interface public pour créer le graphe.
    void ajouterSommet(const S& s);
    void ajouterAreteOrientee(const S& s1, const S& s2, int p);
    void ajouterAreteNonOrientee(const S& s1, const S& s2, int p);

    void parcoursRechercheProfondeur(const S& s) const;
    void parcoursRechercheLargueur(const S& s, bool = false) const;
    void extraireComposantesConnexes() const;
    void afficherCellules() const;
    void afficherVoisin(const S&) const;

    typename map<S, Sommet>::iterator begin();
    typename map<S, Sommet>::const_iterator begin() const;
    typename map<S, Sommet>::iterator end();
    typename map<S, Sommet>::const_iterator end() const;


    Sommet& operator[](const S& s);
    const Sommet& operator[](const S& s) const;
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
    // Doit ajouter les 2 arêtes orientées : s1->s2 et s2->s1;
}

template <class S, class A>
void Graphe<S,A>::ajouterAreteOrientee(const S& s1, const S& s2, int p){
    //si ponderation sur arete: somets[s1].voisin[s2] = voisin[ponderation]
    sommets[s1].voisin[s2] = p;
    //sommets[s1].voisins.insert(s2); //va chercher dans l'ebre le s1. Quand la trouver, va le mettre
    // Doit uniquement ajouter s1->s2.
}

template <class S, class A>
void Graphe<S,A>::parcoursRechercheProfondeur(const S& s) const{
    reinitVisited();

    stack<S> awaiting;
    awaiting.emplace(s);

    bool first = true;
    while(!awaiting.empty())
    {
        const auto currentSName = awaiting.top();
        const auto& currentSommet = sommets.at(currentSName);
        awaiting.pop();
        
        if(!currentSommet.visited)
        {
            for(auto current = currentSommet.voisins.rbegin(); current != currentSommet.voisins.rend(); ++current)
                awaiting.emplace(*current);
            if(!first)
                cout << " ";
            else
                first = false;
            
            cout << currentSName;

            currentSommet.visited = true;
        }
    }
    cout << "}\n";
}

template <class S, class A>
void Graphe<S,A>::parcoursRechercheLargueur(const S& s, bool component) const{
    if(!component)
    {
        reinitVisited(); // quand tu fais le parcours connexe tu ne veux pas changer les noeud deja vue pour composantes connexes.
    }
    else
    {
        cout << "{";
    }

    queue<S> awaiting;
    awaiting.emplace(s);

    bool first = true;
    while(!awaiting.empty())
    {
        const auto currentSName = awaiting.front();
        const auto& currentSommet = sommets.at(currentSName);
        awaiting.pop();

        if(!currentSommet.visited)
        {
            for(const auto& current: currentSommet.voisins)
                awaiting.emplace(current);

            if(!first)
                cout <<(component ? "," : " ");
            else
                first = false;

            cout << currentSName;

            currentSommet.visited = true;
        }
    }
    cout << (component ? "}" : "\n");
}

template <class S, class A>
void Graphe<S,A>::extraireComposantesConnexes() const
{
    reinitVisited();

    bool first = true;

    cout <<"{";
    for(const auto& [sName, current]: sommets)
    {
        if(!current.visited)
        {
            if(!first)
                cout << ",";
            else
                first = false;
            parcoursRechercheLargueur(sName,true);
        }
    }
    cout <<"}\n";
}

template <class S, class A>
void Graphe<S,A>::afficherCellules() const
{
    for(const auto& [sName, current]: sommets)
    {
        cout << sName<<" ";
    }
    cout << sommets.size() <<  "\n" << endl;
}

template<class S, class A>
void Graphe<S,A>::afficherVoisin(const S& s) const
{
    for( auto const& current: sommets.at(s).voisins)
        cout << current << " ";
    cout << "\n" << endl;
}

template<class S, class A>
typename map<S,typename Graphe<S, A>::Sommet>::iterator begin() {
    return sommets.begin();
}

template<class S, class A>    
typename map<S, typename Graphe<S, A>:: Sommet>::const_iterator begin() const {
    return sommets.begin();
}

template<class S, class A>
typename map<S, typename Graphe<S,A>:: Sommet>::iterator end() {
    return sommets.end();
}

template<class S, class A>
typename map<S, typename Graphe<S,A>:: Sommet>::const_iterator end() const {
    return sommets.end();
}

template <class S, class A>
void Graphe<S,A>::reinitVisited() const
{
    for(const auto& [_,current]: sommets)
        current.visited = false;
}

#endif

