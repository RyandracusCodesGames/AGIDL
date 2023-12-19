/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023 Ryandracus Chapman
*
*   Library: libagidl
*   File: agidl_convert_img.c
*   Date: 12/19/2023
*   Version: 0.2b
*   Updated: 12/19/2023
*   Author: Ryandracus Chapman
*
********************************************/
#include <stdio.h>
#include <agidl.h> 

int main(){
	
	AGIDL_GXT* gxt = AGIDL_LoadGXT("w_blaster.gxt");
	AGIDL_LMP* lmp = AGIDL_LoadLMP("loading.lmp");
	AGIDL_BTI* bti = AGIDL_LoadBTI("kettei.bti");
	
	AGIDL_BMP* bmp = AGIDL_ConvertGXT2BMP(gxt);
	AGIDL_ExportBMP(bmp);
	AGIDL_FreeBMP(bmp);
	AGIDL_FreeGXT(gxt);
	
	bmp = AGIDL_ConvertLMP2BMP(lmp);
	AGIDL_ExportBMP(bmp);
	AGIDL_FreeBMP(bmp);
	AGIDL_FreeLMP(lmp);
	
	AGIDL_PCX* pcx = AGIDL_ConvertBTI2PCX(bti);
	AGIDL_ExportPCX(pcx);
	AGIDL_FreePCX(pcx);
	
	AGIDL_BMP* bmp2 = AGIDL_ConvertBTI2BMP(bti);
	AGIDL_ExportBMP(bmp2);
	AGIDL_FreeBMP(bmp2);
	AGIDL_FreeBTI(bti);
	
	return 0;
}