/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023 Ryandracus Chapman
*
*   Library: libagidl
*   File: agidl_img_converter.c
*   Date: 11/3/2023
*   Version: 0.1b
*   Updated: 11/21/2023
*   Author: Ryandracus Chapman
*
********************************************/
#include <stdio.h>
#include <stdlib.h>
#include "agidl_img_converter.h"

AGIDL_TGA* AGIDL_ConvertBMP2TGA(AGIDL_BMP* bmp){
	AGIDL_TGA* tga = AGIDL_CreateTGA(AGIDL_StrCpy(AGIDL_GetImgName(bmp->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_TGA)),AGIDL_BMPGetWidth(bmp),AGIDL_BMPGetHeight(bmp),
	AGIDL_BMPGetClrFmt(bmp));
	AGIDL_TGASetICPMode(tga,bmp->icp);
	AGIDL_TGASetMaxDiff(tga,AGIDL_BMPGetMaxDiff(bmp));
	AGIDL_TGASetCompression(tga,bmp->compression);
	
	int bits = AGIDL_GetBitCount(AGIDL_BMPGetClrFmt(bmp));
	
	if(bits == 24 || bits == 32){
		AGIDL_TGASyncPix(tga,bmp->pixels.pix32);
	}
	else{
		AGIDL_TGASyncPix16(tga,bmp->pixels.pix16);
	}
	return tga;
}

AGIDL_TIM* AGIDL_ConvertBMP2TIM(AGIDL_BMP* bmp){
	AGIDL_TIM* tim = AGIDL_CreateTIM(AGIDL_StrCpy(AGIDL_GetImgName(bmp->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_TIM)),AGIDL_BMPGetWidth(bmp),AGIDL_BMPGetHeight(bmp),
	AGIDL_BMPGetClrFmt(bmp));
	AGIDL_TIMSetICPMode(tim,bmp->icp);
	AGIDL_TIMSetMaxDiff(tim,AGIDL_BMPGetMaxDiff(bmp));
	
	int bits = AGIDL_GetBitCount(AGIDL_BMPGetClrFmt(bmp));
	
	if(bits == 24 || bits == 32){
		AGIDL_TIMSyncPix(tim,bmp->pixels.pix32);
	}
	else{
		AGIDL_TIMSyncPix16(tim,bmp->pixels.pix16);
	}
	return tim;
}

AGIDL_PCX* AGIDL_ConvertBMP2PCX(AGIDL_BMP* bmp){
	AGIDL_PCX* pcx = AGIDL_CreatePCX(AGIDL_StrCpy(AGIDL_GetImgName(bmp->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_PCX)),AGIDL_BMPGetWidth(bmp),AGIDL_BMPGetHeight(bmp),
	AGIDL_BMPGetClrFmt(bmp));
	
	int bits = AGIDL_GetBitCount(AGIDL_BMPGetClrFmt(bmp));
	
	if(bits == 24 || bits == 32){
		AGIDL_PCXSyncPix(pcx,bmp->pixels.pix32);
	}
	else{
		AGIDL_PCXSyncPix16(pcx,bmp->pixels.pix16);
	}
	return pcx;
}

AGIDL_LMP* AGIDL_ConvertBMP2LMP(AGIDL_BMP* bmp){
	AGIDL_LMP* lmp = AGIDL_CreateLMP(AGIDL_StrCpy(AGIDL_GetImgName(bmp->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_LMP)),AGIDL_BMPGetWidth(bmp),AGIDL_BMPGetHeight(bmp),
	AGIDL_BMPGetClrFmt(bmp));
	AGIDL_LMPSetMaxDiff(lmp,AGIDL_BMPGetMaxDiff(bmp));
	
	int bits = AGIDL_GetBitCount(AGIDL_BMPGetClrFmt(bmp));
	
	if(bits == 24 || bits == 32){
		AGIDL_LMPSyncPix(lmp,bmp->pixels.pix32);
	}
	else{
		AGIDL_LMPSyncPix16(lmp,bmp->pixels.pix16);
	}
	return lmp;
}

AGIDL_PVR* AGIDL_ConvertBMP2PVR(AGIDL_BMP* bmp){
	AGIDL_PVR* pvr = AGIDL_CreatePVR(AGIDL_StrCpy(AGIDL_GetImgName(bmp->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_PVR)),AGIDL_BMPGetWidth(bmp),AGIDL_BMPGetHeight(bmp),
	AGIDL_BMPGetClrFmt(bmp));
	AGIDL_PVRSetMaxDiff(pvr,AGIDL_BMPGetMaxDiff(bmp));
	
	int bits = AGIDL_GetBitCount(AGIDL_BMPGetClrFmt(bmp));
	
	if(bits == 24 || bits == 32){
		AGIDL_PVRSyncPix(pvr,bmp->pixels.pix32);
	}
	else{
		AGIDL_PVRSyncPix16(pvr,bmp->pixels.pix16);
	}
	return pvr;
}

AGIDL_BTI* AGIDL_ConvertBMP2BTI(AGIDL_BMP* bmp){
	AGIDL_BTI* bti = AGIDL_CreateBTI(AGIDL_StrCpy(AGIDL_GetImgName(bmp->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_BTI)),AGIDL_BMPGetWidth(bmp),AGIDL_BMPGetHeight(bmp),
	AGIDL_BMPGetClrFmt(bmp));
	AGIDL_BTISetICPMode(bti,bmp->icp);
	AGIDL_BTISetMaxDiff(bti,AGIDL_BMPGetMaxDiff(bmp));
	
	int bits = AGIDL_GetBitCount(AGIDL_BMPGetClrFmt(bmp));
	
	if(bits == 24 || bits == 32){
		AGIDL_BTISyncPix(bti,bmp->pixels.pix32);
	}
	else{
		AGIDL_BTISyncPix16(bti,bmp->pixels.pix16);
	}
	return bti;
}

AGIDL_BMP* AGIDL_ConvertTGA2BMP(AGIDL_TGA* tga){
	AGIDL_BMP* bmp = AGIDL_CreateBMP(AGIDL_StrCpy(AGIDL_GetImgName(tga->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_BMP)),AGIDL_TGAGetWidth(tga),AGIDL_TGAGetHeight(tga),
	AGIDL_TGAGetClrFmt(tga));
	AGIDL_BMPSetICPMode(bmp,tga->icp);
	AGIDL_BMPSetMaxDiff(bmp,AGIDL_TGAGetMaxDiff(tga));
	AGIDL_BMPSetCompression(bmp,tga->compression);
	
	int bits = AGIDL_GetBitCount(AGIDL_TGAGetClrFmt(tga));
	
	if(bits == 24 || bits == 32){
		AGIDL_BMPSyncPix(bmp,tga->pixels.pix32);
	}
	else{
		AGIDL_BMPSyncPix16(bmp,tga->pixels.pix16);
	}
	return bmp;
}

AGIDL_TIM* AGIDL_ConvertTGA2TIM(AGIDL_TGA* tga){
	AGIDL_TIM* tim = AGIDL_CreateTIM(AGIDL_StrCpy(AGIDL_GetImgName(tga->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_TIM)),AGIDL_TGAGetWidth(tga),AGIDL_TGAGetHeight(tga),
	AGIDL_TGAGetClrFmt(tga));
	AGIDL_TIMSetICPMode(tim,tga->icp);
	AGIDL_TIMSetMaxDiff(tim,AGIDL_TGAGetMaxDiff(tga));
	
	int bits = AGIDL_GetBitCount(AGIDL_TGAGetClrFmt(tga));
	
	if(bits == 24 || bits == 32){
		AGIDL_TIMSyncPix(tim,tga->pixels.pix32);
	}
	else{
		AGIDL_TIMSyncPix16(tim,tga->pixels.pix16);
	}
	return tim;
}

AGIDL_PCX* AGIDL_ConvertTGA2PCX(AGIDL_TGA* tga){
	AGIDL_PCX* pcx = AGIDL_CreatePCX(AGIDL_StrCpy(AGIDL_GetImgName(tga->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_PCX)),AGIDL_TGAGetWidth(tga),AGIDL_TGAGetHeight(tga),
	AGIDL_TGAGetClrFmt(tga));
	
	int bits = AGIDL_GetBitCount(AGIDL_TGAGetClrFmt(tga));
	
	if(bits == 24 || bits == 32){
		AGIDL_PCXSyncPix(pcx,tga->pixels.pix32);
	}
	else{
		AGIDL_PCXSyncPix16(pcx,tga->pixels.pix16);
	}
	return pcx;
}

AGIDL_LMP* AGIDL_ConvertTGA2LMP(AGIDL_TGA* tga){
	AGIDL_LMP* lmp = AGIDL_CreateLMP(AGIDL_StrCpy(AGIDL_GetImgName(tga->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_LMP)),AGIDL_TGAGetWidth(tga),AGIDL_TGAGetHeight(tga),
	AGIDL_TGAGetClrFmt(tga));
	AGIDL_LMPSetMaxDiff(lmp,AGIDL_TGAGetMaxDiff(tga));
	
	int bits = AGIDL_GetBitCount(AGIDL_TGAGetClrFmt(tga));
	
	if(bits == 24 || bits == 32){
		AGIDL_LMPSyncPix(lmp,tga->pixels.pix32);
	}
	else{
		AGIDL_LMPSyncPix16(lmp,tga->pixels.pix16);
	}
	return lmp;
}

AGIDL_PVR* AGIDL_ConvertTGA2PVR(AGIDL_TGA* tga){
	AGIDL_PVR* pvr = AGIDL_CreatePVR(AGIDL_StrCpy(AGIDL_GetImgName(tga->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_PVR)),AGIDL_TGAGetWidth(tga),AGIDL_TGAGetHeight(tga),
	AGIDL_TGAGetClrFmt(tga));
	AGIDL_PVRSetMaxDiff(pvr,AGIDL_TGAGetMaxDiff(tga));
	
	int bits = AGIDL_GetBitCount(AGIDL_TGAGetClrFmt(tga));
	
	if(bits == 24 || bits == 32){
		AGIDL_PVRSyncPix(pvr,tga->pixels.pix32);
	}
	else{
		AGIDL_PVRSyncPix16(pvr,tga->pixels.pix16);
	}
	return pvr;
}

AGIDL_GXT* AGIDL_ConvertTGA2GXT(AGIDL_TGA* tga){
	AGIDL_GXT* gxt = AGIDL_CreateGXT(AGIDL_StrCpy(AGIDL_GetImgName(tga->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_GXT)),AGIDL_TGAGetWidth(tga),AGIDL_TGAGetHeight(tga),
	AGIDL_TGAGetClrFmt(tga));
	AGIDL_GXTSetICPMode(gxt,tga->icp);
	AGIDL_GXTSetMaxDiff(gxt,AGIDL_TGAGetMaxDiff(tga));
	
	int bits = AGIDL_GetBitCount(AGIDL_TGAGetClrFmt(tga));
	
	if(bits == 24 || bits == 32){
		AGIDL_GXTSyncPix(gxt,tga->pixels.pix32);
	}
	else{
		AGIDL_GXTSyncPix16(gxt,tga->pixels.pix16);
	}
	return gxt;
}

AGIDL_BTI* AGIDL_ConvertTGA2BTI(AGIDL_TGA* tga){
	AGIDL_BTI* bti = AGIDL_CreateBTI(AGIDL_StrCpy(AGIDL_GetImgName(tga->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_BTI)),AGIDL_TGAGetWidth(tga),AGIDL_TGAGetHeight(tga),
	AGIDL_TGAGetClrFmt(tga));
	AGIDL_BTISetICPMode(bti,tga->icp);
	AGIDL_BTISetMaxDiff(bti,AGIDL_TGAGetMaxDiff(tga));
	
	int bits = AGIDL_GetBitCount(AGIDL_TGAGetClrFmt(tga));
	
	if(bits == 24 || bits == 32){
		AGIDL_BTISyncPix(bti,tga->pixels.pix32);
	}
	else{
		AGIDL_BTISyncPix16(bti,tga->pixels.pix16);
	}
	return bti;
}

AGIDL_BMP* AGIDL_ConvertTIM2BMP(AGIDL_TIM* tim){
	AGIDL_BMP* bmp = AGIDL_CreateBMP(AGIDL_StrCpy(AGIDL_GetImgName(tim->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_BMP)),AGIDL_TIMGetWidth(tim),AGIDL_TIMGetHeight(tim),
	AGIDL_TIMGetClrFmt(tim));
	AGIDL_BMPSetICPMode(bmp,tim->icp);
	AGIDL_BMPSetMaxDiff(bmp,AGIDL_TIMGetMaxDiff(tim));
	
	int bits = AGIDL_GetBitCount(AGIDL_TIMGetClrFmt(tim));
	
	if(bits == 24 || bits == 32){
		AGIDL_BMPSyncPix(bmp,tim->pixels.pix32);
	}
	else{
		AGIDL_BMPSyncPix16(bmp,tim->pixels.pix16);
	}

	return bmp;
}

AGIDL_TGA* AGIDL_ConvertTIM2TGA(AGIDL_TIM* tim){
	AGIDL_TGA* tga = AGIDL_CreateTGA(AGIDL_StrCpy(AGIDL_GetImgName(tim->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_TGA)),AGIDL_TIMGetWidth(tim),AGIDL_TIMGetHeight(tim),
	AGIDL_TIMGetClrFmt(tim));
	AGIDL_TGASetICPMode(tga,tim->icp);
	AGIDL_TGASetMaxDiff(tga,AGIDL_TIMGetMaxDiff(tim));
	
	int bits = AGIDL_GetBitCount(AGIDL_TIMGetClrFmt(tim));
	
	if(bits == 24 || bits == 32){
		AGIDL_TGASyncPix(tga,tim->pixels.pix32);
	}
	else{
		AGIDL_TGASyncPix16(tga,tim->pixels.pix16);
	}
	return tga;
}

AGIDL_PCX* AGIDL_ConvertTIM2PCX(AGIDL_TIM* tim){
	AGIDL_PCX* pcx = AGIDL_CreatePCX(AGIDL_StrCpy(AGIDL_GetImgName(tim->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_PCX)),AGIDL_TIMGetWidth(tim),AGIDL_TIMGetHeight(tim),
	AGIDL_TIMGetClrFmt(tim));
	
	int bits = AGIDL_GetBitCount(AGIDL_TIMGetClrFmt(tim));
	
	if(bits == 24 || bits == 32){
		AGIDL_PCXSyncPix(pcx,tim->pixels.pix32);
	}
	else{
		AGIDL_PCXSyncPix16(pcx,tim->pixels.pix16);
	}
	return pcx;
}

AGIDL_LMP* AGIDL_ConvertTIM2LMP(AGIDL_TIM* tim){
	AGIDL_LMP* lmp = AGIDL_CreateLMP(AGIDL_StrCpy(AGIDL_GetImgName(tim->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_LMP)),AGIDL_TIMGetWidth(tim),AGIDL_TIMGetHeight(tim),
	AGIDL_TIMGetClrFmt(tim));
	AGIDL_LMPSetMaxDiff(lmp,AGIDL_TIMGetMaxDiff(tim));
	
	int bits = AGIDL_GetBitCount(AGIDL_TIMGetClrFmt(tim));
	
	if(bits == 24 || bits == 32){
		AGIDL_LMPSyncPix(lmp,tim->pixels.pix32);
	}
	else{
		AGIDL_LMPSyncPix16(lmp,tim->pixels.pix16);
	}
	return lmp;
}

AGIDL_PVR* AGIDL_ConvertTIM2PVR(AGIDL_TIM* tim){
	AGIDL_PVR* pvr = AGIDL_CreatePVR(AGIDL_StrCpy(AGIDL_GetImgName(tim->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_PVR)),AGIDL_TIMGetWidth(tim),AGIDL_TIMGetHeight(tim),
	AGIDL_TIMGetClrFmt(tim));
	AGIDL_PVRSetICPMode(pvr,tim->icp);
	AGIDL_PVRSetMaxDiff(pvr,AGIDL_TIMGetMaxDiff(tim));
	
	int bits = AGIDL_GetBitCount(AGIDL_TIMGetClrFmt(tim));
	
	if(bits == 24 || bits == 32){
		AGIDL_PVRSyncPix(pvr,tim->pixels.pix32);
	}
	else{
		AGIDL_PVRSyncPix16(pvr,tim->pixels.pix16);
	}
	return pvr;
}

AGIDL_GXT* AGIDL_ConvertTIM2GXT(AGIDL_TIM* tim){
	AGIDL_GXT* gxt = AGIDL_CreateGXT(AGIDL_StrCpy(AGIDL_GetImgName(tim->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_GXT)),AGIDL_TIMGetWidth(tim),AGIDL_TIMGetHeight(tim),
	AGIDL_TIMGetClrFmt(tim));
	AGIDL_GXTSetICPMode(gxt,tim->icp);
	AGIDL_GXTSetMaxDiff(gxt,AGIDL_TIMGetMaxDiff(tim));
	
	int bits = AGIDL_GetBitCount(AGIDL_TIMGetClrFmt(tim));
	
	if(bits == 24 || bits == 32){
		AGIDL_GXTSyncPix(gxt,tim->pixels.pix32);
	}
	else{
		AGIDL_GXTSyncPix16(gxt,tim->pixels.pix16);
	}
	return gxt;
}

AGIDL_BTI* AGIDL_ConvertTIM2BTI(AGIDL_TIM* tim){
	AGIDL_BTI* bti = AGIDL_CreateBTI(AGIDL_StrCpy(AGIDL_GetImgName(tim->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_BTI)),AGIDL_TIMGetWidth(tim),AGIDL_TIMGetHeight(tim),
	AGIDL_TIMGetClrFmt(tim));
	AGIDL_BTISetICPMode(bti,tim->icp);
	AGIDL_BTISetMaxDiff(bti,AGIDL_TIMGetMaxDiff(tim));
	
	int bits = AGIDL_GetBitCount(AGIDL_TIMGetClrFmt(tim));
	
	if(bits == 24 || bits == 32){
		AGIDL_BTISyncPix(bti,tim->pixels.pix32);
	}
	else{
		AGIDL_BTISyncPix16(bti,tim->pixels.pix16);
	}
	return bti;
}

AGIDL_BMP* AGIDL_ConvertPCX2BMP(AGIDL_PCX* pcx){
	AGIDL_BMP* bmp = AGIDL_CreateBMP(AGIDL_StrCpy(AGIDL_GetImgName(pcx->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_BMP)),AGIDL_PCXGetWidth(pcx),AGIDL_PCXGetHeight(pcx),
	AGIDL_PCXGetClrFmt(pcx));
	AGIDL_BMPSetMaxDiff(bmp,15);
	
	int bits = AGIDL_GetBitCount(AGIDL_PCXGetClrFmt(pcx));
	
	if(bits == 24 || bits == 32){
		AGIDL_BMPSyncPix(bmp,pcx->pixels.pix32);
	}
	else{
		AGIDL_BMPSyncPix16(bmp,pcx->pixels.pix16);
	}
	return bmp;
}

AGIDL_TGA* AGIDL_ConvertPCX2TGA(AGIDL_PCX* pcx){
	AGIDL_TGA* tga = AGIDL_CreateTGA(AGIDL_StrCpy(AGIDL_GetImgName(pcx->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_TGA)),AGIDL_PCXGetWidth(pcx),AGIDL_PCXGetHeight(pcx),
	AGIDL_PCXGetClrFmt(pcx));
	AGIDL_TGASetMaxDiff(tga,15);
	
	int bits = AGIDL_GetBitCount(AGIDL_PCXGetClrFmt(pcx));
	
	if(bits == 24 || bits == 32){
		AGIDL_TGASyncPix(tga,pcx->pixels.pix32);
	}
	else{
		AGIDL_TGASyncPix16(tga,pcx->pixels.pix16);
	}
	return tga;
}

AGIDL_TIM* AGIDL_ConvertPCX2TIM(AGIDL_PCX* pcx){
	AGIDL_TIM* tim = AGIDL_CreateTIM(AGIDL_StrCpy(AGIDL_GetImgName(pcx->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_TIM)),AGIDL_PCXGetWidth(pcx),AGIDL_PCXGetHeight(pcx),
	AGIDL_PCXGetClrFmt(pcx));
	AGIDL_TIMSetMaxDiff(tim,15);
	
	int bits = AGIDL_GetBitCount(AGIDL_PCXGetClrFmt(pcx));
	
	if(bits == 24 || bits == 32){
		AGIDL_TIMSyncPix(tim,pcx->pixels.pix32);
	}
	else{
		AGIDL_TIMSyncPix16(tim,pcx->pixels.pix16);
	}
	return tim;
}

AGIDL_LMP* AGIDL_ConvertPCX2LMP(AGIDL_PCX* pcx){
	AGIDL_LMP* lmp = AGIDL_CreateLMP(AGIDL_StrCpy(AGIDL_GetImgName(pcx->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_LMP)),AGIDL_PCXGetWidth(pcx),AGIDL_PCXGetHeight(pcx),
	AGIDL_PCXGetClrFmt(pcx));
	AGIDL_LMPSetMaxDiff(lmp,15);
	
	int bits = AGIDL_GetBitCount(AGIDL_PCXGetClrFmt(pcx));
	
	if(bits == 24 || bits == 32){
		AGIDL_LMPSyncPix(lmp,pcx->pixels.pix32);
	}
	else{
		AGIDL_LMPSyncPix16(lmp,pcx->pixels.pix16);
	}
	return lmp;
}

AGIDL_PVR* AGIDL_ConvertPCX2PVR(AGIDL_PCX* pcx){
	AGIDL_PVR* pvr = AGIDL_CreatePVR(AGIDL_StrCpy(AGIDL_GetImgName(pcx->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_PVR)),AGIDL_PCXGetWidth(pcx),AGIDL_PCXGetHeight(pcx),
	AGIDL_PCXGetClrFmt(pcx));
	AGIDL_PVRSetMaxDiff(pvr,15);
	
	int bits = AGIDL_GetBitCount(AGIDL_PCXGetClrFmt(pcx));
	
	if(bits == 24 || bits == 32){
		AGIDL_PVRSyncPix(pvr,pcx->pixels.pix32);
	}
	else{
		AGIDL_PVRSyncPix16(pvr,pcx->pixels.pix16);
	}
	return pvr;
}

AGIDL_GXT* AGIDL_ConvertPCXT2GXT(AGIDL_PCX* pcx){
	AGIDL_GXT* gxt = AGIDL_CreateGXT(AGIDL_StrCpy(AGIDL_GetImgName(pcx->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_GXT)),AGIDL_PCXGetWidth(pcx),AGIDL_PCXGetHeight(pcx),
	AGIDL_PCXGetClrFmt(pcx));
	AGIDL_GXTSetICPMode(gxt,pcx->icp);
	AGIDL_GXTSetMaxDiff(gxt,AGIDL_PCXGetMaxDiff(pcx));
	
	int bits = AGIDL_GetBitCount(AGIDL_PCXGetClrFmt(pcx));
	
	if(bits == 24 || bits == 32){
		AGIDL_GXTSyncPix(gxt,pcx->pixels.pix32);
	}
	else{
		AGIDL_GXTSyncPix16(gxt,pcx->pixels.pix16);
	}
	return gxt;
}

AGIDL_BTI* AGIDL_ConvertPCXT2BTI(AGIDL_PCX* pcx){
	AGIDL_BTI* bti = AGIDL_CreateBTI(AGIDL_StrCpy(AGIDL_GetImgName(pcx->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_BTI)),AGIDL_PCXGetWidth(pcx),AGIDL_PCXGetHeight(pcx),
	AGIDL_PCXGetClrFmt(pcx));
	AGIDL_BTISetICPMode(bti,pcx->icp);
	AGIDL_BTISetMaxDiff(bti,AGIDL_PCXGetMaxDiff(pcx));
	
	int bits = AGIDL_GetBitCount(AGIDL_PCXGetClrFmt(pcx));
	
	if(bits == 24 || bits == 32){
		AGIDL_BTISyncPix(bti,pcx->pixels.pix32);
	}
	else{
		AGIDL_BTISyncPix16(bti,pcx->pixels.pix16);
	}
	return bti;
}

AGIDL_BMP* AGIDL_ConvertLMP2BMP(AGIDL_LMP* lmp){
	AGIDL_BMP* bmp = AGIDL_CreateBMP(AGIDL_StrCpy(AGIDL_GetImgName(lmp->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_BMP)),AGIDL_LMPGetWidth(lmp),AGIDL_LMPGetHeight(lmp),
	AGIDL_LMPGetClrFmt(lmp));
	AGIDL_BMPSetMaxDiff(bmp,AGIDL_LMPGetMaxDiff(lmp));
	
	int bits = AGIDL_GetBitCount(AGIDL_LMPGetClrFmt(lmp));
	
	if(bits == 24 || bits == 32){
		AGIDL_BMPSyncPix(bmp,lmp->pixels.pix32);
	}
	else{
		AGIDL_BMPSyncPix16(bmp,lmp->pixels.pix16);
	}
	return bmp;
}

AGIDL_TGA* AGIDL_ConvertLMP2TGA(AGIDL_LMP* lmp){
	AGIDL_TGA* tga = AGIDL_CreateTGA(AGIDL_StrCpy(AGIDL_GetImgName(lmp->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_TGA)),AGIDL_LMPGetWidth(lmp),AGIDL_LMPGetHeight(lmp),
	AGIDL_LMPGetClrFmt(lmp));
	AGIDL_TGASetMaxDiff(tga,AGIDL_LMPGetMaxDiff(lmp));
	
	int bits = AGIDL_GetBitCount(AGIDL_LMPGetClrFmt(lmp));
	
	if(bits == 24 || bits == 32){
		AGIDL_TGASyncPix(tga,lmp->pixels.pix32);
	}
	else{
		AGIDL_TGASyncPix16(tga,lmp->pixels.pix16);
	}
	return tga;
}

AGIDL_TIM* AGIDL_ConvertLMP2TIM(AGIDL_LMP* lmp){
	AGIDL_TIM* tim = AGIDL_CreateTIM(AGIDL_StrCpy(AGIDL_GetImgName(lmp->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_TIM)),AGIDL_LMPGetWidth(lmp),AGIDL_LMPGetHeight(lmp),
	AGIDL_LMPGetClrFmt(lmp));
	AGIDL_TIMSetMaxDiff(tim,AGIDL_LMPGetMaxDiff(lmp));
	
	int bits = AGIDL_GetBitCount(AGIDL_LMPGetClrFmt(lmp));
	
	if(bits == 24 || bits == 32){
		AGIDL_TIMSyncPix(tim,lmp->pixels.pix32);
	}
	else{
		AGIDL_TIMSyncPix16(tim,lmp->pixels.pix16);
	}
	return tim;
}

AGIDL_PVR* AGIDL_ConvertLMP2PVR(AGIDL_LMP* lmp){
	AGIDL_PVR* pvr = AGIDL_CreatePVR(AGIDL_StrCpy(AGIDL_GetImgName(lmp->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_PVR)),AGIDL_LMPGetWidth(lmp),AGIDL_LMPGetHeight(lmp),
	AGIDL_LMPGetClrFmt(lmp));
	AGIDL_PVRSetMaxDiff(pvr,AGIDL_LMPGetMaxDiff(lmp));
	
	int bits = AGIDL_GetBitCount(AGIDL_LMPGetClrFmt(lmp));
	
	if(bits == 24 || bits == 32){
		AGIDL_PVRSyncPix(pvr,lmp->pixels.pix32);
	}
	else{
		AGIDL_PVRSyncPix16(pvr,lmp->pixels.pix16);
	}
	return pvr;
}

AGIDL_GXT* AGIDL_ConvertLMP2GXT(AGIDL_LMP* lmp){
	AGIDL_GXT* gxt = AGIDL_CreateGXT(AGIDL_StrCpy(AGIDL_GetImgName(lmp->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_GXT)),AGIDL_LMPGetWidth(lmp),AGIDL_LMPGetHeight(lmp),
	AGIDL_LMPGetClrFmt(lmp));
	AGIDL_GXTSetMaxDiff(gxt,AGIDL_LMPGetMaxDiff(lmp));
	
	int bits = AGIDL_GetBitCount(AGIDL_LMPGetClrFmt(lmp));
	
	if(bits == 24 || bits == 32){
		AGIDL_GXTSyncPix(gxt,lmp->pixels.pix32);
	}
	else{
		AGIDL_GXTSyncPix16(gxt,lmp->pixels.pix16);
	}
	return gxt;
}

AGIDL_BTI* AGIDL_ConvertLMP2BTI(AGIDL_LMP* lmp){
	AGIDL_BTI* bti = AGIDL_CreateBTI(AGIDL_StrCpy(AGIDL_GetImgName(lmp->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_BTI)),AGIDL_LMPGetWidth(lmp),AGIDL_LMPGetHeight(lmp),
	AGIDL_LMPGetClrFmt(lmp));
	AGIDL_BTISetMaxDiff(bti,AGIDL_LMPGetMaxDiff(lmp));
	
	int bits = AGIDL_GetBitCount(AGIDL_LMPGetClrFmt(lmp));
	
	if(bits == 24 || bits == 32){
		AGIDL_BTISyncPix(bti,lmp->pixels.pix32);
	}
	else{
		AGIDL_BTISyncPix16(bti,lmp->pixels.pix16);
	}
	return bti;
}

AGIDL_BMP* AGIDL_ConvertPVR2BMP(AGIDL_PVR* pvr){
	AGIDL_BMP* bmp = AGIDL_CreateBMP(AGIDL_StrCpy(AGIDL_GetImgName(pvr->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_BMP)),AGIDL_PVRGetWidth(pvr),AGIDL_PVRGetHeight(pvr),
	AGIDL_PVRGetClrFmt(pvr));
	AGIDL_BMPSetICPMode(bmp,NO_ICP);
	AGIDL_BMPSetMaxDiff(bmp,AGIDL_PVRGetMaxDiff(pvr));
	
	int bits = AGIDL_GetBitCount(AGIDL_PVRGetClrFmt(pvr));
	
	if(bits == 24 || bits == 32){
		AGIDL_BMPSyncPix(bmp,pvr->pixels.pix32);
	}
	else{
		AGIDL_BMPSyncPix16(bmp,pvr->pixels.pix16);
	}
	return bmp;
}

AGIDL_TGA* AGIDL_ConvertPVR2TGA(AGIDL_PVR* pvr){
	AGIDL_TGA* tga = AGIDL_CreateTGA(AGIDL_StrCpy(AGIDL_GetImgName(pvr->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_TGA)),AGIDL_PVRGetWidth(pvr),AGIDL_PVRGetHeight(pvr),
	AGIDL_PVRGetClrFmt(pvr));
	AGIDL_TGASetICPMode(tga,pvr->icp);
	AGIDL_TGASetMaxDiff(tga,AGIDL_PVRGetMaxDiff(pvr));
	
	int bits = AGIDL_GetBitCount(AGIDL_PVRGetClrFmt(pvr));
	
	if(bits == 24 || bits == 32){
		AGIDL_TGASyncPix(tga,pvr->pixels.pix32);
	}
	else{
		AGIDL_TGASyncPix16(tga,pvr->pixels.pix16);
	}
	return tga;
}

AGIDL_TIM* AGIDL_ConvertPVR2TIM(AGIDL_PVR* pvr){
	AGIDL_TIM* tim = AGIDL_CreateTIM(AGIDL_StrCpy(AGIDL_GetImgName(pvr->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_TIM)),AGIDL_PVRGetWidth(pvr),AGIDL_PVRGetHeight(pvr),
	AGIDL_PVRGetClrFmt(pvr));
	AGIDL_TIMSetICPMode(tim,pvr->icp);
	AGIDL_TIMSetMaxDiff(tim,AGIDL_PVRGetMaxDiff(pvr));
	
	int bits = AGIDL_GetBitCount(AGIDL_PVRGetClrFmt(pvr));
	
	if(bits == 24 || bits == 32){
		AGIDL_TIMSyncPix(tim,pvr->pixels.pix32);
	}
	else{
		AGIDL_TIMSyncPix16(tim,pvr->pixels.pix16);
	}
	return tim;
}

AGIDL_PCX* AGIDL_ConvertPVR2PCX(AGIDL_PVR* pvr){
	AGIDL_PCX* pcx = AGIDL_CreatePCX(AGIDL_StrCpy(AGIDL_GetImgName(pvr->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_PCX)),AGIDL_PVRGetWidth(pvr),AGIDL_PVRGetHeight(pvr),
	AGIDL_PVRGetClrFmt(pvr));
	
	int bits = AGIDL_GetBitCount(AGIDL_PVRGetClrFmt(pvr));
	
	if(bits == 24 || bits == 32){
		AGIDL_PCXSyncPix(pcx,pvr->pixels.pix32);
	}
	else{
		AGIDL_PCXSyncPix16(pcx,pvr->pixels.pix16);
	}
	return pcx;
}

AGIDL_LMP* AGIDL_ConvertPVR2LMP(AGIDL_PVR* pvr){
	AGIDL_LMP* lmp = AGIDL_CreateLMP(AGIDL_StrCpy(AGIDL_GetImgName(pvr->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_LMP)),AGIDL_PVRGetWidth(pvr),AGIDL_PVRGetHeight(pvr),
	AGIDL_PVRGetClrFmt(pvr));
	AGIDL_LMPSetMaxDiff(lmp,AGIDL_PVRGetMaxDiff(pvr));
	
	int bits = AGIDL_GetBitCount(AGIDL_PVRGetClrFmt(pvr));
	
	if(bits == 24 || bits == 32){
		AGIDL_LMPSyncPix(lmp,pvr->pixels.pix32);
	}
	else{
		AGIDL_LMPSyncPix16(lmp,pvr->pixels.pix16);
	}
	return lmp;
}

AGIDL_GXT* AGIDL_ConvertPVR2GXT(AGIDL_PVR* pvr){
	AGIDL_GXT* gxt = AGIDL_CreateGXT(AGIDL_StrCpy(AGIDL_GetImgName(pvr->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_GXT)),AGIDL_PVRGetWidth(pvr),AGIDL_PVRGetHeight(pvr),
	AGIDL_PVRGetClrFmt(pvr));
	AGIDL_GXTSetICPMode(gxt,pvr->icp);
	AGIDL_GXTSetMaxDiff(gxt,AGIDL_PVRGetMaxDiff(pvr));
	
	int bits = AGIDL_GetBitCount(AGIDL_PVRGetClrFmt(pvr));
	
	if(bits == 24 || bits == 32){
		AGIDL_GXTSyncPix(gxt,pvr->pixels.pix32);
	}
	else{
		AGIDL_GXTSyncPix16(gxt,pvr->pixels.pix16);
	}
	return gxt;
}

AGIDL_BTI* AGIDL_ConvertPVR2BTI(AGIDL_PVR* pvr){
	AGIDL_BTI* bti = AGIDL_CreateBTI(AGIDL_StrCpy(AGIDL_GetImgName(pvr->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_BTI)),AGIDL_PVRGetWidth(pvr),AGIDL_PVRGetHeight(pvr),
	AGIDL_PVRGetClrFmt(pvr));
	AGIDL_BTISetICPMode(bti,pvr->icp);
	AGIDL_BTISetMaxDiff(bti,AGIDL_PVRGetMaxDiff(pvr));
	
	int bits = AGIDL_GetBitCount(AGIDL_PVRGetClrFmt(pvr));
	
	if(bits == 24 || bits == 32){
		AGIDL_BTISyncPix(bti,pvr->pixels.pix32);
	}
	else{
		AGIDL_BTISyncPix16(bti,pvr->pixels.pix16);
	}
	return bti;
}

AGIDL_BMP* AGIDL_ConvertGXT2BMP(AGIDL_GXT* gxt){
	AGIDL_BMP* bmp = AGIDL_CreateBMP(AGIDL_StrCpy(AGIDL_GetImgName(gxt->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_BMP)),AGIDL_GXTGetWidth(gxt),AGIDL_GXTGetHeight(gxt),
	AGIDL_GXTGetClrFmt(gxt));
	AGIDL_BMPSetICPMode(bmp,gxt->icp);
	AGIDL_BMPSetMaxDiff(bmp,AGIDL_GXTGetMaxDiff(gxt));
	
	int bits = AGIDL_GetBitCount(AGIDL_GXTGetClrFmt(gxt));
	
	if(bits == 24 || bits == 32){
		AGIDL_BMPSyncPix(bmp,gxt->pixels.pix32);
	}
	else{
		AGIDL_BMPSyncPix16(bmp,gxt->pixels.pix16);
	}
	return bmp;
}

AGIDL_TGA* AGIDL_ConvertGXT2TGA(AGIDL_GXT* gxt){
	AGIDL_TGA* tga = AGIDL_CreateTGA(AGIDL_StrCpy(AGIDL_GetImgName(gxt->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_TGA)),AGIDL_GXTGetWidth(gxt),AGIDL_GXTGetHeight(gxt),
	AGIDL_GXTGetClrFmt(gxt));
	AGIDL_TGASetICPMode(tga,gxt->icp);
	AGIDL_TGASetMaxDiff(tga,AGIDL_GXTGetMaxDiff(gxt));
	
	int bits = AGIDL_GetBitCount(AGIDL_GXTGetClrFmt(gxt));
	
	if(bits == 24 || bits == 32){
		AGIDL_TGASyncPix(tga,gxt->pixels.pix32);
	}
	else{
		AGIDL_TGASyncPix16(tga,gxt->pixels.pix16);
	}
	return tga;
}

AGIDL_TIM* AGIDL_ConvertGXT2TIM(AGIDL_GXT* gxt){
	AGIDL_TIM* tim = AGIDL_CreateTIM(AGIDL_StrCpy(AGIDL_GetImgName(gxt->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_TIM)),AGIDL_GXTGetWidth(gxt),AGIDL_GXTGetHeight(gxt),
	AGIDL_GXTGetClrFmt(gxt));
	AGIDL_TIMSetICPMode(tim,gxt->icp);
	AGIDL_TIMSetMaxDiff(tim,AGIDL_GXTGetMaxDiff(gxt));
	
	int bits = AGIDL_GetBitCount(AGIDL_GXTGetClrFmt(gxt));
	
	if(bits == 24 || bits == 32){
		AGIDL_TIMSyncPix(tim,gxt->pixels.pix32);
	}
	else{
		AGIDL_TIMSyncPix16(tim,gxt->pixels.pix16);
	}
	return tim;
}

AGIDL_PCX* AGIDL_ConvertGXT2PCX(AGIDL_GXT* gxt){
	AGIDL_PCX* pcx = AGIDL_CreatePCX(AGIDL_StrCpy(AGIDL_GetImgName(gxt->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_PCX)),AGIDL_GXTGetWidth(gxt),AGIDL_GXTGetHeight(gxt),
	AGIDL_GXTGetClrFmt(gxt));
	AGIDL_PCXSetICPMode(pcx,gxt->icp);
	AGIDL_PCXSetMaxDiff(pcx,AGIDL_GXTGetMaxDiff(gxt));
	
	int bits = AGIDL_GetBitCount(AGIDL_GXTGetClrFmt(gxt));
	
	if(bits == 24 || bits == 32){
		AGIDL_PCXSyncPix(pcx,gxt->pixels.pix32);
	}
	else{
		AGIDL_PCXSyncPix16(pcx,gxt->pixels.pix16);
	}
	return pcx;
}

AGIDL_LMP* AGIDL_ConvertGXT2LMP(AGIDL_GXT* gxt){
	AGIDL_LMP* lmp = AGIDL_CreateLMP(AGIDL_StrCpy(AGIDL_GetImgName(gxt->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_LMP)),AGIDL_GXTGetWidth(gxt),AGIDL_GXTGetHeight(gxt),
	AGIDL_GXTGetClrFmt(gxt));
	AGIDL_LMPSetMaxDiff(lmp,AGIDL_GXTGetMaxDiff(gxt));
	
	int bits = AGIDL_GetBitCount(AGIDL_GXTGetClrFmt(gxt));
	
	if(bits == 24 || bits == 32){
		AGIDL_LMPSyncPix(lmp,gxt->pixels.pix32);
	}
	else{
		AGIDL_LMPSyncPix16(lmp,gxt->pixels.pix16);
	}
	return lmp;
}

AGIDL_PVR* AGIDL_ConvertGXT2PVR(AGIDL_GXT* gxt){
	AGIDL_PVR* pvr = AGIDL_CreatePVR(AGIDL_StrCpy(AGIDL_GetImgName(gxt->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_PVR)),AGIDL_GXTGetWidth(gxt),AGIDL_GXTGetHeight(gxt),
	AGIDL_GXTGetClrFmt(gxt));
	AGIDL_PVRSetICPMode(pvr,gxt->icp);
	AGIDL_PVRSetMaxDiff(pvr,AGIDL_GXTGetMaxDiff(gxt));
	
	int bits = AGIDL_GetBitCount(AGIDL_GXTGetClrFmt(gxt));
	
	if(bits == 24 || bits == 32){
		AGIDL_PVRSyncPix(pvr,gxt->pixels.pix32);
	}
	else{
		AGIDL_PVRSyncPix16(pvr,gxt->pixels.pix16);
	}
	return pvr;
}

AGIDL_BTI* AGIDL_ConvertGXT2BTI(AGIDL_GXT* gxt){
	AGIDL_BTI* bti = AGIDL_CreateBTI(AGIDL_StrCpy(AGIDL_GetImgName(gxt->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_BTI)),AGIDL_GXTGetWidth(gxt),AGIDL_GXTGetHeight(gxt),
	AGIDL_GXTGetClrFmt(gxt));
	AGIDL_BTISetICPMode(bti,gxt->icp);
	AGIDL_BTISetMaxDiff(bti,AGIDL_GXTGetMaxDiff(gxt));
	
	int bits = AGIDL_GetBitCount(AGIDL_GXTGetClrFmt(gxt));
	
	if(bits == 24 || bits == 32){
		AGIDL_BTISyncPix(bti,gxt->pixels.pix32);
	}
	else{
		AGIDL_BTISyncPix16(bti,gxt->pixels.pix16);
	}
	return bti;
}

AGIDL_BMP* AGIDL_ConvertBTI2BMP(AGIDL_BTI* bti){
	AGIDL_BMP* bmp = AGIDL_CreateBMP(AGIDL_StrCpy(AGIDL_GetImgName(bti->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_BMP)),AGIDL_BTIGetWidth(bti),AGIDL_BTIGetHeight(bti),
	AGIDL_BTIGetClrFmt(bti));
	AGIDL_BMPSetICPMode(bmp,bti->icp);
	AGIDL_BMPSetMaxDiff(bmp,AGIDL_BTIGetMaxDiff(bti));
	
	int bits = AGIDL_GetBitCount(AGIDL_BTIGetClrFmt(bti));
	
	if(bits == 24 || bits == 32){
		AGIDL_BMPSyncPix(bmp,bti->pixels.pix32);
	}
	else{
		AGIDL_BMPSyncPix16(bmp,bti->pixels.pix16);
	}
	return bmp;
}

AGIDL_TGA* AGIDL_ConvertBTI2TGA(AGIDL_BTI* bti){
	AGIDL_TGA* tga = AGIDL_CreateTGA(AGIDL_StrCpy(AGIDL_GetImgName(bti->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_TGA)),AGIDL_BTIGetWidth(bti),AGIDL_BTIGetHeight(bti),
	AGIDL_BTIGetClrFmt(bti));
	AGIDL_TGASetICPMode(tga,bti->icp);
	AGIDL_TGASetMaxDiff(tga,AGIDL_BTIGetMaxDiff(bti));
	
	int bits = AGIDL_GetBitCount(AGIDL_BTIGetClrFmt(bti));
	
	if(bits == 24 || bits == 32){
		AGIDL_TGASyncPix(tga,bti->pixels.pix32);
	}
	else{
		AGIDL_TGASyncPix16(tga,bti->pixels.pix16);
	}
	return tga;
}

AGIDL_TIM* AGIDL_ConvertBTI2TIM(AGIDL_BTI* bti){
	AGIDL_TIM* tim = AGIDL_CreateTIM(AGIDL_StrCpy(AGIDL_GetImgName(bti->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_TIM)),AGIDL_BTIGetWidth(bti),AGIDL_BTIGetHeight(bti),
	AGIDL_BTIGetClrFmt(bti));
	AGIDL_TIMSetICPMode(tim,bti->icp);
	AGIDL_TIMSetMaxDiff(tim,AGIDL_BTIGetMaxDiff(bti));
	
	int bits = AGIDL_GetBitCount(AGIDL_BTIGetClrFmt(bti));
	
	if(bits == 24 || bits == 32){
		AGIDL_TIMSyncPix(tim,bti->pixels.pix32);
	}
	else{
		AGIDL_TIMSyncPix16(tim,bti->pixels.pix16);
	}
	return tim;
}

AGIDL_PCX* AGIDL_ConvertBTI2PCX(AGIDL_BTI* bti){
	AGIDL_PCX* pcx = AGIDL_CreatePCX(AGIDL_StrCpy(AGIDL_GetImgName(bti->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_PCX)),AGIDL_BTIGetWidth(bti),AGIDL_BTIGetHeight(bti),
	AGIDL_BTIGetClrFmt(bti));
	AGIDL_PCXSetICPMode(pcx,bti->icp);
	AGIDL_PCXSetMaxDiff(pcx,AGIDL_BTIGetMaxDiff(bti));
	
	int bits = AGIDL_GetBitCount(AGIDL_BTIGetClrFmt(bti));
	
	if(bits == 24 || bits == 32){
		AGIDL_PCXSyncPix(pcx,bti->pixels.pix32);
	}
	else{
		AGIDL_PCXSyncPix16(pcx,bti->pixels.pix16);
	}
	return pcx;
}

AGIDL_LMP* AGIDL_ConvertBTI2LMP(AGIDL_BTI* bti){
	AGIDL_LMP* lmp = AGIDL_CreateLMP(AGIDL_StrCpy(AGIDL_GetImgName(bti->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_LMP)),AGIDL_BTIGetWidth(bti),AGIDL_BTIGetHeight(bti),
	AGIDL_BTIGetClrFmt(bti));
	AGIDL_LMPSetMaxDiff(lmp,AGIDL_BTIGetMaxDiff(bti));
	
	int bits = AGIDL_GetBitCount(AGIDL_BTIGetClrFmt(bti));
	
	if(bits == 24 || bits == 32){
		AGIDL_LMPSyncPix(lmp,bti->pixels.pix32);
	}
	else{
		AGIDL_LMPSyncPix16(lmp,bti->pixels.pix16);
	}
	return lmp;
}

AGIDL_PVR* AGIDL_ConvertBTI2PVR(AGIDL_BTI* bti){
	AGIDL_PVR* pvr = AGIDL_CreatePVR(AGIDL_StrCpy(AGIDL_GetImgName(bti->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_PVR)),AGIDL_BTIGetWidth(bti),AGIDL_BTIGetHeight(bti),
	AGIDL_BTIGetClrFmt(bti));
	AGIDL_PVRSetICPMode(pvr,bti->icp);
	AGIDL_PVRSetMaxDiff(pvr,AGIDL_BTIGetMaxDiff(bti));
	
	int bits = AGIDL_GetBitCount(AGIDL_BTIGetClrFmt(bti));
	
	if(bits == 24 || bits == 32){
		AGIDL_PVRSyncPix(pvr,bti->pixels.pix32);
	}
	else{
		AGIDL_PVRSyncPix16(pvr,bti->pixels.pix16);
	}
	return pvr;
}

AGIDL_GXT* AGIDL_ConvertBTI2GXT(AGIDL_BTI* bti){
	AGIDL_GXT* gxt = AGIDL_CreateGXT(AGIDL_StrCpy(AGIDL_GetImgName(bti->filename),
	AGIDL_GetImgExtension(AGIDL_IMG_GXT)),AGIDL_BTIGetWidth(bti),AGIDL_BTIGetHeight(bti),
	AGIDL_BTIGetClrFmt(bti));
	AGIDL_GXTSetICPMode(gxt,bti->icp);
	AGIDL_GXTSetMaxDiff(gxt,AGIDL_BTIGetMaxDiff(bti));
	
	int bits = AGIDL_GetBitCount(AGIDL_BTIGetClrFmt(bti));
	
	if(bits == 24 || bits == 32){
		AGIDL_GXTSyncPix(gxt,bti->pixels.pix32);
	}
	else{
		AGIDL_GXTSyncPix16(gxt,bti->pixels.pix16);
	}
	return gxt;
}