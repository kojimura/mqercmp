#!/bin/bash

# Simplify all MQ error log files in spesified directory
# usage: . amqercmp.sh /var/mqm/

logPath=$1

for fileName in `\find $logPath -name 'AMQERR0*.LOG'`; do

 fileAttr=$(file $fileName)

# check new line code 

 if echo "${fileAttr}" | grep 'CRLF' > /dev/null 2>&1 ; then
  Cmd="cat ${fileName} | tr -d '\r' |" 
 else
  Cmd="cat ${fileName} |"
 fi

# check character code for convertion

 case $fileAttr in
 *Non-ISO*)
  Cmd2="iconv -f SJIS |" ;;
 *ISO-8859*)
  Cmd2="iconv -f EUCJP |" ;;
 *)
  Cmd2="" ;;
 esac

 outFile=${fileName: -5:1}.txt
 echo "File:${fileName}" > $outFile
 eval ${Cmd}${Cmd2}mqercmp >> $outFile 

done
