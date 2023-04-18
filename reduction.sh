
# waitsec=1
# echo "running...... please wait"  $waitsec "S"

datestring=$(date +%m-%dT%H:%M:%S)

for tr in {2,4,8,16,32}
do
    for size in {10000000,100000000,500000000,1000000000}
    do
        for i in {1..10}
        do
            scriptname="reduction_OpenMP_${tr}_${size}"
            file="./logs/${scriptname}_${datestring}.log"
            # echo $file

            echo "${datestring}: running OpenMP ${tr} ${size} ...... please wait"
            { ./reduction_OpenMP $tr $size; } 2>&1 | tee -a $file

            # echo "running...... please wait" $waitsec "S" 
            # sleep $waitsec
        done
    done
done


for tr in {2,4,8,16,32}
do
    for size in {10000000,100000000,500000000,1000000000}
    do
        for i in {1..10}
        do
            scriptname="reduction_MPI_${tr}_${size}"
            file="./logs/${scriptname}_${datestring}.log"
            # echo $file

            echo "${datestring}: running MPI ${tr} ${size} ...... please wait"
            { mpiexec -n $tr ./reduction_MPI $size; } 2>&1 | tee -a $file

            # echo "running...... please wait" $waitsec "S" 
            # sleep $waitsec
        done
    done
done
