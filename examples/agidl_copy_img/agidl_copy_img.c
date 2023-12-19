/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023 Ryandracus Chapman
*
*   Library: libagidl
*   File: agidl_copy_img.c
*   Date: 12/19/2023
*   Version: 0.2b
*   Updated: 12/19/2023
*   Author: Ryandracus Chapman
*
********************************************/
#include <stdio.h>
#include <agidl.h> 

int main(){
	
	AGIDL_PVR* pvr = AGIDL_LoadPVR("trucker_rgb_565.pvr");
	AGIDL_BMP* bmp = AGIDL_ConvertPVR2BMP(pvr);
	
	AGIDL_BMP* cpy = AGIDL_BMPCpyImg(bmp);
	
	int x,y;
	for(y = 0; y < AGIDL_BMPGetHeight(bmp); y += 8){
		for(x = 0; x < AGIDL_BMPGetHeight(bmp); x++){
			COLOR16 clr = AGIDL_GetColor(ORANGE,AGIDL_BMPGetClrFmt(bmp));
			AGIDL_BMPSetClr16(cpy,x,y,clr);
		}
	}
	
	AGIDL_ExportBMP(cpy);
	AGIDL_ExportBMP(bmp);
	AGIDL_FreeBMP(cpy);
	AGIDL_FreeBMP(bmp);
	AGIDL_FreePVR(pvr);
	

	return 0;
}