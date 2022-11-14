###########################################################################
## Makefile generated for component 'uavrt_detection'. 
## 
## Makefile     : uavrt_detection_rtw.mk
## Generated on : Mon Sep 26 15:40:40 2022
## Final product: ./uavrt_detection.lib
## Product type : static-library
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile
# MODELLIB                Static library target

PRODUCT_NAME              = uavrt_detection
MAKEFILE                  = uavrt_detection_rtw.mk
MATLAB_ROOT               = $(MATLAB_WORKSPACE)/Applications/MATLAB_R2022b.app
MATLAB_BIN                = $(MATLAB_WORKSPACE)/Applications/MATLAB_R2022b.app/bin
MATLAB_ARCH_BIN           = $(MATLAB_BIN)/maci64
START_DIR                 = $(MATLAB_WORKSPACE)/Users/Don/repos/uavrt_detection/detector
TGT_FCN_LIB               = ISO_C
SOLVER_OBJ                = 
CLASSIC_INTERFACE         = 0
MODEL_HAS_DYNAMICALLY_LOADED_SFCNS = 
RELATIVE_PATH_TO_ANCHOR   = ../../..
C_STANDARD_OPTS           = 
CPP_STANDARD_OPTS         = 
MODELLIB                  = uavrt_detection.lib

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          GNU GCC Embedded Linux
# Supported Version(s):    
# ToolchainInfo Version:   2022b
# Specification Revision:  1.0
# 

#-----------
# MACROS
#-----------

CCOUTPUTFLAG = --output_file=
LDOUTPUTFLAG = --output_file=

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = -lm -lm -lstdc++

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# Assembler: GNU GCC Embedded Linux Assembler
AS = as

# C Compiler: GNU GCC Embedded Linux C Compiler
CC = gcc

# Linker: GNU GCC Embedded Linux Linker
LD = gcc

# C++ Compiler: GNU GCC Embedded Linux C++ Compiler
CPP = g++

# C++ Linker: GNU GCC Embedded Linux C++ Linker
CPP_LD = g++

# Archiver: GNU GCC Embedded Linux Archiver
AR = ar

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_ARCH_BIN)
MEX = "$(MEX_PATH)/mex"

# Download: Download
DOWNLOAD =

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: Make Tool
MAKE = make


#-------------------------
# Directives/Utilities
#-------------------------

ASDEBUG             = -g
AS_OUTPUT_FLAG      = -o
CDEBUG              = -g
C_OUTPUT_FLAG       = -o
LDDEBUG             = -g
OUTPUT_FLAG         = -o
CPPDEBUG            = -g
CPP_OUTPUT_FLAG     = -o
CPPLDDEBUG          = -g
OUTPUT_FLAG         = -o
ARDEBUG             =
STATICLIB_OUTPUT_FLAG =
MEX_DEBUG           = -g
RM                  =
ECHO                = echo
MV                  =
RUN                 =

#--------------------------------------
# "Faster Runs" Build Configuration
#--------------------------------------

ARFLAGS              = -r
ASFLAGS              = -c \
                       $(ASFLAGS_ADDITIONAL) \
                       $(INCLUDES)
CFLAGS               = -c \
                       -MMD -MP -MF"$(@:%.o=%.dep)" -MT"$@"  \
                       -O2
CPPFLAGS             = -c \
                       -MMD -MP -MF"$(@:%.o=%.dep)" -MT"$@"  \
                       -fpermissive  \
                       -O2
CPP_LDFLAGS          = -lrt -lpthread -ldl
CPP_SHAREDLIB_LDFLAGS  = -shared  \
                         -lrt -lpthread -ldl
DOWNLOAD_FLAGS       =
EXECUTE_FLAGS        =
LDFLAGS              = -lrt -lpthread -ldl
MEX_CPPFLAGS         =
MEX_CPPLDFLAGS       =
MEX_CFLAGS           =
MEX_LDFLAGS          =
MAKE_FLAGS           = -j$(($(nproc)+1)) -Otarget -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    = -shared  \
                       -lrt -lpthread -ldl



###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = ./uavrt_detection.lib
PRODUCT_TYPE = "static-library"
BUILD_TYPE = "Static Library"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = -I$(START_DIR)/codegen/lib/uavrt_detection -I$(START_DIR) -I$(MATLAB_ROOT)/toolbox/shared/spc/src_ml/extern/include -I$(MATLAB_WORKSPACE)/Users/Don/Documents/MATLAB/SupportPackages/R2022b/toolbox/realtime/targets/raspi/include -I$(MATLAB_ROOT)/toolbox/coder/rtiostream/src/utils -I$(MATLAB_ROOT)/extern/include

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_ = -D__MW_TARGET_USE_HARDWARE_RESOURCES_H__
DEFINES_CUSTOM = 
DEFINES_SKIPFORSIL = -D__linux__ -DARM_PROJECT -D_USE_TARGET_UDP_ -D_RUNONTARGETHARDWARE_BUILD_ -DSTACK_SIZE=200000
DEFINES_STANDARD = -DMODEL=uavrt_detection

DEFINES = $(DEFINES_) $(DEFINES_CUSTOM) $(DEFINES_SKIPFORSIL) $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(START_DIR)/codegen/lib/uavrt_detection/coder_posix_time.c $(START_DIR)/codegen/lib/uavrt_detection/uavrt_detection_data.c $(START_DIR)/codegen/lib/uavrt_detection/rt_nonfinite.c $(START_DIR)/codegen/lib/uavrt_detection/rtGetNaN.c $(START_DIR)/codegen/lib/uavrt_detection/rtGetInf.c $(START_DIR)/codegen/lib/uavrt_detection/uavrt_detection_initialize.c $(START_DIR)/codegen/lib/uavrt_detection/uavrt_detection_terminate.c $(START_DIR)/codegen/lib/uavrt_detection/uavrt_detection.c $(START_DIR)/codegen/lib/uavrt_detection/DetectorConfig.c $(START_DIR)/codegen/lib/uavrt_detection/fileManager.c $(START_DIR)/codegen/lib/uavrt_detection/fgetl.c $(START_DIR)/codegen/lib/uavrt_detection/ftell.c $(START_DIR)/codegen/lib/uavrt_detection/fseek.c $(START_DIR)/codegen/lib/uavrt_detection/find.c $(START_DIR)/codegen/lib/uavrt_detection/str2double.c $(START_DIR)/codegen/lib/uavrt_detection/str2double1.c $(START_DIR)/codegen/lib/uavrt_detection/str2matrix.c $(START_DIR)/codegen/lib/uavrt_detection/makepulsestruc.c $(START_DIR)/codegen/lib/uavrt_detection/pulsestats.c $(START_DIR)/codegen/lib/uavrt_detection/validator_check_size.c $(START_DIR)/codegen/lib/uavrt_detection/waveform.c $(START_DIR)/codegen/lib/uavrt_detection/validate_print_arguments.c $(START_DIR)/codegen/lib/uavrt_detection/AsyncBuffer.c $(START_DIR)/codegen/lib/uavrt_detection/AsyncBuffercgHelper.c $(START_DIR)/codegen/lib/uavrt_detection/wgn.c $(START_DIR)/codegen/lib/uavrt_detection/randn.c $(START_DIR)/codegen/lib/uavrt_detection/stft.c $(START_DIR)/codegen/lib/uavrt_detection/computeDFT.c $(START_DIR)/codegen/lib/uavrt_detection/FFTImplementationCallback.c $(START_DIR)/codegen/lib/uavrt_detection/psdfreqvec.c $(START_DIR)/codegen/lib/uavrt_detection/wfmstft.c $(START_DIR)/codegen/lib/uavrt_detection/abs.c $(START_DIR)/codegen/lib/uavrt_detection/movSumProdOrMean.c $(START_DIR)/codegen/lib/uavrt_detection/quickselect.c $(START_DIR)/codegen/lib/uavrt_detection/repmat.c $(START_DIR)/codegen/lib/uavrt_detection/mean.c $(START_DIR)/codegen/lib/uavrt_detection/channelreceiver.c $(START_DIR)/codegen/lib/uavrt_detection/pause.c $(START_DIR)/codegen/lib/uavrt_detection/colon.c $(START_DIR)/codegen/lib/uavrt_detection/fwrite.c $(START_DIR)/codegen/lib/uavrt_detection/tic.c $(START_DIR)/codegen/lib/uavrt_detection/timeKeeper.c $(START_DIR)/codegen/lib/uavrt_detection/diff.c $(START_DIR)/codegen/lib/uavrt_detection/sum.c $(START_DIR)/codegen/lib/uavrt_detection/string1.c $(START_DIR)/codegen/lib/uavrt_detection/toc.c $(START_DIR)/codegen/lib/uavrt_detection/linspace.c $(START_DIR)/codegen/lib/uavrt_detection/buildtimecorrelatormatrix.c $(START_DIR)/codegen/lib/uavrt_detection/unique.c $(START_DIR)/codegen/lib/uavrt_detection/sortLE.c $(START_DIR)/codegen/lib/uavrt_detection/minOrMax.c $(START_DIR)/codegen/lib/uavrt_detection/mtimes.c $(START_DIR)/codegen/lib/uavrt_detection/evfit.c $(START_DIR)/codegen/lib/uavrt_detection/fzero.c $(START_DIR)/codegen/lib/uavrt_detection/interp1.c $(START_DIR)/codegen/lib/uavrt_detection/allOrAny.c $(START_DIR)/codegen/lib/uavrt_detection/all.c $(START_DIR)/codegen/lib/uavrt_detection/unaryMinOrMax.c $(START_DIR)/codegen/lib/uavrt_detection/incohsumtoeplitz.c $(START_DIR)/codegen/lib/uavrt_detection/locBsearch.c $(START_DIR)/codegen/lib/uavrt_detection/sparse.c $(START_DIR)/codegen/lib/uavrt_detection/any.c $(START_DIR)/codegen/lib/uavrt_detection/sparse1.c $(START_DIR)/codegen/lib/uavrt_detection/not.c $(START_DIR)/codegen/lib/uavrt_detection/eyeLike.c $(START_DIR)/codegen/lib/uavrt_detection/imresize.c $(START_DIR)/codegen/lib/uavrt_detection/ifWhileCond.c $(START_DIR)/codegen/lib/uavrt_detection/horzcatStructList.c $(START_DIR)/codegen/lib/uavrt_detection/blockedSummation.c $(START_DIR)/codegen/lib/uavrt_detection/waveformcopy.c $(START_DIR)/codegen/lib/uavrt_detection/controlreceiver.c $(START_DIR)/codegen/lib/uavrt_detection/threshold.c $(START_DIR)/codegen/lib/uavrt_detection/handle.c $(START_DIR)/codegen/lib/uavrt_detection/SystemCore.c $(START_DIR)/codegen/lib/uavrt_detection/setup.c $(START_DIR)/codegen/lib/uavrt_detection/eml_rand_mt19937ar_stateful.c $(START_DIR)/codegen/lib/uavrt_detection/CoderTimeAPI.c $(START_DIR)/codegen/lib/uavrt_detection/strcmp.c $(START_DIR)/codegen/lib/uavrt_detection/sort.c $(START_DIR)/codegen/lib/uavrt_detection/sortIdx.c $(START_DIR)/codegen/lib/uavrt_detection/eml_rand_mt19937ar.c $(START_DIR)/codegen/lib/uavrt_detection/insertionsort.c $(START_DIR)/codegen/lib/uavrt_detection/introsort.c $(START_DIR)/codegen/lib/uavrt_detection/heapsort.c $(START_DIR)/codegen/lib/uavrt_detection/fillIn.c $(START_DIR)/codegen/lib/uavrt_detection/parenAssign2D.c $(START_DIR)/codegen/lib/uavrt_detection/circshift.c $(START_DIR)/codegen/lib/uavrt_detection/fftshift.c $(START_DIR)/codegen/lib/uavrt_detection/div.c $(START_DIR)/codegen/lib/uavrt_detection/weightingmatrix.c $(START_DIR)/codegen/lib/uavrt_detection/assembleWq.c $(START_DIR)/codegen/lib/uavrt_detection/uavrt_detection_emxutil.c $(START_DIR)/codegen/lib/uavrt_detection/uavrt_detection_rtwutil.c $(MATLAB_ROOT)/toolbox/shared/spc/src_ml/extern/src/DAHostLib_Network.c $(MATLAB_ROOT)/toolbox/shared/spc/src_ml/extern/src/DAHostLib_rtw.c $(MATLAB_WORKSPACE)/Users/Don/Documents/MATLAB/SupportPackages/R2022b/toolbox/realtime/targets/raspi/src/udp/linuxUDP.c

ALL_SRCS = $(SRCS)

###########################################################################
## OBJECTS
###########################################################################

OBJS = coder_posix_time.c.o uavrt_detection_data.c.o rt_nonfinite.c.o rtGetNaN.c.o rtGetInf.c.o uavrt_detection_initialize.c.o uavrt_detection_terminate.c.o uavrt_detection.c.o DetectorConfig.c.o fileManager.c.o fgetl.c.o ftell.c.o fseek.c.o find.c.o str2double.c.o str2double1.c.o str2matrix.c.o makepulsestruc.c.o pulsestats.c.o validator_check_size.c.o waveform.c.o validate_print_arguments.c.o AsyncBuffer.c.o AsyncBuffercgHelper.c.o wgn.c.o randn.c.o stft.c.o computeDFT.c.o FFTImplementationCallback.c.o psdfreqvec.c.o wfmstft.c.o abs.c.o movSumProdOrMean.c.o quickselect.c.o repmat.c.o mean.c.o channelreceiver.c.o pause.c.o colon.c.o fwrite.c.o tic.c.o timeKeeper.c.o diff.c.o sum.c.o string1.c.o toc.c.o linspace.c.o buildtimecorrelatormatrix.c.o unique.c.o sortLE.c.o minOrMax.c.o mtimes.c.o evfit.c.o fzero.c.o interp1.c.o allOrAny.c.o all.c.o unaryMinOrMax.c.o incohsumtoeplitz.c.o locBsearch.c.o sparse.c.o any.c.o sparse1.c.o not.c.o eyeLike.c.o imresize.c.o ifWhileCond.c.o horzcatStructList.c.o blockedSummation.c.o waveformcopy.c.o controlreceiver.c.o threshold.c.o handle.c.o SystemCore.c.o setup.c.o eml_rand_mt19937ar_stateful.c.o CoderTimeAPI.c.o strcmp.c.o sort.c.o sortIdx.c.o eml_rand_mt19937ar.c.o insertionsort.c.o introsort.c.o heapsort.c.o fillIn.c.o parenAssign2D.c.o circshift.c.o fftshift.c.o div.c.o weightingmatrix.c.o assembleWq.c.o uavrt_detection_emxutil.c.o uavrt_detection_rtwutil.c.o DAHostLib_Network.c.o DAHostLib_rtw.c.o linuxUDP.c.o

ALL_OBJS = $(OBJS)

###########################################################################
## PREBUILT OBJECT FILES
###########################################################################

PREBUILT_OBJS = 

###########################################################################
## LIBRARIES
###########################################################################

LIBS = 

###########################################################################
## SYSTEM LIBRARIES
###########################################################################

SYSTEM_LIBS = 

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_ = -fopenmp
CFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CFLAGS += $(CFLAGS_) $(CFLAGS_BASIC)

#-----------------
# C++ Compiler
#-----------------

CPPFLAGS_ = -fopenmp
CPPFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CPPFLAGS += $(CPPFLAGS_) $(CPPFLAGS_BASIC)

#---------------
# C++ Linker
#---------------

CPP_LDFLAGS_ = -fopenmp
CPP_LDFLAGS_BLOCKMODULES = -lm -ldl

CPP_LDFLAGS += $(CPP_LDFLAGS_) $(CPP_LDFLAGS_BLOCKMODULES)

#------------------------------
# C++ Shared Library Linker
#------------------------------

CPP_SHAREDLIB_LDFLAGS_ = -fopenmp
CPP_SHAREDLIB_LDFLAGS_BLOCKMODULES = -lm -ldl

CPP_SHAREDLIB_LDFLAGS += $(CPP_SHAREDLIB_LDFLAGS_) $(CPP_SHAREDLIB_LDFLAGS_BLOCKMODULES)

#-----------
# Linker
#-----------

LDFLAGS_ = -fopenmp
LDFLAGS_BLOCKMODULES = -lm -ldl

LDFLAGS += $(LDFLAGS_) $(LDFLAGS_BLOCKMODULES)

#--------------------------
# Shared Library Linker
#--------------------------

SHAREDLIB_LDFLAGS_ = -fopenmp
SHAREDLIB_LDFLAGS_BLOCKMODULES = -lm -ldl

SHAREDLIB_LDFLAGS += $(SHAREDLIB_LDFLAGS_) $(SHAREDLIB_LDFLAGS_BLOCKMODULES)

###########################################################################
## INLINED COMMANDS
###########################################################################


DERIVED_SRCS = $(subst .o,.dep,$(OBJS))

build:

%.dep:



-include codertarget_assembly_flags.mk
-include *.dep


###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build clean info prebuild download execute


all : build
	echo "### Successfully generated all binary outputs."


build : prebuild $(PRODUCT)


prebuild : 


download : $(PRODUCT)


execute : download


###########################################################################
## FINAL TARGET
###########################################################################

#---------------------------------
# Create a static library         
#---------------------------------

$(PRODUCT) : $(OBJS) $(PREBUILT_OBJS)
	echo "### Creating static library "$(PRODUCT)" ..."
	$(AR) $(ARFLAGS)  $(PRODUCT) $(OBJS)
	echo "### Created: $(PRODUCT)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

%.c.o : %.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.s.o : %.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.cpp.o : %.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.c.o : $(RELATIVE_PATH_TO_ANCHOR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.s.o : $(RELATIVE_PATH_TO_ANCHOR)/%.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.cpp.o : $(RELATIVE_PATH_TO_ANCHOR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.c.o : $(START_DIR)/codegen/lib/uavrt_detection/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.s.o : $(START_DIR)/codegen/lib/uavrt_detection/%.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.cpp.o : $(START_DIR)/codegen/lib/uavrt_detection/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.c.o : $(START_DIR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.s.o : $(START_DIR)/%.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.cpp.o : $(START_DIR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.c.o : $(MATLAB_ROOT)/toolbox/shared/spc/src_ml/extern/src/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.s.o : $(MATLAB_ROOT)/toolbox/shared/spc/src_ml/extern/src/%.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.cpp.o : $(MATLAB_ROOT)/toolbox/shared/spc/src_ml/extern/src/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


coder_posix_time.c.o : $(START_DIR)/codegen/lib/uavrt_detection/coder_posix_time.c
	$(CC) $(CFLAGS) -o "$@" "$<"


uavrt_detection_data.c.o : $(START_DIR)/codegen/lib/uavrt_detection/uavrt_detection_data.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rt_nonfinite.c.o : $(START_DIR)/codegen/lib/uavrt_detection/rt_nonfinite.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rtGetNaN.c.o : $(START_DIR)/codegen/lib/uavrt_detection/rtGetNaN.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rtGetInf.c.o : $(START_DIR)/codegen/lib/uavrt_detection/rtGetInf.c
	$(CC) $(CFLAGS) -o "$@" "$<"


uavrt_detection_initialize.c.o : $(START_DIR)/codegen/lib/uavrt_detection/uavrt_detection_initialize.c
	$(CC) $(CFLAGS) -o "$@" "$<"


uavrt_detection_terminate.c.o : $(START_DIR)/codegen/lib/uavrt_detection/uavrt_detection_terminate.c
	$(CC) $(CFLAGS) -o "$@" "$<"


uavrt_detection.c.o : $(START_DIR)/codegen/lib/uavrt_detection/uavrt_detection.c
	$(CC) $(CFLAGS) -o "$@" "$<"


DetectorConfig.c.o : $(START_DIR)/codegen/lib/uavrt_detection/DetectorConfig.c
	$(CC) $(CFLAGS) -o "$@" "$<"


fileManager.c.o : $(START_DIR)/codegen/lib/uavrt_detection/fileManager.c
	$(CC) $(CFLAGS) -o "$@" "$<"


fgetl.c.o : $(START_DIR)/codegen/lib/uavrt_detection/fgetl.c
	$(CC) $(CFLAGS) -o "$@" "$<"


ftell.c.o : $(START_DIR)/codegen/lib/uavrt_detection/ftell.c
	$(CC) $(CFLAGS) -o "$@" "$<"


fseek.c.o : $(START_DIR)/codegen/lib/uavrt_detection/fseek.c
	$(CC) $(CFLAGS) -o "$@" "$<"


find.c.o : $(START_DIR)/codegen/lib/uavrt_detection/find.c
	$(CC) $(CFLAGS) -o "$@" "$<"


str2double.c.o : $(START_DIR)/codegen/lib/uavrt_detection/str2double.c
	$(CC) $(CFLAGS) -o "$@" "$<"


str2double1.c.o : $(START_DIR)/codegen/lib/uavrt_detection/str2double1.c
	$(CC) $(CFLAGS) -o "$@" "$<"


str2matrix.c.o : $(START_DIR)/codegen/lib/uavrt_detection/str2matrix.c
	$(CC) $(CFLAGS) -o "$@" "$<"


makepulsestruc.c.o : $(START_DIR)/codegen/lib/uavrt_detection/makepulsestruc.c
	$(CC) $(CFLAGS) -o "$@" "$<"


pulsestats.c.o : $(START_DIR)/codegen/lib/uavrt_detection/pulsestats.c
	$(CC) $(CFLAGS) -o "$@" "$<"


validator_check_size.c.o : $(START_DIR)/codegen/lib/uavrt_detection/validator_check_size.c
	$(CC) $(CFLAGS) -o "$@" "$<"


waveform.c.o : $(START_DIR)/codegen/lib/uavrt_detection/waveform.c
	$(CC) $(CFLAGS) -o "$@" "$<"


validate_print_arguments.c.o : $(START_DIR)/codegen/lib/uavrt_detection/validate_print_arguments.c
	$(CC) $(CFLAGS) -o "$@" "$<"


AsyncBuffer.c.o : $(START_DIR)/codegen/lib/uavrt_detection/AsyncBuffer.c
	$(CC) $(CFLAGS) -o "$@" "$<"


AsyncBuffercgHelper.c.o : $(START_DIR)/codegen/lib/uavrt_detection/AsyncBuffercgHelper.c
	$(CC) $(CFLAGS) -o "$@" "$<"


wgn.c.o : $(START_DIR)/codegen/lib/uavrt_detection/wgn.c
	$(CC) $(CFLAGS) -o "$@" "$<"


randn.c.o : $(START_DIR)/codegen/lib/uavrt_detection/randn.c
	$(CC) $(CFLAGS) -o "$@" "$<"


stft.c.o : $(START_DIR)/codegen/lib/uavrt_detection/stft.c
	$(CC) $(CFLAGS) -o "$@" "$<"


computeDFT.c.o : $(START_DIR)/codegen/lib/uavrt_detection/computeDFT.c
	$(CC) $(CFLAGS) -o "$@" "$<"


FFTImplementationCallback.c.o : $(START_DIR)/codegen/lib/uavrt_detection/FFTImplementationCallback.c
	$(CC) $(CFLAGS) -o "$@" "$<"


psdfreqvec.c.o : $(START_DIR)/codegen/lib/uavrt_detection/psdfreqvec.c
	$(CC) $(CFLAGS) -o "$@" "$<"


wfmstft.c.o : $(START_DIR)/codegen/lib/uavrt_detection/wfmstft.c
	$(CC) $(CFLAGS) -o "$@" "$<"


abs.c.o : $(START_DIR)/codegen/lib/uavrt_detection/abs.c
	$(CC) $(CFLAGS) -o "$@" "$<"


movSumProdOrMean.c.o : $(START_DIR)/codegen/lib/uavrt_detection/movSumProdOrMean.c
	$(CC) $(CFLAGS) -o "$@" "$<"


quickselect.c.o : $(START_DIR)/codegen/lib/uavrt_detection/quickselect.c
	$(CC) $(CFLAGS) -o "$@" "$<"


repmat.c.o : $(START_DIR)/codegen/lib/uavrt_detection/repmat.c
	$(CC) $(CFLAGS) -o "$@" "$<"


mean.c.o : $(START_DIR)/codegen/lib/uavrt_detection/mean.c
	$(CC) $(CFLAGS) -o "$@" "$<"


channelreceiver.c.o : $(START_DIR)/codegen/lib/uavrt_detection/channelreceiver.c
	$(CC) $(CFLAGS) -o "$@" "$<"


pause.c.o : $(START_DIR)/codegen/lib/uavrt_detection/pause.c
	$(CC) $(CFLAGS) -o "$@" "$<"


colon.c.o : $(START_DIR)/codegen/lib/uavrt_detection/colon.c
	$(CC) $(CFLAGS) -o "$@" "$<"


fwrite.c.o : $(START_DIR)/codegen/lib/uavrt_detection/fwrite.c
	$(CC) $(CFLAGS) -o "$@" "$<"


tic.c.o : $(START_DIR)/codegen/lib/uavrt_detection/tic.c
	$(CC) $(CFLAGS) -o "$@" "$<"


timeKeeper.c.o : $(START_DIR)/codegen/lib/uavrt_detection/timeKeeper.c
	$(CC) $(CFLAGS) -o "$@" "$<"


diff.c.o : $(START_DIR)/codegen/lib/uavrt_detection/diff.c
	$(CC) $(CFLAGS) -o "$@" "$<"


sum.c.o : $(START_DIR)/codegen/lib/uavrt_detection/sum.c
	$(CC) $(CFLAGS) -o "$@" "$<"


string1.c.o : $(START_DIR)/codegen/lib/uavrt_detection/string1.c
	$(CC) $(CFLAGS) -o "$@" "$<"


toc.c.o : $(START_DIR)/codegen/lib/uavrt_detection/toc.c
	$(CC) $(CFLAGS) -o "$@" "$<"


linspace.c.o : $(START_DIR)/codegen/lib/uavrt_detection/linspace.c
	$(CC) $(CFLAGS) -o "$@" "$<"


buildtimecorrelatormatrix.c.o : $(START_DIR)/codegen/lib/uavrt_detection/buildtimecorrelatormatrix.c
	$(CC) $(CFLAGS) -o "$@" "$<"


unique.c.o : $(START_DIR)/codegen/lib/uavrt_detection/unique.c
	$(CC) $(CFLAGS) -o "$@" "$<"


sortLE.c.o : $(START_DIR)/codegen/lib/uavrt_detection/sortLE.c
	$(CC) $(CFLAGS) -o "$@" "$<"


minOrMax.c.o : $(START_DIR)/codegen/lib/uavrt_detection/minOrMax.c
	$(CC) $(CFLAGS) -o "$@" "$<"


mtimes.c.o : $(START_DIR)/codegen/lib/uavrt_detection/mtimes.c
	$(CC) $(CFLAGS) -o "$@" "$<"


evfit.c.o : $(START_DIR)/codegen/lib/uavrt_detection/evfit.c
	$(CC) $(CFLAGS) -o "$@" "$<"


fzero.c.o : $(START_DIR)/codegen/lib/uavrt_detection/fzero.c
	$(CC) $(CFLAGS) -o "$@" "$<"


interp1.c.o : $(START_DIR)/codegen/lib/uavrt_detection/interp1.c
	$(CC) $(CFLAGS) -o "$@" "$<"


allOrAny.c.o : $(START_DIR)/codegen/lib/uavrt_detection/allOrAny.c
	$(CC) $(CFLAGS) -o "$@" "$<"


all.c.o : $(START_DIR)/codegen/lib/uavrt_detection/all.c
	$(CC) $(CFLAGS) -o "$@" "$<"


unaryMinOrMax.c.o : $(START_DIR)/codegen/lib/uavrt_detection/unaryMinOrMax.c
	$(CC) $(CFLAGS) -o "$@" "$<"


incohsumtoeplitz.c.o : $(START_DIR)/codegen/lib/uavrt_detection/incohsumtoeplitz.c
	$(CC) $(CFLAGS) -o "$@" "$<"


locBsearch.c.o : $(START_DIR)/codegen/lib/uavrt_detection/locBsearch.c
	$(CC) $(CFLAGS) -o "$@" "$<"


sparse.c.o : $(START_DIR)/codegen/lib/uavrt_detection/sparse.c
	$(CC) $(CFLAGS) -o "$@" "$<"


any.c.o : $(START_DIR)/codegen/lib/uavrt_detection/any.c
	$(CC) $(CFLAGS) -o "$@" "$<"


sparse1.c.o : $(START_DIR)/codegen/lib/uavrt_detection/sparse1.c
	$(CC) $(CFLAGS) -o "$@" "$<"


not.c.o : $(START_DIR)/codegen/lib/uavrt_detection/not.c
	$(CC) $(CFLAGS) -o "$@" "$<"


eyeLike.c.o : $(START_DIR)/codegen/lib/uavrt_detection/eyeLike.c
	$(CC) $(CFLAGS) -o "$@" "$<"


imresize.c.o : $(START_DIR)/codegen/lib/uavrt_detection/imresize.c
	$(CC) $(CFLAGS) -o "$@" "$<"


ifWhileCond.c.o : $(START_DIR)/codegen/lib/uavrt_detection/ifWhileCond.c
	$(CC) $(CFLAGS) -o "$@" "$<"


horzcatStructList.c.o : $(START_DIR)/codegen/lib/uavrt_detection/horzcatStructList.c
	$(CC) $(CFLAGS) -o "$@" "$<"


blockedSummation.c.o : $(START_DIR)/codegen/lib/uavrt_detection/blockedSummation.c
	$(CC) $(CFLAGS) -o "$@" "$<"


waveformcopy.c.o : $(START_DIR)/codegen/lib/uavrt_detection/waveformcopy.c
	$(CC) $(CFLAGS) -o "$@" "$<"


controlreceiver.c.o : $(START_DIR)/codegen/lib/uavrt_detection/controlreceiver.c
	$(CC) $(CFLAGS) -o "$@" "$<"


threshold.c.o : $(START_DIR)/codegen/lib/uavrt_detection/threshold.c
	$(CC) $(CFLAGS) -o "$@" "$<"


handle.c.o : $(START_DIR)/codegen/lib/uavrt_detection/handle.c
	$(CC) $(CFLAGS) -o "$@" "$<"


SystemCore.c.o : $(START_DIR)/codegen/lib/uavrt_detection/SystemCore.c
	$(CC) $(CFLAGS) -o "$@" "$<"


setup.c.o : $(START_DIR)/codegen/lib/uavrt_detection/setup.c
	$(CC) $(CFLAGS) -o "$@" "$<"


eml_rand_mt19937ar_stateful.c.o : $(START_DIR)/codegen/lib/uavrt_detection/eml_rand_mt19937ar_stateful.c
	$(CC) $(CFLAGS) -o "$@" "$<"


CoderTimeAPI.c.o : $(START_DIR)/codegen/lib/uavrt_detection/CoderTimeAPI.c
	$(CC) $(CFLAGS) -o "$@" "$<"


strcmp.c.o : $(START_DIR)/codegen/lib/uavrt_detection/strcmp.c
	$(CC) $(CFLAGS) -o "$@" "$<"


sort.c.o : $(START_DIR)/codegen/lib/uavrt_detection/sort.c
	$(CC) $(CFLAGS) -o "$@" "$<"


sortIdx.c.o : $(START_DIR)/codegen/lib/uavrt_detection/sortIdx.c
	$(CC) $(CFLAGS) -o "$@" "$<"


eml_rand_mt19937ar.c.o : $(START_DIR)/codegen/lib/uavrt_detection/eml_rand_mt19937ar.c
	$(CC) $(CFLAGS) -o "$@" "$<"


insertionsort.c.o : $(START_DIR)/codegen/lib/uavrt_detection/insertionsort.c
	$(CC) $(CFLAGS) -o "$@" "$<"


introsort.c.o : $(START_DIR)/codegen/lib/uavrt_detection/introsort.c
	$(CC) $(CFLAGS) -o "$@" "$<"


heapsort.c.o : $(START_DIR)/codegen/lib/uavrt_detection/heapsort.c
	$(CC) $(CFLAGS) -o "$@" "$<"


fillIn.c.o : $(START_DIR)/codegen/lib/uavrt_detection/fillIn.c
	$(CC) $(CFLAGS) -o "$@" "$<"


parenAssign2D.c.o : $(START_DIR)/codegen/lib/uavrt_detection/parenAssign2D.c
	$(CC) $(CFLAGS) -o "$@" "$<"


circshift.c.o : $(START_DIR)/codegen/lib/uavrt_detection/circshift.c
	$(CC) $(CFLAGS) -o "$@" "$<"


fftshift.c.o : $(START_DIR)/codegen/lib/uavrt_detection/fftshift.c
	$(CC) $(CFLAGS) -o "$@" "$<"


div.c.o : $(START_DIR)/codegen/lib/uavrt_detection/div.c
	$(CC) $(CFLAGS) -o "$@" "$<"


weightingmatrix.c.o : $(START_DIR)/codegen/lib/uavrt_detection/weightingmatrix.c
	$(CC) $(CFLAGS) -o "$@" "$<"


assembleWq.c.o : $(START_DIR)/codegen/lib/uavrt_detection/assembleWq.c
	$(CC) $(CFLAGS) -o "$@" "$<"


uavrt_detection_emxutil.c.o : $(START_DIR)/codegen/lib/uavrt_detection/uavrt_detection_emxutil.c
	$(CC) $(CFLAGS) -o "$@" "$<"


uavrt_detection_rtwutil.c.o : $(START_DIR)/codegen/lib/uavrt_detection/uavrt_detection_rtwutil.c
	$(CC) $(CFLAGS) -o "$@" "$<"


DAHostLib_Network.c.o : $(MATLAB_ROOT)/toolbox/shared/spc/src_ml/extern/src/DAHostLib_Network.c
	$(CC) $(CFLAGS) -o "$@" "$<"


DAHostLib_rtw.c.o : $(MATLAB_ROOT)/toolbox/shared/spc/src_ml/extern/src/DAHostLib_rtw.c
	$(CC) $(CFLAGS) -o "$@" "$<"


linuxUDP.c.o : $(MATLAB_WORKSPACE)/Users/Don/Documents/MATLAB/SupportPackages/R2022b/toolbox/realtime/targets/raspi/src/udp/linuxUDP.c
	$(CC) $(CFLAGS) -o "$@" "$<"


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : rtw_proj.tmw $(MAKEFILE)


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	echo "### PRODUCT = $(PRODUCT)"
	echo "### PRODUCT_TYPE = $(PRODUCT_TYPE)"
	echo "### BUILD_TYPE = $(BUILD_TYPE)"
	echo "### INCLUDES = $(INCLUDES)"
	echo "### DEFINES = $(DEFINES)"
	echo "### ALL_SRCS = $(ALL_SRCS)"
	echo "### ALL_OBJS = $(ALL_OBJS)"
	echo "### LIBS = $(LIBS)"
	echo "### MODELREF_LIBS = $(MODELREF_LIBS)"
	echo "### SYSTEM_LIBS = $(SYSTEM_LIBS)"
	echo "### TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS)"
	echo "### ASFLAGS = $(ASFLAGS)"
	echo "### CFLAGS = $(CFLAGS)"
	echo "### LDFLAGS = $(LDFLAGS)"
	echo "### SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	echo "### CPPFLAGS = $(CPPFLAGS)"
	echo "### CPP_LDFLAGS = $(CPP_LDFLAGS)"
	echo "### CPP_SHAREDLIB_LDFLAGS = $(CPP_SHAREDLIB_LDFLAGS)"
	echo "### ARFLAGS = $(ARFLAGS)"
	echo "### MEX_CFLAGS = $(MEX_CFLAGS)"
	echo "### MEX_CPPFLAGS = $(MEX_CPPFLAGS)"
	echo "### MEX_LDFLAGS = $(MEX_LDFLAGS)"
	echo "### MEX_CPPLDFLAGS = $(MEX_CPPLDFLAGS)"
	echo "### DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS)"
	echo "### EXECUTE_FLAGS = $(EXECUTE_FLAGS)"
	echo "### MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "### Deleting all derived files..."
	$(RM) $(PRODUCT)
	$(RM) $(ALL_OBJS)
	$(RM) *.c.dep
	$(RM) *.cpp.dep
	$(ECHO) "### Deleted all derived files."


