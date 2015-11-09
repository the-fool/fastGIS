#!/bin/bash
a=1
for i in *.rda; do
    new=$(printf "krig%04d.rda" "$a")
    mv -- "$i" "$new"
    ((a++))
done
