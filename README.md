# mqercmp

Function: 
Compress WMQ error log messages to make it easy to see

Usuage: mqercmp
e.g. mqercmp < AMQERR01.LOG > err1.out

Input data: Accept English and Japanese data format

1. Date Time, Japanese short format
2014/12/06 09:13:29 - Process(1972.3) User(koji) Program(amqzmuc0.exe)

2. Date Time, Japanese long format
2017年10月07日 08時03分07秒 - Process(20505.1) User(root) Program(setmqinst)

3. Body, Japanese
AMQ7231: リカバリー・フェーズ中に、キュー・マネージャー 'myqmgr' で 0 ログ・レ
コードがアクセスされました。

4. Body, English
AMQ6209: An unexpected asynchronous signal (15 : SIGTERM) has been received and
ignored.

Output data: Simply one line for each error message log.
2018/03/27 10:46:30 AMQ5026: The listener 'LISTENER.TCP' has started. ProcessId..
2018/03/31 07:28:09 AMQ6183: An internal WebSphere MQ error has occurred.
2018/03/31 07:28:09 AMQ6209: An unexpected asynchronous signal (15 : SIGTERM)..

Make:
1. Linux/UNIX
gcc -o mqercmp mqercmp.c

2. Windows
cl -MD mqercmp.c -Femqercmp.exe

Note:
The result depends on a charset of a platform in which the program was built.
For instance, an input file might be UTF-8 with LR on Linx/UNIX, or SJIS with CRLF on Windows.
Otherwise the program cannot convert a file properly.
Use nkf or iconv for prepare proper charset of input file.

Troubleshooting:
Q. The program does not generate proper output.
A. Check your input file charset and new-line code.
For instance, if it is SJIS and CRLF on UNIX, try:
 nkf -w -Lu AMQERR01.LOG(sjis) | mqercmp > er1.txt
Or if it is UTF-8 and LF on Windows, try:
 nkf -u -Lw AMQERR01.LOG(utf8) | mqercmp > er1.txt

Author:   Kouji Murakami
Date:     2015/06/07
Modified: 2018/06/06
