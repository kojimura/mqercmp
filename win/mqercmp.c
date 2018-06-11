/******************************************************************************/
/*                                                                            */
/* Program name: mqercmp                                                      */
/*                                                                            */
/* Function: Compress MQ error log messages for ease of reference             */
/*                                                                            */
/* Usuage: mqercmp                                                            */
/*  e.g.   mqercmp < AMQERR01.LOG > er1.out                                   */
/*                                                                            */
/* Author:   Kouji Murakami                                                   */
/* Date:     2015/06/07                                                       */
/* Modified: 2018/06/11                                                       */
/*                                                                            */
/******************************************************************************/
#define   DEBUG     0

#define   IBUF_LEN  256   // input buffer length
#define   OBUF_LEN  1024  // output buffer length
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

