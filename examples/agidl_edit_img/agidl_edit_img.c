/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023 Ryandracus Chapman
*
*   Library: libagidl
*   File: agidl_edit_img.c
*   Date: 12/19/2023
*   Version: 0.2b
*   Updated: 12/19/2023
*   Author: Ryandracus Chapman
*
********************************************/
#include <stdio.h>
#include <agidl.h> 

int main(){
	
	AGIDL_BMP* bmp = AGIDL_LoadBMP("bmp_simple_16b.bmp");
	
	int x,y;
	for(y = 0; y < AGIDL_BMPGetHeight(bmp); y += 4){
		for(x = 0; x < AGIDL_BMPGetWidth(bmp); x++){
			COLOR16 edit = AGIDL_GetColor(YELLOW,AGIDL_BMPGetClrFmt(bmp));
			AGIDL_BMPSetClr16(bmp,x,y,edit);
		}
	}
	
	AGIDL_SetBMPFilename(bmp,"edited_bmp.bmp");
	AGIDL_ExportBMP(bmp);
	AGIDL_FreeBMP(bmp);

	return 0;
}