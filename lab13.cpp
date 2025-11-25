/*
 * File: lab13.cpp
 * Description: Debugging and Testing Lab for EECS 348
 * Author: Pranav Amatapu
 * Date: 20/11/2025
 *
 * --- ANSWERS TO QUESTIONS ---
 *
 * 1. Is there a fault in the program? If so, locate it and explain.
 * Yes. The fault is in the loop initialization: 'for (int i = 1; ...'. 
 * In C++, vectors are 0-indexed. Starting at 1 skips the first lecture (index 0).
 * It should be 'int i = 0'.
 *
 * 2. Define a test case that does not execute the fault.
 * Impossible. The fault is in the initialization of the for-loop, which executes 
 * immediately upon entering the function for any vector of size > 1. To process 
 * attendance, the loop must run, thus the faulty line always executes.
 *
 * 3. Define a test case that executes the fault but does not result in an error state.
 * Input: {1, 1, 1, 1, 1, 1, 1, 1, 1, 1} (All Present)
 * Explanation: The loop skips index 0. However, the student was present (1) at index 0.
 * The correct 'absent_count' adds 0 for this index. The faulty code also adds 0 (by skipping).
 * Internal state (absent_count) remains correct (0).
 *
 * 4. Define a test case that results in an error state but not a failure.
 * Input: {0, 1, 1, 1, 1, 1, 1, 1, 1, 1} (Absent at index 0 only)
 * Explanation: The student is absent at index 0. The program skips this.
 * Internal state 'absent_count' is 0, but should be 1. This is an ERROR STATE.
 * However, 1 absence is not enough to fail (>3). So it returns False (Pass).
 * The correct return is also False (Pass). No external failure occurs.
 *
 * 5. Define a test case that results in failure.
 * Input: {0, 0, 0, 1, 1, 1, 1, 1, 1, 1} (Absent at 0, 1, 2)
 * Explanation: The student has 3 absences (Fail). 
 * The program skips index 0, counting only 2 absences.
 * Program returns False (Pass). Correct behavior is True (Fail).
 * The external behavior deviates from expected. FAILURE.
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// --- 1. The Buggy Function (As given in PDF) ---
// Note: This uses 'int i' which causes a warning. This is expected.
bool fail_lecture(const vector<int>& attendance_records) {
    int absent_count = 0;
    // FAULT HERE: PDF specifies starting at i=1
    for (int i = 1; i < attendance_records.size(); ++i) { 
        absent_count += (attendance_records[i] == 0);
    }
    return absent_count >= 3;
}

// --- 2. The Corrected Function (For Expected Output) ---
// Fix: Loop starts at i=0 and uses the same logic
bool fail_lecture_corrected(const vector<int>& attendance_records) {
    int absent_count = 0;
    // FIX HERE: Start at i=0
    for (int i = 0; i < attendance_records.size(); ++i) { 
        absent_count += (attendance_records[i] == 0);
    }
    return absent_count >= 3;
}

// Helper function to print test results
void run_test_case(int id, const vector<int>& attendance, string description) {
    bool actual_result = fail_lecture(attendance);
    bool expected_result = fail_lecture_corrected(attendance);

    cout << "Test Case " << id << ": " << description << endl;
    cout << "Input: { ";
    for (int val : attendance) cout << val << " ";
    cout << "}" << endl;
    
    cout << "Expected Output (from corrected function): " << (expected_result ? "Fail (1)" : "Pass (0)") << endl;
    cout << "Actual Output   (from buggy function):     " << (actual_result ? "Fail (1)" : "Pass (0)") << endl;
    
    if (actual_result != expected_result) {
        cout << "Result: FAILURE (Observed Difference - Bug Detected!)" << endl;
    } else {
        cout << "Result: MATCH (No external failure observed)" << endl;
    }
    cout << "--------------------------------------------------" << endl;
}

int main() {
    cout << "EECS 348 Lab 13: Debugging and Testing" << endl;
    cout << "--------------------------------------------------" << endl;

    // Test Case for Q3
    vector<int> records_q3 = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    run_test_case(3, records_q3, "Execute Fault, No Error State");

    // Test Case for Q4
    vector<int> records_q4 = {0, 1, 1, 1, 1, 1, 1, 1, 1, 1}; 
    run_test_case(4, records_q4, "Error State, No Failure");

    // Test Case for Q5
    vector<int> records_q5 = {0, 0, 0, 1, 1, 1, 1, 1, 1, 1}; 
    run_test_case(5, records_q5, "Failure (External Behavior Incorrect)");

    return 0;
}