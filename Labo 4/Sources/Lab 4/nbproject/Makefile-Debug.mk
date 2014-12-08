#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=clang
CCC=clang++
CXX=clang++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=CLang-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/2140864206/RoadNetwork.o \
	${OBJECTDIR}/_ext/2140864206/UnionFind.o \
	${OBJECTDIR}/_ext/2140864206/Util.o \
	${OBJECTDIR}/_ext/2140864206/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lab_4

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lab_4: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lab_4 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/2140864206/RoadNetwork.o: ../Lab\ 4/RoadNetwork.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2140864206
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2140864206/RoadNetwork.o ../Lab\ 4/RoadNetwork.cpp

${OBJECTDIR}/_ext/2140864206/UnionFind.o: ../Lab\ 4/UnionFind.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2140864206
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2140864206/UnionFind.o ../Lab\ 4/UnionFind.cpp

${OBJECTDIR}/_ext/2140864206/Util.o: ../Lab\ 4/Util.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2140864206
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2140864206/Util.o ../Lab\ 4/Util.cpp

${OBJECTDIR}/_ext/2140864206/main.o: ../Lab\ 4/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2140864206
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2140864206/main.o ../Lab\ 4/main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lab_4

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
