#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define RANDOM_LIMIT 100
#define RANDOM_OFFSET 0

void printArray(int*, int, int);
int* randomArray(int, int, int);

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    int arraySize, chunkSize, onDisplay;
    std::cout << "Type an array size: ";
    std::cin  >> arraySize;
    std::cout << "Type a chunk size: ";
    std::cin  >> chunkSize;
    std::cout << "Type the amount of elements to display: ";
    std::cin  >> onDisplay;
    std::cout << "Generating arrays" << std::endl;
    int* array_a = randomArray(arraySize, RANDOM_LIMIT, RANDOM_OFFSET);
    int* array_b = randomArray(arraySize, RANDOM_LIMIT, RANDOM_OFFSET);
    int* array_c = new int[arraySize];

    int i;

    #pragma omp parallel for \
    shared(array_a, array_b, array_c, chunkSize) private (i) \
    schedule(static, chunkSize)
    for (i = 0; i < arraySize; i++) {
        array_c[i] = array_a[i] + array_b[i];
    }

    std::cout << "Printing the "
    << std::to_string(onDisplay)
    << " first elements for each array:" << std::endl;

    std::cout << "Array A: ";
    printArray(array_a, arraySize, onDisplay);
    std::cout << "Array B: ";
    printArray(array_b, arraySize, onDisplay);
    std::cout << "Array C: ";
    printArray(array_c, arraySize, onDisplay);

    return 0;
}

void printArray(int* array, int length, int display) {
    int limit = display;
    if (length < display) {
        std::cout << "Can't display " 
        << std::to_string(display) 
        << " elements, there are only " 
        << std::to_string(length) 
        << " elements in the array" 
        << std::endl;
        limit = length;
    }
    for (int i = 0; i < limit; i++) {
        std::cout << std::to_string(array[i]);
        if (i != limit-1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}

int* randomArray(int size, int limit, int offset) {
    int* array = new int[size];
    for (int i = 0; i < size; i++) {
        array[i] = rand() % RANDOM_LIMIT + RANDOM_OFFSET;
    }
    return array;
}