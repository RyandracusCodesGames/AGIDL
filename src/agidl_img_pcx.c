#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agidl_img_pcx.h"
#include "agidl_cc_core.h"
#include "agidl_img_compression.h"
#include "agidl_img_error.h"

/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023-2024 Ryandracus Chapman
*
*   Library: libagidl
*   File: agidl_img_pcx.c
*   Date: 9/25/2023
*   Version: 0.1b
*   Updated: 1/19/2024
*   Author: Ryandracus Chapman
*
********************************************/

void AGIDL_SetPCXFilename(AGIDL_PCX *pcx, const char* filename){
	pcx->filename = (char*)realloc(pcx->filename,strlen(filename));
	AGIDL_FilenameCpy(pcx->filename,filename);
}

void AGIDL_PCXSetWidth(AGIDL_PCX *pcx, int width){
	pcx->header.width = width;
}

void AGIDL_PCXSetHeight(AGIDL_PCX *pcx, int height){
	pcx->header.height = height;
}

void AGIDL_PCXSetClrFmt(AGIDL_PCX *pcx, AGIDL_CLR_FMT fmt){
	pcx->fmt = fmt;
}

void AGIDL_PCXSetICPMode(AGIDL_PCX *pcx, int mode){
	pcx->icp = mode;
}

void AGIDL_PCXSetMaxDiff(AGIDL_PCX* pcx, int max_diff){
	pcx->max_diff = max_diff;
}

void AGIDL_PCXSetClr(AGIDL_PCX *pcx, int x, int y, COLOR clr){
	if(AGIDL_GetBitCount(AGIDL_PCXGetClrFmt(pcx)) != 16){
		AGIDL_SetClr(pcx->pixels.pix32,clr,x,y,AGIDL_PCXGetWidth(pcx),AGIDL_PCXGetHeight(pcx));
	}
	else{
		AGIDL_SetClr16(pcx->pixels.pix16,AGIDL_CLR_TO_CLR16(clr,AGIDL_BGR_888,AGIDL_PCXGetClrFmt(pcx)),x,y,AGIDL_PCXGetWidth(pcx),AGIDL_PCXGetHeight(pcx));
	}
}

void AGIDL_PCXSetClr16(AGIDL_PCX *pcx, int x, int y, COLOR16 clr){
	if(AGIDL_GetBitCount(AGIDL_PCXGetClrFmt(pcx) == 16)){
		AGIDL_SetClr16(pcx->pixels.pix16,clr,x,y,AGIDL_PCXGetWidth(pcx),AGIDL_PCXGetHeight(pcx));
	}
	else{
		AGIDL_SetClr(pcx->pixels.pix32,AGIDL_CLR16_TO_CLR(clr,AGIDL_RGB_555,AGIDL_PCXGetClrFmt(pcx)),x,y,AGIDL_PCXGetWidth(pcx),AGIDL_PCXGetHeight(pcx));
	}
}

void AGIDL_PCXSetRGB(AGIDL_PCX *pcx, int x, int y, u8 r, u8 g, u8 b){
	switch(AGIDL_GetBitCount(AGIDL_PCXGetClrFmt(pcx))){
		case 24:{
			AGIDL_PCXSetClr(pcx,x,y,AGIDL_RGB(r,g,b,AGIDL_PCXGetClrFmt(pcx)));
		}break;
		case 16:{
			AGIDL_PCXSetClr16(pcx,x,y,AGIDL_RGB16(r,g,b,AGIDL_PCXGetClrFmt(pcx)));
		}break;
		case 32:{
			AGIDL_PCXSetClr(pcx,x,y,AGIDL_RGBA(r,g,b,0xff,AGIDL_PCXGetClrFmt(pcx)));
		}break;
	}
}

void AGIDL_ClearPCX(AGIDL_PCX *pcx, COLOR clr){
	if(AGIDL_GetBitCount(AGIDL_PCXGetClrFmt(pcx)) != 16){
		AGIDL_ClrMemset(pcx->pixels.pix32,clr,AGIDL_PCXGetSize(pcx));
	}
	else{
		AGIDL_ClrMemset16(pcx->pixels.pix16,(COLOR16)clr,AGIDL_PCXGetSize(pcx));
	}
}

void AGIDL_ClearPCX16(AGIDL_PCX *pcx, COLOR16 clr){
	if(AGIDL_GetBitCount(AGIDL_PCXGetClrFmt(pcx)) == 16){
		AGIDL_ClrMemset16(pcx->pixels.pix16,clr,AGIDL_PCXGetSize(pcx));
	}
	else{
		AGIDL_ClrMemset(pcx->pixels.pix32,AGIDL_CLR16_TO_CLR(clr,AGIDL_RGB_555,AGIDL_PCXGetClrFmt(pcx)),AGIDL_PCXGetSize(pcx));
	}
}

void AGIDL_ClearColorPCX(AGIDL_PCX* pcx, float r, float g, float b){
	if(AGIDL_GetBitCount(AGIDL_PCXGetClrFmt(pcx)) == 16){
		AGIDL_ClearColorBuffer(pcx->pixels.pix16,r,g,b,AGIDL_PCXGetClrFmt(pcx),AGIDL_PCXGetSize(pcx));
	}
	else{
		AGIDL_ClearColorBuffer(pcx->pixels.pix32,r,g,b,AGIDL_PCXGetClrFmt(pcx),AGIDL_PCXGetSize(pcx));
	}
}

void AGIDL_FlushPCX(AGIDL_PCX* pcx){
	AGIDL_ClearPCX(pcx,0);
}

void AGIDL_PCXSyncPix(AGIDL_PCX *pcx, COLOR *clrs){
	if(AGIDL_GetBitCount(AGIDL_PCXGetClrFmt(pcx)) != 16){
		AGIDL_ClrMemcpy(pcx->pixels.pix32,clrs,AGIDL_PCXGetSize(pcx));
	}
}

void AGIDL_PCXSyncPix16(AGIDL_PCX *pcx, COLOR16 *clrs){
	if(AGIDL_GetBitCount(AGIDL_PCXGetClrFmt(pcx)) == 16){
		AGIDL_ClrMemcpy16(pcx->pixels.pix16,clrs,AGIDL_PCXGetSize(pcx));
	}
}

void AGIDL_PCXCopyPix(AGIDL_PCX* pcx, COLOR* clrs, u32 count){
	if(AGIDL_GetBitCount(AGIDL_PCXGetClrFmt(pcx)) != 16){
		AGIDL_ClrMemcpy(pcx->pixels.pix32,clrs,count);
	}
}

void AGIDL_PCXCopyPix16(AGIDL_PCX* pcx, COLOR16* clrs, u32 count){
	if(AGIDL_GetBitCount(AGIDL_PCXGetClrFmt(pcx)) == 16){
		AGIDL_ClrMemcpy16(pcx->pixels.pix16,clrs,count);
	}
}

int AGIDL_PCXGetWidth(AGIDL_PCX *pcx){
	return pcx->header.width;
}

int AGIDL_PCXGetHeight(AGIDL_PCX *pcx){
	return pcx->header.height;
}

u32 AGIDL_PCXGetSize(AGIDL_PCX* pcx){
	return AGIDL_PCXGetWidth(pcx) * AGIDL_PCXGetHeight(pcx);
}

int AGIDL_PCXGetMaxDiff(AGIDL_PCX* pcx){
	return pcx->max_diff;
}

AGIDL_CLR_FMT AGIDL_PCXGetClrFmt(AGIDL_PCX *pcx){
	return pcx->fmt;
}

COLOR AGIDL_PCXGetClr(AGIDL_PCX *pcx, int x, int y){
	if(x >= 0 && y >= 0 && x < AGIDL_PCXGetWidth(pcx) && y < AGIDL_PCXGetHeight(pcx)){
		return pcx->pixels.pix32[x+y*AGIDL_PCXGetWidth(pcx)];
	}
}

COLOR16 AGIDL_PCXGetClr16(AGIDL_PCX *pcx, int x, int y){
	if(x >= 0 && y >= 0 && x < AGIDL_PCXGetWidth(pcx) && y < AGIDL_PCXGetHeight(pcx)){
		return pcx->pixels.pix16[x+y*AGIDL_PCXGetWidth(pcx)];
	}
}

void AGIDL_FreePCX(AGIDL_PCX *pcx){
	free(pcx->filename);
	
	if(AGIDL_GetBitCount(AGIDL_PCXGetClrFmt(pcx)) == 16){
		free(pcx->pixels.pix16);
	}
	else{
		free(pcx->pixels.pix32);
	}
	
	free(pcx);
	
	if(pcx != NULL){
		pcx = NULL;
	}
}

void AGIDL_PCXRGB2BGR(AGIDL_PCX *pcx){
	if(pcx->fmt == AGIDL_RGB_888){
		AGIDL_RGB2BGR(pcx->pixels.pix32,AGIDL_PCXGetWidth(pcx),AGIDL_PCXGetHeight(pcx),&pcx->fmt);
	}
	
	if(pcx->fmt == AGIDL_RGB_555){
		AGIDL_RGB2BGR16(pcx->pixels.pix16,AGIDL_PCXGetWidth(pcx),AGIDL_PCXGetHeight(pcx),&pcx->fmt);
	}
}

void AGIDL_PCXBGR2RGB(AGIDL_PCX *pcx){
	if(pcx->fmt == AGIDL_BGR_888){
		AGIDL_BGR2RGB(pcx->pixels.pix32,AGIDL_PCXGetWidth(pcx),AGIDL_PCXGetHeight(pcx),&pcx->fmt);
	}
	if(pcx->fmt == AGIDL_BGR_555){
		AGIDL_BGR2RGB16(pcx->pixels.pix16,AGIDL_PCXGetWidth(pcx),AGIDL_PCXGetHeight(pcx),&pcx->fmt);
	}
}

void AGIDL_PCXConvert16BPPTO24BPP(AGIDL_PCX *pcx){
	if(pcx->fmt == AGIDL_RGB_555 || pcx->fmt == AGIDL_BGR_555){
		pcx->pixels.pix32 = (COLOR*)malloc(sizeof(COLOR)*(AGIDL_PCXGetHeight(pcx)*AGIDL_PCXGetWidth(pcx)));
		AGIDL_16BPPTO24BPP(pcx->pixels.pix16,pcx->pixels.pix32,AGIDL_PCXGetWidth(pcx),AGIDL_PCXGetHeight(pcx),&pcx->fmt);
		free(pcx->pixels.pix16);
	}
}

void AGIDL_PCXConvert24BPPTO16BPP(AGIDL_PCX *pcx){
	if(pcx->fmt == AGIDL_RGB_888 || pcx->fmt == AGIDL_BGR_888 || pcx->fmt == AGIDL_RGBA_8888 || pcx->fmt == AGIDL_ARGB_8888){
		pcx->fmt = AGIDL_RGB_555;
		AGIDL_24BPPTO16BPP(pcx->pixels.pix32,pcx->pixels.pix16,AGIDL_PCXGetWidth(pcx),AGIDL_PCXGetHeight(pcx),&pcx->fmt);
		free(pcx->pixels.pix32);
	}
}

void AGIDL_PCXConvert555TO565(AGIDL_PCX *pcx){
	AGIDL_555TO565(pcx->pixels.pix16,AGIDL_PCXGetWidth(pcx),AGIDL_PCXGetHeight(pcx),&pcx->fmt);
}

void AGIDL_PCXConvert565TO555(AGIDL_PCX *pcx){
	AGIDL_565TO555(pcx->pixels.pix16,AGIDL_PCXGetWidth(pcx),AGIDL_PCXGetHeight(pcx),&pcx->fmt);
}

AGIDL_PCX * AGIDL_CreatePCX(const char *filename, int width, int height, AGIDL_CLR_FMT fmt){
	AGIDL_PCX *pcx = (AGIDL_PCX*)malloc(sizeof(AGIDL_PCX));
	pcx->filename = (char*)malloc(strlen(filename)+1);
	AGIDL_FilenameCpy(pcx->filename,filename);
	AGIDL_PCXSetWidth(pcx,width);
	AGIDL_PCXSetHeight(pcx,height);
	AGIDL_PCXSetMaxDiff(pcx,15);
	AGIDL_PCXSetClrFmt(pcx,fmt);
	
	if(fmt == AGIDL_RGB_888 || fmt == AGIDL_BGR_888 || fmt == AGIDL_RGBA_8888 || fmt == AGIDL_ARGB_8888){
		pcx->pixels.pix32 = (COLOR*)malloc(sizeof(COLOR)*(width*height));
	}
	
	if(fmt == AGIDL_RGB_555 || fmt == AGIDL_BGR_555 || fmt == AGIDL_RGB_565 || fmt == AGIDL_BGR_565){
		pcx->pixels.pix16 = (COLOR16*)malloc(sizeof(COLOR16)*(width*height));
	}
	return pcx;
}

AGIDL_PCX* AGIDL_PCXCpyImg(AGIDL_PCX* pcx){
	AGIDL_PCX* pcxcpy = AGIDL_CreatePCX("pcxcpy.pcx",AGIDL_PCXGetWidth(pcx),AGIDL_PCXGetHeight(pcx),pcx->fmt);
	AGIDL_PCXSetICPMode(pcxcpy,pcx->icp);
	if(pcx->fmt == AGIDL_RGB_888 || pcx->fmt == AGIDL_BGR_888 || pcx->fmt == AGIDL_RGBA_8888 || pcx->fmt == AGIDL_ARGB_8888){
		AGIDL_PCXSyncPix(pcxcpy,pcx->pixels.pix32);
	}
	
	if(pcx->fmt == AGIDL_RGB_555 || pcx->fmt == AGIDL_BGR_555 || pcx->fmt == AGIDL_RGB_565 || pcx->fmt == AGIDL_BGR_565){
		AGIDL_PCXSyncPix16(pcxcpy,pcx->pixels.pix16);
	}
	return pcxcpy;
}

u16 binmul[9] = {1,2,4,8,16,32,64,128,256};

u16 bin2dec(char *binary){
	u16 accumulation = 0;
	int i, count = 0;
	for(i = strlen(binary)-1; i >= 0; i--){
		int bin;
		if(binary[i] == '0'){
			bin = 0;
		}
		if(binary[i] == '1'){
			bin = 1;
		}
		accumulation += binmul[count] * bin;
		count++;
	}
	return accumulation;
}

char* dec2bin(u16 number){
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

char* pcxrlebits(char *binary){
	char *bin = (char*)malloc(sizeof(char)*7);
	int i;
	for(i = 2; i <= 7; i++){
		bin[i-2] = binary[i];
	}
	bin[6] = '\0';
	return bin;
}

u16 little_endianify(u16 number){
	u8 lsb = (number & 0xff);
	u8 msb = (number & 0xff00) >> 8;
	
	printf("Little Endianifying - %d\n",number);
	printf("lsb - %d\n",lsb);
	printf("msb - %d\n",msb);
	printf("Little Endianified - %d\n",(lsb << 8 | msb));
	
	return lsb << 8 | msb;
}

u16 big_endianify(u16 number){
	u8 msb = (number & 0xff);
	u8 lsb = (number & 0xff00) >> 8;
	
	printf("Big Endianifying - %d\n",number);
	printf("lsb - %d\n",lsb);
	printf("msb - %d\n",msb);
	printf("Big Endianified - %d\n",(msb << 8 | lsb));
	
	return msb << 8 | lsb;
}

int contains_icp(FILE *file, u32 *pal_coord){
	fseek(file,0,SEEK_END);
	
	u32 file_size = ftell(file);
	u32 palette_coord = file_size - 769;
	
	if(file_size <= 769){
		return 0;
	}
	
	fseek(file,palette_coord,SEEK_SET);
	
	*pal_coord = palette_coord;
	
	u8 byte = 0;
	fread(&byte,1,1,file);
	
	fseek(file,0,SEEK_SET);
	
	if(byte == 12){
		return 1;
	}
	else return 0;
}

int AGIDL_PCXDecodeHeader(AGIDL_PCX* pcx, FILE* file){
	fread(&pcx->header.id,1,1,file);
	
	fread(&pcx->header.version,1,1,file);
	fread(&pcx->header.encoding,1,1,file);
	fread(&pcx->header.bits,1,1,file);
	fread(&pcx->header.x_start,2,1,file);
	fread(&pcx->header.y_start,2,1,file);
	fread(&pcx->header.x_end,2,1,file);
	fread(&pcx->header.y_end,2,1,file);
	fread(&pcx->header.width,2,1,file);
	fread(&pcx->header.height,2,1,file);
	
	int i;
	for(i = 0; i < 48; i++){
		char clr = 0;
		fread(&clr,1,1,file);
		pcx->header.ega[i] = clr;
	}
	
	fread(&pcx->header.reserved,1,1,file);
	fread(&pcx->header.numbitplanes,1,1,file);
	fread(&pcx->header.bytesperline,2,1,file);
	fread(&pcx->header.pal_type,2,1,file);
	fread(&pcx->header.screen_horz,2,1,file);
	fread(&pcx->header.screen_vert,2,1,file);
	
	for(i = 0; i < 54; i++){
		char blank = 0;
		fread(&blank,1,1,file);
		pcx->header.blanks[i] = blank;
	}
	
	if((pcx->header.x_end - pcx->header.x_start) == 0){
		AGIDL_PCXSetWidth(pcx, AGIDL_PCXGetWidth(pcx)+1);
		AGIDL_PCXSetHeight(pcx, AGIDL_PCXGetHeight(pcx)+1);
		
		if(AGIDL_PCXGetWidth(pcx) > 258){
			AGIDL_PCXSetWidth(pcx,little_endianify(AGIDL_PCXGetWidth(pcx)));
		}
		if(AGIDL_PCXGetHeight(pcx) > 258){
			AGIDL_PCXSetHeight(pcx,little_endianify(AGIDL_PCXGetHeight(pcx)));
		}
	}
	else{
		AGIDL_PCXSetWidth(pcx,(pcx->header.x_end - pcx->header.x_start) + 1);
		AGIDL_PCXSetHeight(pcx,(pcx->header.y_end - pcx->header.y_start) + 1);
	}
	
	if(pcx->header.id != 10 || !(pcx->header.version == 0 || pcx->header.version == 2 || pcx->header.version == 3 || pcx->header.version == 4 
	   || pcx->header.version == 5) || !(pcx->header.pal_type == 1 || pcx->header.pal_type == 2)){
		return INVALID_HEADER_FORMATTING_ERROR;
	}
	else if(pcx->header.x_end > 4096 || pcx->header.y_end > 4096){
		return CORRUPED_IMG_ERROR;
	}
	else return NO_IMG_ERROR;
}

void AGIDL_PCXDecodeIMG(AGIDL_PCX* pcx, FILE* file){
	if(pcx->header.bits == 24 || pcx->header.bits == 8 || pcx->header.bits == 1){	
		AGIDL_PCXSetClrFmt(pcx,AGIDL_RGB_888);
	}
	if(pcx->header.bits == 16){
		AGIDL_PCXSetClrFmt(pcx,AGIDL_RGB_555);
	}
	
	int scanlinelength = (pcx->header.bytesperline * pcx->header.numbitplanes);
	
//	printf("scanlinelength - %d\n",scanlinelength);
	
	u16 roffset = 0, goffset = pcx->header.bytesperline, boffset = (goffset * 2);
	
//	printf("roffset - %d\n",roffset);
//	printf("goffset - %d\n",goffset);
//	printf("boffset - %d\n",boffset);
	
//	printf("width = %d\n",AGIDL_PCXGetWidth(pcx));
//	printf("height = %d\n",AGIDL_PCXGetHeight(pcx));
	
	u32 pal_coord = 0;
	
	if(!contains_icp(file,&pal_coord)){
		
		fseek(file,128,SEEK_SET);
		
		int scanline;
		for(scanline = 0; scanline < AGIDL_PCXGetHeight(pcx); scanline++){		
			u8 *buf = (u8*)malloc(sizeof(u8)*scanlinelength);
			
			int count = 0;
			while(count < scanlinelength){
				u8 byte = 0;
				fread(&byte,1,1,file);
				
				if(count < 1){
				//	printf("first incoming byte 0x%x\n",byte);
				}
				
				char* bin = dec2bin(byte);
				
			//	printf("bin - %s\n",bin);
				
				if(bin[0] == '1' && bin[1] == '1'){
					char* byte = pcxrlebits(bin);
					u16 rle = bin2dec(byte);
				//	printf("rle byte - %s\n",byte);
					free(bin);
					free(byte);
				//	printf("rle - %d\n",rle);
					u8 read = 0;
					fread(&read,1,1,file);
					int i;
					for(i = 0; i < rle; i++){
						buf[count] = read;
						count++;
					//	printf("count - %d\n",count);
					}
				}
				else{
					int iszero = 1;
					int zero;
					for(zero = 0; zero < 8; zero++){
						if(bin[zero] != '0'){
							iszero = 0;
						}
					}
					if(iszero){
					//	printf("iszero\n");
						buf[count] = 0;
						count++;
					//	printf("non-rle count - %d\n",count);
						free(bin);
					}
					else{
						buf[count] = byte;
						count++;
				//		printf("non-rle count - %d\n",count);
						free(bin);
					}
				}
			}
			
			//printf("Pixel Processing Beginning...\n");
			if(pcx->header.bits == 24 || pcx->header.bits == 8){
				int x;
				for(x = 0; x < AGIDL_PCXGetWidth(pcx); x++){
					COLOR clr = AGIDL_RGB(buf[roffset+x],buf[goffset+x],buf[boffset+x],AGIDL_RGB_888);
					AGIDL_PCXSetClr(pcx,x,scanline,clr);
				}
			}
			else{
				int x;
				for(x = 0; x < AGIDL_PCXGetWidth(pcx); x++){
					COLOR16 clr = AGIDL_RGB(buf[roffset+x],buf[goffset+x],buf[boffset+x],AGIDL_RGB_555);
					AGIDL_PCXSetClr16(pcx,x,scanline,clr);
				}
			}
			
			free(buf);
		
		}
	}
	else{
		fseek(file,pal_coord+1,SEEK_SET);
		
		AGIDL_InitICP(&pcx->palette,AGIDL_ICP_256);
		
		int i;
		for(i = 0; i < 256; i++){
			u8 r,g,b;
			fread(&r,1,1,file);
			fread(&g,1,1,file);
			fread(&b,1,1,file);
			
			pcx->palette.icp.palette_256[i] = AGIDL_RGB(r,g,b,AGIDL_RGB_888);
		}
		
		fseek(file,128,SEEK_SET);
		
		int scanline;
		for(scanline = 0; scanline < AGIDL_PCXGetHeight(pcx); scanline++){		
			u8 *buf = (u8*)malloc(sizeof(u8)*scanlinelength);
			
			int count = 0;
			while(count < scanlinelength){
				u8 byte = 0;
				fread(&byte,1,1,file);
				
				if(count < 1){
					//printf("first incoming byte 0x%x\n",byte);
				}
				
				char* bin = dec2bin(byte);
				
			//	printf("bin - %s\n",bin);
				
				if(bin[0] == '1' && bin[1] == '1'){
					char* byte = pcxrlebits(bin);
					u16 rle = bin2dec(byte);
				//	printf("rle byte - %s\n",byte);
					free(bin);
					free(byte);
				//	printf("rle - %d\n",rle);
					u8 read = 0;
					fread(&read,1,1,file);
					int i;
					for(i = 0; i < rle; i++){
						buf[count] = read;
						count++;
					//	printf("count - %d\n",count);
					}
				}
				else{
					int iszero = 1;
					int zero;
					for(zero = 0; zero < 8; zero++){
						if(bin[zero] != '0'){
							iszero = 0;
						}
					}
					if(iszero){
					//	printf("iszero\n");
						buf[count] = 0;
						count++;
				//		printf("non-rle count - %d\n",count);
						free(bin);
					}
					else{
						buf[count] = byte;
						count++;
			//			printf("non-rle count - %d\n",count);
						free(bin);
					}
				}
			}
			
		//	printf("Pixel Processing Beginning...\n");
			
			int x;
			for(x = 0; x < AGIDL_PCXGetWidth(pcx); x++){
				COLOR clr = pcx->palette.icp.palette_256[buf[x]];
				AGIDL_PCXSetClr(pcx,x,scanline,clr);
			}
			
		//	printf("Current scanline = %d\n",scanline);
		//	printf("We are at address 0x%x in file!\n",ftell(file));

			free(buf);
		
		}
	}
}

void AGIDL_PCXEncodeHeader(AGIDL_PCX* pcx, FILE* file){
	pcx->header.id = 10;
	pcx->header.version = 5;
	pcx->header.encoding = 1;
	pcx->header.bits = 8;
	pcx->header.x_start = 0;
	pcx->header.y_start = 0;
	pcx->header.x_end = AGIDL_PCXGetWidth(pcx)-1;
	pcx->header.y_end = AGIDL_PCXGetHeight(pcx)-1;
	u16 horz = 72;
	u16 vert = 72;
	pcx->header.reserved = 0;
	pcx->header.numbitplanes = 3;
	pcx->header.bytesperline = AGIDL_PCXGetWidth(pcx);
	pcx->header.pal_type = 1;
	pcx->header.screen_horz = 0;
	pcx->header.screen_vert = 0;
	
	u8 icp = 0, blank = 0;
	
	if(pcx->icp == YES_ICP){
		pcx->header.numbitplanes = 1;
	}
	
	fwrite(&pcx->header.id,1,1,file);
	fwrite(&pcx->header.version,1,1,file);
	fwrite(&pcx->header.encoding,1,1,file);
	fwrite(&pcx->header.bits,1,1,file);
	fwrite(&pcx->header.x_start,2,1,file);
	fwrite(&pcx->header.y_start,2,1,file);
	fwrite(&pcx->header.x_end,2,1,file);
	fwrite(&pcx->header.y_end,2,1,file);
	fwrite(&horz,2,1,file);
	fwrite(&vert,2,1,file);
	
	int i;
	for(i = 0; i < 48; i++){
		fwrite(&icp,1,1,file);
	}
	
	fwrite(&pcx->header.reserved,1,1,file);
	fwrite(&pcx->header.numbitplanes,1,1,file);
	fwrite(&pcx->header.bytesperline,2,1,file);
	fwrite(&pcx->header.pal_type,2,1,file);
	fwrite(&pcx->header.screen_horz,2,1,file);
	fwrite(&pcx->header.screen_vert,2,1,file);
	
	for(i = 0; i < 54; i++){
		fwrite(&blank,1,1,file);
	}
}

void AGIDL_PCXEncodeICP(AGIDL_PCX* pcx){
	AGIDL_InitICP(&pcx->palette,AGIDL_ICP_256);
	
	int pass = 0;
	u8 pal_index = 0;
	
	int x,y;
	for(y = 0; y < AGIDL_PCXGetHeight(pcx); y++){
		for(x = 0; x < AGIDL_PCXGetWidth(pcx); x++){
			COLOR clr = AGIDL_PCXGetClr(pcx,x,y);
			
			AGIDL_AddColorICP(&pcx->palette,pal_index,clr,AGIDL_PCXGetClrFmt(pcx),AGIDL_PCXGetMaxDiff(pcx),&pass);
			
			if(pass == 1 && pal_index < 256){
				pal_index++;
			}
			
			pass = 0;
		}
	}
}

void AGIDL_PCXEncodeImg(AGIDL_PCX* pcx, FILE* file){
	AGIDL_CLR_FMT fmt = pcx->fmt;
	
	switch(pcx->fmt){
		case AGIDL_BGR_888:{
			AGIDL_PCXBGR2RGB(pcx);
		}break;
		case AGIDL_RGB_555:{
			AGIDL_PCXConvert16BPPTO24BPP(pcx);
		}break;
		case AGIDL_BGR_555:{
			AGIDL_PCXBGR2RGB(pcx);
			AGIDL_PCXConvert16BPPTO24BPP(pcx);
		}break;
		case AGIDL_RGB_565:{
			AGIDL_PCXConvert565TO555(pcx);
			AGIDL_PCXConvert16BPPTO24BPP(pcx);
		}break;
		case AGIDL_BGR_565:{
			AGIDL_PCXConvert565TO555(pcx);
			AGIDL_PCXBGR2RGB(pcx);
			AGIDL_PCXConvert16BPPTO24BPP(pcx);
		}break;
	}
	
	if(pcx->icp != 1){
		int scanlinelength = AGIDL_PCXGetWidth(pcx) * 3;
		
		int roffset = 0, goffset = AGIDL_PCXGetWidth(pcx), boffset = goffset*2;
		
		int scanline, x;
		for(scanline = 0; scanline <= AGIDL_PCXGetHeight(pcx); scanline++){
			u8 *buf = (u8*)malloc(sizeof(u8)*scanlinelength);
			for(x = 0; x < AGIDL_PCXGetWidth(pcx); x++){
				if(AGIDL_GetBitCount(AGIDL_PCXGetClrFmt(pcx)) == 32){
					COLOR clr = AGIDL_PCXGetClr(pcx,x,scanline);
					u8 r = AGIDL_GetR(clr,AGIDL_PCXGetClrFmt(pcx));
					u8 g = AGIDL_GetG(clr,AGIDL_PCXGetClrFmt(pcx));
					u8 b = AGIDL_GetB(clr,AGIDL_PCXGetClrFmt(pcx));
					buf[x] = r; buf[x+goffset] = g; buf[x+boffset] = b;
				}
				else{
					COLOR clr = AGIDL_PCXGetClr(pcx,x,scanline);
					u8 r = AGIDL_GetR(clr,AGIDL_RGB_888);
					u8 g = AGIDL_GetG(clr,AGIDL_RGB_888);
					u8 b = AGIDL_GetB(clr,AGIDL_RGB_888);
					buf[x] = r; buf[x+goffset] = g; buf[x+boffset] = b;
				}
			}
			
			for(x = 0; x < goffset; x++){
				int count = 1, x_count = x+1;
				while((buf[x] == buf[x_count]) && count < 63){
					count++;
					x_count++;
				}
				
				if(x_count >= goffset){
				
					count = AGIDL_PCXGetWidth(pcx) - x;
					
					char* bin = dec2bin(count);
			
					bin[0] = '1'; bin[1] = '1';
					
					u8 byte = bin2dec(bin);
					u8 data = buf[x];
					
					fwrite(&byte,1,1,file);
					fwrite(&data,1,1,file);
					
					x += count - 1;
					
					if(scanline <= 24)
						//printf("too much x - %d, %d\n",x,count);
					
					free(bin);
					
				}else{
					char* bin = dec2bin(count);
			
					bin[0] = '1'; bin[1] = '1';
					
					u8 byte = bin2dec(bin);
					u8 data = buf[x];
					
					fwrite(&byte,1,1,file);
					fwrite(&data,1,1,file);
					
					x += count - 1;
					
					if(scanline <= 24)
						//printf("much x - %d, %d\n",x,count);
					
					free(bin);
				}
				
			}

			
			for(x = goffset; x < boffset; x++){
				int count = 1, x_count = x+1;
				while((buf[x] == buf[x_count]) && count < 63){
					count++;
					x_count++;
				}
				
				if(x_count >= boffset){
				
					count = (AGIDL_PCXGetWidth(pcx)*2) - x;
					
					char* bin = dec2bin(count);
			
					bin[0] = '1'; bin[1] = '1';
					
					u8 byte = bin2dec(bin);
					u8 data = buf[x];
					
					fwrite(&byte,1,1,file);
					fwrite(&data,1,1,file);
					
					x += count - 1;
					
					free(bin);
					
				}else{
					char* bin = dec2bin(count);
			
					bin[0] = '1'; bin[1] = '1';
					
					u8 byte = bin2dec(bin);
					u8 data = buf[x];
					
					fwrite(&byte,1,1,file);
					fwrite(&data,1,1,file);
					
					x += count - 1;
					
					free(bin);
				}
				
			}
			
			for(x = boffset; x < scanlinelength; x++){
				int count = 1, x_count = x+1;
				while((buf[x] == buf[x_count]) && count < 63){
					count++;
					x_count++;
				}
				
				char* bin = dec2bin(count);
			
				bin[0] = '1'; bin[1] = '1';
				
				u8 byte = bin2dec(bin);
				u8 data = buf[x];
				
				fwrite(&byte,1,1,file);
				fwrite(&data,1,1,file);
				
				x += count - 1;
				
				free(bin);
				
			}
				free(buf);
		}
	}
	else{
		AGIDL_PCXEncodeICP(pcx);
	
		int scanline;
		for(scanline = 0; scanline < AGIDL_PCXGetHeight(pcx); scanline++){
			u8* buf = (u8*)malloc(sizeof(u8)*AGIDL_PCXGetWidth(pcx));
			
			int row;
			for(row = 0; row < AGIDL_PCXGetWidth(pcx); row++){
				COLOR clr = AGIDL_PCXGetClr(pcx,row,scanline);
				buf[row] = AGIDL_FindClosestColor(pcx->palette,clr,AGIDL_PCXGetClrFmt(pcx),AGIDL_PCXGetMaxDiff(pcx));
			}
			
			int x;
			for(x = 0; x < AGIDL_PCXGetWidth(pcx); x++){
				int count = 1, x_count = x+1;
				
				while((buf[x] == buf[x+1]) && count < 63){
					count++;
					x_count++;
				}
				
				char* rle = dec2bin(count);
				
				rle[0] = '1'; rle[1] = '1';
				
				u8 byte = bin2dec(rle);
				u8 data = buf[x];
				
				fwrite(&byte,1,1,file);
				fwrite(&data,1,1,file);
				
				free(rle);
				
				x += count -  1;
			}
			
			free(buf);
		}
		
		u8 hexid = 0x0C;
			
		fwrite(&hexid,1,1,file);
			
		int i;
		for(i = 0; i < 256; i++){
			COLOR clr = pcx->palette.icp.palette_256[i];
			
			u8 r = AGIDL_GetR(clr,AGIDL_RGB_888);
			u8 g = AGIDL_GetG(clr,AGIDL_RGB_888);
			u8 b = AGIDL_GetB(clr,AGIDL_RGB_888);
			
			fwrite(&r,1,1,file);
			fwrite(&g,1,1,file);
			fwrite(&b,1,1,file);
		}	
	}
	
	switch(fmt){
		case AGIDL_BGR_888:{
			AGIDL_PCXRGB2BGR(pcx);
		}break;
		case AGIDL_RGB_555:{
			AGIDL_PCXConvert24BPPTO16BPP(pcx);
		}break;
		case AGIDL_BGR_555:{
			AGIDL_PCXRGB2BGR(pcx);
			AGIDL_PCXConvert24BPPTO16BPP(pcx);
		}break;
		case AGIDL_RGB_565:{
			AGIDL_PCXConvert24BPPTO16BPP(pcx);
			AGIDL_PCXConvert555TO565(pcx);
		}break;
		case AGIDL_BGR_565:{
			AGIDL_PCXRGB2BGR(pcx);
			AGIDL_PCXConvert24BPPTO16BPP(pcx);
			AGIDL_PCXConvert555TO565(pcx);
		}break;
	
	}
}

AGIDL_PCX * AGIDL_LoadPCX(char *filename){
	FILE* file = fopen(filename,"rb");
	
	if(file == NULL){
		printf("%s - %s\n",AGIDL_Error2Str(FILE_NOT_LOCATED_IMG_ERROR),filename);
		return NULL;
	}
	
	AGIDL_PCX *pcx = (AGIDL_PCX*)malloc(sizeof(AGIDL_PCX));
	pcx->filename = (char*)malloc(strlen(filename)+1);
	AGIDL_FilenameCpy(pcx->filename,filename);
	
	if(pcx == NULL || pcx->filename == NULL){
		printf("%s\n",AGIDL_Error2Str(MEMORY_IMG_ERROR));
	}
	
	int error = AGIDL_PCXDecodeHeader(pcx,file);
	
	if(error != NO_IMG_ERROR){
		printf("%s\n",AGIDL_Error2Str(error));
		return NULL;
	}
	
	pcx->pixels.pix32 = (COLOR*)malloc(sizeof(COLOR)*(AGIDL_PCXGetWidth(pcx)*AGIDL_PCXGetHeight(pcx)));
	
	AGIDL_PCXDecodeIMG(pcx,file);
	
	fclose(file);
	
	return pcx;
}

void AGIDL_ExportPCX(AGIDL_PCX *pcx){
	FILE* file = fopen(pcx->filename,"wb");
	
	if(file == NULL){
		printf("Could not export PCX image! - %s\n",pcx->filename);
	}
	
	AGIDL_PCXEncodeHeader(pcx,file);
	AGIDL_PCXEncodeImg(pcx,file);
	
	fclose(file);
}