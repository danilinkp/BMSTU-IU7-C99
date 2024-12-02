#!/bin/bash

count_errors=0

pos_files="../data/pos_??_in.txt"
for pos_file_in in $pos_files; do
	number_of_test=$(echo "$pos_file_in" | grep -o "[0-9]*")
	if [ -z "$number_of_test" ]; then 
		break
	fi
	pos_file_out="../data/pos_""$number_of_test""_out.txt"
	pos_file_args="../data/pos_""$number_of_test""_args.txt"
	if [ -f "$pos_file_args" ]; then
	  command="./pos_case.sh ""$pos_file_in ""$pos_file_out" "$pos_file_args"
	else
	  command="./pos_case.sh ""$pos_file_in ""$pos_file_out"
	fi

	$command
	error="$?"

	if [ "$error" -eq 0 ]; then
		echo "POS TEST ""$number_of_test"": PASSED"
	else
		echo "POS TEST ""$number_of_test"": FAILED"
		count_errors=$((count_errors + 1))
	fi
done

neg_files="../data/neg_??_in.txt"
for neg_file_in in $neg_files; do
	number_of_test=$(echo "$neg_file_in" | grep -o "[0-9]*")
	if [ -z "$number_of_test" ]; then 
		break
	fi

	neg_file_out="../data/neg_""$number_of_test""_out.txt"
  neg_file_args="../data/neg_""$number_of_test""_args.txt"
  if [ -f "$neg_file_out" ]; then
  	if [ -f "$neg_file_args" ]; then
  	  command="./neg_case.sh ""$neg_file_in ""$neg_file_out ""$neg_file_args"
  	else
  	  command="./neg_case.sh ""$neg_file_in ""$neg_file_out"
  	fi
  else
    command="./neg_case.sh ""$neg_file_in"
  fi

	$command
	error="$?"

	if [ "$error" -eq 0 ]; then
		echo -e "NEG TEST ""$number_of_test"": PASSED"
	else
		echo -e "NEG TEST ""$number_of_test"": FAILED"
		count_errors=$((count_errors + 1))
	fi
done

echo "Number of failed tests: $count_errors"

exit "$count_errors"