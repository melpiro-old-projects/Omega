#pragma once
#include <vector>
namespace O
{
namespace data
{




template<class T>
class Tree
{
public:
    Tree();
    Tree(T value);

    std::vector<Tree<T>> getChilds() const;
    std::vector<T> getChildsValues() const;
    void addChild(T value);


    // retourne le niveau de recurance
    int addChildUnder(T value, T parent);

    // prend en paramètre une fonction qui evalue
    // l'efficacité d'ajouter un éléments fils
    // sous un élément père
    // ex : arbre d'ensemble
    // la fonction aura pour but d'ajouter
    // les sous ensembles dans le plus grand ensemble père
    // possible
    // fonction : double func(T parent, T enfant)
    // fonction : retourne le score (-1 pour annuler)
    // retourne le niveau de recurance
    int addChildFromRelation(T value, double (*func)(T, T));
    
private:

    int addChildUnder(T value, T parent, int lvlRecur);
    int addChildFromRelation(T value, double (*func)(T, T), int lvlRecur);


    T value;
    std::vector<Tree<T>> childs;

};




} // namespace name    
} // namespace O



#include "Data/Tree.ipp"