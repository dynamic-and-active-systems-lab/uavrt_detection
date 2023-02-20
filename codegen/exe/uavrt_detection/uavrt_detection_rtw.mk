﻿###########################################################################
## Makefile generated for component 'uavrt_detection'. 
## 
## Makefile     : uavrt_detection_rtw.mk
## Generated on : Mon Feb 20 14:33:47 2023
## Final product: $(START_DIR)\uavrt_detection.exe
## Product type : executable
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile
# COMPILER_COMMAND_FILE   Compiler command listing model reference header paths
# CMD_FILE                Command file

PRODUCT_NAME              = uavrt_detection
MAKEFILE                  = uavrt_detection_rtw.mk
MATLAB_ROOT               = C:\PROGRA~1\MATLAB
MATLAB_BIN                = C:\PROGRA~1\MATLAB\bin
MATLAB_ARCH_BIN           = $(MATLAB_BIN)\win64
START_DIR                 = H:\repos\uavrt_detection
TGT_FCN_LIB               = ISO_C++11
SOLVER_OBJ                = 
CLASSIC_INTERFACE         = 0
MODEL_HAS_DYNAMICALLY_LOADED_SFCNS = 
RELATIVE_PATH_TO_ANCHOR   = ..\..\..
COMPILER_COMMAND_FILE     = uavrt_detection_rtw_comp.rsp
CMD_FILE                  = uavrt_detection_rtw.rsp
C_STANDARD_OPTS           = 
CPP_STANDARD_OPTS         = 
NODEBUG                   = 1

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          Microsoft Visual C++ 2022 v17.0 | nmake (64-bit Windows)
# Supported Version(s):    17.0
# ToolchainInfo Version:   2022a
# Specification Revision:  1.0
# 
#-------------------------------------------
# Macros assumed to be defined elsewhere
#-------------------------------------------

# NODEBUG
# cvarsdll
# cvarsmt
# conlibsmt
# ldebug
# conflags
# cflags

#-----------
# MACROS
#-----------

MW_EXTERNLIB_DIR    = $(MATLAB_ROOT)\extern\lib\win64\microsoft
MW_LIB_DIR          = $(MATLAB_ROOT)\lib\win64
CPU                 = AMD64
APPVER              = 5.02
CVARSFLAG           = $(cvarsmt)
CFLAGS_ADDITIONAL   = -D_CRT_SECURE_NO_WARNINGS
CPPFLAGS_ADDITIONAL = -EHs -D_CRT_SECURE_NO_WARNINGS /wd4251 /Zc:__cplusplus
LIBS_TOOLCHAIN      = $(conlibs)

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = 

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# C Compiler: Microsoft Visual C Compiler
CC = cl

# Linker: Microsoft Visual C Linker
LD = link

# C++ Compiler: Microsoft Visual C++ Compiler
CPP = cl

# C++ Linker: Microsoft Visual C++ Linker
CPP_LD = link

# Archiver: Microsoft Visual C/C++ Archiver
AR = lib

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_ARCH_BIN)
MEX = "$(MEX_PATH)\mex"

# Download: Download
DOWNLOAD =

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: NMAKE Utility
MAKE = nmake


#-------------------------
# Directives/Utilities
#-------------------------

CDEBUG              = -Zi
C_OUTPUT_FLAG       = -Fo
LDDEBUG             = /DEBUG
OUTPUT_FLAG         = -out:
CPPDEBUG            = -Zi
CPP_OUTPUT_FLAG     = -Fo
CPPLDDEBUG          = /DEBUG
OUTPUT_FLAG         = -out:
ARDEBUG             =
STATICLIB_OUTPUT_FLAG = -out:
MEX_DEBUG           = -g
RM                  = @del
ECHO                = @echo
MV                  = @ren
RUN                 = @cmd /C

#--------------------------------------
# "Faster Runs" Build Configuration
#--------------------------------------

ARFLAGS              = /nologo
CFLAGS               = $(cflags) $(CVARSFLAG) $(CFLAGS_ADDITIONAL) \
                       /O2 /Oy-
CPPFLAGS             = /TP $(cflags) $(CVARSFLAG) $(CPPFLAGS_ADDITIONAL) \
                       /O2 /Oy-
CPP_LDFLAGS          = $(ldebug) $(conflags) $(LIBS_TOOLCHAIN)
CPP_SHAREDLIB_LDFLAGS  = $(ldebug) $(conflags) $(LIBS_TOOLCHAIN) \
                         -dll -def:$(DEF_FILE)
DOWNLOAD_FLAGS       =
EXECUTE_FLAGS        =
LDFLAGS              = $(ldebug) $(conflags) $(LIBS_TOOLCHAIN)
MEX_CPPFLAGS         =
MEX_CPPLDFLAGS       =
MEX_CFLAGS           =
MEX_LDFLAGS          =
MAKE_FLAGS           = -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    = $(ldebug) $(conflags) $(LIBS_TOOLCHAIN) \
                       -dll -def:$(DEF_FILE)



###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = $(START_DIR)\uavrt_detection.exe
PRODUCT_TYPE = "executable"
BUILD_TYPE = "Executable"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = 

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

SRCS = udp.cpp $(START_DIR)\codegen\exe\uavrt_detection\coder_posix_time.c $(START_DIR)\codegen\exe\uavrt_detection\uavrt_detection_data.cpp $(START_DIR)\codegen\exe\uavrt_detection\rt_nonfinite.cpp $(START_DIR)\codegen\exe\uavrt_detection\rtGetNaN.cpp $(START_DIR)\codegen\exe\uavrt_detection\rtGetInf.cpp $(START_DIR)\codegen\exe\uavrt_detection\uavrt_detection_initialize.cpp $(START_DIR)\codegen\exe\uavrt_detection\uavrt_detection_terminate.cpp $(START_DIR)\codegen\exe\uavrt_detection\uavrt_detection.cpp $(START_DIR)\codegen\exe\uavrt_detection\fileManager.cpp $(START_DIR)\codegen\exe\uavrt_detection\fgetl.cpp $(START_DIR)\codegen\exe\uavrt_detection\eml_int_forloop_overflow_check.cpp $(START_DIR)\codegen\exe\uavrt_detection\ftell.cpp $(START_DIR)\codegen\exe\uavrt_detection\fseek.cpp $(START_DIR)\codegen\exe\uavrt_detection\find.cpp $(START_DIR)\codegen\exe\uavrt_detection\str2double.cpp $(START_DIR)\codegen\exe\uavrt_detection\str2matrix.cpp $(START_DIR)\codegen\exe\uavrt_detection\validator_check_size.cpp $(START_DIR)\codegen\exe\uavrt_detection\int2str.cpp $(START_DIR)\codegen\exe\uavrt_detection\strtok.cpp $(START_DIR)\codegen\exe\uavrt_detection\makepulsestruc.cpp $(START_DIR)\codegen\exe\uavrt_detection\validate_print_arguments.cpp $(START_DIR)\codegen\exe\uavrt_detection\colon.cpp $(START_DIR)\codegen\exe\uavrt_detection\wgn.cpp $(START_DIR)\codegen\exe\uavrt_detection\randn.cpp $(START_DIR)\codegen\exe\uavrt_detection\stft.cpp $(START_DIR)\codegen\exe\uavrt_detection\validateattributes.cpp $(START_DIR)\codegen\exe\uavrt_detection\iseven.cpp $(START_DIR)\codegen\exe\uavrt_detection\computeDFT.cpp $(START_DIR)\codegen\exe\uavrt_detection\indexShapeCheck.cpp $(START_DIR)\codegen\exe\uavrt_detection\movSumProdOrMean.cpp $(START_DIR)\codegen\exe\uavrt_detection\median.cpp $(START_DIR)\codegen\exe\uavrt_detection\quickselect.cpp $(START_DIR)\codegen\exe\uavrt_detection\repmat.cpp $(START_DIR)\codegen\exe\uavrt_detection\getLocalTime.cpp $(START_DIR)\codegen\exe\uavrt_detection\plus.cpp $(START_DIR)\codegen\exe\uavrt_detection\tic.cpp $(START_DIR)\codegen\exe\uavrt_detection\timeKeeper.cpp $(START_DIR)\codegen\exe\uavrt_detection\singlecomplex2int.cpp $(START_DIR)\codegen\exe\uavrt_detection\fwrite.cpp $(START_DIR)\codegen\exe\uavrt_detection\toc.cpp $(START_DIR)\codegen\exe\uavrt_detection\diff.cpp $(START_DIR)\codegen\exe\uavrt_detection\sum.cpp $(START_DIR)\codegen\exe\uavrt_detection\sparse.cpp $(START_DIR)\codegen\exe\uavrt_detection\fzero.cpp $(START_DIR)\codegen\exe\uavrt_detection\horzcatStructList.cpp $(START_DIR)\codegen\exe\uavrt_detection\waveformcopy.cpp $(START_DIR)\codegen\exe\uavrt_detection\eml_randn.cpp $(START_DIR)\codegen\exe\uavrt_detection\eml_rand.cpp $(START_DIR)\codegen\exe\uavrt_detection\eml_rand_mt19937ar_stateful.cpp $(START_DIR)\codegen\exe\uavrt_detection\CoderTimeAPI.cpp $(START_DIR)\codegen\exe\uavrt_detection\udpSamplesReceiverRead.cpp $(START_DIR)\codegen\exe\uavrt_detection\strcmp.cpp $(START_DIR)\codegen\exe\uavrt_detection\str2double1.cpp $(START_DIR)\codegen\exe\uavrt_detection\nullAssignment.cpp $(START_DIR)\codegen\exe\uavrt_detection\sort.cpp $(START_DIR)\codegen\exe\uavrt_detection\sortIdx.cpp $(START_DIR)\codegen\exe\uavrt_detection\eml_rand_mt19937ar.cpp $(START_DIR)\codegen\exe\uavrt_detection\unique.cpp $(START_DIR)\codegen\exe\uavrt_detection\insertionsort.cpp $(START_DIR)\codegen\exe\uavrt_detection\introsort.cpp $(START_DIR)\codegen\exe\uavrt_detection\heapsort.cpp $(START_DIR)\codegen\exe\uavrt_detection\wfmstft.cpp $(START_DIR)\codegen\exe\uavrt_detection\assembleWq.cpp $(START_DIR)\codegen\exe\uavrt_detection\string1.cpp $(START_DIR)\codegen\exe\uavrt_detection\DetectorConfig.cpp $(START_DIR)\codegen\exe\uavrt_detection\pulsestats.cpp $(START_DIR)\codegen\exe\uavrt_detection\AsyncBuffercgHelper.cpp $(START_DIR)\codegen\exe\uavrt_detection\AsyncBuffer.cpp $(START_DIR)\codegen\exe\uavrt_detection\threshold.cpp $(START_DIR)\codegen\exe\uavrt_detection\waveform.cpp $(START_DIR)\codegen\exe\uavrt_detection\datetime.cpp $(START_DIR)\codegen\exe\uavrt_detection\FFTImplementationCallback.cpp $(START_DIR)\codegen\exe\uavrt_detection\uavrt_detection_rtwutil.cpp

ALL_SRCS = $(SRCS)

###########################################################################
## OBJECTS
###########################################################################

OBJS = udp.obj coder_posix_time.obj uavrt_detection_data.obj rt_nonfinite.obj rtGetNaN.obj rtGetInf.obj uavrt_detection_initialize.obj uavrt_detection_terminate.obj uavrt_detection.obj fileManager.obj fgetl.obj eml_int_forloop_overflow_check.obj ftell.obj fseek.obj find.obj str2double.obj str2matrix.obj validator_check_size.obj int2str.obj strtok.obj makepulsestruc.obj validate_print_arguments.obj colon.obj wgn.obj randn.obj stft.obj validateattributes.obj iseven.obj computeDFT.obj indexShapeCheck.obj movSumProdOrMean.obj median.obj quickselect.obj repmat.obj getLocalTime.obj plus.obj tic.obj timeKeeper.obj singlecomplex2int.obj fwrite.obj toc.obj diff.obj sum.obj sparse.obj fzero.obj horzcatStructList.obj waveformcopy.obj eml_randn.obj eml_rand.obj eml_rand_mt19937ar_stateful.obj CoderTimeAPI.obj udpSamplesReceiverRead.obj strcmp.obj str2double1.obj nullAssignment.obj sort.obj sortIdx.obj eml_rand_mt19937ar.obj unique.obj insertionsort.obj introsort.obj heapsort.obj wfmstft.obj assembleWq.obj string1.obj DetectorConfig.obj pulsestats.obj AsyncBuffercgHelper.obj AsyncBuffer.obj threshold.obj waveform.obj datetime.obj FFTImplementationCallback.obj uavrt_detection_rtwutil.obj

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

SYSTEM_LIBS =  /LIBPATH:"$(MATLAB_ROOT)\bin\win64" "$(MATLAB_ROOT)\bin\win64\libiomp5md.lib"

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_ = /source-charset:utf-8
CFLAGS_OPTS = /openmp /wd4101
CFLAGS_BASIC = $(DEFINES) @$(COMPILER_COMMAND_FILE)

CFLAGS = $(CFLAGS) $(CFLAGS_) $(CFLAGS_OPTS) $(CFLAGS_BASIC)

#-----------------
# C++ Compiler
#-----------------

CPPFLAGS_ = /source-charset:utf-8
CPPFLAGS_OPTS = /openmp /wd4101
CPPFLAGS_BASIC = $(DEFINES) @$(COMPILER_COMMAND_FILE)

CPPFLAGS = $(CPPFLAGS) $(CPPFLAGS_) $(CPPFLAGS_OPTS) $(CPPFLAGS_BASIC)

#---------------
# C++ Linker
#---------------

CPP_LDFLAGS_ = /nodefaultlib:vcomp  

CPP_LDFLAGS = $(CPP_LDFLAGS) $(CPP_LDFLAGS_)

#------------------------------
# C++ Shared Library Linker
#------------------------------

CPP_SHAREDLIB_LDFLAGS_ = /nodefaultlib:vcomp  

CPP_SHAREDLIB_LDFLAGS = $(CPP_SHAREDLIB_LDFLAGS) $(CPP_SHAREDLIB_LDFLAGS_)

#-----------
# Linker
#-----------

LDFLAGS_ = /nodefaultlib:vcomp  

LDFLAGS = $(LDFLAGS) $(LDFLAGS_)

#--------------------------
# Shared Library Linker
#--------------------------

SHAREDLIB_LDFLAGS_ = /nodefaultlib:vcomp  

SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS) $(SHAREDLIB_LDFLAGS_)

###########################################################################
## INLINED COMMANDS
###########################################################################


!include $(MATLAB_ROOT)\rtw\c\tools\vcdefs.mak


###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build buildobj clean info prebuild download execute set_environment_variables


all : build
	@cmd /C "@echo ### Successfully generated all binary outputs."


build : set_environment_variables prebuild $(PRODUCT)


buildobj : set_environment_variables prebuild $(OBJS) $(PREBUILT_OBJS)
	@cmd /C "@echo ### Successfully generated all binary outputs."


prebuild : 


download : $(PRODUCT)


execute : download
	@cmd /C "@echo ### Invoking postbuild tool "Execute" ..."
	$(EXECUTE) $(EXECUTE_FLAGS)
	@cmd /C "@echo ### Done invoking postbuild tool."


set_environment_variables : 
	@set INCLUDE=$(INCLUDES);$(INCLUDE)
	@set LIB=$(LIB)


###########################################################################
## FINAL TARGET
###########################################################################

#-------------------------------------------
# Create a standalone executable            
#-------------------------------------------

$(PRODUCT) : $(OBJS) $(PREBUILT_OBJS)
	@cmd /C "@echo ### Creating standalone executable "$(PRODUCT)" ..."
	$(CPP_LD) $(CPP_LDFLAGS) -out:$(PRODUCT) @$(CMD_FILE) $(SYSTEM_LIBS) $(TOOLCHAIN_LIBS)
	@cmd /C "@echo ### Created: $(PRODUCT)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

.c.obj :
	$(CC) $(CFLAGS) -Fo"$@" "$<"


.cpp.obj :
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


{$(RELATIVE_PATH_TO_ANCHOR)}.c.obj :
	$(CC) $(CFLAGS) -Fo"$@" "$<"


{$(RELATIVE_PATH_TO_ANCHOR)}.cpp.obj :
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


{$(START_DIR)\codegen\exe\uavrt_detection}.c.obj :
	$(CC) $(CFLAGS) -Fo"$@" "$<"


{$(START_DIR)\codegen\exe\uavrt_detection}.cpp.obj :
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


{$(START_DIR)}.c.obj :
	$(CC) $(CFLAGS) -Fo"$@" "$<"


{$(START_DIR)}.cpp.obj :
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


coder_posix_time.obj : "$(START_DIR)\codegen\exe\uavrt_detection\coder_posix_time.c"
	$(CC) $(CFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\coder_posix_time.c"


uavrt_detection_data.obj : "$(START_DIR)\codegen\exe\uavrt_detection\uavrt_detection_data.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\uavrt_detection_data.cpp"


rt_nonfinite.obj : "$(START_DIR)\codegen\exe\uavrt_detection\rt_nonfinite.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\rt_nonfinite.cpp"


rtGetNaN.obj : "$(START_DIR)\codegen\exe\uavrt_detection\rtGetNaN.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\rtGetNaN.cpp"


rtGetInf.obj : "$(START_DIR)\codegen\exe\uavrt_detection\rtGetInf.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\rtGetInf.cpp"


uavrt_detection_initialize.obj : "$(START_DIR)\codegen\exe\uavrt_detection\uavrt_detection_initialize.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\uavrt_detection_initialize.cpp"


uavrt_detection_terminate.obj : "$(START_DIR)\codegen\exe\uavrt_detection\uavrt_detection_terminate.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\uavrt_detection_terminate.cpp"


uavrt_detection.obj : "$(START_DIR)\codegen\exe\uavrt_detection\uavrt_detection.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\uavrt_detection.cpp"


fileManager.obj : "$(START_DIR)\codegen\exe\uavrt_detection\fileManager.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\fileManager.cpp"


fgetl.obj : "$(START_DIR)\codegen\exe\uavrt_detection\fgetl.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\fgetl.cpp"


eml_int_forloop_overflow_check.obj : "$(START_DIR)\codegen\exe\uavrt_detection\eml_int_forloop_overflow_check.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\eml_int_forloop_overflow_check.cpp"


ftell.obj : "$(START_DIR)\codegen\exe\uavrt_detection\ftell.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\ftell.cpp"


fseek.obj : "$(START_DIR)\codegen\exe\uavrt_detection\fseek.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\fseek.cpp"


find.obj : "$(START_DIR)\codegen\exe\uavrt_detection\find.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\find.cpp"


str2double.obj : "$(START_DIR)\codegen\exe\uavrt_detection\str2double.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\str2double.cpp"


str2matrix.obj : "$(START_DIR)\codegen\exe\uavrt_detection\str2matrix.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\str2matrix.cpp"


validator_check_size.obj : "$(START_DIR)\codegen\exe\uavrt_detection\validator_check_size.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\validator_check_size.cpp"


int2str.obj : "$(START_DIR)\codegen\exe\uavrt_detection\int2str.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\int2str.cpp"


strtok.obj : "$(START_DIR)\codegen\exe\uavrt_detection\strtok.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\strtok.cpp"


makepulsestruc.obj : "$(START_DIR)\codegen\exe\uavrt_detection\makepulsestruc.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\makepulsestruc.cpp"


validate_print_arguments.obj : "$(START_DIR)\codegen\exe\uavrt_detection\validate_print_arguments.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\validate_print_arguments.cpp"


colon.obj : "$(START_DIR)\codegen\exe\uavrt_detection\colon.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\colon.cpp"


wgn.obj : "$(START_DIR)\codegen\exe\uavrt_detection\wgn.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\wgn.cpp"


randn.obj : "$(START_DIR)\codegen\exe\uavrt_detection\randn.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\randn.cpp"


stft.obj : "$(START_DIR)\codegen\exe\uavrt_detection\stft.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\stft.cpp"


validateattributes.obj : "$(START_DIR)\codegen\exe\uavrt_detection\validateattributes.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\validateattributes.cpp"


iseven.obj : "$(START_DIR)\codegen\exe\uavrt_detection\iseven.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\iseven.cpp"


computeDFT.obj : "$(START_DIR)\codegen\exe\uavrt_detection\computeDFT.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\computeDFT.cpp"


indexShapeCheck.obj : "$(START_DIR)\codegen\exe\uavrt_detection\indexShapeCheck.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\indexShapeCheck.cpp"


movSumProdOrMean.obj : "$(START_DIR)\codegen\exe\uavrt_detection\movSumProdOrMean.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\movSumProdOrMean.cpp"


median.obj : "$(START_DIR)\codegen\exe\uavrt_detection\median.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\median.cpp"


quickselect.obj : "$(START_DIR)\codegen\exe\uavrt_detection\quickselect.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\quickselect.cpp"


repmat.obj : "$(START_DIR)\codegen\exe\uavrt_detection\repmat.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\repmat.cpp"


getLocalTime.obj : "$(START_DIR)\codegen\exe\uavrt_detection\getLocalTime.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\getLocalTime.cpp"


plus.obj : "$(START_DIR)\codegen\exe\uavrt_detection\plus.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\plus.cpp"


tic.obj : "$(START_DIR)\codegen\exe\uavrt_detection\tic.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\tic.cpp"


timeKeeper.obj : "$(START_DIR)\codegen\exe\uavrt_detection\timeKeeper.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\timeKeeper.cpp"


singlecomplex2int.obj : "$(START_DIR)\codegen\exe\uavrt_detection\singlecomplex2int.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\singlecomplex2int.cpp"


fwrite.obj : "$(START_DIR)\codegen\exe\uavrt_detection\fwrite.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\fwrite.cpp"


toc.obj : "$(START_DIR)\codegen\exe\uavrt_detection\toc.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\toc.cpp"


diff.obj : "$(START_DIR)\codegen\exe\uavrt_detection\diff.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\diff.cpp"


sum.obj : "$(START_DIR)\codegen\exe\uavrt_detection\sum.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\sum.cpp"


sparse.obj : "$(START_DIR)\codegen\exe\uavrt_detection\sparse.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\sparse.cpp"


fzero.obj : "$(START_DIR)\codegen\exe\uavrt_detection\fzero.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\fzero.cpp"


horzcatStructList.obj : "$(START_DIR)\codegen\exe\uavrt_detection\horzcatStructList.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\horzcatStructList.cpp"


waveformcopy.obj : "$(START_DIR)\codegen\exe\uavrt_detection\waveformcopy.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\waveformcopy.cpp"


eml_randn.obj : "$(START_DIR)\codegen\exe\uavrt_detection\eml_randn.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\eml_randn.cpp"


eml_rand.obj : "$(START_DIR)\codegen\exe\uavrt_detection\eml_rand.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\eml_rand.cpp"


eml_rand_mt19937ar_stateful.obj : "$(START_DIR)\codegen\exe\uavrt_detection\eml_rand_mt19937ar_stateful.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\eml_rand_mt19937ar_stateful.cpp"


CoderTimeAPI.obj : "$(START_DIR)\codegen\exe\uavrt_detection\CoderTimeAPI.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\CoderTimeAPI.cpp"


udpSamplesReceiverRead.obj : "$(START_DIR)\codegen\exe\uavrt_detection\udpSamplesReceiverRead.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\udpSamplesReceiverRead.cpp"


strcmp.obj : "$(START_DIR)\codegen\exe\uavrt_detection\strcmp.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\strcmp.cpp"


str2double1.obj : "$(START_DIR)\codegen\exe\uavrt_detection\str2double1.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\str2double1.cpp"


nullAssignment.obj : "$(START_DIR)\codegen\exe\uavrt_detection\nullAssignment.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\nullAssignment.cpp"


sort.obj : "$(START_DIR)\codegen\exe\uavrt_detection\sort.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\sort.cpp"


sortIdx.obj : "$(START_DIR)\codegen\exe\uavrt_detection\sortIdx.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\sortIdx.cpp"


eml_rand_mt19937ar.obj : "$(START_DIR)\codegen\exe\uavrt_detection\eml_rand_mt19937ar.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\eml_rand_mt19937ar.cpp"


unique.obj : "$(START_DIR)\codegen\exe\uavrt_detection\unique.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\unique.cpp"


insertionsort.obj : "$(START_DIR)\codegen\exe\uavrt_detection\insertionsort.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\insertionsort.cpp"


introsort.obj : "$(START_DIR)\codegen\exe\uavrt_detection\introsort.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\introsort.cpp"


heapsort.obj : "$(START_DIR)\codegen\exe\uavrt_detection\heapsort.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\heapsort.cpp"


wfmstft.obj : "$(START_DIR)\codegen\exe\uavrt_detection\wfmstft.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\wfmstft.cpp"


assembleWq.obj : "$(START_DIR)\codegen\exe\uavrt_detection\assembleWq.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\assembleWq.cpp"


string1.obj : "$(START_DIR)\codegen\exe\uavrt_detection\string1.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\string1.cpp"


DetectorConfig.obj : "$(START_DIR)\codegen\exe\uavrt_detection\DetectorConfig.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\DetectorConfig.cpp"


pulsestats.obj : "$(START_DIR)\codegen\exe\uavrt_detection\pulsestats.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\pulsestats.cpp"


AsyncBuffercgHelper.obj : "$(START_DIR)\codegen\exe\uavrt_detection\AsyncBuffercgHelper.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\AsyncBuffercgHelper.cpp"


AsyncBuffer.obj : "$(START_DIR)\codegen\exe\uavrt_detection\AsyncBuffer.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\AsyncBuffer.cpp"


threshold.obj : "$(START_DIR)\codegen\exe\uavrt_detection\threshold.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\threshold.cpp"


waveform.obj : "$(START_DIR)\codegen\exe\uavrt_detection\waveform.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\waveform.cpp"


datetime.obj : "$(START_DIR)\codegen\exe\uavrt_detection\datetime.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\datetime.cpp"


FFTImplementationCallback.obj : "$(START_DIR)\codegen\exe\uavrt_detection\FFTImplementationCallback.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\FFTImplementationCallback.cpp"


uavrt_detection_rtwutil.obj : "$(START_DIR)\codegen\exe\uavrt_detection\uavrt_detection_rtwutil.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\uavrt_detection\uavrt_detection_rtwutil.cpp"


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : rtw_proj.tmw $(COMPILER_COMMAND_FILE) $(MAKEFILE)


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	@cmd /C "@echo ### PRODUCT = $(PRODUCT)"
	@cmd /C "@echo ### PRODUCT_TYPE = $(PRODUCT_TYPE)"
	@cmd /C "@echo ### BUILD_TYPE = $(BUILD_TYPE)"
	@cmd /C "@echo ### INCLUDES = $(INCLUDES)"
	@cmd /C "@echo ### DEFINES = $(DEFINES)"
	@cmd /C "@echo ### ALL_SRCS = $(ALL_SRCS)"
	@cmd /C "@echo ### ALL_OBJS = $(ALL_OBJS)"
	@cmd /C "@echo ### LIBS = $(LIBS)"
	@cmd /C "@echo ### MODELREF_LIBS = $(MODELREF_LIBS)"
	@cmd /C "@echo ### SYSTEM_LIBS = $(SYSTEM_LIBS)"
	@cmd /C "@echo ### TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS)"
	@cmd /C "@echo ### CFLAGS = $(CFLAGS)"
	@cmd /C "@echo ### LDFLAGS = $(LDFLAGS)"
	@cmd /C "@echo ### SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	@cmd /C "@echo ### CPPFLAGS = $(CPPFLAGS)"
	@cmd /C "@echo ### CPP_LDFLAGS = $(CPP_LDFLAGS)"
	@cmd /C "@echo ### CPP_SHAREDLIB_LDFLAGS = $(CPP_SHAREDLIB_LDFLAGS)"
	@cmd /C "@echo ### ARFLAGS = $(ARFLAGS)"
	@cmd /C "@echo ### MEX_CFLAGS = $(MEX_CFLAGS)"
	@cmd /C "@echo ### MEX_CPPFLAGS = $(MEX_CPPFLAGS)"
	@cmd /C "@echo ### MEX_LDFLAGS = $(MEX_LDFLAGS)"
	@cmd /C "@echo ### MEX_CPPLDFLAGS = $(MEX_CPPLDFLAGS)"
	@cmd /C "@echo ### DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS)"
	@cmd /C "@echo ### EXECUTE_FLAGS = $(EXECUTE_FLAGS)"
	@cmd /C "@echo ### MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "### Deleting all derived files..."
	@if exist $(PRODUCT) $(RM) $(PRODUCT)
	$(RM) $(ALL_OBJS)
	$(ECHO) "### Deleted all derived files."


