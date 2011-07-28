# add custom variables to this file

# OF_ROOT allows to move projects outside apps/* just set this variable to the
# absoulte path to the OF root folder

OF_ROOT = ../../..


# USER_CFLAGS allows to pass custom flags to the compiler
# for example search paths like:
# USER_CFLAGS = -I src/objects

USER_CFLAGS = -I /usr/include/ni -I /usr/include/nite -l GL -l OpenNI


# USER_LDFLAGS allows to pass custom flags to the linker
# for example libraries like:
# USER_LD_FLAGS = libs/libawesomelib.a

USER_LD_FLAGS = /usr/lib/ /usr/lib/libnimCodecs.so /usr/lib/libnimMockNodes.so /usr/lib/libnimRecorder.so /usr/lib/libXnCore.so /usr/lib/libXnDDK.so /usr/lib/libXnDeviceFile.so /usr/lib/libXnDeviceSensorV2.so /usr/lib/libXnFormats.so /usr/lib/libXnVCNITE_1_3_1.so /usr/lib/libXnVFeatures.so /usr/lib/libXnVFeatures_1_3_1.so /usr/lib/libXnVHandGenerator.so /usr/lib/libXnVHandGenerator_1_3_1.so /usr/lib/libXnVNite.so /usr/lib/libXnVNite_1_3_1.so /usr/lib/libOpenNI.so 

# use this to add system libraries for example:
# USER_LIBS = -lpango
 
USER_LIBS = -lOpenNI

# change this to add different compiler optimizations to your project

USER_COMPILER_OPTIMIZATION = -march=native -mtune=native -Os


EXCLUDE_FROM_SOURCE="bin,.xcodeproj,obj"
