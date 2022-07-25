#include "listaDobleAvanzada.h"
using namespace std;
listaDobleAvanzada::listaDobleAvanzada(){
}
listaDobleAvanzada::~listaDobleAvanzada(){
    NodoAvanzado* iter=headAv;
    NodoAvanzado* next=iter->siguiente;
    while(next!=tailAv){
        free(iter);
        iter=next;
        next=iter->siguiente;
    }
    free(iter);
    free(next);
}
void listaDobleAvanzada::insertAv(int dato){
    //ACCESOR PARA LA INSERCION DE DATOS
    if(headAv==NULL){//SI ESTA VACIA LA LISTA
        insertFirstAv(dato);//INSERTO EL PRIMERO
    }else{
        insertAv(tailAv,dato);
    }
}
void listaDobleAvanzada::insertAv(NodoAvanzado* anterior,int dato){
    //CREA UN NODO Y LO AÑADE EN LA LISTA ENLAZADA
    NodoAvanzado* nuevoNodo=(NodoAvanzado*)malloc(sizeof(NodoAvanzado));
    nuevoNodo->anterior=anterior;
    anterior->siguiente=nuevoNodo;
    nuevoNodo->dato=dato;
    nuevoNodo->siguiente=NULL;
    tailAv=nuevoNodo;
}
void listaDobleAvanzada::insertFirstAv(int dato){
    //INSERTA EL PRIMER NODO EN LA LISTA
    NodoAvanzado* nuevoNodo=(NodoAvanzado*)malloc(sizeof(NodoAvanzado));
    headAv=nuevoNodo;
    tailAv=headAv;
    nuevoNodo->anterior=NULL;
    nuevoNodo->dato=dato;
    nuevoNodo->siguiente=NULL;
}
void listaDobleAvanzada::removerNodoAv(NodoAvanzado* nodo) {
    //QUITA UN NODO DE LA LISTA Y ACTUALIZA LOS PUNTEROS
    if(nodo==tailAv){
        tailAv=nodo->anterior;
        nodo->anterior->siguiente=NULL;
    }else{
        nodo->anterior->siguiente=nodo->siguiente;
        nodo->siguiente->anterior=nodo->anterior;
    }
    free(nodo);
}
void listaDobleAvanzada::setAp(){
    //ACTUALIZA LOS PUNTEROS A LAS APARICIONES DE LOS PARES EN LA LISTA
    NodoAvanzado* pivote=headAv;
    pair<int,int> par;
    while(pivote->siguiente!=tailAv && pivote!=tailAv){
        //ITERO HASTA EL PENULTIMO ELEMENTO(ULTIMO PAR)
        par=make_pair(pivote->dato,pivote->siguiente->dato);
        setApAnt(par,pivote);//ACTUALIZO SU APARICION ANTERIOR
        setApSig(par,pivote);//ACUALIZO SU SIGUIENTE APARICION
        pivote=pivote->siguiente;
    }
    if(pivote->siguiente==tailAv){
        //SI ES EL PENULTIMO ELEMENTO DE LA LISTA VEO SU APARICION ANTERIOR
        par=make_pair(pivote->dato,pivote->siguiente->dato);
        setApAnt(par,pivote);
    }
    if(pivote==tailAv ){
        //SI ES EL ULTIMO ELEMENTO, NO HAY APARICION SIGUIENTE
        pivote->apSig=NULL;
    }else if(pivote->siguiente==tailAv){
        //SI ES EL PENULTIMO TAMPOCO
        pivote->apSig=NULL;
    }
}
void listaDobleAvanzada::setApAnt(pair<int,int> par,NodoAvanzado* pivote){
    //ACTUALIZA EL PUNTERO A ALA APARICION ANTERIOR DEL PAR
    NodoAvanzado* aux=pivote;
    pair<int,int> parAux;
    pair<int,int> parCons;
    int cons=1;
    while(aux!=headAv && aux->anterior!=headAv){
        //ITERA DESDE EL PAR HASTA EL INICIO DE LA LISTA
        parAux=make_pair(aux->anterior->dato,aux->dato);//PAR OBSERVADO (1)
        parCons=make_pair(aux->dato,aux->siguiente->dato);//PAR SIGUIENTE AL OBSERVADO (2)
        if(parAux==par){//SI EL PAR OBSERVADO ES IGUAL AL PAR A ACTUALIZAR
            if(parAux==parCons && cons==1){
                //SI 1 Y 2 SON PARES CONSECUTIVOS.
                //ESTO SOLO SE CUMPLE SI ES CONSECUTIVO
                //CON EL PAR A ACTUALIZAR
                aux=aux->anterior;
                cons=0;//YA NO ES CONSECUTIVO CON EL PAR A ACTUALIZAR
            }else if(parAux==parCons && cons==0){
                //SI 1 Y 2 SON CONSECUTIVOS PERO NO ES CONSECUTIVO CON EL PAR A ACTUALIZAR
                pivote->apAnt=aux->anterior;//1 ES LA APARICION ANTERIOR
                break;
            }else{
                //SI 1 Y 2 NO SON CONSECUTIVOS
                pivote->apAnt=aux->anterior;
                break;
            }
        }else{
            //SI EL PAR OBSERVADO ES DISTINTO A EL PAR A ACTUALIZAR
            aux=aux->anterior;
        }
    }
    //SI NO SE ENCONTRO NINGUN PAR ANTERIOR
    //EL PAR A ACTUALIZAR ES LA PRIMERA APARICION
    if(aux==headAv){
        pivote->apAnt=NULL;
    }else if(aux->anterior==headAv){
        pivote->apAnt=NULL;
    }
}
void listaDobleAvanzada::setApSig(pair<int,int> par,NodoAvanzado* pivote) {
    //ACTUALIZA EL PUNTERO A ALA APARICION SIGUIENTE DEL PAR
    NodoAvanzado* aux=pivote;
    pair<int,int> parAux;
    pair<int,int> parCons;
    int cons=1;
    while(aux!=tailAv && aux->siguiente!=tailAv){
        //HACE LO MISMO QUE SET_AP_ANT PERO HACIA EL OTRO LADO
        parAux=make_pair(aux->siguiente->dato,aux->siguiente->siguiente->dato);
        parCons=make_pair(aux->dato,aux->siguiente->dato);
        if(parAux==par){
            if(parAux==parCons && cons==1){
                aux=aux->siguiente;
                cons=0;
            }else if(parAux==parCons && cons==0){
                pivote->apSig=aux->siguiente;
                break;
            }else{
                pivote->apSig=aux->siguiente;
                break;
            }
        }else{
            aux=aux->siguiente;
        }
    }
    //SI ESTA EN EL FINAL, EL PAR A ACTUALIZAR ES LA ULTIMA APARICION
    if(aux==tailAv ){
        pivote->apSig=NULL;
    }else if(aux->siguiente==tailAv){
        pivote->apSig=NULL;
    }
}
NodoAvanzado* listaDobleAvanzada::getHeadAv(){
    //RETORNA LA CABEZA DE LA LISTA
    return headAv;
}
NodoAvanzado* listaDobleAvanzada::getTailAv(){
    //RETORNA LA COLA DE LA LISTA
    return tailAv;
}