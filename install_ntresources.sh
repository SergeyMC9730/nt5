#!/bin/bash

echo Copying base resources

rm $1/ntresources -rf
rm $1/resources -rf
cp $2/src/resources $1 -rf
mv $1/resources $1/ntresources

touch $1/file2