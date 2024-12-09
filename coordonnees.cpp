/*  Position d'une cellule dans le metavers
    TP3 - Coordonnees.cpp
    Kaikou Loic Degni
*/

#include "coordonnees.h"

bool operator==(const Coordonnees& c1, const Coordonnees& c2)
{
    return ((c1.x == c2.x) && (c1.y == c2.y) );
}

bool operator <(const Coordonnees& c1, const Coordonnees& c2) 
{
    return (c1.x < c2.x)? true:((c2.x < c1.x)? false: (c1.y < c2.y) );
}

ostream& operator <<(ostream& os,const Coordonnees& c) 
{
    os << " ("
       << c.x
       << ", "
       << c.y
       << ")";
    return os;
}
