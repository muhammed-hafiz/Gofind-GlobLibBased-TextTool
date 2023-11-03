echo Removing old build...
make clean; echo

echo Compiling...
make gofind; echo

echo Unit Test...

echo case 1
if  ./gofind ali hello | grep -q '/home/circle/Desktop/c.txt' 
 then
	echo passed; echo
else echo faild; echo
fi


echo case 2  
if ./gofind noha | grep -q "/home/circle/Desktop/d.txt"
 then
	echo passed; echo
else echo faild; echo
fi

echo case 3
if ./gofind limia | grep -q "/home/circle/Desktop/d.txt"
 then
	echo passed; echo
else echo faild; echo
fi

echo case 4 
if ! ./gofind limia hafiz | grep -q ""
 then
	echo passed; echo
else echo faild; echo
fi

echo case 5
if ./gofind -o limia hafiz | grep -q "/home/circle/Desktop/c.txt
/home/circle/Desktop/d.txt"
 then
	echo passed; echo
else echo faild; echo
fi
