CC = gcc
INCS = -I"$(CURDIR)/include"
CFLAGS = -Wall -O2 $(INCS)
LDFLAGS =
OBJS = src/agidl_math_utils.o src/agidl_cc_manager.o src/agidl_cc_converter.o src/agidl_cc_mixer.o src/agidl_img_types.o src/agidl_imgp_grayscale.o src/agidl_img_bmp.o src/agidl_img_tga.o src/agidl_img_tim.o src/agidl_img_pcx.o src/agidl_img_quake.o src/agidl_img_pvr.o src/agidl_img_gxt.o src/agidl_img_bti.o src/agidl_img_converter.o src/agidl_img_search.o src/agidl_img_compression.o
DEPS = include/agidl_types.h include/agidl_math_utils.h include/agidl_cc_types.h include/agidl_cc_manager.h include/agidl_cc_convert.h include/agidl_cc_mixer.h include/agidl_cc_core.h include/agidl_img_types.h include/agidl_imgp_grayscale.h include/agidl_imgp_core.h include/agidl_img_bmp.h include/agidl_img_tga.h include/agidl_img_tim.h include/agidl_img_pcx.h include/agidl_img_quake.h include/agidl_img_pvr.h include/agidl_img_gxt.h include/agidl_img_bti.h include/agidl_img_converter.h include/agidl_img_search.h include/agidl_img_compression.h include/agidl_img_core.h include/agidl.h
TARGET = main

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)
	
clean:
	rm -f $(OBJS) $(TARGET) *~
