#include <stdio.h>
#include <time.h>
#include <math.h>

#define MAIN setup

/**********************************************************
 * SORTING FUNCTIONS
 **********************************************************/


/* Description:
 *  This sorting algorithm starts at the far left of an array and 
 *  compares each value from left to right with its neighbor to the right.
 *  If the right neighbor is smaller, then we swap values with our current
 *  index. 
 *  
 *  This process will progressively push the largest value of the array to
 *  the far right of the array. So, after the first pass through, the
 *  largest value in you array is on the far right of the array; after the
 *  second pass through the second largest value in the array will be one
 *  index in from the last; and so on. This means you don't need to run
 *  through the whole array through each pass. You can run through one less
 *  value each time since we already know the largest values are at the end
 *  and we won't need to swap them.
 */
void bubbleSort(int A[], int a_len)
{
  // Variable initialization
  int i, j;
  
  // Make a_len passes through the array
  for (i = 0; i < a_len; i++) {

    //Compare neighbors and swap if not in order
    for (j = 0; j < a_len-(i+1); j++){
      if (A[j] > A[j+1]) {
        swap(A, j, j+1);
      }
    }
  }
  Serial.println("Finished bubble sorting");
} // End bubbleSort()

/* Description:
 *  This algorithm will find the smallest value in the array and move it
 *  to the front. After each pass the next smallest value is moved into the
 *  next position in the array moving from left to right.
 */
void selectionSort(int A[], int a_len){
  // Variable initialization
  int i, j;
  int minValue;
  int minValueIndex;

  // Make a_len passes through the array
  for (i = 0; i < a_len; i++) {
    // Our first value we look at is the smallest
    minValue = A[i];
    minValueIndex = i;

    // Find smallest value in array beyond index i
    for (j = i; j < a_len; j++) {
      if (A[j] < minValue) {
        minValue = A[j];
        minValueIndex = j;
      }
    }
    // Swap smallest value in array beyond index i with i
    swap(A, i, minValueIndex);
  }
  Serial.println("Finished selection sorting");
} // End selectionSort()

/* Description:
 *  This algorithm breaks down the original array into growing sub arrays.
 *  The sub arrays grow by taking a value outside of the sub array and
 *  placing it inside. This process does require you to shift the indeces of
 *  the sub array to the right to make room for the placement of this new
 *  value.
 */
void insertionSort(int A[], int a_len)
{
  // Variable initialization
  int i, j; 
  int key;
  int new_index;

  for (i = 1; i < a_len; i++) {
    // Grab first value to right of sub array
    key = A[i];
    // j is index of end of sub array
    j = i - 1;
    // Shift values in subarray to the right until we find where the key
    // goes.
    while ((j >= 0) && (A[j] > key)) {
      A[j+1] = A[j];
      j--;
    }
    A[j+1] = key;
  }
  Serial.println("Finished insertion sorting");
} // End insertionSort()

/* Description:
 *  This function simply calls the mergeRecursion() function to keep
 *  function parameters entered from the main() consistent across
 *  all my sorting functions.
 */
void mergeSort(int A[], int a_len)
{
  mergeRecursion(A, 0, a_len-1);
} // End mergeSort()

/* Description:
 *  MERGESORT HELPER
 *  This function will take our array and continuosly break it in half
 *  until the subarrays only have 1 value left. When it finishes breaking
 *  them down they are remerged in proper order using the merge() function.
 */
void mergeRecursion(int A[], int leftPoint, int rightPoint)
{
  if (leftPoint < rightPoint) {
    int midPoint = (rightPoint + leftPoint) / 2;
    mergeRecursion(A, leftPoint, midPoint);
    mergeRecursion(A, midPoint+1, rightPoint);
    merge(A, leftPoint, midPoint, rightPoint);
  }
} // End mergeRecursion()

/* Description:
 *  MERGESORT HELPER
 *  This function takes two subarrays with the main array A and puts them
 *  together by checking the left most values of each and moving the smaller
 *  value back into the respective merged position.
 */
void merge(int A[], int l, int m, int r)
{
  //Variable initialization
  int subArray1Len = m - l + 1;
  int subArray2Len = r - m;
  int subArray1[subArray1Len];
  int subArray2[subArray2Len];
  int i, j, k;

  //Copy the data in A to our sub-Arrays
  for ( i = 0; i < subArray1Len; i++) {
    subArray1[i] = A[l + i];
  }
  for ( i = 0; i < subArray2Len; i++) {
    subArray2[i] = A[m + i + 1];
  }

  i = 0;
  j = 0;
  k = l;

  // Compare the values within the sub arrays. The smaller value is
  //  placed back in the parent array. Only increment the subarray we
  //  take the value from, but increment the parent array each time.
  while ((i < subArray1Len) && (j < subArray2Len)) {
    if (subArray1[i] < subArray2[j]) {
      A[k] = subArray1[i];
      i++;
    } else {
      A[k] = subArray2[j];
      j++;
    }
    k++;
  }

  // One of the arrays will finish emptying itself into the
  //  parent array before the other. When this happens, append the rest
  //  of whatever subarray still has items left and append it onto the
  //  parent.
  while (j < subArray2Len) {
    A[k] = subArray2[j];
    j++;
    k++;
  }
  while (i < subArray1Len) {
    A[k] = subArray1[i];
    i++;
    k++;
  }
} // End merge()

/* Description
 *  This algorithm will restructure the array into a max heap. When it
 *  finishes, the largest value will be in the 0th index of the array (or
 *  the head of the heap). This value is then swapped with the value at the
 *  end of the array, making a much smaller value the new head of the heap,
 *  and the end of the array now holds the largest value in the array. The
 *  new head of the heap is then sunk down with a sub-array not containing
 *  the last value (the old heap head), and make a new sub-heap. 
 *  
 *  The process repeats with progressively smaller sub-heaps until each
 *  next largest value is moved out of the sub-array. Once the sub-heap only
 *  has one value left, the sort is finished
 */
void heapSort(int A[], int a_len)
{
  //Variable initialization
  int i;
  int heapHead = 0;

  //Make a max heap
  heapify(A, a_len);
  printArray(A, a_len);

  for (i = 1; i < a_len; i++) {
    // Swap head with furthest removed child
    swap(A, heapHead, a_len - i);
    // Reposition head to proper spot within sub-array to recreate proper
    // heap structure
    sinkDown(A, heapHead, a_len - (i+1));
  }
  Serial.println("Finished heap sorting");
} // End heapSort()

/* Description:
 *  HEAPSORT HELPER
 *  Calls bubbleUp function on each value in the array
 */
void heapify(int A[], int a_len){
  //Variable Initialization
  int i;
  
  for (i = 1; i < a_len; i++) {
    bubbleUp(A, i, (i-1)/2);
  }
} // End heapify()

/* Description:
 *  HEAPSORT HELPER
 *  This function compares a given index i with its parent j. If the given
 *  index is larger than its parent, they are swapped. This function
 *  recursively calls itself for as the original index is larger than its
 *  parent.
 */
void bubbleUp(int A[], int i, int j)
{
  if (A[i] > A[j]) {
    swap(A, i, j);
    bubbleUp(A, j, j/2);
  }
} // End bubbleUp()

/* Description:
 *  HEAPSORT HELPER
 *  This function takes a given index and moves it down the heap to its
 *  respective position within a certain range inside the original array
 *  A.
 */
void sinkDown(int A[], int startPoint, int workingRange)
{
  //Variable initialization
  int swapIndex;
  int leftChildIndex = (startPoint*2) + 1;
  int rightChildIndex = (startPoint*2) + 2;

  
  if (leftChildIndex > workingRange) {
    // If we have hit the bottom of our heap with our subarray,
    //  we are done
    return;
  } else if (rightChildIndex > workingRange){
    // If only the right child is outside the working range, we use the
    //  left child index for our comparision.
    swapIndex = leftChildIndex;
  } else if (A[leftChildIndex] > A[rightChildIndex]) {
    // If the left child is larger than the right child, we use the left
    //  child for comparison
    swapIndex = leftChildIndex;
  } else {
    // If the right child is larger than the left child, we use the right
    //  child comparison
    swapIndex = rightChildIndex;
  }

  // If the parent is small than the larger of the two children, we swap
  //  it with the larger child
  if (A[startPoint] < A[swapIndex]) {
    swap(A, startPoint, swapIndex);
    // Repeat the process with our value now in the new child position moving
    //  further down the heap.
    sinkDown(A, swapIndex, workingRange);
  }
} // End sinkDown()

/**********************************************************
 * HELPER FUNCTIONS
 **********************************************************/
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

/**********************************************************
 * MAIN CODE
 **********************************************************/

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
  //mergeSort(myRandomArray, arrayLength);
  heapSort(myRandomArray, arrayLength);
  printArray(myRandomArray, arrayLength);
}

void loop()
{}
