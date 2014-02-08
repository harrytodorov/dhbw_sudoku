/* 
 * File:   helpers.h
 * Author: haralambitodorov
 *
 * Created on February 8, 2014, 3:04 PM
 */

#ifndef HELPERS_H
#define	HELPERS_H

//      int getch()
//      read unbuffered characters from stdin 
//      Return value: ASCII Code of input
//      sets the terminal into non-canonical mode, disables line buffering,
//      reads a character from stdin and then restores the old terminal status
//      
int getch();



void printSudokuField(int y, int x);

#endif	/* HELPERS_H */

