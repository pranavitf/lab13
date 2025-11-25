/*
 * File: lab13.cpp
 * Description: Debugging and Testing Lab for EECS 348
 * Author: Pranav Amatapu
 * Date: 20/11/2025
 */

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// --- The Program Under Test (Algorithm 1 from Lab PDF) ---
// Note: This function intentionally contains the bug as per instructions.
bool fail_lecture(const vector<int>& attendance_records) {
    int absent_count = 0;
    // Fault: Loop starts at i=1, skipping the first record (index 0)
    for (int i = 1; i < attendance_records.size(); ++i) { 
        if (attendance_records[i] == 0) {
            absent_count++;
        }
    }
    return absent_count >= 3;
}

// Helper function to print test results
void run_test_case(int id, const vector<int>& attendance, bool expected_out, string description) {
    bool result = fail_lecture(attendance);
    cout << "Test Case " << id << ": " << description << endl;
    cout << "Input: { ";
    for (int val : attendance) cout << val << " ";
    cout << "}" << endl;
    cout << "Expected Output: " << (expected_out ? "Fail (1)" : "Pass (0)") << endl;
    cout << "Actual Output:   " << (result ? "Fail (1)" : "Pass (0)") << endl;
    
    if (result == expected_out) {
        cout << "Result: MATCH (But logically..." << endl;
        // Logic check for specific questions
        if (id == 5) cout << "        ...Wait, for Q5 this implies the bug wasn't triggered? Error in logic setup?)" << endl; 
        else cout << "        ...Behavior is as expected for this specific scenario)" << endl;
    } else {
        cout << "Result: FAILURE (Observed Difference)" << endl;
    }
    cout << "--------------------------------------------------" << endl;
}

int main() {
    cout << "EECS 348 Lab 13: Debugging and Testing" << endl;
    cout << "--------------------------------------------------" << endl;

    // Q2: Impossible to not execute fault with 10 items, 
    // but running a standard case to demonstrate the code runs.
    vector<int> records_q3 = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}; // All Present
    run_test_case(3, records_q3, false, "Execute Fault, No Error State (All Present)");

    // Q4: Error State but No Failure
    // Real absences: 1 (at index 0). Calc absences: 0. Both < 3. Result: Pass.
    vector<int> records_q4 = {0, 1, 1, 1, 1, 1, 1, 1, 1, 1}; 
    run_test_case(4, records_q4, false, "Error State, No Failure (Absent at Index 0 only)");

    // Q5: Failure
    // Real absences: 3 (Index 0, 1, 2). Calc absences: 2. 
    // Real Result: Fail. Calc Result: Pass.
    vector<int> records_q5 = {0, 0, 0, 1, 1, 1, 1, 1, 1, 1}; 
    run_test_case(5, records_q5, true, "Failure (3 Absences, one at Index 0)");

    return 0;
}