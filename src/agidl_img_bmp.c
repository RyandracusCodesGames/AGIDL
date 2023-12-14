#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "agidl_cc_core.h"
#include "agidl_img_bmp.h"
#include "agidl_math_utils.h"
#include "agidl_img_compression.h"

/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023 Ryandracus Chapman
*
*   Library: libagidl
*   File: agidl_img_bmp.c
*   Date: 9/12/2023
*   Version: 0.1b
*   Updated: 11/30/2023
*   Author: Ryandracus Chapman
*
********************************************/
void AGIDL_SetBMPFilename(AGIDL_BMP *bmp, const char *filename){
	bmp->filename = (char*)realloc(bmp->filename,strlen(filename));
	AGIDL_FilenameCpy(bmp->filename,filename);
}

void AGIDL_BMPSetWidth(AGIDL_BMP *bmp, int width){
	bmp->header.width = width;
}

void AGIDL_BMPSetHeight(AGIDL_BMP *bmp, int height){
	bmp->header.height = height;
}

void AGIDL_BMPSetClrFmt(AGIDL_BMP *bmp, AGIDL_CLR_FMT fmt){
	bmp->fmt = fmt;
}

void AGIDL_BMPSetPalette(AGIDL_BMP *bmp, AGIDL_ICP palette){
	bmp->palette = palette;
}

void AGIDL_BMPSetMaxDiff(AGIDL_BMP *bmp, u16 max_diff){
	bmp->max_diff = max_diff;
}

void AGIDL_BMPSetRGB(AGIDL_BMP *bmp, int x, int y, u8 r, u8 g, u8 b){
	switch(AGIDL_GetBitCount(AGIDL_BMPGetClrFmt(bmp))){
		case 24:{
			AGIDL_BMPSetClr(bmp,x,y,AGIDL_RGB(r,g,b,AGIDL_BMPGetClrFmt(bmp)));
		}break;
		case 16:{
			AGIDL_BMPSetClr16(bmp,x,y,AGIDL_RGB16(r,g,b,AGIDL_BMPGetClrFmt(bmp)));
		}break;
		case 32:{
			AGIDL_BMPSetClr(bmp,x,y,AGIDL_RGBA(r,g,b,0xff,AGIDL_BMPGetClrFmt(bmp)));
		}break;
	}
}

void AGIDL_BMPSetRGBA(AGIDL_BMP *bmp, int x, int y, u8 r, u8 g, u8 b, u8 a){
	switch(bmp->fmt){
		case AGIDL_RGBA_8888:{
			AGIDL_BMPSetClr(bmp,x,y,AGIDL_RGBA(r,g,b,a,AGIDL_RGBA_8888));
		}break;
		case AGIDL_ARGB_8888:{
			AGIDL_BMPSetClr(bmp,x,y,AGIDL_RGBA(r,g,b,a,AGIDL_ARGB_8888));
		}break;
	}
}

void AGIDL_BMPSetClr(AGIDL_BMP *bmp, int x, int y, COLOR clr){
	AGIDL_SetClr(bmp->pixels.pix32,clr,x,y,AGIDL_BMPGetWidth(bmp),AGIDL_BMPGetHeight(bmp));
}

void AGIDL_BMPSetClr16(AGIDL_BMP *bmp, int x, int y, COLOR16 clr){
	AGIDL_SetClr16(bmp->pixels.pix16,clr,x,y,AGIDL_BMPGetWidth(bmp),AGIDL_BMPGetHeight(bmp));
}

void AGIDL_BMPSetICPMode(AGIDL_BMP *bmp, int mode){
	bmp->icp = mode;
}

void AGIDL_BMPSetCompression(AGIDL_BMP *bmp, int compress){
	bmp->compression = compress;
}

void AGIDL_ClearBMP(AGIDL_BMP *bmp, COLOR clr){
	AGIDL_ClrMemset(bmp->pixels.pix32,clr,AGIDL_BMPGetSize(bmp));
}

void AGIDL_ClearBMP16(AGIDL_BMP *bmp, COLOR16 clr){
	AGIDL_ClrMemset16(bmp->pixels.pix16,clr,AGIDL_BMPGetSize(bmp));
}

void AGIDL_BMPRGB2BGR(AGIDL_BMP *bmp){
	if(bmp->fmt == AGIDL_RGB_888){
		AGIDL_RGB2BGR(bmp->pixels.pix32,AGIDL_BMPGetWidth(bmp),AGIDL_BMPGetHeight(bmp),&bmp->fmt);
	}
	if(bmp->fmt == AGIDL_RGB_555){
		AGIDL_RGB2BGR16(bmp->pixels.pix16,AGIDL_BMPGetWidth(bmp),AGIDL_BMPGetHeight(bmp),&bmp->fmt);
	}
}

void AGIDL_BMPBGR2RGB(AGIDL_BMP *bmp){
	if(bmp->fmt == AGIDL_BGR_888){
		AGIDL_BGR2RGB(bmp->pixels.pix32,AGIDL_BMPGetWidth(bmp),AGIDL_BMPGetHeight(bmp),&bmp->fmt);
	}
	if(bmp->fmt == AGIDL_BGR_555){
		AGIDL_BGR2RGB16(bmp->pixels.pix16,AGIDL_BMPGetWidth(bmp),AGIDL_BMPGetHeight(bmp),&bmp->fmt);
	}
}

void AGIDL_BMPConvert16BPPTO24BPP(AGIDL_BMP *bmp){
	if(bmp->fmt == AGIDL_RGB_555 || bmp->fmt == AGIDL_BGR_555 || bmp->fmt == AGIDL_RGB_565 || bmp->fmt == AGIDL_BGR_565){
		bmp->pixels.pix32 = (COLOR*)malloc(sizeof(COLOR)*(AGIDL_BMPGetHeight(bmp)*AGIDL_BMPGetWidth(bmp)));
		AGIDL_16BPPTO24BPP(bmp->pixels.pix16,bmp->pixels.pix32,AGIDL_BMPGetWidth(bmp),AGIDL_BMPGetHeight(bmp),&bmp->fmt);
		free(bmp->pixels.pix16);
	}
}

void AGIDL_BMPConvert24BPPTO16BPP(AGIDL_BMP *bmp){	
	if(bmp->fmt == AGIDL_RGB_888 || bmp->fmt == AGIDL_BGR_888 || bmp->fmt == AGIDL_RGBA_8888 || bmp->fmt == AGIDL_ARGB_8888){
		bmp->pixels.pix16 = (COLOR16*)malloc(sizeof(COLOR16)*(AGIDL_BMPGetHeight(bmp)*AGIDL_BMPGetWidth(bmp)));
		AGIDL_24BPPTO16BPP(bmp->pixels.pix32,bmp->pixels.pix16,AGIDL_BMPGetWidth(bmp),AGIDL_BMPGetHeight(bmp),&bmp->fmt);
		free(bmp->pixels.pix32);
	}
}

void AGIDL_BMP555TO565(AGIDL_BMP* bmp){
	AGIDL_555TO565(bmp->pixels.pix16,AGIDL_BMPGetWidth(bmp),AGIDL_BMPGetHeight(bmp),&bmp->fmt);
}

void AGIDL_BMP565TO555(AGIDL_BMP* bmp){
	AGIDL_565TO555(bmp->pixels.pix16,AGIDL_BMPGetWidth(bmp),AGIDL_BMPGetHeight(bmp),&bmp->fmt);
}

COLOR AGIDL_BMPGetClr(AGIDL_BMP *bmp, int x, int y){
	if(x >= 0 && y >= 0 && x < AGIDL_BMPGetWidth(bmp) && y < AGIDL_BMPGetHeight(bmp)){
		return bmp->pixels.pix32[x+y*AGIDL_BMPGetWidth(bmp)];
	}
}

COLOR16 AGIDL_BMPGetClr16(AGIDL_BMP *bmp, int x, int y){
	if(x >= 0 && y >= 0 && x < AGIDL_BMPGetWidth(bmp) && y < AGIDL_BMPGetHeight(bmp)){
		return bmp->pixels.pix16[x+y*AGIDL_BMPGetWidth(bmp)];
	}
}

void AGIDL_BMPSyncPix(AGIDL_BMP *bmp, COLOR *clrs){
	AGIDL_ClrMemcpy(bmp->pixels.pix32,clrs,AGIDL_BMPGetSize(bmp));
}

void AGIDL_BMPSyncPix16(AGIDL_BMP *bmp, COLOR16 *clrs){
	AGIDL_ClrMemcpy16(bmp->pixels.pix16,clrs,AGIDL_BMPGetSize(bmp));
}

void AGIDL_FreeBMP(AGIDL_BMP *bmp){
	free(bmp);
	if(bmp != NULL){
		bmp = NULL;
	}
}

int AGIDL_BMPGetWidth(AGIDL_BMP *bmp){
	return bmp->header.width;
}

int AGIDL_BMPGetHeight(AGIDL_BMP *bmp){
	return bmp->header.height;
}

u32 AGIDL_BMPGetSize(AGIDL_BMP* bmp){
	return AGIDL_BMPGetWidth(bmp) * AGIDL_BMPGetHeight(bmp);
}

u16 AGIDL_BMPGetMaxDiff(AGIDL_BMP *bmp){
	return bmp->max_diff;
}

AGIDL_CLR_FMT AGIDL_BMPGetClrFmt(AGIDL_BMP* bmp){
	return bmp->fmt;
}

BMP_IMG_TYPE AGIDL_BMPGetImgType(int bits){
	switch(bits){
		case 4:{
			return BMP_IMG_TYPE_ICP_16;
		}break;
		case 8:{
			return BMP_IMG_TYPE_ICP_256;
		}break;
		case 16:{
			return BMP_IMG_TYPE_HIGH_CLR;
		}break;
		case 24:{
			return BMP_IMG_TYPE_TRUE_CLR;
		}break;
		case 32:{
			return BMP_IMG_TYPE_DEEP_CLR;
		}break;
		case 1:{
			return BMP_IMG_TYPE_RLE;
		}break;
	}
}

void AGIDL_BMPEncodeICP(AGIDL_BMP* bmp, FILE* file){
	int pass = 0;
	u8 pal_index = 0;
	
	AGIDL_InitICP(&bmp->palette, AGIDL_ICP_256);
	
	int x,y;
	for(y = 0; y < AGIDL_BMPGetHeight(bmp); y++){
		for(x = 0; x < AGIDL_BMPGetWidth(bmp); x++){
			COLOR clr = AGIDL_BMPGetClr(bmp,x,y);
			
			if(AGIDL_GetBitCount(AGIDL_BMPGetClrFmt(bmp)) == 32){
				u8 r = AGIDL_GetR(clr,AGIDL_BMPGetClrFmt(bmp));
				u8 g = AGIDL_GetG(clr,AGIDL_BMPGetClrFmt(bmp));
				u8 b = AGIDL_GetB(clr,AGIDL_BMPGetClrFmt(bmp));
				clr = AGIDL_RGB(r,g,b,AGIDL_BGR_888);
				AGIDL_AddColorICP(&bmp->palette,pal_index,clr,AGIDL_BGR_888,AGIDL_BMPGetMaxDiff(bmp),&pass);
			}
			else{
				AGIDL_AddColorICP(&bmp->palette,pal_index,clr,bmp->fmt,AGIDL_BMPGetMaxDiff(bmp),&pass);
			}
			
			if(pass == 1 && pal_index < 256){
				pal_index++;
			}
			
			pass = 0;
		}
	}
	
	int i;
	for(i = 0; i < 256; i++){
		COLOR clr = bmp->palette.icp.palette_256[i];
		AGIDL_ExtractAndPrintRGB(file,clr,AGIDL_RGB_888);
		u8 pad = 0;
		fwrite(&pad,1,1,file);
	}
}

void AGIDL_BMPEncodeRLE(AGIDL_BMP* bmp, FILE* file){
	int x,y;
	for(y = 0; y < AGIDL_BMPGetHeight(bmp); y++){
		for(x = 0; x < AGIDL_BMPGetWidth(bmp); x++){
			COLOR clr = AGIDL_BMPGetClr(bmp,x,y);

			u32 count = AGIDL_EncodeRLE(bmp->pixels.pix32,24,x,y,AGIDL_BMPGetWidth(bmp),AGIDL_BMPGetHeight(bmp),AGIDL_BMPGetWidth(bmp));
			
			x += count - 1;
			
			u8 index;
			if(AGIDL_GetBitCount(AGIDL_BMPGetClrFmt(bmp)) == 32){
				u8 r = AGIDL_GetR(clr,AGIDL_BMPGetClrFmt(bmp));
				u8 g = AGIDL_GetG(clr,AGIDL_BMPGetClrFmt(bmp));
				u8 b = AGIDL_GetB(clr,AGIDL_BMPGetClrFmt(bmp));
				clr = AGIDL_RGB(r,g,b,AGIDL_BGR_888);
				index = AGIDL_FindClosestColor(bmp->palette,clr,AGIDL_BGR_888,AGIDL_BMPGetMaxDiff(bmp));			
			}
			else{
				index = AGIDL_FindClosestColor(bmp->palette,clr,bmp->fmt,AGIDL_BMPGetMaxDiff(bmp));
			}
			

			fwrite(&count,1,1,file);
			fwrite(&index,1,1,file);
			
			if(x == AGIDL_BMPGetWidth(bmp)-1){
				if(y == AGIDL_BMPGetHeight(bmp)-1){
					u8 zero = 0, one = 1;
					fwrite(&zero,1,1,file);
					fwrite(&one,1,1,file);
				}
				u16 zero = 0;
				fwrite(&zero,2,1,file);
				break;
			}
		}
	}
}

void AGIDL_BMPEncodeIMG(AGIDL_BMP* bmp, FILE* file){
	int padding = 0;
	int pad = AGIDL_BMPGetWidth(bmp) % 4;
	int x,y;
	for(y = 0; y < AGIDL_BMPGetHeight(bmp); y++){
		for(x = 0; x < AGIDL_BMPGetWidth(bmp); x++){
			COLOR clr = AGIDL_BMPGetClr(bmp,x,y);
			
			u8 index;
			if(AGIDL_GetBitCount(AGIDL_BMPGetClrFmt(bmp)) == 32){
				u8 r = AGIDL_GetR(clr,AGIDL_BMPGetClrFmt(bmp));
				u8 g = AGIDL_GetG(clr,AGIDL_BMPGetClrFmt(bmp));
				u8 b = AGIDL_GetB(clr,AGIDL_BMPGetClrFmt(bmp));
				clr = AGIDL_RGB(r,g,b,AGIDL_BGR_888);
				index = AGIDL_FindClosestColor(bmp->palette,clr,AGIDL_BGR_888,AGIDL_BMPGetMaxDiff(bmp));
			}
			else{
			    index = AGIDL_FindClosestColor(bmp->palette,clr,bmp->fmt,AGIDL_BMPGetMaxDiff(bmp));
			}
			fwrite(&index,1,1,file);
		}
		if(!(pad) == 0){
			fwrite(&padding,pad,1,file);
		}
	}
}

void AGIDL_BMPEncodeIMG0(AGIDL_BMP* bmp, FILE* file){
	switch(bmp->fmt){
		case AGIDL_BGR_888:{
			int padding = 0;
			int pad = AGIDL_BMPGetWidth(bmp) % 4;
			
			int x,y;
			for(y = 0; y < AGIDL_BMPGetHeight(bmp); y++){
				for(x = 0; x < AGIDL_BMPGetWidth(bmp); x++){
					COLOR clr = AGIDL_BMPGetClr(bmp,x,y);
					AGIDL_ExtractAndPrintBGR(file,clr,AGIDL_BGR_888);
				}
				if(!(pad) == 0){
					fwrite(&padding,pad,1,file);
				}
			}
		}break;
		case AGIDL_RGB_555:{
			int x,y;
			for(y = 0; y <= AGIDL_BMPGetHeight(bmp); y++){
				for(x = 0; x < AGIDL_BMPGetWidth(bmp); x++){
					COLOR16 clr = AGIDL_BMPGetClr16(bmp,x,y);
					AGIDL_ExtractAndPrintRGB(file,clr,AGIDL_RGB_555);
				}
			}
		}break;
		case AGIDL_RGBA_8888:{
			int x,y;
			for(y = 0; y < AGIDL_BMPGetHeight(bmp); y++){
				for(x = 0; x < AGIDL_BMPGetWidth(bmp); x++){
					COLOR clr = AGIDL_BMPGetClr(bmp,x,y);
					AGIDL_ExtractAndPrintRGBA(file,clr,AGIDL_RGBA_8888);
				}
			}
		}break;
	}
}

void AGIDL_BMPDecodeHeader(AGIDL_BMP* bmp, FILE* file){
	fread(&bmp->header.magic,2,1,file);
	
	if(bmp->header.magic != 0x4d42){
		printf("Image file is not a proper .BMP -> %s!\n",bmp->filename);
	}
	
	fread(&bmp->header.file_size,4,1,file);
	fread(&bmp->header.reserved1,2,1,file);
	fread(&bmp->header.reserved2,2,1,file);
	fread(&bmp->header.offset,4,1,file);
	fread(&bmp->header.header_size,4,1,file);
	fread(&bmp->header.width,4,1,file);
	fread(&bmp->header.height,4,1,file);
	fread(&bmp->header.num_of_planes,2,1,file);
	fread(&bmp->header.bits,2,1,file);
	fread(&bmp->header.compress,4,1,file);
	fread(&bmp->header.img_size,4,1,file);
	fread(&bmp->header.x_resolution,4,1,file);
	fread(&bmp->header.y_resolution,4,1,file);
	fread(&bmp->header.num_of_colors,4,1,file);
	fread(&bmp->header.important_colors,4,1,file);
}

void AGIDL_BMPDecodeIMG(AGIDL_BMP* bmp, FILE* file, BMP_IMG_TYPE img_type){
	if(bmp->header.compress != 1 && bmp->header.compress != 2){
		switch(img_type){
			case BMP_IMG_TYPE_TRUE_CLR:{
				AGIDL_BMPSetClrFmt(bmp,AGIDL_BGR_888);
				int padding = bmp->header.width % 4;
					
				bmp->pixels.pix32 = (COLOR*)malloc(sizeof(COLOR)*(AGIDL_BMPGetSize(bmp)));
				
				int x,y;
				for(y = 0; y < AGIDL_BMPGetHeight(bmp); y++){
					for(x = 0; x < AGIDL_BMPGetWidth(bmp); x++){
						u8 r,g,b;
						fread(&b,1,1,file);
						fread(&g,1,1,file);
						fread(&r,1,1,file);
						COLOR clr = AGIDL_RGB(r,g,b,bmp->fmt);
						AGIDL_BMPSetClr(bmp,x,y,clr);
					}
					fseek(file,padding,SEEK_CUR);
				}
			}break;
			case BMP_IMG_TYPE_HIGH_CLR:{
				AGIDL_BMPSetClrFmt(bmp,AGIDL_RGB_555);
				
				bmp->pixels.pix16 = (COLOR16*)malloc(sizeof(COLOR16)*(AGIDL_BMPGetWidth(bmp)*AGIDL_BMPGetHeight(bmp)));
			
				int x,y;
				for(y = 0; y < AGIDL_BMPGetHeight(bmp); y++){
					for(x = 0; x < AGIDL_BMPGetWidth(bmp); x++){
						COLOR16 clr = 0;
						fread(&clr,2,1,file);
						AGIDL_BMPSetClr16(bmp,x,y,clr);
					}
				}
			}break;
			case BMP_IMG_TYPE_DEEP_CLR:{
				AGIDL_BMPSetClrFmt(bmp,AGIDL_RGBA_8888);
				
				bmp->pixels.pix32 = (COLOR*)malloc(sizeof(COLOR)*(AGIDL_BMPGetWidth(bmp)*AGIDL_BMPGetHeight(bmp)));
				
				int x,y;
				for(y = 0; y < AGIDL_BMPGetHeight(bmp); y++){
					for(x = 0; x < AGIDL_BMPGetWidth(bmp); x++){
						u8 r,g,b,a;
						fread(&b,1,1,file);
						fread(&g,1,1,file);
						fread(&r,1,1,file);
						fread(&a,1,1,file);
						COLOR clr = AGIDL_RGBA(b,g,r,a,AGIDL_RGBA_8888);
						AGIDL_BMPSetClr(bmp,x,y,clr);
					}
				}
			}break;
			case BMP_IMG_TYPE_ICP_256:{
				AGIDL_BMPSetClrFmt(bmp,AGIDL_RGB_888);
				
					int pad = AGIDL_BMPGetWidth(bmp) % 4;
				
					bmp->pixels.pix32 = (COLOR*)malloc(sizeof(COLOR)*(AGIDL_BMPGetWidth(bmp)*AGIDL_BMPGetHeight(bmp)));
					
					if(bmp->header.num_of_colors != 256){
						int i;
						for(i = 0; i < bmp->header.num_of_colors; i++){
							COLOR clr = 0;
							u8 r,g,b;
							fread(&b,1,1,file);
							fread(&g,1,1,file);
							fread(&r,1,1,file);
							clr = AGIDL_RGB(r,g,b,bmp->fmt);
							bmp->palette.icp.palette_256[i] = clr;
							fseek(file,1,SEEK_CUR);
						}
						
						int x,y;
						for(y = 0; y < AGIDL_BMPGetHeight(bmp); y++){
							for(x = 0; x < AGIDL_BMPGetWidth(bmp); x++){
								u8 index;
								fread(&index,1,1,file);
								AGIDL_BMPSetClr(bmp,x,y,bmp->palette.icp.palette_256[index]);
							}
							if(pad){
								fseek(file,pad,SEEK_CUR);
							}
						}
					}
					else{
						int i;
						for(i = 0; i < 256; i++){
							COLOR clr = 0;
							u8 r,g,b;
							fread(&b,1,1,file);
							fread(&g,1,1,file);
							fread(&r,1,1,file);
							clr = AGIDL_RGB(r,g,b,bmp->fmt);
							bmp->palette.icp.palette_256[i] = clr;
							fseek(file,1,SEEK_CUR);
						}
						
						int x,y;
						for(y = 0; y < AGIDL_BMPGetHeight(bmp); y++){
							for(x = 0; x < AGIDL_BMPGetWidth(bmp); x++){
								u8 index;
								fread(&index,1,1,file);
								AGIDL_BMPSetClr(bmp,x,y,bmp->palette.icp.palette_256[index]);
							}
							if(pad){
								fseek(file,pad,SEEK_CUR);
							}
						}
					}
			}break;
			case BMP_IMG_TYPE_ICP_16:{
				AGIDL_BMPSetClrFmt(bmp,AGIDL_RGB_888);
				
				int pad = AGIDL_BMPGetWidth(bmp) % 4;
				
				bmp->pixels.pix32 = (COLOR*)malloc(sizeof(COLOR)*(AGIDL_BMPGetWidth(bmp)*AGIDL_BMPGetHeight(bmp)));
				
				if(bmp->header.num_of_colors != 16){
					int i;
					for(i = 0; i < bmp->header.num_of_colors; i++){
						COLOR clr = 0;
						u8 r,g,b;
						fread(&b,1,1,file);
						fread(&g,1,1,file);
						fread(&r,1,1,file);
						clr = AGIDL_RGB(r,g,b,bmp->fmt);
						bmp->palette.icp.palette_16[i] = clr;
						fseek(file,1,SEEK_CUR);
					}
					
					int x,y;
					for(y = 0; y < AGIDL_BMPGetHeight(bmp); y++){
						for(x = 0; x < AGIDL_BMPGetWidth(bmp); x++){
							u8 index;
							fread(&index,1,1,file);
							AGIDL_BMPSetClr(bmp,x,y,bmp->palette.icp.palette_16[index]);
						}
						if(pad){
							fseek(file,pad,SEEK_CUR);
						}
					}
				}
				else{
					int i;
					for(i = 0; i < 16; i++){
						COLOR clr = 0;
						u8 r,g,b;
						fread(&b,1,1,file);
						fread(&g,1,1,file);
						fread(&r,1,1,file);
						clr = AGIDL_RGB(r,g,b,bmp->fmt);
						bmp->palette.icp.palette_16[i] = clr;
						fseek(file,1,SEEK_CUR);
					}
					
					int x,y;
					for(y = 0; y < AGIDL_BMPGetHeight(bmp); y++){
						for(x = 0; x < AGIDL_BMPGetWidth(bmp); x++){
							u8 index;
							fread(&index,1,1,file);
							AGIDL_BMPSetClr(bmp,x,y,bmp->palette.icp.palette_16[index]);
						}
						if(pad){
							fseek(file,pad,SEEK_CUR);
						}
					}
				}
			}break;
		}
	}
}

void AGIDL_BMPDecodeRLE(AGIDL_BMP* bmp, FILE* file, BMP_IMG_TYPE img_type){
	if(bmp->header.compress){
		switch(img_type){
			case BMP_IMG_TYPE_ICP_256:{
				AGIDL_BMPSetClrFmt(bmp,AGIDL_RGB_888);
				int i;
				for(i = 0; i < bmp->header.num_of_colors; i++){
					COLOR clr = 0;
					u8 r,g,b;
					fread(&b,1,1,file);
					fread(&g,1,1,file);
					fread(&r,1,1,file);
					clr = AGIDL_RGB(r,g,b,bmp->fmt);
					bmp->palette.icp.palette_256[i] = clr;
					fseek(file,1,SEEK_CUR);
				}
				
				if(img_type == BMP_IMG_TYPE_ICP_256){
					bmp->pixels.pix32 = (COLOR*)malloc(sizeof(COLOR)*(AGIDL_BMPGetWidth(bmp)*(AGIDL_BMPGetHeight(bmp))));
					
					int x,y;
					for(y = 0; y < AGIDL_BMPGetHeight(bmp); y++){
						for(x = 0; x < AGIDL_BMPGetWidth(bmp); x++){
							u8 rle, index;
							fread(&rle,1,1,file);
							fread(&index,1,1,file);
							
							int i;
							for(i = 0; i < rle; i++){
								AGIDL_BMPSetClr(bmp,x+i,y,bmp->palette.icp.palette_256[index]);
							}
							
							x += rle - 1;
							
							if(x == AGIDL_BMPGetWidth(bmp) && rle != 0 && index != 0){
								fread(&rle,1,1,file);
								fread(&index,1,1,file);
								
								if(rle == 0 && index == 0){
									break;
								}
							}
							
						}
					}
				}
			}break;
			case BMP_IMG_TYPE_ICP_16:{
				AGIDL_BMPSetClrFmt(bmp,AGIDL_RGB_888);
				
				int i;
				for(i = 0; i < bmp->header.num_of_colors; i++){
					u8 r,g,b,blank;
					fread(&r,1,1,file);
					fread(&g,1,1,file);
					fread(&b,1,1,file);
					fread(&blank,1,1,file);
					bmp->palette.icp.palette_16[i] = AGIDL_RGB(r,g,b,AGIDL_BGR_888);
				}
				
				if(img_type == BMP_IMG_TYPE_ICP_16){
					bmp->pixels.pix32 = (COLOR*)malloc(sizeof(COLOR)*(AGIDL_BMPGetWidth(bmp)*(AGIDL_BMPGetHeight(bmp))));
					
					int x,y;
					for(y = 0; y < AGIDL_BMPGetHeight(bmp); y++){
						for(x = 0; x < AGIDL_BMPGetWidth(bmp); x++){
							u8 rle, index;
							fread(&rle,1,1,file);
							fread(&index,1,1,file);
				
							if(rle == 0 && index != 0){
								int i;
								for(i = 0; i < index / 2; i++){
									u8 ind;
									fread(&ind,1,1,file);
									
									u8 backind = (ind & 0xf) , frontind = ((ind & 0xff) >> 4);
									AGIDL_BMPSetClr(bmp,x+(i*2),y,bmp->palette.icp.palette_16[frontind]);
									AGIDL_BMPSetClr(bmp,x+((i*2)+1),y,bmp->palette.icp.palette_16[backind]);
								}
								
								x += index - 1;
							}
							else{
								if((index & 0xf) == ((index & 0xff) >> 4)){
								int i;
								for(i = 0; i < rle; i++){
									AGIDL_BMPSetClr(bmp,x+i,y,bmp->palette.icp.palette_16[index&0xf]);
								}
								
								x += rle - 1;
								
								if(x == AGIDL_BMPGetWidth(bmp) && rle != 0 && index != 0){
									fread(&rle,1,1,file);
									fread(&index,1,1,file);
									
									if(rle == 0 && index == 0){
										break;
									}
								}
							}
								else{
									u8 frontindex = (index & 0xff) >> 4, backindex = (index & 0xf);
									int i;
									for(i = 0; i < rle; i++){
										if((i % 2) == 0){	
											AGIDL_BMPSetClr(bmp,x+i,y,bmp->palette.icp.palette_16[frontindex]);
										}
										else{
											AGIDL_BMPSetClr(bmp,x+i,y,bmp->palette.icp.palette_16[backindex]);
										}
									}
									
									x += rle - 1;
									
									if(x == AGIDL_BMPGetWidth(bmp) && rle != 0 && index != 0){
										fread(&rle,1,1,file);
										fread(&index,1,1,file);
										
										if(rle == 0 && index == 0){
											break;
										}
									}
								}
							}								
						}
					}
				}
			}break;
		}
	}
}

AGIDL_BMP * AGIDL_LoadBMP(char* filename){
	AGIDL_BMP *bmp = (AGIDL_BMP*)malloc(sizeof(AGIDL_BMP));
	
	bmp->filename = (char*)malloc(strlen(filename)+1);
	AGIDL_FilenameCpy(bmp->filename,filename);
	
	FILE* file = fopen(filename,"rb");
	
	if(file == NULL){
		printf("Could not locate BMP file %s!\n",filename);
	}
	
	AGIDL_BMPDecodeHeader(bmp,file);
	
	BMP_IMG_TYPE img_type = AGIDL_BMPGetImgType(bmp->header.bits);
	
	AGIDL_BMPDecodeIMG(bmp,file,img_type);
	AGIDL_BMPDecodeRLE(bmp,file,img_type);
	
	fclose(file);
	
	return bmp;
}

AGIDL_BMP * AGIDL_CreateBMP(const char *filename, int width, int height, AGIDL_CLR_FMT fmt){
	AGIDL_BMP* bmp = (AGIDL_BMP*)malloc(sizeof(AGIDL_BMP));
	bmp->filename = (char*)malloc(strlen(filename)+1);
	AGIDL_FilenameCpy(bmp->filename,filename);
	AGIDL_BMPSetWidth(bmp,width);
	AGIDL_BMPSetHeight(bmp,height);
	AGIDL_BMPSetClrFmt(bmp,fmt);
	AGIDL_BMPSetICPMode(bmp,0);
	AGIDL_BMPSetCompression(bmp,0);
	AGIDL_BMPSetMaxDiff(bmp,7);
	
	if(fmt == AGIDL_RGB_888 || fmt == AGIDL_BGR_888 || fmt == AGIDL_RGBA_8888 || fmt == AGIDL_ARGB_8888){
		bmp->pixels.pix32 = (COLOR*)malloc(sizeof(COLOR)*(width*height));
	}
	
	if(fmt == AGIDL_RGB_555 || fmt == AGIDL_BGR_555 || fmt == AGIDL_RGB_565 || fmt == AGIDL_BGR_565){
		bmp->pixels.pix16 = (COLOR16*)malloc(sizeof(COLOR16)*(width*height));
	}
	
	return bmp;
}

AGIDL_BMP* AGIDL_BMPCpyImg(AGIDL_BMP* bmp){
	AGIDL_BMP* bmpcpy = AGIDL_CreateBMP("bmpcpy.bmp",AGIDL_BMPGetWidth(bmp),AGIDL_BMPGetHeight(bmp),bmp->fmt);
	AGIDL_BMPSetICPMode(bmpcpy,bmp->icp);
	AGIDL_BMPSetCompression(bmpcpy,bmp->compression);
	AGIDL_BMPSetMaxDiff(bmpcpy,AGIDL_BMPGetMaxDiff(bmp));
	if(bmp->fmt == AGIDL_RGB_888 || bmp->fmt == AGIDL_BGR_888 || bmp->fmt == AGIDL_RGBA_8888 || bmp->fmt == AGIDL_ARGB_8888){
		AGIDL_BMPSyncPix(bmpcpy,bmp->pixels.pix32);
	}
	
	if(bmp->fmt == AGIDL_RGB_555 || bmp->fmt == AGIDL_BGR_555 || bmp->fmt == AGIDL_RGB_565 || bmp->fmt == AGIDL_BGR_565){
		AGIDL_BMPSyncPix16(bmpcpy,bmp->pixels.pix16);
	}
	return bmpcpy;
}

void AGIDL_BMPEncodeHeader(AGIDL_BMP* bmp, FILE* file){
	fwrite(&bmp->header.magic,2,1,file);
	fwrite(&bmp->header.file_size,4,1,file);
	fwrite(&bmp->header.reserved1,2,1,file);
	fwrite(&bmp->header.reserved1,2,1,file);
	fwrite(&bmp->header.offset,4,1,file);
	fwrite(&bmp->header.header_size,4,1,file);
	fwrite(&bmp->header.width,4,1,file);
	fwrite(&bmp->header.height,4,1,file);
	fwrite(&bmp->header.num_of_planes,2,1,file);
	fwrite(&bmp->header.bits,2,1,file);
	fwrite(&bmp->header.compress,4,1,file);
	fwrite(&bmp->header.img_size,4,1,file);
	fwrite(&bmp->header.x_resolution,4,1,file);
	fwrite(&bmp->header.y_resolution,4,1,file);
	fwrite(&bmp->header.num_of_colors,4,1,file);
	fwrite(&bmp->header.important_colors,4,1,file);
}

void AGIDL_ExportBMP(AGIDL_BMP *bmp){
	FILE *file = fopen(bmp->filename,"wb");
	
	bmp->header.magic = 0x4d42;
	bmp->header.reserved1 = 0;
	bmp->header.reserved2 = 0;
	bmp->header.offset = 54;
	bmp->header.header_size = 40;
	
	if(bmp->fmt == AGIDL_RGB_888 || bmp->fmt == AGIDL_BGR_888){
		bmp->header.bits = 24;
		bmp->header.file_size = 54 + (AGIDL_BMPGetWidth(bmp) * AGIDL_BMPGetHeight(bmp) * 3);
	}
	
	if(bmp->fmt == AGIDL_RGB_555 || bmp->fmt == AGIDL_BGR_555 || bmp->fmt == AGIDL_RGB_565 || bmp->fmt == AGIDL_BGR_565){
		bmp->header.bits = 16;
		bmp->header.file_size = 54 + (AGIDL_BMPGetWidth(bmp) * AGIDL_BMPGetHeight(bmp) * 2);
	}
	
	if(bmp->fmt == AGIDL_RGBA_8888 || bmp->fmt == AGIDL_ARGB_8888){
		bmp->header.bits = 32;
		bmp->header.file_size = 54 + (AGIDL_BMPGetWidth(bmp) * AGIDL_BMPGetHeight(bmp) * 4);
	}
	
	bmp->header.compress = 0;
	bmp->header.img_size = (AGIDL_BMPGetWidth(bmp) * AGIDL_BMPGetHeight(bmp) * 3);
	bmp->header.x_resolution = 0;
	bmp->header.y_resolution = 0;
	bmp->header.num_of_colors = 0;
	bmp->header.important_colors = 0;
	bmp->header.num_of_planes = 1;
	
	if(bmp->icp == YES_ICP){
		bmp->header.bits = 8;
		bmp->header.num_of_colors = 256;
		bmp->header.important_colors = 256;
		bmp->header.offset = 54 + (256*4);
		bmp->header.file_size = 54 + (AGIDL_BMPGetWidth(bmp)*AGIDL_BMPGetHeight(bmp)) + (256*4);
		bmp->header.img_size = (AGIDL_BMPGetWidth(bmp)*AGIDL_BMPGetHeight(bmp));
	}
	
	if(bmp->compression == 1){
		bmp->header.bits = 8;
		bmp->header.compress = 1;
		bmp->header.num_of_colors = 256;
		bmp->header.important_colors = 256;
		bmp->header.offset = 54 + (256*4);
		bmp->header.file_size = 54 + (AGIDL_BMPGetWidth(bmp)*AGIDL_BMPGetHeight(bmp)) + (256*4);
		bmp->header.img_size = (AGIDL_BMPGetWidth(bmp)*AGIDL_BMPGetHeight(bmp));
	}
	
	if(bmp->compression != 1 && bmp->compression != 0){
		bmp->compression = 0;
	}
	
	AGIDL_BMPEncodeHeader(bmp,file);
	
	if(bmp->icp == YES_ICP){
		switch(bmp->fmt){
			case AGIDL_RGB_888:{
				AGIDL_BMPRGB2BGR(bmp);
				AGIDL_BMPEncodeICP(bmp,file);
				AGIDL_BMPEncodeIMG(bmp,file);
				AGIDL_BMPBGR2RGB(bmp);
			}break;
			case AGIDL_BGR_888:{
				AGIDL_BMPEncodeICP(bmp,file);
				AGIDL_BMPEncodeIMG(bmp,file);
			}break;
			case AGIDL_RGBA_8888:{
				AGIDL_BMPEncodeICP(bmp,file);
				AGIDL_BMPEncodeIMG(bmp,file);
			}break;
			case AGIDL_ARGB_8888:{
				AGIDL_BMPEncodeICP(bmp,file);
				AGIDL_BMPEncodeIMG(bmp,file);
			}break;
			case AGIDL_RGB_555:{	
				AGIDL_BMPConvert16BPPTO24BPP(bmp);
				AGIDL_BMPRGB2BGR(bmp);
				AGIDL_BMPEncodeICP(bmp,file);
				AGIDL_BMPEncodeIMG(bmp,file);
				AGIDL_BMPBGR2RGB(bmp);
				AGIDL_BMPConvert24BPPTO16BPP(bmp);	
			}break;
			case AGIDL_BGR_555:{
				AGIDL_BMPConvert16BPPTO24BPP(bmp);
				AGIDL_BMPEncodeICP(bmp,file);
				AGIDL_BMPEncodeIMG(bmp,file);
				AGIDL_BMPConvert24BPPTO16BPP(bmp);	
			}break;
			case AGIDL_RGB_565:{
				AGIDL_BMP565TO555(bmp);
				AGIDL_BMPConvert16BPPTO24BPP(bmp);
				AGIDL_BMPRGB2BGR(bmp);
				AGIDL_BMPEncodeICP(bmp,file);
				AGIDL_BMPEncodeIMG(bmp,file);
				AGIDL_BMPBGR2RGB(bmp);
				AGIDL_BMPConvert24BPPTO16BPP(bmp);
				AGIDL_BMP555TO565(bmp);
			}break;
			case AGIDL_BGR_565:{
				AGIDL_BMP565TO555(bmp);
				AGIDL_BMPConvert16BPPTO24BPP(bmp);
				AGIDL_BMPEncodeICP(bmp,file);
				AGIDL_BMPEncodeIMG(bmp,file);
				AGIDL_BMPConvert24BPPTO16BPP(bmp);
				AGIDL_BMP555TO565(bmp);
			}break;
		}
	}
	else if(!bmp->compression){
		switch(bmp->fmt){
			case AGIDL_BGR_888:{
				AGIDL_BMPEncodeIMG0(bmp,file);
			}break;
			case AGIDL_RGB_888:{
				AGIDL_BMPRGB2BGR(bmp);
				AGIDL_BMPEncodeIMG0(bmp,file);
				AGIDL_BMPBGR2RGB(bmp);
			}break;
			case AGIDL_RGB_555:{
				AGIDL_BMPEncodeIMG0(bmp,file);
			}break;
			case AGIDL_BGR_555:{
				AGIDL_BMPBGR2RGB(bmp);
				AGIDL_BMPEncodeIMG0(bmp,file);
				AGIDL_BMPRGB2BGR(bmp);
			}break;
			case AGIDL_RGB_565:{
				AGIDL_BMP565TO555(bmp);
				AGIDL_BMPEncodeIMG0(bmp,file);
				AGIDL_BMP555TO565(bmp);
			}break;
			case AGIDL_BGR_565:{
				AGIDL_BMP565TO555(bmp);
				AGIDL_BMPBGR2RGB(bmp);
				AGIDL_BMPEncodeIMG0(bmp,file);
				AGIDL_BMPRGB2BGR(bmp);
				AGIDL_BMP555TO565(bmp);
			}break;
			case AGIDL_RGBA_8888:{
				AGIDL_BMPEncodeIMG0(bmp,file);
			}break;
			case AGIDL_ARGB_8888:{
				int x,y;
				for(y = 0; y < AGIDL_BMPGetHeight(bmp); y++){
					for(x = 0; x < AGIDL_BMPGetWidth(bmp); x++){
						COLOR clr = AGIDL_BMPGetClr(bmp,x,y);
						AGIDL_ExtractAndPrintRGBA(file,clr,AGIDL_ARGB_8888);
					}
				}
			}break;
		}
	}
	else{
		switch(bmp->fmt){
			case AGIDL_RGB_888:{
				AGIDL_BMPBGR2RGB(bmp);
				AGIDL_BMPEncodeICP(bmp,file);
				AGIDL_BMPEncodeRLE(bmp,file);
				AGIDL_BMPRGB2BGR(bmp);
			}break;
			case AGIDL_BGR_888:{
				AGIDL_BMPEncodeICP(bmp,file);
				AGIDL_BMPEncodeRLE(bmp,file);
			}break;
			case AGIDL_RGBA_8888:{
				AGIDL_BMPEncodeICP(bmp,file);
				AGIDL_BMPEncodeRLE(bmp,file);
			}break;
			case AGIDL_ARGB_8888:{
				AGIDL_BMPEncodeICP(bmp,file);
				AGIDL_BMPEncodeRLE(bmp,file);
			}break;
			case AGIDL_RGB_555:{
				AGIDL_BMPRGB2BGR(bmp);
				AGIDL_BMPConvert16BPPTO24BPP(bmp);
				AGIDL_BMPEncodeICP(bmp,file);
				AGIDL_BMPEncodeRLE(bmp,file);
				AGIDL_BMPConvert24BPPTO16BPP(bmp);
				AGIDL_BMPBGR2RGB(bmp);
			}break;
			case AGIDL_BGR_555:{
				AGIDL_BMPConvert16BPPTO24BPP(bmp);
				AGIDL_BMPEncodeICP(bmp,file);
				AGIDL_BMPEncodeRLE(bmp,file);
				AGIDL_BMPConvert24BPPTO16BPP(bmp);
			}break;
			case AGIDL_RGB_565:{
				AGIDL_BMP565TO555(bmp);
				AGIDL_BMPRGB2BGR(bmp);
				AGIDL_BMPConvert16BPPTO24BPP(bmp);
				AGIDL_BMPEncodeICP(bmp,file);
				AGIDL_BMPEncodeRLE(bmp,file);
				AGIDL_BMPConvert24BPPTO16BPP(bmp);
				AGIDL_BMPBGR2RGB(bmp);
				AGIDL_BMP555TO565(bmp);
			}break;
			case AGIDL_BGR_565:{
				AGIDL_BMP565TO555(bmp);
				AGIDL_BMPConvert16BPPTO24BPP(bmp);
				AGIDL_BMPEncodeICP(bmp,file);
				AGIDL_BMPEncodeRLE(bmp,file);
				AGIDL_BMPConvert24BPPTO16BPP(bmp);
				AGIDL_BMP555TO565(bmp);
			}break;
		}
	}
	
	fclose(file);
}