/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023-2024 Ryandracus Chapman
*
*   Library: libagidl
*   File: agidl_imgp_impl.c
*   Date: 12/17/2023
*   Version: 0.2b
*   Updated: 1/19/2024
*   Author: Ryandracus Chapman
*
********************************************/

#include "agidl_imgp_impl.h"

void AGIDL_GrayscaleBMP(AGIDL_BMP* bmp){
	if(AGIDL_GetBitCount(AGIDL_BMPGetClrFmt(bmp)) == 16){
		AGIDL_GrayscaleImgData(bmp->pixels.pix16,AGIDL_BMPGetWidth(bmp),AGIDL_BMPGetHeight(bmp),
		AGIDL_BMPGetClrFmt(bmp));
	}
	else{
		AGIDL_GrayscaleImgData(bmp->pixels.pix32,AGIDL_BMPGetWidth(bmp),AGIDL_BMPGetHeight(bmp),
		AGIDL_BMPGetClrFmt(bmp));
	}
}

void AGIDL_GrayscaleTGA(AGIDL_TGA* tga){
	if(AGIDL_GetBitCount(AGIDL_TGAGetClrFmt(tga)) == 16){
		AGIDL_GrayscaleImgData(tga->pixels.pix16,AGIDL_TGAGetWidth(tga),AGIDL_TGAGetHeight(tga),
		AGIDL_TGAGetClrFmt(tga));
	}
	else{
		AGIDL_GrayscaleImgData(tga->pixels.pix32,AGIDL_TGAGetWidth(tga),AGIDL_TGAGetHeight(tga),
		AGIDL_TGAGetClrFmt(tga));
	}
}

void AGIDL_GrayscaleTIM(AGIDL_TIM* tim){
	if(AGIDL_GetBitCount(AGIDL_TIMGetClrFmt(tim)) == 16){
		AGIDL_GrayscaleImgData(tim->pixels.pix16,AGIDL_TIMGetWidth(tim),AGIDL_TIMGetHeight(tim),
		AGIDL_TIMGetClrFmt(tim));
	}
	else{
		AGIDL_GrayscaleImgData(tim->pixels.pix32,AGIDL_TIMGetWidth(tim),AGIDL_TIMGetHeight(tim),
		AGIDL_TIMGetClrFmt(tim));
	}
}

void AGIDL_GrayscalePCX(AGIDL_PCX* pcx){
	if(AGIDL_GetBitCount(AGIDL_PCXGetClrFmt(pcx)) == 16){
		AGIDL_GrayscaleImgData(pcx->pixels.pix16,AGIDL_PCXGetWidth(pcx),AGIDL_PCXGetHeight(pcx),
		AGIDL_PCXGetClrFmt(pcx));
	}
	else{
		AGIDL_GrayscaleImgData(pcx->pixels.pix32,AGIDL_PCXGetWidth(pcx),AGIDL_PCXGetHeight(pcx),
		AGIDL_PCXGetClrFmt(pcx));
	}
}

void AGIDL_GrayscaleLMP(AGIDL_LMP* lmp){
	if(AGIDL_GetBitCount(AGIDL_LMPGetClrFmt(lmp)) == 16){
		AGIDL_GrayscaleImgData(lmp->pixels.pix16,AGIDL_LMPGetWidth(lmp),AGIDL_LMPGetHeight(lmp),
		AGIDL_LMPGetClrFmt(lmp));
	}
	else{
		AGIDL_GrayscaleImgData(lmp->pixels.pix32,AGIDL_LMPGetWidth(lmp),AGIDL_LMPGetHeight(lmp),
		AGIDL_LMPGetClrFmt(lmp));
	}
}

void AGIDL_GrayscalePVR(AGIDL_PVR* pvr){
	if(AGIDL_GetBitCount(AGIDL_PVRGetClrFmt(pvr)) == 16){
		AGIDL_GrayscaleImgData(pvr->pixels.pix16,AGIDL_PVRGetWidth(pvr),AGIDL_PVRGetHeight(pvr),
		AGIDL_PVRGetClrFmt(pvr));
	}
	else{
		AGIDL_GrayscaleImgData(pvr->pixels.pix32,AGIDL_PVRGetWidth(pvr),AGIDL_PVRGetHeight(pvr),
		AGIDL_PVRGetClrFmt(pvr));
	}
}

void AGIDL_GrayscaleGXT(AGIDL_GXT* gxt){
	if(AGIDL_GetBitCount(AGIDL_GXTGetClrFmt(gxt)) == 16){
		AGIDL_GrayscaleImgData(gxt->pixels.pix16,AGIDL_GXTGetWidth(gxt),AGIDL_GXTGetHeight(gxt),
		AGIDL_GXTGetClrFmt(gxt));
	}
	else{
		AGIDL_GrayscaleImgData(gxt->pixels.pix32,AGIDL_GXTGetWidth(gxt),AGIDL_GXTGetHeight(gxt),
		AGIDL_GXTGetClrFmt(gxt));
	}
}

void AGIDL_GrayscaleBTI(AGIDL_BTI* bti){
	if(AGIDL_GetBitCount(AGIDL_BTIGetClrFmt(bti)) == 16){
		AGIDL_GrayscaleImgData(bti->pixels.pix16,AGIDL_BTIGetWidth(bti),AGIDL_BTIGetHeight(bti),
		AGIDL_BTIGetClrFmt(bti));
	}
	else{
		AGIDL_GrayscaleImgData(bti->pixels.pix32,AGIDL_BTIGetWidth(bti),AGIDL_BTIGetHeight(bti),
		AGIDL_BTIGetClrFmt(bti));
	}
}

void AGIDL_FlipHorzBMP(AGIDL_BMP* bmp){
	if(AGIDL_GetBitCount(AGIDL_BMPGetClrFmt(bmp)) == 16){
		AGIDL_FlipImgDataHorz(bmp->pixels.pix16,AGIDL_BMPGetWidth(bmp),AGIDL_BMPGetHeight(bmp),
		AGIDL_BMPGetClrFmt(bmp));
	}
	else{
		AGIDL_FlipImgDataHorz(bmp->pixels.pix32,AGIDL_BMPGetWidth(bmp),AGIDL_BMPGetHeight(bmp),
		AGIDL_BMPGetClrFmt(bmp));
	}
}

void AGIDL_FlipHorzTGA(AGIDL_TGA* tga){
	if(AGIDL_GetBitCount(AGIDL_TGAGetClrFmt(tga)) == 16){
		AGIDL_FlipImgDataHorz(tga->pixels.pix16,AGIDL_TGAGetWidth(tga),AGIDL_TGAGetHeight(tga),
		AGIDL_TGAGetClrFmt(tga));
	}
	else{
		AGIDL_FlipImgDataHorz(tga->pixels.pix32,AGIDL_TGAGetWidth(tga),AGIDL_TGAGetHeight(tga),
		AGIDL_TGAGetClrFmt(tga));
	}
}

void AGIDL_FlipHorzTIM(AGIDL_TIM* tim){
	if(AGIDL_GetBitCount(AGIDL_TIMGetClrFmt(tim)) == 16){
		AGIDL_FlipImgDataHorz(tim->pixels.pix16,AGIDL_TIMGetWidth(tim),AGIDL_TIMGetHeight(tim),
		AGIDL_TIMGetClrFmt(tim));
	}
	else{
		AGIDL_FlipImgDataHorz(tim->pixels.pix32,AGIDL_TIMGetWidth(tim),AGIDL_TIMGetHeight(tim),
		AGIDL_TIMGetClrFmt(tim));
	}
}

void AGIDL_FlipHorzPCX(AGIDL_PCX* pcx){
	if(AGIDL_GetBitCount(AGIDL_PCXGetClrFmt(pcx)) == 16){
		AGIDL_FlipImgDataHorz(pcx->pixels.pix16,AGIDL_PCXGetWidth(pcx),AGIDL_PCXGetHeight(pcx),
		AGIDL_PCXGetClrFmt(pcx));
	}
	else{
		AGIDL_FlipImgDataHorz(pcx->pixels.pix32,AGIDL_PCXGetWidth(pcx),AGIDL_PCXGetHeight(pcx),
		AGIDL_PCXGetClrFmt(pcx));
	}
}

void AGIDL_FlipHorzLMP(AGIDL_LMP* lmp){
	if(AGIDL_GetBitCount(AGIDL_LMPGetClrFmt(lmp)) == 16){
		AGIDL_FlipImgDataHorz(lmp->pixels.pix16,AGIDL_LMPGetWidth(lmp),AGIDL_LMPGetHeight(lmp),
		AGIDL_LMPGetClrFmt(lmp));
	}
	else{
		AGIDL_FlipImgDataHorz(lmp->pixels.pix32,AGIDL_LMPGetWidth(lmp),AGIDL_LMPGetHeight(lmp),
		AGIDL_LMPGetClrFmt(lmp));
	}
}

void AGIDL_FlipHorzPVR(AGIDL_PVR* pvr){
	if(AGIDL_GetBitCount(AGIDL_PVRGetClrFmt(pvr)) == 16){
		AGIDL_FlipImgDataHorz(pvr->pixels.pix16,AGIDL_PVRGetWidth(pvr),AGIDL_PVRGetHeight(pvr),
		AGIDL_PVRGetClrFmt(pvr));
	}
	else{
		AGIDL_FlipImgDataHorz(pvr->pixels.pix32,AGIDL_PVRGetWidth(pvr),AGIDL_PVRGetHeight(pvr),
		AGIDL_PVRGetClrFmt(pvr));
	}
}

void AGIDL_FlipHorzGXT(AGIDL_GXT* gxt){
	if(AGIDL_GetBitCount(AGIDL_GXTGetClrFmt(gxt)) == 16){
		AGIDL_FlipImgDataHorz(gxt->pixels.pix16,AGIDL_GXTGetWidth(gxt),AGIDL_GXTGetHeight(gxt),
		AGIDL_GXTGetClrFmt(gxt));
	}
	else{
		AGIDL_FlipImgDataHorz(gxt->pixels.pix32,AGIDL_GXTGetWidth(gxt),AGIDL_GXTGetHeight(gxt),
		AGIDL_GXTGetClrFmt(gxt));
	}
}

void AGIDL_FlipHorzBTI(AGIDL_BTI* bti){
	if(AGIDL_GetBitCount(AGIDL_BTIGetClrFmt(bti)) == 16){
		AGIDL_FlipImgDataHorz(bti->pixels.pix16,AGIDL_BTIGetWidth(bti),AGIDL_BTIGetHeight(bti),
		AGIDL_BTIGetClrFmt(bti));
	}
	else{
		AGIDL_FlipImgDataHorz(bti->pixels.pix32,AGIDL_BTIGetWidth(bti),AGIDL_BTIGetHeight(bti),
		AGIDL_BTIGetClrFmt(bti));
	}
}

void AGIDL_FlipVertBMP(AGIDL_BMP* bmp){
	if(AGIDL_GetBitCount(AGIDL_BMPGetClrFmt(bmp)) == 16){
		AGIDL_FlipImgDataVert(bmp->pixels.pix16,AGIDL_BMPGetWidth(bmp),AGIDL_BMPGetHeight(bmp),
		AGIDL_BMPGetClrFmt(bmp));
	}
	else{
		AGIDL_FlipImgDataVert(bmp->pixels.pix32,AGIDL_BMPGetWidth(bmp),AGIDL_BMPGetHeight(bmp),
		AGIDL_BMPGetClrFmt(bmp));
	}
}

void AGIDL_FlipVertTGA(AGIDL_TGA* tga){
	if(AGIDL_GetBitCount(AGIDL_TGAGetClrFmt(tga)) == 16){
		AGIDL_FlipImgDataVert(tga->pixels.pix16,AGIDL_TGAGetWidth(tga),AGIDL_TGAGetHeight(tga),
		AGIDL_TGAGetClrFmt(tga));
	}
	else{
		AGIDL_FlipImgDataVert(tga->pixels.pix32,AGIDL_TGAGetWidth(tga),AGIDL_TGAGetHeight(tga),
		AGIDL_TGAGetClrFmt(tga));
	}
}

void AGIDL_FlipVertTIM(AGIDL_TIM* tim){
	if(AGIDL_GetBitCount(AGIDL_TIMGetClrFmt(tim)) == 16){
		AGIDL_FlipImgDataVert(tim->pixels.pix16,AGIDL_TIMGetWidth(tim),AGIDL_TIMGetHeight(tim),
		AGIDL_TIMGetClrFmt(tim));
	}
	else{
		AGIDL_FlipImgDataVert(tim->pixels.pix32,AGIDL_TIMGetWidth(tim),AGIDL_TIMGetHeight(tim),
		AGIDL_TIMGetClrFmt(tim));
	}
}

void AGIDL_FlipVertPCX(AGIDL_PCX* pcx){
	if(AGIDL_GetBitCount(AGIDL_PCXGetClrFmt(pcx)) == 16){
		AGIDL_FlipImgDataVert(pcx->pixels.pix16,AGIDL_PCXGetWidth(pcx),AGIDL_PCXGetHeight(pcx),
		AGIDL_PCXGetClrFmt(pcx));
	}
	else{
		AGIDL_FlipImgDataVert(pcx->pixels.pix32,AGIDL_PCXGetWidth(pcx),AGIDL_PCXGetHeight(pcx),
		AGIDL_PCXGetClrFmt(pcx));
	}
}

void AGIDL_FlipVertLMP(AGIDL_LMP* lmp){
	if(AGIDL_GetBitCount(AGIDL_LMPGetClrFmt(lmp)) == 16){
		AGIDL_FlipImgDataVert(lmp->pixels.pix16,AGIDL_LMPGetWidth(lmp),AGIDL_LMPGetHeight(lmp),
		AGIDL_LMPGetClrFmt(lmp));
	}
	else{
		AGIDL_FlipImgDataVert(lmp->pixels.pix32,AGIDL_LMPGetWidth(lmp),AGIDL_LMPGetHeight(lmp),
		AGIDL_LMPGetClrFmt(lmp));
	}
}

void AGIDL_FlipVertPVR(AGIDL_PVR* pvr){
	if(AGIDL_GetBitCount(AGIDL_PVRGetClrFmt(pvr)) == 16){
		AGIDL_FlipImgDataVert(pvr->pixels.pix16,AGIDL_PVRGetWidth(pvr),AGIDL_PVRGetHeight(pvr),
		AGIDL_PVRGetClrFmt(pvr));
	}
	else{
		AGIDL_FlipImgDataVert(pvr->pixels.pix32,AGIDL_PVRGetWidth(pvr),AGIDL_PVRGetHeight(pvr),
		AGIDL_PVRGetClrFmt(pvr));
	}
}

void AGIDL_FlipVertGXT(AGIDL_GXT* gxt){
	if(AGIDL_GetBitCount(AGIDL_GXTGetClrFmt(gxt)) == 16){
		AGIDL_FlipImgDataVert(gxt->pixels.pix16,AGIDL_GXTGetWidth(gxt),AGIDL_GXTGetHeight(gxt),
		AGIDL_GXTGetClrFmt(gxt));
	}
	else{
		AGIDL_FlipImgDataVert(gxt->pixels.pix32,AGIDL_GXTGetWidth(gxt),AGIDL_GXTGetHeight(gxt),
		AGIDL_GXTGetClrFmt(gxt));
	}
}

void AGIDL_FlipVertBTI(AGIDL_BTI* bti){
	if(AGIDL_GetBitCount(AGIDL_BTIGetClrFmt(bti)) == 16){
		AGIDL_FlipImgDataVert(bti->pixels.pix16,AGIDL_BTIGetWidth(bti),AGIDL_BTIGetHeight(bti),
		AGIDL_BTIGetClrFmt(bti));
	}
	else{
		AGIDL_FlipImgDataVert(bti->pixels.pix32,AGIDL_BTIGetWidth(bti),AGIDL_BTIGetHeight(bti),
		AGIDL_BTIGetClrFmt(bti));
	}
}

void AGIDL_FlipHorzAndVertBMP(AGIDL_BMP* bmp){
	if(AGIDL_GetBitCount(AGIDL_BMPGetClrFmt(bmp)) == 16){
		AGIDL_FlipImgDataHorzAndVert(bmp->pixels.pix16,AGIDL_BMPGetWidth(bmp),AGIDL_BMPGetHeight(bmp),
		AGIDL_BMPGetClrFmt(bmp));
	}
	else{
		AGIDL_FlipImgDataHorzAndVert(bmp->pixels.pix32,AGIDL_BMPGetWidth(bmp),AGIDL_BMPGetHeight(bmp),
		AGIDL_BMPGetClrFmt(bmp));
	}
}

void AGIDL_FlipHorzAndVertTGA(AGIDL_TGA* tga){
	if(AGIDL_GetBitCount(AGIDL_TGAGetClrFmt(tga)) == 16){
		AGIDL_FlipImgDataHorzAndVert(tga->pixels.pix16,AGIDL_TGAGetWidth(tga),AGIDL_TGAGetHeight(tga),
		AGIDL_TGAGetClrFmt(tga));
	}
	else{
		AGIDL_FlipImgDataHorzAndVert(tga->pixels.pix32,AGIDL_TGAGetWidth(tga),AGIDL_TGAGetHeight(tga),
		AGIDL_TGAGetClrFmt(tga));
	}
}

void AGIDL_FlipHorzAndVertTIM(AGIDL_TIM* tim){
	if(AGIDL_GetBitCount(AGIDL_TIMGetClrFmt(tim)) == 16){
		AGIDL_FlipImgDataHorzAndVert(tim->pixels.pix16,AGIDL_TIMGetWidth(tim),AGIDL_TIMGetHeight(tim),
		AGIDL_TIMGetClrFmt(tim));
	}
	else{
		AGIDL_FlipImgDataHorzAndVert(tim->pixels.pix32,AGIDL_TIMGetWidth(tim),AGIDL_TIMGetHeight(tim),
		AGIDL_TIMGetClrFmt(tim));
	}
}

void AGIDL_FlipHorzAndVertPCX(AGIDL_PCX* pcx){
	if(AGIDL_GetBitCount(AGIDL_PCXGetClrFmt(pcx)) == 16){
		AGIDL_FlipImgDataHorzAndVert(pcx->pixels.pix16,AGIDL_PCXGetWidth(pcx),AGIDL_PCXGetHeight(pcx),
		AGIDL_PCXGetClrFmt(pcx));
	}
	else{
		AGIDL_FlipImgDataHorzAndVert(pcx->pixels.pix32,AGIDL_PCXGetWidth(pcx),AGIDL_PCXGetHeight(pcx),
		AGIDL_PCXGetClrFmt(pcx));
	}
}

void AGIDL_FlipHorzAndVertLMP(AGIDL_LMP* lmp){
	if(AGIDL_GetBitCount(AGIDL_LMPGetClrFmt(lmp)) == 16){
		AGIDL_FlipImgDataHorzAndVert(lmp->pixels.pix16,AGIDL_LMPGetWidth(lmp),AGIDL_LMPGetHeight(lmp),
		AGIDL_LMPGetClrFmt(lmp));
	}
	else{
		AGIDL_FlipImgDataHorzAndVert(lmp->pixels.pix32,AGIDL_LMPGetWidth(lmp),AGIDL_LMPGetHeight(lmp),
		AGIDL_LMPGetClrFmt(lmp));
	}
}

void AGIDL_FlipHorzAndVertPVR(AGIDL_PVR* pvr){
	if(AGIDL_GetBitCount(AGIDL_PVRGetClrFmt(pvr)) == 16){
		AGIDL_FlipImgDataHorzAndVert(pvr->pixels.pix16,AGIDL_PVRGetWidth(pvr),AGIDL_PVRGetHeight(pvr),
		AGIDL_PVRGetClrFmt(pvr));
	}
	else{
		AGIDL_FlipImgDataHorzAndVert(pvr->pixels.pix32,AGIDL_PVRGetWidth(pvr),AGIDL_PVRGetHeight(pvr),
		AGIDL_PVRGetClrFmt(pvr));
	}
}

void AGIDL_FlipHorzAndVertGXT(AGIDL_GXT* gxt){
	if(AGIDL_GetBitCount(AGIDL_GXTGetClrFmt(gxt)) == 16){
		AGIDL_FlipImgDataHorzAndVert(gxt->pixels.pix16,AGIDL_GXTGetWidth(gxt),AGIDL_GXTGetHeight(gxt),
		AGIDL_GXTGetClrFmt(gxt));
	}
	else{
		AGIDL_FlipImgDataHorzAndVert(gxt->pixels.pix32,AGIDL_GXTGetWidth(gxt),AGIDL_GXTGetHeight(gxt),
		AGIDL_GXTGetClrFmt(gxt));
	}
}

void AGIDL_FlipHorzAndVertBTI(AGIDL_BTI* bti){
	if(AGIDL_GetBitCount(AGIDL_BTIGetClrFmt(bti)) == 16){
		AGIDL_FlipImgDataHorzAndVert(bti->pixels.pix16,AGIDL_BTIGetWidth(bti),AGIDL_BTIGetHeight(bti),
		AGIDL_BTIGetClrFmt(bti));
	}
	else{
		AGIDL_FlipImgDataHorzAndVert(bti->pixels.pix32,AGIDL_BTIGetWidth(bti),AGIDL_BTIGetHeight(bti),
		AGIDL_BTIGetClrFmt(bti));
	}
}

void AGIDL_RotateBMP(AGIDL_BMP* bmp, AGIDL_ANGLE angle){
	if(AGIDL_GetBitCount(AGIDL_BMPGetClrFmt(bmp)) == 16){
		AGIDL_RotateImgData(bmp->pixels.pix16,&bmp->header.width,&bmp->header.height,
		AGIDL_BMPGetClrFmt(bmp),angle);
	}
	else{
		AGIDL_RotateImgData(bmp->pixels.pix32,&bmp->header.width,&bmp->header.height,
		AGIDL_BMPGetClrFmt(bmp),angle);
	}
}

void AGIDL_RotateTGA(AGIDL_TGA* tga, AGIDL_ANGLE angle){
	if(AGIDL_GetBitCount(AGIDL_TGAGetClrFmt(tga)) == 16){
		AGIDL_RotateImgData(tga->pixels.pix16,&tga->header.width,&tga->header.height,
		AGIDL_TGAGetClrFmt(tga),angle);
	}
	else{
		AGIDL_RotateImgData(tga->pixels.pix32,&tga->header.width,&tga->header.height,
		AGIDL_TGAGetClrFmt(tga),angle);
	}
}

void AGIDL_RotateTIM(AGIDL_TIM* tim, AGIDL_ANGLE angle){
	if(AGIDL_GetBitCount(AGIDL_TIMGetClrFmt(tim)) == 16){
		AGIDL_RotateImgData(tim->pixels.pix16,&tim->img_header.width,&tim->img_header.height,
		AGIDL_TIMGetClrFmt(tim),angle);
	}
	else{
		AGIDL_RotateImgData(tim->pixels.pix32,&tim->img_header.width,&tim->img_header.height,
		AGIDL_TIMGetClrFmt(tim),angle);
	}
}

void AGIDL_RotatePCX(AGIDL_PCX* pcx, AGIDL_ANGLE angle){
	if(AGIDL_GetBitCount(AGIDL_PCXGetClrFmt(pcx)) == 16){
		AGIDL_RotateImgData(pcx->pixels.pix16,&pcx->header.width,&pcx->header.height,
		AGIDL_PCXGetClrFmt(pcx),angle);
	}
	else{
		AGIDL_RotateImgData(pcx->pixels.pix32,&pcx->header.width,&pcx->header.height,
		AGIDL_PCXGetClrFmt(pcx),angle);
	}
}

void AGIDL_RotateLMP(AGIDL_LMP* lmp, AGIDL_ANGLE angle){
	if(AGIDL_GetBitCount(AGIDL_LMPGetClrFmt(lmp)) == 16){
		AGIDL_RotateImgData(lmp->pixels.pix16,&lmp->width,&lmp->height,
		AGIDL_LMPGetClrFmt(lmp),angle);
	}
	else{
		AGIDL_RotateImgData(lmp->pixels.pix32,&lmp->width,&lmp->height,
		AGIDL_LMPGetClrFmt(lmp),angle);
	}
}

void AGIDL_RotatePVR(AGIDL_PVR* pvr, AGIDL_ANGLE angle){
	if(AGIDL_GetBitCount(AGIDL_PVRGetClrFmt(pvr)) == 16){
		AGIDL_RotateImgData(pvr->pixels.pix16,&pvr->header.width,&pvr->header.height,
		AGIDL_PVRGetClrFmt(pvr),angle);
	}
	else{
		AGIDL_RotateImgData(pvr->pixels.pix32,&pvr->header.width,&pvr->header.height,
		AGIDL_PVRGetClrFmt(pvr),angle);
	}
}

void AGIDL_RotateGXT(AGIDL_GXT* gxt, AGIDL_ANGLE angle){
	if(AGIDL_GetBitCount(AGIDL_GXTGetClrFmt(gxt)) == 16){
		AGIDL_RotateImgData(gxt->pixels.pix16,&gxt->header.header.width,&gxt->header.header.height,
		AGIDL_GXTGetClrFmt(gxt),angle);
	}
	else{
		AGIDL_RotateImgData(gxt->pixels.pix32,&gxt->header.header.width,&gxt->header.header.height,
		AGIDL_GXTGetClrFmt(gxt),angle);
	}
}

void AGIDL_RotateBTI(AGIDL_BTI* bti, AGIDL_ANGLE angle){
	if(AGIDL_GetBitCount(AGIDL_BTIGetClrFmt(bti)) == 16){
		AGIDL_RotateImgData(bti->pixels.pix16,&bti->header.width,&bti->header.height,
		AGIDL_BTIGetClrFmt(bti),angle);
	}
	else{
		AGIDL_RotateImgData(bti->pixels.pix32,&bti->header.width,&bti->header.height,
		AGIDL_BTIGetClrFmt(bti),angle);
	}
}

void AGIDL_ScaleBMP(AGIDL_BMP* bmp, float sx, float sy, AGIDL_SCALE scale){
	if(AGIDL_GetBitCount(AGIDL_BMPGetClrFmt(bmp)) == 16){
		bmp->pixels.pix16 = (COLOR16*)AGIDL_ScaleImgData(bmp->pixels.pix16,&bmp->header.width,&bmp->header.height,
		sx,sy,scale,AGIDL_BMPGetClrFmt(bmp));
	}
	else{
		bmp->pixels.pix32 = (COLOR*)AGIDL_ScaleImgData(bmp->pixels.pix32,&bmp->header.width,&bmp->header.height,
		sx,sy,scale,AGIDL_BMPGetClrFmt(bmp));
	}
}

void AGIDL_ScaleTGA(AGIDL_TGA* tga, float sx, float sy, AGIDL_SCALE scale){
	if(AGIDL_GetBitCount(AGIDL_TGAGetClrFmt(tga)) == 16){
		tga->pixels.pix16 = (COLOR16*)AGIDL_ScaleImgData(tga->pixels.pix16,&tga->header.width,&tga->header.height,
		sx,sy,scale,AGIDL_TGAGetClrFmt(tga));
	}
	else{
		tga->pixels.pix32 = (COLOR*)AGIDL_ScaleImgData(tga->pixels.pix32,&tga->header.width,&tga->header.height,
		sx,sy,scale,AGIDL_TGAGetClrFmt(tga));
	}
}

void AGIDL_ScaleTIM(AGIDL_TIM* tim, float sx, float sy, AGIDL_SCALE scale){
	if(AGIDL_GetBitCount(AGIDL_TIMGetClrFmt(tim)) == 16){
		tim->pixels.pix16 = (COLOR16*)AGIDL_ScaleImgData(tim->pixels.pix16,&tim->img_header.width,&tim->img_header.height,
		sx,sy,scale,AGIDL_TIMGetClrFmt(tim));
	}
	else{
		tim->pixels.pix32 = (COLOR*)AGIDL_ScaleImgData(tim->pixels.pix32,&tim->img_header.width,&tim->img_header.height,
		sx,sy,scale,AGIDL_TIMGetClrFmt(tim));
	}
}

void AGIDL_ScalePCX(AGIDL_PCX* pcx, float sx, float sy, AGIDL_SCALE scale){
	if(AGIDL_GetBitCount(AGIDL_PCXGetClrFmt(pcx)) == 16){
		pcx->pixels.pix16 = (COLOR16*)AGIDL_ScaleImgData(pcx->pixels.pix16,&pcx->header.width,&pcx->header.height,
		sx,sy,scale,AGIDL_PCXGetClrFmt(pcx));
	}
	else{
		pcx->pixels.pix32 = (COLOR*)AGIDL_ScaleImgData(pcx->pixels.pix32,&pcx->header.width,&pcx->header.height,
		sx,sy,scale,AGIDL_PCXGetClrFmt(pcx));
	}
}

void AGIDL_ScaleLMP(AGIDL_LMP* lmp, float sx, float sy, AGIDL_SCALE scale){
	if(AGIDL_GetBitCount(AGIDL_LMPGetClrFmt(lmp)) == 16){
		lmp->pixels.pix16 = (COLOR16*)AGIDL_ScaleImgData(lmp->pixels.pix16,&lmp->width,&lmp->height,
		sx,sy,scale,AGIDL_LMPGetClrFmt(lmp));
	}
	else{
		lmp->pixels.pix32 = (COLOR*)AGIDL_ScaleImgData(lmp->pixels.pix32,&lmp->width,&lmp->height,
		sx,sy,scale,AGIDL_LMPGetClrFmt(lmp));
	}
}

void AGIDL_ScalePVR(AGIDL_PVR* pvr, float sx, float sy, AGIDL_SCALE scale){
	if(AGIDL_GetBitCount(AGIDL_PVRGetClrFmt(pvr)) == 16){
		pvr->pixels.pix16 = (COLOR16*)AGIDL_ScaleImgData(pvr->pixels.pix16,&pvr->header.width,&pvr->header.height,
		sx,sy,scale,AGIDL_PVRGetClrFmt(pvr));
	}
	else{
		pvr->pixels.pix32 = (COLOR*)AGIDL_ScaleImgData(pvr->pixels.pix32,&pvr->header.width,&pvr->header.height,
		sx,sy,scale,AGIDL_PVRGetClrFmt(pvr));
	}
}

void AGIDL_ScaleGXT(AGIDL_GXT* gxt, float sx, float sy, AGIDL_SCALE scale){
	if(AGIDL_GetBitCount(AGIDL_GXTGetClrFmt(gxt)) == 16){
		gxt->pixels.pix16 = (COLOR16*)AGIDL_ScaleImgData(gxt->pixels.pix16,&gxt->header.header.width,&gxt->header.header.height,
		sx,sy,scale,AGIDL_GXTGetClrFmt(gxt));
	}
	else{
		gxt->pixels.pix32 = (COLOR*)AGIDL_ScaleImgData(gxt->pixels.pix32,&gxt->header.header.width,&gxt->header.header.height,
		sx,sy,scale,AGIDL_GXTGetClrFmt(gxt));
	}
}

void AGIDL_ScaleBTI(AGIDL_BTI* bti, float sx, float sy, AGIDL_SCALE scale){
	if(AGIDL_GetBitCount(AGIDL_BTIGetClrFmt(bti)) == 16){
		bti->pixels.pix16 = (COLOR16*)AGIDL_ScaleImgData(bti->pixels.pix16,&bti->header.width,&bti->header.height,
		sx,sy,scale,AGIDL_BTIGetClrFmt(bti));
	}
	else{
		bti->pixels.pix32 = (COLOR*)AGIDL_ScaleImgData(bti->pixels.pix32,&bti->header.width,&bti->header.height,
		sx,sy,scale,AGIDL_BTIGetClrFmt(bti));
	}
}

void AGIDL_FilterBilerpBMP(AGIDL_BMP* bmp){
	if(AGIDL_GetBitCount(AGIDL_BMPGetClrFmt(bmp)) == 16){
		AGIDL_FilterImgDataBilerp(bmp->pixels.pix16,AGIDL_BMPGetWidth(bmp),AGIDL_BMPGetHeight(bmp),
		AGIDL_BMPGetClrFmt(bmp));
	}
	else{
		AGIDL_FilterImgDataBilerp(bmp->pixels.pix32,AGIDL_BMPGetWidth(bmp),AGIDL_BMPGetHeight(bmp),
		AGIDL_BMPGetClrFmt(bmp));
	}
}

void AGIDL_FilterBilerpTGA(AGIDL_TGA* tga){
	if(AGIDL_GetBitCount(AGIDL_TGAGetClrFmt(tga)) == 16){
		AGIDL_FilterImgDataBilerp(tga->pixels.pix16,AGIDL_TGAGetWidth(tga),AGIDL_TGAGetHeight(tga),
		AGIDL_TGAGetClrFmt(tga));
	}
	else{
		AGIDL_FilterImgDataBilerp(tga->pixels.pix32,AGIDL_TGAGetWidth(tga),AGIDL_TGAGetHeight(tga),
		AGIDL_TGAGetClrFmt(tga));
	}
}

void AGIDL_FilterBilerpTIM(AGIDL_TIM* tim){
	if(AGIDL_GetBitCount(AGIDL_TIMGetClrFmt(tim)) == 16){
		AGIDL_FilterImgDataBilerp(tim->pixels.pix16,AGIDL_TIMGetWidth(tim),AGIDL_TIMGetHeight(tim),
		AGIDL_TIMGetClrFmt(tim));
	}
	else{
		AGIDL_FilterImgDataBilerp(tim->pixels.pix32,AGIDL_TIMGetWidth(tim),AGIDL_TIMGetHeight(tim),
		AGIDL_TIMGetClrFmt(tim));
	}
}

void AGIDL_FilterBilerpPCX(AGIDL_PCX* pcx){
	if(AGIDL_GetBitCount(AGIDL_PCXGetClrFmt(pcx)) == 16){
		AGIDL_FilterImgDataBilerp(pcx->pixels.pix16,AGIDL_PCXGetWidth(pcx),AGIDL_PCXGetHeight(pcx),
		AGIDL_PCXGetClrFmt(pcx));
	}
	else{
		AGIDL_FilterImgDataBilerp(pcx->pixels.pix32,AGIDL_PCXGetWidth(pcx),AGIDL_PCXGetHeight(pcx),
		AGIDL_PCXGetClrFmt(pcx));
	}
}

void AGIDL_FilterBilerpLMP(AGIDL_LMP* lmp){
	if(AGIDL_GetBitCount(AGIDL_LMPGetClrFmt(lmp)) == 16){
		AGIDL_FilterImgDataBilerp(lmp->pixels.pix16,AGIDL_LMPGetWidth(lmp),AGIDL_LMPGetHeight(lmp),
		AGIDL_LMPGetClrFmt(lmp));
	}
	else{
		AGIDL_FilterImgDataBilerp(lmp->pixels.pix32,AGIDL_LMPGetWidth(lmp),AGIDL_LMPGetHeight(lmp),
		AGIDL_LMPGetClrFmt(lmp));
	}
}

void AGIDL_FilterBilerpPVR(AGIDL_PVR* pvr){
	if(AGIDL_GetBitCount(AGIDL_PVRGetClrFmt(pvr)) == 16){
		AGIDL_FilterImgDataBilerp(pvr->pixels.pix16,AGIDL_PVRGetWidth(pvr),AGIDL_PVRGetHeight(pvr),
		AGIDL_PVRGetClrFmt(pvr));
	}
	else{
		AGIDL_FilterImgDataBilerp(pvr->pixels.pix32,AGIDL_PVRGetWidth(pvr),AGIDL_PVRGetHeight(pvr),
		AGIDL_PVRGetClrFmt(pvr));
	}
}

void AGIDL_FilterBilerpGXT(AGIDL_GXT* gxt){
	if(AGIDL_GetBitCount(AGIDL_GXTGetClrFmt(gxt)) == 16){
		AGIDL_FilterImgDataBilerp(gxt->pixels.pix16,AGIDL_GXTGetWidth(gxt),AGIDL_GXTGetHeight(gxt),
		AGIDL_GXTGetClrFmt(gxt));
	}
	else{
		AGIDL_FilterImgDataBilerp(gxt->pixels.pix32,AGIDL_GXTGetWidth(gxt),AGIDL_GXTGetHeight(gxt),
		AGIDL_GXTGetClrFmt(gxt));
	}
}

void AGIDL_FilterBilerpBTI(AGIDL_BTI* bti){
	if(AGIDL_GetBitCount(AGIDL_BTIGetClrFmt(bti)) == 16){
		AGIDL_FilterImgDataBilerp(bti->pixels.pix16,AGIDL_BTIGetWidth(bti),AGIDL_BTIGetHeight(bti),
		AGIDL_BTIGetClrFmt(bti));
	}
	else{
		AGIDL_FilterImgDataBilerp(bti->pixels.pix32,AGIDL_BTIGetWidth(bti),AGIDL_BTIGetHeight(bti),
		AGIDL_BTIGetClrFmt(bti));
	}
}

void AGIDL_FilterTrilerpBMP(AGIDL_BMP* bmp){
	if(AGIDL_GetBitCount(AGIDL_BMPGetClrFmt(bmp)) == 16){
		AGIDL_FilterImgDataTrilerp(bmp->pixels.pix16,AGIDL_BMPGetWidth(bmp),AGIDL_BMPGetHeight(bmp),
		AGIDL_BMPGetClrFmt(bmp));
	}
	else{
		AGIDL_FilterImgDataTrilerp(bmp->pixels.pix32,AGIDL_BMPGetWidth(bmp),AGIDL_BMPGetHeight(bmp),
		AGIDL_BMPGetClrFmt(bmp));
	}
}

void AGIDL_FilterTrilerpTGA(AGIDL_TGA* tga){
	if(AGIDL_GetBitCount(AGIDL_TGAGetClrFmt(tga)) == 16){
		AGIDL_FilterImgDataTrilerp(tga->pixels.pix16,AGIDL_TGAGetWidth(tga),AGIDL_TGAGetHeight(tga),
		AGIDL_TGAGetClrFmt(tga));
	}
	else{
		AGIDL_FilterImgDataTrilerp(tga->pixels.pix32,AGIDL_TGAGetWidth(tga),AGIDL_TGAGetHeight(tga),
		AGIDL_TGAGetClrFmt(tga));
	}
}

void AGIDL_FilterTrilerpTIM(AGIDL_TIM* tim){
	if(AGIDL_GetBitCount(AGIDL_TIMGetClrFmt(tim)) == 16){
		AGIDL_FilterImgDataTrilerp(tim->pixels.pix16,AGIDL_TIMGetWidth(tim),AGIDL_TIMGetHeight(tim),
		AGIDL_TIMGetClrFmt(tim));
	}
	else{
		AGIDL_FilterImgDataTrilerp(tim->pixels.pix32,AGIDL_TIMGetWidth(tim),AGIDL_TIMGetHeight(tim),
		AGIDL_TIMGetClrFmt(tim));
	}
}

void AGIDL_FilterTrilerpPCX(AGIDL_PCX* pcx){
	if(AGIDL_GetBitCount(AGIDL_PCXGetClrFmt(pcx)) == 16){
		AGIDL_FilterImgDataTrilerp(pcx->pixels.pix16,AGIDL_PCXGetWidth(pcx),AGIDL_PCXGetHeight(pcx),
		AGIDL_PCXGetClrFmt(pcx));
	}
	else{
		AGIDL_FilterImgDataTrilerp(pcx->pixels.pix32,AGIDL_PCXGetWidth(pcx),AGIDL_PCXGetHeight(pcx),
		AGIDL_PCXGetClrFmt(pcx));
	}
}

void AGIDL_FilterTrilerpLMP(AGIDL_LMP* lmp){
	if(AGIDL_GetBitCount(AGIDL_LMPGetClrFmt(lmp)) == 16){
		AGIDL_FilterImgDataTrilerp(lmp->pixels.pix16,AGIDL_LMPGetWidth(lmp),AGIDL_LMPGetHeight(lmp),
		AGIDL_LMPGetClrFmt(lmp));
	}
	else{
		AGIDL_FilterImgDataTrilerp(lmp->pixels.pix32,AGIDL_LMPGetWidth(lmp),AGIDL_LMPGetHeight(lmp),
		AGIDL_LMPGetClrFmt(lmp));
	}
}

void AGIDL_FilterTrilerpPVR(AGIDL_PVR* pvr){
	if(AGIDL_GetBitCount(AGIDL_PVRGetClrFmt(pvr)) == 16){
		AGIDL_FilterImgDataTrilerp(pvr->pixels.pix16,AGIDL_PVRGetWidth(pvr),AGIDL_PVRGetHeight(pvr),
		AGIDL_PVRGetClrFmt(pvr));
	}
	else{
		AGIDL_FilterImgDataTrilerp(pvr->pixels.pix32,AGIDL_PVRGetWidth(pvr),AGIDL_PVRGetHeight(pvr),
		AGIDL_PVRGetClrFmt(pvr));
	}
}

void AGIDL_FilterTrilerpGXT(AGIDL_GXT* gxt){
	if(AGIDL_GetBitCount(AGIDL_GXTGetClrFmt(gxt)) == 16){
		AGIDL_FilterImgDataTrilerp(gxt->pixels.pix16,AGIDL_GXTGetWidth(gxt),AGIDL_GXTGetHeight(gxt),
		AGIDL_GXTGetClrFmt(gxt));
	}
	else{
		AGIDL_FilterImgDataTrilerp(gxt->pixels.pix32,AGIDL_GXTGetWidth(gxt),AGIDL_GXTGetHeight(gxt),
		AGIDL_GXTGetClrFmt(gxt));
	}
}

void AGIDL_FilterTrilerpBTI(AGIDL_BTI* bti){
	if(AGIDL_GetBitCount(AGIDL_BTIGetClrFmt(bti)) == 16){
		AGIDL_FilterImgDataTrilerp(bti->pixels.pix16,AGIDL_BTIGetWidth(bti),AGIDL_BTIGetHeight(bti),
		AGIDL_BTIGetClrFmt(bti));
	}
	else{
		AGIDL_FilterImgDataTrilerp(bti->pixels.pix32,AGIDL_BTIGetWidth(bti),AGIDL_BTIGetHeight(bti),
		AGIDL_BTIGetClrFmt(bti));
	}
}

void AGIDL_MirrorBMP(AGIDL_BMP* bmp, AGIDL_MIRROR mirror){
	if(AGIDL_GetBitCount(AGIDL_BMPGetClrFmt(bmp)) == 16){
		bmp->pixels.pix16 = (COLOR16*)AGIDL_MirrorImgData(bmp->pixels.pix16,&bmp->header.width,&bmp->header.height,AGIDL_BMPGetClrFmt(bmp),mirror);
	}
	else{
		bmp->pixels.pix32 = (COLOR*)AGIDL_MirrorImgData(bmp->pixels.pix32,&bmp->header.width,&bmp->header.height,AGIDL_BMPGetClrFmt(bmp),mirror);
	}
}

void AGIDL_MirrorTGA(AGIDL_TGA* tga, AGIDL_MIRROR mirror){
	if(AGIDL_GetBitCount(AGIDL_TGAGetClrFmt(tga)) == 16){
		tga->pixels.pix16 = (COLOR16*)AGIDL_MirrorImgData(tga->pixels.pix16,&tga->header.width,&tga->header.height,AGIDL_TGAGetClrFmt(tga),mirror);
	}
	else{
		tga->pixels.pix32 = (COLOR*)AGIDL_MirrorImgData(tga->pixels.pix32,&tga->header.width,&tga->header.height,AGIDL_TGAGetClrFmt(tga),mirror);
	}
}

void AGIDL_MirrorTIM(AGIDL_TIM* tim, AGIDL_MIRROR mirror){
	if(AGIDL_GetBitCount(AGIDL_TIMGetClrFmt(tim)) == 16){
		tim->pixels.pix16 = (COLOR16*)AGIDL_MirrorImgData(tim->pixels.pix16,&tim->img_header.width,&tim->img_header.height,AGIDL_TIMGetClrFmt(tim),mirror);
	}
	else{
		tim->pixels.pix32 = (COLOR*)AGIDL_MirrorImgData(tim->pixels.pix32,&tim->img_header.width,&tim->img_header.height,AGIDL_TIMGetClrFmt(tim),mirror);
	}
}

void AGIDL_MirrorPCX(AGIDL_PCX* pcx, AGIDL_MIRROR mirror){
	if(AGIDL_GetBitCount(AGIDL_PCXGetClrFmt(pcx)) == 16){
		pcx->pixels.pix16 = (COLOR16*)AGIDL_MirrorImgData(pcx->pixels.pix16,&pcx->header.width,&pcx->header.height,AGIDL_PCXGetClrFmt(pcx),mirror);
	}
	else{
		pcx->pixels.pix32 = (COLOR*)AGIDL_MirrorImgData(pcx->pixels.pix32,&pcx->header.width,&pcx->header.height,AGIDL_PCXGetClrFmt(pcx),mirror);
	}
}

void AGIDL_MirrorLMP(AGIDL_LMP* lmp, AGIDL_MIRROR mirror){
	if(AGIDL_GetBitCount(AGIDL_LMPGetClrFmt(lmp)) == 16){
		lmp->pixels.pix16 = (COLOR16*)AGIDL_MirrorImgData(lmp->pixels.pix16,&lmp->width,&lmp->height,AGIDL_LMPGetClrFmt(lmp),mirror);
	}
	else{
		lmp->pixels.pix32 = (COLOR*)AGIDL_MirrorImgData(lmp->pixels.pix32,&lmp->width,&lmp->height,AGIDL_LMPGetClrFmt(lmp),mirror);
	}
}

void AGIDL_MirrorPVR(AGIDL_PVR* pvr, AGIDL_MIRROR mirror){
	if(AGIDL_GetBitCount(AGIDL_PVRGetClrFmt(pvr)) == 16){
		pvr->pixels.pix16 = (COLOR16*)AGIDL_MirrorImgData(pvr->pixels.pix16,&pvr->header.width,&pvr->header.height,AGIDL_PVRGetClrFmt(pvr),mirror);
	}
	else{
		pvr->pixels.pix32 = (COLOR*)AGIDL_MirrorImgData(pvr->pixels.pix32,&pvr->header.width,&pvr->header.height,AGIDL_PVRGetClrFmt(pvr),mirror);
	}
}

void AGIDL_MirrorGXT(AGIDL_GXT* gxt, AGIDL_MIRROR mirror){
	if(AGIDL_GetBitCount(AGIDL_GXTGetClrFmt(gxt)) == 16){
		gxt->pixels.pix16 = (COLOR16*)AGIDL_MirrorImgData(gxt->pixels.pix16,&gxt->header.header.width,&gxt->header.header.height,AGIDL_GXTGetClrFmt(gxt),mirror);
	}
	else{
		gxt->pixels.pix32 = (COLOR*)AGIDL_MirrorImgData(gxt->pixels.pix32,&gxt->header.header.width,&gxt->header.header.height,AGIDL_GXTGetClrFmt(gxt),mirror);
	}
}

void AGIDL_MirrorBTI(AGIDL_BTI* bti, AGIDL_MIRROR mirror){
	if(AGIDL_GetBitCount(AGIDL_BTIGetClrFmt(bti)) == 16){
		bti->pixels.pix16 = (COLOR16*)AGIDL_MirrorImgData(bti->pixels.pix16,&bti->header.width,&bti->header.height,AGIDL_BTIGetClrFmt(bti),mirror);
	}
	else{
		bti->pixels.pix32 = (COLOR*)AGIDL_MirrorImgData(bti->pixels.pix32,&bti->header.width,&bti->header.height,AGIDL_BTIGetClrFmt(bti),mirror);
	}
}

void AGIDL_WrapBMP(AGIDL_BMP* bmp, u8 num_of_wraps){
	if(AGIDL_GetBitCount(AGIDL_BMPGetClrFmt(bmp)) == 16){
		bmp->pixels.pix16 = (COLOR16*)AGIDL_WrapImgData(bmp->pixels.pix16,&bmp->header.width,AGIDL_BMPGetHeight(bmp),AGIDL_BMPGetClrFmt(bmp),num_of_wraps);
	}
	else{
		bmp->pixels.pix32 = (COLOR*)AGIDL_WrapImgData(bmp->pixels.pix32,&bmp->header.width,AGIDL_BMPGetHeight(bmp),AGIDL_BMPGetClrFmt(bmp),num_of_wraps);
	}
}

void AGIDL_WrapTGA(AGIDL_TGA* tga, u8 num_of_wraps){
	if(AGIDL_GetBitCount(AGIDL_TGAGetClrFmt(tga)) == 16){
		tga->pixels.pix16 = (COLOR16*)AGIDL_WrapImgData(tga->pixels.pix16,&tga->header.width,AGIDL_TGAGetHeight(tga),AGIDL_TGAGetClrFmt(tga),num_of_wraps);
	}
	else{
		tga->pixels.pix32 = (COLOR*)AGIDL_WrapImgData(tga->pixels.pix32,&tga->header.width,AGIDL_TGAGetHeight(tga),AGIDL_TGAGetClrFmt(tga),num_of_wraps);
	}
}

void AGIDL_WrapTIM(AGIDL_TIM* tim, u8 num_of_wraps){
	if(AGIDL_GetBitCount(AGIDL_TIMGetClrFmt(tim)) == 16){
		tim->pixels.pix16 = (COLOR16*)AGIDL_WrapImgData(tim->pixels.pix16,&tim->img_header.width,AGIDL_TIMGetHeight(tim),AGIDL_TIMGetClrFmt(tim),num_of_wraps);
	}
	else{
		tim->pixels.pix32 = (COLOR*)AGIDL_WrapImgData(tim->pixels.pix32,&tim->img_header.width,AGIDL_TIMGetHeight(tim),AGIDL_TIMGetClrFmt(tim),num_of_wraps);
	}
}

void AGIDL_WrapPCX(AGIDL_PCX* pcx, u8 num_of_wraps){
	if(AGIDL_GetBitCount(AGIDL_PCXGetClrFmt(pcx)) == 16){
		pcx->pixels.pix16 = (COLOR16*)AGIDL_WrapImgData(pcx->pixels.pix16,&pcx->header.width,AGIDL_PCXGetHeight(pcx),AGIDL_PCXGetClrFmt(pcx),num_of_wraps);
	}
	else{
		pcx->pixels.pix32 = (COLOR*)AGIDL_WrapImgData(pcx->pixels.pix32,&pcx->header.width,AGIDL_PCXGetHeight(pcx),AGIDL_PCXGetClrFmt(pcx),num_of_wraps);
	}
}

void AGIDL_WrapLMP(AGIDL_LMP* lmp, u8 num_of_wraps){
	if(AGIDL_GetBitCount(AGIDL_LMPGetClrFmt(lmp)) == 16){
		lmp->pixels.pix16 = (COLOR16*)AGIDL_WrapImgData(lmp->pixels.pix16,&lmp->width,AGIDL_LMPGetHeight(lmp),AGIDL_LMPGetClrFmt(lmp),num_of_wraps);
	}
	else{
		lmp->pixels.pix32 = (COLOR*)AGIDL_WrapImgData(lmp->pixels.pix32,&lmp->width,AGIDL_LMPGetHeight(lmp),AGIDL_LMPGetClrFmt(lmp),num_of_wraps);
	}
}

void AGIDL_WrapPVR(AGIDL_PVR* pvr, u8 num_of_wraps){
	if(AGIDL_GetBitCount(AGIDL_PVRGetClrFmt(pvr)) == 16){
		pvr->pixels.pix16 = (COLOR16*)AGIDL_WrapImgData(pvr->pixels.pix16,&pvr->header.width,AGIDL_PVRGetHeight(pvr),AGIDL_PVRGetClrFmt(pvr),num_of_wraps);
	}
	else{
		pvr->pixels.pix32 = (COLOR*)AGIDL_WrapImgData(pvr->pixels.pix32,&pvr->header.width,AGIDL_PVRGetHeight(pvr),AGIDL_PVRGetClrFmt(pvr),num_of_wraps);
	}
}

void AGIDL_WrapGXT(AGIDL_GXT* gxt, u8 num_of_wraps){
	if(AGIDL_GetBitCount(AGIDL_GXTGetClrFmt(gxt)) == 16){
		gxt->pixels.pix16 = (COLOR16*)AGIDL_WrapImgData(gxt->pixels.pix16,&gxt->header.header.width,AGIDL_GXTGetHeight(gxt),AGIDL_GXTGetClrFmt(gxt),num_of_wraps);
	}
	else{
		gxt->pixels.pix32 = (COLOR*)AGIDL_WrapImgData(gxt->pixels.pix32,&gxt->header.header.width,AGIDL_GXTGetHeight(gxt),AGIDL_GXTGetClrFmt(gxt),num_of_wraps);
	}
}

void AGIDL_WrapBTI(AGIDL_BTI* bti, u8 num_of_wraps){
	if(AGIDL_GetBitCount(AGIDL_BTIGetClrFmt(bti)) == 16){
		bti->pixels.pix16 = (COLOR16*)AGIDL_WrapImgData(bti->pixels.pix16,&bti->header.width,AGIDL_BTIGetHeight(bti),AGIDL_BTIGetClrFmt(bti),num_of_wraps);
	}
	else{
		bti->pixels.pix32 = (COLOR*)AGIDL_WrapImgData(bti->pixels.pix32,&bti->header.width,AGIDL_BTIGetHeight(bti),AGIDL_BTIGetClrFmt(bti),num_of_wraps);
	}
}

void AGIDL_WrapAndMirrorBMP(AGIDL_BMP* bmp, u8 num_of_wraps, AGIDL_MIRROR mirror){
	if(AGIDL_GetBitCount(AGIDL_BMPGetClrFmt(bmp)) == 16){
		bmp->pixels.pix16 = (COLOR16*)AGIDL_WrapAndMirrorImgData(bmp->pixels.pix16,&bmp->header.width,&bmp->header.height,AGIDL_BMPGetClrFmt(bmp),num_of_wraps, mirror);
	}
	else{
		bmp->pixels.pix32 = (COLOR*)AGIDL_WrapAndMirrorImgData(bmp->pixels.pix32,&bmp->header.width,&bmp->header.height,AGIDL_BMPGetClrFmt(bmp),num_of_wraps, mirror);
	}
}

void AGIDL_WrapAndMirrorTGA(AGIDL_TGA* tga, u8 num_of_wraps, AGIDL_MIRROR mirror){
	if(AGIDL_GetBitCount(AGIDL_TGAGetClrFmt(tga)) == 16){
		tga->pixels.pix16 = (COLOR16*)AGIDL_WrapAndMirrorImgData(tga->pixels.pix16,&tga->header.width,&tga->header.height,AGIDL_TGAGetClrFmt(tga),num_of_wraps, mirror);
	}
	else{
		tga->pixels.pix32 = (COLOR*)AGIDL_WrapAndMirrorImgData(tga->pixels.pix32,&tga->header.width,&tga->header.height,AGIDL_TGAGetClrFmt(tga),num_of_wraps, mirror);
	}
}

void AGIDL_WrapAndMirrorTIM(AGIDL_TIM* tim, u8 num_of_wraps, AGIDL_MIRROR mirror){
	if(AGIDL_GetBitCount(AGIDL_TIMGetClrFmt(tim)) == 16){
		tim->pixels.pix16 = (COLOR16*)AGIDL_WrapAndMirrorImgData(tim->pixels.pix16,&tim->img_header.width,&tim->img_header.height,AGIDL_TIMGetClrFmt(tim),num_of_wraps, mirror);
	}
	else{
		tim->pixels.pix32 = (COLOR*)AGIDL_WrapAndMirrorImgData(tim->pixels.pix32,&tim->img_header.width,&tim->img_header.height,AGIDL_TIMGetClrFmt(tim),num_of_wraps, mirror);
	}
}

void AGIDL_WrapAndMirrorPCX(AGIDL_PCX* pcx, u8 num_of_wraps, AGIDL_MIRROR mirror){
	if(AGIDL_GetBitCount(AGIDL_PCXGetClrFmt(pcx)) == 16){
		pcx->pixels.pix16 = (COLOR16*)AGIDL_WrapAndMirrorImgData(pcx->pixels.pix16,&pcx->header.width,&pcx->header.height,AGIDL_PCXGetClrFmt(pcx),num_of_wraps, mirror);
	}
	else{
		pcx->pixels.pix32 = (COLOR*)AGIDL_WrapAndMirrorImgData(pcx->pixels.pix32,&pcx->header.width,&pcx->header.height,AGIDL_PCXGetClrFmt(pcx),num_of_wraps, mirror);
	}
}

void AGIDL_WrapAndMirrorLMP(AGIDL_LMP* lmp, u8 num_of_wraps, AGIDL_MIRROR mirror){
	if(AGIDL_GetBitCount(AGIDL_LMPGetClrFmt(lmp)) == 16){
		lmp->pixels.pix16 = (COLOR16*)AGIDL_WrapAndMirrorImgData(lmp->pixels.pix16,&lmp->width,&lmp->height,AGIDL_LMPGetClrFmt(lmp),num_of_wraps, mirror);
	}
	else{
		lmp->pixels.pix32 = (COLOR*)AGIDL_WrapAndMirrorImgData(lmp->pixels.pix32,&lmp->width,&lmp->height,AGIDL_LMPGetClrFmt(lmp),num_of_wraps, mirror);
	}
}

void AGIDL_WrapAndMirrorPVR(AGIDL_PVR* pvr, u8 num_of_wraps, AGIDL_MIRROR mirror){
	if(AGIDL_GetBitCount(AGIDL_PVRGetClrFmt(pvr)) == 16){
		pvr->pixels.pix16 = (COLOR16*)AGIDL_WrapAndMirrorImgData(pvr->pixels.pix16,&pvr->header.width,&pvr->header.height,AGIDL_PVRGetClrFmt(pvr),num_of_wraps, mirror);
	}
	else{
		pvr->pixels.pix32 = (COLOR*)AGIDL_WrapAndMirrorImgData(pvr->pixels.pix32,&pvr->header.width,&pvr->header.height,AGIDL_PVRGetClrFmt(pvr),num_of_wraps, mirror);
	}
}

void AGIDL_WrapAndMirrorGXT(AGIDL_GXT* gxt, u8 num_of_wraps, AGIDL_MIRROR mirror){
	if(AGIDL_GetBitCount(AGIDL_GXTGetClrFmt(gxt)) == 16){
		gxt->pixels.pix16 = (COLOR16*)AGIDL_WrapAndMirrorImgData(gxt->pixels.pix16,&gxt->header.header.width,&gxt->header.header.height,AGIDL_GXTGetClrFmt(gxt),num_of_wraps, mirror);
	}
	else{
		gxt->pixels.pix32 = (COLOR*)AGIDL_WrapAndMirrorImgData(gxt->pixels.pix32,&gxt->header.header.width,&gxt->header.header.height,AGIDL_GXTGetClrFmt(gxt),num_of_wraps, mirror);
	}
}

void AGIDL_WrapAndMirrorBTI(AGIDL_BTI* bti, u8 num_of_wraps, AGIDL_MIRROR mirror){
	if(AGIDL_GetBitCount(AGIDL_BTIGetClrFmt(bti)) == 16){
		bti->pixels.pix16 = (COLOR16*)AGIDL_WrapAndMirrorImgData(bti->pixels.pix16,&bti->header.width,&bti->header.height,AGIDL_BTIGetClrFmt(bti),num_of_wraps, mirror);
	}
	else{
		bti->pixels.pix32 = (COLOR*)AGIDL_WrapAndMirrorImgData(bti->pixels.pix32,&bti->header.width,&bti->header.height,AGIDL_BTIGetClrFmt(bti),num_of_wraps, mirror);
	}
}