<#
Simplify all MQ FDC files in spesified directory
usage: .\mqercmp.ps1 C:\home\myprog\mqercmp\testdata
#>
Param( $p1 )
$f = Get-ChildItem $p1 -Filter *.LOG
foreach ($i in $f){
 $flag=0;
 echo $i.Name
 cat $i.FullName | %{
 if($_ -match "^(\d+)/(\d+)/(\d+)" -or $_ -match "^(\d+)年(\d+)月(\d+)日"){
   $d1=$_.Split(' ')[0];
   $d2=$_.Split(' ')[1];
   $flag=1;
  }
  elseif($_.StartsWith("AMQ")){
   $d3=$_;
   Write-Output -NoEnumerate "$d1 $d2 $d3";
   if($_.EndsWith("。") -or $_.EndsWith(".")){
<#    Write-Output ""; #>
    $flag=0;
   }
   else{
    $flag=2;
   }
  }
  elseif($flag -eq 2){
   Write-Output -NoEnumerate $_;
   if($_.EndsWith("。") -or $_.EndsWith(".")){
<#    Write-Output "";#>
    $flag=0;
   }
  }
 }
}
<# buf末尾に追加すべき #>
