#include <iostream>
#include <vector>
#include "merge.h"
using namespace std;

int main(){
    vector<int> test1 = {13,7,14,21,37,2,5};
    printArray(test1);
    mergeSort(test1,0,test1.size()-1);
    printArray(test1);
    return 0;
}