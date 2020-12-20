# include <iostream>
# include "Sort.h"
# include <ctime>


using namespace std;

// default constructor
Sort::Sort(){
    arraySize = 0;
}

// overloaded constructor, passed in file name
Sort::Sort(string name){
    // create FileIO object to begin
    FileIO file = FileIO(name);
    // get array size
    arraySize = file.getSumLines();

    // copy content from original array to individual arrays
    setArr(file);

    // start sorting
    start();
}

Sort::~Sort(){
    delete QSArr;
    delete MSArr;
    delete SSArr;
    delete ISArr;
    delete BSArr;
}

void Sort::setArr(FileIO f){
    // copy content from original array to individual arrays
    QSArr = new double[arraySize];
    MSArr = new double[arraySize];
    SSArr = new double[arraySize];
    ISArr = new double[arraySize];
    BSArr = new double[arraySize];

    cout << endl << "Original list: ";

    for(int i = 0; i < arraySize; ++i){
        double temp = f.getLine();
        QSArr[i] = temp;
        MSArr[i] = temp;
        SSArr[i] = temp;
        ISArr[i] = temp;
        BSArr[i] = temp;
        cout << temp << " ";
    }
    cout << endl;
    cout << endl;
}

// start sorting
void Sort::start(){
    double time = 0.0;

    clock_t begin;

    // quick sort
    begin = clock();
    QSort(QSArr, 0, arraySize - 1);
    begin = clock() - begin;
    time = (double)begin/(double)CLOCKS_PER_SEC;
    cout << "Time for quick sort: " << time * 1000000000 << "ns." << endl << "- ";
    for(int i = 0; i < arraySize; ++i){
        cout << QSArr[i] << " ";
    }
    cout << endl;

    // merge sort
    begin = clock();
    MSort(0, arraySize - 1);
    begin = clock() - begin;
    time = (double)begin/(double)CLOCKS_PER_SEC;
    cout << "Time for merge sort: " << time * 1000000000 << "ns." << endl << "- ";
    for(int i = 0; i < arraySize; ++i){
        cout << MSArr[i] << " ";
    }
    cout << endl;

    // selection sort
    begin = clock();
    SSort();
    begin = clock() - begin;
    time = (double)begin/(double)CLOCKS_PER_SEC;
    cout << "Time for selection sort: " << time * 1000000000 << "ns." << endl << "- ";
    for(int i = 0; i < arraySize; ++i){
        cout << SSArr[i] << " ";
    }
    cout << endl;

    // insertion sort
    begin = clock();
    ISort();
    begin = clock() - begin;
    time = (double)begin/(double)CLOCKS_PER_SEC;
    cout << "Time for insertion sort: " << time * 1000000000 << "ns." << endl << "- ";
    for(int i = 0; i < arraySize; ++i){
        cout << ISArr[i] << " ";
    }
    cout << endl;

    // bubble sort
    begin = clock();
    BSort();
    begin = clock() - begin;
    time = (double)begin/(double)CLOCKS_PER_SEC;
    cout << "Time for bubble sort: " << time * 1000000000 << "ns." << endl << "- ";
    for(int i = 0; i < arraySize; ++i){
        cout << BSArr[i] << " ";
    }
    cout << endl << endl;
}

// partition function used for quick sort, passed in array pointer, low index and high index
int Sort::partition(double* arr, int lowIdx, int highIdx){
    // pick pivot
    double pivot = arr[highIdx];

    int i = lowIdx - 1;

    // for loop to swap if pivot is larger
    for(int j = lowIdx; j <= highIdx - 1; ++j){
        if(arr[j] <= pivot){
            ++i;
            swap(&arr[i], &arr[j]);
        }
    }
    // final swap to get index of lowest value
    swap(&arr[i + 1], &arr[highIdx]);

    return i + 1;
}

// quick sort
void Sort::QSort(double* arr, int lowIdx, int highIdx){
    if(lowIdx >= highIdx){
        return;
    }

    int lowEndIdx = partition(arr, lowIdx, highIdx);

    // lower values
    QSort(arr, lowIdx, lowEndIdx - 1);
    // higher values
    QSort(arr, lowEndIdx + 1, highIdx);
}

// merge sort
void Sort::MSort(int l, int r){
    if(r > l){
        // middle index
        int m = l + (r - l)/2;

        // left half
        MSort(l, m);
        // right half
        MSort(m + 1, r);

        // combine back to merge sort array
        merge(l, m, r);
    }
}

// merge function for merge sort
void Sort::merge(int l, int m, int r){
    // how many valid index on the left
    int left = m - l + 1;
    // how many valid index on the right
    int right = r - m;

    // create temp arrays for left and right
    double leftArr[left], rightArr[right];

    // copy for the left
    for (int i = 0; i < left; ++i){
        leftArr[i] = MSArr[l + i];
    }
    // copy for the right
    for (int i = 0; i < right; ++i){
        rightArr[i] = MSArr[m + 1 + i];
    }

    // setting index for both new array and merge sort array
    int leftIdx = 0;
    int rightIdx = 0;
    int msIdx = l;

    // check for both left array and right array
    while(leftIdx < left && rightIdx < right){
        // merging to merge sort array from left array
        if(leftArr[leftIdx] <= rightArr[rightIdx]){
            MSArr[msIdx++] = leftArr[leftIdx++];
        }
        // merging to merge sort array from right array
        else{
            MSArr[msIdx++] = rightArr[rightIdx++];
        }
    }

    // check what is left from left array
    while(leftIdx < left){
        MSArr[msIdx++] = leftArr[leftIdx++];
    }
    // check what is left from right array
    while(rightIdx < right){
        MSArr[msIdx++] = rightArr[rightIdx++];
    }
}

// selection sort
void Sort::SSort(){
    // smalles value
    int minIdx = 0;

    // for loop to iterate over the array to find and replace the smallest value in order
    for(int i = 0; i < arraySize - 1; ++i){
        minIdx = i;
        for(int j = i + 1; j < arraySize; ++j){
            if(SSArr[minIdx] > SSArr[j]){
                minIdx = j;
            }
        }
        swap(&SSArr[minIdx], &SSArr[i]);
    }
}

// insertion sort
void Sort::ISort(){
    int j = 0;
    for(int i = 1; i < arraySize; ++i){
        j = i;
        while(j > 0 && ISArr[j] < ISArr[j - 1]){
            swap(&ISArr[j], &ISArr[j - 1]);
            --j;
        }
    }
}

// bubble sort
void Sort::BSort(){
    for(int i = 0; i < arraySize; ++i){
        for(int j = 0; j < arraySize - 1; ++j){
            // not in order
            if(BSArr[j] > BSArr[j + 1]){
                swap(&BSArr[j], &BSArr[j + 1]);
            }
        }
    }
}

// swap values not pointers
void Sort::swap(double* x, double* y){
    double temp = *x;
    *x = *y;
    *y = temp;
}
