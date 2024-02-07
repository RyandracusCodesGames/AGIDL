/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023-2024 Ryandracus Chapman
*
*   Library: libagidl
*   File: agidl_imgp_mipmap.c
*   Date: 1/23/2024
*   Version: 0.2b
*   Updated: 2/6/2024
*   Author: Ryandracus Chapman
*
********************************************/
#include <stdlib.h>
#include "agidl_imgp_mipmap.h"
#include "agidl_cc_manager.h"
#include "agidl_img_core.h"
#include "agidl_imgp_impl.h"
#include "agidl_mmu_utils.h"
#include "agidl_file_utils.h"

AGIDL_MIPMAP* AGIDL_CreateMipmapMMU(u16 width, u16 height, AGIDL_CLR_FMT fmt, AGIDL_Bool IsLinear){
	u16 w = width;
	u16 h = height;
	
	u16 mipcount = 0;
	
	while(w >= 2 && h >= 2){
		w >>= 1;
		h >>= 1;
		
		mipcount++;
	}
	
	AGIDL_MIPMAP* mipmap = (AGIDL_MIPMAP*)malloc(sizeof(AGIDL_MIPMAP));
	mipmap->width = width;
	mipmap->height = height;
	mipmap->fmt = fmt;
	mipmap->IsLinear = IsLinear;
	mipmap->mipcount = mipcount;
	
	return mipmap;
}

void AGIDL_DestroyMipmapMMU(AGIDL_MIPMAP* mipmap){
	int i;
	for(i = 0; i < mipmap->mipcount; i++){
		if(mipmap->mipmap[i].img_data != NULL){
			free(mipmap->mipmap[i].img_data);
			mipmap->mipmap[i].img_data = NULL;
		}
	}
	
	free(mipmap);
	
	if(mipmap != NULL){
		mipmap = NULL;
	}
}

AGIDL_MIPMAP* AGIDL_GenerateMipmapFromImgData(void* data, u16 width, u16 height, AGIDL_CLR_FMT fmt){
	AGIDL_MIPMAP* mipmap = AGIDL_CreateMipmapMMU(width,height,fmt,FALSE);
	
	if(AGIDL_GetBitCount(fmt) == 16){
		COLOR16* clr_data = (COLOR16*)data;
		COLOR16* clr_cpy = (COLOR16*)AGIDL_AllocImgDataMMU(width,height,fmt);
		
		mipmap->mipmap[0].width = width;
		mipmap->mipmap[0].height = height;
		mipmap->mipmap[0].fmt = fmt;
		mipmap->mipmap[0].img_data = (COLOR16*)AGIDL_AllocImgDataMMU(width,height,fmt);
		
		AGIDL_ClrMemcpy16(mipmap->mipmap[0].img_data,clr_data,width*height);
		AGIDL_ClrMemcpy16(clr_cpy,clr_data,width*height);
		
		int i;
		for(i = 1; i < mipmap->mipcount; i++){
			
			width >>= 1;
			height >>= 1;
			
			u16 w = width << 1;
			u16 h = height << 1;
			
			mipmap->mipmap[i].width = width;
			mipmap->mipmap[i].height = height;
			mipmap->mipmap[i].fmt = fmt;
			mipmap->mipmap[i].img_data = (COLOR16*)AGIDL_AllocImgDataMMU(width,height,fmt);
			
			clr_cpy = (COLOR16*)AGIDL_HalfImgDataNearest(clr_cpy,&w,&h,fmt);
			AGIDL_ClrMemcpy16(mipmap->mipmap[i].img_data,clr_cpy,width*height);
		}
		
		free(clr_cpy);
	}
	else{
		COLOR* clr_data = (COLOR*)data;
		COLOR* clr_cpy = (COLOR*)AGIDL_AllocImgDataMMU(width,height,fmt);
		
		mipmap->mipmap[0].width = width;
		mipmap->mipmap[0].height = height;
		mipmap->mipmap[0].fmt = fmt;
		mipmap->mipmap[0].img_data = (COLOR*)AGIDL_AllocImgDataMMU(width,height,fmt);
		
		AGIDL_ClrMemcpy(mipmap->mipmap[0].img_data,clr_data,width*height);
		AGIDL_ClrMemcpy(clr_cpy,clr_data,width*height);
		
		int i;
		for(i = 1; i < mipmap->mipcount; i++){
			
			width >>= 1;
			height >>= 1;
			
			u16 w = width << 1;
			u16 h = height << 1;
			
			mipmap->mipmap[i].width = width;
			mipmap->mipmap[i].height = height;
			mipmap->mipmap[i].fmt = fmt;
			mipmap->mipmap[i].img_data = (COLOR*)AGIDL_AllocImgDataMMU(width,height,fmt);
			
			clr_cpy = (COLOR*)AGIDL_HalfImgDataNearest(clr_cpy,&w,&h,fmt);
			AGIDL_ClrMemcpy(mipmap->mipmap[i].img_data,clr_cpy,width*height);
		}
		
		free(clr_cpy);
	}
	
	return mipmap;
}

AGIDL_MIPMAP* AGIDL_LoadMipmapImgData(FILE* file, u16 width, u16 height, AGIDL_CLR_FMT fmt, u8 count, AGIDL_Bool IsLinear){
	AGIDL_MIPMAP* mipmap = (AGIDL_MIPMAP*)malloc(sizeof(AGIDL_MIPMAP));
	mipmap->width = width;
	mipmap->height = height;
	mipmap->fmt = fmt;
	mipmap->IsLinear = IsLinear;
	mipmap->mipcount = count;
	
	if(AGIDL_GetBitCount(fmt) == 16){
		int i;
		for(i = 0; i < mipmap->mipcount; i++){
			mipmap->mipmap[i].width = width;
			mipmap->mipmap[i].height = height;
			mipmap->mipmap[i].fmt = fmt;
			mipmap->mipmap[i].img_data = (COLOR16*)AGIDL_AllocImgDataMMU(width,height,fmt);
			AGIDL_ReadBufClr16(file,mipmap->mipmap[i].img_data,width,height);
			
			if(IsLinear == TRUE){
				int x,y;
				for(y = 0; y < height; y++){
					for(x = 0; x < width; x++){
						u16 clr = AGIDL_GetClr16(mipmap->mipmap[i].img_data,x,y,width,height);
						clr = AGIDL_GammaCorrectColor(clr,2.2f,mipmap->fmt);
						AGIDL_SetClr16(mipmap->mipmap[i].img_data,clr,x,y,width,height);
					}
				}
			}
			
			width >>= 1;
			height >>= 1;
		}
	}
	else{
		int i;
		for(i = 0; i < mipmap->mipcount; i++){
			mipmap->mipmap[i].width = width;
			mipmap->mipmap[i].height = height;
			mipmap->mipmap[i].fmt = fmt;
			mipmap->mipmap[i].img_data = (COLOR*)AGIDL_AllocImgDataMMU(width,height,fmt);
			
			if(AGIDL_GetBitCount(fmt) == 24){
				AGIDL_ReadBufRGB(file,mipmap->mipmap[i].img_data,width,height);
			}
			else{
				AGIDL_ReadBufRGBA(file,mipmap->mipmap[i].img_data,width,height);
			}
			
			if(IsLinear == TRUE){
				int x,y;
				for(y = 0; y < height; y++){
					for(x = 0; x < width; x++){
						u32 clr = AGIDL_GetClr(mipmap->mipmap[i].img_data,x,y,width,height);
						clr = AGIDL_GammaCorrectColor(clr,2.2f,mipmap->fmt);
						AGIDL_SetClr(mipmap->mipmap[i].img_data,clr,x,y,width,height);
					}
				}
			}
			
			width >>= 1;
			height >>= 1;
		}
	}
	
	return mipmap;
}

void AGIDL_ExportMipmap(AGIDL_MIPMAP* mipmap, AGIDL_IMG_TYPE img_type, AGIDL_Bool flip){
	int i;
	for(i = 0; i < mipmap->mipcount; i++){
		u16 w = mipmap->mipmap[i].width;
		u16 h = mipmap->mipmap[i].height;
		
		char filename[30];
		
		switch(img_type){
			case AGIDL_IMG_BMP:{
				sprintf(filename,"mipmap_%d.bmp",i+1);
				AGIDL_BMP* bmp = AGIDL_CreateBMP(filename,w,h,mipmap->fmt);
				if(AGIDL_GetBitCount(mipmap->fmt) == 16){
					COLOR16* img = (COLOR16*)mipmap->mipmap[i].img_data;
					AGIDL_BMPSyncPix16(bmp,img);
				}
				else{
					COLOR* img = (COLOR*)mipmap->mipmap[i].img_data;
					AGIDL_BMPSyncPix(bmp,img);
				}
				if(flip == TRUE){
					AGIDL_FlipHorzBMP(bmp);
				}
				AGIDL_ExportBMP(bmp);
				AGIDL_FreeBMP(bmp);
			}break;
			case AGIDL_IMG_TGA:{
				sprintf(filename,"mipmap_%d.tga",i+1);
				AGIDL_TGA* tga = AGIDL_CreateTGA(filename,w,h,mipmap->fmt);
				if(AGIDL_GetBitCount(mipmap->fmt) == 16){
					COLOR16* img = (COLOR16*)mipmap->mipmap[i].img_data;
					AGIDL_TGASyncPix16(tga,img);
				}
				else{
					COLOR* img = (COLOR*)mipmap->mipmap[i].img_data;
					AGIDL_TGASyncPix(tga,img);
				}
				if(flip == TRUE){
					AGIDL_FlipHorzTGA(tga);
				}
				AGIDL_ExportTGA(tga);
				AGIDL_FreeTGA(tga);
			}break;
			case AGIDL_IMG_TIM:{
				sprintf(filename,"mipmap_%d.tim",i+1);
				AGIDL_TIM* tim = AGIDL_CreateTIM(filename,w,h,mipmap->fmt);
				if(AGIDL_GetBitCount(mipmap->fmt) == 16){
					COLOR16* img = (COLOR16*)mipmap->mipmap[i].img_data;
					AGIDL_TIMSyncPix16(tim,img);
				}
				else{
					COLOR* img = (COLOR*)mipmap->mipmap[i].img_data;
					AGIDL_TIMSyncPix(tim,img);
				}
				if(flip == TRUE){
					AGIDL_FlipHorzTIM(tim);
				}
				AGIDL_ExportTIM(tim);
				AGIDL_FreeTIM(tim);
			}break;
			case AGIDL_IMG_PCX:{
				sprintf(filename,"mipmap_%d.pcx",i+1);
				AGIDL_PCX* pcx = AGIDL_CreatePCX(filename,w,h,mipmap->fmt);
				if(AGIDL_GetBitCount(mipmap->fmt) == 16){
					COLOR16* img = (COLOR16*)mipmap->mipmap[i].img_data;
					AGIDL_PCXSyncPix16(pcx,img);
				}
				else{
					COLOR* img = (COLOR*)mipmap->mipmap[i].img_data;
					AGIDL_PCXSyncPix(pcx,img);
				}
				if(flip == TRUE){
					AGIDL_FlipHorzPCX(pcx);
				}
				AGIDL_ExportPCX(pcx);
				AGIDL_FreePCX(pcx);
			}break;
			case AGIDL_IMG_LMP:{
				sprintf(filename,"mipmap_%d.lmp",i+1);
				AGIDL_LMP* lmp = AGIDL_CreateLMP(filename,w,h,mipmap->fmt);
				if(AGIDL_GetBitCount(mipmap->fmt) == 16){
					COLOR16* img = (COLOR16*)mipmap->mipmap[i].img_data;
					AGIDL_LMPSyncPix16(lmp,img);
				}
				else{
					COLOR* img = (COLOR*)mipmap->mipmap[i].img_data;
					AGIDL_LMPSyncPix(lmp,img);
				}
				if(flip == TRUE){
					AGIDL_FlipHorzLMP(lmp);
				}
				AGIDL_ExportLMP(lmp);
				AGIDL_FreeLMP(lmp);
			}break;
			case AGIDL_IMG_PVR:{
				sprintf(filename,"mipmap_%d.pvr",i+1);
				AGIDL_PVR* pvr = AGIDL_CreatePVR(filename,w,h,mipmap->fmt);
				if(AGIDL_GetBitCount(mipmap->fmt) == 16){
					COLOR16* img = (COLOR16*)mipmap->mipmap[i].img_data;
					AGIDL_PVRSyncPix16(pvr,img);
				}
				else{
					COLOR* img = (COLOR*)mipmap->mipmap[i].img_data;
					AGIDL_PVRSyncPix(pvr,img);
				}
				if(flip == TRUE){
					AGIDL_FlipHorzPVR(pvr);
				}
				AGIDL_ExportPVR(pvr);
				AGIDL_FreePVR(pvr);
			}break;
			case AGIDL_IMG_GXT:{
				sprintf(filename,"mipmap_%d.gxt",i+1);
				AGIDL_GXT* gxt = AGIDL_CreateGXT(filename,w,h,mipmap->fmt);
				if(AGIDL_GetBitCount(mipmap->fmt) == 16){
					COLOR16* img = (COLOR16*)mipmap->mipmap[i].img_data;
					AGIDL_GXTSyncPix16(gxt,img);
				}
				else{
					COLOR* img = (COLOR*)mipmap->mipmap[i].img_data;
					AGIDL_GXTSyncPix(gxt,img);
				}
				if(flip == TRUE){
					AGIDL_FlipHorzGXT(gxt);
				}
				AGIDL_ExportGXT(gxt);
				AGIDL_FreeGXT(gxt);
			}break;
			case AGIDL_IMG_BTI:{
				sprintf(filename,"mipmap_%d.bti",i+1);
				AGIDL_BTI* bti = AGIDL_CreateBTI(filename,w,h,mipmap->fmt);
				if(AGIDL_GetBitCount(mipmap->fmt) == 16){
					COLOR16* img = (COLOR16*)mipmap->mipmap[i].img_data;
					AGIDL_BTISyncPix16(bti,img);
				}
				else{
					COLOR* img = (COLOR*)mipmap->mipmap[i].img_data;
					AGIDL_BTISyncPix(bti,img);
				}
				if(flip == TRUE){
					AGIDL_FlipHorzBTI(bti);
				}
				AGIDL_ExportBTI(bti);
				AGIDL_FreeBTI(bti);
			}break;
		}
	}
}
