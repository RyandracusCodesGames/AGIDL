/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023 Ryandracus Chapman
*
*   Library: libagidl
*   File: agidl_write_img.c
*   Date: 12/19/2023
*   Version: 0.2b
*   Updated: 12/19/2023
*   Author: Ryandracus Chapman
*
********************************************/
#include <stdio.h>
#include <agidl.h> 

int main(){
	
	FILE* file = fopen("write_custom.bmp","wb");
	
	AGIDL_BMP* bmp = AGIDL_CreateBMP("write_custom.bmp",100,50,AGIDL_RGB_555);
	AGIDL_ClearBMP16(bmp,PURPLE_RGB_555);
	
	bmp->header.magic = 0x4d42;
	bmp->header.reserved1 = 0;
	bmp->header.reserved2 = 0;
	bmp->header.offset = 54;
	bmp->header.header_size = 40;
	bmp->header.bits = 16;
	bmp->header.file_size = 54 + (AGIDL_BMPGetWidth(bmp) * AGIDL_BMPGetHeight(bmp) * 2);
	bmp->header.compress = 0;
	bmp->header.img_size = (AGIDL_BMPGetWidth(bmp) * AGIDL_BMPGetHeight(bmp) * 3);
	bmp->header.x_resolution = 0;
	bmp->header.y_resolution = 0;
	bmp->header.num_of_colors = 0;
	bmp->header.important_colors = 0;
	bmp->header.num_of_planes = 1;
	
	AGIDL_BMPEncodeHeader(bmp,file);
	
	int x,y;
	for(y = 0; y <= AGIDL_BMPGetHeight(bmp); y++){
		for(x = 0; x < AGIDL_BMPGetWidth(bmp); x++){
			COLOR16 clr = AGIDL_BMPGetClr16(bmp,x,y);
			AGIDL_ExtractAndPrintRGB(file,clr,AGIDL_BMPGetClrFmt(bmp));
		}
	}
	
	AGIDL_FreeBMP(bmp);
	fclose(file);
	
	return 0;
}