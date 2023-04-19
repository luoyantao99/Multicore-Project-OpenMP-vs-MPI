
# waitsec=1
# echo "running...... please wait"  $waitsec "S"

datestring=$(date +%m-%dT%H:%M:%S)

for tr in {4,32}
do
    for size in {1000000,10000000,50000000,100000000}
    do
        for i in {1..10}
        do
            scriptname="reduction_OpenMP_${tr}_${size}"
            file="./logs/${scriptname}_${datestring}.log"
            # echo $file

            echo "$(date +%m-%dT%H:%M:%S): running OpenMP ${tr} ${size} iteration #${i} ...... please wait"
            { ./reduction_OpenMP $tr $size; } 2>&1 | tee -a $file

            # echo "running...... please wait" $waitsec "S" 
            # sleep $waitsec
        done
    done
done


for tr in {4,32}
do
    for size in {1000000,10000000,50000000,100000000}
    do
        for i in {1..10}
        do
            scriptname="reduction_MPI_${tr}_${size}"
            file="./logs/${scriptname}_${datestring}.log"
            # echo $file

            echo "$(date +%m-%dT%H:%M:%S): running MPI ${tr} ${size} iteration #${i} ...... please wait"
            { mpiexec -n $tr ./reduction_MPI $size; } 2>&1 | tee -a $file

            # echo "running...... please wait" $waitsec "S" 
            # sleep $waitsec
        done
    done
done


echo "reduction benchmark finished"
