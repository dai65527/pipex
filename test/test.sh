#!/bin/bash

echo -n "pipex tester: " > test.log
date "+%Y/%m/%d %H:%M:%S" >> test.log
echo >> test.log

if [ ! -x ../pipex ]; then
    echo "No pipex executable found. Compiling..." | tee -a test.log
    make pipex -C .. 
fi

RETURNVAL=0

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
    RETURNVAL=1
fi
diff out_ref.txt out_mine.txt >> test.log
if [ $? -eq 0 ]; then
    echo "        diff OK:)" | tee -a test.log
else
    echo "        diff KO:)" | tee -a test.log
    RETURNVAL=1
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
    RETURNVAL=1
fi
diff out_ref.txt out_mine.txt >> test.log
if [ $? -eq 0 ]; then
    echo "        diff OK:)" | tee -a test.log
else
    echo "        diff KO:)" | tee -a test.log
    RETURNVAL=1
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
    RETURNVAL=1
fi
diff out_ref.txt out_mine.txt >> test.log
if [ $? -eq 0 ]; then
    echo "        diff OK:)" | tee -a test.log
else
    echo "        diff KO:)" | tee -a test.log
    RETURNVAL=1
fi

echo "CASE: case1.txt /bin/cat \"/usr/bin/grep a\" out.txt" | tee -a test.log
< case1.txt /bin/cat | /usr/bin/grep a > out_ref.txt
RET_REF=$?
../pipex case1.txt /bin/cat "/usr/bin/grep a" out_mine.txt
RET_MINE=$?
if [ $RET_REF = $RET_MINE ]; then
    echo "  return val OK:)" | tee -a test.log
else
    echo "  return val KO:)" | tee -a test.log
    echo "REF: $RET_REF, MINE: $RET_MINE" >> test.log
    RETURNVAL=1
fi
diff out_ref.txt out_mine.txt >> test.log
if [ $? -eq 0 ]; then
    echo "        diff OK:)" | tee -a test.log
else
    echo "        diff KO:)" | tee -a test.log
    RETURNVAL=1
fi

echo "CASE: case1.txt \"grep a\" \"wc\" out.txt" | tee -a test.log
< case1.txt grep a | wc > out_ref.txt
RET_REF=$?
../pipex case1.txt "grep a" wc out_mine.txt
RET_MINE=$?
if [ $RET_REF = $RET_MINE ]; then
    echo "  return val OK:)" | tee -a test.log
else
    echo "  return val KO:)" | tee -a test.log
    echo "REF: $RET_REF, MINE: $RET_MINE" >> test.log
    RETURNVAL=1
fi
diff out_ref.txt out_mine.txt >> test.log
if [ $? -eq 0 ]; then
    echo "        diff OK:)" | tee -a test.log
else
    echo "        diff KO:)" | tee -a test.log
    RETURNVAL=1
fi

# ERROR CASES
echo "CASE: error: filenofound cat cat out.txt" | tee -a test.log
2> out_error_ref.log < filenofound cat | cat > out_ref.txt
RET_REF=$?
../pipex filenofound cat cat out_mine.txt 2> out_error_mine.log
RET_MINE=$?
if [ $RET_REF = $RET_MINE ]; then
    echo "  return val OK:)" | tee -a test.log
else
    echo "  return val KO:)" | tee -a test.log
    echo "REF: $RET_REF, MINE: $RET_MINE" >> test.log
    RETURNVAL=1
fi
diff out_ref.txt out_mine.txt >> test.log
if [ $? -eq 0 ]; then
    echo "        diff OK:)" | tee -a test.log
else
    echo "        diff KO:)" | tee -a test.log
    RETURNVAL=1
fi
sed -ie "s/\.\/test\.sh: line [0-9]*/pipex/" out_error_ref.log
diff out_error_ref.log out_error_mine.log >> test.log
if [ $? -eq 0 ]; then
    echo "  error diff OK:)" | tee -a test.log
else
    echo "  error diff KO:)" | tee -a test.log
    RETURNVAL=1
fi

echo "CASE: error: case1.txt nonexistingcmd cat out.txt" | tee -a test.log
2> out_error_ref.log < case1.txt nonexistingcmd | cat > out_ref.txt
RET_REF=$?
../pipex case1.txt nonexistingcmd cat out_mine.txt 2> out_error_mine.log
RET_MINE=$?
if [ $RET_REF = $RET_MINE ]; then
    echo "  return val OK:)" | tee -a test.log
else
    echo "  return val KO:)" | tee -a test.log
    echo "REF: $RET_REF, MINE: $RET_MINE" >> test.log
    RETURNVAL=1
fi
diff out_ref.txt out_mine.txt >> test.log
if [ $? -eq 0 ]; then
    echo "        diff OK:)" | tee -a test.log
else
    echo "        diff KO:)" | tee -a test.log
    RETURNVAL=1
fi
sed -ie "s/\.\/test\.sh: line [0-9]*/pipex/" out_error_ref.log
diff out_error_ref.log out_error_mine.log >> test.log
if [ $? -eq 0 ]; then
    echo "  error diff OK:)" | tee -a test.log
else
    echo "  error diff KO:)" | tee -a test.log
    RETURNVAL=1
fi

echo "CASE: error: case1.txt cat nonexistingcmd out.txt" | tee -a test.log
< case1.txt cat | 2> out_error_ref.log nonexistingcmd > out_ref.txt 
RET_REF=$?
../pipex case1.txt cat nonexistingcmd out_mine.txt 2> out_error_mine.log
RET_MINE=$?
if [ $RET_REF = $RET_MINE ]; then
    echo "  return val OK:)" | tee -a test.log
else
    echo "  return val KO:)" | tee -a test.log
    echo "REF: $RET_REF, MINE: $RET_MINE" >> test.log
    RETURNVAL=1
fi
diff out_ref.txt out_mine.txt >> test.log
if [ $? -eq 0 ]; then
    echo "        diff OK:)" | tee -a test.log
else
    echo "        diff KO:)" | tee -a test.log
    RETURNVAL=1
fi
sed -ie "s/\.\/test\.sh: line [0-9]*/pipex/" out_error_ref.log
diff out_error_ref.log out_error_mine.log >> test.log
if [ $? -eq 0 ]; then
    echo "  error diff OK:)" | tee -a test.log
else
    echo "  error diff KO:)" | tee -a test.log
    RETURNVAL=1
fi

echo "CASE: error: case1.txt cat forbidden.txt" | tee -a test.log
< case1.txt cat | 2> out_error_ref.log cat > forbidden.txt 
RET_REF=$?
../pipex case1.txt cat cat forbidden.txt 2> out_error_mine.log
RET_MINE=$?
if [ $RET_REF = $RET_MINE ]; then
    echo "  return val OK:)" | tee -a test.log
else
    echo "  return val KO:)" | tee -a test.log
    echo "REF: $RET_REF, MINE: $RET_MINE" >> test.log
    RETURNVAL=1
fi
diff out_ref.txt out_mine.txt >> test.log
if [ $? -eq 0 ]; then
    echo "        diff OK:)" | tee -a test.log
else
    echo "        diff KO:)" | tee -a test.log
    RETURNVAL=1
fi
sed -ie "s/\.\/test\.sh: line [0-9]*/pipex/" out_error_ref.log
diff out_error_ref.log out_error_mine.log >> test.log
if [ $? -eq 0 ]; then
    echo "  error diff OK:)" | tee -a test.log
else
    echo "  error diff KO:)" | tee -a test.log
    RETURNVAL=1
fi

echo "CASE: error: case1.txt /bin/nonexistingcmd cat out.txt" | tee -a test.log
2> out_error_ref.log < case1.txt /bin/nonexistingcmd | cat > out_ref.txt
RET_REF=$?
../pipex case1.txt /bin/nonexistingcmd cat out_mine.txt 2> out_error_mine.log
RET_MINE=$?
if [ $RET_REF = $RET_MINE ]; then
    echo "  return val OK:)" | tee -a test.log
else
    echo "  return val KO:)" | tee -a test.log
    echo "REF: $RET_REF, MINE: $RET_MINE" >> test.log
    RETURNVAL=1
fi
diff out_ref.txt out_mine.txt >> test.log
if [ $? -eq 0 ]; then
    echo "        diff OK:)" | tee -a test.log
else
    echo "        diff KO:)" | tee -a test.log
    RETURNVAL=1
fi
sed -ie "s/\.\/test\.sh: line [0-9]*/pipex/" out_error_ref.log
diff out_error_ref.log out_error_mine.log >> test.log
if [ $? -eq 0 ]; then
    echo "  error diff OK:)" | tee -a test.log
else
    echo "  error diff KO:)" | tee -a test.log
    RETURNVAL=1
fi

echo "CASE: error: case1.txt cat /bin/nonexistingcmd out.txt" | tee -a test.log
< case1.txt cat | 2> out_error_ref.log /bin/nonexistingcmd > out_ref.txt 
RET_REF=$?
../pipex case1.txt cat /bin/nonexistingcmd out_mine.txt 2> out_error_mine.log
RET_MINE=$?
if [ $RET_REF = $RET_MINE ]; then
    echo "  return val OK:)" | tee -a test.log
else
    echo "  return val KO:)" | tee -a test.log
    echo "REF: $RET_REF, MINE: $RET_MINE" >> test.log
    RETURNVAL=1
fi
diff out_ref.txt out_mine.txt >> test.log
if [ $? -eq 0 ]; then
    echo "        diff OK:)" | tee -a test.log
else
    echo "        diff KO:)" | tee -a test.log
    RETURNVAL=1
fi
sed -ie "s/\.\/test\.sh: line [0-9]*/pipex/" out_error_ref.log
diff out_error_ref.log out_error_mine.log >> test.log
if [ $? -eq 0 ]; then
    echo "  error diff OK:)" | tee -a test.log
else
    echo "  error diff KO:)" | tee -a test.log
    RETURNVAL=1
fi

if [ $RETURNVAL = 0 ]; then
    echo "ALL TEST PASSED OK :)"
else
    echo "FAILED TEST KO :("
fi

if [ "$1" != "bonus" ]; then
    exit $RETURNVAL
fi

echo
echo "<< CHECK BONUS >>"
make bonus -C .. > /dev/null

# test bonus
echo "CASE: case1.txt cat cat cat out.txt" | tee -a test.log
< case1.txt cat | cat | cat > out_ref.txt
RET_REF=$?
../pipex case1.txt cat cat cat out_mine.txt
RET_MINE=$?
if [ $RET_REF = $RET_MINE ]; then
    echo "  return val OK:)" | tee -a test.log
else
    echo "  return val KO:)" | tee -a test.log
    echo "REF: $RET_REF, MINE: $RET_MINE" >> test.log
    RETURNVAL=1
fi
diff out_ref.txt out_mine.txt >> test.log
if [ $? -eq 0 ]; then
    echo "        diff OK:)" | tee -a test.log
else
    echo "        diff KO:)" | tee -a test.log
    RETURNVAL=1
fi

echo "CASE: case1.txt cat \"grep h\" \"grep s\" nc out.txt" | tee -a test.log
< case1.txt cat | grep h | grep s | wc > out_ref.txt
RET_REF=$?
../pipex case1.txt cat "grep h" "grep s" wc out_mine.txt
RET_MINE=$?
if [ $RET_REF = $RET_MINE ]; then
    echo "  return val OK:)" | tee -a test.log
else
    echo "  return val KO:)" | tee -a test.log
    echo "REF: $RET_REF, MINE: $RET_MINE" >> test.log
    RETURNVAL=1
fi
diff out_ref.txt out_mine.txt >> test.log
if [ $? -eq 0 ]; then
    echo "        diff OK:)" | tee -a test.log
else
    echo "        diff KO:)" | tee -a test.log
    RETURNVAL=1
fi

echo "CASE: case1.txt cat .. cat out.txt" | tee -a test.log
< case1.txt cat | cat | cat | cat | cat | cat | cat | cat | cat | cat > out_ref.txt
RET_REF=$?
../pipex case1.txt cat cat cat cat cat cat cat cat cat cat out_mine.txt
RET_MINE=$?
if [ $RET_REF = $RET_MINE ]; then
    echo "  return val OK:)" | tee -a test.log
else
    echo "  return val KO:)" | tee -a test.log
    echo "REF: $RET_REF, MINE: $RET_MINE" >> test.log
    RETURNVAL=1
fi
diff out_ref.txt out_mine.txt >> test.log
if [ $? -eq 0 ]; then
    echo "        diff OK:)" | tee -a test.log
else
    echo "        diff KO:)" | tee -a test.log
    RETURNVAL=1
fi

if [ $RETURNVAL = 0 ]; then
    echo "ALL TEST PASSED OK :)"
else
    echo "FAILED TEST KO :("
fi

exit $RETURNVAL
