#!/usr/bin/env bash
set -euo pipefail

# Check if the correct number of arguments is passed
if [ "$#" -lt 1 ] || [ "$#" -gt 2 ]; then
    echo "Usage: $0 <a|b>"
    exit 1
fi

arg=$1
optional_arg=${2:-notfull}

latest_day_folder=$(ls -d Day* 2>/dev/null | sort -V | tail -n 1)
# Navigate to the Day1 folder
cd $latest_day_folder || { echo "Directory 'Day1' not found!"; exit 1; }

# Construct the source file name and output binary name based on the argument
source_file="${arg}.cpp"
output_binary="${arg}"

clang++ -std=c++20 -Xpreprocessor -fopenmp "$source_file" -o "$output_binary" -lomp $(echo ${LDFLAGS})

if [ $? -eq 0 ]; then
    echo "Compiled"
    if [[ "$optional_arg" == "full" ]]; then
        ./"$output_binary" < input_full
    else
        ./"$output_binary" < input
    fi
else
    echo "Compilation failed."
    exit 1
fi
