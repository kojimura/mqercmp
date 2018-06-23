#!/bin/bash

# Simplify all MQ error log files in spesified directory
# using bash calling Windows C program for SJIS CRLF text. 
# Summarize each error information into one line. 
# This bash script is written in UTF8 with LF for Windows Cygwin platform.

if [ "${1}" = "-h" -o "${1}" = "--help" ];
then
  echo "usage: bash mqercmp.sh <path>"
  echo "e.g.   bash mqercmp.sh /var/mqm/"
  echo "convert utf8, euc to sjis and LF to CRLF for calling Windows C program"
  exit 1
fi

logPath=$1

for fileName in `\find $logPath -name 'AMQERR0*.LOG'`; do

<< UNIX 
# for UNIX naitive bash

  fileAttr=$(file $fileName)

# check new line code 

  if echo "${fileAttr}" | grep 'CRLF' > /dev/null 2>&1 ; then
    Cmd="cat ${fileName} | tr -d '\r' |" 
  else
    Cmd="cat ${fileName} | perl -p -e 's/\n/\r\n/' |"
  fi

# check character code for convertion

  case $fileAttr in
  *UTF-8*)
    Cmd2="iconv -f UTF8 -t SJIS |" ;;
  *ISO-8859*)
    Cmd2="iconv -f EUCJP -t SJIS |" ;;
  *)
    Cmd2="" ;;
  esac
UNIX

# for Windows cygwin bash

  Cmd="cat ${fileName} | " 
  Cmd2="nkf -cs | " 

  outFile=${fileName: -5:1}.txt
  allFile=a.txt
  echo "File:${fileName}" > $outFile
  eval ${Cmd}${Cmd2}mqercmp >> $outFile 
  cat $outFile >> $allFile

done
