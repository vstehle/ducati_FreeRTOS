# Makefile for ducati_FreeRTOS

# compiler / linker
COMPILER=gcc
CC=arm-linux-gnueabihf-gcc
AR=arm-linux-gnueabihf-ar
LD=arm-linux-gnueabihf-ld
OBJCOPY=arm-linux-gnueabihf-objcopy
FLAGS := -mthumb -march=armv7-m -mcpu=cortex-m3 -fno-stack-protector -static -O2

# Directories
OUTPUT_DIR=./out
FREERTOS_SOURCE_DIR=../Source
COMMON_SOURCE_DIR=../Common/Minimal

VPATH=${FREERTOS_SOURCE_DIR}: \
	${FREERTOS_SOURCE_DIR}/portable/MemMang: \
	${FREERTOS_SOURCE_DIR}/portable/GCC/ARM_CM3: \
	${COMMON_SOURCE_DIR}: \
	./init

# files to be built
OBJS=	${OUTPUT_DIR}/main.o \
	${OUTPUT_DIR}/mailbox.o \
	${OUTPUT_DIR}/trace.o \
	${OUTPUT_DIR}/interrupt.o \
	${OUTPUT_DIR}/virtio.o \
	${OUTPUT_DIR}/rpmsg.o \
	${OUTPUT_DIR}/rdaemon.o \
	${OUTPUT_DIR}/list.o \
	${OUTPUT_DIR}/queue.o \
	${OUTPUT_DIR}/tasks.o \
	${OUTPUT_DIR}/port.o \
	${OUTPUT_DIR}/heap_1.o \
	${OUTPUT_DIR}/BlockQ.o \
	${OUTPUT_DIR}/PollQ.o	\
	${OUTPUT_DIR}/integer.o \
	${OUTPUT_DIR}/semtest.o \
	${OUTPUT_DIR}/libc.o \

INIT_OBJS=${OUTPUT_DIR}/startup.o

# gcc compiler flags
CFLAGS=$(FLAGS)        \
       -MD \
       -O2 \
       -fno-stack-protector

# gcc source flags
CFLAGS+= -I . \
	-I ${FREERTOS_SOURCE_DIR}/include \
	-I ${FREERTOS_SOURCE_DIR}/portable/GCC/ARM_CM3 \
	-I ../Common/include

ifdef DEBUG
CFLAGS+= -g
endif

LDFLAGS= -Map $(OUTPUT_DIR)/out.map

# rules
all: ${OUTPUT_DIR} build

${OUTPUT_DIR}:
	mkdir ${OUTPUT_DIR}

build: ${INIT_OBJS} ${OBJS}
	$(LD) -nostdlib -static -T ducati.ld --entry "ResetISR" $(LDFLAGS) -o $(OUTPUT_DIR)/FreeRTOS_ducati.axf  $^ $(LDLIBS)

${OUTPUT_DIR}/%.o : %.c
	$(CC) $(CFLAGS) -Dgcc -o $@ -c $<

clean:
	rm -rf ${OUTPUT_DIR}
