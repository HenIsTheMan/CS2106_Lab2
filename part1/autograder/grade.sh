#!/bin/bash

## I changed up the steps as I felt this way is clearer and perhaps more efficient

# [1 - 5] Input Validation
if [[ $# -ne 3 ]]; then # [1] Ensuring exactly 3 args
    echo "Usage: ./grade.sh <filename> <number_of_tests> <query_point>"
    exit 1
fi

numberOfTests=$2

if [[ $numberOfTests -le 0 ]]; then # [2] Ensuring $numberOfTests is valid
    echo "number_of_tests must be larger than 0"
    exit 1
fi

queryPt=$3

if [[ $queryPt -lt 0 ]]; then # [3] Ensuring $queryPt is valid
    echo "query_point must be larger than or equal 0"
    exit 1
fi

if [[ $queryPt -gt $numberOfTests ]]; then # [4] Ensuring $queryPt <= $numberOfTests
    echo "query_point must be less than or equal to the number_of_tests"
    exit 1
fi

testCaseCount=$(ls ref/*.in | wc -l)

if [[ $numberOfTests -gt $testCaseCount ]]; then # [5] Ensuring $numberOfTests <= number of test cases available
    let numberOfTests=$testCaseCount
fi

# [6] Ref Prog
refProgName=$1

gcc $(ls ref/*.c) -o $refProgName # [6] Compilation of Ref Prog

# [7] Deletion of Old Output Ref Files (if any)
rm -f ref/*.out

# [8] Generation of New Output Ref Files

# Now mark submissions

#
# Note: See Lab02Qn.pdf for format of output file. Marks will be deducted for missing elements.
#

# Iterate over every submission directory
    # Compile C code
    # Print compile error message to output file
    # Generate output from C code using *.in files in ref
    # Compare with reference output files  and award 1 mark if they are identical
    # Print the student submission with the score equals to query_point

# Print total students who have <qurey_score>.
    
