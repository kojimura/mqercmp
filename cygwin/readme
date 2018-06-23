Prgram:
 mqercmp

 For Cygwin environment, source file must be UTF8 LF.

Function:
 Compress MQ error log messages into one line for ease of reference.

Usuage:
 awk -f mqercmp.awk AMQERR01.LOG

Input data:                       
 Accept English and Japanese data format

1. Date Time
Japanese short format
2014/12/06 09:13:29 - Process(1972.3) User(koji) Program(amqzmuc0.exe)

Japanese long format
2017年10月07日 08時03分07秒 - Process(20505.1) User(root) Program(setmqinst)

Body, Japanese
AMQ7231: リカバリー・フェーズ中に、キュー・マネージャー 'myqmgr' で 0 ログ・レ
コードがアクセスされました。

Body, English
AMQ6209: An unexpected asynchronous signal (15 : SIGTERM) has been received and
ignored.

Body, more than two lines
AMQ5806: WebSphere MQ Publish/Subscribe
ブローカーがキュー・マネージャー qm1
に対して始動されました。

Output data:
2018/03/27 10:46:30 AMQ5026: The listener 'LISTENER.TCP' has started. ProcessId..
2018/03/31 07:28:09 AMQ6183: An internal WebSphere MQ error has occurred.
2018/03/31 07:28:09 AMQ6209: An unexpected asynchronous signal (15 : SIGTERM)..

Author:   Kouji Murakami
Date:     2018/06/19

ToDo:
Month Day Year, short
5/21/18 

Month Day Year, long, space separater
Jun 14 2018

process evry file in a directory

mqercmp.sh /var/mqm/errors/
