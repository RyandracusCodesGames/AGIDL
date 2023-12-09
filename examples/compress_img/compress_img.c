/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023 Ryandracus Chapman
*
*   Library: libagidl
*   File: compress_img.c
*   Date: 12/8/2023
*   Version: 0.1b
*   Updated: 12/8/2023
*   Author: Ryandracus Chapman
*
********************************************/
#include <stdio.h>
#include <agidl.h>

int main(){
	
	AGIDL_TIM* tim = AGIDL_LoadTIM("sad_mug_box.tim");
	
	AGIDL_BMP* bmp = AGIDL_ConvertTIM2BMP(tim);
	AGIDL_BMPSetCompression(bmp,1);
	AGIDL_BMPSetMaxDiff(bmp,19);
	AGIDL_ExportBMP(bmp);
	AGIDL_FreeBMP(bmp);
	
	AGIDL_BMP* bmpnocompress = AGIDL_ConvertTIM2BMP(tim);
	AGIDL_SetBMPFilename(bmpnocompress,"sad_mug_no_rle_box.bmp");
	AGIDL_ExportBMP(bmpnocompress);
	AGIDL_FreeBMP(bmpnocompress);
	
	AGIDL_TGA* tga = AGIDL_ConvertTIM2TGA(tim);
	AGIDL_TGAConvert16BPPTO24BPP(tga);
	AGIDL_TGASetCompression(tga,1);
	AGIDL_ExportTGA(tga);
	AGIDL_FreeTGA(tga);
	
	AGIDL_FreeTIM(tim);

	return 0;
}