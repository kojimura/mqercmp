<#
Simplify all MQ FDC files in spesified directory
usage: .\mqercmp.ps1 C:\home\myprog\mqercmp\testdata
Set-ExecutionPolicy RemoteSigned
#>
Param( $p1 )
$f = Get-ChildItem $p1 -Filter *.LOG
foreach ($i in $f){
 echo $i.Name
 $out=$i.Name.Split('.')[0]
 $out=$out.Substring($out.Length - 1,1)+".txt"
 echo $out
 .\mqercmp2.ps1 $i.FullName > $out
}
