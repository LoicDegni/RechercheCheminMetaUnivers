/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    © Jaël Champagne Gareau (champagne_gareau.jael@uqam.ca)
*/
#ifndef MONCEAU_H
#define MONCEAU_H

#include <vector>

using namespace std;

template <class T>
class Monceau {
 public:
  void inserer(const T&);
  const T& minimum() const;
  void enleverMinimum();
  bool estVide() const;

 private:
  vector<T> contenu;
  void descendre();
  void remonter();
  
};

template <class T>
void Monceau<T>::inserer(const T& t) {
    contenu.push_back(t);
    remonter();
}

template <class T>
const T& Monceau<T>::minimum() const {
  assert(!contenu.empty());
  return contenu.front();
}

template <class T>
void Monceau<T>::enleverMinimum() {
    assert(!contenu.empty());
    contenu.front() = contenu.back();
    contenu.pop_back();
    descendre();
}

template <class T>
bool Monceau<T>::estVide() const {
  return contenu.empty();
}

template <class T>
void Monceau<T>::remonter() 
{
    size_t indiceCourant = contenu.size() - 1;

    while(indiceCourant > 0)
    {
        const size_t indiceParent = (indiceCourant-1)/2;
        if(contenu[indiceCourant] < contenu[indiceParent]){
        swap(contenu[indiceParent], contenu[indiceCourant]);
        indiceCourant = indiceParent;
        }
        else
            break;
    }
}

template <class T>
void Monceau<T>::descendre()
{
    size_t currentIndex = 0;
    size_t selectedSon = 0;

    while( (selectedSon = (2*currentIndex+1)) < contenu.size())
    {
        if(selectedSon+1 < contenu.size() && contenu[selectedSon+1] < contenu[selectedSon])
            ++selectedSon;

        if(contenu[selectedSon] < contenu[currentIndex])
        {
            swap(contenu[selectedSon], contenu[currentIndex]);
            currentIndex = selectedSon;
        }
        else
            break;
    }
}
#endif

