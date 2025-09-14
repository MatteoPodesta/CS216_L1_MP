#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <string>
using namespace std;

const string INPUT = "in_numbers";
const string OUTPUT = "out_numbers";
const int MAX_SIZE = 10;


void readInput(int list[], int divisible, int& size);
void readInputDivisibleByNeither(int list[], int divisible, int divisible2, int& size);

bool isDivisileBy(int input, int divisibleBy);

void displayFunction(int threeList[], int threeSize, int sevenList[], int sevenSize, int neitherList[], int neitherSize);
int getSum(int list[], int size);
int getMedian(int list[], int size);
double getAverage(int list[], int size);

void sortFunction(int threeList[], int threeSize, int sevenList[], int sevenSize, int neitherList[], int neitherSize);
void sortArrayDescending(int list[], int size);

void printList(int list[], int size);
string printToFile(int list[], int size);
void exitFunction(int threeList[], int threeSize, int sevenList[], int sevenSize, int neitherList[], int neitherSize);

int main()
{
    int divByThreeArray[MAX_SIZE];
    int divBySevenArray[MAX_SIZE];
    int divByNeitherArray[MAX_SIZE];

    int threeSize = 0;
    int sevenSize = 0;
    int neitherSize = 0;

    readInput(divByThreeArray, 3, threeSize);
    readInput(divBySevenArray, 7, sevenSize);
    readInputDivisibleByNeither(divByNeitherArray, 3, 7, neitherSize);

    int userInput = 0;

    while (userInput != 3) {

        cout << "\nMenu:\n1. Print each list\n2. Sort each list in descending order\n3. Quit and print the list on the output file\n\nInput: ";
        cin >> userInput;

        switch (userInput) {
        case 1:

            displayFunction(divByThreeArray, threeSize, divBySevenArray, sevenSize, divByNeitherArray, neitherSize);
            break;
        case 2:

            sortFunction(divByThreeArray, threeSize, divBySevenArray, sevenSize, divByNeitherArray, neitherSize);
            break;
        case 3:

            exitFunction(divByThreeArray, threeSize, divBySevenArray, sevenSize, divByNeitherArray, neitherSize);
            exit(EXIT_SUCCESS);
            break;
        default:
            cout << "Invalid choice, try again\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }

    }

}


void readInput(int list[], int divisible, int& size) {

    int temp = 0;

    ifstream infile;
    infile.open(INPUT + ".dat");
    if (!infile) {
        cout << "Cannot open file" << endl;
        exit(EXIT_FAILURE);
    }

    while (size < MAX_SIZE && !infile.eof()) {

        temp = 0;

        infile >> temp;

        if (isDivisileBy(temp, divisible)) {

            list[size] = temp;
            size++;
        }

    }
    if (size == 0) {

        cout << "ERROR: Input file is empty.  Quitting...\n";
        exit(EXIT_FAILURE);

    }
    else if (size == MAX_SIZE && !infile.eof()) {


        cout << "WARNING: Not all numbers were stored, only the first " << MAX_SIZE << " will be stored\n";

    }

    infile.close();
}
void readInputDivisibleByNeither(int list[], int divisible, int divisible2, int& size) {

    int temp = 0;

    ifstream infile;
    infile.open(INPUT + ".dat");
    if (!infile) {
        cout << "Cannot open file" << endl;
        exit(EXIT_FAILURE);
    }

    while (size < MAX_SIZE && !infile.eof()) {

        infile >> temp;
        if (!isDivisileBy(temp, divisible) && !isDivisileBy(temp, divisible2)) {

            list[size] = temp;
            size++;
        }

    }
    if (size == 0) {

        cout << "ERROR: Input file is empty.  Quitting...\n";
        exit(EXIT_FAILURE);

    }
    else if (size == MAX_SIZE && !infile.eof()) {


        cout << "WARNING: Not all numbers were stored, only the first " << MAX_SIZE << " will be stored\n";

    }

    infile.close();
}

bool isDivisileBy(const int input, int divisibleBy) {
    //============================================================================
    //Rather than the if statement returning true if its true,
    // I used a seperate variariable to make sure that it can return false
    // without using multiple return statements.  The code wouldn't work otherwise
    //============================================================================

    bool isTrue = false;

    if (input % divisibleBy == 0) {

        isTrue = true;
    }

    return isTrue;
}

void displayFunction(int threeList[], int threeSize, int sevenList[], int sevenSize, int neitherList[], int neitherSize) {
    cout << "Numbers divisible by three: \n";
    printList(threeList, threeSize);
    cout << "\nSum: " << getSum(threeList, threeSize) << endl
        << "\nAverage: " << getAverage(threeList, threeSize) << endl
        << "\nMedian: " << getMedian(threeList, threeSize) << endl;

    cout << "Numbers divisible by seven: \n";
    printList(sevenList, sevenSize);
    cout << "\nSum: " << getSum(sevenList, sevenSize) << endl
        << "\nAverage: " << getAverage(sevenList, sevenSize) << endl
        << "\nMedian: " << getMedian(sevenList, sevenSize) << endl;

    cout << "Numbers divisible by neither: \n";
    printList(neitherList, neitherSize);
    cout << "\nSum: " << getSum(neitherList, neitherSize) << endl
        << "\nAverage: " << getAverage(neitherList, neitherSize) << endl
        << "\nMedian: " << getMedian(neitherList, neitherSize) << endl;

}
int getSum(int list[], int size) {

    int sum = 0;

    for (int i = 0; i < size; i++) {

        sum = sum + list[i];

    }

    return sum;

}
int getMedian(int list[], int size) {

    int temp = 0;

    for (int i = 0; i < size; i++) {

        for (int j = 0; j < size; j++) {

            if (list[i] > list[j]) {

                temp = list[i];
                list[i] = list[j];
                list[j] = temp;

            }

        }

    }

    return list[size / 2];

}
double getAverage(int list[], int size) {

    double average = getSum(list, size) / size;
    return average;

}

void sortFunction(int threeList[], int threeSize, int sevenList[], int sevenSize, int neitherList[], int neitherSize) {

    cout << "\nThree\n";
    sortArrayDescending(threeList, threeSize);
    cout << "\nSeven\n";
    sortArrayDescending(sevenList, sevenSize);
    cout << "\nNeither\n";
    sortArrayDescending(neitherList, neitherSize);

}
void sortArrayDescending(int list[], int size) {

    int temp = 0;

    for (int i = 0; i < size; i++) {

        for (int j = 0; j < size; j++) {

            if (list[i] > list[j]) {

                temp = list[i];
                list[i] = list[j];
                list[j] = temp;

            }

        }

    }

    printList(list, size);

}

void printList(int list[], int size) {

    for (int i = 0; i < size; i++) {

        cout << list[i] << endl;

    }

}
string printToFile(int list[], int size) {

    string output;

    for (int i = 0; i < size; i++) {

        output = output + to_string(list[i]) + "\n";

    }

    return output;
}
void exitFunction(int threeList[], int threeSize, int sevenList[], int sevenSize, int neitherList[], int neitherSize) {

    ofstream outfile;
    outfile.open(OUTPUT + ".dat");

    outfile << "List of numbers divisible by three: \n"
        << printToFile(threeList, threeSize)

        << "List of numbers divisible by seven: \n"
        << printToFile(sevenList, sevenSize)

        << "List of numbers not divisible by three or seven: \n"
        << printToFile(neitherList, neitherSize);

    outfile.close();

}

//TEST RUN
/*
Menu:
1. Print each list
2. Sort each list in descending order
3. Quit and print the list on the output file

Input: 1
Numbers divisible by three:
12
33
12
23535

Sum: 23592

Average: 5898

Median: 12
Numbers divisible by seven:
7

Sum: 7

Average: 7

Median: 7
Numbers divisible by neither:
4
5
17
23

Sum: 49

Average: 12

Median: 5

Menu:
1. Print each list
2. Sort each list in descending order
3. Quit and print the list on the output file

Input: 2

Three
23535
33
12
12

Seven
7

Neither
23
17
5
4

Menu:
1. Print each list
2. Sort each list in descending order
3. Quit and print the list on the output file

Input: 3

C:\Users\Matteo\source\repos\ConsoleApplication1\x64\Debug\ConsoleApplication1.exe (process 20908) exited with code 0.
Press any key to close this window . . .*/
