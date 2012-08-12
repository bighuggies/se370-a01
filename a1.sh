#!/bin/bash
t=(1, 2, 4, 8)

# Run this script with ./a1.sh [i] where i is the part of the assignment you wish to run.


# For each part of the assignment
for i in {0..3}
do
  
  # Compile the program
  gcc -pthread a1.$i.c -o a1.$i
  
  # Clear the file and write headers.
  filename="a1.$i.csv"
  : > $filename
  echo "Threads,Tickets Grabbed,Wall Clock,Usermode,Kernel,Context Switches" >> $filename

  # For each number of threads
  for j in "${t[@]}"
  do
    # Run the experiment five times
    for ((c=0;  $c < 5; c = $c + 1))
    do
      (/usr/bin/time -f ",%E,%U,%S,%c" ./a1.$i $j) &>> $filename
    done
  done
done
