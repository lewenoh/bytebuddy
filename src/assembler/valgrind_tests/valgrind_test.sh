#!/bin/bash

# Path to the program
PROGRAM="./assemble"

# Path to the test cases directory
TEST_CASES_DIR="../../../armv8_testsuite/test/test_cases/generated"

#Path to outfile
OUT="./memdebug"

# Check if Valgrind is installed
if ! command -v valgrind &> /dev/null; then
    echo "Valgrind is not installed. Please install Valgrind to proceed."
    exit 1
fi

# Run Valgrind on each test case
#for test_case in "$TEST_CASES_DIR"/*; do
#    if [[ -f "$test_case" ]]; then
#        echo "Running Valgrind on test case: $test_case"
        
#        valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes $PROGRAM "$test_case" "$OUT" > "shifts.log" 2>&1
        
#        if [[ $? -eq 0 ]]; then
#            echo "Valgrind completed successfully for $test_case." 
#        else
#            echo "Valgrind encountered an error for $test_case."
#        fi
#    fi
#done

# Run Valgrind on each test case (recursive case)
find "$TEST_CASES_DIR" -type f | while read -r test_case; do
    if [[ -f "$test_case" ]]; then
        echo "Running Valgrind on test case: $test_case"
        
        # Redirect valgrind output to log file
        valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes "$PROGRAM" "$test_case" "$OUT" > "generated.log" 2>&1
        
        if [[ $? -eq 0 ]]; then
            echo "Valgrind completed successfully for $test_case. Check valgrind_$(basename "$test_case").log for details."
        else
            echo "Valgrind encountered an error for $test_case. Check valgrind_$(basename "$test_case").log for details."
        fi
    fi
done
