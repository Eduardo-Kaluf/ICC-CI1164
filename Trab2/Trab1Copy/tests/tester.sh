#!/bin/bash

# This script runs a series of tests defined in test.dat.
# It compiles the code, loops through each test case, executes the solvers,
# prints the result for each case, and then cleans up.

# 1. Compile the C++ projects first
echo "--- Building project ---"
(cd .. && make debug)

# Check if the build was successful. If not, exit.
if [ $? -ne 0 ]; then
    echo "Build failed. Exiting script."
    exit 1
fi

# Define the input file containing all test cases
TEST_FILE="test.dat"

# 2. Loop through each line in the test data file
while IFS= read -r line || [[ -n "$line" ]]; do
    # Skip any empty lines in the test file
    if [ -z "$line" ]; then
        continue
    fi

    echo "============================================="
    echo "Processing test case: $line"
    echo "============================================="

    # Create a temporary file containing only the current line (test case)
    echo "$line" > current_case.dat

    # Get the matrix size 'n' from the first number in the line.
    # Using 'cut' is a robust way to extract the first field.
    n=$(echo "$line" | cut -d' ' -f1)
    echo "Extracted n = $n"

    # 3. Run the first solver using the single-line test case file
    # and pipe the output to a temporary file.
    ./../cgSolver < current_case.dat | tail -n $((n + 2)) > temp.dat

    # 4. Process the output for the second solver
    # Extract the first line of the result for the final output
    head -n 1 temp.dat > result.dat
    # Replace the first line of the temp file with 'n' for the next solver
    sed -i "1c$n" temp.dat

    # 5. Clear the screen, run the second solver, and show its output
    echo "--- Solver Output ---"
    ./Solver < temp.dat | sed '3,3!d'

    # 6. Show the final result for this test case
    echo "--- Result for this case ---"
    cat result.dat
    echo ""

done < "$TEST_FILE"

# 7. Clean up all the temporary files
echo "--- All tests complete. Cleaning up. ---"
rm -f result.dat temp.dat current_case.dat

# 8. Purge the build artifacts from the C++ project
(cd .. && make purge)
