#!/bin/bash

# Simplify all MQ error files in spesified directory
# usage: mqfdcawk.sh /var/mqm/errors/

#fPath=$1
#for fname in ${fPath}*.LOG; do
 fname=$1
 echo "${fname}"
# awk '{if($1 == /\d{2}.+?/){print $1 $2}}' < ${fname}
#cat ${fname} | grep ^[12][0-9] | awk '{print $1 $2}' 
#cat ${fname} | awk '($1 ~ /^[12][0-9]/) { print $1,$2 }' 
#cat ${fname} | awk '{if($1~/^[12][0-9]/) printf "%s %s ",$1,$2; else if($1~/AMQ/) print $0}' 
#cat ${fname} | awk '{if($1~/^[12][0-9]/){dt=$1; tm=$2;} else if($1~/AMQ/) printf "%s %s %s\n",$dt,$tm,$0}' 

cat ${fname} | 
awk '
BEGIN { flg=0 }
{
# print "flg=" flg
 if($1~/^[12][0-9]/ && $2~/^[012]/){
  if(flg==1) printf("\n")
  printf "%s %s ",$1,$2;
  flg=1;
 } 
 else if($1~/AMQ/){
  printf $0 
  if($0~/[。.]$/){
   flg=0
   printf("\n")
  }
  else{
   flg=2
  }
 }
 else if(flg==2){
  printf $0
  if($0~/[。.]$/){
   flg=0
   printf("\n")
  }
 }
}' 

#done
