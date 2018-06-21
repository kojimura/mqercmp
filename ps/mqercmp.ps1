Param( $p1 )
$f = Get-ChildItem $p1 -Filter *.LOG
foreach ($i in $f){
 $flag=0;
 echo $i.Name
 $out=$i.Name.Split('.')[0]
 $out=$out.Substring($out.Length - 1,1)+".txt"
 echo $out
 cat $i.FullName | %{
 if($_ -match "^(\d+)/(\d+)/(\d+)" -or $_ -match "^(\d+)年(\d+)月(\d+)日"){
   $date=$_.Split(' ')[0]
   $time=$_.Split(' ')[1]
   $flag=1
  }
  elseif($_.StartsWith("AMQ")){
   $err=$_
   $buf=$date+' '+$time+' '+$err
   if($_.EndsWith("。") -or $_.EndsWith(".")){
    Write-Output "$buf"
    $flag=0;
   }
   else{
    $flag=2
   }
  }
  elseif($flag -eq 2){
   $buf+=$_;
   if($_.EndsWith("。") -or $_.EndsWith(".")){
    Write-Output "$buf"
    $flag=0
   }
  }
 }
}
