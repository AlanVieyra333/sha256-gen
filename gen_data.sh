#!/bin/bash

rm -f data.csv

for (( i=0; i<2000; ++i)); do
  hash=$(./gen_in_msg.a)
  ./sha256 $hash >> data.csv
done
