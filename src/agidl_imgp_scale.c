/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023 Ryandracus Chapman
*
*   Library: libagidl
*   File: agidl_imgp_scale.c
*   Date: 12/9/2023
*   Version: 0.2b
*   Updated: 12/10/2023
*   Author: Ryandracus Chapman
*
********************************************/
#include <stdlib.h>
#include <string.h>
#include "agidl_imgp_scale.h"
#include "agidl_cc_mixer.h"

void * AGIDL_ScaleImgDataNearest(void* data, u16* width, u16* height, float sx, float sy, AGIDL_CLR_FMT fmt){
	if(AGIDL_GetBitCount(fmt) == 24 || AGIDL_GetBitCount(fmt) == 32){
		u16 worg = *width;
		u16 horg = *height;
		
		COLOR* clrs = (COLOR*)data;
		
		u16 newwidth = (u16)(worg*sx), newheight = (u16)(horg*sy);
		
		COLOR* scale = (COLOR*)malloc(sizeof(COLOR)*newwidth*newheight);
		
		float xscale = ((float)(worg-1)/newwidth);
		float yscale = ((float)(horg-1)/newheight);
		
		u16 x,y;
		for(y = 0; y < newheight; y++){
			for(x = 0; x < newwidth; x++){
				u16 x2 = (x*xscale);
				u16 y2 = (y*yscale);
				
				COLOR clr = AGIDL_GetClr(clrs,x2,y2,worg,horg);
				AGIDL_SetClr(scale,clr,x,y,newwidth,newheight);
			}
		}
		
		*width = newwidth;
		*height = newheight;
		
		free(clrs);

		return scale;
	}
	else{
		u16 worg = *width;
		u16 horg = *height;
		
		COLOR16* clrs = (COLOR16*)data;
		
		u16 newwidth = (u16)(worg*sx), newheight = (u16)(horg*sy);
		
		COLOR16* scale = (COLOR16*)malloc(sizeof(COLOR16)*newwidth*newheight);
		
		float xscale = ((float)(worg-1)/newwidth);
		float yscale = ((float)(horg-1)/newheight);
		
		u16 x,y;
		for(y = 0; y < newheight; y++){
			for(x = 0; x < newwidth; x++){
				u16 x2 = (x*xscale);
				u16 y2 = (y*yscale);
				
				COLOR16 clr = AGIDL_GetClr16(clrs,x2,y2,worg,horg);
				AGIDL_SetClr16(scale,clr,x,y,newwidth,newheight);
			}
		}
		
		*width = newwidth;
		*height = newheight;
		
		free(clrs);
		
		return scale;
	}
}

void * AGIDL_ScaleImgDataBilerp(void* data, u16* width, u16* height, float sx, float sy, AGIDL_CLR_FMT fmt){
	if(AGIDL_GetBitCount(fmt) == 24 || AGIDL_GetBitCount(fmt) == 32){
		u16 worg = *width;
		u16 horg = *height;
		
		COLOR* clrs = (COLOR*)data;
		
		u16 newwidth = (u16)(worg*sx), newheight = (u16)(horg*sy);
		
		COLOR* scale = (COLOR*)malloc(sizeof(COLOR)*newwidth*newheight);
		
		float xscale = ((float)(worg-1)/newwidth);
		float yscale = ((float)(horg-1)/newheight);
		
		float x_diff, y_diff;
		
		u16 x,y;
		for(y = 0; y < newheight; y++){
			for(x = 0; x < newwidth; x++){
				u16 x2 = (x*xscale);
				u16 y2 = (y*yscale);
				
				COLOR clr1 = AGIDL_GetClr(clrs,x2,y2,worg,horg);
				COLOR clr2 = AGIDL_GetClr(clrs,x2+1,y2,worg,horg);
				COLOR clr3 = AGIDL_GetClr(clrs,x2,y2+1,worg,horg);
				COLOR clr4 = AGIDL_GetClr(clrs,x2+1,y2+1,worg,horg);
				
				COLOR clr = AGIDL_BilerpColor(clr1,clr2,clr3,clr4,0.5,0.5,fmt);
				
				AGIDL_SetClr(scale,clr,x,y,newwidth,newheight);
			}
		}
		
		*width = newwidth;
		*height = newheight;
		
		free(clrs);

		return scale;
	}
	else{
		u16 worg = *width;
		u16 horg = *height;
		
		COLOR16* clrs = (COLOR16*)data;
		
		u16 newwidth = (u16)(worg*sx), newheight = (u16)(horg*sy);
		
		COLOR16* scale = (COLOR16*)malloc(sizeof(COLOR16)*newwidth*newheight);
		
		float xscale = ((float)(worg-1)/newwidth);
		float yscale = ((float)(horg-1)/newheight);
		
		float x_diff, y_diff;
		
		u16 x,y;
		for(y = 0; y < newheight; y++){
			for(x = 0; x < newwidth; x++){
				u16 x2 = (x*xscale);
				u16 y2 = (y*yscale);
				
				COLOR16 clr1 = AGIDL_GetClr16(clrs,x2,y2,worg,horg);
				COLOR16 clr2 = AGIDL_GetClr16(clrs,x2+1,y2,worg,horg);
				COLOR16 clr3 = AGIDL_GetClr16(clrs,x2,y2+1,worg,horg);
				COLOR16 clr4 = AGIDL_GetClr16(clrs,x2+1,y2+1,worg,horg);
				
				COLOR16 clr = AGIDL_BilerpColor(clr1,clr2,clr3,clr4,0.5,0.5,fmt);
				
				AGIDL_SetClr16(scale,clr,x,y,newwidth,newheight);
			}
		}
		
		*width = newwidth;
		*height = newheight;
		
		free(clrs);

		return scale;
	}
}

void * AGIDL_ScaleImgDataTrilerp(void* data, u16* width, u16* height, float sx, float sy, AGIDL_CLR_FMT fmt){
	if(AGIDL_GetBitCount(fmt) == 24 || AGIDL_GetBitCount(fmt) == 32){
		u16 worg = *width;
		u16 horg = *height;
		
		u16 whalf = worg;
		u16 hhalf = horg;
		
		COLOR* clrs = (COLOR*)data;
		
		u16 newwidth = (u16)(worg*sx), newheight = (u16)(horg*sy);
		
		COLOR* datacpy = (COLOR*)malloc(sizeof(COLOR)*worg*horg);
		AGIDL_ClrMemcpy(datacpy,clrs,worg*horg);
		
		COLOR* scale = (COLOR*)malloc(sizeof(COLOR)*newwidth*newheight);
		COLOR* scalehalf = (COLOR*)malloc(sizeof(COLOR)*whalf*hhalf);
		
		scalehalf = (COLOR*)AGIDL_ScaleImgDataBilerp(datacpy,&whalf,&hhalf,0.5f,0.5f,fmt);
		
		float xscale = ((float)(worg-1)/newwidth);
		float yscale = ((float)(horg-1)/newheight);
		
		float xscalehalf = ((float)(whalf-1)/newwidth);
		float yscalehalf = ((float)(hhalf-1)/newheight);
		
		float x_diff, y_diff, x_half, y_half;
		
		u16 x,y;
		for(y = 0; y < newheight; y++){
			for(x = 0; x < newwidth; x++){
				u16 x2 = (x*xscale);
				u16 y2 = (y*yscale);
				
				u16 x2half = (x*xscalehalf);
				u16 y2half = (y*yscalehalf);
				
				COLOR clr1 = AGIDL_GetClr(clrs,x2,y2,worg,horg);
				COLOR clr2 = AGIDL_GetClr(clrs,x2+1,y2,worg,horg);
				COLOR clr3 = AGIDL_GetClr(clrs,x2,y2+1,worg,horg);
				COLOR clr4 = AGIDL_GetClr(clrs,x2+1,y2+1,worg,horg);
				
				COLOR clr1half = AGIDL_GetClr(scalehalf,x2half,y2half,whalf,hhalf);
				COLOR clr2half = AGIDL_GetClr(scalehalf,x2half+1,y2half,whalf,hhalf);
				COLOR clr3half = AGIDL_GetClr(scalehalf,x2half,y2half+1,whalf,hhalf);
				COLOR clr4half = AGIDL_GetClr(scalehalf,x2half+1,y2half+1,whalf,hhalf);
				
				COLOR clr = AGIDL_BilerpColor(clr1,clr2,clr3,clr4,0.5,0.5,fmt);
				COLOR clrhalf = AGIDL_BilerpColor(clr1half,clr2half,clr3half,clr4half,0.5,0.5,fmt);
				
				COLOR clrfinal = AGIDL_InterpColor(clr,clrhalf,0.5f,fmt);
				
				AGIDL_SetClr(scale,clrfinal,x,y,newwidth,newheight);
			}
		}
		
		*width = newwidth;
		*height = newheight;
		
		free(clrs);
		free(scalehalf);

		return scale;
	}
	else{
		u16 worg = *width;
		u16 horg = *height;
		
		u16 whalf = worg;
		u16 hhalf = horg;
		
		COLOR16* clrs = (COLOR16*)data;
		
		u16 newwidth = (u16)(worg*sx), newheight = (u16)(horg*sy);
		
		COLOR16* datacpy = (COLOR16*)malloc(sizeof(COLOR16)*worg*horg);
		AGIDL_ClrMemcpy16(datacpy,clrs,worg*horg);
		
		COLOR16* scale = (COLOR16*)malloc(sizeof(COLOR16)*newwidth*newheight);
		COLOR16* scalehalf = (COLOR16*)malloc(sizeof(COLOR16)*whalf*hhalf);
		
		scalehalf = (COLOR16*)AGIDL_ScaleImgDataBilerp(datacpy,&whalf,&hhalf,0.5f,0.5f,fmt);
		
		float xscale = ((float)(worg-1)/newwidth);
		float yscale = ((float)(horg-1)/newheight);
		
		float xscalehalf = ((float)(whalf-1)/newwidth);
		float yscalehalf = ((float)(hhalf-1)/newheight);
		
		float x_diff, y_diff, x_half, y_half;
		
		u16 x,y;
		for(y = 0; y < newheight; y++){
			for(x = 0; x < newwidth; x++){
				u16 x2 = (x*xscale);
				u16 y2 = (y*yscale);
				
				u16 x2half = (x*xscalehalf);
				u16 y2half = (y*yscalehalf);
				
				COLOR16 clr1 = AGIDL_GetClr16(clrs,x2,y2,worg,horg);
				COLOR16 clr2 = AGIDL_GetClr16(clrs,x2+1,y2,worg,horg);
				COLOR16 clr3 = AGIDL_GetClr16(clrs,x2,y2+1,worg,horg);
				COLOR16 clr4 = AGIDL_GetClr16(clrs,x2+1,y2+1,worg,horg);
				
				COLOR16 clr1half = AGIDL_GetClr16(scalehalf,x2half,y2half,whalf,hhalf);
				COLOR16 clr2half = AGIDL_GetClr16(scalehalf,x2half+1,y2half,whalf,hhalf);
				COLOR16 clr3half = AGIDL_GetClr16(scalehalf,x2half,y2half+1,whalf,hhalf);
				COLOR16 clr4half = AGIDL_GetClr16(scalehalf,x2half+1,y2half+1,whalf,hhalf);
				
				COLOR16 clr = AGIDL_BilerpColor(clr1,clr2,clr3,clr4,0.5,0.5,fmt);
				COLOR16 clrhalf = AGIDL_BilerpColor(clr1half,clr2half,clr3half,clr4half,0.5,0.5,fmt);
				
				COLOR16 clrfinal = AGIDL_InterpColor(clr,clrhalf,0.5f,fmt);
				
				AGIDL_SetClr16(scale,clrfinal,x,y,newwidth,newheight);
			}
		}
		
		*width = newwidth;
		*height = newheight;
		
		free(clrs);
		free(scalehalf);

		return scale;
	}
}

void * AGIDL_ScaleImgData(void* data, u16* width, u16* height, float sx, float sy, AGIDL_SCALE scale, AGIDL_CLR_FMT fmt){
	switch(scale){
		case AGIDL_SCALE_NEAREST:{
			return AGIDL_ScaleImgDataNearest(data,width,height,sx,sy,fmt);
		}break;
		case AGIDL_SCALE_BILERP:{
			return AGIDL_ScaleImgDataBilerp(data,width,height,sx,sy,fmt);
		}break;
		case AGIDL_SCALE_TRILERP:{
			return AGIDL_ScaleImgDataTrilerp(data,width,height,sx,sy,fmt);
		}break;
	}
	return AGIDL_ScaleImgDataNearest(data,width,height,sx,sy,fmt);
}