# Microsoft Developer Studio Generated NMAKE File, Based on ddio_win.dsp
!IF "$(CFG)" == ""
CFG=ddio_win - Win32 GameGauge Release
!MESSAGE No configuration specified. Defaulting to ddio_win - Win32 GameGauge Release.
!ENDIF 

!IF "$(CFG)" != "ddio_win - Win32 Debug" && "$(CFG)" != "ddio_win - Win32 OEM Debug" && "$(CFG)" != "ddio_win - Win32 Release" && "$(CFG)" != "ddio_win - Win32 BETA Release" && "$(CFG)" != "ddio_win - Win32 OEM Release" && "$(CFG)" != "ddio_win - Win32 Katmai Release" && "$(CFG)" != "ddio_win - Win32 Demo Debug" && "$(CFG)" != "ddio_win - Win32 Demo Release" && "$(CFG)" != "ddio_win - Win32 GameGauge Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ddio_win.mak" CFG="ddio_win - Win32 GameGauge Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ddio_win - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "ddio_win - Win32 OEM Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "ddio_win - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ddio_win - Win32 BETA Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ddio_win - Win32 OEM Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ddio_win - Win32 Katmai Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ddio_win - Win32 Demo Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "ddio_win - Win32 Demo Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ddio_win - Win32 GameGauge Release" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "ddio_win - Win32 Debug"

OUTDIR=.\./Debug
INTDIR=.\./Debug
# Begin Custom Macros
OutDir=.\./Debug
# End Custom Macros

ALL : "$(OUTDIR)\ddio_win.lib"


CLEAN :
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\winfile.obj"
	-@erase "$(INTDIR)\winforcefeedback.obj"
	-@erase "$(INTDIR)\winio.obj"
	-@erase "$(INTDIR)\winjoy.obj"
	-@erase "$(INTDIR)\winkey.obj"
	-@erase "$(INTDIR)\winmouse.obj"
	-@erase "$(INTDIR)\wintimer.obj"
	-@erase "$(OUTDIR)\ddio_win.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=xicl6.exe
CPP_PROJ=/nologo /G5 /MDd /W3 /GX /ZI /Od /I "..\lib" /I "..\lib\win" /I "..\lib\win\directx" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "MONO" /D "IMMERSION" /Fp"$(INTDIR)\ddio_win.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ddio_win.bsc" 
BSC32_SBRS= \
	
LIB32=xilink6.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\ddio_win.lib" 
LIB32_OBJS= \
	"$(INTDIR)\winfile.obj" \
	"$(INTDIR)\winforcefeedback.obj" \
	"$(INTDIR)\winio.obj" \
	"$(INTDIR)\winjoy.obj" \
	"$(INTDIR)\winkey.obj" \
	"$(INTDIR)\winmouse.obj" \
	"$(INTDIR)\wintimer.obj"

"$(OUTDIR)\ddio_win.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ddio_win - Win32 OEM Debug"

OUTDIR=.\./OEM_Debug
INTDIR=.\./OEM_Debug
# Begin Custom Macros
OutDir=.\./OEM_Debug
# End Custom Macros

ALL : "$(OUTDIR)\ddio_win.lib"


CLEAN :
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\winfile.obj"
	-@erase "$(INTDIR)\winforcefeedback.obj"
	-@erase "$(INTDIR)\winio.obj"
	-@erase "$(INTDIR)\winjoy.obj"
	-@erase "$(INTDIR)\winkey.obj"
	-@erase "$(INTDIR)\winmouse.obj"
	-@erase "$(INTDIR)\wintimer.obj"
	-@erase "$(OUTDIR)\ddio_win.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=xicl6.exe
CPP_PROJ=/nologo /G5 /MDd /W3 /GX /ZI /Od /I "..\lib" /I "..\lib\win" /I "..\lib\win\directx" /D "_WINDOWS" /D "MONO" /D "WIN32" /D "_DEBUG" /D "OEM" /Fp"$(INTDIR)\ddio_win.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ddio_win.bsc" 
BSC32_SBRS= \
	
LIB32=xilink6.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\ddio_win.lib" 
LIB32_OBJS= \
	"$(INTDIR)\winfile.obj" \
	"$(INTDIR)\winforcefeedback.obj" \
	"$(INTDIR)\winio.obj" \
	"$(INTDIR)\winjoy.obj" \
	"$(INTDIR)\winkey.obj" \
	"$(INTDIR)\winmouse.obj" \
	"$(INTDIR)\wintimer.obj"

"$(OUTDIR)\ddio_win.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ddio_win - Win32 Release"

OUTDIR=.\./Release
INTDIR=.\./Release
# Begin Custom Macros
OutDir=.\./Release
# End Custom Macros

ALL : "$(OUTDIR)\ddio_win.lib"


CLEAN :
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\winfile.obj"
	-@erase "$(INTDIR)\winforcefeedback.obj"
	-@erase "$(INTDIR)\winio.obj"
	-@erase "$(INTDIR)\winjoy.obj"
	-@erase "$(INTDIR)\winkey.obj"
	-@erase "$(INTDIR)\winmouse.obj"
	-@erase "$(INTDIR)\wintimer.obj"
	-@erase "$(OUTDIR)\ddio_win.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=xicl6.exe
CPP_PROJ=/nologo /G5 /MT /W3 /GX /O2 /I "..\lib" /I "..\lib\win" /I "..\lib\win\directx" /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /D "RELEASE" /Fp"$(INTDIR)\ddio_win.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ddio_win.bsc" 
BSC32_SBRS= \
	
LIB32=xilink6.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\ddio_win.lib" 
LIB32_OBJS= \
	"$(INTDIR)\winfile.obj" \
	"$(INTDIR)\winforcefeedback.obj" \
	"$(INTDIR)\winio.obj" \
	"$(INTDIR)\winjoy.obj" \
	"$(INTDIR)\winkey.obj" \
	"$(INTDIR)\winmouse.obj" \
	"$(INTDIR)\wintimer.obj"

"$(OUTDIR)\ddio_win.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ddio_win - Win32 BETA Release"

OUTDIR=.\./BETA_Release
INTDIR=.\./BETA_Release
# Begin Custom Macros
OutDir=.\./BETA_Release
# End Custom Macros

ALL : "$(OUTDIR)\ddio_win.lib"


CLEAN :
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\winfile.obj"
	-@erase "$(INTDIR)\winforcefeedback.obj"
	-@erase "$(INTDIR)\winio.obj"
	-@erase "$(INTDIR)\winjoy.obj"
	-@erase "$(INTDIR)\winkey.obj"
	-@erase "$(INTDIR)\winmouse.obj"
	-@erase "$(INTDIR)\wintimer.obj"
	-@erase "$(OUTDIR)\ddio_win.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=xicl6.exe
CPP_PROJ=/nologo /G5 /MT /W3 /GX /O2 /I "..\lib" /I "..\lib\win" /I "..\lib\win\directx" /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /D "BETA" /Fp"$(INTDIR)\ddio_win.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ddio_win.bsc" 
BSC32_SBRS= \
	
LIB32=xilink6.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\ddio_win.lib" 
LIB32_OBJS= \
	"$(INTDIR)\winfile.obj" \
	"$(INTDIR)\winforcefeedback.obj" \
	"$(INTDIR)\winio.obj" \
	"$(INTDIR)\winjoy.obj" \
	"$(INTDIR)\winkey.obj" \
	"$(INTDIR)\winmouse.obj" \
	"$(INTDIR)\wintimer.obj"

"$(OUTDIR)\ddio_win.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ddio_win - Win32 OEM Release"

OUTDIR=.\./OEM_Release
INTDIR=.\./OEM_Release
# Begin Custom Macros
OutDir=.\./OEM_Release
# End Custom Macros

ALL : "$(OUTDIR)\ddio_win.lib"


CLEAN :
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\winfile.obj"
	-@erase "$(INTDIR)\winforcefeedback.obj"
	-@erase "$(INTDIR)\winio.obj"
	-@erase "$(INTDIR)\winjoy.obj"
	-@erase "$(INTDIR)\winkey.obj"
	-@erase "$(INTDIR)\winmouse.obj"
	-@erase "$(INTDIR)\wintimer.obj"
	-@erase "$(OUTDIR)\ddio_win.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=xicl6.exe
CPP_PROJ=/nologo /G5 /MT /W3 /GX /O2 /I "..\lib" /I "..\lib\win" /I "..\lib\win\directx" /D "NDEBUG" /D "_WINDOWS" /D "OEM" /D "WIN32" /D "RELEASE" /Fp"$(INTDIR)\ddio_win.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ddio_win.bsc" 
BSC32_SBRS= \
	
LIB32=xilink6.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\ddio_win.lib" 
LIB32_OBJS= \
	"$(INTDIR)\winfile.obj" \
	"$(INTDIR)\winforcefeedback.obj" \
	"$(INTDIR)\winio.obj" \
	"$(INTDIR)\winjoy.obj" \
	"$(INTDIR)\winkey.obj" \
	"$(INTDIR)\winmouse.obj" \
	"$(INTDIR)\wintimer.obj"

"$(OUTDIR)\ddio_win.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ddio_win - Win32 Katmai Release"

OUTDIR=.\./Katmai_Release
INTDIR=.\./Katmai_Release
# Begin Custom Macros
OutDir=.\./Katmai_Release
# End Custom Macros

ALL : "$(OUTDIR)\ddio_win.lib"


CLEAN :
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\winfile.obj"
	-@erase "$(INTDIR)\winforcefeedback.obj"
	-@erase "$(INTDIR)\winio.obj"
	-@erase "$(INTDIR)\winjoy.obj"
	-@erase "$(INTDIR)\winkey.obj"
	-@erase "$(INTDIR)\winmouse.obj"
	-@erase "$(INTDIR)\wintimer.obj"
	-@erase "$(OUTDIR)\ddio_win.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=xicl6.exe
CPP_PROJ=/nologo /G5 /MT /W3 /GX /O2 /I "..\lib" /I "..\lib\win" /I "..\lib\win\directx" /D "NDEBUG" /D "_WINDOWS" /D "KATMAI" /D "WIN32" /D "RELEASE" /Fp"$(INTDIR)\ddio_win.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ddio_win.bsc" 
BSC32_SBRS= \
	
LIB32=xilink6.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\ddio_win.lib" 
LIB32_OBJS= \
	"$(INTDIR)\winfile.obj" \
	"$(INTDIR)\winforcefeedback.obj" \
	"$(INTDIR)\winio.obj" \
	"$(INTDIR)\winjoy.obj" \
	"$(INTDIR)\winkey.obj" \
	"$(INTDIR)\winmouse.obj" \
	"$(INTDIR)\wintimer.obj"

"$(OUTDIR)\ddio_win.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ddio_win - Win32 Demo Debug"

OUTDIR=.\./Demo_Debug
INTDIR=.\./Demo_Debug
# Begin Custom Macros
OutDir=.\./Demo_Debug
# End Custom Macros

ALL : "$(OUTDIR)\ddio_win.lib"


CLEAN :
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\winfile.obj"
	-@erase "$(INTDIR)\winforcefeedback.obj"
	-@erase "$(INTDIR)\winio.obj"
	-@erase "$(INTDIR)\winjoy.obj"
	-@erase "$(INTDIR)\winkey.obj"
	-@erase "$(INTDIR)\winmouse.obj"
	-@erase "$(INTDIR)\wintimer.obj"
	-@erase "$(OUTDIR)\ddio_win.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=xicl6.exe
CPP_PROJ=/nologo /G5 /MD /W3 /GX /ZI /Od /I "..\lib" /I "..\lib\win" /I "..\lib\win\directx" /D "DEMO" /D "_WINDOWS" /D "MONO" /D "WIN32" /D "_DEBUG" /Fp"$(INTDIR)\ddio_win.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ddio_win.bsc" 
BSC32_SBRS= \
	
LIB32=xilink6.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\ddio_win.lib" 
LIB32_OBJS= \
	"$(INTDIR)\winfile.obj" \
	"$(INTDIR)\winforcefeedback.obj" \
	"$(INTDIR)\winio.obj" \
	"$(INTDIR)\winjoy.obj" \
	"$(INTDIR)\winkey.obj" \
	"$(INTDIR)\winmouse.obj" \
	"$(INTDIR)\wintimer.obj"

"$(OUTDIR)\ddio_win.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ddio_win - Win32 Demo Release"

OUTDIR=.\./Demo_Release
INTDIR=.\./Demo_Release
# Begin Custom Macros
OutDir=.\./Demo_Release
# End Custom Macros

ALL : "$(OUTDIR)\ddio_win.lib"


CLEAN :
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\winfile.obj"
	-@erase "$(INTDIR)\winforcefeedback.obj"
	-@erase "$(INTDIR)\winio.obj"
	-@erase "$(INTDIR)\winjoy.obj"
	-@erase "$(INTDIR)\winkey.obj"
	-@erase "$(INTDIR)\winmouse.obj"
	-@erase "$(INTDIR)\wintimer.obj"
	-@erase "$(OUTDIR)\ddio_win.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=xicl6.exe
CPP_PROJ=/nologo /G5 /MT /W3 /GX /O2 /I "..\lib" /I "..\lib\win" /I "..\lib\win\directx" /D "DEMO" /D "_WINDOWS" /D "MONO" /D "WIN32" /D "RELEASE" /Fp"$(INTDIR)\ddio_win.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ddio_win.bsc" 
BSC32_SBRS= \
	
LIB32=xilink6.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\ddio_win.lib" 
LIB32_OBJS= \
	"$(INTDIR)\winfile.obj" \
	"$(INTDIR)\winforcefeedback.obj" \
	"$(INTDIR)\winio.obj" \
	"$(INTDIR)\winjoy.obj" \
	"$(INTDIR)\winkey.obj" \
	"$(INTDIR)\winmouse.obj" \
	"$(INTDIR)\wintimer.obj"

"$(OUTDIR)\ddio_win.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ddio_win - Win32 GameGauge Release"

OUTDIR=.\./GameGauge_Release
INTDIR=.\./GameGauge_Release
# Begin Custom Macros
OutDir=.\./GameGauge_Release
# End Custom Macros

ALL : "$(OUTDIR)\ddio_win.lib"


CLEAN :
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\winfile.obj"
	-@erase "$(INTDIR)\winforcefeedback.obj"
	-@erase "$(INTDIR)\winio.obj"
	-@erase "$(INTDIR)\winjoy.obj"
	-@erase "$(INTDIR)\winkey.obj"
	-@erase "$(INTDIR)\winmouse.obj"
	-@erase "$(INTDIR)\wintimer.obj"
	-@erase "$(OUTDIR)\ddio_win.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=xicl6.exe
CPP_PROJ=/nologo /G5 /MT /W3 /GX /O2 /I "..\lib" /I "..\lib\win" /I "..\lib\win\directx" /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /D "GAMEGAUGE" /D "RELEASE" /Fp"$(INTDIR)\ddio_win.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ddio_win.bsc" 
BSC32_SBRS= \
	
LIB32=xilink6.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\ddio_win.lib" 
LIB32_OBJS= \
	"$(INTDIR)\winfile.obj" \
	"$(INTDIR)\winforcefeedback.obj" \
	"$(INTDIR)\winio.obj" \
	"$(INTDIR)\winjoy.obj" \
	"$(INTDIR)\winkey.obj" \
	"$(INTDIR)\winmouse.obj" \
	"$(INTDIR)\wintimer.obj"

"$(OUTDIR)\ddio_win.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("ddio_win.dep")
!INCLUDE "ddio_win.dep"
!ELSE 
!MESSAGE Warning: cannot find "ddio_win.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ddio_win - Win32 Debug" || "$(CFG)" == "ddio_win - Win32 OEM Debug" || "$(CFG)" == "ddio_win - Win32 Release" || "$(CFG)" == "ddio_win - Win32 BETA Release" || "$(CFG)" == "ddio_win - Win32 OEM Release" || "$(CFG)" == "ddio_win - Win32 Katmai Release" || "$(CFG)" == "ddio_win - Win32 Demo Debug" || "$(CFG)" == "ddio_win - Win32 Demo Release" || "$(CFG)" == "ddio_win - Win32 GameGauge Release"
SOURCE=.\winfile.cpp

"$(INTDIR)\winfile.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\winforcefeedback.cpp

"$(INTDIR)\winforcefeedback.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\winio.cpp

"$(INTDIR)\winio.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\winjoy.cpp

"$(INTDIR)\winjoy.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\winkey.cpp

"$(INTDIR)\winkey.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\winmouse.cpp

"$(INTDIR)\winmouse.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\wintimer.cpp

"$(INTDIR)\wintimer.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

