# Microsoft Developer Studio Generated NMAKE File, Based on 2dlib.dsp
!IF "$(CFG)" == ""
CFG=2dlib - Win32 GameGauge Release
!MESSAGE No configuration specified. Defaulting to 2dlib - Win32 GameGauge Release.
!ENDIF 

!IF "$(CFG)" != "2dlib - Win32 Debug" && "$(CFG)" != "2dlib - Win32 OEM Debug" && "$(CFG)" != "2dlib - Win32 Release" && "$(CFG)" != "2dlib - Win32 BETA Release" && "$(CFG)" != "2dlib - Win32 OEM Release" && "$(CFG)" != "2dlib - Win32 Katmai Release" && "$(CFG)" != "2dlib - Win32 Demo Debug" && "$(CFG)" != "2dlib - Win32 Demo Release" && "$(CFG)" != "2dlib - Win32 GameGauge Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "2dlib.mak" CFG="2dlib - Win32 GameGauge Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "2dlib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "2dlib - Win32 OEM Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "2dlib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "2dlib - Win32 BETA Release" (based on "Win32 (x86) Static Library")
!MESSAGE "2dlib - Win32 OEM Release" (based on "Win32 (x86) Static Library")
!MESSAGE "2dlib - Win32 Katmai Release" (based on "Win32 (x86) Static Library")
!MESSAGE "2dlib - Win32 Demo Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "2dlib - Win32 Demo Release" (based on "Win32 (x86) Static Library")
!MESSAGE "2dlib - Win32 GameGauge Release" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "2dlib - Win32 Debug"

OUTDIR=.\./Debug
INTDIR=.\./Debug
# Begin Custom Macros
OutDir=.\./Debug
# End Custom Macros

ALL : "$(OUTDIR)\2dlib.lib"


CLEAN :
	-@erase "$(INTDIR)\font.obj"
	-@erase "$(INTDIR)\hardsurf.obj"
	-@erase "$(INTDIR)\memsurf.obj"
	-@erase "$(INTDIR)\pen.obj"
	-@erase "$(INTDIR)\pentext.obj"
	-@erase "$(INTDIR)\screen.obj"
	-@erase "$(INTDIR)\surface.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\viewport.obj"
	-@erase "$(OUTDIR)\2dlib.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=xicl6.exe
CPP_PROJ=/nologo /G5 /MDd /W3 /GX /ZI /Od /I "..\lib" /I "..\lib\win" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "MONO" /Fp"$(INTDIR)\2dlib.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\2dlib.bsc" 
BSC32_SBRS= \
	
LIB32=xilink6.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\2dlib.lib" 
LIB32_OBJS= \
	"$(INTDIR)\font.obj" \
	"$(INTDIR)\hardsurf.obj" \
	"$(INTDIR)\memsurf.obj" \
	"$(INTDIR)\pen.obj" \
	"$(INTDIR)\pentext.obj" \
	"$(INTDIR)\screen.obj" \
	"$(INTDIR)\surface.obj" \
	"$(INTDIR)\viewport.obj"

"$(OUTDIR)\2dlib.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "2dlib - Win32 OEM Debug"

OUTDIR=.\./OEM_Debug
INTDIR=.\./OEM_Debug
# Begin Custom Macros
OutDir=.\./OEM_Debug
# End Custom Macros

ALL : "$(OUTDIR)\2dlib.lib"


CLEAN :
	-@erase "$(INTDIR)\font.obj"
	-@erase "$(INTDIR)\hardsurf.obj"
	-@erase "$(INTDIR)\memsurf.obj"
	-@erase "$(INTDIR)\pen.obj"
	-@erase "$(INTDIR)\pentext.obj"
	-@erase "$(INTDIR)\screen.obj"
	-@erase "$(INTDIR)\surface.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\viewport.obj"
	-@erase "$(OUTDIR)\2dlib.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=xicl6.exe
CPP_PROJ=/nologo /G5 /MDd /W3 /GX /ZI /Od /I "..\lib" /I "..\lib\win" /D "_WINDOWS" /D "MONO" /D "WIN32" /D "_DEBUG" /D "OEM" /Fp"$(INTDIR)\2dlib.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\2dlib.bsc" 
BSC32_SBRS= \
	
LIB32=xilink6.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\2dlib.lib" 
LIB32_OBJS= \
	"$(INTDIR)\font.obj" \
	"$(INTDIR)\hardsurf.obj" \
	"$(INTDIR)\memsurf.obj" \
	"$(INTDIR)\pen.obj" \
	"$(INTDIR)\pentext.obj" \
	"$(INTDIR)\screen.obj" \
	"$(INTDIR)\surface.obj" \
	"$(INTDIR)\viewport.obj"

"$(OUTDIR)\2dlib.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "2dlib - Win32 Release"

OUTDIR=.\./Release
INTDIR=.\./Release
# Begin Custom Macros
OutDir=.\./Release
# End Custom Macros

ALL : "$(OUTDIR)\2dlib.lib"


CLEAN :
	-@erase "$(INTDIR)\font.obj"
	-@erase "$(INTDIR)\hardsurf.obj"
	-@erase "$(INTDIR)\memsurf.obj"
	-@erase "$(INTDIR)\pen.obj"
	-@erase "$(INTDIR)\pentext.obj"
	-@erase "$(INTDIR)\screen.obj"
	-@erase "$(INTDIR)\surface.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\viewport.obj"
	-@erase "$(OUTDIR)\2dlib.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=xicl6.exe
CPP_PROJ=/nologo /G5 /MT /W3 /GX /Od /I "..\lib" /I "..\lib\win" /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /D "RELEASE" /Fp"$(INTDIR)\2dlib.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\2dlib.bsc" 
BSC32_SBRS= \
	
LIB32=xilink6.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\2dlib.lib" 
LIB32_OBJS= \
	"$(INTDIR)\font.obj" \
	"$(INTDIR)\hardsurf.obj" \
	"$(INTDIR)\memsurf.obj" \
	"$(INTDIR)\pen.obj" \
	"$(INTDIR)\pentext.obj" \
	"$(INTDIR)\screen.obj" \
	"$(INTDIR)\surface.obj" \
	"$(INTDIR)\viewport.obj"

"$(OUTDIR)\2dlib.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "2dlib - Win32 BETA Release"

OUTDIR=.\./BETA_Release
INTDIR=.\./BETA_Release
# Begin Custom Macros
OutDir=.\./BETA_Release
# End Custom Macros

ALL : "$(OUTDIR)\2dlib.lib"


CLEAN :
	-@erase "$(INTDIR)\font.obj"
	-@erase "$(INTDIR)\hardsurf.obj"
	-@erase "$(INTDIR)\memsurf.obj"
	-@erase "$(INTDIR)\pen.obj"
	-@erase "$(INTDIR)\pentext.obj"
	-@erase "$(INTDIR)\screen.obj"
	-@erase "$(INTDIR)\surface.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\viewport.obj"
	-@erase "$(OUTDIR)\2dlib.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=xicl6.exe
CPP_PROJ=/nologo /G5 /MDd /W3 /GX /ZI /Od /I "..\lib" /I "..\lib\win" /D "_DEBUG" /D "_WINDOWS" /D "WIN32" /D "BETA" /Fp"$(INTDIR)\2dlib.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\2dlib.bsc" 
BSC32_SBRS= \
	
LIB32=xilink6.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\2dlib.lib" 
LIB32_OBJS= \
	"$(INTDIR)\font.obj" \
	"$(INTDIR)\hardsurf.obj" \
	"$(INTDIR)\memsurf.obj" \
	"$(INTDIR)\pen.obj" \
	"$(INTDIR)\pentext.obj" \
	"$(INTDIR)\screen.obj" \
	"$(INTDIR)\surface.obj" \
	"$(INTDIR)\viewport.obj"

"$(OUTDIR)\2dlib.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "2dlib - Win32 OEM Release"

OUTDIR=.\./OEM_Release
INTDIR=.\./OEM_Release
# Begin Custom Macros
OutDir=.\./OEM_Release
# End Custom Macros

ALL : "$(OUTDIR)\2dlib.lib"


CLEAN :
	-@erase "$(INTDIR)\font.obj"
	-@erase "$(INTDIR)\hardsurf.obj"
	-@erase "$(INTDIR)\memsurf.obj"
	-@erase "$(INTDIR)\pen.obj"
	-@erase "$(INTDIR)\pentext.obj"
	-@erase "$(INTDIR)\screen.obj"
	-@erase "$(INTDIR)\surface.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\viewport.obj"
	-@erase "$(OUTDIR)\2dlib.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=xicl6.exe
CPP_PROJ=/nologo /G5 /MDd /W3 /GX /Od /I "..\lib" /I "..\lib\win" /D "_DEBUG" /D "_WINDOWS" /D "OEM" /D "WIN32" /D "RELEASE" /Fp"$(INTDIR)\2dlib.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\2dlib.bsc" 
BSC32_SBRS= \
	
LIB32=xilink6.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\2dlib.lib" 
LIB32_OBJS= \
	"$(INTDIR)\font.obj" \
	"$(INTDIR)\hardsurf.obj" \
	"$(INTDIR)\memsurf.obj" \
	"$(INTDIR)\pen.obj" \
	"$(INTDIR)\pentext.obj" \
	"$(INTDIR)\screen.obj" \
	"$(INTDIR)\surface.obj" \
	"$(INTDIR)\viewport.obj"

"$(OUTDIR)\2dlib.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "2dlib - Win32 Katmai Release"

OUTDIR=.\./Katmai_Release
INTDIR=.\./Katmai_Release
# Begin Custom Macros
OutDir=.\./Katmai_Release
# End Custom Macros

ALL : "$(OUTDIR)\2dlib.lib"


CLEAN :
	-@erase "$(INTDIR)\font.obj"
	-@erase "$(INTDIR)\hardsurf.obj"
	-@erase "$(INTDIR)\memsurf.obj"
	-@erase "$(INTDIR)\pen.obj"
	-@erase "$(INTDIR)\pentext.obj"
	-@erase "$(INTDIR)\screen.obj"
	-@erase "$(INTDIR)\surface.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\viewport.obj"
	-@erase "$(OUTDIR)\2dlib.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=xicl6.exe
CPP_PROJ=/nologo /G5 /MDd /W3 /GX /Od /I "..\lib" /I "..\lib\win" /D "_DEBUG" /D "_WINDOWS" /D "KATMAI" /D "WIN32" /D "RELEASE" /Fp"$(INTDIR)\2dlib.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\2dlib.bsc" 
BSC32_SBRS= \
	
LIB32=xilink6.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\2dlib.lib" 
LIB32_OBJS= \
	"$(INTDIR)\font.obj" \
	"$(INTDIR)\hardsurf.obj" \
	"$(INTDIR)\memsurf.obj" \
	"$(INTDIR)\pen.obj" \
	"$(INTDIR)\pentext.obj" \
	"$(INTDIR)\screen.obj" \
	"$(INTDIR)\surface.obj" \
	"$(INTDIR)\viewport.obj"

"$(OUTDIR)\2dlib.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "2dlib - Win32 Demo Debug"

OUTDIR=.\./Demo_Debug
INTDIR=.\./Demo_Debug
# Begin Custom Macros
OutDir=.\./Demo_Debug
# End Custom Macros

ALL : "$(OUTDIR)\2dlib.lib"


CLEAN :
	-@erase "$(INTDIR)\font.obj"
	-@erase "$(INTDIR)\hardsurf.obj"
	-@erase "$(INTDIR)\memsurf.obj"
	-@erase "$(INTDIR)\pen.obj"
	-@erase "$(INTDIR)\pentext.obj"
	-@erase "$(INTDIR)\screen.obj"
	-@erase "$(INTDIR)\surface.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\viewport.obj"
	-@erase "$(OUTDIR)\2dlib.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=xicl6.exe
CPP_PROJ=/nologo /G5 /MD /W3 /GX /ZI /Od /I "..\lib" /I "..\lib\win" /D "DEMO" /D "_WINDOWS" /D "MONO" /D "WIN32" /D "_DEBUG" /Fp"$(INTDIR)\2dlib.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\2dlib.bsc" 
BSC32_SBRS= \
	
LIB32=xilink6.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\2dlib.lib" 
LIB32_OBJS= \
	"$(INTDIR)\font.obj" \
	"$(INTDIR)\hardsurf.obj" \
	"$(INTDIR)\memsurf.obj" \
	"$(INTDIR)\pen.obj" \
	"$(INTDIR)\pentext.obj" \
	"$(INTDIR)\screen.obj" \
	"$(INTDIR)\surface.obj" \
	"$(INTDIR)\viewport.obj"

"$(OUTDIR)\2dlib.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "2dlib - Win32 Demo Release"

OUTDIR=.\./Demo_Release
INTDIR=.\./Demo_Release
# Begin Custom Macros
OutDir=.\./Demo_Release
# End Custom Macros

ALL : "$(OUTDIR)\2dlib.lib"


CLEAN :
	-@erase "$(INTDIR)\font.obj"
	-@erase "$(INTDIR)\hardsurf.obj"
	-@erase "$(INTDIR)\memsurf.obj"
	-@erase "$(INTDIR)\pen.obj"
	-@erase "$(INTDIR)\pentext.obj"
	-@erase "$(INTDIR)\screen.obj"
	-@erase "$(INTDIR)\surface.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\viewport.obj"
	-@erase "$(OUTDIR)\2dlib.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=xicl6.exe
CPP_PROJ=/nologo /G5 /MT /W3 /GX /Od /I "..\lib" /I "..\lib\win" /D "DEMO" /D "_WINDOWS" /D "MONO" /D "WIN32" /D "RELEASE" /Fp"$(INTDIR)\2dlib.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\2dlib.bsc" 
BSC32_SBRS= \
	
LIB32=xilink6.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\2dlib.lib" 
LIB32_OBJS= \
	"$(INTDIR)\font.obj" \
	"$(INTDIR)\hardsurf.obj" \
	"$(INTDIR)\memsurf.obj" \
	"$(INTDIR)\pen.obj" \
	"$(INTDIR)\pentext.obj" \
	"$(INTDIR)\screen.obj" \
	"$(INTDIR)\surface.obj" \
	"$(INTDIR)\viewport.obj"

"$(OUTDIR)\2dlib.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "2dlib - Win32 GameGauge Release"

OUTDIR=.\./GameGauge_Release
INTDIR=.\./GameGauge_Release
# Begin Custom Macros
OutDir=.\./GameGauge_Release
# End Custom Macros

ALL : "$(OUTDIR)\2dlib.lib"


CLEAN :
	-@erase "$(INTDIR)\font.obj"
	-@erase "$(INTDIR)\hardsurf.obj"
	-@erase "$(INTDIR)\memsurf.obj"
	-@erase "$(INTDIR)\pen.obj"
	-@erase "$(INTDIR)\pentext.obj"
	-@erase "$(INTDIR)\screen.obj"
	-@erase "$(INTDIR)\surface.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\viewport.obj"
	-@erase "$(OUTDIR)\2dlib.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=xicl6.exe
CPP_PROJ=/nologo /G5 /MDd /W3 /GX /Od /I "..\lib" /I "..\lib\win" /D "_DEBUG" /D "_WINDOWS" /D "WIN32" /D "GAMEGAUGE" /D "RELEASE" /Fp"$(INTDIR)\2dlib.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\2dlib.bsc" 
BSC32_SBRS= \
	
LIB32=xilink6.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\2dlib.lib" 
LIB32_OBJS= \
	"$(INTDIR)\font.obj" \
	"$(INTDIR)\hardsurf.obj" \
	"$(INTDIR)\memsurf.obj" \
	"$(INTDIR)\pen.obj" \
	"$(INTDIR)\pentext.obj" \
	"$(INTDIR)\screen.obj" \
	"$(INTDIR)\surface.obj" \
	"$(INTDIR)\viewport.obj"

"$(OUTDIR)\2dlib.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("2dlib.dep")
!INCLUDE "2dlib.dep"
!ELSE 
!MESSAGE Warning: cannot find "2dlib.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "2dlib - Win32 Debug" || "$(CFG)" == "2dlib - Win32 OEM Debug" || "$(CFG)" == "2dlib - Win32 Release" || "$(CFG)" == "2dlib - Win32 BETA Release" || "$(CFG)" == "2dlib - Win32 OEM Release" || "$(CFG)" == "2dlib - Win32 Katmai Release" || "$(CFG)" == "2dlib - Win32 Demo Debug" || "$(CFG)" == "2dlib - Win32 Demo Release" || "$(CFG)" == "2dlib - Win32 GameGauge Release"
SOURCE=.\font.cpp

"$(INTDIR)\font.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\hardsurf.cpp

"$(INTDIR)\hardsurf.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\memsurf.cpp

"$(INTDIR)\memsurf.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\pen.cpp

"$(INTDIR)\pen.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\pentext.cpp

"$(INTDIR)\pentext.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\screen.cpp

"$(INTDIR)\screen.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\surface.cpp

"$(INTDIR)\surface.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\viewport.cpp

"$(INTDIR)\viewport.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

