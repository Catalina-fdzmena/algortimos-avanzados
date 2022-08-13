#ifndef MERGE_H // include guard
#define MERGE_H



void merge(vector<int>&array,int start, int half, int end){
    int i,j,k;
    int elementsLeftSide = half - start + 1;
    int elementsRightSide = end - half;

    vector<int>left(elementsLeftSide);
    vector<int>right(elementsRightSide);

    for(int i = 0; i < elementsLeftSide; i++){
        left[i] = array[start+i];
    }
    for(int j = 0; j < elementsRightSide; j++){
        right[j] = array[half + 1 + j];
    }

    i = 0;
    j = 0;
    k = start;

    while(i < elementsLeftSide && j < elementsRightSide){
        if(left[i] <= right[j]){
            array[k] = left[i];
            i++;
        }else{
            array[k] = right[j];
            j++;
        }
        k++;
    }

    while(j < elementsRightSide){
        array[k] = right[j];
        j++;
        k++;
    }

    while(i < elementsLeftSide){
        array[k] = left[i];
        i++;
        k++;
    }

}

void mergeSort(vector<int>&array,int start, int end){
    if(start < end){
        int half = start + (end - start)/2;
        mergeSort(array,start,half);
        mergeSort(array,half+1,end);
        merge(array,start,half,end);
    }
}

void printArray(vector<int>array){
    for(int i = 0; i < array.size(); i++){
        cout << array[i] << " ";
    }
    cout << endl;
}


#endif
