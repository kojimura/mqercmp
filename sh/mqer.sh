#!/bin/bash

# Simplify all MQ error files in spesified directory
# usage: mqer.sh /var/mqm/errors/

echo $0 $1 $2
ScriptDir=$(cd $(dirname $0); pwd)
echo $ScriptDir

fPath=$1
for fname in ${fPath}*.LOG; do
# echo "${fname}"
  awk -f ${ScriptDir}/mqercmp.awk ${fname} > ${fname: -5:1}.txt
done
