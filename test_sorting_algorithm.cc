// Homework 5
// Testing Sorting Algorithms
// Shihab Islam

#include "Sort.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <vector>
using namespace std;

// Test function that shows how you can time a piece of code.
// Just times a simple loop.

void TestTiming() {
    cout << "Test Timing" << endl;
    const auto begin = chrono::high_resolution_clock::now();
    // Time this piece of code.
    int sum = 0;
    for (int i = 1; i < 10000; ++i) sum++;
    // End of piece of code to time.
    const auto end = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << "ns" << endl;
    cout << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "ms" << endl;

}

// Generates and returns random vector of size @size_of_vector.
// Calls rand() function to fill vector with random values
//  return gives a vector of random values
vector<int> GenerateRandomVector(size_t size_of_vector) {
    vector<int> result;
    for (int i = 0; i < size_of_vector; i++) {
        result.push_back(rand());
    }
    return result;
}

// Generate and returns sorted vecotr of size @size_of_vector
// If smaller_to_larger is true, returns vector sorted from small to large
// Otherwise returns vector sorted from large to small
// This function calls the SORT function from Sort.h and passes a comparator
//  to the sort function and sorts the vetor according to the value of small_to_larger
// small_to_larger: a bool indicating how vector is sorted
// return gives back a sorted vector
vector<int> GenerateSortedVector(size_t size_of_vector, bool smaller_to_larger) {
    vector<int> result;
    for (int i = 0; i < size_of_vector; i++) {
        result.push_back(rand());
    }

    //smaller_to_larger = True
    if (smaller_to_larger) {
        SORT(result, less<int>{});
    }

    //smaller_to_larger = False
    else {
        SORT(result, greater<int>{});
    }

    return result;
}


// Verifies that a vector is sorted given a comparator
// input is  the vector that we will be checking the order of
// less_than is the comparator that indicates how the vector should be sorted, and what order we should check them in - increasing or decreasing order
// return gives  a boolean, that tells us if the vector is properly sorted
template <typename Comparable, typename Comparator>
bool VerifyOrder(const vector<Comparable>& input, Comparator less_than) {
    for (int i = 0; i < input.size() - 1; i++) {
        if (less_than(input[i + 1], input[i]) && input[i] != input[i + 1]) {
            return false;
        }
    }
    return true;
}

// Computes duration given a start time and a stop time in nano seconds
// start_time: the time that the sorting algorithm started running
// end_time: the time that the sorting algorithm finished running
// return gives back  the amount of time the sroting algorithm took to run, in nanoseconds
long long ComputeDuration(chrono::high_resolution_clock::time_point start_time, chrono::high_resolution_clock::time_point end_time) {
    return chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
}

// Wrapper function to test different sorting algorithms
// The wrapper function calls all the sorting algorithms and calls ComputeDuration in to calculate
//  how long the sortng algorithm too to run, and verifys that the vectors are in correct order
void sortTestingWrapper(int argc, char** argv) {
    const string input_type = string(argv[1]);
    const int input_size = stoi(string(argv[2]));
    const string comparison_type = string(argv[3]);
    if (input_type != "random" && input_type != "sorted_small_to_large" && input_type != "sorted_large_to_small") {
        cout << "Invalid input type" << endl;
    }
    if (input_size <= 0) {
        cout << "Invalid size" << endl;
    }
    if (comparison_type != "less" && comparison_type != "greater") {
        cout << "Invalid comparison type" << endl;
    }

    cout << "Running sorting algorithms: " << input_type << " " << input_size << " numbers " << comparison_type << endl;
    vector<int> input_vector;

    if (input_type == "random") {
        // Generate random vector
        input_vector = GenerateRandomVector(input_size);
    }
    else {
        // Generate sorted vector.
        if (input_type == "sorted") {
            input_vector = GenerateSortedVector(input_size, 1);
        }
        else {
            input_vector = GenerateSortedVector(input_size, 0);
        }
    }

    //if  user enters less, it passes less<int>{} for  the Comparator
    if (comparison_type == "less") {
        cout << "Heapsort" << endl;
        cout << endl;
        auto begin = chrono::high_resolution_clock::now();
        HeapSort(input_vector, less<int>{});
        auto end = chrono::high_resolution_clock::now();
        cout << ComputeDuration(begin, end) << " ns" << endl;
        cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << endl;

        cout << endl;

        cout << "MergeSort" << endl;
        cout << endl;
        begin = chrono::high_resolution_clock::now();
        MergeSort(input_vector, less<int>{});
        end = chrono::high_resolution_clock::now();
        cout << ComputeDuration(begin, end) << " ns" << endl;
        cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << endl;

        cout << endl;

        cout << "QuickSort" << endl;
        cout << endl;
        begin = chrono::high_resolution_clock::now();
        QuickSort(input_vector, less<int>{});
        end = chrono::high_resolution_clock::now();
        cout << ComputeDuration(begin, end) << " ns" << endl;
        cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << endl;

        cout << endl;

        cout << "Testing QuickSort Implementations" << endl;

        cout << endl;

        cout << "Median of Three" << endl;
        cout << endl;
        begin = chrono::high_resolution_clock::now();
        QuickSort(input_vector, less<int>{});
        end = chrono::high_resolution_clock::now();
        cout << ComputeDuration(begin, end) << " ns" << endl;
        cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << endl;

        cout << endl;

        cout << "Middle" << endl;
        cout << endl;
        begin = chrono::high_resolution_clock::now();
        QuickSort2(input_vector, less<int>{});
        end = chrono::high_resolution_clock::now();
        cout << ComputeDuration(begin, end) << " ns" << endl;
        cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << endl;

        cout << endl;

        cout << "First" << endl;
        cout << endl;
        begin = chrono::high_resolution_clock::now();
        QuickSort3(input_vector, less<int>{});
        end = chrono::high_resolution_clock::now();
        cout << ComputeDuration(begin, end) << " ns" << endl;
        cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << endl;

    }

    //if  user enters greater, it passes greater<int>{} to the Comparator
    else {

        cout << "Heapsort" << endl;
        cout << endl;
        auto begin = chrono::high_resolution_clock::now();
        HeapSort(input_vector, less<int>{});
        auto end = chrono::high_resolution_clock::now();
        cout << ComputeDuration(begin, end) << " ns" << endl;
        cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << endl;

        cout << endl;

        cout << "MergeSort" << endl;
        cout << endl;
        begin = chrono::high_resolution_clock::now();
        MergeSort(input_vector, less<int>{});
        end = chrono::high_resolution_clock::now();
        cout << ComputeDuration(begin, end) << " ns" << endl;
        cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << endl;

        cout << endl;

        cout << "QuickSort" << endl;
        cout << endl;
        begin = chrono::high_resolution_clock::now();
        QuickSort(input_vector, less<int>{});
        end = chrono::high_resolution_clock::now();
        cout << ComputeDuration(begin, end) << " ns" << endl;
        cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << endl;

        cout << endl;

        cout << "Testing QuickSort Implementations" << endl;

        cout << endl;

        cout << "Median of Three" << endl;
        cout << endl;
        begin = chrono::high_resolution_clock::now();
        QuickSort(input_vector, less<int>{});
        end = chrono::high_resolution_clock::now();
        cout << ComputeDuration(begin, end) << " ns" << endl;
        cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << endl;

        cout << endl;

        cout << "Middle" << endl;
        cout << endl;
        begin = chrono::high_resolution_clock::now();
        QuickSort2(input_vector, less<int>{});
        end = chrono::high_resolution_clock::now();
        cout << ComputeDuration(begin, end) << " ns" << endl;
        cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << endl;

        cout << endl;

        cout << "First" << endl;
        cout << endl;
        begin = chrono::high_resolution_clock::now();
        QuickSort3(input_vector, less<int>{});
        end = chrono::high_resolution_clock::now();
        cout << ComputeDuration(begin, end) << " ns" << endl;
        cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << endl;


    }


}

int main(int argc, char** argv) {
    if (argc != 4) {
        cout << "Usage: " << argv[0] << "<input_type> <input_size> <comparison_type>" << endl;
        return 0;
    }

    sortTestingWrapper(argc, argv);

    return 0;
}