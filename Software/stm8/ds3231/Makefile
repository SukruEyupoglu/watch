#!/bin/sh
#export PATH := $(PATH):$(HOME)/local/sdcc/bin
VPATH =/home/qwe/stm8/sdcc-3.6.0/bin
MCU  = stm8s003f3
ARCH = stm8

F_CPU   ?= 16000000
TARGET  ?= stm8.ihx

LIBDIR0   = char_lcd
LIBDIR1   = char_lcd/hc595
LIBDIR2   = char_lcd/delay
RMS   = *.map *.asm *.rel *.ihx *.o *.sym *.lk *.lst *.rst *.cdb *.bin

SRCS    := $(wildcard *.c $(LIBDIR0)/*.c $(LIBDIR1)/*.c $(LIBDIR2)/*.c)
ASRCS   := $(wildcard *.s $(LIBDIR0)/*.s $(LIBDIR1)/*.s $(LIBDIR2)/*.s)

OBJS     = $(SRCS:.c=.rel)
OBJS    += $(ASRCS:.s=.rel)

CC       = $(VPATH)/sdcc
LD       = $(VPATH)/sdld
AS       = $(VPATH)/sdasstm8
OBJCOPY  = $(VPATH)/sdobjcopy
ASFLAGS  = -plosgff
CFLAGS   = -m$(ARCH) -p$(MCU) --std-sdcc11
CFLAGS  += -DF_CPU=$(F_CPU)UL -I. -I$(LIBDIR0) -I$(LIBDIR1) -I$(LIBDIR2)
CFLAGS  += --stack-auto --noinduction --use-non-free
## Disable lospre (workaround for bug 2673)
#CFLAGS  += --nolospre
## Extra optimization rules - use with care
#CFLAGS  += --peep-file $(LIBDIR)/util/extra.def
LDFLAGS  = -m$(ARCH) -l$(ARCH) --out-fmt-ihx

all: $(TARGET) size

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

%.rel: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

%.rel: %.s
	$(AS) $(ASFLAGS) $<

size:
	@$(OBJCOPY) -I ihex --output-target=binary $(TARGET) $(TARGET).bin
	@echo "----------"
	@echo "Image size:"
	@stat -L -c %s $(TARGET).bin

flash: $(TARGET)
	../sh/stm8flash -c stlinkv2 -p $(MCU) -w $(TARGET)

serial: $(TARGET)
	stm8gal -p /dev/ttyUSB0 -w $(TARGET)

clean:
	rm -f $(LIBDIR0)/*.map $(LIBDIR0)/*.asm $(LIBDIR0)/*.rel $(LIBDIR0)/*.ihx $(LIBDIR0)/*.o $(LIBDIR0)/*.sym $(LIBDIR0)/*.lk $(LIBDIR0)/*.lst $(LIBDIR0)/*.rst $(LIBDIR0)/*.cdb $(LIBDIR0)/*.bin
	rm -f $(LIBDIR1)/*.map $(LIBDIR1)/*.asm $(LIBDIR1)/*.rel $(LIBDIR1)/*.ihx $(LIBDIR1)/*.o $(LIBDIR1)/*.sym $(LIBDIR1)/*.lk $(LIBDIR1)/*.lst $(LIBDIR1)/*.rst $(LIBDIR1)/*.cdb $(LIBDIR1)/*.bin
	rm -f $(LIBDIR2)/*.map $(LIBDIR2)/*.asm $(LIBDIR2)/*.rel $(LIBDIR2)/*.ihx $(LIBDIR2)/*.o $(LIBDIR2)/*.sym $(LIBDIR2)/*.lk $(LIBDIR2)/*.lst $(LIBDIR2)/*.rst $(LIBDIR2)/*.cdb $(LIBDIR2)/*.bin
	rm -f $(RMS)

cm:
	$(MAKE) clean
	$(MAKE) all

.PHONY: clean all flash
