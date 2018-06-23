#!/bin/bash

# Simplify all MQ error files in spesified directory
# usage: mqer.sh /var/mqm/errors/

fPath=$1
for fname in ${fPath}*.LOG; do
# echo "${fname}"
 awk -f mqercmp.awk ${fname} > ${fname: -5:1}.txt
done
