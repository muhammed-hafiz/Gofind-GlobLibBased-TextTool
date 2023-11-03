echo Removing old build...
make clean; echo

echo Compiling...
make all; echo

echo Unit Test...

echo case 1
if  ./bin/gofind ali hello | grep -q 'tests/path_c/c.txt' 
 then
	echo passed; echo
else echo faild; echo
fi


echo case 2  
if ./bin/gofind noha | grep -q "tests/path_c/path_d/d.txt"
 then
	echo passed; echo
else echo faild; echo
fi

echo case 3
if ./bin/gofind limia | grep -q "tests/path_c/path_d/d.txt"
 then
	echo passed; echo
else echo faild; echo
fi

echo case 4 
if ! ./bin/gofind limia hafiz | grep -q ""
 then
	echo passed; echo
else echo faild; echo
fi

echo case 5
if ./bin/gofind -o limia hafiz | grep -q "tests/path_c/c.txt
	tests/path_c/path_d/d.txt"
 then
	echo passed; echo
else echo faild; echo
fi
