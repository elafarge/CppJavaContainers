#ifndef _LIST_H_
#define _LIST_H_

/**
 *
 * Classe template abstraite définissant une liste au sens de la classe List de Java, c'est à dire un conteneur générique disposant des méthodes d'accès usuelles (ajout à la fin ou au début de la liste, accès en lecture ou en écriture au ième élément, recherche...
 *
 * Le parcours d'élément se fait à l'aide d'itérateurs (tout comme en Java), cachés derrière les méthodes first(), next() et hasNext(). Contrairement au Java, ceux-ci ne sont pas définis dans une classe à part pour des raisons de simplicités. L'inconvénient de cette méthode est qu'il est impossible d'avoir plusieurs itérateurs simultanément sur la même liste. Si cela ne pose pas de problème pour l'écriture (il est fortement déconseillé de modifier une liste en cours de parcours, encore plus avec deux itérateurs différents), il peut arriver qu'on en ait besoin pour la lecture, notamment pour effectuer des tris.
 *
 * Le mot "liste" ne doit pas induire en erreur, il ne présage en rien de la façon dont les données seront stockées en mémoire (ce conteneur ne doit en aucun cas être confondu avec la notion de liste en Caml, qui porte ici, tout comme en Java, le nom de "LinkedList" (liste chainée). 
 *
 * De cette classe abstraite vont hériter deux classes : LinkedList<T> qui représente une liste chainée d'éléments de type T et Vector<T> qui stocke les données sous forme de Vecteur (tout comme en Caml et en Java).
 *
 * Ce sont ces deux classes qui vont définir la façon dont sont stockées les données et dont celles-ci seront parcourues. Il va de soit que selon l'utilisation que l'on souhaite en faire, l'un des conteneurs sera plus adapté que l'autre. Si les ajouts d'éléments sont fréquents et que les données sont parcourues de façon linéaire (on accède au dernier, puis à l'avant dernier, puis à l'avant avant dernier... élement de la liste), la LinkedList sera plus appropriée. En revanche, si la taille du conteneur est connue à l'avance et/ou ne varie pas trop, le type Vector sera le mieux adapté.
 *
 * Dernier point : l'implémentation que j'ai choisie pour LinkedList est itérative. Néanmoins une implémentation récursive est tout à fait envisageable (sous réserve de bonne gestion des questions de récursivité terminale ou non et des problèmes de complexité spatiale induite). 
 *
 * TODO : ajout d'une méthode de parcours par surcharge de l'opérateur *.
 *
 * 2014 - Etienne LAFARGE
 * École Nationale Supérieure des Mines de Paris
 * Mail : etienne.lafarge@gmail.com
 *
 */

/* Classe d'abstraction pour un type de liste générique dont les deux implémentation seront un ArrayList et une LinkedList */

#include <iostream>
#include <exception>
#include <string>
#include <sstream>

template<typename T>
class ElementNotFoundException; //Déclaration de la classe ElementNotFoundException (définie plus bas). Cette déclaration doit figurer ici car la classe ElementNotFoundException est utilisée dans la décalaration de la méthode "pos()" de List. Elle permet de dire au compilateur "Il y'a une classe ElementNotFoundException définie quelque part donc si tu lis ElementNotFoundException quelque part, ne t'inquiètes pas, tu trouvera la définition de cette classe plus loin, continues à lire jusqu'à ce qu'elle soit définie et ne renvoies pas d'erreur tout de suite s'il te plait".

template<typename T>
class List
{
       
    public:
        virtual void append(T e) = 0;
        virtual void prepend(T e) = 0;
        virtual T operator[] (int i) const = 0;
        virtual T& operator[] (int i) = 0; //Accès en écriture au i-ème élément de la liste 
        
        /////////////////////////////////////////
        ///////// MÉTHODES DE PARCOURS //////////
        /////////////////////////////////////////
        
        virtual bool hasNext() const = 0;
        virtual T next() const = 0;
        virtual T first() const = 0; 
        virtual T last() const = 0;
        virtual void remove(T e) = 0;

        /**
         * Renvoie la position de l'élément t dans la liste (ou -1 si il n'a pas été trouvé). La méthode de parcours utilisée par une implémentation donnée est cachée derrière les méthodes abstraites first(), next() et hasNext().
         */
        int pos(T t){
            int i = 0;
            this->first();
            while(this->hasNext()){
                if(t == this->next())
                    return i;
                i++;
            }
            throw ElementNotFoundException<T>(t);
            return -1;
        }

    /**
     * Surcharge de l'opérateur binaire externe << pour afficher la liste.
     */
    friend std::ostream& operator<< (std::ostream& flux, List<T> const& l){
        l.first();
        flux << "{";
        while(l.hasNext()){
            T e = l.next();
            flux << e;
            if(l.hasNext())
                flux << ", ";
        }
        flux << "}";
        return flux;
    }
};

/**
 * Classes de gestion des exceptions : 
 *
 * On définit deux types d'exception possible : le conteneur est vide et on essaie d'accéder à un élément ; on essaie d'accéder à un élément donc l'indice n'est pas dépasse la taille du conteneur (ou est strictement négatif) ; on recherche un élément qui n'est pas présent dans la liste.
 *
 */
class EmptyContainerException : public std::exception
{
    public:
        EmptyContainerException(){
            std::exception(); //Appel du constructeur de la classe mère
        }

        /**
         * Méthode ( surcharge de la méthode abstraite virtual const char* std::exception::what const throw() ) qui renvoie un message décrivant plus précisément l'exception. Ce message est généralement affiché dans le catch.
         */
        const char* what() const throw(){
            return "The given container is empty, be careful !";
        }
};

class IndexOutOfBoundsException : public std::exception
{
    public:
        IndexOutOfBoundsException(){
            std::exception(); //Appel du constructeur de la classe mère
        }

        const char* what() const throw(){
            return "The given index is out of the container's bounds, I suggest you forgot to check if hasNext() was true before calling next() on it. Or maybe you just try to access an element directly with a wrong index value.";
        }
};

template<typename T>
class ElementNotFoundException : public std::exception
{
    T el;

    public:
        ElementNotFoundException(T el) : el(el){
            std::exception(); //Appel du constructeur de la classe mère
        }

        const char* what() const throw(){ //Notez le passage par un StringStream pour afficher l'élement this->el en appelant l'opérateur de signature "std::ostream& << (std::ostream&, const T&)"
            std::stringstream msgstm;
            msgstm << "The element you requested (" << this->el << ") wasn't found in the list.";
            return msgstm.str().c_str();
        }
};


#endif
