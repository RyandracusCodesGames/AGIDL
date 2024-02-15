/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023-2024 Ryandracus Chapman
*
*   Library: libagidl
*   File: agidl_mmu_utils.c
*   Date: 2/6/2024
*   Version: 0.3b
*   Updated: 2/8/2024
*   Author: Ryandracus Chapman
*
********************************************/
#include <stdlib.h>
#include "agidl_img_types.h"
#include "agidl_mmu_utils.h"
#include "agidl_cc_converter.h"

void* AGIDL_AllocImgDataMMU(u32 width, u32 height, AGIDL_CLR_FMT fmt){
	if(AGIDL_GetBitCount(fmt) == 16){
		COLOR16* clr = (COLOR16*)malloc(sizeof(COLOR16)*width*height);
		return clr;
	}
	else{
		COLOR* clr = (COLOR*)malloc(sizeof(COLOR)*width*height);
		return clr;
	}
	return NULL;
}

void AGIDL_ConvertRGB2RGBA(void* src, void* dest, u32 width, u32 height, AGIDL_CLR_FMT srcfmt, AGIDL_CLR_FMT destfmt){
	COLOR* clr_data = (COLOR*)src;
	COLOR* dest_data = (COLOR*)dest;
	
	int i;
	for(i = 0; i < width*height; i++){
		COLOR clr = clr_data[i];
		dest_data[i] = AGIDL_RGB_TO_RGBA(clr,srcfmt,destfmt);
	}
}

void AGIDL_ConvertRGBA2RGB(void* src, void* dest, u32 width, u32 height, AGIDL_CLR_FMT srcfmt, AGIDL_CLR_FMT destfmt){
	COLOR* clr_data = (COLOR*)src;
	COLOR* dest_data = (COLOR*)dest;
	
	int i;
	for(i = 0; i < width*height; i++){
		COLOR clr = clr_data[i];
		dest_data[i] = AGIDL_RGBA_TO_RGB(clr,srcfmt,destfmt);
	}
}