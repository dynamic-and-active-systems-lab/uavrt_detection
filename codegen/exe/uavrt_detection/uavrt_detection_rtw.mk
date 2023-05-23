###########################################################################
## Makefile generated for component 'uavrt_detection'. 
## 
## Makefile     : uavrt_detection_rtw.mk
## Generated on : Tue Feb 14 10:07:34 2023
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
MATLAB_ROOT               = /Applications/MATLAB_R2023a.app
MATLAB_BIN                = /Applications/MATLAB_R2023a.app/bin
MATLAB_ARCH_BIN           = $(MATLAB_BIN)/maci64
START_DIR                 = /Users/mshafer/Desktop/PLAYGROUND/CODE_TOEPLITZ/uavrt_detection
TGT_FCN_LIB               = ISO_C++11
SOLVER_OBJ                = 
CLASSIC_INTERFACE         = 0
MODEL_HAS_DYNAMICALLY_LOADED_SFCNS = 
RELATIVE_PATH_TO_ANCHOR   = ../../..
C_STANDARD_OPTS           = -fno-common -fexceptions
CPP_STANDARD_OPTS         = -std=c++14 -fno-common -fexceptions

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          Xcode with Clang | gmake (64-bit Mac)
# Supported Version(s):    
# ToolchainInfo Version:   2023a
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

ARCHS             = x86_64
XCODE_SDK_VER     = $(shell perl $(MATLAB_ROOT)/rtw/c/tools/macsdkver.pl)
XCODE_SDK         = MacOSX$(XCODE_SDK_VER).sdk
XCODE_DEVEL_DIR   = $(shell xcode-select -print-path)
XCODE_SDK_ROOT    = $(XCODE_DEVEL_DIR)/Platforms/MacOSX.platform/Developer/SDKs/$(XCODE_SDK)

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = 

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# C Compiler: Clang C Compiler
CC = xcrun clang

# Linker: Clang Linker
LD = xcrun clang++

# C++ Compiler: Clang C++ Compiler
CPP = xcrun clang++

# C++ Linker: Clang C++ Linker
CPP_LD = xcrun clang++

# Archiver: Clang Archiver
AR = xcrun ar

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_ARCH_BIN)
MEX = "$(MEX_PATH)/mex"

# Download: Download
DOWNLOAD =

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: GMAKE Utility
MAKE_PATH = %MATLAB%/bin/maci64
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
CFLAGS               = -c -isysroot $(XCODE_SDK_ROOT) -arch $(ARCHS) $(C_STANDARD_OPTS) -mmacosx-version-min=10.15 \
                       -O3
CPPFLAGS             = -c -isysroot $(XCODE_SDK_ROOT) -arch $(ARCHS) $(CPP_STANDARD_OPTS) -mmacosx-version-min=10.15 \
                       -O3
CPP_LDFLAGS          = -arch $(ARCHS) -isysroot $(XCODE_SDK_ROOT) -Wl,-rpath,@executable_path -Wl,-rpath,@executable_path/$(RELATIVE_PATH_TO_ANCHOR)
CPP_SHAREDLIB_LDFLAGS  = -arch $(ARCHS)  \
                         -dynamiclib -install_name @rpath/$(notdir $(PRODUCT)) -isysroot $(XCODE_SDK_ROOT) \
                         -Wl,$(LD_NAMESPACE) $(LD_UNDEFS)
DOWNLOAD_FLAGS       =
EXECUTE_FLAGS        =
LDFLAGS              = -arch $(ARCHS) -isysroot $(XCODE_SDK_ROOT) -Wl,-rpath,@executable_path -Wl,-rpath,@executable_path/$(RELATIVE_PATH_TO_ANCHOR)
MEX_CPPFLAGS         =
MEX_CPPLDFLAGS       =
MEX_CFLAGS           =
MEX_LDFLAGS          =
MAKE_FLAGS           = -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    = -arch $(ARCHS)  \
                       -dynamiclib -install_name @rpath/$(notdir $(PRODUCT)) -isysroot $(XCODE_SDK_ROOT) \
                       -Wl,$(LD_NAMESPACE) $(LD_UNDEFS)



###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = $(START_DIR)/uavrt_detection
PRODUCT_TYPE = "executable"
BUILD_TYPE = "Executable"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = -I$(START_DIR)/codegen/exe/uavrt_detection -I$(START_DIR) -I$(START_DIR)/codegen/exe/uavrt_detection/examples -I$(MATLAB_ROOT)/toolbox/shared/spc/src_ml/extern/include -I$(MATLAB_ROOT)/extern/include

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

SRCS = $(START_DIR)/codegen/exe/uavrt_detection/coder_posix_time.c $(START_DIR)/codegen/exe/uavrt_detection/coder_fileops.c $(START_DIR)/codegen/exe/uavrt_detection/uavrt_detection_data.cpp $(START_DIR)/codegen/exe/uavrt_detection/rt_nonfinite.cpp $(START_DIR)/codegen/exe/uavrt_detection/rtGetNaN.cpp $(START_DIR)/codegen/exe/uavrt_detection/rtGetInf.cpp $(START_DIR)/codegen/exe/uavrt_detection/uavrt_detection_initialize.cpp $(START_DIR)/codegen/exe/uavrt_detection/uavrt_detection_terminate.cpp $(START_DIR)/codegen/exe/uavrt_detection/uavrt_detection.cpp $(START_DIR)/codegen/exe/uavrt_detection/fileManager.cpp $(START_DIR)/codegen/exe/uavrt_detection/fgetl.cpp $(START_DIR)/codegen/exe/uavrt_detection/feof.cpp $(START_DIR)/codegen/exe/uavrt_detection/ftell.cpp $(START_DIR)/codegen/exe/uavrt_detection/fseek.cpp $(START_DIR)/codegen/exe/uavrt_detection/find.cpp $(START_DIR)/codegen/exe/uavrt_detection/str2double.cpp $(START_DIR)/codegen/exe/uavrt_detection/str2matrix.cpp $(START_DIR)/codegen/exe/uavrt_detection/validator_check_size.cpp $(START_DIR)/codegen/exe/uavrt_detection/lower.cpp $(START_DIR)/codegen/exe/uavrt_detection/strtok.cpp $(START_DIR)/codegen/exe/uavrt_detection/makepulsestruc.cpp $(START_DIR)/codegen/exe/uavrt_detection/validate_print_arguments.cpp $(START_DIR)/codegen/exe/uavrt_detection/colon.cpp $(START_DIR)/codegen/exe/uavrt_detection/wgn.cpp $(START_DIR)/codegen/exe/uavrt_detection/randn.cpp $(START_DIR)/codegen/exe/uavrt_detection/stft.cpp $(START_DIR)/codegen/exe/uavrt_detection/validateattributes.cpp $(START_DIR)/codegen/exe/uavrt_detection/computeDFT.cpp $(START_DIR)/codegen/exe/uavrt_detection/psdfreqvec.cpp $(START_DIR)/codegen/exe/uavrt_detection/iseven.cpp $(START_DIR)/codegen/exe/uavrt_detection/indexShapeCheck.cpp $(START_DIR)/codegen/exe/uavrt_detection/abs.cpp $(START_DIR)/codegen/exe/uavrt_detection/movSumProdOrMean.cpp $(START_DIR)/codegen/exe/uavrt_detection/quickselect.cpp $(START_DIR)/codegen/exe/uavrt_detection/repmat.cpp $(START_DIR)/codegen/exe/uavrt_detection/assertValidSizeArg.cpp $(START_DIR)/codegen/exe/uavrt_detection/mean.cpp $(START_DIR)/codegen/exe/uavrt_detection/getLocalTime.cpp $(START_DIR)/codegen/exe/uavrt_detection/plus.cpp $(START_DIR)/codegen/exe/uavrt_detection/channelreceiver.cpp $(START_DIR)/codegen/exe/uavrt_detection/tic.cpp $(START_DIR)/codegen/exe/uavrt_detection/timeKeeper.cpp $(START_DIR)/codegen/exe/uavrt_detection/pause.cpp $(START_DIR)/codegen/exe/uavrt_detection/singlecomplex2int.cpp $(START_DIR)/codegen/exe/uavrt_detection/fwrite.cpp $(START_DIR)/codegen/exe/uavrt_detection/toc.cpp $(START_DIR)/codegen/exe/uavrt_detection/diff.cpp $(START_DIR)/codegen/exe/uavrt_detection/sum.cpp $(START_DIR)/codegen/exe/uavrt_detection/linspace.cpp $(START_DIR)/codegen/exe/uavrt_detection/norm.cpp $(START_DIR)/codegen/exe/uavrt_detection/buildtimecorrelatormatrix.cpp $(START_DIR)/codegen/exe/uavrt_detection/unique.cpp $(START_DIR)/codegen/exe/uavrt_detection/sortLE.cpp $(START_DIR)/codegen/exe/uavrt_detection/minOrMax.cpp $(START_DIR)/codegen/exe/uavrt_detection/sparse.cpp $(START_DIR)/codegen/exe/uavrt_detection/unaryMinOrMax.cpp $(START_DIR)/codegen/exe/uavrt_detection/evfit.cpp $(START_DIR)/codegen/exe/uavrt_detection/fzero.cpp $(START_DIR)/codegen/exe/uavrt_detection/interp1.cpp $(START_DIR)/codegen/exe/uavrt_detection/allOrAny.cpp $(START_DIR)/codegen/exe/uavrt_detection/all.cpp $(START_DIR)/codegen/exe/uavrt_detection/incohsumtoeplitz.cpp $(START_DIR)/codegen/exe/uavrt_detection/locBsearch.cpp $(START_DIR)/codegen/exe/uavrt_detection/any1.cpp $(START_DIR)/codegen/exe/uavrt_detection/sub2ind.cpp $(START_DIR)/codegen/exe/uavrt_detection/bigProduct.cpp $(START_DIR)/codegen/exe/uavrt_detection/ind2sub.cpp $(START_DIR)/codegen/exe/uavrt_detection/mtimes.cpp $(START_DIR)/codegen/exe/uavrt_detection/imresize.cpp $(START_DIR)/codegen/exe/uavrt_detection/assertCompatibleDims.cpp $(START_DIR)/codegen/exe/uavrt_detection/ifWhileCond.cpp $(START_DIR)/codegen/exe/uavrt_detection/horzcatStructList.cpp $(START_DIR)/codegen/exe/uavrt_detection/blockedSummation.cpp $(START_DIR)/codegen/exe/uavrt_detection/waveformcopy.cpp $(START_DIR)/codegen/exe/uavrt_detection/mod.cpp $(START_DIR)/codegen/exe/uavrt_detection/dec2hex.cpp $(START_DIR)/codegen/exe/uavrt_detection/dec2bin.cpp $(START_DIR)/codegen/exe/uavrt_detection/controlreceiver.cpp $(START_DIR)/codegen/exe/uavrt_detection/pwd.cpp $(START_DIR)/codegen/exe/uavrt_detection/setup.cpp $(START_DIR)/codegen/exe/uavrt_detection/eml_rand_mt19937ar_stateful.cpp $(START_DIR)/codegen/exe/uavrt_detection/examples/main.cpp $(START_DIR)/codegen/exe/uavrt_detection/CoderTimeAPI.cpp $(START_DIR)/codegen/exe/uavrt_detection/strcmp.cpp $(START_DIR)/codegen/exe/uavrt_detection/eml_int_forloop_overflow_check.cpp $(START_DIR)/codegen/exe/uavrt_detection/sort.cpp $(START_DIR)/codegen/exe/uavrt_detection/sortIdx.cpp $(START_DIR)/codegen/exe/uavrt_detection/eml_rand_mt19937ar.cpp $(START_DIR)/codegen/exe/uavrt_detection/formatSTFTOutput.cpp $(START_DIR)/codegen/exe/uavrt_detection/insertionsort.cpp $(START_DIR)/codegen/exe/uavrt_detection/introsort.cpp $(START_DIR)/codegen/exe/uavrt_detection/heapsort.cpp $(START_DIR)/codegen/exe/uavrt_detection/circshift.cpp $(START_DIR)/codegen/exe/uavrt_detection/sqrt.cpp $(START_DIR)/codegen/exe/uavrt_detection/log10.cpp $(START_DIR)/codegen/exe/uavrt_detection/fftshift.cpp $(START_DIR)/codegen/exe/uavrt_detection/wfmstft.cpp $(START_DIR)/codegen/exe/uavrt_detection/div.cpp $(START_DIR)/codegen/exe/uavrt_detection/weightingmatrix.cpp $(START_DIR)/codegen/exe/uavrt_detection/assembleWq.cpp $(START_DIR)/codegen/exe/uavrt_detection/waveform.cpp $(START_DIR)/codegen/exe/uavrt_detection/function_handle.cpp $(START_DIR)/codegen/exe/uavrt_detection/vecfind.cpp $(START_DIR)/codegen/exe/uavrt_detection/threshold.cpp $(START_DIR)/codegen/exe/uavrt_detection/string1.cpp $(START_DIR)/codegen/exe/uavrt_detection/DetectorConfig.cpp $(START_DIR)/codegen/exe/uavrt_detection/pulsestats.cpp $(START_DIR)/codegen/exe/uavrt_detection/AsyncBuffercgHelper.cpp $(START_DIR)/codegen/exe/uavrt_detection/AsyncBuffer.cpp $(START_DIR)/codegen/exe/uavrt_detection/UDPSender.cpp $(START_DIR)/codegen/exe/uavrt_detection/datetime.cpp $(START_DIR)/codegen/exe/uavrt_detection/pulseOut.cpp $(START_DIR)/codegen/exe/uavrt_detection/UDPReceiver.cpp $(START_DIR)/codegen/exe/uavrt_detection/sparse1.cpp $(START_DIR)/codegen/exe/uavrt_detection/FFTImplementationCallback.cpp $(START_DIR)/codegen/exe/uavrt_detection/uavrt_detection_rtwutil.cpp $(MATLAB_ROOT)/toolbox/shared/spc/src_ml/extern/src/DAHostLib_Network.c $(MATLAB_ROOT)/toolbox/shared/spc/src_ml/extern/src/DAHostLib_rtw.c

ALL_SRCS = $(SRCS)

###########################################################################
## OBJECTS
###########################################################################

OBJS = coder_posix_time.o coder_fileops.o uavrt_detection_data.o rt_nonfinite.o rtGetNaN.o rtGetInf.o uavrt_detection_initialize.o uavrt_detection_terminate.o uavrt_detection.o fileManager.o fgetl.o feof.o ftell.o fseek.o find.o str2double.o str2matrix.o validator_check_size.o lower.o strtok.o makepulsestruc.o validate_print_arguments.o colon.o wgn.o randn.o stft.o validateattributes.o computeDFT.o psdfreqvec.o iseven.o indexShapeCheck.o abs.o movSumProdOrMean.o quickselect.o repmat.o assertValidSizeArg.o mean.o getLocalTime.o plus.o channelreceiver.o tic.o timeKeeper.o pause.o singlecomplex2int.o fwrite.o toc.o diff.o sum.o linspace.o norm.o buildtimecorrelatormatrix.o unique.o sortLE.o minOrMax.o sparse.o unaryMinOrMax.o evfit.o fzero.o interp1.o allOrAny.o all.o incohsumtoeplitz.o locBsearch.o any1.o sub2ind.o bigProduct.o ind2sub.o mtimes.o imresize.o assertCompatibleDims.o ifWhileCond.o horzcatStructList.o blockedSummation.o waveformcopy.o mod.o dec2hex.o dec2bin.o controlreceiver.o pwd.o setup.o eml_rand_mt19937ar_stateful.o main.o CoderTimeAPI.o strcmp.o eml_int_forloop_overflow_check.o sort.o sortIdx.o eml_rand_mt19937ar.o formatSTFTOutput.o insertionsort.o introsort.o heapsort.o circshift.o sqrt.o log10.o fftshift.o wfmstft.o div.o weightingmatrix.o assembleWq.o waveform.o function_handle.o vecfind.o threshold.o string1.o DetectorConfig.o pulsestats.o AsyncBuffercgHelper.o AsyncBuffer.o UDPSender.o datetime.o pulseOut.o UDPReceiver.o sparse1.o FFTImplementationCallback.o uavrt_detection_rtwutil.o DAHostLib_Network.o DAHostLib_rtw.o

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

SYSTEM_LIBS =  -L"$(MATLAB_ROOT)/sys/os/maci64" -lm -lstdc++ -liomp5

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_OPTS = -Xpreprocessor -fopenmp -I/Applications/MATLAB_R2023a.app/toolbox/eml/externalDependency/omp/maci64/include -DOpenMP_omp_LIBRARY=/Applications/MATLAB_R2023a.app/sys/os/maci64/libiomp5.dylib
CFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CFLAGS += $(CFLAGS_OPTS) $(CFLAGS_BASIC)

#-----------------
# C++ Compiler
#-----------------

CPPFLAGS_OPTS = -Xpreprocessor -fopenmp -I/Applications/MATLAB_R2023a.app/toolbox/eml/externalDependency/omp/maci64/include -DOpenMP_omp_LIBRARY=/Applications/MATLAB_R2023a.app/sys/os/maci64/libiomp5.dylib
CPPFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CPPFLAGS += $(CPPFLAGS_OPTS) $(CPPFLAGS_BASIC)

#---------------
# C++ Linker
#---------------

CPP_LDFLAGS_ = -Wl,-rpath,$(MATLAB_ROOT)/sys/os/maci64
CPP_LDFLAGS_BLOCKMODULES = -lm -ldl

CPP_LDFLAGS += $(CPP_LDFLAGS_) $(CPP_LDFLAGS_BLOCKMODULES)

#------------------------------
# C++ Shared Library Linker
#------------------------------

CPP_SHAREDLIB_LDFLAGS_ = -Wl,-rpath,$(MATLAB_ROOT)/sys/os/maci64
CPP_SHAREDLIB_LDFLAGS_BLOCKMODULES = -lm -ldl

CPP_SHAREDLIB_LDFLAGS += $(CPP_SHAREDLIB_LDFLAGS_) $(CPP_SHAREDLIB_LDFLAGS_BLOCKMODULES)

#-----------
# Linker
#-----------

LDFLAGS_ = -Wl,-rpath,$(MATLAB_ROOT)/sys/os/maci64
LDFLAGS_BLOCKMODULES = -lm -ldl

LDFLAGS += $(LDFLAGS_) $(LDFLAGS_BLOCKMODULES)

#--------------------------
# Shared Library Linker
#--------------------------

SHAREDLIB_LDFLAGS_ = -Wl,-rpath,$(MATLAB_ROOT)/sys/os/maci64
SHAREDLIB_LDFLAGS_BLOCKMODULES = -lm -ldl

SHAREDLIB_LDFLAGS += $(SHAREDLIB_LDFLAGS_) $(SHAREDLIB_LDFLAGS_BLOCKMODULES)

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


%.o : $(MATLAB_ROOT)/toolbox/shared/spc/src_ml/extern/src/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/toolbox/shared/spc/src_ml/extern/src/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


coder_posix_time.o : $(START_DIR)/codegen/exe/uavrt_detection/coder_posix_time.c
	$(CC) $(CFLAGS) -o "$@" "$<"


coder_fileops.o : $(START_DIR)/codegen/exe/uavrt_detection/coder_fileops.c
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


str2matrix.o : $(START_DIR)/codegen/exe/uavrt_detection/str2matrix.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


validator_check_size.o : $(START_DIR)/codegen/exe/uavrt_detection/validator_check_size.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


lower.o : $(START_DIR)/codegen/exe/uavrt_detection/lower.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


strtok.o : $(START_DIR)/codegen/exe/uavrt_detection/strtok.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


makepulsestruc.o : $(START_DIR)/codegen/exe/uavrt_detection/makepulsestruc.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


validate_print_arguments.o : $(START_DIR)/codegen/exe/uavrt_detection/validate_print_arguments.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


colon.o : $(START_DIR)/codegen/exe/uavrt_detection/colon.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


wgn.o : $(START_DIR)/codegen/exe/uavrt_detection/wgn.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


randn.o : $(START_DIR)/codegen/exe/uavrt_detection/randn.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


stft.o : $(START_DIR)/codegen/exe/uavrt_detection/stft.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


validateattributes.o : $(START_DIR)/codegen/exe/uavrt_detection/validateattributes.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


computeDFT.o : $(START_DIR)/codegen/exe/uavrt_detection/computeDFT.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


psdfreqvec.o : $(START_DIR)/codegen/exe/uavrt_detection/psdfreqvec.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


iseven.o : $(START_DIR)/codegen/exe/uavrt_detection/iseven.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


indexShapeCheck.o : $(START_DIR)/codegen/exe/uavrt_detection/indexShapeCheck.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


abs.o : $(START_DIR)/codegen/exe/uavrt_detection/abs.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


movSumProdOrMean.o : $(START_DIR)/codegen/exe/uavrt_detection/movSumProdOrMean.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


quickselect.o : $(START_DIR)/codegen/exe/uavrt_detection/quickselect.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


repmat.o : $(START_DIR)/codegen/exe/uavrt_detection/repmat.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


assertValidSizeArg.o : $(START_DIR)/codegen/exe/uavrt_detection/assertValidSizeArg.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


mean.o : $(START_DIR)/codegen/exe/uavrt_detection/mean.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


getLocalTime.o : $(START_DIR)/codegen/exe/uavrt_detection/getLocalTime.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


plus.o : $(START_DIR)/codegen/exe/uavrt_detection/plus.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


channelreceiver.o : $(START_DIR)/codegen/exe/uavrt_detection/channelreceiver.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


tic.o : $(START_DIR)/codegen/exe/uavrt_detection/tic.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


timeKeeper.o : $(START_DIR)/codegen/exe/uavrt_detection/timeKeeper.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


pause.o : $(START_DIR)/codegen/exe/uavrt_detection/pause.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


singlecomplex2int.o : $(START_DIR)/codegen/exe/uavrt_detection/singlecomplex2int.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


fwrite.o : $(START_DIR)/codegen/exe/uavrt_detection/fwrite.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


toc.o : $(START_DIR)/codegen/exe/uavrt_detection/toc.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


diff.o : $(START_DIR)/codegen/exe/uavrt_detection/diff.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


sum.o : $(START_DIR)/codegen/exe/uavrt_detection/sum.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


linspace.o : $(START_DIR)/codegen/exe/uavrt_detection/linspace.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


norm.o : $(START_DIR)/codegen/exe/uavrt_detection/norm.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


buildtimecorrelatormatrix.o : $(START_DIR)/codegen/exe/uavrt_detection/buildtimecorrelatormatrix.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


unique.o : $(START_DIR)/codegen/exe/uavrt_detection/unique.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


sortLE.o : $(START_DIR)/codegen/exe/uavrt_detection/sortLE.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


minOrMax.o : $(START_DIR)/codegen/exe/uavrt_detection/minOrMax.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


sparse.o : $(START_DIR)/codegen/exe/uavrt_detection/sparse.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


unaryMinOrMax.o : $(START_DIR)/codegen/exe/uavrt_detection/unaryMinOrMax.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


evfit.o : $(START_DIR)/codegen/exe/uavrt_detection/evfit.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


fzero.o : $(START_DIR)/codegen/exe/uavrt_detection/fzero.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


interp1.o : $(START_DIR)/codegen/exe/uavrt_detection/interp1.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


allOrAny.o : $(START_DIR)/codegen/exe/uavrt_detection/allOrAny.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


all.o : $(START_DIR)/codegen/exe/uavrt_detection/all.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


incohsumtoeplitz.o : $(START_DIR)/codegen/exe/uavrt_detection/incohsumtoeplitz.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


locBsearch.o : $(START_DIR)/codegen/exe/uavrt_detection/locBsearch.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


any1.o : $(START_DIR)/codegen/exe/uavrt_detection/any1.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


sub2ind.o : $(START_DIR)/codegen/exe/uavrt_detection/sub2ind.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


bigProduct.o : $(START_DIR)/codegen/exe/uavrt_detection/bigProduct.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


ind2sub.o : $(START_DIR)/codegen/exe/uavrt_detection/ind2sub.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


mtimes.o : $(START_DIR)/codegen/exe/uavrt_detection/mtimes.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


imresize.o : $(START_DIR)/codegen/exe/uavrt_detection/imresize.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


assertCompatibleDims.o : $(START_DIR)/codegen/exe/uavrt_detection/assertCompatibleDims.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


ifWhileCond.o : $(START_DIR)/codegen/exe/uavrt_detection/ifWhileCond.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


horzcatStructList.o : $(START_DIR)/codegen/exe/uavrt_detection/horzcatStructList.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


blockedSummation.o : $(START_DIR)/codegen/exe/uavrt_detection/blockedSummation.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


waveformcopy.o : $(START_DIR)/codegen/exe/uavrt_detection/waveformcopy.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


mod.o : $(START_DIR)/codegen/exe/uavrt_detection/mod.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


dec2hex.o : $(START_DIR)/codegen/exe/uavrt_detection/dec2hex.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


dec2bin.o : $(START_DIR)/codegen/exe/uavrt_detection/dec2bin.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


controlreceiver.o : $(START_DIR)/codegen/exe/uavrt_detection/controlreceiver.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


pwd.o : $(START_DIR)/codegen/exe/uavrt_detection/pwd.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


setup.o : $(START_DIR)/codegen/exe/uavrt_detection/setup.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


eml_rand_mt19937ar_stateful.o : $(START_DIR)/codegen/exe/uavrt_detection/eml_rand_mt19937ar_stateful.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


main.o : $(START_DIR)/codegen/exe/uavrt_detection/examples/main.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


CoderTimeAPI.o : $(START_DIR)/codegen/exe/uavrt_detection/CoderTimeAPI.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


strcmp.o : $(START_DIR)/codegen/exe/uavrt_detection/strcmp.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


eml_int_forloop_overflow_check.o : $(START_DIR)/codegen/exe/uavrt_detection/eml_int_forloop_overflow_check.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


sort.o : $(START_DIR)/codegen/exe/uavrt_detection/sort.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


sortIdx.o : $(START_DIR)/codegen/exe/uavrt_detection/sortIdx.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


eml_rand_mt19937ar.o : $(START_DIR)/codegen/exe/uavrt_detection/eml_rand_mt19937ar.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


formatSTFTOutput.o : $(START_DIR)/codegen/exe/uavrt_detection/formatSTFTOutput.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


insertionsort.o : $(START_DIR)/codegen/exe/uavrt_detection/insertionsort.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


introsort.o : $(START_DIR)/codegen/exe/uavrt_detection/introsort.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


heapsort.o : $(START_DIR)/codegen/exe/uavrt_detection/heapsort.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


circshift.o : $(START_DIR)/codegen/exe/uavrt_detection/circshift.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


sqrt.o : $(START_DIR)/codegen/exe/uavrt_detection/sqrt.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


log10.o : $(START_DIR)/codegen/exe/uavrt_detection/log10.cpp
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


function_handle.o : $(START_DIR)/codegen/exe/uavrt_detection/function_handle.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


vecfind.o : $(START_DIR)/codegen/exe/uavrt_detection/vecfind.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


threshold.o : $(START_DIR)/codegen/exe/uavrt_detection/threshold.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


string1.o : $(START_DIR)/codegen/exe/uavrt_detection/string1.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


DetectorConfig.o : $(START_DIR)/codegen/exe/uavrt_detection/DetectorConfig.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


pulsestats.o : $(START_DIR)/codegen/exe/uavrt_detection/pulsestats.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


AsyncBuffercgHelper.o : $(START_DIR)/codegen/exe/uavrt_detection/AsyncBuffercgHelper.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


AsyncBuffer.o : $(START_DIR)/codegen/exe/uavrt_detection/AsyncBuffer.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


UDPSender.o : $(START_DIR)/codegen/exe/uavrt_detection/UDPSender.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


datetime.o : $(START_DIR)/codegen/exe/uavrt_detection/datetime.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


pulseOut.o : $(START_DIR)/codegen/exe/uavrt_detection/pulseOut.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


UDPReceiver.o : $(START_DIR)/codegen/exe/uavrt_detection/UDPReceiver.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


sparse1.o : $(START_DIR)/codegen/exe/uavrt_detection/sparse1.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


FFTImplementationCallback.o : $(START_DIR)/codegen/exe/uavrt_detection/FFTImplementationCallback.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


uavrt_detection_rtwutil.o : $(START_DIR)/codegen/exe/uavrt_detection/uavrt_detection_rtwutil.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


DAHostLib_Network.o : $(MATLAB_ROOT)/toolbox/shared/spc/src_ml/extern/src/DAHostLib_Network.c
	$(CC) $(CFLAGS) -o "$@" "$<"


DAHostLib_rtw.o : $(MATLAB_ROOT)/toolbox/shared/spc/src_ml/extern/src/DAHostLib_rtw.c
	$(CC) $(CFLAGS) -o "$@" "$<"


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
	$(ECHO) "### Deleting all derived files ..."
	$(RM) $(PRODUCT)
	$(RM) $(ALL_OBJS)
	$(ECHO) "### Deleted all derived files."


