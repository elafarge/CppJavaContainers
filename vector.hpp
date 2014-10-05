#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "list.hpp"

#ifndef nullptr
#define nullptr 0
#endif


/**
 * La variable de préprocesseur LIST_CLUSTER_SIZE définie le nombre de case dont on va augmenter le tableau contenant les éléments lorsque la taille de de celui-ci ne suffit plus. Cela permet d'éviter, lorsqu'on rajoute 5 éléments, d'avoir à détruire puis à recréer le tableau de données 5 fois. Cette valeur est purement arbitraire et, pour un Vecteur dans lequel on ajoute souvent des données, il est conseillé d'augmenter cette valeur.
 */
#ifndef LIST_CLUSTER_SIZE
#define LIST_CLUSTER_SIZE 10
#endif

template<typename T>
class Vector : public List<T>
{
    private:
        int mSize; //Taille du tableau mTab (est supérieur ou égal au nombre d'éléments que nous avons mis dans la collection
        mutable int mCursor; //Itérateur sur le tableau
        int mFilled; //Nombre d'éléments réellement présents dans le tableau (mFilled <= mSize)
        T* mTab;

        /**
         * Méthode permettant d'étendre le tableau mTab de n case + le nombre de cases restantes de sorte à ce que la taille du nouveau tableau reste une multiple de LIST_CLUSTER_SIZE
         */
        void extendTab(int n){
            int fact = n/LIST_CLUSTER_SIZE + 1;
            T* oldTab = this->mTab;
            
            //Création du tableau étendu
            mTab = new T[mSize + fact*LIST_CLUSTER_SIZE];
            mSize = mSize + fact*LIST_CLUSTER_SIZE;


            //Copie des éléments un à un
            for(int i = 0; i < mFilled; i++){
                mTab[i] = oldTab[i];
            }

            //Suppression de l'ancien tableau
            delete[] oldTab;
        }


        /**
         * Décale le tableau vers l'avant à partir de l'élément d de n cases (utile pour la méthode prepend)
         */
        void offset(int d, int n){
            T tmp, ttmp;
            //On agrandit le tableau autant que nécessaire
            if(n + mFilled >= mSize)
                this->extendTab(n);

            //Et on décale comme des gros autistes
            for(int i = mFilled; i >= d; i--){
                mTab[i-1+n] = mTab[i-1];
            }
        }

        /**
         * Décale le tableau de n cases vers l'arrière de la fin jusque à l'élément d inclus (utile pour la méthode remove)
         */
        void backOffset(int d, int n){
            for(int i = d; i <= this->mFilled-n-1; i++){
                mTab[i] = mTab[i+n];
            }
        }


    public:

        /**
         * Constructeur par défaut (on met la taille de mTab à LIST_CLUSTER_SIZE, il y'a peu de chance qu'on crée un Vecteur pour ne rien y insérer...
         */
        Vector(){
            mCursor = -1;
            mSize = LIST_CLUSTER_SIZE;
            mFilled = 0;
            mTab = new T[LIST_CLUSTER_SIZE];
        }

        /**
         * Destructeur libérant les ressources allouées à l'instance de Vector<T>
         */
        ~Vector(){
            if(mTab != nullptr)
                delete[] mTab;
        }

        void append(T e){
            //Si nécessaire on augmente la taille du tableau
            if(mFilled == mSize)
                this->extendTab(1);

            mTab[mFilled] = e;

            mFilled++;
        }

        void prepend(T e){
            //Si nécessaire on augmente la taille du tableau
            if(mFilled == mSize)
                this->extendTab(1);

            //On décale tous les éléments du tableau
            this->offset(0, 1);

            //On met le nouveau à l'index 0
            this->mTab[0] = e;
            mFilled++;
        }

        T operator[] (int i) const{
            if(this->mFilled == 0)
                throw EmptyContainerException();

            if(i < 0 || this->mFilled <= i)
                throw IndexOutOfBoundsException();

            return this->mTab[i];
        }

        T& operator[] (int i){
            if(this->mFilled == 0)
                throw EmptyContainerException();

            if(i < 0 || this->mFilled <= i)
                throw IndexOutOfBoundsException();

            return this->mTab[i];
        }

        bool hasNext() const{
            return this->mCursor+1 < this->mFilled;
        }

        T next() const{
            if(hasNext()){
                mCursor++;
                return this->mTab[this->mCursor];
            }
            
            if(this->mFilled == 0)
                throw EmptyContainerException();

            throw IndexOutOfBoundsException();
        }

        T first() const{
            if(this->mFilled == 0)
               throw EmptyContainerException();

            mCursor = -1;
            return this->mTab[mCursor+1];
        }        

        T last() const{
            if(this->mFilled == 0)
                throw EmptyContainerException();


            return this->mTab[this->mFilled-1];
        }

        void remove(T e){
            int i = this->pos(e);
            this->backOffset(i, 1);
            mFilled--;
        }
        
};

#endif
