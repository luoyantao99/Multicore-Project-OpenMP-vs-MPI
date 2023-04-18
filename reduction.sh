
# waitsec=1
# echo "running...... please wait"  $waitsec "S"

tr=64
size=1000000
# datestring=$(date +%m-%dT%H:%M:%S)

for i in {1..10}
do
    # scriptname="reduction_OpenMP_${tr}_${size}"
    # file="./logs/${scriptname}_${datestring}.log"
    # echo $file

    echo "$(date +%m-%dT%H:%M:%S): running OpenMP ${tr} ${size} ...... please wait"
    time ./reduction_OpenMP $tr $size 2>&1 | tee -a $file

    # echo "running...... please wait" $waitsec "S" 
    # sleep $waitsec
done


for i in {1..10}
do
    # scriptname="reduction_MPI_${tr}_${size}"
    # file="./logs/${scriptname}_${datestring}.log"
    # echo $file

    echo "$(date +%m-%dT%H:%M:%S): running MPI ${tr} ${size} ...... please wait"
    time mpiexec -n $tr ./reduction_MPI $size 2>&1 | tee -a $file

    # echo "running...... please wait" $waitsec "S" 
    # sleep $waitsec
done