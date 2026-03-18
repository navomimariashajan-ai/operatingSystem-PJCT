#!/bin/bash
# Compile main.c which is in the same 'src' folder as this script
gcc src/main.c -o program

# Run your test case
output=$(echo "input_here" | ./program)

if [ "$output" == "expected_output" ]; then
  echo "✅ Pass"
  exit 0
else
  echo "❌ Fail"
  exit 1
fi
