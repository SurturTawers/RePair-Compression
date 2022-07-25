#include "rePairAvanzado.h"
using namespace std;
rePairAvanzado::rePairAvanzado(){
    lisDobAv=new listaDobleAvanzada();
    mH=new maxHeap();
}
rePairAvanzado::~rePairAvanzado(){
    delete lisDobAv;
    delete mH;
}
vector<int> rePairAvanzado::control(vector<int>& secuencia){
    //UNICO METODO ACCESIBLE POR EL USUARIO
    if(secuencia.size()>1){
        datos(secuencia);
        return comprimir();
    }else if(secuencia.size()==1){
        cout<<"el vector tiene un solo elemento"<<endl;
    }
}
void rePairAvanzado::datos(vector<int>& secuencia){
    //INICIALIZA LA LISTA DOBLEMENTE ENLAZADA
    int maximo=0;
    if(secuencia.empty()==false) {
        for (vector<int>::iterator it = secuencia.begin(); it != secuencia.end(); it++) {
            if(*it>maximo){
                maximo=*it;
            }
            lisDobAv->insertAv(*it);
        }
        sigma=maximo+1;
        lisDobAv->setAp();
        mapear();
        setPos();
    }else{
        cout<<"El vector esta vacio"<<endl;
    }
}
vector<int> rePairAvanzado::comprimir(){
    //COMPRIME LA SECUENCIA
    nodoHeap max;
    NodoAvanzado* iter;
    NodoAvanzado* tail;
    map<pair<int,int>,Node>::iterator it,eliminar,swap;
    max=mH->getMax();//OBTIENE EL MAXIMO EN EL HEAP
    while(max.frec>1){
        max=mH->getMax();
        //Compresion;
        it=mapa.find(max.par);//BUSCA EN EL MAP SI ES QUE EXISTE EL PAR MAXIMO
        if(it!=mapa.end()){//SI LO ENCUENTRA
            //cout<<"Comprimiendo..."<<get<0>(it->first)<<" "<<get<1>(it->first)<<" -> "<<sigma<<endl;
            iter=it->second.primAp;
            while(iter->apSig!=NULL){
                //SE ITERA EN LA LISTA ENLAZADA
                // DESDE LA PRIMERA APARICION DEL PAR HASTA LA ULTIMA
                modVal(iter);
                iter->dato=sigma;//CAMBIA EL PRIMER ELEMENTO DEL PAR POR SIGMA>27
                lisDobAv->removerNodoAv(iter->siguiente);//ELIMINA EL SEGUNDO ELEMENTO DEL PAR
                iter=iter->apSig;
            }
            modVal(iter);
            iter->dato=sigma;
            sigma++;
            lisDobAv->removerNodoAv(iter->siguiente);
            if(get<1>(max.par)!=0){
                //REVISA SI ES QUE EL PAR MAXIMO NO POSEE UN CERO EN EL SEGUNDO ELEMENTO DEL PAR
                //(EL CERO REPRESENTA QUE ESTOS PARES SON CONSECUTIVOS)
                //EJ: 3 3 3 2 3 3 => DE 3 3 3 SE ALMACENA EL PRIMER PAR COMO 3 3 EN EL MAP Y HEAP
                //Y EL SEGUNDO PAR 3 3 SE ALMACENA COMO 3 0 EN EL MAP Y HEAP.
                //BUSCA SI ES QUE EXISTE  EL PAR CON CERO EN EL MAPA
                eliminar=mapa.find(make_pair(get<1>(max.par),0));
                if(eliminar!=mapa.end()){
                    //BORRO DEL HEAP HACIENDO UN SWAP ENTRE EL NODO A BORRAR Y EL ULTIMO
                    //ELEMENTO DEL HEAP, RETORNANDO EL PAR INTERCAMBIADO Y ACTUALIZANDO SU POSICION
                    //Y LUEGO BORRA EN EL MAP.
                    swap=mapa.find(mH->erase(eliminar->second.pos));
                    swap->second.pos=eliminar->second.pos;
                    mapa.erase(eliminar);
                }
            }else{
                //SI TIENE UN CERO HACE LO MISMO A LO ANTERIOR PERO BUSCA EL PAR SIN EL CERO
                //ELIMINA DE LA MISMA MANERA
                eliminar=mapa.find(make_pair(get<0>(max.par),get<0>(max.par)));
                if(eliminar!=mapa.end()){
                    //BORRO DEL HEAP Y EL MAP
                    swap=mapa.find(mH->erase(eliminar->second.pos));
                    swap->second.pos=eliminar->second.pos;
                    mapa.erase(eliminar);
                }
            }
            //AL CAMBIAR TODOS LOS ELEMENTOS DE LA LISTA
            lisDobAv->setAp();//ACTUALIZO LAS APARICIONES DE LOS PARES
            mH->popMax();//RETIRO EL MAXIMO DEL HEAP
            mapear();//ACTUALIZO LOS PUNTEROS DEL MAP
            setPos();//ACTUALIZO LAS POSICIONES DEL HEAP EN EL MAP
            max=mH->getMax();
        }
    }
    //AL TERMINAR DE COMPRIMIR(CUANDO YA NO HAY UN MAXIMO CON FRECUENCIA MAYOR A 1)
    iter=lisDobAv->getHeadAv();
    tail=lisDobAv->getTailAv();
    sec_rPA.clear();
    while(iter!=tail){
        //GUARDO LA SECUENCIA RESULTANTE EN UN VECTOR
        sec_rPA.push_back(iter->dato);
        iter=iter->siguiente;
    }
    sec_rPA.push_back(iter->dato);
    return sec_rPA;
}
void rePairAvanzado::modVal(NodoAvanzado* iter){
    //MODIFICA LOS VALORES EN EL HEAP Y EL MAP
    //RECIBE EL PUNTERO AL PAR QUE SE ESTA COMPRIMIENDO ACTUALMENTE
    //ACTUALIZO LOS VALORES DE LOS PARES ANTERIOR Y SIGUIENTE AL PAR QUE SE ESTA COMPRIMIENDO
    map<pair<int,int>,Node>::iterator itAux,aux;
    if(iter!=lisDobAv->getHeadAv()){
        //HAGO EL PAR ANTERIOR Y LOS BUSCO EN EL MAP
        pair<int,int> parAnt=make_pair(iter->anterior->dato,iter->dato);
        itAux=mapa.find(parAnt);
        if(itAux!=mapa.end()){
            //SI LO ENCUENTRA MODIFICA SU VALOR DE FRECUENCIA, SI ES 1 LO BORRA DEL HEAP
            //MODVAL RETORNA UN PAR: ESTE PUEDE SER EL MISMO PAR QUE SE ENVIO
            //O EN EL CASO DE QUE SE ELIMINE UN PAR EN EL HEAP, DEVUELVE EL PAR POR
            //EL QUE SE INTERCAMBIO.
            aux=mapa.find(mH->modVal(itAux->second.pos,itAux->second.f));
            if(itAux->second.f==1 && aux!=mapa.end()){
                //SI FRECUENCIA ES 1, AL DECREMENTAR ES CERO, LUEGO LO BORRA DEL MAP
                aux->second.pos=itAux->second.pos;
                mapa.erase(itAux->first);
            }else{
                itAux->second.f-=1;
            }
        }
    }
    if(iter->siguiente!=lisDobAv->getTailAv() && iter!=lisDobAv->getTailAv()){
        //LO MISMO QUE EL ANTERIOR PERO CON EL PAR SIGUIENTE AL PAR COMPRIMIENDOSE
        pair<int,int> parSig=make_pair(iter->siguiente->dato,iter->siguiente->siguiente->dato);
        itAux=mapa.find(parSig);
        if(itAux!=mapa.end()){
            aux=mapa.find(mH->modVal(itAux->second.pos,itAux->second.f));
            if(itAux->second.f==1 && aux!=mapa.end()){
                aux->second.pos=itAux->second.pos;
                mapa.erase(itAux->first);
            }else{
                itAux->second.f-=1;
            }
        }
    }
}
void rePairAvanzado::setPos(){
    //ACTUALIZA EN EL MAP, LAS POSICIONES DE LOS PARES EN EL HEAP
    vector<nodoHeap>::iterator itPos,end;
    map<pair<int,int>,Node>::iterator it;
    pair<vector<nodoHeap>::iterator,vector<nodoHeap>::iterator> limites;
    limites=mH->getLimits();//ME RETORNA EL HEAD+1 Y EL END DEL HEAP
    end=get<1>(limites);
    for(itPos=get<0>(limites);itPos!=end;itPos++){
        it=mapa.find(itPos->par);//BUSCA EL PAR DEL HEAP EN EL MAP
        it->second.pos=&(*itPos);//GUARDO LA DIRECCION DE MEMORIA DE ESE PAR
    }
}
void rePairAvanzado::mapear(){
    //CREA Y ACTUALIZA EL MAP
    Node* nodo=(Node*)malloc(sizeof(Node));
    map<pair<int,int>,Node>::iterator it;
    NodoAvanzado* iterSig;//ITERA POR LA LISTA BUSCANDO LA PRIMERA APARICION
    NodoAvanzado* iterAnt;//ITERA POR LA LISTA BUSCANDO LA ULTIMA APARICION
    NodoAvanzado* pivote=lisDobAv->getHeadAv();
    NodoAvanzado* tail=lisDobAv->getTailAv();
    NodoAvanzado* auxAnt;
    NodoAvanzado* auxSig;
    pair<int,int> par;
    int count;
    while(pivote!=tail){
        //ITERO POR LA LISTA ENLAZADA
        count=1;
        iterAnt=pivote;
        iterSig=pivote;
        auxAnt=pivote;
        auxSig=pivote;
        while(iterAnt->apAnt!=NULL || iterSig->apSig!=NULL){
            //ITERO HASTA ENCONTRAR LA PRIMERA Y ULTIMA APARICION DEL PAR
            if(iterAnt->apAnt==NULL){
                auxAnt=iterAnt;
            }else if(iterAnt->apAnt!=NULL){
                //SI NO ES LA ULTIMA SIGUE ITERANDO
                iterAnt=iterAnt->apAnt;
                count++;
            }
            if(iterSig->apSig==NULL){
                auxSig=iterSig;
            }if(iterSig->apSig!=NULL){
                iterSig=iterSig->apSig;
                count++;
            }
        }
        //COMPRUEBO SI EFECTIVAMENTE LLEGO A LA PRIMERA Y ULTIMA APARICION
        if(iterSig->apSig==NULL){
            auxSig=iterSig;
        }
        if(iterAnt->apAnt==NULL){
            auxAnt=iterAnt;
        }
        //ACTUALIZO LOS DATOS DEL NODO A INGRESAR AL MAP
        nodo->primAp=auxAnt;
        nodo->ultAp=auxSig;
        nodo->f=count;
        par=make_pair(auxAnt->dato,auxAnt->siguiente->dato);
        it=mapa.find(par);//BUSCO SI ES QUE EL PAR YA EXISTE
        if(it==mapa.end()){
            //SI NO EXISTE LO INSERTO EN EL MAP Y EN EL HEAP
            mapa.insert(make_pair(par,*nodo));
            mH->insert(par,count);
        }else{
            //SI EXISTE ACTUALIZO LOS PUNTEROS DE LAS APARICIONES
            it->second.primAp=auxAnt;
            it->second.ultAp=auxSig;
            if(it->second.primAp!=nodo->primAp){//COMPRUEBO SI ES PAR CONSECUTIVO
                map<pair<int,int>,Node>::iterator a;
                a=mapa.find(make_pair(auxAnt->dato,0));//SI ES CONSECUTIVO VEO SI EXISTE
                if(a==mapa.end()){//SI NO EXISTE LO INSERTO EN EL HEAP Y EN LA MAP
                    mH->insert(make_pair(auxAnt->dato,0),count);
                    mapa.insert(make_pair(make_pair(auxAnt->dato,0),*nodo));
                }
            }
        }
        pivote=pivote->siguiente;
    }
    free(nodo);
}