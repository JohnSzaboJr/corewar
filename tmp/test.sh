a=0
array=(zork bigzork turtle fluttershy helltrain bee_gees toto tdc4b \
tdc3b tdc2b slider2 mortel maxidef jumper ex Torpilleb Survivor \
Octobre_Rouge_V4.2 Gagnant Deathb Backwards \
darksasuke champ DAVID misaka STIDAV _ addDAV addchp andDAV chp_sti \
dallas_super_champ ldOK \
ldi live_chp lld lldsti lldi lldif lldid lldif3 lldim sbuono skynet \
st stOK st_chp sub_chp subdav zorkdie Asombra Douceur_power \
youforkmytralala ultimate-surrender \
ultima terminator sam_2.0 salamahenagalabadoun run_Kitty_RUN \
overwatch mise_a_jour_windows95 meowluigi mandragore live littlepuppy \
justin_bee jinx gedeon dubo corelol casimir big_feet _honeybadger \
Varimathras THUNDER Rainbow_dash MarineKing Machine-gun Explosive_Kitty \
Wall)

while [ $a -lt 80 ]
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