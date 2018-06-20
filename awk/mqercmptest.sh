# Simplify MQ error message into one line.
# usage: awk -f mqfdcawk.awk AMQERR01.LOG 

#cat ${fname} | 
#awk '
BEGIN { flag=0 }
{
 if(($1~/^[0-9]/ && $2~/^[012][0-9]/)){
  # date and time
  if(flag==1) printf("\n")
  printf "%s %s ",$1,$2;
  flag=1;
 } 
 if($1~/^(Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Sep|Oct|Nov|Dec)/){
  # date and time English, long, space separater
  if(flag==1) printf("\n")
  printf "%s %s %s %s ",$1,$2,$3,$4;
  flag=1;
 }
 else if($1~/AMQ/){
  # error code
  printf $0 
  if($0~/[。.]$/){
   # message end in a line
   flag=0
   printf("\n")
  }
  else{
   # message continue
   flag=2
  }
 }
 else if(flag==2){
  # message continuing
  printf $0
  if($0~/[。.]$/){
   # message end after several lines
   flag=0
   printf("\n")
  }
 }
}
#' 
