<#
Simplify all MQ error log files in spesified directory
usage: .\mqer.ps1 <path>
e.g.:  Set-ExecutionPolicy RemoteSigned
       .\mqer.ps1 C:\ProgramData\IBM\MQ\qmgrs\QM1\errors
batch: powershell -ExecutionPolicy RemoteSigned -File .\mqer.ps1 C:\ProgramData\IBM\MQ\qmgrs\QM1\errors
#>
Param( $p1 )
$f = Get-ChildItem $p1 -Filter AMQERR0*.LOG

$allFile="a.txt"
#date | Out-File  ${allFile} -Encoding default

foreach ($i in $f){
  $outFile=$i.Name.Split('.')[0]
  $outFile=$outFile.Substring($outFile.Length - 1,1)+".txt"
  Write-Output $i.FullName | Out-File ${allFile} -Encoding default -Append
  .\mqercmp.ps1 $i.FullName "${outFile}"
  Get-Content "${outFile}" | Add-Content "${allFile}" -encoding String
}

