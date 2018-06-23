@echo off
rem Simplify MQ error messages into one line calling Windows powershell script.
rem usage: .\mqercmp.bat <file>
rem e.g.:  .\mqercmp.bat .\AMQERR01.LOG 1.txt

rem echo %1 %2

powershell -ExecutionPolicy RemoteSigned -File .\mqercmp.ps1 %1 %2


