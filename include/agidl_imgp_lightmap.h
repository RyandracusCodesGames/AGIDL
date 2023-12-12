#ifndef AGIDL_IMGP_LIGHTMAP_H
#define AGIDL_IMGP_LIGHTMAP_H

/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023 Ryandracus Chapman
*
*   Library: libagidl
*   File: agidl_imgp_lightmap.h
*   Date: 12/10/2023
*   Version: 0.2b
*   Updated: 12/11/2023
*   Author: Ryandracus Chapman
*
********************************************/

#include "agidl_types.h"
#include "agidl_cc_types.h"
#include "agidl_img_types.h"

#define MAX_POINTS 512

typedef enum AGIDL_LIGHT{
	LIGHTMAP = 0x1,
	INVLIGHTMAP = 0x2,
}AGIDL_LIGHT;

typedef struct AGIDL_Point{
	u16 x,y;
	u8 size;
	float bias;
	int inv;
	COLOR clr;
}AGIDL_Point;

typedef struct AGIDL_LIGHTMAP{
	AGIDL_LIGHT light;
	u16 width, height;
	AGIDL_CLR_FMT fmt;
	AGIDL_Point points[MAX_POINTS];
	u16 num_of_points;
}AGIDL_LIGHTMAP;

void AGIDL_BindLightmapAndImg(void* data, void* lightdata, u16 width, u16 height, u16 widthl, u16 heightl, AGIDL_CLR_FMT imgfmt, AGIDL_CLR_FMT lightfmt, AGIDL_LIGHT light, COLOR blend);
void * AGIDL_GenerateLightmapImgData(AGIDL_LIGHTMAP lightmap);
AGIDL_Point AGIDL_CreateLightPoint(u16 x, u16 y, u8 size, float bias, int inv, COLOR clr);
void AGIDL_SetLight(AGIDL_LIGHTMAP* lightmap, AGIDL_LIGHT light);
void AGIDL_SetWidth(AGIDL_LIGHTMAP* lightmap, u16 width);
void AGIDL_SetHeight(AGIDL_LIGHTMAP* lightmap, u16 height);
void AGIDL_SetClrFmt(AGIDL_LIGHTMAP* lightmap, AGIDL_CLR_FMT fmt);
int IsInXRange(float bias, u16 x, u8 size, u16 width);
int IsInYRange(float bias, u16 y, u8 size, u16 height);
void AGIDL_InitLightmap(AGIDL_LIGHTMAP* lightmap, AGIDL_LIGHT light, u16 width, u16 height, AGIDL_CLR_FMT fmt);
void AGIDL_AddLightPoint(AGIDL_LIGHTMAP* lightmap, AGIDL_Point point);
void AGIDL_FillLightRect(COLOR* clrs, u16 x, u16 y, u16 width, u16 height, u8 size, COLOR clr);
void AGIDL_FloodLightRect(COLOR* clrs, COLOR clr, float clrfactor, AGIDL_CLR_FMT fmt, u16 x, u16 y, u16 width, u16 height, float bias, u8 size);
void AGIDL_FillLightRect16(COLOR16* clrs, u16 x, u16 y, u16 width, u16 height, u8 size, COLOR16 clr);
void AGIDL_RemoveLightPoint(AGIDL_LIGHTMAP* lightmap, u16 index);

#endif