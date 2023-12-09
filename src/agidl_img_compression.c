#include "agidl_img_compression.h"
#include "agidl_img_types.h"

/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023 Ryandracus Chapman
*
*   Library: libagidl
*   File: agidl_img_compression.c
*   Date: 11/25/2023
*   Version: 0.1b
*   Updated: 11/25/2023
*   Author: Ryandracus Chapman
*
********************************************/

u32 AGIDL_EncodeRLE(void* data, u32 bit_count, u32 x, u32 y, u32 width, u32 height, u16 max_rle){

	u32 count = 1;

	if(bit_count == 24 || bit_count == 32){
		COLOR* clrdata = (COLOR*)data;
		
		u32 x_count = x + 1;
		while(AGIDL_GetClr(clrdata,x,y,width,height) == AGIDL_GetClr(clrdata,x_count,y,width,height) && count < max_rle){
			count++;
			x_count++;
		}
	}
	else{
		COLOR16* clrdata = (COLOR16*)data;
		u32 x_count = x + 1;
		while((AGIDL_GetClr16(clrdata,x,y,width,height) == AGIDL_GetClr16(clrdata,x_count,y,width,height)) && count < max_rle){
			count++;
			x_count++;
		}
	}

	return count;
}