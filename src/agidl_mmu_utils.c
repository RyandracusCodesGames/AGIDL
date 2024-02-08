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