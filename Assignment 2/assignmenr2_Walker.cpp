#include <iostream>
#include <fstream>
#include <utility>
#include <string>

using namespace std;

int const SIZE = 10000;

void bubbleSort(int &cCnt, int &mCnt, string ary[])
{
    bool swapped;
    for (int i = 0; i < SIZE - 1; i++)
    {
        swapped = false;
        for (int j = 0; j < SIZE - i - 1; j++)
        {
            cCnt++;
            if (ary[j] > ary[j + 1])
            {
                mCnt++;
                swap(ary[j], ary[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
        {
            break;
        }
    }
}
void selectionSort(int &cCnt, int &mCnt, string ary[])
{
    for (int i = 0; i < SIZE - 1; i++)
    {
        // Find index of smallest remaining element
        int indexSmallest = i;
        for (int j = i + 1; j < SIZE; j++)
        {
            if (ary[j] < ary[indexSmallest])
            {
                cCnt++;
                indexSmallest = j;
            }
        }

        // Swap numbers[i] and numbers[indexSmallest]
        string temp = ary[i];
        ary[i] = ary[indexSmallest];
        ary[indexSmallest] = temp;
        mCnt++;
    }
}
void insertionSort(int &cCnt, int &mCnt, string ary[])
{
    string key;
    int j;
    for (int i = 0; i < SIZE; i++)
    {
        key = ary[i];
        j = i - 1;
        cCnt++;
        while (j >= 0 && ary[j] > key)
        {
            ary[j + 1] = ary[j];
            j = j - 1;
            mCnt++;
        }
        ary[j + 1] = key;
    }
}
void Merge(string *numbers, int leftFirst, int leftLast, int rightLast)
{
    int mergedSize = rightLast - leftFirst + 1;     // Size of merged partition
    string *mergedNumbers = new string[mergedSize]; // Dynamically allocates temporary
                                                    // array for merged numbers
    int mergePos = 0;                               // Position to insert merged number
    int leftPos = leftFirst;                        // Initialize left partition position
    int rightPos = leftLast + 1;                    // Initialize right partition position

    // Add smallest element from left or right partition to merged numbers
    while (leftPos <= leftLast && rightPos <= rightLast)
    {
        if (numbers[leftPos] <= numbers[rightPos])
        {
            mergedNumbers[mergePos] = numbers[leftPos];
            leftPos++;
        }
        else
        {
            mergedNumbers[mergePos] = numbers[rightPos];
            rightPos++;
        }
        mergePos++;
    }

    // If left partition is not empty, add remaining elements to merged numbers
    while (leftPos <= leftLast)
    {
        mergedNumbers[mergePos] = numbers[leftPos];
        leftPos++;
        mergePos++;
    }

    // If right partition is not empty, add remaining elements to merged numbers
    while (rightPos <= rightLast)
    {
        mergedNumbers[mergePos] = numbers[rightPos];
        rightPos++;
        mergePos++;
    }

    // Copy merged numbers back to numbers
    for (mergePos = 0; mergePos < mergedSize; mergePos++)
    {
        numbers[leftFirst + mergePos] = mergedNumbers[mergePos];
    }

    // Free temporary array
    delete[] mergedNumbers;
}

void mergeSort(string aryCpy[SIZE], int startIndex, int endIndex)
{
    string *ary = aryCpy;

    if (startIndex < endIndex)
    {
        // Find the midpoint in the partition
        int mid = (startIndex + endIndex) / 2;

        // Recursively sort left and right partitions
        mergeSort(ary, startIndex, mid);
        mergeSort(ary, mid + 1, endIndex);

        // Merge left and right partition in sorted order
        Merge(ary, startIndex, mid, endIndex);
    }
}

int Partition(string *numbers, int startIndex, int endIndex)
{
    // Select the middle value as the pivot.
    int midpoint = startIndex + (endIndex - startIndex) / 2;
    string pivot = numbers[midpoint];

    // "low" and "high" start at the ends of the partition
    // and move toward each other.
    int low = startIndex;
    int high = endIndex;

    bool done = false;
    while (!done)
    {
        // Increment low while numbers[low] < pivot
        while (numbers[low] < pivot)
        {
            low = low + 1;
        }

        // Decrement high while pivot < numbers[high]
        while (pivot < numbers[high])
        {
            high = high - 1;
        }

        // If low and high have crossed each other, the loop
        // is done. If not, the elements are swapped, low is
        // incremented and high is decremented.
        if (low >= high)
        {
            done = true;
        }
        else
        {
            string temp = numbers[low];
            numbers[low] = numbers[high];
            numbers[high] = temp;
            low = low + 1;
            high = high - 1;
        }
    }

    // "high" is the last index in the left partition.
    return high;
}

void quickSort(string aryCpy[SIZE], int startIndex, int endIndex)
{
    string *ary = aryCpy;

    // Only sort if at least 2 elements exist
    if (endIndex <= startIndex)
    {
        return;
    }

    // Partition the array
    int high = Partition(ary, startIndex, endIndex);

    // Recursively sort the left partition
    quickSort(ary, startIndex, high);

    // Recursively sort the right partition
    quickSort(ary, high + 1, endIndex);
}

int main()
{
    // open file
    ifstream inData;
    inData.open("Passwords.txt");

    // init vars
    string pswordAry[SIZE];
    int i = 0;
    int bsCCnt = 0, ssCCnt = 0, isCCnt = 0, msCCnt = 0, qsCCnt = 0;
    int bsMCnt = 0, ssMCnt = 0, isMCnt = 0, msMCnt = 0, qsMCnt = 0;

    // get data
    if (inData.is_open())
    {
        while (getline(inData, pswordAry[i]))
        {
            i++;
        }
        inData.close();
    }
    else
    {
        cout << "ERROR: File Not Read" << endl;
        return 0;
    }

    int test = 0;
    while (test < SIZE - 1)
    {
        cout << pswordAry[test] << endl;
        test++;
    }

    // get results
    bubbleSort(bsCCnt, bsMCnt, pswordAry);
    selectionSort(ssCCnt, ssMCnt, pswordAry);
    insertionSort(isCCnt, isMCnt, pswordAry);
    mergeSort(pswordAry, 0, SIZE - 1);
    quickSort(pswordAry, 0, SIZE - 1);

    // print results
    cout << "Bubble Sort:" << endl;
    cout << "Number of Comparisons: " << bsCCnt << endl;
    cout << "Number of Movements: " << bsMCnt << endl;
    cout << "Selection Sort:" << endl;
    cout << "Number of Comparisons: " << ssCCnt << endl;
    cout << "Number of Movements: " << ssMCnt << endl;
    cout << "Insertion Sort:" << endl;
    cout << "Number of Comparisons: " << isCCnt << endl;
    cout << "Number of Movements: " << isMCnt << endl;
    cout << "Merge Sort:" << endl;
    cout << "Number of Comparisons: " << msCCnt << endl;
    cout << "Number of Movements: " << msMCnt << endl;
    cout << "Quick Sort:" << endl;
    cout << "Number of Comparisons: " << qsCCnt << endl;
    cout << "Number of Movements: " << qsMCnt << endl;
}