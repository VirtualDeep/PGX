echo 'Start building'
g++ Func.h main.cpp Func.cpp Interface.cpp freeze.cpp
mv a.out PGX.out
echo 'end'