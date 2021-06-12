#!/bin/bash

echo -n "pipex tester: " > test.log
date "+%Y/%m/%d %H:%M:%S" >> test.log
echo >> test.log

if [ ! -x ../pipex ]; then
    echo "No pipex executable found. Compiling..." | tee -a test.log
    make pipex -C .. 
fi

echo "CASE: case1.txt cat cat out.txt" | tee -a test.log
< case1.txt cat | cat > out_ref.txt
RET_REF=$?
../pipex case1.txt cat cat out_mine.txt
RET_MINE=$?
if [ $RET_REF = $RET_MINE ]; then
    echo "  return val OK:)" | tee -a test.log
else
    echo "  return val KO:)" | tee -a test.log
    echo "REF: $RET_REF, MINE: $RET_MINE" >> test.log
fi
diff out_ref.txt out_mine.txt >> test.log
if [ $? -eq 0 ]; then
    echo "        diff OK:)" | tee -a test.log
else
    echo "        diff KO:)" | tee -a test.log
fi

echo "CASE: case1.txt cat \"grep k\" out.txt" | tee -a test.log
< case1.txt cat | grep k > out_ref.txt
RET_REF=$?
../pipex case1.txt cat "grep k" out_mine.txt
RET_MINE=$?
if [ $RET_REF = $RET_MINE ]; then
    echo "  return val OK:)" | tee -a test.log
else
    echo "  return val KO:)" | tee -a test.log
    echo "REF: $RET_REF, MINE: $RET_MINE" >> test.log
fi
diff out_ref.txt out_mine.txt >> test.log
if [ $? -eq 0 ]; then
    echo "        diff OK:)" | tee -a test.log
else
    echo "        diff KO:)" | tee -a test.log
fi

echo "CASE: case1.txt cat \"grep z\" out.txt" | tee -a test.log
< case1.txt cat | grep z > out_ref.txt
RET_REF=$?
../pipex case1.txt cat "grep z" out_mine.txt
RET_MINE=$?
if [ $RET_REF = $RET_MINE ]; then
    echo "  return val OK:)" | tee -a test.log
else
    echo "  return val KO:)" | tee -a test.log
    echo "REF: $RET_REF, MINE: $RET_MINE" >> test.log
fi
diff out_ref.txt out_mine.txt >> test.log
if [ $? -eq 0 ]; then
    echo "        diff OK:)" | tee -a test.log
else
    echo "        diff KO:)" | tee -a test.log
fi
