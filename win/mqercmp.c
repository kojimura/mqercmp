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
/* Modified: 2020/09/27 remake date-time-check  S                             */
/*                                                                            */
/******************************************************************************/
#define   DEBUG     0

#define   IBUF_LEN  2048   // input buffer length
#define   OBUF_LEN  4096   // output buffer length
#define   DTIME_LEN 48     // Date time length. enough for Japanese long format

#define   MQDATETIME_JP 1   // MQ Date-Time Japanese
#define   MQDATETIME_EN 2   // MQ Date-Time English
#define   MQDATETIME_NO 0   // MQ Date-Time Not Date-Time format

#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <ctype.h>

int main( int argc, char **argv )
{
 char *p, ibuf[IBUF_LEN], token[IBUF_LEN], obuf[OBUF_LEN];   // input buffer, output buffer
 int sts;

 p = &obuf[0];
 while(fgets(ibuf, IBUF_LEN-1, stdin)){
    if(DEBUG) printf("DBG.ibuf* %s\n", ibuf);

    strncpy(token, ibuf, IBUF_LEN);              // copy to token for pursing
    if(DEBUG) printf("DBG.p(%c)obuf* %s\n", *p, obuf);
    sts = ismqdate(token);                        // check if Date-Time
    if(DEBUG) printf("DBG.ismqdate RC(%i)\n", sts);
    
    if(sts == MQDATETIME_NO){                    // not Date & Time
       if(!strncmp(ibuf, "AMQ", 3)){             // found a code AMQxxxx!
           if(DEBUG) printf("DBG.AMQ!\n");
           strcpy(++p, ibuf);                        // retrieve following sentence
           moreline(stdin, ibuf, p);                 // get more lines, if exist
           printf("%s", obuf);                       // output buffer
       } else {                                  // no Date-Time, no AMQxxxx
           continue;                             // ignore this line, get next
       }
    } else {                        // Date-Time (1:Jp or 2:En)
       if(DEBUG) printf("DBG.date(%c)\n", ibuf[0]);
       strncpy(obuf, ibuf, DTIME_LEN);           // copy Date-Time to outbuffer
       p = strchr(obuf, ' ');                    // first space between Date Time(JP)
       if(p){
          p = strchr(++p, ' ');                  // second space following Time(JP)
          if(sts == MQDATETIME_EN){              // English Date Time
             p = strchr(++p, ' ');               // 3rd space(EN Jan 23 2020)
             p = strchr(++p, ' ');               // 4th space(EN Jan 23 2020 10:10)
          }
       }
       else {
          continue;                             // not Date & Time, ignore!
       }
    }
   /*
    if(sts){ 
       if(DEBUG) printf("DBG.date(%c)\n", ibuf[0]);
       strncpy(obuf, ibuf, DTIME_LEN);           // get Date & Time
       p = strchr(obuf, ' ');                    // space between Date & Time
       if(p){
          p = strchr(++p, ' ');                 // second space following Time
       }
       else {
          continue;                             // not Date & Time, ignore!
       }

    
    } else if(!strncmp(ibuf, "AMQ", 3)){         // found a code AMQxxxx!
       if(DEBUG) printf("DBG.AMQ!\n");
       strcpy(++p, ibuf);                        // retrieve following sentence
       moreline(stdin, ibuf, p);                 // get more lines, if exist
       printf("%s", obuf);                       // output buffer
    }
    */
 }
 exit(0);                                        // normal end
}

int ismqdate(char *s )
/******************************************************************************/
/* Program name: isdate                                                       */
/* Function: check if the string contain date                                 */
/* Return:                                                                    */
/*  0 MQDATETIME_NO: None date-time string                                    */
/*  1 MQDATETIME_JP: Japanese Date-Time String (1 space in between)           */
/*   2017�N10��07�� 08��03��07�b                                              */
/*   2014/12/06 09:13:29                                                      */
/*   5/21/18 09:13:29                                                         */
/*  2 MQDATETIME_EN: English Date-Time String (3 spaces in between)           */
/*   Jun 14 2018 09:13:29                                                     */
/******************************************************************************/
{
 char *t;     // Token pointer, original string will change
 char *s2;    // Temporary pointer, shifting for next word checking

 t = s;     // pointer of Token
 s2 = s;    // temporary pointer
 
 if(DEBUG) printf("DBG.ismqdate.s %s\n", s);
 
 if((t = strtok(s, " \t\n")) == NULL) return(MQDATETIME_NO);      // empty line
 if(DEBUG) printf("DBG.ismqdate.t* %s\n", t);
 
 /* English date */

 if(strstr(t, "Jan") || strstr(t, "Feb") || strstr(t, "Mar") || strstr(t, "Apr") || strstr(t, "May") || strstr(t, "Jun") ||
   strstr(t, "Jul") || strstr(t, "Aug") || strstr(t, "Sep") || strstr(t, "Oct") || strstr(t, "Nov") || strstr(t, "Dec")){
    return(MQDATETIME_EN);
 }

 /* Now, it could be Japanese Date which must start with digit */
 if(!isdigit(*s)) return(MQDATETIME_NO);
 if(DEBUG) {                             // 
   s2 = strstr(s, "�N");   // strstr �Ō��o����Ă��邩�A�����|�C���^����ĂȂ���
   if(s2){
     printf("DBG.ismqdate.�Ns2 %s\n", s2); // �N������Ύ��o���Ă��邩
   }
   else{
     printf("DBG.ismqdate.�Ns2 NULL\n");  // NULL���Ԃ�����
  }
 }
 
/* Japanese Date */
 if((s2 = strstr(s, "�N")) && (s2 = strstr(s2, "��")) && (s2 = strstr(s2, "��"))) return(MQDATETIME_JP);
 if((s2 = strstr(s, "/")) && (s2 = strstr(s2, "/"))) return(MQDATETIME_JP);

/* Otherwise, it is not Date */
 return(MQDATETIME_NO);
}

/******************************************************************************/
/* Program name: moreline                                                     */
/* Function: Append following lines of sentence to buffer                     */
/* if a sentence has several lines, continue parcing until the end            */
/******************************************************************************/

#define   TERM_EN    (".\n")       // terminate character (English)
#define   TERM_JP    ("�B\n")      // terminate character (Japanese)

moreline( FILE *fp, char *in, char *p )
{
 if(DEBUG) printf("DBG.moreline(%c)in %s\n", *p, in);

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

