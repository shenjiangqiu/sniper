#!/bin/bash
files=`cat files.txt`
echo $files
for file in $files;do
    rm -rf $file;
    mkdir $file;
    cd $file;
    mkdir O0;
    cd O0;
    perf record ../../../glucose_debug ../../../cnfs/$file &
    cd ../;
    mkdir O3;
    cd O3;
    perf record ../../../glucose_release ../../../cnfs/$file&
    cd ../..;

done
