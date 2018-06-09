# makefile for Windows

CC = cl.exe

LINK = link.exe

mqercmp.exe : mqercmp.c
	$(CC) -MD mqercmp.c -Femqercmp.exe

