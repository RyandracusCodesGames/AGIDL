/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023 Ryandracus Chapman
*
*   Library: libagidl
*   File: agidl_imgp_filter.c
*   Date: 12/13/2023
*   Version: 0.2b
*   Updated: 12/13/2023
*   Author: Ryandracus Chapman
*
********************************************/
#include <stdlib.h>
#include "agidl_imgp_filter.h"
#include "agidl_imgp_scale.h"
#include "agidl_img_bmp.h"
#include "agidl_cc_mixer.h"

void AGIDL_FilterImgDataBilerp(void* data, u32 width, u32 height, AGIDL_CLR_FMT fmt){
	if(AGIDL_GetBitCount(fmt) == 24 || AGIDL_GetBitCount(fmt) == 32){
		COLOR* clrs = (COLOR*)data;

		u16 x,y;
		for(y = 0; y < height - 1; y++){
			for(x = 0; x < width - 1; x++){
				COLOR clr1 = AGIDL_GetClr(clrs,x,y,width,height);
				COLOR clr2 = AGIDL_GetClr(clrs,x+1,y,width,height);
				COLOR clr3 = AGIDL_GetClr(clrs,x,y+1,width,height);
				COLOR clr4 = AGIDL_GetClr(clrs,x+1,y+1,width,height);
				
				COLOR clr = AGIDL_BilerpColor(clr1,clr2,clr3,clr4,0.5,0.5,fmt);
				
				AGIDL_SetClr(clrs,clr,x,y,width,height); 
			}
		}
	}
	else{
		COLOR16* clrs = (COLOR16*)data;

		u16 x,y;
		for(y = 0; y < height - 1; y++){
			for(x = 0; x < width - 1; x++){
				COLOR16 clr1 = AGIDL_GetClr16(clrs,x,y,width,height);
				COLOR16 clr2 = AGIDL_GetClr16(clrs,x+1,y,width,height);
				COLOR16 clr3 = AGIDL_GetClr16(clrs,x,y+1,width,height);
				COLOR16 clr4 = AGIDL_GetClr16(clrs,x+1,y+1,width,height);
				
				COLOR16 clr = AGIDL_BilerpColor(clr1,clr2,clr3,clr4,0.5,0.5,fmt);
				
				AGIDL_SetClr16(clrs,clr,x,y,width,height); 
			}
		}
	}
}

void AGIDL_FilterImgDataTrilerp(void* data, u32 width, u32 height, AGIDL_CLR_FMT fmt){
	if(AGIDL_GetBitCount(fmt) == 24 || AGIDL_GetBitCount(fmt) == 32){
		COLOR* clrs = (COLOR*)data;
		COLOR* clrscpy = (COLOR*)malloc(sizeof(COLOR)*width*height);
		
		AGIDL_ClrMemcpy(clrscpy,clrs,width*height);
		
		u16 w = width, h = height;
		
		COLOR* clrscale = (COLOR*)malloc(sizeof(COLOR)*w*h);
		clrscale = (COLOR*)AGIDL_ScaleImgDataNearest(clrscpy,&w,&h,0.5f,0.5f,fmt);
		
		AGIDL_FilterImgDataBilerp(clrscale,w,h,fmt);
		
		float x_scale = ((float)(w-1)/width);
		float y_scale = ((float)(h-1)/height);
		
		u32 x,y;
		for(y = 0; y < height - 1; y++){
			for(x = 0; x < width - 1; x++){
				
				u16 xx = (x * x_scale);
				u16 yy = (y * y_scale);
			
				COLOR clr1 = AGIDL_GetClr(clrs,x,y,width,height);
				COLOR clr2 = AGIDL_GetClr(clrs,x+1,y,width,height);
				COLOR clr3 = AGIDL_GetClr(clrs,x,y+1,width,height);
				COLOR clr4 = AGIDL_GetClr(clrs,x+1,y+1,width,height);
				
				COLOR clr1s = AGIDL_GetClr(clrscale,xx,yy,w,h);
				COLOR clr2s = AGIDL_GetClr(clrscale,xx+1,yy,w,h);
				COLOR clr3s = AGIDL_GetClr(clrscale,xx,yy+1,w,h);
				COLOR clr4s = AGIDL_GetClr(clrscale,xx+1,yy+1,w,h);
				
				COLOR clrbilerp1 = AGIDL_BilerpColor(clr1,clr2,clr3,clr4,0.5f,0.5f,fmt);
				COLOR clrbilerp2 = AGIDL_BilerpColor(clr1s,clr2s,clr3s,clr4s,0.5f,0.5f,fmt);
				
				COLOR clr = AGIDL_InterpColor(clrbilerp1,clrbilerp2,0.5f,fmt);
				
				AGIDL_SetClr(clrs,clr,x,y,width,height);
			}
		}
		
		free(clrscale);
	}
	else{
		COLOR16* clrs = (COLOR16*)data;
		COLOR16* clrscpy = (COLOR16*)malloc(sizeof(COLOR16)*width*height);
		
		AGIDL_ClrMemcpy16(clrscpy,clrs,width*height);
		
		u16 w = width, h = height;
		
		COLOR16* clrscale = (COLOR16*)malloc(sizeof(COLOR16)*w*h);
		clrscale = (COLOR16*)AGIDL_ScaleImgDataNearest(clrscpy,&w,&h,0.5f,0.5f,fmt);
		
		AGIDL_FilterImgDataBilerp(clrscale,w,h,fmt);
		
		float x_scale = ((float)(w-1)/width);
		float y_scale = ((float)(h-1)/height);
		
		u32 x,y;
		for(y = 0; y < height - 1; y++){
			for(x = 0; x < width - 1; x++){
				
				u16 xx = (x * x_scale);
				u16 yy = (y * y_scale);
			
				COLOR16 clr1 = AGIDL_GetClr16(clrs,x,y,width,height);
				COLOR16 clr2 = AGIDL_GetClr16(clrs,x+1,y,width,height);
				COLOR16 clr3 = AGIDL_GetClr16(clrs,x,y+1,width,height);
				COLOR16 clr4 = AGIDL_GetClr16(clrs,x+1,y+1,width,height);
				
				COLOR16 clr1s = AGIDL_GetClr16(clrscale,xx,yy,w,h);
				COLOR16 clr2s = AGIDL_GetClr16(clrscale,xx+1,yy,w,h);
				COLOR16 clr3s = AGIDL_GetClr16(clrscale,xx,yy+1,w,h);
				COLOR16 clr4s = AGIDL_GetClr16(clrscale,xx+1,yy+1,w,h);
				
				COLOR16 clrbilerp1 = AGIDL_BilerpColor(clr1,clr2,clr3,clr4,0.5f,0.5f,fmt);
				COLOR16 clrbilerp2 = AGIDL_BilerpColor(clr1s,clr2s,clr3s,clr4s,0.5f,0.5f,fmt);
				
				COLOR16 clr = AGIDL_InterpColor(clrbilerp1,clrbilerp2,0.5f,fmt);
				
				AGIDL_SetClr16(clrs,clr,x,y,width,height);
			}
		}
		
		free(clrscale);
	}
}