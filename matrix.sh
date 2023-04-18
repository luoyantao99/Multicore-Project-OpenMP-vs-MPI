
datestring=$(date +%m-%dT%H:%M:%S)

for tr in {2,4,8,16,32,64}
do
    for size in {250,500,1000,2000}
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


for tr in {2,4,8,16,32,64}
do
    for size in {250,500,1000,2000}
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


echo "matrix benchmark finished"
