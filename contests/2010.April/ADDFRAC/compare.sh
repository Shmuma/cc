#!/bin/sh

./test < $1 > $$-1.txt
./bf < $1 > $$-2.txt

diff -Nru $$-1.txt $$-2.txt
rm -f $$-1.txt $$-2.txt