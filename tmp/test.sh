a=0
array=(zork bigzork turtle fluttershy helltrain bee_gees 42 toto tdc4b \
tdc3b tdc2b slider2 new2 mortel maxidef matb leeloob lde jumper ex barriere \
Torpilleb Survivor Octobre_Rouge_V4.2 Gagnant Deathb Car Backwards zork_error2 \
darksasuke champ DAVID misaka STIDAV _ addDAV addchp andDAV chp_sti \
dallas_super_champ jump2battrain jump2mur jump3 jump_chp ldOK ld_chp \
ldi live_chp lld lldsti lldi lldif lldid lldif3 lldim rouo sbuono skynet \
st stOK st_chp sub_chp subdav zorkdie)

while [ $a -lt 64 ]
do
    ARG=${array[a]}
    echo 'testing:'"\033[33m" $ARG.s "\033[0m"
    ../asm/asm champs/$ARG.s && \
    mv ./champs/$ARG.cor ./champs/$ARG.my.cor && \
    ./asm_given champs/$ARG.s && \
    hexdump -C ./champs/$ARG.my.cor > ./results/$ARG.myresult && \
    hexdump -C ./champs/$ARG.cor > ./results/$ARG.hisresult && \
    echo "checking difference..." && \
    echo "\033[31m" && \
    diff ./results/$ARG.hisresult ./results/$ARG.myresult && \
    echo "\033[0m"
    echo "\033[32m""done" "\033[0m"
    echo "-----------------------------------------"
   a=`expr $a + 1`
done