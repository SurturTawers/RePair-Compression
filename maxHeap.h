#ifndef UNTITLED_MAXHEAP_H
#define UNTITLED_MAXHEAP_H
#include <algorithm>
#include <vector>
typedef struct{
    int frec;
    std::pair<int,int> par;
}nodoHeap;
class maxHeap{
public:
    maxHeap();
    ~maxHeap();
    void insert(std::pair<int,int>,int);
    std::pair<std::vector<nodoHeap>::iterator,std::vector<nodoHeap>::iterator> getLimits();
    nodoHeap getMax();
    std::pair<int,int> modVal(nodoHeap*,int);
    void popMax();
    std::pair<int,int> maxHeap::erase(nodoHeap* );
private:
    std::vector<nodoHeap> heap;
    void downHeap(std::vector<nodoHeap>::iterator ,int);
    void upHeap(std::vector<nodoHeap>::iterator,int);
};
#endif //UNTITLED_MAXHEAP_H
