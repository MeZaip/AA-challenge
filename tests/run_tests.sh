#!/bin/bash
cd ../src
make clean; make
cd ../tests
make clean; make

PROGRAMS="../src"

for testfile in $(ls ./*.txt | sort -V); do
    echo "=== Test: $testfile ==="
    for prog in "$PROGRAMS"/*; do
        name=$(basename "$prog")
        if [[ "$name" == "backtracking" || "$name" == "dynamic" ]]; then
            echo "Running program: $(basename "$prog")"
            start=$(date +%s%3N)

            "$prog" "$testfile" &
            pid=$!

            while kill -0 "$pid" 2>/dev/null; do
                now=$(date +%s%3N)
                elapsed=$((now - start))

                if (( elapsed > 30000 )); then
                    echo "Timeout after ${elapsed} ms"
                    kill -9 "$pid"
                    break
                fi

                sleep 0.1
            done

            end=$(date +%s%3N)
            echo "Time: $((end - start)) ms"
        fi
    done
    echo
done

make clean
cd ../src
make clean
