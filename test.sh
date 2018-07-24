a=0
array=(zork bigzork turtle fluttershy helltrain bee_gees 42)

while [ $a -lt 7 ]
do
    ARG=${array[a]}
    echo 'testing' $ARG
    ./asm champs/$ARG.s && \
    mv ./champs/$ARG.cor ./champs/$ARG.my.cor && \
    ./asm_given champs/$ARG.s && \
    hexdump -C ./champs/$ARG.my.cor > ./results/$ARG.myresult && \
    hexdump -C ./champs/$ARG.cor > ./results/$ARG.hisresult && \
    echo "checking difference..." && \
    diff ./results/$ARG.hisresult ./results/$ARG.myresult && \
    echo "done"
   a=`expr $a + 1`
done