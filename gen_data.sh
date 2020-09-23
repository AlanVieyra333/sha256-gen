#!/bin/bash

rm -f data.csv

for (( i=0; i<200; ++i)); do
  hash=$(./gen_in_msg.a)
  ./sha256-breakdown.a $hash >> data.csv
done
