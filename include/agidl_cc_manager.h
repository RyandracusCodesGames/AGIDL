#ifndef AGIDL_CC_MANAGER
#define AGIDL_CC_MANAGER

#include "agidl_types.h"
#include "agidl_cc_types.h"

#define MAX_TABLE_CLRS 8000

/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023-2024 Ryandracus Chapman
*
*   Library: libagidl
*   File: agidl_cc_manager.h
*   Date: 9/8/2023
*   Version: 0.1b
*   Updated: 2/4/2024
*   Author: Ryandracus Chapman
*
********************************************/

u8 AGIDL_GetR(COLOR clr, AGIDL_CLR_FMT fmt);
u8 AGIDL_GetG(COLOR clr, AGIDL_CLR_FMT fmt);
u8 AGIDL_GetB(COLOR clr, AGIDL_CLR_FMT fmt);
u8 AGIDL_GetA(COLOR clr, AGIDL_CLR_FMT fmt);

COLOR AGIDL_SetR(COLOR clr, u8 newR, AGIDL_CLR_FMT fmt);
COLOR AGIDL_SetG(COLOR clr, u8 newG, AGIDL_CLR_FMT fmt);
COLOR AGIDL_SetB(COLOR clr, u8 newB, AGIDL_CLR_FMT fmt);
COLOR AGIDL_SetA(COLOR clr, u8 newA, AGIDL_CLR_FMT fmt);

COLOR AGIDL_RGB(u8 r, u8 g, u8 b, AGIDL_CLR_FMT fmt); 
COLOR AGIDL_RGBA(u8 r, u8 g, u8 b, u8 a, AGIDL_CLR_FMT fmt);
COLOR16 AGIDL_RGB16(u8 r, u8 g, u8 b, AGIDL_CLR_FMT fmt);
COLOR AGIDL_GetColor(AGIDL_CLR clr, AGIDL_CLR_FMT fmt);
COLOR16 AGIDL_GetColor16(AGIDL_CLR clr, AGIDL_CLR_FMT fmt);
COLOR AGIDL_Color3f(float r, float g, float b, AGIDL_CLR_FMT fmt);
COLOR AGIDL_Color4f(float r, float g, float b, float a, AGIDL_CLR_FMT fmt);

COLOR AGIDL_GammaCorrectColor(COLOR clr, f32 gamma, AGIDL_CLR_FMT fmt);
u8 AGIDL_GammaCorrectColorComponent(u8 rgb, f32 gamma, AGIDL_CLR_FMT fmt);

typedef enum AGIDL_ICP_ENCODE{
	ICP_ENCODE_HISTOGRAM = 0x1,
	ICP_ENCODE_THRESHOLD = 0x2,
}AGIDL_ICP_ENCODE;

typedef struct AGIDL_HistEntry{
	COLOR clr;
	u32 occurence;
}AGIDL_HistEntry;

typedef struct AGIDL_Hist{
	AGIDL_HistEntry table[MAX_TABLE_CLRS];
	u32 num_of_clrs;
}AGIDL_Hist;

AGIDL_Bool AGIDL_IsClrInHistogram(AGIDL_Hist hist, COLOR clr);
void AGIDL_EncodeHistogramICP(AGIDL_ICP* palette, void* data, u32 width, u32 height, AGIDL_CLR_FMT fmt);

void AGIDL_SetICPMode(AGIDL_ICP* palette, int mode, AGIDL_CLR_FMT fmt);
void AGIDL_ClearICP(AGIDL_ICP* palette, COLOR clr);
void AGIDL_ClearRGBICP(AGIDL_ICP* palette, u8 r, u8 g, u8 b);
void AGIDL_ClearColorICP(AGIDL_ICP* palette, float r, float g, float b);
int AGIDL_IsInThreshold(COLOR clr1, COLOR clr2, AGIDL_CLR_FMT fmt, AGIDL_CLR_FMT fmt2, u8 max_diff);
AGIDL_ICP AGIDL_GenerateVGAICP();
AGIDL_ICP AGIDL_GenerateAloneInTheDarkICP();
AGIDL_CLR_MDL AGIDL_GetClrMDL(AGIDL_CLR_FMT fmt);
AGIDL_CLR_FMT AGIDL_GetClrFmt(AGIDL_CLR_MDL mdl, AGIDL_BITS bits);
void AGIDL_ExportICP(const char* name, AGIDL_ICP icp);
AGIDL_ICP AGIDL_LoadICP(const char* filename);
void AGIDL_InitICP(AGIDL_ICP *palette, int mode);
void AGIDL_ForceAddColor(AGIDL_ICP* palette, COLOR clr, u8 index);
void AGIDL_AddColorICP16(AGIDL_ICP *palette, u8 index, COLOR16 clr, AGIDL_CLR_FMT fmt, int max_diff, int *pass);
void AGIDL_AddColorICP(AGIDL_ICP *palette, u8 index, COLOR clr, AGIDL_CLR_FMT fmt, int max_diff, int *pass);
u8 AGIDL_FindClosestColor(AGIDL_ICP palette, COLOR clr, AGIDL_CLR_FMT fmt, int max_difference);
u8 AGIDL_FindNearestColor(AGIDL_ICP palette, COLOR clr, AGIDL_CLR_FMT fmt);
AGIDL_ICP AGIDL_GenerateVGAICP();
AGIDL_ICP AGIDL_GenerateVGAICP16();
/*BASIC SETTERS FOR ALL COLOR SPACES*/
void AGIDL_SetY(AGIDL_YCbCr *ycbcr, u8 y);
void AGIDL_SetCb(AGIDL_YCbCr *ycbcr, u8 cb);
void AGIDL_SetCr(AGIDL_YCbCr *ycbcr, u8 cr);
void AGIDL_SetYCbCr(AGIDL_YCbCr *ycbcr, u8 y, u8 cb, u8 cr);

#endif