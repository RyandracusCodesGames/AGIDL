#ifndef AGIDL_IMG_COMPRESSION_H
#define AGIDL_IMG_COMPRESSION_H

/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023-2024 Ryandracus Chapman
*
*   Library: libagidl
*   File: agidl_img_compression.h
*   Date: 11/25/2023
*   Version: 0.1b
*   Updated: 1/19/2024
*   Author: Ryandracus Chapman
*
********************************************/

#include "agidl_types.h"

u32 AGIDL_EncodeRLE(void* data, u32 bit_count, u32 x, u32 y, u32 width, u32 height, u16 max_rle);

#endif