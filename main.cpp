#include <iostream>
#include <fstream>
#include "rePair.h"
#include "rePairAvanzado.h"
#include <ctime>
#include <vector>
#include <sstream>
using namespace std;
int main(int argc, char* argv[]){
    //PARA INGRESAR LA SECUENCIA DEBE SER UN ARCHIVO DE TEXTO
    //CON LOS NUMEROS EN UNA SOLA LINEA PREFERIBLEMENTE
    //1 22 347 4 51 6 *NOTAR EL ESPACIO*
    //EJECUTAR DE LA FORMA ./programa.out archivo
    int n;
    ifstream sec;
    ofstream secComp;
    double tiempo_rP=0,tiempo_rPA=0;
    clock_t start;
    vector<int> secuencia;
    vector<int> asd;
    vector<int> sec_rP,sec_rPA;
    string input;
    rePair* rP;
    rePairAvanzado* rPA;
    srand((unsigned)time(NULL));
    //MENU
    if(argc!=2){
        cout<<"numero de parametros incorrecto"<<endl;
        return 1;
    }else{
        sec.open(argv[1]);
        if(sec.is_open()){
            while(getline(sec,input)){
                stringstream  linestream(input);
                int numero;
                while(linestream>>numero){
                    secuencia.push_back(numero);
                }
            }
        }else{
            cout<<"No se encontro el archivo"<<endl;
            return 1;
        }
    }
    n=secuencia.size();
    cout<<"Se almacenaran "<<n<<" elementos"<<endl;
    //MEDICION TIEMPO REPAIR
    cout<<"Ejecutando rePair"<<endl;
    rP= new rePair();
    start=clock();
    sec_rP=rP->control(secuencia);
    tiempo_rP+=((double)clock()-start)/CLOCKS_PER_SEC;

    cout<<"Secuencia despues de rePair: ";
    for(int i=0;i<sec_rP.size();i++){
        cout<<sec_rP.at(i)<<" ";
    }
    cout<<endl;

    //MEDICION TIEMPO REPAIR AVANZADO
    cout<<"Ejecutando rePairAvanzado"<<endl;
    rPA= new rePairAvanzado();
    start=clock();
    sec_rPA=rPA->control(secuencia);
    tiempo_rPA+=((double)clock()-start)/CLOCKS_PER_SEC;
    cout<<"Secuencia despues de rePair Avanzado: ";
    for(int i=0;i<sec_rPA.size();i++){
        cout<<sec_rPA.at(i)<<" ";
    }
    cout<<endl;
    secuencia.clear();
    sec_rP.clear();
    sec_rPA.clear();
    delete rP;
    delete rPA;
    sec.close();
    tiempo_rP=(tiempo_rP/(double)1);
    tiempo_rPA=(tiempo_rPA/(double)1);
    cout<<"Tiempo promedio rePair: "<<tiempo_rP<<" [s]"<<endl;
    cout<<"Tiempo promedio rePair Avanzado: "<<tiempo_rPA<<" [s]"<<endl;
    return 0;
}