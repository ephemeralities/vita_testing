#include <psp2/kernel/processmgr.h>
#include <psp2/ctrl.h>
#include <psp2/display.h>
#include <stdio.h>

#include "debugScreen.h"

#define printf psvDebugScreenPrintf

int main(int argc, char *argv[]) {
	int remain = 0;
	psvDebugScreenInit();

	SceDisplayFrameBuf buffer;
	SceCtrlData ctrl;

	sceDisplayGetFrameBuf(&buffer, SCE_DISPLAY_SETBUF_IMMEDIATE);

	buffer.height = 480U;
	buffer.width = 272U;

	int err = sceDisplaySetFrameBuf(&buffer, SCE_DISPLAY_SETBUF_IMMEDIATE);

	printf("Welcome to the psvDebugScreen showcase !\n");
	
	printf("Hello, my name is Diego Martinez \n");

	printf("Height = %i \n Width  = %i \nError? %i", buffer.height, buffer.width, err);
	
	/* print some bg/fg colors */
	const char* message = "Let's have some foreground/background colors !\n";
	int modes[]={3,9,4,10}, c;
	for(c = 0; message[c] != '\0'; c++)
		printf("\e[%i%im%c", modes[(c/8)%4], c%8, message[c]);

	/* reset fg/bg color back to default */
	printf("\e[m");

	/* \r demo using a countdown */
	/*
	while(ctrl.buttons | SCE_CTRL_CIRCLE){
		sceCtrlPeekBufferPositive(0, &ctrl, 1);
		printf("This sample has been opened for %i s...\r", ++remain);
		sceKernelDelayThread(1000*1000);
	}*/

	do{
		sceCtrlPeekBufferPositive(0, &ctrl, 1);
		printf("This sample has been opened for %i s...\r", ++remain);
		sceKernelDelayThread(1000*1000);
}while(ctrl.buttons != SCE_CTRL_CIRCLE);

	/* print at specific col;row */
	printf("\e[10;20HBye Bye");
	sceKernelDelayThread(2*1000*1000);

	sceKernelExitProcess(0);
	return 0;
}
