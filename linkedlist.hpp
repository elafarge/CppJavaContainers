#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include "list.hpp"

#ifndef nullptr
#define nullptr 0
#endif

/////////// ELEMENT DE LISTE ///////////

/*
 * Structure intermédiaire définissant un élement de la liste comme le doublet composé d'un élément de type T et d'un pointeur sur l'élément suivant (ou nullptr si il n'y a pas d'élément suivant).
 */

template<typename T>
struct ListElt{
    T val;
    ListElt* next;

    ListElt(T nVal, ListElt* nNext){
        val = nVal;
        next = nNext;
    }
};

/////////////// LA LISTE ///////////////

template<typename T>
class LinkedList : public List<T>
{    
    private:

        ListElt<T>* mFirst; //Pointeur sur le premier élément de la liste
        ListElt<T>* mLast; //Pointeur sur le dernier élément de la liste
        mutable ListElt<T>* mCurs; //Itérateur pointant sur un élément de la liste, le mot clef mutable signifie ici que l'on peut modifier mCurs, même dans une méthode déclarée "const" comme first par exemple.
        int mSize; //Entier maintenu à jour au fil de l'évolution de la liste et contenant sa taille (évite d'avoir à recompter les éléments de la liste chaque fois qu'on veut sa taille).
    
    public:

        /**
         * Constructeur par défaut
         */
        LinkedList(){
            mFirst = nullptr;
            mLast = nullptr;
            mCurs = nullptr;
            mSize = 0;
        }

        /**
         * Destructeur : parcours les éléments de la liste pour les supprimer un a un
         */
        ~LinkedList(){
            ListElt<T>* next = mFirst;
            ListElt<T>* prev = nullptr;
            while(next != nullptr){
                prev = next;
                next = prev->next;
                delete prev;
            }
        }

        /**
         * Ajout d'un élément en fin de liste
         */
        void append(T e){
            ListElt<T>* nHead = new ListElt<T>(e, nullptr);

            if(mFirst == nullptr){
                mFirst = nHead;
                mLast = nHead;
            }
            else{
                //Cette méthode n'est plus utilisée depuis l'ajout du pointeur mLast sur le dernier élément
                /*ListElt<T>* oldHead = mFirst;
                while(oldHead->next != nullptr)
                    oldHead = oldHead->next;
                oldHead->next = nHead;*/
                mLast->next = nHead;
                mLast = nHead;
            }
            mSize++;
        }

        /**
         * Ajout d'un élément en début de liste
         */
        void prepend(T e){
            ListElt<T>* nFirst = new ListElt<T>(e, mFirst);
            mFirst = nFirst;
            mSize++;
        }

        /**
         * Accès en lecture à la valeur du i-ème élément de la liste. (La modification est inderdite à l'aide du mot-clef const et grace au fait que la valeur renvoyée est copiée en mémoire (TODO : à vérifier)
         */
        T operator[] (int i) const{
            if(this->mSize == 0)
                throw EmptyContainerException();

            if(i < 0 || this->mSize <= i)
                throw IndexOutOfBoundsException();

            int k = 0;
            ListElt<T>* elt = mFirst;
            while(k < i){
                elt = elt->next;
                k++;
            }
            return elt->val;
        }

        /**
         * Accès en écriture au i-ème élément de la liste. Une référence vers la valeur de ce i-ième élement est retournée ce qui en permet la modification
         */
        T& operator[] (int i){
            if(this->mSize == 0)
                throw EmptyContainerException();

            if(i < 0 || this->mSize <= i)
                throw IndexOutOfBoundsException();

            int k = 0;
            ListElt<T>* elt = mFirst;
            while(k < i){
                elt = elt->next;
                k++;
            }
            return elt->val;
        }

        /**
         * Retourne true si l'itérateur mCurs n'est pas en fin de liste
         */
        bool hasNext() const{
            if(this->mCurs == nullptr)
                return false;

            return this->mCurs != nullptr;
        }

        /**
         * Renvoie la valeur de l'élément vers lequel pointe l'itérateur mCurs (ou le premier élément si mCurs n'a pas été initialisé).
         */
        T next() const{
            if(this->mCurs != nullptr){
                T ret = mCurs->val;
                mCurs = mCurs->next;
                return ret;
            }

            if(this->mSize == 0)
                throw EmptyContainerException();

            throw IndexOutOfBoundsException();
        }

        /**
         * Renvoie le premier élément de la liste ou nullptr si la liste est vide.
         */
        T first() const{
           this->mCurs = this->mFirst;
            if(this->mCurs != nullptr)
                return this->mCurs->val;
            else
                throw EmptyContainerException();
        }

        T last() const{
            if(this->mLast == nullptr)
               throw EmptyContainerException();
 

            return this->mLast->val; 
        }

        void remove(T e){
            this->first();
            ListElt<T>* prev = nullptr;
            ListElt<T>* t = this->mFirst;
    
            while(t != nullptr){
                if(t->val == e){
                    if(prev == nullptr){
                        prev = this->mFirst;
                        this->mFirst = t->next;
                        delete prev;
                    }else{
                        prev->next = t->next;
                        delete t;
                    }
                    return;
                }
                prev = t;
                t = t->next;
            }

            throw ElementNotFoundException<T>(e);
        }


};


#endif
