clear
gcc ./src/master.c -lm -lrt  -o ./bin/master
gcc ./src/processAc.c -lbmp -lncurses -lm -lrt -o ./bin/processAc
gcc ./src/processAs.c -lbmp -lncurses -lm -lrt -o ./bin/processAs
gcc ./src/processB.c -lbmp -lncurses -lm -lrt -o ./bin/processB
./bin/master
