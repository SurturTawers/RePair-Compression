#ifndef UNTITLED_REPAIR_H
#define UNTITLED_REPAIR_H
#include "listaDoble.h"
#include <vector>
#include <map>
#include <iostream>
class rePair{
public:
    rePair();
    ~rePair();
    std::vector<int> control(std::vector<int>&);
private:
    int sigma=28;
    listaDoble* lisDob;
    std::vector<int> *sec;
    std::vector<int> sec_rP;
    std::pair<int,int> par;
    std::map<std::pair<int,int>,int> mapa;
    std::vector<int> comprimir();
    void datos(std::vector<int>&);
    std::map<std::pair<int,int>,int>::iterator mapear();
};
#endif //UNTITLED_REPAIR_H
