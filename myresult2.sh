ARG="Backward" && ../../../../../../Downloads/vm_champs/asm ../../../../../\
../Downloads/vm_champs/champs/$ARG.s && ./asm ../../../../../../Downloads/vm_champs/champs/$ARG.s | rev | cut -c 2- | rev > ./results/$ARG.myresult && hexdump -C ../../../../../../Downloads/vm_champs/champs/$ARG.cor | cut -c 11- | rev | cut -c 20- | rev | sed -e '$d' > ./results/$ARG.hisresult && echo '\nchecking differences...\n' && diff ./results/$ARG.hisresult ./results/$ARG.myresult && echo 'done\n'