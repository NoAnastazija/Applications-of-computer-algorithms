#include <fstream>
#include <vector>
#include <algorithm>
#include <limits>
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

void Izpis_Stevil(int* polje, unsigned int velikost) {
    ofstream output("out.txt");

    for (int i = 0; i <velikost; i++)
        output << polje[i] << ' ';
}

// countSort function
void countSort(vector<int>& A) {
    // Find the minimum and maximum elements in the array
    int mini = *min_element(A.begin(), A.end());
    int maxi = *max_element(A.begin(), A.end());

    // Adjust values to start from 0 and find the new maximum value
    for (int i = 0; i < A.size(); i++) {
        A[i] = A[i] - mini;
        if (A[i] > maxi) {
            maxi = A[i];
        }
    }

    // Initialize a counting array with size equal to maximum value
    vector<int> C(maxi + 1, 0);

    // Count occurrences of each element in the original array
    for (int num : A) {
        C[num]++;
    }

    // sum of counts to determine the position of each element in the sorted array
    for (int i = 1; i <= maxi; i++) {
        C[i] += C[i - 1];
    }

    // Create a temporary array to store the sorted elements
    vector<int> B(A.size());

    // Reconstruct the sorted array by placing elements in their correct positions
    for (int i = A.size() - 1; i >= 0; --i) {
        B[C[A[i]] - 1] = A[i];
        C[A[i]]--;
    }

    // Adjust values back to their original range and update the original array
    for (int i = 0; i < A.size(); i++) {
        A[i] = B[i] + mini;
    }
}

// romanSort function
void romanSort(vector<int>& A) {
    // Find the minimum and maximum elements in the array
    int mini = *min_element(A.begin(), A.end());
    int maxi = *max_element(A.begin(), A.end());

    // Adjust values to start from 0 and find the new maximum value
    for (int i = 0; i < A.size(); i++) {
        A[i] = A[i] - mini;
        if (A[i] > maxi) {
            maxi = A[i];
        }
    }

    // Initialize a counting array with size equal to maximum value
    vector<int> C(maxi + 1, 0);

    // Count occurrences of each element in the original array
    for (size_t i = 0; i < A.size(); i++) {
        int num = A[i];
        C[num]++;
    }

    // Create a temporary array to store the sorted elements
    vector<int> B(A.size());
    int index = 0;

    // Reconstruct the sorted array using the counts from the counting array
    for (int i = 0; i <= maxi; i++) {
        for (int j = 0; j < C[i]; j++) {
            B[index++] = i;
        }
    }

    // Adjust values back to their original range and update the original array
    for (size_t i = 0; i < A.size(); i++) {
        A[i] = B[i] + mini;
    }
}


int main(int argc, const char* argv[]) {
    vector<int> A;

    if (argc < 3) return 0;
    if (!Branje_Stevil(A, argv[2])) return 0;

    if (argv[1][0] == '0') {
        // counting sort
        countSort(A);
    }else{
        // roman sort
        romanSort(A);
    }
    Izpis_Stevil(&A[0],A.size());

    return 0;

}