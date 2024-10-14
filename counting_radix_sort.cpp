#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

bool Branje_Stevil(vector<int> &vec, const char s[]) {
    ifstream input(s);
    int st;

    if (!input.is_open()) {
        return false;
    }

    while (!input.eof()) {
        input >> st;
        vec.push_back(st);
        while (isspace(input.peek())) input.get();
    }
    input.close();
    return true;
}

void Izpis_Stevil(const vector<int>& A) {
    ofstream output("out.txt");

    for (size_t i = 0; i < A.size(); i++)
        output << A[i] << ' ';
}


void countingSort(vector<int>& A, int exp) {
    const int BASE = 10; // Base for digits (0 to 9)
    vector<int> count(BASE, 0), output(A.size());

    // Count the appearance of digits
    for (size_t i = 0; i < A.size(); i++) {
        int number = A[i]; // Get the number
        int digit = (number / exp) % 10;
        count[digit]++;
    }

    // Modify count array to store position of each digit
    for (int i = 1; i < BASE; i++)
        count[i] += count[i - 1];

    // Output array
    for (int i = A.size() - 1; i >= 0; i--) {
        int num = A[i]; // Get the current number
        int digit = (num / exp) % 10;
        output[count[digit] - 1] = num;
        count[digit]--;
    }

    //  Copy the sorted elements into the original array
    for (size_t i = 0; i < A.size(); i++)
        A[i] = output[i];
}

void radixSort(vector<int>& A) {
    int max = *max_element(A.begin(), A.end());

    int exp = 1;
    while (max / exp > 0) {
        countingSort(A, exp);
        exp *= 10;
    }
}


int main(int argc, const char* argv[]) {
    vector<int> A;

    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <input file>\n";
        return 1;
    }

    if (!Branje_Stevil(A, argv[1])) {
        cout << "Error reading input file.\n";
        return 1;
    }

    radixSort(A);

    Izpis_Stevil(A);


    return 0;

}