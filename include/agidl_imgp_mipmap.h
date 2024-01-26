#ifndef AGIDL_IMGP_MIPMAP_H
#define AGIDL_IMGP_MIPMAP_H

/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023-2024 Ryandracus Chapman
*
*   Library: libagidl
*   File: agidl_imgp_mipmap.h
*   Date: 1/23/2024
*   Version: 0.2b
*   Updated: 1/23/2024
*   Author: Ryandracus Chapman
*
********************************************/
#include <stdio.h>
#include "agidl_types.h"
#include "agidl_cc_types.h"
#include "agidl_img_types.h"
#include "agidl_imgp_scale.h"

typedef struct AGIDL_MIPMAP_NODE{
	void* img_data;
	u16 width;
	u16 height;
	u8 mip_lvl;
	AGIDL_CLR_FMT fmt;
	struct AGIDL_MIPMAP_NODE *next;
}AGIDL_MIPMAP_NODE;

typedef struct AGIDL_MIPMAP_LINKED_LIST{
	AGIDL_MIPMAP_NODE* head;
	u8 num_mips;
}AGIDL_MIPMAP_LINKED_LIST;

typedef struct AGIDL_MIPMAP{
	AGIDL_MIPMAP_LINKED_LIST *list;
	AGIDL_CLR_FMT fmt;
	u16 width;
	u16 height;
	AGIDL_Bool IsLinear;
	void* img_data;
}AGIDL_MIPMAP;

AGIDL_MIPMAP_NODE* AGIDL_CreateMipmapNode(void* img_data, u16 width, u16 height, AGIDL_CLR_FMT fmt, u8 mip_lvl);
AGIDL_MIPMAP_LINKED_LIST* AGIDL_CreateMipmapList();
void AGIDL_AddMipmapNode(AGIDL_MIPMAP_LINKED_LIST* list, void* img_data, u16 width, u16 height, AGIDL_CLR_FMT fmt);
void AGIDL_RemoveMipampNode(AGIDL_MIPMAP_LINKED_LIST* list, u8 mip_lvl);
AGIDL_MIPMAP_NODE* AGIDL_FindMipmapNode(AGIDL_MIPMAP_LINKED_LIST* list, u8 mip_lvl);
void AGIDL_PopMipmapStart(AGIDL_MIPMAP_LINKED_LIST* list);
void AGIDL_DestroyMipmapList(AGIDL_MIPMAP_LINKED_LIST* list);
AGIDL_MIPMAP* AGIDL_CreateMipmap(void* img_data, u16 width, u16 height, AGIDL_CLR_FMT fmt, AGIDL_Bool IsLinear);
void AGIDL_DestroyMipmap(AGIDL_MIPMAP* mipmap);
void AGIDL_LoadMipmapImgData(AGIDL_MIPMAP* mipmap, u8 mipmap_count, FILE* file);
void AGIDL_ExportMipmapImgData(AGIDL_MIPMAP* mipmap, AGIDL_IMG_TYPE img, int flip);
void AGIDL_GenerateMipmapFromImgData(AGIDL_MIPMAP* mipmap, void* img_data, u16 width, u16 height, AGIDL_CLR_FMT fmt, u8 mip_lvl, AGIDL_SCALE scale);

#endif