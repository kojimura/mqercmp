<#
Simplify MQ error messages into one line.
usage: .\mqercmp.ps1 <input file> <output file>
e.g.:  Set-ExecutionPolicy RemoteSigned
       .\mqercmp.ps1 C:\ProgramData\IBM\MQ\qmgrs\QM1\AMQERR01.LOG 1.txt
batch: powershell -ExecutionPolicy RemoteSigned -File .\mqercmp.ps1 .\AMQERR01.LOG 1.txt
#>

Param( $p1, $p2 )

$d1=date
$buf="mqercmp.ps1 ${d1}"
Write-Output "$buf" | Out-File $p2 -Encoding default

cat $p1 | 
%{
  if($_ -match "^(\d+)/(\d+)/(\d+)" -or $_ -match "^(\d+)îN(\d+)åé(\d+)ì˙"){
  # date and time
    $date=$_.Split(' ')[0]
    $time=$_.Split(' ')[1]
    $flag=1
  }
  elseif($_.StartsWith("AMQ")){
  # error message
    $err=$_
    $buf=$date+' '+$time+' '+$err
    if($_.EndsWith("ÅB") -or $_.EndsWith(".")){
      # error message end
      Write-Output "$buf" | Out-File $p2 -Encoding default -Append
      $flag=0;
    }
    else{
    # errror message continue
      $flag=2
    }
  }
  elseif($flag -eq 2){
  # error message continueing
    $buf+=$_;
    if($_.EndsWith("ÅB") -or $_.EndsWith(".")){
      # error message end
      Write-Output "$buf" | Out-File $p2 -Encoding default -Append
      $flag=0
    }
  }
}

