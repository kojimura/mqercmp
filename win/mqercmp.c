/******************************************************************************/
/*                                                                            */
/* Program name: mqercmp                                                      */
/*                                                                            */
/* Function: Compress MQ error log messages for ease of reference             */
/*                                                                            */
/* Usuage: mqercmp                                                            */
/*  e.g.   mqercmp < AMQERR01.LOG > er1.out                                   */
/*                                                                            */
/* Input data:                                                                */
/*  Accept English and Japanese data format                                   */
/*  1. Date Time, Japanese short format                                       */
/*   2014/12/06 09:13:29 -                                                    */
/*  2. Date Time, Japanese long format                                        */
/*   2014îN10åé07ì˙ 08éû03ï™07ïb -                                            */
/*  3. Body, Japanese                                                         */
/*   AMQnnnn: DBCS characters will end with "ÅB"                              */
/*  4. Body, English                                                          */
/*   AMQnnnn: SBCS characters will end with "."                               */
/*                                                                            */
/* Output data:                                                               */
/*  2018/03/27 10:46:30 AMQ5026: The listener 'LISTENER.TCP' has started..    */
/*  2018/03/31 07:28:09 AMQ6183: An internal WebSphere MQ error has occurred. */
/*  2018/03/31 07:28:09 AMQ6209: An unexpected asynchronous signal..          */
/*                                                                            */
/* Note:                                                                      */
/*  It depends on a charset of a platform in which the program was built.     */
/*  e.g.) Input file might be UTF-8 with LR on Linx/UNIX, or SJIS with CRLF   */
/*  on Windows. Otherwise the program cannot convert a file properly. Use nkf */
/*  or iconv for preparing proper charset of input file, if necessary.        */ 
/*                                                                            */
/* Author:   Kouji Murakami                                                   */
/* Date:     2015/06/07                                                       */
/* Modified: 2018/05/23                                                       */
/*                                                                            */
/******************************************************************************/
#define   DEBUG     0

#define   IBUF_LEN  256   // input buffer length
#define   OBUF_LEN  4096  // output buffer length
#define   DTIME_LEN 34    // Date time length. enough for Japanese long format

#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <ctype.h>

int main( int argc, char **argv )
{
 char ibuf[IBUF_LEN], obuf[OBUF_LEN], *p;        // input buffer, output buffer

 while(fgets(ibuf, IBUF_LEN-1, stdin)){
    if(DEBUG) printf("DBG.in* %s\n", ibuf);
    if(isdigit(ibuf[0])){                        // should be Date & Time
       if(DEBUG) printf("DBG.digit* %c\n", ibuf[0]);
       strncpy(obuf, ibuf, DTIME_LEN);           // get Date & Time
       p = strchr(obuf, ' ');                    // space between Date & Time
       if(p) p = strchr(++p, ' ');               // second space following Time
       else continue;                            // not Date & Time, ignore!
    } else if(!strncmp(ibuf, "AMQ", 3)){         // found a code AMQxxxx!
       if(DEBUG) printf("DBG.AMQ!\n");
       strcpy(++p, ibuf);                        // retrieve following sentence
       moreline(stdin, ibuf, p);                 // get more lines, if exist
       printf("%s", obuf);                       // output buffer
    }
 }
 exit(0);                                        // normal end
}

/******************************************************************************/
/* Program name: moreline                                                     */
/* Function: Append following lines of sentence to buffer                     */
/* if a sentence has several lines, continue parcing until the end            */
/******************************************************************************/

#define   TERM_EN    (".\n")       // terminate character (English)
#define   TERM_JP    ("ÅB\n")      // terminate character (Japanese)

moreline( FILE *fp, char *in, char *p )
{
 if(strstr(p, TERM_EN)) return 0;  // end of sentence
 if(strstr(p, TERM_JP)) return 0;
 p = strchr(p, '\n');              // find the end of line
 *p = ' ';                         // replace it to a space
 if(isalnum(*(p-1))) p++;          // spacing a word of alphabet or number
 fgets(in, IBUF_LEN-1, fp);        // fetch next line
 strcpy(p, in);                    // append the line to tail
 moreline(fp, in, p);              // check more lines
 return 0;
}

