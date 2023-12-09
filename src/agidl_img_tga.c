#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agidl_img_tga.h"
#include "agidl_cc_core.h"
#include "agidl_img_compression.h"

/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023 Ryandracus Chapman
*
*   Library: libagidl
*   File: agidl_img_tga.c
*   Date: 9/13/2023
*   Version: 0.1b
*   Updated: 11/30/2023
*   Author: Ryandracus Chapman
*
********************************************/

void AGIDL_SetTGAFilename(AGIDL_TGA *tga, const char *filename){
	tga->filename = (char*)realloc(tga->filename,strlen(filename));
	AGIDL_FilenameCpy(tga->filename,filename);
}

void AGIDL_TGASetWidth(AGIDL_TGA *tga, int width){
	tga->header.width = width;
}

void AGIDL_TGASetHeight(AGIDL_TGA *tga, int height){
	tga->header.height = height;
}

void AGIDL_TGASetClrFmt(AGIDL_TGA *tga, AGIDL_CLR_FMT fmt){
	tga->fmt = fmt;
}

void AGIDL_TGASetClr(AGIDL_TGA *tga, int x, int y, COLOR clr){
	AGIDL_SetClr(tga->pixels.pix32,clr,x,y,AGIDL_TGAGetWidth(tga),AGIDL_TGAGetHeight(tga));
}

void AGIDL_TGASetClr16(AGIDL_TGA *tga, int x, int y, COLOR16 clr){
	AGIDL_SetClr16(tga->pixels.pix16,clr,x,y,AGIDL_TGAGetWidth(tga),AGIDL_TGAGetHeight(tga));
}

void AGIDL_TGASetRGB(AGIDL_TGA *tga, int x, int y, u8 r, u8 g, u8 b){
	switch(AGIDL_GetBitCount(AGIDL_TGAGetClrFmt(tga))){
		case 24:{
			AGIDL_TGASetClr(tga,x,y,AGIDL_RGB(r,g,b,AGIDL_TGAGetClrFmt(tga)));
		}break;
		case 16:{
			AGIDL_TGASetClr16(tga,x,y,AGIDL_RGB16(r,g,b,AGIDL_TGAGetClrFmt(tga)));
		}break;
		case 32:{
			AGIDL_TGASetClr(tga,x,y,AGIDL_RGBA(r,g,b,0xff,AGIDL_TGAGetClrFmt(tga)));
		}break;
	}
}

void AGIDL_TGASetICPMode(AGIDL_TGA *tga, int mode){
	tga->icp = mode;
}

void AGIDL_TGASetRGBA(AGIDL_TGA *tga, int x, int y, u8 r, u8 g, u8 b, u8 a){
	switch(tga->fmt){
		case AGIDL_RGBA_8888:{
			AGIDL_TGASetClr(tga,x,y,AGIDL_RGBA(r,g,b,a,AGIDL_RGBA_8888));
		}break;
		case AGIDL_ARGB_8888:{
			AGIDL_TGASetClr(tga,x,y,AGIDL_RGBA(r,g,b,a,AGIDL_ARGB_8888));
		}break;
	}
}

void AGIDL_TGASetMaxDiff(AGIDL_TGA *tga, int max_diff){
	tga->max_diff = max_diff;
}

void AGIDL_TGASetCompression(AGIDL_TGA* tga, int compress){
	tga->compression = compress;
}

void AGIDL_ClearTGA(AGIDL_TGA *tga, COLOR clr){
	AGIDL_ClrMemset(tga->pixels.pix32,clr,AGIDL_TGAGetWidth(tga)*AGIDL_TGAGetHeight(tga));
}

void AGIDL_ClearTGA16(AGIDL_TGA *tga, COLOR16 clr){
	AGIDL_ClrMemset16(tga->pixels.pix16,clr,AGIDL_TGAGetWidth(tga)*AGIDL_TGAGetHeight(tga));
}

int AGIDL_TGAGetWidth(AGIDL_TGA *tga){
	return tga->header.width;
}

int AGIDL_TGAGetHeight(AGIDL_TGA *tga){
	return tga->header.height;
}

u32 AGIDL_TGAGetSize(AGIDL_TGA* tga){
	return AGIDL_TGAGetWidth(tga) * AGIDL_TGAGetHeight(tga);
}

AGIDL_CLR_FMT AGIDL_TGAGetClrFmt(AGIDL_TGA* tga){
	return tga->fmt;
}

COLOR AGIDL_TGAGetClr(AGIDL_TGA *tga, int x, int y){
	if(x >= 0 && y >= 0 && x < AGIDL_TGAGetWidth(tga) && y < AGIDL_TGAGetHeight(tga)){
		return tga->pixels.pix32[x+y*AGIDL_TGAGetWidth(tga)];
	}
}

int AGIDL_TGAGetMaxDiff(AGIDL_TGA* tga){
	return tga->max_diff;
}

COLOR16 AGIDL_TGAGetClr16(AGIDL_TGA *tga, int x, int y){
	if(x >= 0 && y >= 0 && x < AGIDL_TGAGetWidth(tga) && y < AGIDL_TGAGetHeight(tga)){
		return tga->pixels.pix16[x+y*AGIDL_TGAGetWidth(tga)];
	}
}

void AGIDL_TGASyncPix(AGIDL_TGA *tga, COLOR *clrs){
	AGIDL_ClrMemcpy(tga->pixels.pix32,clrs,(AGIDL_TGAGetWidth(tga)*(AGIDL_TGAGetHeight(tga))));
}

void AGIDL_TGASyncPix16(AGIDL_TGA *tga, COLOR16 *clrs){
	AGIDL_ClrMemcpy16(tga->pixels.pix16,clrs,(AGIDL_TGAGetWidth(tga)*(AGIDL_TGAGetHeight(tga))));
}

void AGIDL_FreeTGA(AGIDL_TGA *tga){
	free(tga);
	if(tga != NULL){
		tga = NULL;
	}
}

AGIDL_TGA * AGIDL_CreateTGA(const char* filename, int width, int height, AGIDL_CLR_FMT fmt){
	AGIDL_TGA *tga = (AGIDL_TGA*)malloc(sizeof(AGIDL_TGA));
	tga->filename = (char*)malloc(strlen(filename)+1);
	AGIDL_FilenameCpy(tga->filename,filename);
	AGIDL_TGASetWidth(tga,width);
	AGIDL_TGASetHeight(tga,height);
	AGIDL_TGASetClrFmt(tga,fmt);
	AGIDL_TGASetMaxDiff(tga,7);
	
	if(fmt == AGIDL_RGB_888 || fmt == AGIDL_BGR_888 || fmt == AGIDL_RGBA_8888 || fmt == AGIDL_ARGB_8888){
		tga->pixels.pix32 = (COLOR*)malloc(sizeof(COLOR)*(width*height));
	}
	
	if(fmt == AGIDL_RGB_555 || fmt == AGIDL_BGR_555 || fmt == AGIDL_RGB_565 || fmt == AGIDL_BGR_565){
		tga->pixels.pix16 = (COLOR16*)malloc(sizeof(COLOR16)*(width*height));
	}
	
	return tga;
}

AGIDL_TGA* AGIDL_TGACpyImg(AGIDL_TGA* tga){
	AGIDL_TGA* tgacpy = AGIDL_CreateTGA("tgacpy.tga",AGIDL_TGAGetWidth(tga),AGIDL_TGAGetHeight(tga),tga->fmt);
	AGIDL_TGASetICPMode(tgacpy,tga->icp);
	AGIDL_TGASetCompression(tgacpy,tga->compression);
	AGIDL_TGASetMaxDiff(tgacpy,AGIDL_TGAGetMaxDiff(tga));
	if(tga->fmt == AGIDL_RGB_888 || tga->fmt == AGIDL_BGR_888 || tga->fmt == AGIDL_RGBA_8888 || tga->fmt == AGIDL_ARGB_8888){
		AGIDL_TGASyncPix(tgacpy,tga->pixels.pix32);
	}
	
	if(tga->fmt == AGIDL_RGB_555 || tga->fmt == AGIDL_BGR_555 || tga->fmt == AGIDL_RGB_565 || tga->fmt == AGIDL_BGR_565){
		AGIDL_TGASyncPix16(tgacpy,tga->pixels.pix16);
	}
	return tgacpy;
}

void AGIDL_TGARGB2BGR(AGIDL_TGA *tga){
	if(tga->fmt == AGIDL_RGB_888){
		AGIDL_RGB2BGR(tga->pixels.pix32,AGIDL_TGAGetWidth(tga),AGIDL_TGAGetHeight(tga),&tga->fmt);
	}
	if(tga->fmt == AGIDL_RGB_555){
		AGIDL_RGB2BGR16(tga->pixels.pix16,AGIDL_TGAGetWidth(tga),AGIDL_TGAGetHeight(tga),&tga->fmt);
	}
}

void AGIDL_TGABGR2RGB(AGIDL_TGA *tga){
	if(tga->fmt == AGIDL_BGR_888){
		AGIDL_BGR2RGB(tga->pixels.pix32,AGIDL_TGAGetWidth(tga),AGIDL_TGAGetHeight(tga),&tga->fmt);
	}
	if(tga->fmt == AGIDL_BGR_555){
		AGIDL_BGR2RGB16(tga->pixels.pix16,AGIDL_TGAGetWidth(tga),AGIDL_TGAGetHeight(tga),&tga->fmt);
	}
}

void AGIDL_TGAConvert16BPPTO24BPP(AGIDL_TGA *tga){
	if(tga->fmt == AGIDL_RGB_555 || tga->fmt == AGIDL_BGR_555 || tga->fmt == AGIDL_RGB_565 || tga->fmt == AGIDL_BGR_565){
		tga->pixels.pix32 = (COLOR*)malloc(sizeof(COLOR)*(AGIDL_TGAGetHeight(tga)*AGIDL_TGAGetWidth(tga)));
		AGIDL_16BPPTO24BPP(tga->pixels.pix16,tga->pixels.pix32,AGIDL_TGAGetWidth(tga),AGIDL_TGAGetHeight(tga),&tga->fmt);
		free(tga->pixels.pix16);
	}
}

void AGIDL_TGAConvert24BPPTO16BPP(AGIDL_TGA *tga){
	if(tga->fmt == AGIDL_RGB_888 || tga->fmt == AGIDL_BGR_888 || tga->fmt == AGIDL_RGBA_8888 || tga->fmt == AGIDL_ARGB_8888){
		tga->pixels.pix16 = (COLOR16*)malloc(sizeof(COLOR16)*(AGIDL_TGAGetHeight(tga)*AGIDL_TGAGetWidth(tga)));
		AGIDL_24BPPTO16BPP(tga->pixels.pix32,tga->pixels.pix16,AGIDL_TGAGetWidth(tga),AGIDL_TGAGetHeight(tga),&tga->fmt);
		free(tga->pixels.pix32);
	}
}

void AGIDL_TGAConvert555TO565(AGIDL_TGA* tga){
	AGIDL_555TO565(tga->pixels.pix16,AGIDL_TGAGetWidth(tga),AGIDL_TGAGetHeight(tga),&tga->fmt);
}

void AGIDL_TGAConvert565TO555(AGIDL_TGA* tga){
	AGIDL_565TO555(tga->pixels.pix16,AGIDL_TGAGetWidth(tga),AGIDL_TGAGetHeight(tga),&tga->fmt);
}

TGA_ICP_TYPE AGIDL_TGAGetICPType(int num){
	switch(num){
		case 1:{
			return TGA_IMG_TYPE_ICP;
		}
		case 2:{
			return TGA_IMG_TYPE_NO_ICP;
		}
		case 9:{
			return TGA_IMG_TYPE_RLE_ICP;
		}
		case 10:{
			return TGA_IMG_TYPE_RLE_NO_ICP;
		}
	}
}

TGA_IMG_TYPE AGIDL_TGAGetIMGType(int bits){
	switch(bits){
		case 15:{
			return TGA_IMG_TYPE_HIGH_CLR;
		}
		case 16:{
			return TGA_IMG_TYPE_HIGH_CLR;
		}
		case 24:{
			return TGA_IMG_TYPE_TRUE_CLR;
		}
		case 32:{
			return TGA_IMG_TYPE_DEEP_CLR;
		}
	}
}

void AGIDL_TGADecodeHeader(AGIDL_TGA* tga, FILE* file){
	fread(&tga->header.id,1,1,file);
	fread(&tga->header.clrmaptype,1,1,file);
	fread(&tga->header.imgtype,1,1,file);
	fread(&tga->header.clrmapstart,2,1,file);
	fread(&tga->header.clrmaplength,2,1,file);
	fread(&tga->header.icpbits,1,1,file);
	fread(&tga->header.xstart,2,1,file);
	fread(&tga->header.ystart,2,1,file);
	fread(&tga->header.width,2,1,file);
	fread(&tga->header.height,2,1,file);
	fread(&tga->header.bits,1,1,file);
	fread(&tga->header.flip,1,1,file);
	
	if(tga->header.id != 0){
		fseek(file,tga->header.id,SEEK_CUR);
	}
}

void AGIDL_TGADecodeIMG(AGIDL_TGA *tga, FILE* file, TGA_ICP_TYPE icp, TGA_IMG_TYPE img_type){
	if(icp == TGA_IMG_TYPE_NO_ICP){
		if(img_type == TGA_IMG_TYPE_HIGH_CLR){
			AGIDL_TGASetClrFmt(tga,AGIDL_BGR_555);
			tga->pixels.pix16 = (COLOR16*)malloc(sizeof(COLOR16)*(AGIDL_TGAGetWidth(tga)*AGIDL_TGAGetHeight(tga)));
		}
		else if(img_type == TGA_IMG_TYPE_DEEP_CLR){
			AGIDL_TGASetClrFmt(tga,AGIDL_RGBA_8888);
			tga->pixels.pix32 = (COLOR*)malloc(sizeof(COLOR)*(AGIDL_TGAGetWidth(tga)*AGIDL_TGAGetHeight(tga)));
		}
		else{
			AGIDL_TGASetClrFmt(tga,AGIDL_BGR_888);
			tga->pixels.pix32 = (COLOR*)malloc(sizeof(COLOR)*(AGIDL_TGAGetWidth(tga)*AGIDL_TGAGetHeight(tga)));
		}

		int x,y;
		for(y = 0; y < AGIDL_TGAGetHeight(tga); y++){
			for(x = 0; x < AGIDL_TGAGetWidth(tga); x++){
				switch(img_type){
					case TGA_IMG_TYPE_TRUE_CLR:{
						COLOR clr = 0;
						u8 r,g,b;
						fread(&b,1,1,file);
						fread(&g,1,1,file);
						fread(&r,1,1,file);
						clr = AGIDL_RGB(r,g,b,tga->fmt);
						AGIDL_TGASetClr(tga,x,y,clr);
					}break;
					case TGA_IMG_TYPE_HIGH_CLR:{
						COLOR16 clr = 0;
						fread(&clr,2,1,file);
						u8 r = AGIDL_GetR(clr,tga->fmt);
						u8 g = AGIDL_GetG(clr,tga->fmt);
						u8 b = AGIDL_GetB(clr,tga->fmt);
						clr = AGIDL_RGB16(b,g,r,tga->fmt);
						AGIDL_TGASetClr16(tga,x,y,clr);
					}break;
					case TGA_IMG_TYPE_DEEP_CLR:{
						COLOR clr = 0;
						fread(&clr,4,1,file);
						u8 b = AGIDL_GetR(clr,AGIDL_RGBA_8888);
						u8 g = AGIDL_GetG(clr,AGIDL_RGBA_8888);
						u8 r = AGIDL_GetB(clr,AGIDL_RGBA_8888);
						u8 a = AGIDL_GetA(clr,AGIDL_RGBA_8888);
						clr = AGIDL_RGBA(b,g,r,a,AGIDL_RGBA_8888);
						AGIDL_TGASetClr(tga,x,y,clr);
					}break;
				}
			}
		}
	}
	else if(icp != TGA_IMG_TYPE_RLE_ICP && icp != TGA_IMG_TYPE_RLE_NO_ICP){
		if(img_type == TGA_IMG_TYPE_HIGH_CLR){
			AGIDL_TGASetClrFmt(tga,AGIDL_BGR_555);
				
			tga->pixels.pix16 = (COLOR16*)malloc(sizeof(COLOR16)*(tga->header.width*tga->header.height));
			
			int i;
			for(i = 0; i < tga->header.clrmaplength; i++){
				COLOR16 clr = 0;
				u8 r = AGIDL_GetR(clr,tga->fmt);
				u8 g = AGIDL_GetG(clr,tga->fmt);
				u8 b = AGIDL_GetB(clr,tga->fmt);
				clr = AGIDL_RGB16(b,g,r,tga->fmt);
				tga->palette.icp.palette_16b_256[i] = clr;
			}
			
			int x,y;
			for(y = 0; y < AGIDL_TGAGetHeight(tga); y++){
				for(x = 0; x < AGIDL_TGAGetWidth(tga); x++){
					u8 index;
					fread(&index,1,1,file);
					AGIDL_TGASetClr16(tga,x,y,tga->palette.icp.palette_16b_256[index]);
				}
			}
		}
		else if(img_type == TGA_IMG_TYPE_TRUE_CLR){
			AGIDL_TGASetClrFmt(tga,AGIDL_BGR_888);
			
			tga->pixels.pix32 = (COLOR*)malloc(sizeof(COLOR)*(AGIDL_TGAGetWidth(tga)*AGIDL_TGAGetHeight(tga)));
			
			int i;
			for(i = 0; i < tga->header.clrmaplength; i++){
				COLOR clr = 0;
				u8 r,g,b;
				fread(&b,1,1,file);
				fread(&g,1,1,file);
				fread(&r,1,1,file);
				clr = AGIDL_RGB(r,g,b,tga->fmt);
				tga->palette.icp.palette_256[i] = clr;
			}
			
			int x,y;
			for(y = 0; y < AGIDL_TGAGetHeight(tga); y++){
				for(x = 0; x < AGIDL_TGAGetWidth(tga); x++){
					u8 index;
					fread(&index,1,1,file);
					AGIDL_TGASetClr(tga,x,y,tga->palette.icp.palette_256[index]);
				}
			}
		}
		else{
			AGIDL_TGASetClrFmt(tga,AGIDL_RGBA_8888);
				
			tga->pixels.pix32 = (COLOR*)malloc(sizeof(COLOR)*(AGIDL_TGAGetWidth(tga)*AGIDL_TGAGetHeight(tga)));
			
			int i;
			for(i = 0; i < tga->header.clrmaplength; i++){
				COLOR clr = 0;
				u8 r,g,b;
				fread(&b,1,1,file);
				fread(&g,1,1,file);
				fread(&r,1,1,file);
				clr = AGIDL_RGB(r,g,b,tga->fmt);
				tga->palette.icp.palette_256[i] = clr;
			}
			
			int x,y;
			for(y = 0; y < AGIDL_TGAGetHeight(tga); y++){
				for(x = 0; x < AGIDL_TGAGetWidth(tga); x++){
					u8 index;
					fread(&index,1,1,file);
					AGIDL_TGASetClr(tga,x,y,tga->palette.icp.palette_256[index]);
				}
			}
		}
	}
}

u16 binmul2[9] = {1,2,4,8,16,32,64,128,256};

u16 bin2dec2(char* binary){
	int i, accumulation = 0, count = 0;
	for(i = strlen(binary)-1; i >= 0; i--){
		int bin;
		if(binary[i] == '0'){
			bin = 0;
		}
		if(binary[i] == '1'){
			bin = 1;
		}
		accumulation += bin * binmul2[count];
		count++;
	}
	return accumulation;
}

char* dec2bin2(u16 number){
	char *bin = (char*)malloc(sizeof(char)*9);
	int i;
	for(i = 7; i >= 0; i--){
		int k = number >> i;
		if(k & 1){
			bin[7-i] = '1';
		}
		else{
			bin[7-i] = '0';
		}
	}
	bin[8] = '\0';
	return bin;
}

char* tgarlebits(char *binary){
	char *bin = (char*)malloc(sizeof(char)*9);
	int i;
	for(i = 1; i <= 7; i++){
		bin[i-1] = binary[i];
	}
	bin[7] = '\0';
	return bin;
}

void AGIDL_TGADecodeRLE(AGIDL_TGA* tga, FILE* file, TGA_ICP_TYPE icp, TGA_IMG_TYPE img_type){
	if(icp == TGA_IMG_TYPE_RLE_NO_ICP){
		switch(img_type){
			case TGA_IMG_TYPE_HIGH_CLR:{
				AGIDL_TGASetClrFmt(tga,AGIDL_BGR_555);
				tga->pixels.pix16 = (COLOR16*)malloc(sizeof(COLOR16)*(AGIDL_TGAGetWidth(tga)*AGIDL_TGAGetHeight(tga)));
				int x,y;
				for(y = 0; y < AGIDL_TGAGetHeight(tga); y++){
					for(x = 0; x < AGIDL_TGAGetWidth(tga); x++){
						u8 byte;
						fread(&byte,1,1,file);
						
						char* binbyte = dec2bin2(byte);

						if(binbyte[0] == '1' && bin2dec2(tgarlebits(binbyte)) > 0){
							char* packrle = tgarlebits(binbyte);
							u16 rle = bin2dec2(packrle) + 1;
							COLOR16 col;
							fread(&col,2,1,file);
							u8 r = AGIDL_GetR(col,tga->fmt);
							u8 g = AGIDL_GetG(col,tga->fmt);
							u8 b = AGIDL_GetB(col,tga->fmt);
							col = AGIDL_RGB16(b,g,r,tga->fmt);
							int i;
							for(i = 0; i < rle; i++){
								AGIDL_TGASetClr16(tga,x+i,y,col);
							}
							x += rle - 1;
							free(packrle);
						}
						else{
							COLOR16 col;
							fread(&col,2,1,file);
							u8 r = AGIDL_GetR(col,tga->fmt);
							u8 g = AGIDL_GetG(col,tga->fmt);
							u8 b = AGIDL_GetB(col,tga->fmt);
							col = AGIDL_RGB16(b,g,r,tga->fmt);
							AGIDL_TGASetClr16(tga,x,y,col);
						}
						
						free(binbyte);
					}
				}
			}break;
			case TGA_IMG_TYPE_TRUE_CLR:{
				AGIDL_TGASetClrFmt(tga,AGIDL_BGR_888);
				tga->pixels.pix32 = (COLOR*)malloc(sizeof(COLOR)*(AGIDL_TGAGetWidth(tga)*AGIDL_TGAGetHeight(tga)));
		
				int x,y;
				for(y = 0; y < AGIDL_TGAGetHeight(tga); y++){
					for(x = 0; x < AGIDL_TGAGetWidth(tga); x++){
						u8 byte;
						fread(&byte,1,1,file);
						
						char* binbyte = dec2bin2(byte);
						
						if(binbyte[0] == '1'  && bin2dec2(tgarlebits(binbyte)) > 0){
							char* packrle = tgarlebits(binbyte);
							u16 rle = bin2dec2(packrle) + 1;
							COLOR clr = 0;
							u8 r,g,b;
							fread(&b,1,1,file);
							fread(&g,1,1,file);
							fread(&r,1,1,file);
							clr = AGIDL_RGB(r,g,b,tga->fmt);
							int i;
							for(i = 0; i < rle; i++){
								AGIDL_TGASetClr(tga,x+i,y,clr);
							}
							x += rle - 1;
							free(packrle);
						}
						else{
							COLOR clr = 0;
							u8 r,g,b;
							fread(&b,1,1,file);
							fread(&g,1,1,file);
							fread(&r,1,1,file);
							clr = AGIDL_RGB(r,g,b,tga->fmt);
							AGIDL_TGASetClr(tga,x,y,clr);
						}
						
						free(binbyte);
					}
				}
			}break;
			case TGA_IMG_TYPE_DEEP_CLR:{
				AGIDL_TGASetClrFmt(tga,AGIDL_RGBA_8888);
				tga->pixels.pix32 = (COLOR*)malloc(sizeof(COLOR)*(AGIDL_TGAGetWidth(tga)*AGIDL_TGAGetHeight(tga)));
				int x,y;
				for(y = 0; y < AGIDL_TGAGetHeight(tga); y++){
					for(x = 0; x < AGIDL_TGAGetWidth(tga); x++){
						u8 byte;
						fread(&byte,1,1,file);
						
						char* binbyte = dec2bin2(byte);
						
						if(binbyte[0] == '1' && bin2dec2(tgarlebits(binbyte)) > 0){
							char* packrle = tgarlebits(binbyte);
							u16 rle = bin2dec2(packrle) + 1;
							COLOR col;
							u8 r = AGIDL_GetR(col,AGIDL_RGBA_8888);
							u8 g = AGIDL_GetG(col,AGIDL_RGBA_8888);
							u8 b = AGIDL_GetB(col,AGIDL_RGBA_8888);
							u8 a = AGIDL_GetA(col,AGIDL_RGBA_8888);
							col = AGIDL_RGBA(b,g,r,a,AGIDL_RGBA_8888);
							fread(&col,4,1,file);
							int i;
							for(i = 0; i < rle; i++){
								AGIDL_TGASetClr(tga,x+i,y,col);
							}
							x += rle - 1;
							free(packrle);
						}
						else{
							COLOR col;
							u8 r = AGIDL_GetR(col,AGIDL_RGBA_8888);
							u8 g = AGIDL_GetG(col,AGIDL_RGBA_8888);
							u8 b = AGIDL_GetB(col,AGIDL_RGBA_8888);
							u8 a = AGIDL_GetA(col,AGIDL_RGBA_8888);
							col = AGIDL_RGBA(b,g,r,a,AGIDL_RGBA_8888);
							fread(&col,4,1,file);
							AGIDL_TGASetClr(tga,x,y,col);
						}
						
						free(binbyte);
					}
				}
			}break;
		}
	}
	else if(icp == TGA_IMG_TYPE_RLE_ICP){
		switch(img_type){
			case TGA_IMG_TYPE_TRUE_CLR:{
				AGIDL_TGASetClrFmt(tga,AGIDL_BGR_888);
			
				tga->pixels.pix32 = (COLOR*)malloc(sizeof(COLOR)*(AGIDL_TGAGetWidth(tga)*AGIDL_TGAGetHeight(tga)));
				
				int i;
				for(i = 0; i < tga->header.clrmaplength; i++){
					COLOR clr = 0;
					u8 r,g,b;
					fread(&b,1,1,file);
					fread(&g,1,1,file);
					fread(&r,1,1,file);
					clr = AGIDL_RGB(r,g,b,tga->fmt);
					tga->palette.icp.palette_256[i] = clr;
				}
				
				int x,y;
				for(y = 0; y < AGIDL_TGAGetHeight(tga); y++){
					for(x = 0; x < AGIDL_TGAGetWidth(tga); x++){
						u8 index;
						fread(&index,1,1,file);
						AGIDL_TGASetClr(tga,x,y,tga->palette.icp.palette_256[index]);
					}
				}
				
				for(y = 0; y < AGIDL_TGAGetHeight(tga); y++){
					for(x = 0; x < AGIDL_TGAGetWidth(tga); x++){
						u8 byte;
						fread(&byte,1,1,file);
						
						char* binbyte = dec2bin2(byte);
						
						if(binbyte[0] == '1' && bin2dec2(tgarlebits(binbyte)) > 0){
							char* packrle = tgarlebits(binbyte);
							u16 rle = bin2dec2(packrle) + 1;
							u8 index;
							fread(&index,1,1,file);
							int i;
							for(i = 0; i < rle; i++){
								AGIDL_TGASetClr(tga,x+i,y,tga->palette.icp.palette_256[index]);
							}
							x += rle - 1;
							free(packrle);
						}
						else{
							u8 index;
							fread(&index,1,1,file);
							AGIDL_TGASetClr(tga,x,y,tga->palette.icp.palette_256[index]);
						}
						
						free(binbyte);
					}
				}
			}break;
			case TGA_IMG_TYPE_HIGH_CLR:{
				AGIDL_TGASetClrFmt(tga,AGIDL_BGR_555);
			
				tga->pixels.pix16 = (COLOR16*)malloc(sizeof(COLOR16)*(AGIDL_TGAGetWidth(tga)*AGIDL_TGAGetHeight(tga)));
				
				int i;
				for(i = 0; i < tga->header.clrmaplength; i++){
					COLOR16 clr = 0;
					fread(&clr,2,1,file);
					u8 r = AGIDL_GetR(clr,tga->fmt);
					u8 g = AGIDL_GetG(clr,tga->fmt);
					u8 b = AGIDL_GetB(clr,tga->fmt);
					clr = AGIDL_RGB16(b,g,r,tga->fmt);
					tga->palette.icp.palette_16b_256[i] = clr;
				}
				
				int x,y;
				for(y = 0; y < AGIDL_TGAGetHeight(tga); y++){
					for(x = 0; x < AGIDL_TGAGetWidth(tga); x++){
						u8 index;
						fread(&index,1,1,file);
						AGIDL_TGASetClr(tga,x,y,tga->palette.icp.palette_256[index]);
					}
				}

				for(y = 0; y < AGIDL_TGAGetHeight(tga); y++){
					for(x = 0; x < AGIDL_TGAGetWidth(tga); x++){
						u8 byte;
						fread(&byte,1,1,file);
						
						char* binbyte = dec2bin2(byte);
						
						if(binbyte[0] == '1' && bin2dec2(tgarlebits(binbyte)) > 0){
							char* packrle = tgarlebits(binbyte);
							u16 rle = bin2dec2(packrle) + 1;
							u8 index;
							fread(&index,1,1,file);
							int i;
							for(i = 0; i < rle; i++){
								AGIDL_TGASetClr(tga,x+i,y,tga->palette.icp.palette_16b_256[index]);
							}
							x += rle - 1;
							free(packrle);
						}
						else{
							u8 index;
							fread(&index,1,1,file);
							AGIDL_TGASetClr(tga,x,y,tga->palette.icp.palette_16b_256[index]);
						}
						
						free(binbyte);
					}
				}
			}break;
		}
	}
}

void AGIDL_TGAEncodeHeader(AGIDL_TGA* tga, FILE* file){
	fwrite(&tga->header.id,1,1,file);
	fwrite(&tga->header.clrmaptype,1,1,file);
	fwrite(&tga->header.imgtype,1,1,file);
	fwrite(&tga->header.clrmapstart,2,1,file);
	fwrite(&tga->header.clrmaplength,2,1,file);
	fwrite(&tga->header.icpbits,1,1,file);
	fwrite(&tga->header.xstart,2,1,file);
	fwrite(&tga->header.ystart,2,1,file);
	fwrite(&tga->header.width,2,1,file);
	fwrite(&tga->header.height,2,1,file);
	fwrite(&tga->header.bits,1,1,file);
	fwrite(&tga->header.flip,1,1,file);
}

void AGIDL_TGAEncodeIMG(AGIDL_TGA* tga, FILE* file){
	if(tga->header.bits != 8){
		if(tga->fmt == AGIDL_BGR_888){
			int x,y;
			for(y = 0; y < AGIDL_TGAGetHeight(tga); y++){
				for(x = 0; x < AGIDL_TGAGetWidth(tga); x++){
					COLOR clr = AGIDL_TGAGetClr(tga,x,y);
					AGIDL_ExtractAndPrintBGR(file,clr,tga->fmt);
				}
			}	
		}	
		if(tga->fmt == AGIDL_RGBA_8888){
			int x,y;
			for(y = 0; y < AGIDL_TGAGetHeight(tga); y++){
				for(x = 0; x < AGIDL_TGAGetWidth(tga); x++){
					COLOR clr = AGIDL_TGAGetClr(tga,x,y);
					u8 r = AGIDL_GetR(clr,AGIDL_TGAGetClrFmt(tga));
					u8 g = AGIDL_GetG(clr,AGIDL_TGAGetClrFmt(tga));
					u8 b = AGIDL_GetB(clr,AGIDL_TGAGetClrFmt(tga));
					clr = AGIDL_RGB(r,g,b,AGIDL_BGR_888);
					AGIDL_ExtractAndPrintBGR(file,clr,AGIDL_BGR_888);
				}
			}	
		}
		if(tga->fmt == AGIDL_ARGB_8888){
			int x,y;
			for(y = 0; y < AGIDL_TGAGetHeight(tga); y++){
				for(x = 0; x < AGIDL_TGAGetWidth(tga); x++){
					COLOR clr = AGIDL_TGAGetClr(tga,x,y);
					u8 r = AGIDL_GetR(clr,AGIDL_TGAGetClrFmt(tga));
					u8 g = AGIDL_GetG(clr,AGIDL_TGAGetClrFmt(tga));
					u8 b = AGIDL_GetB(clr,AGIDL_TGAGetClrFmt(tga));
					clr = AGIDL_RGB(r,g,b,AGIDL_BGR_888);
					AGIDL_ExtractAndPrintBGR(file,clr,AGIDL_BGR_888);
				}
			}	
		}
		if(tga->fmt == AGIDL_RGB_555){
			int x,y;
			for(y = 0; y < AGIDL_TGAGetHeight(tga); y++){
				for(x = 0; x < AGIDL_TGAGetWidth(tga); x++){
					COLOR16 clr = AGIDL_TGAGetClr16(tga,x,y);
					fwrite(&clr,2,1,file);
				}
			}	
		}
	}
	else{
		int x,y;
		for(y = 0; y < AGIDL_TGAGetHeight(tga); y++){
			for(x = 0; x < AGIDL_TGAGetWidth(tga); x++){
				COLOR clr = AGIDL_TGAGetClr(tga,x,y);
				
				if(AGIDL_GetBitCount(AGIDL_TGAGetClrFmt(tga)) == 32){
					u8 r = AGIDL_GetR(clr,AGIDL_TGAGetClrFmt(tga));
					u8 g = AGIDL_GetG(clr,AGIDL_TGAGetClrFmt(tga));
					u8 b = AGIDL_GetB(clr,AGIDL_TGAGetClrFmt(tga));
					clr = AGIDL_RGB(r,g,b,AGIDL_BGR_888);
					u8 index = AGIDL_FindClosestColor(tga->palette,clr,AGIDL_BGR_888,AGIDL_TGAGetMaxDiff(tga));
					fwrite(&index,1,1,file);
				}
				else{
					u8 index = AGIDL_FindClosestColor(tga->palette,clr,tga->fmt,AGIDL_TGAGetMaxDiff(tga));
					fwrite(&index,1,1,file);
				}
			}
		}
	}
}

void AGIDL_TGAEncodeICP(AGIDL_TGA* tga, FILE* file){
	if(tga->fmt == AGIDL_RGB_555){
		int pass = 0;
		u8 pal_index = 0;
		
		AGIDL_InitICP(&tga->palette, AGIDL_ICP_16b_256);
		
		int x,y;
		for(y = 0; y < AGIDL_TGAGetHeight(tga); y++){
			for(x = 0; x < AGIDL_TGAGetWidth(tga); x++){
				COLOR16 clr = AGIDL_TGAGetClr16(tga,x,y);
				
				AGIDL_AddColorICP16(&tga->palette,pal_index,clr,tga->fmt,AGIDL_TGAGetMaxDiff(tga),&pass);
				if(pass == 1 && pal_index < 256){
					pal_index++;
				}
				
				pass = 0;
			}
		}
		
		tga->header.id = 0;
		tga->header.clrmaptype = 1;
		tga->header.imgtype = 1;
		tga->header.clrmapstart = 0;
		tga->header.clrmaplength = 256;
		tga->header.icpbits = 16;
		tga->header.xstart = 0;
		tga->header.ystart = 0;
		tga->header.bits = 8;
		tga->header.flip = 0;
		
		AGIDL_TGAEncodeHeader(tga,file);
		
		int i;
		for(i = 0; i < 256; i++){
			fwrite(&tga->palette.icp.palette_16b_256[i],2,1,file);
		}
	}
	else{
		int pass = 0;
		u8 pal_index = 0;
		
		AGIDL_InitICP(&tga->palette, AGIDL_ICP_256);
		
		int x,y;
		for(y = 0; y < AGIDL_TGAGetHeight(tga); y++){
			for(x = 0; x < AGIDL_TGAGetWidth(tga); x++){
				COLOR clr = AGIDL_TGAGetClr(tga,x,y);
				
				if(AGIDL_GetBitCount(AGIDL_TGAGetClrFmt(tga)) == 32){
					u8 r = AGIDL_GetR(clr,AGIDL_TGAGetClrFmt(tga));
					u8 g = AGIDL_GetG(clr,AGIDL_TGAGetClrFmt(tga));
					u8 b = AGIDL_GetB(clr,AGIDL_TGAGetClrFmt(tga));
					clr = AGIDL_RGB(r,g,b,AGIDL_BGR_888);
					
					AGIDL_AddColorICP(&tga->palette,pal_index,clr,AGIDL_BGR_888,AGIDL_TGAGetMaxDiff(tga),&pass);
				}
				else{
					AGIDL_AddColorICP(&tga->palette,pal_index,clr,tga->fmt,AGIDL_TGAGetMaxDiff(tga),&pass);
				}
				
				if(pass == 1 && pal_index < 256){
					pal_index++;
				}
				
				pass = 0;
			}
		}
		
		tga->header.id = 0;
		tga->header.clrmaptype = 1;
		tga->header.imgtype = 1;
		tga->header.clrmapstart = 0;
		tga->header.clrmaplength = 256;
		tga->header.icpbits = 24;
		tga->header.xstart = 0;
		tga->header.ystart = 0;
		tga->header.bits = 8;
		tga->header.flip = 0;
		
		AGIDL_TGAEncodeHeader(tga,file);
		
		int i;
		for(i = 0; i < 256; i++){
			COLOR clr = tga->palette.icp.palette_256[i];
			AGIDL_ExtractAndPrintBGR(file,clr,AGIDL_BGR_888);
		}
	}
}

void AGIDL_TGAEncodeRLE(AGIDL_TGA* tga, FILE* file){
	if(tga->compression){
		switch(tga->fmt){
			case AGIDL_BGR_888:{
				int x,y;
				for(y = 0; y < AGIDL_TGAGetHeight(tga); y++){
					for(x = 0; x < AGIDL_TGAGetWidth(tga); x++){
					
						COLOR clr = AGIDL_TGAGetClr(tga,x,y);
					
						u32 count = AGIDL_EncodeRLE(tga->pixels.pix32,24,x,y,AGIDL_TGAGetWidth(tga),AGIDL_TGAGetHeight(tga),AGIDL_TGAGetWidth(tga));
						
						x += count - 1;
						
						if(count > 0){
							char* rle = dec2bin2(count-1);
							rle[0] = '1';
							u16 rleshort = bin2dec2(rle);
							fwrite(&rleshort,1,1,file);
							AGIDL_ExtractAndPrintBGR(file,clr,AGIDL_BGR_888);
							free(rle);
						}
						else{
							u8 zero = 1;
							fwrite(&zero,1,1,file);
							AGIDL_ExtractAndPrintBGR(file,clr,AGIDL_BGR_888);
						}
					}
				}
			}break;
			case AGIDL_RGB_555:{
				int x,y;
				for(y = 0; y < AGIDL_TGAGetHeight(tga); y++){
					for(x = 0; x < AGIDL_TGAGetWidth(tga); x++){
						COLOR16 clr = AGIDL_TGAGetClr16(tga,x,y);
						
						u32 count = AGIDL_EncodeRLE(tga->pixels.pix16,16,x,y,AGIDL_TGAGetWidth(tga),AGIDL_TGAGetHeight(tga),AGIDL_TGAGetWidth(tga));
						
						x += count - 1;
						
						if(count > 0){
							char* rle = dec2bin2(count-1);
							rle[0] = '1';
							u16 rleshort = bin2dec2(rle);
							fwrite(&rleshort,1,1,file);
							fwrite(&clr,2,1,file);
							free(rle);
						}
						else{
							u8 zero = 0;
							fwrite(&zero,1,1,file);
							fwrite(&clr,1,1,file);
						}
					}
				}
			}break;
			case AGIDL_RGBA_8888:{
				int x,y;
				for(y = 0; y < AGIDL_TGAGetHeight(tga); y++){
					for(x = 0; x < AGIDL_TGAGetWidth(tga); x++){
						COLOR clr = AGIDL_TGAGetClr(tga,x,y);
						
						u32 count = AGIDL_EncodeRLE(tga->pixels.pix32,32,x,y,AGIDL_TGAGetWidth(tga),AGIDL_TGAGetHeight(tga),AGIDL_TGAGetWidth(tga));
						
						x += count - 1;
						
						u8 r = AGIDL_GetR(clr,AGIDL_RGBA_8888);
						u8 g = AGIDL_GetG(clr,AGIDL_RGBA_8888);
						u8 b = AGIDL_GetB(clr,AGIDL_RGBA_8888);
						clr = AGIDL_RGB(r,g,b,AGIDL_RGB_888);
						
						if(count > 0){
							char* rle = dec2bin2(count-1);
							rle[0] = '1';
							u16 rleshort = bin2dec2(rle);
							fwrite(&rleshort,1,1,file);
							fwrite(&clr,3,1,file);
							free(rle);
						}
						else{
							u8 zero = 0;
							fwrite(&zero,1,1,file);
							fwrite(&clr,3,1,file);
						}
					}
				}
			}break;
			case AGIDL_ARGB_8888:{
				int x,y;
				for(y = 0; y < AGIDL_TGAGetHeight(tga); y++){
					for(x = 0; x < AGIDL_TGAGetWidth(tga); x++){
						COLOR clr = AGIDL_TGAGetClr(tga,x,y);
						
						u32 count = AGIDL_EncodeRLE(tga->pixels.pix32,32,x,y,AGIDL_TGAGetWidth(tga),AGIDL_TGAGetHeight(tga),AGIDL_TGAGetWidth(tga));
						
						x += count - 1;
						
						u8 r = AGIDL_GetR(clr,AGIDL_ARGB_8888);
						u8 g = AGIDL_GetG(clr,AGIDL_ARGB_8888);
						u8 b = AGIDL_GetB(clr,AGIDL_ARGB_8888);
						clr = AGIDL_RGB(r,g,b,AGIDL_RGB_888);
						
						if(count > 0){
							char* rle = dec2bin2(count-1);
							rle[0] = '1';
							u16 rleshort = bin2dec2(rle);
							fwrite(&rleshort,1,1,file);
							fwrite(&clr,3,1,file);
							free(rle);
						}
						else{
							u8 zero = 0;
							fwrite(&zero,1,1,file);
							fwrite(&clr,3,1,file);
						}
					}
				}
			}break;
		}
	}
}

AGIDL_TGA * AGIDL_LoadTGA(char *filename){
	FILE* file = fopen(filename,"rb");
	
	if(file == NULL){
		printf("Could not locate TGA image file - %s\n",filename);
	}
	
	AGIDL_TGA *tga = (AGIDL_TGA*)malloc(sizeof(AGIDL_TGA));
	AGIDL_SetTGAFilename(tga,filename);
	
	AGIDL_TGADecodeHeader(tga,file);
	
	TGA_ICP_TYPE icp = AGIDL_TGAGetICPType(tga->header.imgtype);
	TGA_IMG_TYPE img_type = AGIDL_TGAGetIMGType(tga->header.bits);
	
	AGIDL_TGADecodeIMG(tga,file,icp,img_type);
	AGIDL_TGADecodeRLE(tga,file,icp,img_type);
	
	fclose(file);
	
	return tga;
}

void AGIDL_ExportTGA(AGIDL_TGA *tga){
	FILE *file = fopen(tga->filename,"wb");
	
	if(file == NULL){
		printf("Could not create TGA image file - %s\n",tga->filename);
	}
	
	if(tga->icp != 1 && tga->compression != 1){
		tga->header.id = 0;
		tga->header.clrmaptype = 0;
		tga->header.imgtype = 2;
		tga->header.clrmapstart = 0;
		tga->header.clrmaplength = 0;
		tga->header.icpbits = 0;
		
		if(AGIDL_GetBitCount(AGIDL_TGAGetClrFmt(tga)) == 24 || AGIDL_GetBitCount(AGIDL_TGAGetClrFmt(tga)) == 32){
			tga->header.bits = 24;
		}
		
		if(AGIDL_GetBitCount(AGIDL_TGAGetClrFmt(tga)) == 16){
			tga->header.bits = 16;
		}
		
		tga->header.xstart = 0;
		tga->header.ystart = 0;
		tga->header.flip = 0;
		
		AGIDL_TGAEncodeHeader(tga,file);
		
		switch(tga->fmt){
			case AGIDL_RGB_888:{
				AGIDL_TGARGB2BGR(tga);
				AGIDL_TGAEncodeIMG(tga,file);
				AGIDL_TGABGR2RGB(tga);
			}break;
			case AGIDL_BGR_888:{
				AGIDL_TGAEncodeIMG(tga,file);
			}break;
			case AGIDL_RGB_555:{
				AGIDL_TGAEncodeIMG(tga,file);
			}break;
			case AGIDL_BGR_555:{
				AGIDL_TGABGR2RGB(tga);
				AGIDL_TGAEncodeIMG(tga,file);
				AGIDL_TGABGR2RGB(tga);
			}break;
			case AGIDL_RGB_565:{
				AGIDL_TGAConvert565TO555(tga);
				AGIDL_TGAEncodeIMG(tga,file);
				AGIDL_TGAConvert555TO565(tga);
			}break;
			case AGIDL_BGR_565:{
				AGIDL_TGAConvert565TO555(tga);
				AGIDL_TGABGR2RGB(tga);
				AGIDL_TGAEncodeIMG(tga,file);
				AGIDL_TGABGR2RGB(tga);
				AGIDL_TGAConvert555TO565(tga);
			}break;
			case AGIDL_RGBA_8888:{
				AGIDL_TGAEncodeIMG(tga,file);
			}break;
			case AGIDL_ARGB_8888:{
				AGIDL_TGAEncodeIMG(tga,file);
			}break;
		}
	}
	else if(tga->compression != 1){
		switch(tga->fmt){
			case AGIDL_RGB_888:{
				AGIDL_TGARGB2BGR(tga);
				AGIDL_TGAEncodeICP(tga,file);
				AGIDL_TGAEncodeIMG(tga,file);
				AGIDL_TGABGR2RGB(tga);
			}break;
			case AGIDL_BGR_888:{
				AGIDL_TGAEncodeICP(tga,file);
				AGIDL_TGAEncodeIMG(tga,file);
			}break;
			case AGIDL_RGBA_8888:{
				AGIDL_TGAEncodeICP(tga,file);
				AGIDL_TGAEncodeIMG(tga,file);
			}break;
			case AGIDL_ARGB_8888:{
				AGIDL_TGAEncodeICP(tga,file);
				AGIDL_TGAEncodeIMG(tga,file);
			}break;
			case AGIDL_RGB_555:{
				AGIDL_TGARGB2BGR(tga);
				AGIDL_TGAConvert16BPPTO24BPP(tga);
				AGIDL_TGAEncodeICP(tga,file);
				AGIDL_TGAEncodeIMG(tga,file);
				AGIDL_TGAConvert24BPPTO16BPP(tga);
				AGIDL_TGABGR2RGB(tga);
			}break;
			case AGIDL_BGR_555:{
				AGIDL_TGAConvert16BPPTO24BPP(tga);
				AGIDL_TGAEncodeICP(tga,file);
				AGIDL_TGAEncodeIMG(tga,file);
				AGIDL_TGAConvert24BPPTO16BPP(tga);
			}break;
			case AGIDL_RGB_565:{
				AGIDL_TGAConvert565TO555(tga);
				AGIDL_TGARGB2BGR(tga);
				AGIDL_TGAConvert16BPPTO24BPP(tga);
				AGIDL_TGAEncodeICP(tga,file);
				AGIDL_TGAEncodeIMG(tga,file);
				AGIDL_TGAConvert24BPPTO16BPP(tga);
				AGIDL_TGABGR2RGB(tga);
				AGIDL_TGAConvert555TO565(tga);
			}break;
			case AGIDL_BGR_565:{
				AGIDL_TGAConvert565TO555(tga);
				AGIDL_TGAConvert16BPPTO24BPP(tga);
				AGIDL_TGAEncodeICP(tga,file);
				AGIDL_TGAEncodeIMG(tga,file);
				AGIDL_TGAConvert24BPPTO16BPP(tga);
				AGIDL_TGAConvert555TO565(tga);
			}break;
		}
	}
	else{
		tga->header.id = 0;
		tga->header.clrmaptype = 0;
		tga->header.imgtype = 10;
		tga->header.clrmapstart = 0;
		tga->header.clrmaplength = 0;
		tga->header.icpbits = 0;
		
		if(AGIDL_GetBitCount(AGIDL_TGAGetClrFmt(tga)) == 24 || AGIDL_GetBitCount(AGIDL_TGAGetClrFmt(tga)) == 32){
			tga->header.bits = 24;
		}
		
		if(AGIDL_GetBitCount(AGIDL_TGAGetClrFmt(tga)) == 16){
			tga->header.bits = 16;
		}
		
		tga->header.xstart = 0;
		tga->header.ystart = 0;
		tga->header.flip = 0;
		
		AGIDL_TGAEncodeHeader(tga,file);
		
		switch(tga->fmt){
			case AGIDL_RGB_888:{
				AGIDL_TGARGB2BGR(tga);
				AGIDL_TGAEncodeRLE(tga,file);
				AGIDL_TGABGR2RGB(tga);
			}break;
			case AGIDL_BGR_888:{
				AGIDL_TGAEncodeRLE(tga,file);
			}break;
			case AGIDL_RGB_555:{
				AGIDL_TGAEncodeRLE(tga,file);
			}break;
			case AGIDL_BGR_555:{
				AGIDL_TGABGR2RGB(tga);
				AGIDL_TGAEncodeRLE(tga,file);
				AGIDL_TGARGB2BGR(tga);
			}break;
			case AGIDL_RGB_565:{
				AGIDL_TGAConvert565TO555(tga);
				AGIDL_TGAEncodeRLE(tga,file);
				AGIDL_TGAConvert555TO565(tga);
			}break;
			case AGIDL_BGR_565:{
				AGIDL_TGAConvert565TO555(tga);
				AGIDL_TGABGR2RGB(tga);
				AGIDL_TGAEncodeRLE(tga,file);
				AGIDL_TGARGB2BGR(tga);
				AGIDL_TGAConvert555TO565(tga);
			}break;
			case AGIDL_RGBA_8888:{
				AGIDL_TGAEncodeRLE(tga,file);
			}break;
			case AGIDL_ARGB_8888:{
				AGIDL_TGAEncodeRLE(tga,file);
			}break;
		}
	}
	
	fclose(file);
}