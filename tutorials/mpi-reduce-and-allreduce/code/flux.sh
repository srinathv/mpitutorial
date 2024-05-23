#!/usr/bin/env bash


EXES="reduce_avg  reduce_int64_t_stddev  reduce_stddev"
num_elems=100
num_iterations=1000
for name in ${EXES}
do 
  flux submit -N 4 -n 16 --output=${name}_{{id}}.out --error=${name}_{{id}}.err ./$name $num_elems $num_iterations
done
