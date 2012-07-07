/*
 * =====================================================================================
 *
 *       Filename:  parser.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05.04.2010 19:02:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  cbarwise (Ryan)
 *        Company:  http://www.unix.com/programming/126160-building-argc-argv-style-structure-string-char.html
 *
 * =====================================================================================
 */

char ** 
getArgv();

int 
getArgc();

/* main parser */
void
str2argv(char *s);

