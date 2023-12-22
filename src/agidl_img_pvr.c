#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "agidl_img_pvr.h"
#include "agidl_cc_core.h"
#include "agidl_math_utils.h"

/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023 Ryandracus Chapman
*
*   Library: libagidl
*   File: agidl_img_pvr.c
*   Date: 10/28/2023
*   Version: 0.1b
*   Updated: 12/21/2023
*   Author: Ryandracus Chapman
*
********************************************/

void AGIDL_SetPVRFilename(AGIDL_PVR* pvr, const char* filename){
	pvr->filename = (char*)realloc(pvr->filename,strlen(filename));
	AGIDL_FilenameCpy(pvr->filename,filename);
}

void AGIDL_PVRSetWidth(AGIDL_PVR* pvr, int width){
	pvr->header.width = width;
}

void AGIDL_PVRSetHeight(AGIDL_PVR* pvr, int height){
	pvr->header.height = height;
}

void AGIDL_PVRSetClrFmt(AGIDL_PVR* pvr, AGIDL_CLR_FMT fmt){
	pvr->fmt = fmt;
}

void AGIDL_PVRSetMaxDiff(AGIDL_PVR* pvr, int max_diff){
	max_diff = AGIDL_Max(0,max_diff);
	pvr->max_diff = max_diff;
}

void AGIDL_PVRSetICPMode(AGIDL_PVR* pvr, int mode){
	pvr->icp = mode;
}

void AGIDL_PVRSetClr(AGIDL_PVR *pvr, int x, int y, COLOR clr){
	if(AGIDL_GetBitCount(AGIDL_PVRGetClrFmt(pvr)) != 16){
		AGIDL_SetClr(pvr->pixels.pix32,clr,x,y,AGIDL_PVRGetWidth(pvr),AGIDL_PVRGetHeight(pvr));
	}
	else{
		AGIDL_SetClr16(pvr->pixels.pix16,AGIDL_CLR_TO_CLR16(clr,AGIDL_BGR_888,AGIDL_PVRGetClrFmt(pvr)),x,y,AGIDL_PVRGetWidth(pvr),AGIDL_PVRGetHeight(pvr));
	}
}

void AGIDL_PVRSetClr16(AGIDL_PVR *pvr, int x, int y, COLOR16 clr){
	if(AGIDL_GetBitCount(AGIDL_PVRGetClrFmt(pvr) == 16)){
		AGIDL_SetClr16(pvr->pixels.pix16,clr,x,y,AGIDL_PVRGetWidth(pvr),AGIDL_PVRGetHeight(pvr));
	}
	else{
		AGIDL_SetClr(pvr->pixels.pix32,AGIDL_CLR16_TO_CLR(clr,AGIDL_RGB_555,AGIDL_PVRGetClrFmt(pvr)),x,y,AGIDL_PVRGetWidth(pvr),AGIDL_PVRGetHeight(pvr));
	}
}

void AGIDL_PVRSetRGB(AGIDL_PVR *pvr, int x, int y, u8 r, u8 g, u8 b){
	switch(AGIDL_GetBitCount(AGIDL_PVRGetClrFmt(pvr))){
		case 24:{
			AGIDL_PVRSetClr(pvr,x,y,AGIDL_RGB(r,g,b,AGIDL_PVRGetClrFmt(pvr)));
		}break;
		case 16:{
			AGIDL_PVRSetClr16(pvr,x,y,AGIDL_RGB16(r,g,b,AGIDL_PVRGetClrFmt(pvr)));
		}break;
		case 32:{
			AGIDL_PVRSetClr(pvr,x,y,AGIDL_RGBA(r,g,b,0xff,AGIDL_PVRGetClrFmt(pvr)));
		}break;
	}
}

void AGIDL_ClearPVR(AGIDL_PVR *pvr, COLOR clr){
	if(AGIDL_GetBitCount(AGIDL_PVRGetClrFmt(pvr)) != 16){
		AGIDL_ClrMemset(pvr->pixels.pix32,clr,AGIDL_PVRGetSize(pvr));
	}
	else{
		AGIDL_ClrMemset16(pvr->pixels.pix16,(COLOR16)clr,AGIDL_PVRGetSize(pvr));
	}
}

void AGIDL_ClearPVR16(AGIDL_PVR *pvr, COLOR16 clr){
	if(AGIDL_GetBitCount(AGIDL_PVRGetClrFmt(pvr)) == 16){
		AGIDL_ClrMemset16(pvr->pixels.pix16,clr,AGIDL_PVRGetSize(pvr));
	}
	else{
		AGIDL_ClrMemset(pvr->pixels.pix32,AGIDL_CLR16_TO_CLR(clr,AGIDL_RGB_555,AGIDL_PVRGetClrFmt(pvr)),AGIDL_PVRGetSize(pvr));
	}
}

void AGIDL_ClearColorPVR(AGIDL_PVR* pvr, float r, float g, float b){
	if(AGIDL_GetBitCount(AGIDL_PVRGetClrFmt(pvr)) == 16){
		AGIDL_ClearColorBuffer(pvr->pixels.pix16,r,g,b,AGIDL_PVRGetClrFmt(pvr),AGIDL_PVRGetSize(pvr));
	}
	else{
		AGIDL_ClearColorBuffer(pvr->pixels.pix32,r,g,b,AGIDL_PVRGetClrFmt(pvr),AGIDL_PVRGetSize(pvr));
	}
}

void AGIDL_FlushPVR(AGIDL_PVR* pvr){
	AGIDL_ClearPVR(pvr,0);
}

void AGIDL_PVRSyncPix(AGIDL_PVR *pvr, COLOR *clrs){
	if(AGIDL_GetBitCount(AGIDL_PVRGetClrFmt(pvr)) != 16){
		AGIDL_ClrMemcpy(pvr->pixels.pix32,clrs,AGIDL_PVRGetSize(pvr));
	}
}

void AGIDL_PVRSyncPix16(AGIDL_PVR *pvr, COLOR16 *clrs){
	if(AGIDL_GetBitCount(AGIDL_PVRGetClrFmt(pvr)) == 16){
		AGIDL_ClrMemcpy16(pvr->pixels.pix16,clrs,AGIDL_PVRGetSize(pvr));
	}
}

void AGIDL_PVRCopyPix(AGIDL_PVR* pvr, COLOR* clrs, u32 count){
	if(AGIDL_GetBitCount(AGIDL_PVRGetClrFmt(pvr)) != 16){
		AGIDL_ClrMemcpy(pvr->pixels.pix32,clrs,count);
	}
}

void AGIDL_PVRCopyPix16(AGIDL_PVR* pvr, COLOR16* clrs, u32 count){
	if(AGIDL_GetBitCount(AGIDL_PVRGetClrFmt(pvr)) == 16){
		AGIDL_ClrMemcpy16(pvr->pixels.pix16,clrs,count);
	}
}

int AGIDL_PVRGetWidth(AGIDL_PVR* pvr){
	return pvr->header.width;
}

u32 AGIDL_PVRGetSize(AGIDL_PVR* pvr){
	return AGIDL_PVRGetWidth(pvr) * AGIDL_PVRGetHeight(pvr);
}

int AGIDL_PVRGetHeight(AGIDL_PVR* pvr){
	return pvr->header.height;
}

AGIDL_CLR_FMT AGIDL_PVRGetClrFmt(AGIDL_PVR* pvr){
	return pvr->fmt;
}

int AGIDL_PVRGetMaxDiff(AGIDL_PVR* pvr){
	return pvr->max_diff;
}

COLOR AGIDL_PVRGetClr(AGIDL_PVR* pvr, int x, int y){
	if(x >= 0 && y >= 0 && x < AGIDL_PVRGetWidth(pvr) && y < AGIDL_PVRGetHeight(pvr)){
		return pvr->pixels.pix32[x+y*AGIDL_PVRGetWidth(pvr)];
	}
}

COLOR16 AGIDL_PVRGetClr16(AGIDL_PVR* pvr, int x, int y){
	if(x >= 0 && y >= 0 && x < AGIDL_PVRGetWidth(pvr) && y < AGIDL_PVRGetHeight(pvr)){
		return pvr->pixels.pix16[x+y*AGIDL_PVRGetWidth(pvr)];
	}
}

void AGIDL_FreePVR(AGIDL_PVR* pvr){
	free(pvr->filename);
	
	if(AGIDL_GetBitCount(AGIDL_PVRGetClrFmt(pvr)) == 16){
		free(pvr->pixels.pix16);
	}
	else{
		free(pvr->pixels.pix32);
	}
	
	free(pvr);
	
	if(pvr != NULL){
		pvr = NULL;
	}
}

void AGIDL_PVRRGB2BGR(AGIDL_PVR *pvr){
	if(pvr->fmt == AGIDL_RGB_888){
		AGIDL_RGB2BGR(pvr->pixels.pix32,AGIDL_PVRGetWidth(pvr),AGIDL_PVRGetHeight(pvr),&pvr->fmt);
	}
	if(pvr->fmt == AGIDL_RGB_555 || pvr->fmt == AGIDL_RGB_565){
		AGIDL_RGB2BGR16(pvr->pixels.pix16,AGIDL_PVRGetWidth(pvr),AGIDL_PVRGetHeight(pvr),&pvr->fmt);
	}
}

void AGIDL_PVRBGR2RGB(AGIDL_PVR* pvr){
	if(pvr->fmt == AGIDL_BGR_888){
		AGIDL_BGR2RGB(pvr->pixels.pix32,AGIDL_PVRGetWidth(pvr),AGIDL_PVRGetHeight(pvr),&pvr->fmt);
	}
	if(pvr->fmt == AGIDL_BGR_555 || pvr->fmt == AGIDL_BGR_565){
		AGIDL_BGR2RGB16(pvr->pixels.pix16,AGIDL_PVRGetWidth(pvr),AGIDL_PVRGetHeight(pvr),&pvr->fmt);
	}
}

void AGIDL_PVRConvert16BPPTO24BPP(AGIDL_PVR *pvr){
	if(pvr->fmt == AGIDL_RGB_555 || pvr->fmt == AGIDL_BGR_555 || pvr->fmt == AGIDL_RGB_565 || pvr->fmt == AGIDL_BGR_565){
		pvr->pixels.pix32 = (COLOR*)malloc(sizeof(COLOR)*(AGIDL_PVRGetHeight(pvr)*AGIDL_PVRGetWidth(pvr)));
		AGIDL_16BPPTO24BPP(pvr->pixels.pix16,pvr->pixels.pix32,AGIDL_PVRGetWidth(pvr),AGIDL_PVRGetHeight(pvr),&pvr->fmt);
		free(pvr->pixels.pix16);
	}
}

void AGIDL_PVRConvert24BPPTO16BPP(AGIDL_PVR *pvr){
	if(pvr->fmt == AGIDL_RGB_888 || pvr->fmt == AGIDL_BGR_888 || pvr->fmt == AGIDL_RGBA_8888 || pvr->fmt == AGIDL_ARGB_8888){
		pvr->pixels.pix16 = (COLOR16*)malloc(sizeof(COLOR16)*(AGIDL_PVRGetHeight(pvr)*AGIDL_PVRGetWidth(pvr)));
		AGIDL_24BPPTO16BPP(pvr->pixels.pix32,pvr->pixels.pix16,AGIDL_PVRGetWidth(pvr),AGIDL_PVRGetHeight(pvr),&pvr->fmt);
		free(pvr->pixels.pix32);
	}
}

void AGIDL_PVRConvert555TO565(AGIDL_PVR* pvr){
	AGIDL_555TO565(pvr->pixels.pix16,AGIDL_PVRGetWidth(pvr),AGIDL_PVRGetHeight(pvr),&pvr->fmt);
}

void AGIDL_PVRConvert565TO555(AGIDL_PVR* pvr){
	AGIDL_565TO555(pvr->pixels.pix16,AGIDL_PVRGetWidth(pvr),AGIDL_PVRGetHeight(pvr),&pvr->fmt);
}

void AGIDL_PVRConvertRGBA2RGB(AGIDL_PVR* pvr){
	if(pvr->fmt == AGIDL_RGBA_8888 || pvr->fmt == AGIDL_ARGB_8888){
		int x,y;
		for(y = 0; y < AGIDL_PVRGetHeight(pvr); y++){
			for(x = 0; x < AGIDL_PVRGetWidth(pvr); x++){
				COLOR clr = AGIDL_PVRGetClr(pvr,x,y);
				
				u8 r = AGIDL_GetR(clr,pvr->fmt);
				u8 g = AGIDL_GetG(clr,pvr->fmt);
				u8 b = AGIDL_GetB(clr,pvr->fmt);
				
				clr = AGIDL_RGB(r,g,b,AGIDL_RGB_888);
				AGIDL_PVRSetClr(pvr,x,y,clr);
			}
		}
	}
}

AGIDL_PVR * AGIDL_CreatePVR(const char* filename, int width, int height, AGIDL_CLR_FMT fmt){
	AGIDL_PVR* pvr = (AGIDL_PVR*)malloc(sizeof(AGIDL_PVR));
	pvr->filename = (char*)malloc(strlen(filename)+1);
	AGIDL_FilenameCpy(pvr->filename,filename);
	AGIDL_PVRSetWidth(pvr,width);
	AGIDL_PVRSetHeight(pvr,height);
	AGIDL_PVRSetClrFmt(pvr,fmt);
	AGIDL_PVRSetMaxDiff(pvr,7);
	
	if(fmt == AGIDL_RGB_888 || fmt == AGIDL_BGR_888 || fmt == AGIDL_RGBA_8888 || fmt == AGIDL_ARGB_8888){
		pvr->pixels.pix32 = (COLOR*)malloc(sizeof(COLOR)*(width*height));
	}
	
	if(fmt == AGIDL_RGB_555 || fmt == AGIDL_BGR_555 || fmt == AGIDL_RGB_565 || fmt == AGIDL_BGR_565){
		pvr->pixels.pix16 = (COLOR16*)malloc(sizeof(COLOR16)*(width*height));
	}
	return pvr;
}

AGIDL_PVR* AGIDL_PVRCpyImg(AGIDL_PVR* pvr){
	AGIDL_PVR* pvrcpy = AGIDL_CreatePVR("pvrcpy.pvr",AGIDL_PVRGetWidth(pvr),AGIDL_PVRGetHeight(pvr),AGIDL_PVRGetClrFmt(pvr));
	AGIDL_PVRSetICPMode(pvrcpy,pvr->icp);
	AGIDL_PVRSetMaxDiff(pvrcpy,AGIDL_PVRGetMaxDiff(pvr));
	AGIDL_CLR_FMT fmt = AGIDL_PVRGetClrFmt(pvr);
	if(fmt == AGIDL_RGB_888 || fmt == AGIDL_BGR_888 || fmt == AGIDL_RGBA_8888 || fmt == AGIDL_ARGB_8888){
		AGIDL_PVRSyncPix(pvrcpy,pvr->pixels.pix32);
	}
	
	if(fmt == AGIDL_RGB_555 || fmt == AGIDL_BGR_555 || fmt == AGIDL_RGB_565 || fmt == AGIDL_BGR_565){
		AGIDL_PVRSyncPix16(pvrcpy,pvr->pixels.pix16);
	}
	return pvrcpy;
}

PVRClrFmt AGIDL_GetPVRClrFmt(u8 byte){
	switch(byte){
		case 0x00:{
			return PVR_RGB_555;
		}break;
		case 0x01:{
			return PVR_RGB_565;
		}break;
		case 0x02:{
			return PVR_ARGB_4444;
		}break;
		case 0x03:{
			return PVR_YUV_442;
		}break;
		case 0x05:{
			return PVR_ICP_16;
		}break;
		case 0x06:{
			return PVR_ICP_256;
		}break;
		default: return PVR_RGB_565; break;
	}
}

PVRImgType AGIDL_PVRGetImgType(u8 byte){
	switch(byte){
		case 0x01:{
			return PVR_IMG_SQUARE_TWIDDLED;
		}break;
		case 0x02:{
			return PVR_IMG_SQUARE_TWIDDLED_AND_MIPMAPPED;
		}break;
		case 0x05:{
			return PVR_IMG_ICP_256_TWIDDLED;
		}break;
		case 0x06:{
			return PVR_IMG_ICP_16_TWIDDLED;
		}break;
		case 0x07:{
			return PVR_IMG_ICP_256;
		}break;
		case 0x08:{
			return PVR_IMG_ICP_16;
		}break;
		case 0x09:{
			return PVR_IMG_RECTANGLE;
		}break;
		case 0x0D:{
			return PVR_IMG_RECTANGLE_TWIDDLED;
		}break;
		default: return PVR_IMG_SQUARE_TWIDDLED; break;
	}
}

int isImgPVR(u32 gbix, u32 pvrt){
	u8 g = ((gbix & 0xFF));
	u8 b = ((gbix & 0xFF00) >> 8);
	u8 i = ((gbix & 0xFF0000) >> 16);
	u8 x = ((gbix & 0xFF000000) >> 24);
	
	u8 p = ((pvrt & 0xFF));
	u8 v = ((pvrt & 0xFF00) >> 8);
	u8 r = ((pvrt & 0xFF0000) >> 16);
	u8 t = ((pvrt & 0xFF000000) >> 24);
	
	if(g != 'G' || b != 'B' || i != 'I' || x != 'X'){
		return 0;
	}
	else if(p != 'P' || v != 'V' || r != 'R' || t != 'T'){
		return 0;
	}
	else return 1;
}

void AGIDL_PVRDecodeHeader(AGIDL_PVR* pvr, FILE* file){
	fread(&pvr->header.id1,4,1,file);
	fread(&pvr->header.offset,4,1,file);
	fread(&pvr->header.global_index_1,4,1,file);
	fread(&pvr->header.global_index_2,4,1,file);
	fread(&pvr->header.id2,4,1,file);
	fread(&pvr->header.file_size,4,1,file);
	fread(&pvr->header.pvr_clr_fmt,1,1,file);
	fread(&pvr->header.pvr_img_type,1,1,file);
	fseek(file,2,SEEK_CUR);
	fread(&pvr->header.width,2,1,file);
	fread(&pvr->header.height,2,1,file);
	
	if(!isImgPVR(pvr->header.id1,pvr->header.id2)){
		printf("Current file is not a valid Sega Dreamcast PVR image - %s!\n",pvr->filename);
	}
}

void AGIDL_PVREncodeHeader(AGIDL_PVR* pvr, FILE* file){
	fwrite(&pvr->header.id1,4,1,file);
	fwrite(&pvr->header.offset,4,1,file);
	fwrite(&pvr->header.global_index_1,4,1,file);
	fwrite(&pvr->header.global_index_2,4,1,file);
	fwrite(&pvr->header.id2,4,1,file);
	fwrite(&pvr->header.file_size,4,1,file);
	fwrite(&pvr->header.pvr_clr_fmt,1,1,file);
	fwrite(&pvr->header.pvr_img_type,1,1,file);
	u16 zero = 0;
	fwrite(&zero,2,1,file);
	fwrite(&pvr->header.width,2,1,file);
	fwrite(&pvr->header.height,2,1,file);
}

void AGIDL_PVRDecodeImg(AGIDL_PVR* pvr, PVRClrFmt fmt, PVRImgType img, FILE* file){
	if(fmt == PVR_RGB_555 && img == PVR_IMG_RECTANGLE){
		AGIDL_PVRSetClrFmt(pvr,AGIDL_RGB_555);
		pvr->pixels.pix16 = (COLOR16*)malloc(sizeof(COLOR16)*(AGIDL_PVRGetWidth(pvr)*AGIDL_PVRGetHeight(pvr)));
		
		int x,y;
		for(y = 0; y < AGIDL_PVRGetHeight(pvr); y++){
			for(x = 0; x < AGIDL_PVRGetWidth(pvr); x++){
				COLOR16 clr;
				fread(&clr,2,1,file);
				AGIDL_PVRSetClr16(pvr,x,y,clr);
			}
		}
	}
	if(fmt == PVR_RGB_565 && img == PVR_IMG_RECTANGLE){
		AGIDL_PVRSetClrFmt(pvr,AGIDL_RGB_565);
		pvr->pixels.pix16 = (COLOR16*)malloc(sizeof(COLOR16)*(AGIDL_PVRGetWidth(pvr)*AGIDL_PVRGetHeight(pvr)));
		
		int x,y;
		for(y = 0; y < AGIDL_PVRGetHeight(pvr); y++){
			for(x = 0; x < AGIDL_PVRGetWidth(pvr); x++){
				COLOR16 clr;
				fread(&clr,2,1,file);
				AGIDL_PVRSetClr16(pvr,x,y,clr);
			}
		}
	}	
	if(fmt == PVR_ARGB_4444 && img == PVR_IMG_RECTANGLE){
		AGIDL_PVRSetClrFmt(pvr,AGIDL_RGB_555);
		pvr->pixels.pix16 = (COLOR16*)malloc(sizeof(COLOR16)*(AGIDL_PVRGetWidth(pvr)*AGIDL_PVRGetHeight(pvr)));
		
		int x,y;
		for(y = 0; y < AGIDL_PVRGetHeight(pvr); y++){
			for(x = 0; x < AGIDL_PVRGetWidth(pvr); x++){
				COLOR16 clr;
				fread(&clr,2,1,file);
				
				u8 r = ((clr & 0xf00) >> 8);
				u8 g = ((clr & 0xf0) >> 4);
				u8 b = ((clr & 0xf));
				
				r = r << 1; g = g << 1; b = b << 1;
				
				r |= r >> 4; g |= g >> 4; b |= b >> 4;
				
				COLOR16 color = AGIDL_RGB16(r,g,b,AGIDL_RGB_555);
				
				AGIDL_PVRSetClr16(pvr,x,y,color);
			}
		}
	}
}

void AGIDL_PVREncodeIMG(AGIDL_PVR* pvr, FILE* file){
	int x,y;
	for(y = 0; y < AGIDL_PVRGetHeight(pvr); y++){
		for(x = 0; x < AGIDL_PVRGetWidth(pvr); x++){
			COLOR16 clr = AGIDL_PVRGetClr16(pvr,x,y);
			fwrite(&clr,2,1,file);
		}
	}
}

u32 AGIDL_GetTwiddleValue(u32 i){
	u32 result = 0, resultbit = 1;
	while(i != 0){
		if((i & 1) != 0){
			result |= resultbit;
		}
		
		i >>= 1;
		
		resultbit <<= 2;
	}
	return result;
}

u32 AGIDL_GetDetwiddledIndex(u32 x, u32 y){
	return (AGIDL_GetTwiddleValue(x) << 1) | AGIDL_GetTwiddleValue(y);
}

void AGIDL_PVRDecodeTwiddledImg(AGIDL_PVR* pvr, PVRClrFmt fmt, PVRImgType img, FILE* file){
	if(fmt == PVR_RGB_555 && img == PVR_IMG_SQUARE_TWIDDLED){
		AGIDL_PVRSetClrFmt(pvr,AGIDL_RGB_555);
		pvr->pixels.pix16 = (COLOR16*)malloc(sizeof(COLOR16)*(AGIDL_PVRGetWidth(pvr)*AGIDL_PVRGetHeight(pvr)));
		
		COLOR16* buf = (COLOR16*)malloc(sizeof(COLOR16)*(AGIDL_PVRGetWidth(pvr)*AGIDL_PVRGetHeight(pvr)));
		
		int img_size = AGIDL_PVRGetWidth(pvr) * AGIDL_PVRGetHeight(pvr);
		
		fread(buf,2,img_size,file);
		
		int x,y;
		for(y = 0; y < AGIDL_PVRGetHeight(pvr); y++){
			for(x = 0; x < AGIDL_PVRGetWidth(pvr); x++){
				
				int index = AGIDL_GetDetwiddledIndex(x,y);
				
				AGIDL_PVRSetClr16(pvr,x,y,buf[index]);
			}
		}
		
		free(buf);
	}	
	else if(fmt == PVR_RGB_565 && img == PVR_IMG_SQUARE_TWIDDLED){
		AGIDL_PVRSetClrFmt(pvr,AGIDL_RGB_565);
		pvr->pixels.pix16 = (COLOR16*)malloc(sizeof(COLOR16)*(AGIDL_PVRGetWidth(pvr)*AGIDL_PVRGetHeight(pvr)));
		
		COLOR16* buf = (COLOR16*)malloc(sizeof(COLOR16)*(AGIDL_PVRGetWidth(pvr)*AGIDL_PVRGetHeight(pvr)));
		
		int img_size = 2 * AGIDL_PVRGetWidth(pvr) * AGIDL_PVRGetHeight(pvr);
		
		fread(buf,2,img_size,file);
		
		int x,y;
		for(y = 0; y < AGIDL_PVRGetHeight(pvr); y++){
			for(x = 0; x < AGIDL_PVRGetWidth(pvr); x++){
				
				int index = AGIDL_GetDetwiddledIndex(x,y);
				
				AGIDL_PVRSetClr16(pvr,x,y,buf[index]);
			}
		}
		
		free(buf);
	}
	else if(fmt == PVR_ARGB_4444 && img == PVR_IMG_SQUARE_TWIDDLED){
		AGIDL_PVRSetClrFmt(pvr,AGIDL_RGB_555);
		pvr->pixels.pix16 = (COLOR16*)malloc(sizeof(COLOR16)*(AGIDL_PVRGetWidth(pvr)*AGIDL_PVRGetHeight(pvr)));
		
		COLOR16* buf = (COLOR16*)malloc(sizeof(COLOR16)*(AGIDL_PVRGetWidth(pvr)*AGIDL_PVRGetHeight(pvr)));
		
		int img_size = 2 * AGIDL_PVRGetWidth(pvr) * AGIDL_PVRGetHeight(pvr);
		
		fread(buf,2,img_size,file);
		
		int x,y;
		for(y = 0; y < AGIDL_PVRGetHeight(pvr); y++){
			for(x = 0; x < AGIDL_PVRGetWidth(pvr); x++){
				
				int index = AGIDL_GetDetwiddledIndex(x,y);
				
				COLOR16 clr = buf[index];
				
				u8 r = ((clr & 0xf00) >> 8);
				u8 g = ((clr & 0xf0) >> 4);
				u8 b = ((clr & 0xf));
				
				r = r << 1; g = g << 1; b = b << 1;
				
				r |= r >> 4; g |= g >> 4; b |= b >> 4;
				
				COLOR16 color = AGIDL_RGB16(r,g,b,AGIDL_RGB_555);
				
				AGIDL_PVRSetClr16(pvr,x,y,color);
			}
		}
		
		free(buf);
	}
}

AGIDL_PVR * AGIDL_LoadPVR(char* filename){
	FILE* file = fopen(filename,"rb");
	
	if(file == NULL){
		printf("Could not locate PVR image file - %s!\n",filename);
	}
	
	AGIDL_PVR* pvr = (AGIDL_PVR*)malloc(sizeof(AGIDL_PVR));
	pvr->filename = (char*)malloc(strlen(filename)+1);
	AGIDL_FilenameCpy(pvr->filename,filename);
	AGIDL_PVRDecodeHeader(pvr,file);
	
	PVRClrFmt fmt = AGIDL_GetPVRClrFmt(pvr->header.pvr_clr_fmt);
	PVRImgType img = AGIDL_PVRGetImgType(pvr->header.pvr_img_type);
	
	AGIDL_PVRDecodeImg(pvr,fmt,img,file);
	AGIDL_PVRDecodeTwiddledImg(pvr,fmt,img,file);
	
	fclose(file);
	
	return pvr;
}

void AGIDL_ExportPVR(AGIDL_PVR* pvr){
	FILE* file = fopen(pvr->filename,"wb");
	
	if(file == NULL){
		printf("Could not create PVR image - %s!\n",pvr->filename);
	}
	
	u8 g = 'G', b = 'B', i = 'I', x = 'X';
	u8 p = 'P', v = 'V', r = 'R', t = 'T';
	
	pvr->header.id1 = x << 24 | i << 16 | b << 8 | g;
	pvr->header.offset = 8;
	pvr->header.global_index_1 = 0;
	pvr->header.global_index_2 = 0;
	pvr->header.id2 = t << 24 | r << 16 | v << 8 | p;
	pvr->header.file_size = 30 + (2 * AGIDL_PVRGetWidth(pvr) * AGIDL_PVRGetHeight(pvr));
	
	if(pvr->fmt == AGIDL_RGB_565 && pvr->fmt == AGIDL_BGR_565){
		pvr->header.pvr_clr_fmt = PVR_RGB_565;
	}
	else{
		pvr->header.pvr_clr_fmt = PVR_RGB_555;
	}
	
	pvr->header.pvr_img_type = PVR_IMG_RECTANGLE;
	
	AGIDL_PVREncodeHeader(pvr,file);
	
	switch(pvr->fmt){
		case AGIDL_RGB_555:{
			AGIDL_PVREncodeIMG(pvr,file);
		}break;	
		case AGIDL_RGB_565:{
			AGIDL_PVREncodeIMG(pvr,file);
		}break;
		case AGIDL_BGR_555:{
			AGIDL_PVRBGR2RGB(pvr);
			AGIDL_PVREncodeIMG(pvr,file);
			AGIDL_PVRRGB2BGR(pvr);
		}break;
		case AGIDL_BGR_565:{
			AGIDL_PVRBGR2RGB(pvr);
			AGIDL_PVREncodeIMG(pvr,file);
			AGIDL_PVRRGB2BGR(pvr);
		}break;
		case AGIDL_RGB_888:{
			AGIDL_PVRConvert24BPPTO16BPP(pvr);
			AGIDL_PVREncodeIMG(pvr,file);
			AGIDL_PVRConvert16BPPTO24BPP(pvr);
		}break;
		case AGIDL_BGR_888:{
			AGIDL_PVRConvert24BPPTO16BPP(pvr);
			AGIDL_PVRBGR2RGB(pvr);
			AGIDL_PVREncodeIMG(pvr,file);
			AGIDL_PVRRGB2BGR(pvr);
			AGIDL_PVRConvert16BPPTO24BPP(pvr);
		}break;
		case AGIDL_RGBA_8888:{
			AGIDL_PVRConvertRGBA2RGB(pvr);
			AGIDL_PVRConvert24BPPTO16BPP(pvr);
			AGIDL_PVREncodeIMG(pvr,file);
			AGIDL_PVRConvert16BPPTO24BPP(pvr);
		}break;
		case AGIDL_ARGB_8888:{
			AGIDL_PVRConvertRGBA2RGB(pvr);
			AGIDL_PVRConvert24BPPTO16BPP(pvr);
			AGIDL_PVREncodeIMG(pvr,file);
			AGIDL_PVRConvert16BPPTO24BPP(pvr);
		}break;
	}
	
	fclose(file);
}