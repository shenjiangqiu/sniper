#!/bin/bash
files=`cat files.txt`
sniper_root=$HOME/git/sniper
echo $files
for file in $files;do
    rm -rf $file;
    mkdir $file;
    cd $file;

    $sniper_root/run-sniper --roi --no-cache-warming -n 1 -v -s branchflag   -- ../../glucose_release ../../cnfs/$file &

    

    cd ..

done
