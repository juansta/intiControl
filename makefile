#
#             LUFA Library
#     Copyright (C) Dean Camera, 2015.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#
# --------------------------------------
#         LUFA Project Makefile.
# --------------------------------------

# Run "make help" for target help.

MCU          = atmega32u2
ARCH         = AVR8
BOARD        = inti
F_CPU        = 8000000
F_USB        = $(F_CPU)
OPTIMIZATION = s
TARGET       = intiController
CPP_FILES    = $(wildcard src/*.cpp) 
C_FILES      = $(wildcard src/*.c) 
SRC          = $(TARGET).cpp $(C_FILES) $(CPP_FILES) $(LUFA_SRC_USB) $(LUFA_SRC_USBCLASS)
LUFA_PATH    = /opt/lufa/LUFA
CC_FLAGS     = -DUSB_DEBUG -DUSE_LUFA_CONFIG_HEADER -IConfig/ -Iinclude/ -fshort-enums 

#default target
all:
# Include LUFA build script makefiles
include $(LUFA_PATH)/Build/lufa_core.mk
include $(LUFA_PATH)/Build/lufa_sources.mk
include $(LUFA_PATH)/Build/lufa_build.mk
include $(LUFA_PATH)/Build/lufa_cppcheck.mk
include $(LUFA_PATH)/Build/lufa_doxygen.mk
include $(LUFA_PATH)/Build/lufa_dfu.mk
include $(LUFA_PATH)/Build/lufa_hid.mk
include $(LUFA_PATH)/Build/lufa_avrdude.mk
include $(LUFA_PATH)/Build/lufa_atprogram.mk

flash:  $(TARGET).hex
	dfu-programmer atmega32u2 erase
	dfu-programmer atmega32u2 flash $(TARGET).hex
