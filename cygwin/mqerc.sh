#!/bin/bash

# Simplify all MQ error files in spesified directory calling awk.
# For Windows Cygwin platform.
# usage: bash mqerc.sh <parh>
# e.g.   bash mqerc.sh /cygdrive/c/ProgramData/IBM/MQ/qmgrs/QM1/errors
# output file will be UTF8 LF
# This script must be with UTF8 LF

fPath=$1

allFile=0.txt
echo `date '+%F'` "mqerc.sh: MQ Error Log Summary" > ${allFile}
for fname in ${fPath}/*.LOG; do
  outFile=${fname: -5:1}.txt
  echo "${fname} => ${outFile}" >> ${allFile}
  cat ${fname} | nkf -wd | awk -f mqercmp.awk > ${outFile}
  cat ${outFile} >> ${allFile}
done
