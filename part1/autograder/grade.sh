#!/bin/bash

# [1] Check if we have enough and the right arguments
if [[ $# -ne 3 ]]; then # [1] Ensuring we have exactly 3 args
    echo "Usage: ./grade.sh <filename> <number_of_tests> <query_point>"
    exit 1
fi

if [[ $2 -le 0 ]]; then # [2] Ensuring number_of_tests is valid (not sure why the brief said "less than")
    echo "number_of_tests must be larger than 0"
    exit 1
fi

if [[ $3 -lt 0 ]]; then # [3] Ensuring query_point is valid
    echo "query_point must be larger than or equal 0"
    exit 1
fi

if [[ $3 -gt $2 ]]; then # [4] Ensuring query_point <= number_of_tests
    echo "query_point must be less than or equal to the number_of_tests"
    exit 1
fi

# [5] Making number_of_tests <= number of test cases available (I feel like this is the better sln but need to delete temp files)
# if [[ $2 -gt $(ls ref/*.in | wc -l) ]]; then
    # set $1 $(ls ref/*.in | wc -l) $3
    
    ## Debugging (can remove)
    ## echo $1
    ## echo $2
    ## echo $3
# fi

# [5] Making number_of_tests <= number of test cases available
ls ref/*.in > myTempFile
count=$(wc -l < myTempFile)

if [[ $2 -gt $count ]]; then
    set $1 $count $3
fi

# [5] Delete temporary files
rm myTempFile

# [6] Compile the reference program
gcc $(ls ref/*.c) -o fun

# Generate reference output files

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
    
