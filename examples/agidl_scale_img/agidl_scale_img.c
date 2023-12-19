/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023 Ryandracus Chapman
*
*   Library: libagidl
*   File: agidl_scale_img.c
*   Date: 12/19/2023
*   Version: 0.2b
*   Updated: 12/19/2023
*   Author: Ryandracus Chapman
*
********************************************/
#include <stdio.h>
#include <agidl.h> 

int main(){
	
	AGIDL_BMP* bmp = AGIDL_LoadBMP("sad_mug_box.bmp");
	AGIDL_SetBMPFilename(bmp,"nearest_scale.bmp");
	AGIDL_ScaleBMP(bmp,4,4,AGIDL_SCALE_NEAREST);
	AGIDL_ExportBMP(bmp);
	AGIDL_FreeBMP(bmp);
	
	AGIDL_BMP* bmp2 = AGIDL_LoadBMP("sad_mug_box.bmp");
	AGIDL_SetBMPFilename(bmp2,"bilerp_scale.bmp");
	AGIDL_ScaleBMP(bmp2,4,4,AGIDL_SCALE_BILERP);
	AGIDL_ExportBMP(bmp2);
	AGIDL_FreeBMP(bmp2);
	
	AGIDL_BMP* bmp3 = AGIDL_LoadBMP("sad_mug_box.bmp");
	AGIDL_SetBMPFilename(bmp3,"trilerp_scale.bmp");
	AGIDL_ScaleBMP(bmp3,4,4,AGIDL_SCALE_TRILERP);
	AGIDL_ExportBMP(bmp3);
	AGIDL_FreeBMP(bmp3);
	
	return 0;
}