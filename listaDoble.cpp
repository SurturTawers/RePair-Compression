#include "listaDoble.h"
using namespace std;
listaDoble::listaDoble(){
}
listaDoble::~listaDoble(){
    Nodo* iter=head;
    Nodo* next=iter->siguiente;
    while(next!=tail){
        free(iter);
        iter=next;
        next=iter->siguiente;
    }
    free(iter);
    free(next);
}
void listaDoble::insert(int dato){
    //INSERTA LOS ELEMENTOS EN LA LISTA
    if(head==NULL){
        insertFirst(dato);//INSERTA EL PRIMERO
    }else{
        insert(tail,dato);
    }
}
void listaDoble::insertFirst(int dato){
    //INSERTA EL PRIMER ELEMENTO DE LA LISTA
    Nodo* nuevoNodo=(Nodo*)malloc(sizeof(Nodo));
    head=nuevoNodo;
    tail=head;
    nuevoNodo->anterior=NULL;
    nuevoNodo->dato=dato;
    nuevoNodo->siguiente=NULL;
}
void listaDoble::insert(Nodo* anterior, int dato){
    //INSERTA UN NODO EN LA LISTA
    Nodo* nuevoNodo=(Nodo*)malloc(sizeof(Nodo));
    nuevoNodo->anterior=anterior;
    anterior->siguiente=nuevoNodo;
    nuevoNodo->dato=dato;
    nuevoNodo->siguiente=NULL;
    tail=nuevoNodo;
}
void listaDoble::removerNodo(Nodo* nodo){
    //QUITA UN NODO DE LA LISTA Y ACTUALIZA LOS PUNTEROS DE SUS VECINOS
    if(nodo==tail){
        tail=nodo->anterior;
        nodo->anterior->siguiente=NULL;
    }else{
        nodo->anterior->siguiente=nodo->siguiente;
        nodo->siguiente->anterior=nodo->anterior;
    }
    free(nodo);
}
Nodo* listaDoble::getHead(){
    //DEVUELVE LA CABEZA DE LA LISTA
    return head;
}
Nodo* listaDoble::getTail(){
    //DEVUELVE LA COLA DE LA LISTA
    return tail;
}