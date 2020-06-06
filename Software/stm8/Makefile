#!/bin/sh
#export PATH := $(PATH):$(HOME)/local/sdcc/bin
VPATH =/home/qwe/soft/stm8/sdcc-3.6.0/bin
MCU  = stm8s103f3
ARCH = stm8

F_CPU   ?= 16000000
TARGET  ?= stm8.ihx

LIBDIR   = lib
RMS   = *.map *.asm *.rel *.ihx *.o *.sym *.lk *.lst *.rst *.cdb *.bin

SRCS    := $(wildcard *.c $(LIBDIR)/*.c)
ASRCS   := $(wildcard *.s $(LIBDIR)/*.s)

OBJS     = $(SRCS:.c=.rel)
OBJS    += $(ASRCS:.s=.rel)

CC       = $(VPATH)/sdcc
LD       = $(VPATH)/sdld
AS       = $(VPATH)/sdasstm8
OBJCOPY  = $(VPATH)/sdobjcopy
ASFLAGS  = -plosgff
CFLAGS   = -m$(ARCH) -p$(MCU) --std-sdcc11
CFLAGS  += -DF_CPU=$(F_CPU)UL -I. -I$(LIBDIR)
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
	rm -f $(LIBDIR)/*.map $(LIBDIR)/*.asm $(LIBDIR)/*.rel $(LIBDIR)/*.ihx $(LIBDIR)/*.o $(LIBDIR)/*.sym $(LIBDIR)/*.lk $(LIBDIR)/*.lst $(LIBDIR)/*.rst $(LIBDIR)/*.cdb $(LIBDIR)/*.bin
	rm -f $(RMS)

.PHONY: clean all flash
