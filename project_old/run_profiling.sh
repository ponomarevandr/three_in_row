#!/usr/bin/env bash

cd "$(dirname $0)"
./build_profiling.sh
if [ $? -ne 0 ]; then
	exit 1
fi

echo "==================== Running the program..."
cd bin
./three_in_row $@

echo "==================== Running profiling..."
gprof ./three_in_row $@ > profile.txt
gprof2dot profile.txt | dot -Tsvg -o profile.svg