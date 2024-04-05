/*Ella Jewel Wolter
*ejw0073@auburn.edu
*COMP 2710 Project 3
*project3_Wolter_ejw0073.cpp
*compile with g++ project3_Wolter_ejw0073.cpp
*run with ./a.out
*/

/*references:
 *used https://www.youtube.com/watch?v=Cz4fl-TUjVk for some tips on reading files
 *used https://www.youtube.com/watch?v=QnCVoYnLIg8&t=27s for help on streams and reading files
 *watched https://www.youtube.com/watch?v=K7Pi0jGnyqw for help with putting ints into array
 *referred to www.javatpoint.com/cpp-program-to-merge-two-unsorted-arrays for merging the two arrays
 *used https://prepinsta.com/data-structures-algorithms/sorting-of-array/ for help with the different algorithms in c++
 */

# include <iostream>
# include <fstream> //used for reading or writing streams
using namespace std;

//variables
const int MAX_SIZE = 100;
int finalArray[MAX_SIZE];

//reads file and adds to an array, printing out values
int readfile(int numArray[], ifstream& fileIn) {
    int index = 0;
    while (!fileIn.eof() && index != MAX_SIZE) {
        fileIn >> numArray[index];
        index++;
    }

    return index;
}

//combines the two files into one large array
int combine(const int array1[], const int array2[], int array1Size, int array2Size) {
    int finalSize = array1Size + array2Size;

    int i = 0;
    int j = 0;
    int k = 0;
    while (i < array1Size) { //iterate in first array
        finalArray[k] = array1[i];
        i += 1;
        k += 1;
    } while (j < array2Size) { //iterate in second array
        finalArray[k] = array2[j];
        j += 1;
        k += 1;
    }

    return finalSize;
}

//sort merged array
int sort(const int unsortedArray[], int size) {
    int sortedArray[size];
    for (int i = 0; i < size; i++) {
        sortedArray[i] = unsortedArray[i];
    }

    for (int i = 1; i < size; i++) {
        int key = sortedArray[i];
        int j = i - 1;

        while (j >= 0 && sortedArray[j] > key) {
            sortedArray[j + 1] = sortedArray[j];
            j--;
        }

        sortedArray[j + 1] = key;
    }

    cout << "\nThe sorted list of " << size << " numbers is: ";
    for (int m = 0; m < size; m++) {
        cout << sortedArray[m] << " ";
        finalArray[m] = sortedArray[m];
    }

    return size;
}

int main( ) {
    int array1[MAX_SIZE];
    int array1Size;
    int array2[MAX_SIZE];
    int array2Size;

    ifstream fileIn;

    //file one
    cout << "*** Welcome to Jewels' sorting program! ***\n";
    cout << "Enter the first input file name: ";
    string name1;
    cin >> name1;

    fileIn.open(name1.c_str());
    if (fileIn.fail()) {
        cout << "File failed to open." << endl;
        return 0;
    }
    array1Size = readfile(array1, fileIn) -1;
    readfile(array1, fileIn);
    fileIn.close();


    cout << "The list of " << array1Size << " numbers in file " << name1 << " is: \n";
    for (int i = 0; i < array1Size; i++) {
        cout << array1[i] << "\n";
    }

    //file two
    cout << "\nEnter the second  input file name: ";
    string name2;
    cin >> name2;

    fileIn.open(name2.c_str());
    if (fileIn.fail()) {
        cout << "File failed to open." << endl;
        return 0;
    }
    array2Size = readfile(array2, fileIn) - 1;
    readfile(array2, fileIn);
    fileIn.close();

    cout << "The list of " << array2Size << " numbers in file " << name2 << " is: \n";
    for (int i = 0; i < array2Size; i++) {
        cout << array2[i] << "\n";
    }
    int size = combine(array1, array2, array1Size, array2Size);
    combine(array1, array2, array1Size, array2Size);
    sort(finalArray, size);

    //make output file
    cout << "\nEnter the output file name: ";
    string outputName;
    cin >> outputName;

    ofstream file(outputName.c_str());
    for (int i = 0; i < size; i++) {
        file << finalArray[i] << "\n";
    }
    file.close();

    cout << "*** Please check the new file - " << outputName << " ***\n";
    cout << "*** Goodbye! ***\n";

    return 1;
}

//tested on local server with input1.txt and input2.txt from project folder.
//tested fail cases when inputting unknown file name.
//tested on auburn server wth input1.txt and input2.txt from project folder.
