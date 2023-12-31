#ifndef AGIDL_IMGP_SCALE_H
#define AGIDL_IMGP_SCALE_H

/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023 Ryandracus Chapman
*
*   Library: libagidl
*   File: agidl_imgp_scale.h
*   Date: 12/9/2023
*   Version: 0.2b
*   Updated: 12/13/2023
*   Author: Ryandracus Chapman
*
********************************************/

#include "agidl_types.h"
#include "agidl_cc_types.h"
#include "agidl_img_types.h"

typedef enum AGIDL_SCALE{
	AGIDL_SCALE_NEAREST = 0x1,
	AGIDL_SCALE_BILERP = 0x2,
	AGIDL_SCALE_TRILERP = 0x3,
}AGIDL_SCALE;

void * AGIDL_ScaleImgDataNearest(void* data, u16* width, u16* height, float sx, float sy, AGIDL_CLR_FMT fmt);
void * AGIDL_ScaleImgDataBilerp(void* data, u16* width, u16* height, float sx, float sy, AGIDL_CLR_FMT fmt);
void * AGIDL_ScaleImgDataTrilerp(void* data, u16* width, u16* height, float sx, float sy, AGIDL_CLR_FMT fmt);
void * AGIDL_ScaleImgData(void* data, u16* width, u16* height, float sx, float sy, AGIDL_SCALE scale, AGIDL_CLR_FMT fmt);

#endif