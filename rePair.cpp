#include "rePair.h"
using namespace std;
rePair::rePair(){
    lisDob=new listaDoble();
}
rePair::~rePair(){
    delete lisDob;
}
vector<int> rePair::control(vector<int>& secuencia){
    //UNICO METODO ACCESIBLE POR EL USUARIO
    if(secuencia.size()>1){
        datos(secuencia);
        return comprimir();
    }else if(secuencia.size()==1){
        cout<<"el vector tiene un solo elemento"<<endl;
    }
}
void rePair::datos(vector<int>& secuencia){
    //INSERTA LOS ELEMENTOS EN LA LISTA ENLAZADA
    sec=&secuencia;
    int maximo=0;
    if(secuencia.empty()==false){
        for(vector<int>::iterator it=secuencia.begin(); it!=secuencia.end();it++){
            if(*it>maximo){
                maximo=*it;
            }
            lisDob->insert(*it);
        }
        sigma=maximo+1;
    }else{
        cout<<"El vector esta vacio"<<endl;
    }
}
vector<int> rePair::comprimir(){
    //COMPRIME LA SECUENCIA
    Nodo* iter;
    Nodo* tail;
    map<pair<int,int>,int>::iterator it= mapear();
    while(it!=mapa.end()){//ITERA POR EL MAP
        //cout<<"Comprimiendo... "<<get<0>(it->first)<<" "<<get<1>(it->first)<<" -> "<<sigma<<endl;
        iter=lisDob->getHead();
        tail=lisDob->getTail();
        pair<int,int> parComp;
        while(iter->siguiente!=tail && iter!=tail){//ITERA POR LA LISTA ENLAZADA
            parComp=make_pair(iter->dato,iter->siguiente->dato);//ARMA LOS PARES DE LA LISTA
            if(parComp==it->first){//SI EL PAR ARMADO ES EL MISMO QUE EL PAR A COMPRIMIR
                iter->dato=sigma;//ACTUALIZA EL PRIMER NUMERO DEL PAR
                lisDob->removerNodo(iter->siguiente);//QUITA DE LA LISTA EL SEGUNDO NUMERO DEL PAR
            }
            iter=iter->siguiente;
        }
        if(iter!=tail){//SI LLEGO AL PENULTIMO ELEMENTO
            parComp=make_pair(iter->dato,iter->siguiente->dato);
            if(parComp==it->first){//SI ES EL PAR A COMPRIMIR
                iter->dato=sigma;
                lisDob->removerNodo(iter->siguiente);
            }
        }
        mapa.clear();
        it=mapear();
        sigma++;

    }
    //CUANDO TERMINA LA COMPRESION, HAGO LA SECUENCIA COMPRIMIDA
    sec_rP.clear();
    iter=lisDob->getHead();
    tail=lisDob->getTail();
    while(iter!=tail){
        sec_rP.push_back(iter->dato);
        iter=iter->siguiente;
    }
    sec_rP.push_back(iter->dato);
    return sec_rP;
}
map<pair<int,int>,int>::iterator rePair::mapear(){
    //ACTUALIZA EL MAP
    Nodo* iter=lisDob->getHead();
    Nodo* tail=lisDob->getTail();
    Nodo* head=lisDob->getHead();
    pair<int,int> parAux;
    map<pair<int,int>,int>::iterator it,aux;
    int a,b,max=0,consecutivo=1;
    while(iter->siguiente!=tail && iter!=tail){//ITERO POR LA LISTA DOBLE
        a=iter->dato;
        b=iter->siguiente->dato;
        par=make_pair(a,b);//PAR A MAPEAR
        it=mapa.find(par);//BUSCO EL PAR EN EL MAPA
        if(iter!=head){//SI NO ES EL PRIMER ELEMENTO
            parAux=make_pair(iter->anterior->dato,iter->dato);//PAR ANTERIOR AL A MAPEAR
            if(parAux==par && consecutivo==1){//VERIFICO SI EL PAR ANTERIOR ES EL MISMO Y CONSECUTIVO
                consecutivo=0;//EL PROXIMO PAR YA NO SERA CONSECUTIVO
            }else if(parAux!=par || consecutivo==0){//SI EL PAR ANTERIOR ES DISTINTO O NO ES CONSECUTIVO
                consecutivo=1;//EL PROXIMO PAR PUEDE SER CONESCUTIVO
            }
        }
        if(it!=mapa.end() && consecutivo==1){//SI SE ENCUENTRA EL PAR EN EL MAPA Y "ES CONSECUTIVO"
            //ENTRA DESPUES DE CAMBIAR DE CONSECUTIVO=0 A CONSECUTIVO=1 (2 ITERACIONES)
            it->second++;//
        }else{
            //SI NO LO ENCUENTRA O NO ES CONESCUTIVO LO INSERTA EN EL MAPA
            mapa.insert(make_pair(par,1));
        }
        iter=iter->siguiente;
    }
    //HAGO EL MAP DEL ULTIMO PAR
    if(iter!=tail){
        a=iter->dato;
        b=iter->siguiente->dato;
        par=make_pair(a,b);
        it=mapa.find(par);
        parAux=make_pair(iter->anterior->dato,iter->dato);
        if(parAux==par && consecutivo==1){
            consecutivo=0;
        }else if(parAux!=par || consecutivo==0){
            consecutivo=1;
        }
        if(it!=mapa.end() && consecutivo==1){
            it->second++;
        }else{
            mapa.insert(make_pair(par,1));
        }
    }
    //BUSCO EL PAR DE MAYOR FRECUENCIA EN EL MAP
    iter=lisDob->getHead();
    tail=lisDob->getTail();
    pair<int,int> parComp;
    while(iter->siguiente!=tail){//ITERO POR LA LISTA
        it=mapa.begin();
        parComp=make_pair(iter->dato,iter->siguiente->dato);//PAR A OBSERVAR
        while(it!=mapa.end()){//ITERA POR EL MAP
            if(parComp==it->first && it->second>1 && it->second>max){
                //SI SE ENCUENTRA EL PAR A OBSERVAR EN EL MAP, SU FRECUENCIA ES MAYOR A UNO
                //Y SI SU FRECUENCIA ES MAYOR A LA MAXIMA FRECUENCIA OBTENIDA;
                aux=it;//GUARDO EL ITERADOR DEL ELEMENTO
                max=it->second;//ALMACENO SU VALOR DE FRECUENCIA
            }
            it++;
        }
        iter=iter->siguiente;
    }
    if(max==0){//SI NO SE ENCONTRO PAR CON FRECUENCIA MAYOR A 1
        return mapa.end(); //RETORNA EL FIN DEL MAP
    }
    return aux;//SI SE ENCONTRO MAYOR RETORNO SU ITERADOR
}