/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023 Ryandracus Chapman
*
*   Library: libagidl
*   File: agidl_compress_img.c
*   Date: 12/19/2023
*   Version: 0.2b
*   Updated: 12/19/2023
*   Author: Ryandracus Chapman
*
********************************************/
#include <stdio.h>
#include <agidl.h> 

int main(){
	
	AGIDL_BMP* bmp = AGIDL_LoadBMP("tree.bmp");
	AGIDL_SetBMPFilename(bmp,"tree_rle.bmp");
	AGIDL_BMPSetMaxDiff(bmp,6);
	AGIDL_BMPSetCompression(bmp,1);
	AGIDL_ExportBMP(bmp);
	AGIDL_FreeBMP(bmp);
	
	AGIDL_TGA* tga = AGIDL_LoadTGA("legal.tga");
	AGIDL_SetTGAFilename(tga,"legal_rle.tga");
	AGIDL_TGAConvert24BPPTO16BPP(tga); 
	AGIDL_TGASetCompression(tga,1);
	AGIDL_ExportTGA(tga);
	AGIDL_FreeTGA(tga);
	
	return 0;
}