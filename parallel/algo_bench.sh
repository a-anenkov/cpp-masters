#!/bin/bash

set -x

./build/parallel/algo_bench -alg=reduce -policy=seq >& reduce.seq
./build/parallel/algo_bench -alg=reduce -policy=unseq >& reduce.unseq
./build/parallel/algo_bench -alg=reduce -policy=par >& reduce.par
./build/parallel/algo_bench -alg=reduce -policy=par_unseq >& reduce.par_unseq
./build/parallel/algo_bench -alg=transform -policy=seq >& transform.seq
./build/parallel/algo_bench -alg=transform -policy=unseq >& transform.unseq
./build/parallel/algo_bench -alg=transform -policy=par >& transform.par
./build/parallel/algo_bench -alg=transform -policy=par_unseq >& transform.par_unseq
./build/parallel/algo_bench -alg=sort -policy=seq >& sort.seq
./build/parallel/algo_bench -alg=sort -policy=unseq >& sort.unseq
./build/parallel/algo_bench -alg=sort -policy=par >& sort.par
./build/parallel/algo_bench -alg=sort -policy=par_unseq >& sort.par_unseq

gnuplot -persist -c ./parallel/algo_bench.plot
