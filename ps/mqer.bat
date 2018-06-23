@echo off
rem Simplify all MQ error log files in spesified directory.
rem usage: .\mqer.bat <path>
rem e.g.:  .\mqer.bat C:\ProgramData\IBM\MQ\qmgrs\QM1\errors

powershell -ExecutionPolicy RemoteSigned -File .\mqer.ps1 %1


