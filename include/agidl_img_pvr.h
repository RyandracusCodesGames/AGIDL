#ifndef AGIDL_IMG_PVR_H
#define AGIDL_IMG_PVR_H

/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023 Ryandracus Chapman
*
*   Library: libagidl
*   File: agidl_img_pvr.h
*   Date: 10/28/2023
*   Version: 0.1b
*   Updated: 12/21/2023
*   Author: Ryandracus Chapman
*
********************************************/

#include <stdio.h>
#include "agidl_types.h"
#include "agidl_cc_types.h"
#include "agidl_img_types.h"

typedef enum PVRClrFmt{
	PVR_RGB_555 = 0x00,
	PVR_RGB_565 = 0x01,
	PVR_ARGB_4444 = 0x02,
	PVR_YUV_442 = 0x03,
	PVR_ICP_16 = 0x05,
	PVR_ICP_256 = 0x06,
}PVRClrFmt;

typedef enum PVRImgType{
	PVR_IMG_SQUARE_TWIDDLED = 0x01,
	PVR_IMG_SQUARE_TWIDDLED_AND_MIPMAPPED = 0x02,
	PVR_IMG_ICP_256_TWIDDLED = 0x05,
	PVR_IMG_ICP_16_TWIDDLED = 0x06,
	PVR_IMG_ICP_256 = 0x07,
	PVR_IMG_ICP_16 = 0x08,
	PVR_IMG_RECTANGLE = 0x09,
	PVR_IMG_RECTANGLE_TWIDDLED = 0x0D,
}PVRImgType;

typedef struct PVRHEADER{
	u32 id1;
	u32 offset;
	u32 global_index_1;
	u32 global_index_2;
	u32 id2;
	u32 file_size;
	u8 pvr_clr_fmt;
	u8 pvr_img_type;
	u16 width;
	u16 height;
}PVRHEADER;

typedef struct AGIDL_PVR{
	PVRHEADER header;
	int icp;
	int max_diff;
	AGIDL_ICP palette;
	AGIDL_CLR_FMT fmt;
	Pixels pixels;
	char* filename;
}AGIDL_PVR;

void AGIDL_SetPVRFilename(AGIDL_PVR* pvr, const char* filename);
void AGIDL_PVRSetWidth(AGIDL_PVR* pvr, int width);
void AGIDL_PVRSetHeight(AGIDL_PVR* pvr, int height);
void AGIDL_PVRSetClrFmt(AGIDL_PVR* pvr, AGIDL_CLR_FMT fmt);
void AGIDL_PVRSetMaxDiff(AGIDL_PVR* pvr, int max_diff);
void AGIDL_PVRSetICPMode(AGIDL_PVR* pvr, int mode);
void AGIDL_PVRSetClr(AGIDL_PVR* pvr, int x, int y, COLOR clr);
void AGIDL_PVRSetClr16(AGIDL_PVR* pvr, int x, int y, COLOR16 clr);
void AGIDL_PVRSetRGB(AGIDL_PVR* pvr, int x, int y, u8 r, u8 g, u8 b);
void AGIDL_ClearPVR(AGIDL_PVR* pvr, COLOR clr);
void AGIDL_ClearPVR16(AGIDL_PVR* pvr, COLOR16 clr);
void AGIDL_ClearColorPVR(AGIDL_PVR* pvr, float r, float g, float b);
void AGIDL_FlushPVR(AGIDL_PVR* pvr);
int AGIDL_PVRGetWidth(AGIDL_PVR* pvr);
int AGIDL_PVRGetHeight(AGIDL_PVR* pvr);
u32 AGIDL_PVRGetSize(AGIDL_PVR* pvr);
AGIDL_CLR_FMT AGIDL_PVRGetClrFmt(AGIDL_PVR* pvr);
int AGIDL_PVRGetMaxDiff(AGIDL_PVR* pvr);
COLOR AGIDL_PVRGetClr(AGIDL_PVR* pvr, int x, int y);
COLOR16 AGIDL_PVRGetClr16(AGIDL_PVR* pvr, int, int y);
void AGIDL_PVRSyncPix(AGIDL_PVR *pvr, COLOR *clrs);
void AGIDL_PVRSyncPix16(AGIDL_PVR *pvr, COLOR16 *clrs);
void AGIDL_PVRCopyPix(AGIDL_PVR* pvr, COLOR* clrs, u32 count);
void AGIDL_PVRCopyPix16(AGIDL_PVR* pvr, COLOR16* clrs, u32 count);
void AGIDL_FreePVR(AGIDL_PVR* pvr);
void AGIDL_PVRRGB2BGR(AGIDL_PVR* pvr);
void AGIDL_PVRBGR2RGB(AGIDL_PVR* pvr);
void AGIDL_PVRConvert24BPPTO16BPP(AGIDL_PVR* pvr);
void AGIDL_PVRConvert16BPPTO24BPP(AGIDL_PVR* pvr);
void AGIDL_PVRConvertRGBA2RGB(AGIDL_PVR* pvr);
void AGIDL_PVR555TO565(AGIDL_PVR* pvr);
void AGIDL_PVR565TO555(AGIDL_PVR* pvr);
AGIDL_PVR * AGIDL_LoadPVR(char *filename);
AGIDL_PVR * AGIDL_CreatePVR(const char *filename, int width, int height, AGIDL_CLR_FMT fmt);
AGIDL_PVR* AGIDL_PVRCpyImg(AGIDL_PVR* pvr);
void AGIDL_ExportPVR(AGIDL_PVR *pvr);

int isImgPVR(u32 gbix, u32 pvrt);
void AGIDL_PVRDecodeHeader(AGIDL_PVR* pvr, FILE* file);
void AGIDL_PVRDecodeImg(AGIDL_PVR* pvr, PVRClrFmt fmt, PVRImgType img, FILE* file);
void AGIDL_PVRDecodeTwiddledImg(AGIDL_PVR* pvr, PVRClrFmt fmt, PVRImgType img, FILE* file);
void AGIDL_PVRDecodeICP(AGIDL_PVR* pvr, FILE* file);
PVRClrFmt AGIDL_GetPVRClrFmt(u8 byte);
PVRImgType AGIDL_PVRGetImgType(u8 byte);
u32 AGIDL_GetTwiddleValue(u32 i);
u32 AGIDL_GetDetwiddledIndex(u32 x, u32 y);
void AGIDL_PVREncodeHeader(AGIDL_PVR* pvr, FILE* file);
void AGIDL_PVREncodeIMG(AGIDL_PVR* pvr, FILE* file);

#endif