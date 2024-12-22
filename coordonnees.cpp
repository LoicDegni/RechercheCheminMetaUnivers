/*  Position d'une cellule dans le metavers
    TP3 - Coordonnees.cpp
    Kaikou Loic Degni
*/

#include "coordonnees.h"

bool operator==(const Coordonnees& c1, const Coordonnees& c2)
{
    return ((c1.x == c2.x) && (c1.y == c2.y) && (c1.u == c2.u));
}

bool operator <(const Coordonnees& c1, const Coordonnees& c2) 
{
    return (c1.id < c2.id);
}

Coordonnees& Coordonnees::operator =(const Coordonnees& c)
{
    if(this != &c){
        this->x = c.x;
        this->y = c.y;
        this->c = c.c;
        this->id = c.id;
        this->u = c.u;
    }
    return *this;
}


ostream& operator <<(ostream& os,const Coordonnees& c) 
{
    os << " ("
       << c.x
       << ", "
       << c.y
       << ") couleur:"
       << c.c
       << "  ID:"
       << c.id;
    return os;
}
