/******************************************************************************/
/*                                                                            */
/* Program name: mqercmp                                                      */
/*                                                                            */
/* Function: Compress MQ error log messages for ease of reference             */
/*                                                                            */
/* Usuage: mqercmp                                                            */
/*  e.g.   mqercmp < AMQERR01.LOG > er1.out                                   */
/*                                                                            */
/* Note:                                                                      */
/*  Input file might be UTF-8 with LR on Linx/UNIX, or SJIS with CRLF on      */
/*  Windows. Otherwise the program cannot convert a file properly. Use nkf    */
/*  or iconv for preparing proper charset of input file, if necessary.        */
/*                                                                            */
/* Author:   Kouji Murakami                                                   */
/* Date:     2015/06/07                                                       */
/* Modified: 2018/06/09                                                       */
/*                                                                            */
/******************************************************************************/
#define   DEBUG     0

#define   IBUF_LEN  256   // input buffer length
#define   OBUF_LEN  2048  // output buffer length
#define   DTIME_LEN 34    // Date time length. enough for Japanese long format

#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <ctype.h>

int moreline( FILE *fp, char *in, char *out, char *bx );

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
    } else if(!strncmp(ibuf, "AMQ", 3)){         // found a code AMQxxxx!
       if(DEBUG) printf("DBG.AMQ!\n");
       strcpy(++p, ibuf);                        // retrieve following sentence
       moreline(stdin, ibuf, p, obuf);           // get more lines, if exist
       if(DEBUG) printf("DBG.out*\n");
       printf("%s", obuf);                       // output buffer
    }
 }
 exit(0);                                        // normal end
}

/******************************************************************************/
/* Program name: moreline                                                     */
/* Function: Append following lines of sentence to buffer                     */
/* if a sentence has several lines, continue parsing until the end            */
/******************************************************************************/

#define   TERM_EN    (".\n")       // terminate character (English)
#define   TERM_ENW   (".\r\n")     // terminate character (English,Windows)
#define   TERM_JP    ("。\n")      // terminate character (Japanese)
#define   TERM_JPW   ("。\r\n")    // terminate character (Japanese,Windows)

int moreline( FILE *fp, char *in, char *out, char *bx )
{
 char *p;

 if(strstr(out, TERM_EN)) return 0;    // end of sentence
 if(strstr(out, TERM_JP)) return 0;
 if(strstr(out, TERM_ENW)) return 0;
 if(strstr(out, TERM_JPW)) return 0;
 p = strchr(out, '\r');                // CR
 if(!p) p = strchr(out, '\n');         // LF
 if(!p){
    printf("Error: no CR nor LF! check the file format or charset!\n");
    exit(1);
 }
 *p = ' ';                             // replace it to a space
 if(isalnum(*(p-1))) p++;              // spacing a word of alphabet or number
 fgets(in, IBUF_LEN-1, fp);            // fetch next line
 if(DEBUG) printf("DBG.in2* %s\n", in);
 if(p - bx + strlen(in) > OBUF_LEN - 1){
    printf("Error: too long sentence. wrong input. check encoding.\n");
    return 1;
 }
 strcpy(p, in);                        // append the line to tail
 moreline(fp, in, p, bx);              // check more lines

 return 0;
}
