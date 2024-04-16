# Microsoft Developer Studio Generated NMAKE File, Based on fix.dsp
!IF "$(CFG)" == ""
CFG=fix - Win32 GameGauge Release
!MESSAGE No configuration specified. Defaulting to fix - Win32 GameGauge Release.
!ENDIF 

!IF "$(CFG)" != "fix - Win32 Debug" && "$(CFG)" != "fix - Win32 OEM Debug" && "$(CFG)" != "fix - Win32 Release" && "$(CFG)" != "fix - Win32 BETA Release" && "$(CFG)" != "fix - Win32 OEM Release" && "$(CFG)" != "fix - Win32 Katmai Release" && "$(CFG)" != "fix - Win32 Demo Debug" && "$(CFG)" != "fix - Win32 Demo Release" && "$(CFG)" != "fix - Win32 GameGauge Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "fix.mak" CFG="fix - Win32 GameGauge Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "fix - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "fix - Win32 OEM Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "fix - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "fix - Win32 BETA Release" (based on "Win32 (x86) Static Library")
!MESSAGE "fix - Win32 OEM Release" (based on "Win32 (x86) Static Library")
!MESSAGE "fix - Win32 Katmai Release" (based on "Win32 (x86) Static Library")
!MESSAGE "fix - Win32 Demo Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "fix - Win32 Demo Release" (based on "Win32 (x86) Static Library")
!MESSAGE "fix - Win32 GameGauge Release" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "fix - Win32 Debug"

OUTDIR=.\./Debug
INTDIR=.\./Debug
# Begin Custom Macros
OutDir=.\./Debug
# End Custom Macros

ALL : "$(OUTDIR)\fix.lib"


CLEAN :
	-@erase "$(INTDIR)\fix.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\fix.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=xicl6.exe
CPP_PROJ=/nologo /G5 /MDd /W3 /GX /ZI /Od /I "..\lib" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "MONO" /Fp"$(INTDIR)\fix.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\fix.bsc" 
BSC32_SBRS= \
	
LIB32=xilink6.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\fix.lib" 
LIB32_OBJS= \
	"$(INTDIR)\fix.obj"

"$(OUTDIR)\fix.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "fix - Win32 OEM Debug"

OUTDIR=.\./OEM_Debug
INTDIR=.\./OEM_Debug
# Begin Custom Macros
OutDir=.\./OEM_Debug
# End Custom Macros

ALL : "$(OUTDIR)\fix.lib"


CLEAN :
	-@erase "$(INTDIR)\fix.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\fix.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=xicl6.exe
CPP_PROJ=/nologo /G5 /MDd /W3 /GX /ZI /Od /I "..\lib" /D "_WINDOWS" /D "MONO" /D "WIN32" /D "_DEBUG" /D "OEM" /Fp"$(INTDIR)\fix.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\fix.bsc" 
BSC32_SBRS= \
	
LIB32=xilink6.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\fix.lib" 
LIB32_OBJS= \
	"$(INTDIR)\fix.obj"

"$(OUTDIR)\fix.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "fix - Win32 Release"

OUTDIR=.\./Release
INTDIR=.\./Release
# Begin Custom Macros
OutDir=.\./Release
# End Custom Macros

ALL : "$(OUTDIR)\fix.lib"


CLEAN :
	-@erase "$(INTDIR)\fix.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\fix.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=xicl6.exe
CPP_PROJ=/nologo /G5 /MT /W3 /GX /O2 /I "..\lib" /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /D "RELEASE" /Fp"$(INTDIR)\fix.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\fix.bsc" 
BSC32_SBRS= \
	
LIB32=xilink6.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\fix.lib" 
LIB32_OBJS= \
	"$(INTDIR)\fix.obj"

"$(OUTDIR)\fix.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "fix - Win32 BETA Release"

OUTDIR=.\./BETA_Release
INTDIR=.\./BETA_Release
# Begin Custom Macros
OutDir=.\./BETA_Release
# End Custom Macros

ALL : "$(OUTDIR)\fix.lib"


CLEAN :
	-@erase "$(INTDIR)\fix.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\fix.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=xicl6.exe
CPP_PROJ=/nologo /G5 /MT /W3 /GX /O2 /I "..\lib" /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /D "BETA" /Fp"$(INTDIR)\fix.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\fix.bsc" 
BSC32_SBRS= \
	
LIB32=xilink6.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\fix.lib" 
LIB32_OBJS= \
	"$(INTDIR)\fix.obj"

"$(OUTDIR)\fix.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "fix - Win32 OEM Release"

OUTDIR=.\./OEM_Release
INTDIR=.\./OEM_Release
# Begin Custom Macros
OutDir=.\./OEM_Release
# End Custom Macros

ALL : "$(OUTDIR)\fix.lib"


CLEAN :
	-@erase "$(INTDIR)\fix.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\fix.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=xicl6.exe
CPP_PROJ=/nologo /G5 /MT /W3 /GX /O2 /I "..\lib" /D "NDEBUG" /D "_WINDOWS" /D "OEM" /D "WIN32" /D "RELEASE" /Fp"$(INTDIR)\fix.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\fix.bsc" 
BSC32_SBRS= \
	
LIB32=xilink6.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\fix.lib" 
LIB32_OBJS= \
	"$(INTDIR)\fix.obj"

"$(OUTDIR)\fix.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "fix - Win32 Katmai Release"

OUTDIR=.\./Katmai_Release
INTDIR=.\./Katmai_Release
# Begin Custom Macros
OutDir=.\./Katmai_Release
# End Custom Macros

ALL : "$(OUTDIR)\fix.lib"


CLEAN :
	-@erase "$(INTDIR)\fix.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\fix.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=xicl6.exe
CPP_PROJ=/nologo /G5 /MT /W3 /GX /O2 /I "..\lib" /D "NDEBUG" /D "_WINDOWS" /D "KATMAI" /D "WIN32" /D "RELEASE" /Fp"$(INTDIR)\fix.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\fix.bsc" 
BSC32_SBRS= \
	
LIB32=xilink6.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\fix.lib" 
LIB32_OBJS= \
	"$(INTDIR)\fix.obj"

"$(OUTDIR)\fix.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "fix - Win32 Demo Debug"

OUTDIR=.\./Demo_Debug
INTDIR=.\./Demo_Debug
# Begin Custom Macros
OutDir=.\./Demo_Debug
# End Custom Macros

ALL : "$(OUTDIR)\fix.lib"


CLEAN :
	-@erase "$(INTDIR)\fix.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\fix.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=xicl6.exe
CPP_PROJ=/nologo /G5 /MD /W3 /GX /ZI /Od /I "..\lib" /D "DEMO" /D "_WINDOWS" /D "MONO" /D "WIN32" /D "_DEBUG" /Fp"$(INTDIR)\fix.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\fix.bsc" 
BSC32_SBRS= \
	
LIB32=xilink6.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\fix.lib" 
LIB32_OBJS= \
	"$(INTDIR)\fix.obj"

"$(OUTDIR)\fix.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "fix - Win32 Demo Release"

OUTDIR=.\./Demo_Release
INTDIR=.\./Demo_Release
# Begin Custom Macros
OutDir=.\./Demo_Release
# End Custom Macros

ALL : "$(OUTDIR)\fix.lib"


CLEAN :
	-@erase "$(INTDIR)\fix.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\fix.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=xicl6.exe
CPP_PROJ=/nologo /G5 /MT /W3 /GX /O2 /I "..\lib" /D "DEMO" /D "_WINDOWS" /D "MONO" /D "WIN32" /D "RELEASE" /Fp"$(INTDIR)\fix.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\fix.bsc" 
BSC32_SBRS= \
	
LIB32=xilink6.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\fix.lib" 
LIB32_OBJS= \
	"$(INTDIR)\fix.obj"

"$(OUTDIR)\fix.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "fix - Win32 GameGauge Release"

OUTDIR=.\./GameGauge_Release
INTDIR=.\./GameGauge_Release
# Begin Custom Macros
OutDir=.\./GameGauge_Release
# End Custom Macros

ALL : "$(OUTDIR)\fix.lib"


CLEAN :
	-@erase "$(INTDIR)\fix.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\fix.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=xicl6.exe
CPP_PROJ=/nologo /G5 /MT /W3 /GX /O2 /I "..\lib" /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /D "GAMEGAUGE" /D "RELEASE" /Fp"$(INTDIR)\fix.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\fix.bsc" 
BSC32_SBRS= \
	
LIB32=xilink6.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\fix.lib" 
LIB32_OBJS= \
	"$(INTDIR)\fix.obj"

"$(OUTDIR)\fix.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("fix.dep")
!INCLUDE "fix.dep"
!ELSE 
!MESSAGE Warning: cannot find "fix.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "fix - Win32 Debug" || "$(CFG)" == "fix - Win32 OEM Debug" || "$(CFG)" == "fix - Win32 Release" || "$(CFG)" == "fix - Win32 BETA Release" || "$(CFG)" == "fix - Win32 OEM Release" || "$(CFG)" == "fix - Win32 Katmai Release" || "$(CFG)" == "fix - Win32 Demo Debug" || "$(CFG)" == "fix - Win32 Demo Release" || "$(CFG)" == "fix - Win32 GameGauge Release"
SOURCE=.\fix.cpp

"$(INTDIR)\fix.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

