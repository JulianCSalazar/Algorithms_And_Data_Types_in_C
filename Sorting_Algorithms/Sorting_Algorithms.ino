#include <stdio.h>
#include <time.h>
#include <math.h>

#define MAIN setup

void bubbleSort(int A[], int a_len)
{
  int i, j;
  for (i = 0; i < a_len; i++) {
    for (j = 0; j < a_len-(i+1); j++){
      if (A[j] > A[j+1]) {
        swap(A, j, j+1);
      }
    }
  }
  Serial.println("Finished bubble sorting");
}

void selectionSort(int A[], int a_len){
  int i, j;
  int minValue;
  int minValueIndex;
  for (i = 0; i < a_len; i++) {
    minValue = A[i];
    minValueIndex = i;
    for (j = i; j < a_len; j++) {
      if (A[j] < minValue) {
        minValue = A[j];
        minValueIndex = j;
      }
    }
    swap(A, i, minValueIndex);
  }
  Serial.println("Finished selection sorting");
}

void insertionSort(int A[], int a_len)
{
  int i, j, key, new_index;
  for (i = 1; i < a_len; i++) {
    key = A[i];
    j = i - 1;
    while ((j >= 0) && (A[j] > key)) {
      A[j+1] = A[j];
      j--;
    }
    A[j+1] = key;
  }
  Serial.println("Finished insertion sorting");
}

void swap(int A[], int i1, int i2) 
{
  int temp = A[i1];
  A[i1] = A[i2];
  A[i2] = temp;
}

int arrayLength(int A[])
{
  if (A[0] != NULL) {
    return (sizeof(A) / sizeof(A[0]));
  } else {
    return -1;
  }
}

void generateRandomArray(int A[], int a_len)
{
  int i;
  for (i = 0; i < a_len; i++) {
    A[i] = random(0,19);
    //Serial.println(A[i]);
  }
}

void printArray(int A[], int a_len)
{
  int i;
  for (i = 0; i < a_len; i++) {
    Serial.print(A[i]);
    Serial.print(" ");
  }
  Serial.println(" ");
}

void MAIN() 
{
  Serial.begin(9600);
  
  int arrayLength = 10;
  int myRandomArray[arrayLength];
  generateRandomArray(myRandomArray, arrayLength);
  printArray(myRandomArray, arrayLength);
  //bubbleSort(myRandomArray, arrayLength);
  //selectionSort(myRandomArray, arrayLength);
  //insertionSort(myRandomArray, arrayLength);
  printArray(myRandomArray, arrayLength);
}

void loop()
{}
