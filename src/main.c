#include <stdio.h>
#include <agidl.h>

/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023-2024 Ryandracus Chapman
*
*   Library: libagidl
*   File: main.c
*  	Purpose: Demonstrate a simple AGIDL program
*   Author: Ryandracus Chapman
*
********************************************/

int main(){
	
	/*CREATE FUNCTION ALLOCATES RESOURCES TO OUR IMAGE AND INITIALIZES CORE ATTRIBUTES OF THE FILE FORMAT*/
	AGIDL_BMP* bmp = AGIDL_CreateBMP("sample.bmp",640,480,AGIDL_RGB_555);
	/*CLEAR FUNCTION WILL FILL THE ENTIRE IMAGE WITH A PARTICULAR COLOR - IDENTICAL IN FUNCTIONAL TO LEGACY OPENGL COLO3F CALL*/
	AGIDL_ClearBMP16(bmp,AGIDL_Color3f(0.25f,0.0f,0.57f,AGIDL_RGB_555));
	AGIDL_ExportBMP(bmp); /*SAVE OUR IMAGE AS A FILE IN OUR DESIGNATED DIRECTORY*/
	AGIDL_FreeBMP(bmp);  /*DEALLOCATE THE PROVIDED RESOURCES WHEN FINISHED*/

	return 0;
}