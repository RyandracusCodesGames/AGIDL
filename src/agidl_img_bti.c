#include <stdlib.h>
#include <string.h>
#include "agidl_img_bti.h"
#include "agidl_cc_core.h"

/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023 Ryandracus Chapman
*
*   Library: libagidl
*   File: agidl_img_bti.c
*   Date: 11/22/2023
*   Version: 0.1b
*   Updated: 12/14/2023
*   Author: Ryandracus Chapman
*
********************************************/

void AGIDL_SetBTIFilename(AGIDL_BTI* bti, const char* filename){
	bti->filename = (char*)realloc(bti->filename,strlen(filename));
	AGIDL_FilenameCpy(bti->filename,filename);
}

void AGIDL_BTISetWidth(AGIDL_BTI* bti, u16 width){
	bti->header.width = width;
}

void AGIDL_BTISetHeight(AGIDL_BTI* bti, u16 height){
	bti->header.height = height;
}

void AGIDL_BTISetClrFmt(AGIDL_BTI* bti, AGIDL_CLR_FMT fmt){
	bti->fmt = fmt;
}

void AGIDL_BTISetMaxDiff(AGIDL_BTI* bti, int max_diff){
	bti->max_diff = max_diff;
}

void AGIDL_BTISetICPMode(AGIDL_BTI* bti, int mode){
	bti->icp = mode;
}

void AGIDL_BTISetCompression(AGIDL_BTI* bti, int compress){
	bti->compression = compress;
}

void AGIDL_BTISetClr(AGIDL_BTI *bti, int x, int y, COLOR clr){
	if(AGIDL_GetBitCount(AGIDL_BTIGetClrFmt(bti)) != 16){
		AGIDL_SetClr(bti->pixels.pix32,clr,x,y,AGIDL_BTIGetWidth(bti),AGIDL_BTIGetHeight(bti));
	}
	else{
		AGIDL_SetClr16(bti->pixels.pix16,AGIDL_CLR_TO_CLR16(clr,AGIDL_BGR_888,AGIDL_BTIGetClrFmt(bti)),x,y,AGIDL_BTIGetWidth(bti),AGIDL_BTIGetHeight(bti));
	}
}

void AGIDL_BTISetClr16(AGIDL_BTI *bti, int x, int y, COLOR16 clr){
	if(AGIDL_GetBitCount(AGIDL_BTIGetClrFmt(bti) == 16)){
		AGIDL_SetClr16(bti->pixels.pix16,clr,x,y,AGIDL_BTIGetWidth(bti),AGIDL_BTIGetHeight(bti));
	}
	else{
		AGIDL_SetClr(bti->pixels.pix32,AGIDL_CLR16_TO_CLR(clr,AGIDL_RGB_555,AGIDL_BTIGetClrFmt(bti)),x,y,AGIDL_BTIGetWidth(bti),AGIDL_BTIGetHeight(bti));
	}
}

void AGIDL_BTISetRGB(AGIDL_BTI* bti, int x, int y, u8 r, u8 g, u8 b){
	switch(AGIDL_GetBitCount(AGIDL_BTIGetClrFmt(bti))){
		case 24:{
			AGIDL_BTISetClr(bti,x,y,AGIDL_RGB(r,g,b,AGIDL_BTIGetClrFmt(bti)));
		}break;
		case 16:{
			AGIDL_BTISetClr16(bti,x,y,AGIDL_RGB16(r,g,b,AGIDL_BTIGetClrFmt(bti)));
		}break;
		case 32:{
			AGIDL_BTISetRGBA(bti,x,y,r,g,b,0xff);
		}break;	
	}
}

void AGIDL_BTISetRGBA(AGIDL_BTI* bti, int x, int y, u8 r, u8 g, u8 b, u8 a){
	if(AGIDL_GetBitCount(AGIDL_BTIGetClrFmt(bti)) == 32){
		AGIDL_BTISetClr(bti,x,y,AGIDL_RGBA(r,g,b,a,AGIDL_BTIGetClrFmt(bti)));
	}
}

void AGIDL_ClearBTI(AGIDL_BTI *bti, COLOR clr){
	if(AGIDL_GetBitCount(AGIDL_BTIGetClrFmt(bti)) != 16){
		AGIDL_ClrMemset(bti->pixels.pix32,clr,AGIDL_BTIGetSize(bti));
	}
	else{
		AGIDL_ClrMemset16(bti->pixels.pix16,(COLOR16)clr,AGIDL_BTIGetSize(bti));
	}
}

void AGIDL_ClearBTI16(AGIDL_BTI *bti, COLOR16 clr){
	if(AGIDL_GetBitCount(AGIDL_BTIGetClrFmt(bti)) == 16){
		AGIDL_ClrMemset16(bti->pixels.pix16,clr,AGIDL_BTIGetSize(bti));
	}
	else{
		AGIDL_ClrMemset(bti->pixels.pix32,AGIDL_CLR16_TO_CLR(clr,AGIDL_RGB_555,AGIDL_BTIGetClrFmt(bti)),AGIDL_BTIGetSize(bti));
	}
}

int AGIDL_BTIGetWidth(AGIDL_BTI* bti){
	return bti->header.width;
}

int AGIDL_BTIGetHeight(AGIDL_BTI* bti){
	return bti->header.height;
}

u32 AGIDL_BTIGetSize(AGIDL_BTI* bti){
	return AGIDL_BTIGetWidth(bti) * AGIDL_BTIGetHeight(bti);
}

AGIDL_CLR_FMT AGIDL_BTIGetClrFmt(AGIDL_BTI* bti){
	return bti->fmt;
}

int AGIDL_BTIGetMaxDiff(AGIDL_BTI* bti){
	return bti->max_diff;
}

COLOR AGIDL_BTIGetClr(AGIDL_BTI* bti, int x, int y){
	return AGIDL_GetClr(bti->pixels.pix32,x,y,AGIDL_BTIGetWidth(bti),AGIDL_BTIGetHeight(bti));
}
COLOR16 AGIDL_BTIGetClr16(AGIDL_BTI* bti, int x, int y){
	return AGIDL_GetClr16(bti->pixels.pix16,x,y,AGIDL_BTIGetWidth(bti),AGIDL_BTIGetHeight(bti));
}

void AGIDL_BTIRGB2BGR(AGIDL_BTI* bti){
	if(bti->fmt == AGIDL_RGB_888){
		AGIDL_RGB2BGR(bti->pixels.pix32,AGIDL_BTIGetWidth(bti),AGIDL_BTIGetHeight(bti),&bti->fmt);
	}
	if(bti->fmt == AGIDL_RGB_555 || bti->fmt == AGIDL_RGB_565){
		AGIDL_RGB2BGR16(bti->pixels.pix16,AGIDL_BTIGetWidth(bti),AGIDL_BTIGetHeight(bti),&bti->fmt);
	}
}

void AGIDL_BTIBGR2RGB(AGIDL_BTI* bti){
	if(bti->fmt == AGIDL_BGR_888){
		AGIDL_BGR2RGB(bti->pixels.pix32,AGIDL_BTIGetWidth(bti),AGIDL_BTIGetHeight(bti),&bti->fmt);
	}
	if(bti->fmt == AGIDL_BGR_555 || bti->fmt == AGIDL_BGR_565){
		AGIDL_BGR2RGB16(bti->pixels.pix16,AGIDL_BTIGetWidth(bti),AGIDL_BTIGetHeight(bti),&bti->fmt);
	}
}

void AGIDL_BTIConvert24BPPTO16BPP(AGIDL_BTI* bti){
	if(AGIDL_GetBitCount(AGIDL_BTIGetClrFmt(bti)) == 24){
		bti->pixels.pix16 = (COLOR16*)malloc(sizeof(COLOR16)*AGIDL_BTIGetSize(bti));
		AGIDL_24BPPTO16BPP(bti->pixels.pix32,bti->pixels.pix16,AGIDL_BTIGetWidth(bti),AGIDL_BTIGetHeight(bti),&bti->fmt);
		free(bti->pixels.pix32);
	}
}

void AGIDL_BTIConvert16BPPTO24BPP(AGIDL_BTI* bti){
	if(AGIDL_GetBitCount(AGIDL_BTIGetClrFmt(bti)) == 16){
		bti->pixels.pix16 = (COLOR16*)malloc(sizeof(COLOR16)*AGIDL_BTIGetSize(bti));
		AGIDL_24BPPTO16BPP(bti->pixels.pix32,bti->pixels.pix16,AGIDL_BTIGetWidth(bti),AGIDL_BTIGetHeight(bti),&bti->fmt);
		free(bti->pixels.pix32);
	}
}

void AGIDL_BTIRGBATORGB(AGIDL_BTI* bti){
	int x,y;
	for(y = 0; y < AGIDL_BTIGetHeight(bti); y++){
		for(x = 0; x < AGIDL_BTIGetWidth(bti); x++){
			COLOR clr = AGIDL_BTIGetClr(bti,x,y);
			u8 r = AGIDL_GetR(clr,bti->fmt);
			u8 g = AGIDL_GetG(clr,bti->fmt);
			u8 b = AGIDL_GetB(clr,bti->fmt);
			clr = AGIDL_RGB(r,g,b,AGIDL_RGB_888);
		}
	}
	bti->fmt = AGIDL_RGB_888;
}

void AGIDL_BTI555TO565(AGIDL_BTI* bti){
	AGIDL_555TO565(bti->pixels.pix16,AGIDL_BTIGetWidth(bti),AGIDL_BTIGetHeight(bti),&bti->fmt);
}

void AGIDL_BTI565TO555(AGIDL_BTI* bti){
	AGIDL_565TO555(bti->pixels.pix16,AGIDL_BTIGetWidth(bti),AGIDL_BTIGetHeight(bti),&bti->fmt);
}

void AGIDL_BTISyncPix(AGIDL_BTI* bti, COLOR* clrs){
	AGIDL_ClrMemcpy(bti->pixels.pix32,clrs,AGIDL_BTIGetSize(bti));
}

void AGIDL_BTISyncPix16(AGIDL_BTI* bti, COLOR16* clrs){
	AGIDL_ClrMemcpy16(bti->pixels.pix16,clrs,AGIDL_BTIGetSize(bti));
}

AGIDL_BTI* AGIDL_CreateBTI(const char* filename, int width, int height, AGIDL_CLR_FMT fmt){
	AGIDL_BTI* bti = (AGIDL_BTI*)malloc(sizeof(AGIDL_BTI));
	bti->filename = (char*)malloc(strlen(filename)+1);
	AGIDL_FilenameCpy(bti->filename,filename);
	AGIDL_BTISetWidth(bti,width);
	AGIDL_BTISetHeight(bti,height);
	AGIDL_BTISetClrFmt(bti,fmt);
	AGIDL_BTISetICPMode(bti,0);
	AGIDL_BTISetMaxDiff(bti,7);
	AGIDL_BTISetCompression(bti,0);
	
	if(AGIDL_GetBitCount(fmt) == 24 || AGIDL_GetBitCount(fmt) == 32){
		bti->pixels.pix32 = (COLOR*)malloc(sizeof(COLOR)*AGIDL_BTIGetSize(bti));
	}
	if(AGIDL_GetBitCount(fmt) == 16){
		bti->pixels.pix16 = (COLOR16*)malloc(sizeof(COLOR16)*AGIDL_BTIGetSize(bti));
	}
	
	return bti;
}

AGIDL_BTI* AGIDL_BTICpyImg(AGIDL_BTI* bti){
	AGIDL_BTI* cpybti = AGIDL_CreateBTI("cpy.bti",AGIDL_BTIGetWidth(bti),AGIDL_BTIGetHeight(bti),
	AGIDL_BTIGetClrFmt(bti));
	AGIDL_BTISetICPMode(cpybti,bti->icp);
	AGIDL_BTISetMaxDiff(cpybti,AGIDL_BTIGetMaxDiff(bti));
	AGIDL_BTISetCompression(cpybti,bti->compression);
	
	if(AGIDL_GetBitCount(AGIDL_BTIGetClrFmt(bti)) == 24 ||  AGIDL_GetBitCount(AGIDL_BTIGetClrFmt(bti)) == 32){
		AGIDL_BTISyncPix(cpybti,bti->pixels.pix32);
	}
	
	if(AGIDL_GetBitCount(AGIDL_BTIGetClrFmt(bti)) == 16){
		AGIDL_BTISyncPix16(cpybti,bti->pixels.pix16);
	}
	
	return cpybti;
}

void AGIDL_FreeBTI(AGIDL_BTI* bti){
	free(bti->filename);
	
	if(AGIDL_GetBitCount(AGIDL_BMPGetClrFmt(bti)) == 16){
		free(bti->pixels.pix16);
	}
	else{
		free(bti->pixels.pix32);
	}
	
	if(bti != NULL){
		bti = NULL;
	}
}

BTI_CLR_FMT AGIDL_GetBTIClrFmt(u8 type){
	switch(type){
		case 0x00:{
			return BTI_I4;
		}break;
		case 0x01:{
			return BTI_I8;
		}break;
		case 0x02:{
			return BTI_IA4;
		}break;
		case 0x03:{
			return BTI_IA8;
		}break;
		case 0x04:{
			return BTI_RGB_565;
		}break;
		case 0x05:{
			return BTI_RGB5A3;
		}break;
		case 0x06:{
			return BTI_RGBA32;
		}break;
		case 0x08:{
			return BTI_CI4;
		}break;
		case 0x09:{
			return BTI_CI8;
		}break;
		case 0x0A:{
			return BTI_C14X2;
		}break;
		case 0x0E:{
			return BTI_CMPR;
		}break;
	}
}

BTI_ICP_FMT AGIDL_BTIGetICPFmt(u8 type){
	switch(type){
		case 0x00:{
			return BTI_ICP_IA8;
		}break;
		case 0x01:{
			return BTI_ICP_565;
		}break;
		case 0x02:{
			return BTI_ICP_5A3;
		}break;
		default: return 0x04; break;
	}
}

void AGIDL_BTIDecodeHeader(AGIDL_BTI* bti, FILE* file){
	u8 fmt1;
	u16 fmt2;
	fread(&fmt1,1,1,file);
	fread(&bti->header.alpha,2,1,file);
	fread(&bti->header.width,2,1,file);
	fread(&bti->header.height,2,1,file);
	fread(&bti->header.wraps,1,1,file);
	fread(&bti->header.wrapt,1,1,file);
	fread(&fmt2,2,1,file);
	fread(&bti->header.num_of_icps,2,1,file);
	fread(&bti->header.offset_icp,4,1,file);
	fread(&bti->header.blank,3,1,file);
	fread(&bti->header.filter_type,1,1,file);
	fread(&bti->header.filter_type2,1,1,file);
	fread(&bti->header.blank2,2,1,file);
	fread(&bti->header.mipmapcount,1,1,file);
	fread(&bti->header.blank3,4,1,file);
	fread(&bti->header.blank4,2,1,file);
	fread(&bti->header.offset,1,1,file);
	
	bti->header.fmt = AGIDL_GetBTIClrFmt(fmt1);
	bti->header.icp_fmt = AGIDL_BTIGetICPFmt(fmt2);
}

void AGIDL_BTIDecodeIMG(AGIDL_BTI* bti, FILE* file){
	if(bti->header.num_of_icps == 0){
		switch(bti->header.fmt){
			case BTI_RGB5A3:{
				AGIDL_BTISetClrFmt(bti,AGIDL_RGBA_8888);
				bti->pixels.pix32 = (COLOR*)malloc(sizeof(COLOR)*AGIDL_BTIGetSize(bti));

				int x,y;
				for(y = 0; y < AGIDL_BTIGetHeight(bti); y += 4){
					for(x = 0; x < AGIDL_BTIGetWidth(bti); x += 4){
					
						u8 i,j;
						for(j = 0; j < 4; j++){
							for(i = 0; i < 4; i++){
								u8 byte1 = 0,byte2 = 0;
								fread(&byte1,1,1,file);
								fread(&byte2,1,1,file);
								
								u8 r = 0, g = 0, b = 0;
								
								if(((byte1 >> 7) & 0x1) == 0){
									//r = (byte1 & 0xf);
									//g = (byte2 >> 4) & 0xf;
									//b = (byte2 & 0xf);
									u8 a = ((byte1 >> 4) & 0x0C) << 4;
									
									COLOR clr = AGIDL_RGBA(155,155,155,a,AGIDL_RGBA_8888);							
									AGIDL_BTISetClr(bti,x+i,y+j,clr);
								}
								else{
									COLOR16 clr16 = byte1 << 8 | byte2;
									COLOR clr = AGIDL_CLR16_TO_CLR(clr16,AGIDL_RGB_555,AGIDL_RGBA_8888);
									clr = AGIDL_SetA(clr,0xff,bti->fmt);
									AGIDL_BTISetClr(bti,x+i,y+j,clr);
								}
							}
						}
					}
				}
			}break;
			case BTI_RGB_565:{
				AGIDL_BTISetClrFmt(bti,AGIDL_RGB_565);
				bti->pixels.pix16 = (COLOR16*)malloc(sizeof(COLOR16)*AGIDL_BTIGetSize(bti));

				int x,y;
				for(y = 0; y < AGIDL_BTIGetHeight(bti); y += 4){
					for(x = 0; x < AGIDL_BTIGetWidth(bti); x += 4){
					
						u8 i,j;
						for(j = 0; j < 4; j++){
							for(i = 0; i < 4; i++){
								u8 byte1,byte2;
								fread(&byte1,1,1,file);
								fread(&byte2,1,1,file);
								COLOR16 clr = byte1 << 8 | byte2;
								AGIDL_BTISetClr16(bti,x+i,y+j,clr);
							}
						}
					}
				}
			}break;
			case BTI_RGBA32:{
				AGIDL_BTISetClrFmt(bti,AGIDL_RGBA_8888);
				bti->pixels.pix32 = (COLOR*)malloc(sizeof(COLOR)*AGIDL_BTIGetSize(bti));

				int x,y;
				for(y = 0; y < AGIDL_BTIGetHeight(bti); y += 4){
					for(x = 0; x < AGIDL_BTIGetWidth(bti); x += 4){
						u8 byte1,byte2,byte3,byte4,byte5,byte6,byte7,byte8,
						byte9,byte10,byte11,byte12,byte13,byte14,byte15,byte16;
						
						fread(&byte1,1,1,file);fread(&byte2,1,1,file);fread(&byte3,1,1,file);
						fread(&byte4,1,1,file);fread(&byte5,1,1,file);fread(&byte6,1,1,file);
						fread(&byte7,1,1,file);fread(&byte8,1,1,file);fread(&byte9,1,1,file);
						fread(&byte10,1,1,file);fread(&byte11,1,1,file);fread(&byte12,1,1,file);
						fread(&byte13,1,1,file);fread(&byte14,1,1,file);fread(&byte15,1,1,file);
						fread(&byte16,1,1,file);
						
						u8 a1 = byte1, a2 = byte3, a3 = byte5, a4 = byte7;
						u8 r1 = byte2, r2 = byte4, r3 = byte6, r4 = byte8;
						u8 aa1 = byte9, aa2 = byte11, aa3 = byte13, aa4 = byte15;
						u8 rr1 = byte10, rr2 = byte12, rr3 = byte14, rr4 = byte16;
											
						fread(&byte1,1,1,file);fread(&byte2,1,1,file);fread(&byte3,1,1,file);
						fread(&byte4,1,1,file);fread(&byte5,1,1,file);fread(&byte6,1,1,file);
						fread(&byte7,1,1,file);fread(&byte8,1,1,file);fread(&byte9,1,1,file);
						fread(&byte10,1,1,file);fread(&byte11,1,1,file);fread(&byte12,1,1,file);
						fread(&byte13,1,1,file);fread(&byte14,1,1,file);fread(&byte15,1,1,file);
						fread(&byte16,1,1,file);
						
						u8 aaa1 = byte1, aaa2 = byte3, aaa3 = byte5, aaa4 = byte7;
						u8 rrr1 = byte2, rrr2 = byte4, rrr3 = byte6, rrr4 = byte8;
						u8 aaaa1 = byte9, aaaa2 = byte11, aaaa3 = byte13, aaaa4 = byte15;
						u8 rrrr1 = byte10, rrrr2 = byte12, rrrr3 = byte14, rrrr4 = byte16;
						
						fread(&byte1,1,1,file);fread(&byte2,1,1,file);fread(&byte3,1,1,file);
						fread(&byte4,1,1,file);fread(&byte5,1,1,file);fread(&byte6,1,1,file);
						fread(&byte7,1,1,file);fread(&byte8,1,1,file);fread(&byte9,1,1,file);
						fread(&byte10,1,1,file);fread(&byte11,1,1,file);fread(&byte12,1,1,file);
						fread(&byte13,1,1,file);fread(&byte14,1,1,file);fread(&byte15,1,1,file);
						fread(&byte16,1,1,file);
						
						u8 g1 = byte1, g2 = byte3, g3 = byte5, g4 = byte7;
						u8 b1 = byte2, b2 = byte4, b3 = byte6, b4 = byte8;
						u8 gg1 = byte9, gg2 = byte11, gg3 = byte13, gg4 = byte15;
						u8 bb1 = byte10, bb2 = byte12, bb3 = byte14, bb4 = byte16;
						
						fread(&byte1,1,1,file);fread(&byte2,1,1,file);fread(&byte3,1,1,file);
						fread(&byte4,1,1,file);fread(&byte5,1,1,file);fread(&byte6,1,1,file);
						fread(&byte7,1,1,file);fread(&byte8,1,1,file);fread(&byte9,1,1,file);
						fread(&byte10,1,1,file);fread(&byte11,1,1,file);fread(&byte12,1,1,file);
						fread(&byte13,1,1,file);fread(&byte14,1,1,file);fread(&byte15,1,1,file);
						fread(&byte16,1,1,file);
						
						u8 ggg1 = byte1, ggg2 = byte3, ggg3 = byte5, ggg4 = byte7;
						u8 bbb1 = byte2, bbb2 = byte4, bbb3 = byte6, bbb4 = byte8;
						u8 gggg1 = byte9, gggg2 = byte11, gggg3 = byte13, gggg4 = byte15;
						u8 bbbb1 = byte10, bbbb2 = byte12, bbbb3 = byte14, bbbb4 = byte16;
						
						COLOR clr1 = AGIDL_RGBA(r1,g1,b1,a2,bti->fmt);
						COLOR clr2 = AGIDL_RGBA(r2,g2,b2,a2,bti->fmt);
						COLOR clr3 = AGIDL_RGBA(r3,g3,b3,a3,bti->fmt);
						COLOR clr4 = AGIDL_RGBA(r4,g4,b4,a4,bti->fmt);
						
						COLOR clr5 = AGIDL_RGBA(rr1,gg1,bb1,aa2,bti->fmt);
						COLOR clr6 = AGIDL_RGBA(rr2,gg2,bb2,aa2,bti->fmt);
						COLOR clr7 = AGIDL_RGBA(rr3,gg3,bb3,aa3,bti->fmt);
						COLOR clr8 = AGIDL_RGBA(rr4,gg4,bb4,aa4,bti->fmt);
						
						COLOR clr9 = AGIDL_RGBA(rrr1,ggg1,bbb1,aaa2,bti->fmt);
						COLOR clr10 = AGIDL_RGBA(rrr2,ggg2,bbb2,aaa2,bti->fmt);
						COLOR clr11 = AGIDL_RGBA(rrr3,ggg3,bbb3,aaa3,bti->fmt);
						COLOR clr12 = AGIDL_RGBA(rrr4,ggg4,bbb4,aaa4,bti->fmt);
						
						COLOR clr13 = AGIDL_RGBA(rrrr1,gggg1,bbbb1,aaaa2,bti->fmt);
						COLOR clr14 = AGIDL_RGBA(rrrr2,gggg2,bbbb2,aaaa2,bti->fmt);
						COLOR clr15 = AGIDL_RGBA(rrrr3,gggg3,bbbb3,aaaa3,bti->fmt);
						COLOR clr16 = AGIDL_RGBA(rrrr4,gggg4,bbbb4,aaaa4,bti->fmt);
						
						AGIDL_BTISetClr(bti,0+x,0+y,clr1);AGIDL_BTISetClr(bti,1+x,0+y,clr2);
						AGIDL_BTISetClr(bti,2+x,0+y,clr3);AGIDL_BTISetClr(bti,3+x,0+y,clr4);
						
						AGIDL_BTISetClr(bti,0+x,1+y,clr5);AGIDL_BTISetClr(bti,1+x,1+y,clr6);
						AGIDL_BTISetClr(bti,2+x,1+y,clr7);AGIDL_BTISetClr(bti,3+x,1+y,clr8);
						
						AGIDL_BTISetClr(bti,0+x,2+y,clr9);AGIDL_BTISetClr(bti,1+x,2+y,clr10);
						AGIDL_BTISetClr(bti,2+x,2+y,clr11);AGIDL_BTISetClr(bti,3+x,2+y,clr12);
						
						AGIDL_BTISetClr(bti,0+x,3+y,clr13);AGIDL_BTISetClr(bti,1+x,3+y,clr14);
						AGIDL_BTISetClr(bti,2+x,3+y,clr15);AGIDL_BTISetClr(bti,3+x,3+y,clr16);
					}
				}
			}break;
			case BTI_I4:{
				AGIDL_BTISetClrFmt(bti,AGIDL_RGB_888);
				bti->pixels.pix32 = (COLOR*)malloc(sizeof(COLOR)*AGIDL_BTIGetSize(bti));
				
				int x,y;
				for(y = 0; y < AGIDL_BTIGetHeight(bti); y += 8){
					for(x = 0; x < AGIDL_BTIGetWidth(bti); x += 8){
						u8 i,j;
						for(j = 0; j < 8; j++){
							for(i = 0; i < 8; i+=2){
								u8 byte;
								fread(&byte,1,1,file);
								
								u8 rgb1 = ((byte >> 4) & 0xf) * 0x11, rgb2 = (byte & 0xf) * 0x11;
								
								AGIDL_BTISetClr(bti,x+i,y+j,AGIDL_RGB(rgb1,rgb1,rgb1,AGIDL_BTIGetClrFmt(bti)));
								AGIDL_BTISetClr(bti,(x+i)+1,y+j,AGIDL_RGB(rgb2,rgb2,rgb2,AGIDL_BTIGetClrFmt(bti)));
							}
						}
					}
				}
			}break;
			case BTI_I8:{
				AGIDL_BTISetClrFmt(bti,AGIDL_RGB_888);
				bti->pixels.pix32 = (COLOR*)malloc(sizeof(COLOR)*AGIDL_BTIGetSize(bti));
				
				int x,y;
				for(y = 0; y < AGIDL_BTIGetHeight(bti); y += 4){
					for(x = 0; x < AGIDL_BTIGetWidth(bti); x += 8){
						u8 i,j;
						for(j = 0; j < 4; j++){
							for(i = 0; i < 8; i++){
								u8 byte;
								fread(&byte,1,1,file);
								
								u8 rgb = byte;
								
								AGIDL_BTISetClr(bti,x+i,y+j,AGIDL_RGB(rgb,rgb,rgb,AGIDL_BTIGetClrFmt(bti)));;
							}
						}
					}
				}
			}break;
			case BTI_IA4:{
				AGIDL_BTISetClrFmt(bti,AGIDL_RGBA_8888);
				bti->pixels.pix32 = (COLOR*)malloc(sizeof(COLOR)*AGIDL_BTIGetSize(bti));
				
				int x,y;
				for(y = 0; y < AGIDL_BTIGetHeight(bti); y += 4){
					for(x = 0; x < AGIDL_BTIGetWidth(bti); x += 8){
						u8 i,j;
						for(j = 0; j < 4; j++){
							for(i = 0; i < 8; i++){
								u8 byte;
								fread(&byte,1,1,file);
								
								u8 alpha = ((byte >> 4) & 0xf) * 0x11;
								u8 rgb = (byte & 0xf) * 0x11;
								
								AGIDL_BTISetClr(bti,x+i,y+j,AGIDL_RGBA(rgb,rgb,rgb,alpha,AGIDL_BTIGetClrFmt(bti)));;
							}
						}
					}
				}
			}break;
			case BTI_IA8:{
				AGIDL_BTISetClrFmt(bti,AGIDL_RGBA_8888);
				bti->pixels.pix32 = (COLOR*)malloc(sizeof(COLOR)*AGIDL_BTIGetSize(bti));
				
				int x,y;
				for(y = 0; y < AGIDL_BTIGetHeight(bti); y += 4){
					for(x = 0; x < AGIDL_BTIGetWidth(bti); x += 4){
						u8 i,j;
						for(j = 0; j < 4; j++){
							for(i = 0; i < 4; i++){
								u8 byte1,byte2;
								fread(&byte1,1,1,file);
								fread(&byte2,1,1,file);
								
								u8 alpha = byte1;
								u8 rgb = byte2;
								
								AGIDL_BTISetClr(bti,x+i,y+j,AGIDL_RGBA(rgb,rgb,rgb,alpha,AGIDL_BTIGetClrFmt(bti)));;
							}
						}
					}
				}
			}break;
		}
	}
	else{
		if(bti->header.fmt == BTI_CI8 && bti->header.icp_fmt == BTI_ICP_5A3){
			AGIDL_BTISetClrFmt(bti,AGIDL_RGBA_8888);
			bti->pixels.pix32 = (COLOR*)malloc(sizeof(COLOR)*AGIDL_BTIGetSize(bti));
			
			u32 offset = bti->header.offset_icp;
			
			u8 msb = (offset & 0xff00) >> 8;
			u8 lsb = (offset & 0xff0000) >> 16;
			
			offset = msb << 8 | lsb;
			
			u32 pos = ftell(file);
			fseek(file,offset,SEEK_SET);

			AGIDL_InitICP(&bti->palette,AGIDL_ICP_256);
			
			int i;
			for(i = 0; i < bti->header.num_of_icps; i++){
				u8 byte1 = 0,byte2 = 0;
				fread(&byte1,1,1,file);
				fread(&byte2,1,1,file);
				
				u8 r = 0, g = 0, b = 0;
				
				if(((byte1 >> 7) & 0x1) == 0){
					//r = (byte1 & 0xf);
					//g = (byte2 >> 4) & 0xf;
					//b = (byte2 & 0xf);
					u8 a = ((byte1 >> 4) & 0x0C) << 4;
					
					COLOR clr = AGIDL_RGBA(155,155,155,a,AGIDL_RGBA_8888);	

					bti->palette.icp.palette_256[i] = clr;
				}
				else{
					COLOR16 clr16 = byte1 << 8 | byte2;
					COLOR clr = AGIDL_CLR16_TO_CLR(clr16,AGIDL_RGB_555,AGIDL_RGBA_8888);
					clr = AGIDL_SetA(clr,0xff,bti->fmt);
					bti->palette.icp.palette_256[i] = clr;
				}
			}
			
			fseek(file,pos,SEEK_SET);
			
			int x,y;
			for(y = 0; y < AGIDL_BTIGetHeight(bti); y += 4){
				for(x = 0; x < AGIDL_BTIGetWidth(bti); x += 8){
					u8 i,j;
					for(j = 0; j < 4; j++){
						for(i = 0; i < 8; i++){
							u8 byte;
							fread(&byte,1,1,file);
														
							COLOR clr = bti->palette.icp.palette_256[byte];
							
							AGIDL_BTISetClr(bti,x+i,y+j,clr);
						}
					}
				}
			}
			
		}
		else if(bti->header.fmt == BTI_CI8 && bti->header.icp_fmt == BTI_ICP_565){
			AGIDL_BTISetClrFmt(bti,AGIDL_RGB_565);
			bti->pixels.pix16 = (COLOR16*)malloc(sizeof(COLOR16)*AGIDL_BTIGetSize(bti));
			
			u32 offset = bti->header.offset_icp;
			
			u8 msb = (offset & 0xff00) >> 8;
			u8 lsb = (offset & 0xff0000) >> 16;
			
			offset = msb << 8 | lsb;
			
			u32 pos = ftell(file);
			fseek(file,offset,SEEK_SET);

			AGIDL_InitICP(&bti->palette,AGIDL_ICP_16b_256);
			
			int i;
			for(i = 0; i < bti->header.num_of_icps; i++){
				u8 byte1 = 0,byte2 = 0;
				fread(&byte1,1,1,file);
				fread(&byte2,1,1,file);
				COLOR16 clr = byte1 << 8 | byte2;
				bti->palette.icp.palette_16b_256[i] = clr;
			}
			
			fseek(file,pos,SEEK_SET);
			
			int x,y;
			for(y = 0; y < AGIDL_BTIGetHeight(bti); y += 4){
				for(x = 0; x < AGIDL_BTIGetWidth(bti); x += 8){
					u8 i,j;
					for(j = 0; j < 4; j++){
						for(i = 0; i < 8; i++){
							u8 byte;
							fread(&byte,1,1,file);
														
							COLOR16 clr = bti->palette.icp.palette_16b_256[byte];
							
							AGIDL_BTISetClr16(bti,x+i,y+j,clr);
						}
					}
				}
			}
		}
	}
}

AGIDL_BTI* AGIDL_LoadBTI(char* filename){
	FILE* file = fopen(filename,"rb");
	
	if(file == NULL){
		printf("Could not open/locate Nintendo Gamecube BTI image - %s!\n",filename);
	}
	
	AGIDL_BTI* bti = (AGIDL_BTI*)malloc(sizeof(AGIDL_BTI));
	bti->filename = (char*)malloc(strlen(filename)+1);
	AGIDL_FilenameCpy(bti->filename,filename);
	
	AGIDL_BTIDecodeHeader(bti,file);
	AGIDL_BTIDecodeIMG(bti,file);
	
	fclose(file);
	
	return bti;
}

void AGIDL_BTIEncodeHeader(AGIDL_BTI* bti, FILE* file){
	if(bti->icp != 1){
		if(AGIDL_GetBitCount(AGIDL_BTIGetClrFmt(bti)) == 24 || AGIDL_GetBitCount(AGIDL_BTIGetClrFmt(bti)) == 16){
			u8 fmt = BTI_RGB_565, zero = 0, mipmap = 1, offsetdata = 0x20;
			u16 zero16 = 0;
	
			u16 alpha = 0, zero2 = 16;
			u32 offset = 0, blank = 0;
			fwrite(&fmt,1,1,file);
			fwrite(&alpha,2,1,file);
			fwrite(&bti->header.width,2,1,file);
			fwrite(&bti->header.height,2,1,file);
			fwrite(&zero,1,1,file);
			fwrite(&zero,1,1,file);
			fwrite(&zero16,2,1,file);
			fwrite(&zero16,2,1,file);
			fwrite(&offset,4,1,file);
			fwrite(&blank,3,1,file);
			fwrite(&zero,1,1,file);
			fwrite(&zero,1,1,file);
			fwrite(&alpha,2,1,file);
			fwrite(&mipmap,1,1,file);
			fwrite(&alpha,2,1,file);
			fwrite(&blank,4,1,file);
			fwrite(&offsetdata,1,1,file);
		}
		else if(AGIDL_GetBitCount(AGIDL_BTIGetClrFmt(bti)) == 32){
			u8 fmt = BTI_RGBA32, zero = 0, mipmap = 1, offsetdata = 0x20;
			u16 zero16 = 0;
	
			u16 alpha = 0, zero2 = 16;
			u32 offset = 0, blank = 0;
			fwrite(&fmt,1,1,file);
			fwrite(&alpha,2,1,file);
			fwrite(&bti->header.width,2,1,file);
			fwrite(&bti->header.height,2,1,file);
			fwrite(&zero,1,1,file);
			fwrite(&zero,1,1,file);
			fwrite(&zero16,2,1,file);
			fwrite(&zero16,2,1,file);
			fwrite(&offset,4,1,file);
			fwrite(&blank,3,1,file);
			fwrite(&zero,1,1,file);
			fwrite(&zero,1,1,file);
			fwrite(&alpha,2,1,file);
			fwrite(&mipmap,1,1,file);
			fwrite(&alpha,2,1,file);
			fwrite(&blank,4,1,file);
			fwrite(&offsetdata,1,1,file);
		}
	}
	else{
			u8 fmt = BTI_CI8, zero = 0, mipmap = 1, offsetdata = 0x20;
			u16 zero16 = 256, fmt2 = BTI_ICP_565;
	
			u16 alpha = 0, zero2 = 16;
			u32 offset = 33 + AGIDL_BTIGetSize(bti), blank = 0;
			
			fwrite(&fmt,1,1,file);
			fwrite(&alpha,2,1,file);
			fwrite(&bti->header.width,2,1,file);
			fwrite(&bti->header.height,2,1,file);
			fwrite(&zero,1,1,file);
			fwrite(&zero,1,1,file);
			fwrite(&fmt2,2,1,file);
			fwrite(&zero16,2,1,file);
			fwrite(&offset,4,1,file);
			fwrite(&blank,3,1,file);
			fwrite(&zero,1,1,file);
			fwrite(&zero,1,1,file);
			fwrite(&alpha,2,1,file);
			fwrite(&mipmap,1,1,file);
			fwrite(&alpha,2,1,file);
			fwrite(&blank,4,1,file);
			fwrite(&offsetdata,1,1,file);
	}
}

void AGIDL_BTIEncodeICP(AGIDL_BTI* bti){
	if(AGIDL_GetBitCount(AGIDL_BTIGetClrFmt(bti)) == 16){
		AGIDL_InitICP(&bti->palette,AGIDL_ICP_16b_256);
	
		int pass = 0;
		u8 pal_index = 0;
		
		int x,y;
		for(y = 0; y < AGIDL_BTIGetHeight(bti); y++){
			for(x = 0; x < AGIDL_BTIGetWidth(bti); x++){
				COLOR16 clr = AGIDL_BTIGetClr16(bti,x,y);
				
				AGIDL_AddColorICP16(&bti->palette,pal_index,clr,AGIDL_BTIGetClrFmt(bti),AGIDL_BTIGetMaxDiff(bti),&pass);
				
				if(pass == 1 && pal_index < 256){
					pal_index++;
				}
				
				pass = 0;
			}
		}
	}
}

void AGIDL_BTIEncodeIMG(AGIDL_BTI* bti, FILE* file){
	if(bti->icp != 1){
		if(AGIDL_GetBitCount(AGIDL_BTIGetClrFmt(bti)) == 16){
			int x,y;
			for(y = 0; y < AGIDL_BTIGetHeight(bti); y += 4){
				for(x = 0; x < AGIDL_BTIGetWidth(bti); x += 4){
					u8 i,j;
					for(j = 0; j < 4; j++){
						for(i = 0; i < 4; i++){
							COLOR16 clr = AGIDL_BTIGetClr16(bti,x+i,y+j);
							u8 msb = (clr & 0xff);
							u8 lsb = (clr & 0xff00) >> 8; 
							fwrite(&lsb,1,1,file);
							fwrite(&msb,1,1,file);
						}
					}
				}
			}
		}
		else{
			int x,y;
			for(y = 0; y < AGIDL_BTIGetHeight(bti); y += 4){
				for(x = 0; x < AGIDL_BTIGetWidth(bti); x += 4){
					COLOR clr1 = AGIDL_BTIGetClr(bti,x+0,y+0);
					COLOR clr2 = AGIDL_BTIGetClr(bti,x+1,y+0);
					COLOR clr3 = AGIDL_BTIGetClr(bti,x+2,y+0);
					COLOR clr4 = AGIDL_BTIGetClr(bti,x+3,y+0);
					COLOR clr5 = AGIDL_BTIGetClr(bti,x+0,y+1);
					COLOR clr6 = AGIDL_BTIGetClr(bti,x+1,y+1);
					COLOR clr7 = AGIDL_BTIGetClr(bti,x+2,y+1);
					COLOR clr8 = AGIDL_BTIGetClr(bti,x+3,y+1);
					COLOR clr9 = AGIDL_BTIGetClr(bti,x+0,y+2);
					COLOR clr10 = AGIDL_BTIGetClr(bti,x+1,y+2);
					COLOR clr11 = AGIDL_BTIGetClr(bti,x+2,y+2);
					COLOR clr12 = AGIDL_BTIGetClr(bti,x+3,y+2);
					COLOR clr13 = AGIDL_BTIGetClr(bti,x+0,y+3);
					COLOR clr14 = AGIDL_BTIGetClr(bti,x+1,y+3);
					COLOR clr15 = AGIDL_BTIGetClr(bti,x+2,y+3);
					COLOR clr16 = AGIDL_BTIGetClr(bti,x+3,y+3);
					
					u8 a1 = AGIDL_GetA(clr1,AGIDL_BTIGetClrFmt(bti));
					u8 a2 = AGIDL_GetA(clr2,AGIDL_BTIGetClrFmt(bti));
					u8 a3 = AGIDL_GetA(clr3,AGIDL_BTIGetClrFmt(bti));
					u8 a4 = AGIDL_GetA(clr4,AGIDL_BTIGetClrFmt(bti));
					
					u8 r1 = AGIDL_GetR(clr1,AGIDL_BTIGetClrFmt(bti));
					u8 r2 = AGIDL_GetR(clr2,AGIDL_BTIGetClrFmt(bti));
					u8 r3 = AGIDL_GetR(clr3,AGIDL_BTIGetClrFmt(bti));
					u8 r4 = AGIDL_GetR(clr4,AGIDL_BTIGetClrFmt(bti));
					
					fwrite(&a1,1,1,file);
					fwrite(&r1,1,1,file);
					fwrite(&a2,1,1,file);
					fwrite(&r1,1,1,file);
					fwrite(&a3,1,1,file);
					fwrite(&r3,1,1,file);
					fwrite(&a4,1,1,file);
					fwrite(&r4,1,1,file);
					
					a1 = AGIDL_GetA(clr5,AGIDL_BTIGetClrFmt(bti));
					a2 = AGIDL_GetA(clr6,AGIDL_BTIGetClrFmt(bti));
					a3 = AGIDL_GetA(clr7,AGIDL_BTIGetClrFmt(bti));
					a4 = AGIDL_GetA(clr8,AGIDL_BTIGetClrFmt(bti));
					
					r1 = AGIDL_GetR(clr5,AGIDL_BTIGetClrFmt(bti));
					r2 = AGIDL_GetR(clr6,AGIDL_BTIGetClrFmt(bti));
					r3 = AGIDL_GetR(clr7,AGIDL_BTIGetClrFmt(bti));
					r4 = AGIDL_GetR(clr8,AGIDL_BTIGetClrFmt(bti));
					
					fwrite(&a1,1,1,file);
					fwrite(&r1,1,1,file);
					fwrite(&a2,1,1,file);
					fwrite(&r1,1,1,file);
					fwrite(&a3,1,1,file);
					fwrite(&r3,1,1,file);
					fwrite(&a4,1,1,file);
					fwrite(&r4,1,1,file);
					
					a1 = AGIDL_GetA(clr9,AGIDL_BTIGetClrFmt(bti));
					a2 = AGIDL_GetA(clr10,AGIDL_BTIGetClrFmt(bti));
					a3 = AGIDL_GetA(clr11,AGIDL_BTIGetClrFmt(bti));
					a4 = AGIDL_GetA(clr12,AGIDL_BTIGetClrFmt(bti));
					
					r1 = AGIDL_GetR(clr9,AGIDL_BTIGetClrFmt(bti));
					r2 = AGIDL_GetR(clr10,AGIDL_BTIGetClrFmt(bti));
					r3 = AGIDL_GetR(clr11,AGIDL_BTIGetClrFmt(bti));
					r4 = AGIDL_GetR(clr12,AGIDL_BTIGetClrFmt(bti));
					
					fwrite(&a1,1,1,file);
					fwrite(&r1,1,1,file);
					fwrite(&a2,1,1,file);
					fwrite(&r1,1,1,file);
					fwrite(&a3,1,1,file);
					fwrite(&r3,1,1,file);
					fwrite(&a4,1,1,file);
					fwrite(&r4,1,1,file);
					
					a1 = AGIDL_GetA(clr13,AGIDL_BTIGetClrFmt(bti));
					a2 = AGIDL_GetA(clr14,AGIDL_BTIGetClrFmt(bti));
					a3 = AGIDL_GetA(clr15,AGIDL_BTIGetClrFmt(bti));
					a4 = AGIDL_GetA(clr16,AGIDL_BTIGetClrFmt(bti));
					
					r1 = AGIDL_GetR(clr13,AGIDL_BTIGetClrFmt(bti));
					r2 = AGIDL_GetR(clr14,AGIDL_BTIGetClrFmt(bti));
					r3 = AGIDL_GetR(clr15,AGIDL_BTIGetClrFmt(bti));
					r4 = AGIDL_GetR(clr16,AGIDL_BTIGetClrFmt(bti));
					
					fwrite(&a1,1,1,file);
					fwrite(&r1,1,1,file);
					fwrite(&a2,1,1,file);
					fwrite(&r1,1,1,file);
					fwrite(&a3,1,1,file);
					fwrite(&r3,1,1,file);
					fwrite(&a4,1,1,file);
					fwrite(&r4,1,1,file);
					
					u8 g1 = AGIDL_GetG(clr1,AGIDL_BTIGetClrFmt(bti));
					u8 g2 = AGIDL_GetG(clr2,AGIDL_BTIGetClrFmt(bti));
					u8 g3 = AGIDL_GetG(clr3,AGIDL_BTIGetClrFmt(bti));
					u8 g4 = AGIDL_GetG(clr4,AGIDL_BTIGetClrFmt(bti));
					
					u8 b1 = AGIDL_GetB(clr1,AGIDL_BTIGetClrFmt(bti));
					u8 b2 = AGIDL_GetB(clr2,AGIDL_BTIGetClrFmt(bti));
					u8 b3 = AGIDL_GetB(clr3,AGIDL_BTIGetClrFmt(bti));
					u8 b4 = AGIDL_GetB(clr4,AGIDL_BTIGetClrFmt(bti));
					
					fwrite(&g1,1,1,file);
					fwrite(&b1,1,1,file);
					fwrite(&g2,1,1,file);
					fwrite(&b1,1,1,file);
					fwrite(&g3,1,1,file);
					fwrite(&b3,1,1,file);
					fwrite(&g4,1,1,file);
					fwrite(&b4,1,1,file);
					
					g1 = AGIDL_GetG(clr5,AGIDL_BTIGetClrFmt(bti));
					g2 = AGIDL_GetG(clr6,AGIDL_BTIGetClrFmt(bti));
					g3 = AGIDL_GetG(clr7,AGIDL_BTIGetClrFmt(bti));
					g4 = AGIDL_GetG(clr8,AGIDL_BTIGetClrFmt(bti));
					
					b1 = AGIDL_GetB(clr5,AGIDL_BTIGetClrFmt(bti));
					b2 = AGIDL_GetB(clr6,AGIDL_BTIGetClrFmt(bti));
					b3 = AGIDL_GetB(clr7,AGIDL_BTIGetClrFmt(bti));
					b4 = AGIDL_GetB(clr8,AGIDL_BTIGetClrFmt(bti));
					
					fwrite(&g1,1,1,file);
					fwrite(&b1,1,1,file);
					fwrite(&g2,1,1,file);
					fwrite(&b1,1,1,file);
					fwrite(&g3,1,1,file);
					fwrite(&b3,1,1,file);
					fwrite(&g4,1,1,file);
					fwrite(&b4,1,1,file);
					
					g1 = AGIDL_GetG(clr9,AGIDL_BTIGetClrFmt(bti));
					g2 = AGIDL_GetG(clr10,AGIDL_BTIGetClrFmt(bti));
					g3 = AGIDL_GetG(clr11,AGIDL_BTIGetClrFmt(bti));
					g4 = AGIDL_GetG(clr12,AGIDL_BTIGetClrFmt(bti));
					
					b1 = AGIDL_GetB(clr9,AGIDL_BTIGetClrFmt(bti));
					b2 = AGIDL_GetB(clr10,AGIDL_BTIGetClrFmt(bti));
					b3 = AGIDL_GetB(clr11,AGIDL_BTIGetClrFmt(bti));
					b4 = AGIDL_GetB(clr12,AGIDL_BTIGetClrFmt(bti));
					
					fwrite(&g1,1,1,file);
					fwrite(&b1,1,1,file);
					fwrite(&g2,1,1,file);
					fwrite(&b1,1,1,file);
					fwrite(&g3,1,1,file);
					fwrite(&b3,1,1,file);
					fwrite(&g4,1,1,file);
					fwrite(&b4,1,1,file);
					
					g1 = AGIDL_GetG(clr13,AGIDL_BTIGetClrFmt(bti));
					g2 = AGIDL_GetG(clr14,AGIDL_BTIGetClrFmt(bti));
					g3 = AGIDL_GetG(clr15,AGIDL_BTIGetClrFmt(bti));
					g4 = AGIDL_GetG(clr16,AGIDL_BTIGetClrFmt(bti));
					
					b1 = AGIDL_GetB(clr13,AGIDL_BTIGetClrFmt(bti));
					b2 = AGIDL_GetB(clr14,AGIDL_BTIGetClrFmt(bti));
					b3 = AGIDL_GetB(clr15,AGIDL_BTIGetClrFmt(bti));
					b4 = AGIDL_GetB(clr16,AGIDL_BTIGetClrFmt(bti));
					
					fwrite(&g1,1,1,file);
					fwrite(&b1,1,1,file);
					fwrite(&g2,1,1,file);
					fwrite(&b1,1,1,file);
					fwrite(&g3,1,1,file);
					fwrite(&b3,1,1,file);
					fwrite(&g4,1,1,file);
					fwrite(&b4,1,1,file);
				}
			}
		}
	}
	else{
		int x,y;
		for(y = 0; y < AGIDL_BTIGetHeight(bti); y += 4){
			for(x = 0; x < AGIDL_BTIGetWidth(bti); x += 8){
				u8 i,j;
				for(j = 0; j < 4; j++){
					for(i = 0; i < 8; i++){
						COLOR16 clr = AGIDL_BTIGetClr16(bti,x+i,y+j);
						u8 index = AGIDL_FindClosestColor(bti->palette,clr,AGIDL_BTIGetClrFmt(bti),AGIDL_BTIGetMaxDiff(bti));
						fwrite(&index,1,1,file);
					}
				}
			}
		}
		
		u32 pos = ftell(file);
		
		fseek(file,13,SEEK_SET);
		
		u8 msb = (pos & 0xff00) >> 8;
		u8 lsb = (pos & 0xff);
		
		u32 offset = lsb << 16 | msb << 8;
		
		if(pos >= 65536){
			u8 msb = (offset & 0xff00) >> 8;
			u8 lsb = (offset & 0xff0000) >> 16;
			offset = lsb << 8 | msb;
		}
		
		fwrite(&offset,4,1,file);
		
		fseek(file,pos,SEEK_SET);
		
		int i;
		for(i = 0; i < 256; i++){
			COLOR16 clr = bti->palette.icp.palette_16b_256[i];
			u8 msb = (clr & 0xff00) >> 8;
			u8 lsb = (clr & 0xff);
			fwrite(&msb,1,1,file);
			fwrite(&lsb,1,1,file);
		}
	}
}

void AGIDL_ExportBTI(AGIDL_BTI* bti){
	FILE* file = fopen(bti->filename,"wb");
	
	if(file == NULL){
		printf("Could not open/create Nintendo Gamecube BTI image - %s!\n",bti->filename);
	}
	
	AGIDL_BTIEncodeHeader(bti,file);
	
	if(bti->icp != 1){
		switch(AGIDL_BTIGetClrFmt(bti)){
			case AGIDL_RGB_888:{
				AGIDL_BTIConvert24BPPTO16BPP(bti);
				AGIDL_BTI555TO565(bti);
				AGIDL_BTIEncodeIMG(bti,file);
				AGIDL_BTI565TO555(bti);
				AGIDL_BTIConvert16BPPTO24BPP(bti);
			}break;
			case AGIDL_BGR_888:{
				AGIDL_BTIBGR2RGB(bti);
				AGIDL_BTIConvert24BPPTO16BPP(bti);
				AGIDL_BTI555TO565(bti);
				AGIDL_BTIEncodeIMG(bti,file);
				AGIDL_BTI565TO555(bti);
				AGIDL_BTIConvert16BPPTO24BPP(bti);
				AGIDL_BTIBGR2RGB(bti);
			}break;
			case AGIDL_RGB_555:{
				AGIDL_BTI555TO565(bti);
				AGIDL_BTIEncodeIMG(bti,file);
				AGIDL_BTI565TO555(bti);
			}break;
			case AGIDL_BGR_555:{
				AGIDL_BTIBGR2RGB(bti);
				AGIDL_BTI555TO565(bti);
				AGIDL_BTIEncodeIMG(bti,file);
				AGIDL_BTI565TO555(bti);
				AGIDL_BTIBGR2RGB(bti);
			}break;
			case AGIDL_RGB_565:{
				AGIDL_BTIEncodeIMG(bti,file);
			}break;
			case AGIDL_BGR_565:{
				AGIDL_BTIBGR2RGB(bti);
				AGIDL_BTIEncodeIMG(bti,file);
				AGIDL_BTIBGR2RGB(bti);
			}break;
			case AGIDL_RGBA_8888:{
				AGIDL_BTIEncodeIMG(bti,file);
			}break;
			case AGIDL_ARGB_8888:{
				AGIDL_BTIEncodeIMG(bti,file);
			}break;
		}
	}
	else{
		switch(AGIDL_BTIGetClrFmt(bti)){
			case AGIDL_RGB_888:{
				AGIDL_BTIConvert24BPPTO16BPP(bti);
				AGIDL_BTI555TO565(bti);
				AGIDL_BTIEncodeICP(bti);
				AGIDL_BTIEncodeIMG(bti,file);
				AGIDL_BTI565TO555(bti);
				AGIDL_BTIConvert16BPPTO24BPP(bti);
			}break;
			case AGIDL_BGR_888:{
				AGIDL_BTIBGR2RGB(bti);
				AGIDL_BTIConvert24BPPTO16BPP(bti);
				AGIDL_BTI555TO565(bti);
				AGIDL_BTIEncodeICP(bti);
				AGIDL_BTIEncodeIMG(bti,file);
				AGIDL_BTI565TO555(bti);
				AGIDL_BTIConvert16BPPTO24BPP(bti);
				AGIDL_BTIBGR2RGB(bti);
			}break;
			case AGIDL_RGB_555:{
				AGIDL_BTI555TO565(bti);
				AGIDL_BTIEncodeICP(bti);
				AGIDL_BTIEncodeIMG(bti,file);
				AGIDL_BTI565TO555(bti);
			}break;
			case AGIDL_BGR_555:{
				AGIDL_BTIBGR2RGB(bti);
				AGIDL_BTI555TO565(bti);
				AGIDL_BTIEncodeICP(bti);
				AGIDL_BTIEncodeIMG(bti,file);
				AGIDL_BTI565TO555(bti);
				AGIDL_BTIBGR2RGB(bti);
			}break;
			case AGIDL_RGB_565:{
				AGIDL_BTIEncodeICP(bti);
				AGIDL_BTIEncodeIMG(bti,file);
			}break;
			case AGIDL_BGR_565:{
				AGIDL_BTIBGR2RGB(bti);
				AGIDL_BTIEncodeICP(bti);
				AGIDL_BTIEncodeIMG(bti,file);
				AGIDL_BTIBGR2RGB(bti);
			}break;
			case AGIDL_RGBA_8888:{
				AGIDL_BTIRGBATORGB(bti);
				AGIDL_BTIConvert24BPPTO16BPP(bti);
				AGIDL_BTI555TO565(bti);
				AGIDL_BTIEncodeICP(bti);
				AGIDL_BTIEncodeIMG(bti,file);
				AGIDL_BTI565TO555(bti);
				AGIDL_BTIConvert16BPPTO24BPP(bti);
			}break;
			case AGIDL_ARGB_8888:{
				AGIDL_BTIRGBATORGB(bti);
				AGIDL_BTIConvert24BPPTO16BPP(bti);
				AGIDL_BTI555TO565(bti);
				AGIDL_BTIEncodeICP(bti);
				AGIDL_BTIEncodeIMG(bti,file);
				AGIDL_BTI565TO555(bti);
				AGIDL_BTIConvert16BPPTO24BPP(bti);
			}break;
		}
	}
}