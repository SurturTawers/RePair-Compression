#include "maxHeap.h"
#include <iostream>
using namespace std;
maxHeap::maxHeap() {
    heap.push_back({0,make_pair(0,0)});
}
maxHeap::~maxHeap() {
    heap.clear();
}
void maxHeap::insert(pair<int,int> par, int f){
    //INSERTA UN ELEMENTO EN EL HEAP
    heap.push_back({f,par});
    if(heap.size()-1>1) {
        //SI HAY MAS DE UNO INSERTADO, ORDENO.
        //LE ENVIO LA POSICION DEL ULTIMO INSERTADO Y EL INDICE DEL PADRE
        upHeap(heap.end() - 1, (heap.size() - 1) / 2);
    }
}
void maxHeap::upHeap(vector<nodoHeap>::iterator nodo,int ind) {
    //ORDENA EL MAX HEAP POR FRECUENCIA MAYOR
    vector<nodoHeap>::iterator cambio=heap.begin()+ind;//NODO PADRE
    nodoHeap aux;
    if(ind==0){
        return;
    }
    if(cambio->frec<nodo->frec){
        //SI EL PADRE ES MENOR QUE EL HIJO, LOS INTERCAMBIO
        aux=*cambio;
        *cambio=*nodo;
        *nodo=aux;
        upHeap(cambio,(ind/2));//REVISO EL PADRE DEL PADRE
    }
}
void maxHeap::downHeap(vector<nodoHeap>::iterator nodo,int ind){
    //ORDENA EL HEAP
    nodoHeap aux;
    if(ind*2<=heap.size()-1){//SI TIENE HIJO IZQUIERDO
        vector<nodoHeap>::iterator cambioIzq=heap.begin()+(ind*2);
        if(nodo->frec<cambioIzq->frec){
            //VERIFICO SI EL HIJO IZQUIERDO ES MAYOR,
            //Y LOS INTERCAMBIO SI ES MAYOR
            aux=*nodo;
            *nodo=*cambioIzq;
            *cambioIzq=aux;
        }
        downHeap(cambioIzq,ind*2);//BAJO AL HIJO IZQUIERDO
    }
    if((ind*2)+1<=heap.size()-1){//SI TIENE HIJO DERECHO
        vector<nodoHeap>::iterator cambioDer=heap.begin()+(ind*2)+1;
        if(nodo->frec<cambioDer->frec){
            //INTERCAMBIO SI EL HIJO ES MAYOR QUE EL PADRE
            aux=*nodo;
            *nodo=*cambioDer;
            *cambioDer=aux;
        }
        downHeap(cambioDer,(ind*2)+1);//BAJO AL HIJO DERECHO
    }
}
pair<int,int> maxHeap::erase(nodoHeap* elim){
    //ELIMINA UN NODO DEL HEAP
    nodoHeap aux=*(heap.end()-1);
    if(&(*elim)!=&(*(heap.end()-1))){//SI EL NODO A ELIMINAR NO ES EL ULTIMO ELEMENTO DEL HEAP
        //INTERCAMBIO CON EL ULTIMO ELEMENTO
        *(heap.end()-1)=*elim;
        *elim=aux;
    }
    heap.pop_back();//ELIMINO EL ELEMENTO FINAL
    return elim->par; //RETORNO EL PAR POR EL QUE INTERCAMBIE EL NOD A ELIMINAR
}
pair<int,int> maxHeap::modVal(nodoHeap* mod,int f){
    //MODIFICA EL VALOR DE LA FRECUENCIA DE UN NODO
    if(f==1 && (heap.size()-1)>1){//SI LA FRECUENCIA ES 1 Y HAY MAS DE UN ELEMENTO EN EL HEAP
        //INTERCAMBIO CON EL FINAL
        nodoHeap aux=*(heap.end()-1);
        *(heap.end()-1)=*mod;
        *mod=aux;
        heap.pop_back();//ELIMINO EL FINAL
        return mod->par;//RETORNO EL PAR POR EL QUE INTERCAMBIE
    }else if((heap.size()-1)>0){//SI LA FRECUENCIA ES MAYOR A 1 Y HAY MAS DE UN ELEMENTO
        mod->frec-=1;//LE RESTO A LA FRECUENCIA
        return mod->par;//DEVUELVO EL MISMO PAR
    }
}
pair<vector<nodoHeap>::iterator,vector<nodoHeap>::iterator> maxHeap::getLimits(){
    //RETORNA EL ITERADOR AL PRIMER ELEMENTO REAL DEL HEAP, Y AL FINAL DEL HEAP
    return make_pair(heap.begin()+1,heap.end());
}
void maxHeap::popMax(){
    //QUITA EL MAXIMO ELEMENTO DEL HEAP
    if(heap.size()-1>0){
        heap.erase(heap.begin()+1);
        downHeap(heap.begin()+1,1);//ORDENA EL HEAP
    }
}
nodoHeap maxHeap::getMax(){
    //RETORNA EL ELEMENTO MAXIMO DEL HEAP
    nodoHeap aux=*(heap.begin()+1);
    return aux;
}