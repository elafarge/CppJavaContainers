#include <iostream>

#include "list.hpp"
#include "vector.hpp"
#include "linkedlist.hpp"

using namespace std;

int main(int argc, char** argv){
    
    /////// TEST DU TYPE LinkedList ///////

    List<int>* v = new LinkedList<int>(); //Création d'une liste (remarquez au passage l'utilisation du polymorphisme)

    //Ajout d'éléments en début et en fin de liste
    for(int i = 1; i < 10; i++){
        v->append(i);
        v->prepend(-i);
    }
    (*v)[0] = 77; //Modification d'un élément à l'aide de l'opérateur []

    cout << *v << endl; //Affichage (et donc preuve que les méthodes first(), hasNext() et next() fonctionnent comme prévu)

    try{
        cout << v->pos(2) << endl;
        cout << v->pos(12) << endl; //Va renvoyer une ElementNotFoundException
    }catch(ElementNotFoundException<int> e){
        cout << e.what() << endl;
    }

    try{
        cout << (*v)[128] << endl; //Va renvoyer une IndexOutOfBoundsException
    }
    catch(IndexOutOfBoundsException e){
        cout << e.what() << endl;
    }

    cout << v->last() << endl;

    try{
        v->remove(5);
        v->remove(13);
        v->remove(7); // Ne sera pas exécuté car la ligne au dessus lance une exception
    }catch(ElementNotFoundException<int> e){
        cout << e.what() << endl;
    }

    cout << *v << endl;

    delete v; //Libération de la mémoire

    v = new Vector<int>(); //Création d'une liste (remarquez au passage l'utilisation du polymorphisme)

    //Ajout d'éléments en début et en fin de liste
    for(int i = 1; i < 10; i++){
        v->append(i);
        v->prepend(-i);
    }
    (*v)[0] = 77; //Modification d'un élément à l'aide de l'opérateur []

    cout << *v << endl; //Affichage (et donc preuve que les méthodes first(), hasNext() et next() fonctionnent comme prévu)

    try{
        cout << v->pos(2) << endl;
        cout << v->pos(12) << endl; //Va renvoyer une ElementNotFoundException
    }catch(ElementNotFoundException<int> e){
        cout << e.what() << endl;
    }

    try{
        cout << (*v)[128] << endl; //Va renvoyer une IndexOutOfBoundsException
    }
    catch(IndexOutOfBoundsException e){
        cout << e.what() << endl;
    }

    cout << v->last() << endl;

    try{
        v->remove(5);
        v->remove(13);
        v->remove(7); // Ne sera pas exécuté car la ligne au dessus lance une exception
    }catch(ElementNotFoundException<int> e){
        cout << e.what() << endl;
    }

    cout << *v << endl;

    delete v; //Libération de la mémoire

    return 0;
}
