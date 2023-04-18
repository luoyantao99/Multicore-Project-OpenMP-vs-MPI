
datestring=$(date +%m-%dT%H:%M:%S)

for tr in {2,4,8,16,32}
do
    for size in {10000000,100000000,500000000,1000000000}
    do
        for i in {1..10}
        do
            scriptname="matrix_OpenMP_${tr}_${size}"
            file="./logs/${scriptname}_${datestring}.log"

            echo "$(date +%m-%dT%H:%M:%S): running OpenMP ${tr} ${size} iteration #${i} ...... please wait"
            { ./matrix_OpenMP $tr $size; } 2>&1 | tee -a $file

        done
    done
done


for tr in {2,4,8,16,32}
do
    for size in {10000000,100000000,500000000,1000000000}
    do
        for i in {1..10}
        do
            scriptname="matrix_MPI_${tr}_${size}"
            file="./logs/${scriptname}_${datestring}.log"

            echo "$(date +%m-%dT%H:%M:%S): running MPI ${tr} ${size} iteration #${i} ...... please wait"
            { mpiexec -n $tr ./matrix_MPI $size; } 2>&1 | tee -a $file

        done
    done
done
