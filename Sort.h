# include <iostream>
# include "FileIO.h"

using namespace std;

class Sort {
    public:
        Sort();
        Sort(string name);
        ~Sort();

        void setArr(FileIO f);

        // functions needed for quick sort
        void QSort(double* arr, int lowIdx, int highIdx);
        int partition(double* arr, int lowIdx, int highIdx);

        // functions needed for merge sort
        void MSort(int l, int r);
        void merge(int l, int m, int r);

        // functions needed for selection sort
        void SSort();

        // functions needed for insertion sort
        void ISort();

        // functions needed for bubble sort
        void BSort();

        void start();

        // swap content not pointers
        void swap(double* x, double* y);

        // individual arrays for each sorting algorithm
        double* QSArr;
        double* MSArr;
        double* SSArr;
        double* ISArr;
        double* BSArr;

        int arraySize;
};
