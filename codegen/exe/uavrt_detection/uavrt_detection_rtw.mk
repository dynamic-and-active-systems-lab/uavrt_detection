###########################################################################
## Makefile generated for component 'uavrt_detection'. 
## 
## Makefile     : uavrt_detection_rtw.mk
## Generated on : Sat Oct 22 12:51:45 2022
## Final product: $(START_DIR)/uavrt_detection
## Product type : executable
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile

PRODUCT_NAME              = uavrt_detection
MAKEFILE                  = uavrt_detection_rtw.mk
MATLAB_ROOT               = /usr/local/MATLAB/R2022b
MATLAB_BIN                = /usr/local/MATLAB/R2022b/bin
MATLAB_ARCH_BIN           = $(MATLAB_BIN)/glnxa64
START_DIR                 = /home/parallels/repos/uavrt_detection
TGT_FCN_LIB               = ISO_C++11
SOLVER_OBJ                = 
CLASSIC_INTERFACE         = 0
MODEL_HAS_DYNAMICALLY_LOADED_SFCNS = 
RELATIVE_PATH_TO_ANCHOR   = ../../..
C_STANDARD_OPTS           = -fwrapv
CPP_STANDARD_OPTS         = -fwrapv

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          GNU gcc/g++ | gmake (64-bit Linux)
# Supported Version(s):    
# ToolchainInfo Version:   2022b
# Specification Revision:  1.0
# 
#-------------------------------------------
# Macros assumed to be defined elsewhere
#-------------------------------------------

# C_STANDARD_OPTS
# CPP_STANDARD_OPTS

#-----------
# MACROS
#-----------

WARN_FLAGS         = -Wall -W -Wwrite-strings -Winline -Wstrict-prototypes -Wnested-externs -Wpointer-arith -Wcast-align
WARN_FLAGS_MAX     = $(WARN_FLAGS) -Wcast-qual -Wshadow
CPP_WARN_FLAGS     = -Wall -W -Wwrite-strings -Winline -Wpointer-arith -Wcast-align
CPP_WARN_FLAGS_MAX = $(CPP_WARN_FLAGS) -Wcast-qual -Wshadow

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = 

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# C Compiler: GNU C Compiler
CC = gcc

# Linker: GNU Linker
LD = g++

# C++ Compiler: GNU C++ Compiler
CPP = g++

# C++ Linker: GNU C++ Linker
CPP_LD = g++

# Archiver: GNU Archiver
AR = ar

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_ARCH_BIN)
MEX = "$(MEX_PATH)/mex"

# Download: Download
DOWNLOAD =

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: GMAKE Utility
MAKE_PATH = %MATLAB%/bin/glnxa64
MAKE = "$(MAKE_PATH)/gmake"


#-------------------------
# Directives/Utilities
#-------------------------

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
RM                  = @rm -f
ECHO                = @echo
MV                  = @mv
RUN                 =

#--------------------------------------
# "Faster Runs" Build Configuration
#--------------------------------------

ARFLAGS              = ruvs
CFLAGS               = -c $(C_STANDARD_OPTS) -fPIC \
                       -O3 -fno-loop-optimize -fno-aggressive-loop-optimizations
CPPFLAGS             = -c $(CPP_STANDARD_OPTS) -fPIC \
                       -O3 -fno-loop-optimize -fno-aggressive-loop-optimizations
CPP_LDFLAGS          =
CPP_SHAREDLIB_LDFLAGS  = -shared -Wl,--no-undefined
DOWNLOAD_FLAGS       =
EXECUTE_FLAGS        =
LDFLAGS              =
MEX_CPPFLAGS         =
MEX_CPPLDFLAGS       =
MEX_CFLAGS           =
MEX_LDFLAGS          =
MAKE_FLAGS           = -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    = -shared -Wl,--no-undefined



###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = $(START_DIR)/uavrt_detection
PRODUCT_TYPE = "executable"
BUILD_TYPE = "Executable"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = -I$(START_DIR)/codegen/exe/uavrt_detection -I$(START_DIR) -I$(START_DIR)/codegen/exe/uavrt_detection/examples -I$(MATLAB_ROOT)/extern/include

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_CUSTOM = 
DEFINES_STANDARD = -DMODEL=uavrt_detection

DEFINES = $(DEFINES_CUSTOM) $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(START_DIR)/udp.cpp $(START_DIR)/codegen/exe/uavrt_detection/coder_posix_time.c $(START_DIR)/codegen/exe/uavrt_detection/uavrt_detection_data.cpp $(START_DIR)/codegen/exe/uavrt_detection/rt_nonfinite.cpp $(START_DIR)/codegen/exe/uavrt_detection/rtGetNaN.cpp $(START_DIR)/codegen/exe/uavrt_detection/rtGetInf.cpp $(START_DIR)/codegen/exe/uavrt_detection/uavrt_detection_initialize.cpp $(START_DIR)/codegen/exe/uavrt_detection/uavrt_detection_terminate.cpp $(START_DIR)/codegen/exe/uavrt_detection/uavrt_detection.cpp $(START_DIR)/codegen/exe/uavrt_detection/fileManager.cpp $(START_DIR)/codegen/exe/uavrt_detection/fgetl.cpp $(START_DIR)/codegen/exe/uavrt_detection/feof.cpp $(START_DIR)/codegen/exe/uavrt_detection/ftell.cpp $(START_DIR)/codegen/exe/uavrt_detection/fseek.cpp $(START_DIR)/codegen/exe/uavrt_detection/find.cpp $(START_DIR)/codegen/exe/uavrt_detection/str2double.cpp $(START_DIR)/codegen/exe/uavrt_detection/str2double1.cpp $(START_DIR)/codegen/exe/uavrt_detection/str2matrix.cpp $(START_DIR)/codegen/exe/uavrt_detection/makepulsestruc.cpp $(START_DIR)/codegen/exe/uavrt_detection/validator_check_size.cpp $(START_DIR)/codegen/exe/uavrt_detection/validate_print_arguments.cpp $(START_DIR)/codegen/exe/uavrt_detection/wgn.cpp $(START_DIR)/codegen/exe/uavrt_detection/randn.cpp $(START_DIR)/codegen/exe/uavrt_detection/stft.cpp $(START_DIR)/codegen/exe/uavrt_detection/computeDFT.cpp $(START_DIR)/codegen/exe/uavrt_detection/psdfreqvec.cpp $(START_DIR)/codegen/exe/uavrt_detection/abs.cpp $(START_DIR)/codegen/exe/uavrt_detection/movSumProdOrMean.cpp $(START_DIR)/codegen/exe/uavrt_detection/quickselect.cpp $(START_DIR)/codegen/exe/uavrt_detection/mean.cpp $(START_DIR)/codegen/exe/uavrt_detection/colon.cpp $(START_DIR)/codegen/exe/uavrt_detection/tic.cpp $(START_DIR)/codegen/exe/uavrt_detection/timeKeeper.cpp $(START_DIR)/codegen/exe/uavrt_detection/diff.cpp $(START_DIR)/codegen/exe/uavrt_detection/sum.cpp $(START_DIR)/codegen/exe/uavrt_detection/toc.cpp $(START_DIR)/codegen/exe/uavrt_detection/linspace.cpp $(START_DIR)/codegen/exe/uavrt_detection/buildtimecorrelatormatrix.cpp $(START_DIR)/codegen/exe/uavrt_detection/unique.cpp $(START_DIR)/codegen/exe/uavrt_detection/sortLE.cpp $(START_DIR)/codegen/exe/uavrt_detection/minOrMax.cpp $(START_DIR)/codegen/exe/uavrt_detection/evfit.cpp $(START_DIR)/codegen/exe/uavrt_detection/fzero.cpp $(START_DIR)/codegen/exe/uavrt_detection/interp1.cpp $(START_DIR)/codegen/exe/uavrt_detection/all.cpp $(START_DIR)/codegen/exe/uavrt_detection/unaryMinOrMax.cpp $(START_DIR)/codegen/exe/uavrt_detection/incohsumtoeplitz.cpp $(START_DIR)/codegen/exe/uavrt_detection/locBsearch.cpp $(START_DIR)/codegen/exe/uavrt_detection/sparse.cpp $(START_DIR)/codegen/exe/uavrt_detection/any1.cpp $(START_DIR)/codegen/exe/uavrt_detection/imresize.cpp $(START_DIR)/codegen/exe/uavrt_detection/repmat.cpp $(START_DIR)/codegen/exe/uavrt_detection/ifWhileCond.cpp $(START_DIR)/codegen/exe/uavrt_detection/blockedSummation.cpp $(START_DIR)/codegen/exe/uavrt_detection/waveformcopy.cpp $(START_DIR)/codegen/exe/uavrt_detection/eml_rand_mt19937ar_stateful.cpp $(START_DIR)/codegen/exe/uavrt_detection/examples/main.cpp $(START_DIR)/codegen/exe/uavrt_detection/CoderTimeAPI.cpp $(START_DIR)/codegen/exe/uavrt_detection/strcmp.cpp $(START_DIR)/codegen/exe/uavrt_detection/sort.cpp $(START_DIR)/codegen/exe/uavrt_detection/sortIdx.cpp $(START_DIR)/codegen/exe/uavrt_detection/eml_rand_mt19937ar.cpp $(START_DIR)/codegen/exe/uavrt_detection/insertionsort.cpp $(START_DIR)/codegen/exe/uavrt_detection/introsort.cpp $(START_DIR)/codegen/exe/uavrt_detection/heapsort.cpp $(START_DIR)/codegen/exe/uavrt_detection/circshift.cpp $(START_DIR)/codegen/exe/uavrt_detection/fftshift.cpp $(START_DIR)/codegen/exe/uavrt_detection/wfmstft.cpp $(START_DIR)/codegen/exe/uavrt_detection/div.cpp $(START_DIR)/codegen/exe/uavrt_detection/weightingmatrix.cpp $(START_DIR)/codegen/exe/uavrt_detection/assembleWq.cpp $(START_DIR)/codegen/exe/uavrt_detection/waveform.cpp $(START_DIR)/codegen/exe/uavrt_detection/threshold.cpp $(START_DIR)/codegen/exe/uavrt_detection/AsyncBuffercgHelper.cpp $(START_DIR)/codegen/exe/uavrt_detection/AsyncBuffer.cpp $(START_DIR)/codegen/exe/uavrt_detection/string1.cpp $(START_DIR)/codegen/exe/uavrt_detection/DetectorConfig.cpp $(START_DIR)/codegen/exe/uavrt_detection/pulsestats.cpp $(START_DIR)/codegen/exe/uavrt_detection/sparse1.cpp $(START_DIR)/codegen/exe/uavrt_detection/FFTImplementationCallback.cpp $(START_DIR)/codegen/exe/uavrt_detection/uavrt_detection_rtwutil.cpp

ALL_SRCS = $(SRCS)

###########################################################################
## OBJECTS
###########################################################################

OBJS = udp.o coder_posix_time.o uavrt_detection_data.o rt_nonfinite.o rtGetNaN.o rtGetInf.o uavrt_detection_initialize.o uavrt_detection_terminate.o uavrt_detection.o fileManager.o fgetl.o feof.o ftell.o fseek.o find.o str2double.o str2double1.o str2matrix.o makepulsestruc.o validator_check_size.o validate_print_arguments.o wgn.o randn.o stft.o computeDFT.o psdfreqvec.o abs.o movSumProdOrMean.o quickselect.o mean.o colon.o tic.o timeKeeper.o diff.o sum.o toc.o linspace.o buildtimecorrelatormatrix.o unique.o sortLE.o minOrMax.o evfit.o fzero.o interp1.o all.o unaryMinOrMax.o incohsumtoeplitz.o locBsearch.o sparse.o any1.o imresize.o repmat.o ifWhileCond.o blockedSummation.o waveformcopy.o eml_rand_mt19937ar_stateful.o main.o CoderTimeAPI.o strcmp.o sort.o sortIdx.o eml_rand_mt19937ar.o insertionsort.o introsort.o heapsort.o circshift.o fftshift.o wfmstft.o div.o weightingmatrix.o assembleWq.o waveform.o threshold.o AsyncBuffercgHelper.o AsyncBuffer.o string1.o DetectorConfig.o pulsestats.o sparse1.o FFTImplementationCallback.o uavrt_detection_rtwutil.o

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

SYSTEM_LIBS =  -L"$(MATLAB_ROOT)/sys/os/glnxa64" -lm -lstdc++ -lgomp

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_OPTS = -fopenmp
CFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CFLAGS += $(CFLAGS_OPTS) $(CFLAGS_BASIC)

#-----------------
# C++ Compiler
#-----------------

CPPFLAGS_OPTS = -fopenmp
CPPFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CPPFLAGS += $(CPPFLAGS_OPTS) $(CPPFLAGS_BASIC)

###########################################################################
## INLINED COMMANDS
###########################################################################

###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build buildobj clean info prebuild download execute


all : build
	@echo "### Successfully generated all binary outputs."


build : prebuild $(PRODUCT)


buildobj : prebuild $(OBJS) $(PREBUILT_OBJS)
	@echo "### Successfully generated all binary outputs."


prebuild : 


download : $(PRODUCT)


execute : download
	@echo "### Invoking postbuild tool "Execute" ..."
	$(EXECUTE) $(EXECUTE_FLAGS)
	@echo "### Done invoking postbuild tool."


###########################################################################
## FINAL TARGET
###########################################################################

#-------------------------------------------
# Create a standalone executable            
#-------------------------------------------

$(PRODUCT) : $(OBJS) $(PREBUILT_OBJS)
	@echo "### Creating standalone executable "$(PRODUCT)" ..."
	$(CPP_LD) $(CPP_LDFLAGS) -o $(PRODUCT) $(OBJS) $(SYSTEM_LIBS) $(TOOLCHAIN_LIBS)
	@echo "### Created: $(PRODUCT)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

%.o : %.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : %.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/codegen/exe/uavrt_detection/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/codegen/exe/uavrt_detection/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/codegen/exe/uavrt_detection/examples/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/codegen/exe/uavrt_detection/examples/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


udp.o : $(START_DIR)/udp.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


coder_posix_time.o : $(START_DIR)/codegen/exe/uavrt_detection/coder_posix_time.c
	$(CC) $(CFLAGS) -o "$@" "$<"


uavrt_detection_data.o : $(START_DIR)/codegen/exe/uavrt_detection/uavrt_detection_data.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


rt_nonfinite.o : $(START_DIR)/codegen/exe/uavrt_detection/rt_nonfinite.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


rtGetNaN.o : $(START_DIR)/codegen/exe/uavrt_detection/rtGetNaN.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


rtGetInf.o : $(START_DIR)/codegen/exe/uavrt_detection/rtGetInf.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


uavrt_detection_initialize.o : $(START_DIR)/codegen/exe/uavrt_detection/uavrt_detection_initialize.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


uavrt_detection_terminate.o : $(START_DIR)/codegen/exe/uavrt_detection/uavrt_detection_terminate.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


uavrt_detection.o : $(START_DIR)/codegen/exe/uavrt_detection/uavrt_detection.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


fileManager.o : $(START_DIR)/codegen/exe/uavrt_detection/fileManager.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


fgetl.o : $(START_DIR)/codegen/exe/uavrt_detection/fgetl.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


feof.o : $(START_DIR)/codegen/exe/uavrt_detection/feof.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


ftell.o : $(START_DIR)/codegen/exe/uavrt_detection/ftell.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


fseek.o : $(START_DIR)/codegen/exe/uavrt_detection/fseek.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


find.o : $(START_DIR)/codegen/exe/uavrt_detection/find.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


str2double.o : $(START_DIR)/codegen/exe/uavrt_detection/str2double.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


str2double1.o : $(START_DIR)/codegen/exe/uavrt_detection/str2double1.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


str2matrix.o : $(START_DIR)/codegen/exe/uavrt_detection/str2matrix.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


makepulsestruc.o : $(START_DIR)/codegen/exe/uavrt_detection/makepulsestruc.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


validator_check_size.o : $(START_DIR)/codegen/exe/uavrt_detection/validator_check_size.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


validate_print_arguments.o : $(START_DIR)/codegen/exe/uavrt_detection/validate_print_arguments.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


wgn.o : $(START_DIR)/codegen/exe/uavrt_detection/wgn.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


randn.o : $(START_DIR)/codegen/exe/uavrt_detection/randn.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


stft.o : $(START_DIR)/codegen/exe/uavrt_detection/stft.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


computeDFT.o : $(START_DIR)/codegen/exe/uavrt_detection/computeDFT.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


psdfreqvec.o : $(START_DIR)/codegen/exe/uavrt_detection/psdfreqvec.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


abs.o : $(START_DIR)/codegen/exe/uavrt_detection/abs.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


movSumProdOrMean.o : $(START_DIR)/codegen/exe/uavrt_detection/movSumProdOrMean.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


quickselect.o : $(START_DIR)/codegen/exe/uavrt_detection/quickselect.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


mean.o : $(START_DIR)/codegen/exe/uavrt_detection/mean.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


colon.o : $(START_DIR)/codegen/exe/uavrt_detection/colon.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


tic.o : $(START_DIR)/codegen/exe/uavrt_detection/tic.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


timeKeeper.o : $(START_DIR)/codegen/exe/uavrt_detection/timeKeeper.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


diff.o : $(START_DIR)/codegen/exe/uavrt_detection/diff.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


sum.o : $(START_DIR)/codegen/exe/uavrt_detection/sum.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


toc.o : $(START_DIR)/codegen/exe/uavrt_detection/toc.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


linspace.o : $(START_DIR)/codegen/exe/uavrt_detection/linspace.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


buildtimecorrelatormatrix.o : $(START_DIR)/codegen/exe/uavrt_detection/buildtimecorrelatormatrix.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


unique.o : $(START_DIR)/codegen/exe/uavrt_detection/unique.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


sortLE.o : $(START_DIR)/codegen/exe/uavrt_detection/sortLE.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


minOrMax.o : $(START_DIR)/codegen/exe/uavrt_detection/minOrMax.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


evfit.o : $(START_DIR)/codegen/exe/uavrt_detection/evfit.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


fzero.o : $(START_DIR)/codegen/exe/uavrt_detection/fzero.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


interp1.o : $(START_DIR)/codegen/exe/uavrt_detection/interp1.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


all.o : $(START_DIR)/codegen/exe/uavrt_detection/all.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


unaryMinOrMax.o : $(START_DIR)/codegen/exe/uavrt_detection/unaryMinOrMax.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


incohsumtoeplitz.o : $(START_DIR)/codegen/exe/uavrt_detection/incohsumtoeplitz.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


locBsearch.o : $(START_DIR)/codegen/exe/uavrt_detection/locBsearch.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


sparse.o : $(START_DIR)/codegen/exe/uavrt_detection/sparse.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


any1.o : $(START_DIR)/codegen/exe/uavrt_detection/any1.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


imresize.o : $(START_DIR)/codegen/exe/uavrt_detection/imresize.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


repmat.o : $(START_DIR)/codegen/exe/uavrt_detection/repmat.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


ifWhileCond.o : $(START_DIR)/codegen/exe/uavrt_detection/ifWhileCond.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


blockedSummation.o : $(START_DIR)/codegen/exe/uavrt_detection/blockedSummation.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


waveformcopy.o : $(START_DIR)/codegen/exe/uavrt_detection/waveformcopy.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


eml_rand_mt19937ar_stateful.o : $(START_DIR)/codegen/exe/uavrt_detection/eml_rand_mt19937ar_stateful.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


main.o : $(START_DIR)/codegen/exe/uavrt_detection/examples/main.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


CoderTimeAPI.o : $(START_DIR)/codegen/exe/uavrt_detection/CoderTimeAPI.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


strcmp.o : $(START_DIR)/codegen/exe/uavrt_detection/strcmp.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


sort.o : $(START_DIR)/codegen/exe/uavrt_detection/sort.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


sortIdx.o : $(START_DIR)/codegen/exe/uavrt_detection/sortIdx.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


eml_rand_mt19937ar.o : $(START_DIR)/codegen/exe/uavrt_detection/eml_rand_mt19937ar.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


insertionsort.o : $(START_DIR)/codegen/exe/uavrt_detection/insertionsort.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


introsort.o : $(START_DIR)/codegen/exe/uavrt_detection/introsort.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


heapsort.o : $(START_DIR)/codegen/exe/uavrt_detection/heapsort.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


circshift.o : $(START_DIR)/codegen/exe/uavrt_detection/circshift.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


fftshift.o : $(START_DIR)/codegen/exe/uavrt_detection/fftshift.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


wfmstft.o : $(START_DIR)/codegen/exe/uavrt_detection/wfmstft.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


div.o : $(START_DIR)/codegen/exe/uavrt_detection/div.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


weightingmatrix.o : $(START_DIR)/codegen/exe/uavrt_detection/weightingmatrix.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


assembleWq.o : $(START_DIR)/codegen/exe/uavrt_detection/assembleWq.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


waveform.o : $(START_DIR)/codegen/exe/uavrt_detection/waveform.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


threshold.o : $(START_DIR)/codegen/exe/uavrt_detection/threshold.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


AsyncBuffercgHelper.o : $(START_DIR)/codegen/exe/uavrt_detection/AsyncBuffercgHelper.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


AsyncBuffer.o : $(START_DIR)/codegen/exe/uavrt_detection/AsyncBuffer.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


string1.o : $(START_DIR)/codegen/exe/uavrt_detection/string1.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


DetectorConfig.o : $(START_DIR)/codegen/exe/uavrt_detection/DetectorConfig.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


pulsestats.o : $(START_DIR)/codegen/exe/uavrt_detection/pulsestats.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


sparse1.o : $(START_DIR)/codegen/exe/uavrt_detection/sparse1.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


FFTImplementationCallback.o : $(START_DIR)/codegen/exe/uavrt_detection/FFTImplementationCallback.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


uavrt_detection_rtwutil.o : $(START_DIR)/codegen/exe/uavrt_detection/uavrt_detection_rtwutil.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : rtw_proj.tmw $(MAKEFILE)


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	@echo "### PRODUCT = $(PRODUCT)"
	@echo "### PRODUCT_TYPE = $(PRODUCT_TYPE)"
	@echo "### BUILD_TYPE = $(BUILD_TYPE)"
	@echo "### INCLUDES = $(INCLUDES)"
	@echo "### DEFINES = $(DEFINES)"
	@echo "### ALL_SRCS = $(ALL_SRCS)"
	@echo "### ALL_OBJS = $(ALL_OBJS)"
	@echo "### LIBS = $(LIBS)"
	@echo "### MODELREF_LIBS = $(MODELREF_LIBS)"
	@echo "### SYSTEM_LIBS = $(SYSTEM_LIBS)"
	@echo "### TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS)"
	@echo "### CFLAGS = $(CFLAGS)"
	@echo "### LDFLAGS = $(LDFLAGS)"
	@echo "### SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	@echo "### CPPFLAGS = $(CPPFLAGS)"
	@echo "### CPP_LDFLAGS = $(CPP_LDFLAGS)"
	@echo "### CPP_SHAREDLIB_LDFLAGS = $(CPP_SHAREDLIB_LDFLAGS)"
	@echo "### ARFLAGS = $(ARFLAGS)"
	@echo "### MEX_CFLAGS = $(MEX_CFLAGS)"
	@echo "### MEX_CPPFLAGS = $(MEX_CPPFLAGS)"
	@echo "### MEX_LDFLAGS = $(MEX_LDFLAGS)"
	@echo "### MEX_CPPLDFLAGS = $(MEX_CPPLDFLAGS)"
	@echo "### DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS)"
	@echo "### EXECUTE_FLAGS = $(EXECUTE_FLAGS)"
	@echo "### MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "### Deleting all derived files..."
	$(RM) $(PRODUCT)
	$(RM) $(ALL_OBJS)
	$(ECHO) "### Deleted all derived files."


