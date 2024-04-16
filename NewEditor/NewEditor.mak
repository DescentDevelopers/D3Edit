# Microsoft Developer Studio Generated NMAKE File, Based on NewEditor.dsp
!IF "$(CFG)" == ""
CFG=NewEditor - Win32 Debug
!MESSAGE No configuration specified. Defaulting to NewEditor - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "NewEditor - Win32 Release" && "$(CFG)" != "NewEditor - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "NewEditor.mak" CFG="NewEditor - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "NewEditor - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "NewEditor - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "NewEditor - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\NewEditor.exe"

!ELSE 

ALL : "module - Win32 Release" "ddio_win - Win32 Release" "ddio_common - Win32 Release" "3d - Win32 Release" "ddvid_win32 - Win32 Release" "texmap - Win32 Release" "2dlib - Win32 Release" "ddgr_win32 - Win32 Release" "misc - Win32 Release" "win32 - Win32 Release" "vecmat - Win32 Release" "mem - Win32 Release" "fix - Win32 Release" "cfile - Win32 Release" "bitmap - Win32 Release" "$(OUTDIR)\NewEditor.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"bitmap - Win32 ReleaseCLEAN" "cfile - Win32 ReleaseCLEAN" "fix - Win32 ReleaseCLEAN" "mem - Win32 ReleaseCLEAN" "vecmat - Win32 ReleaseCLEAN" "win32 - Win32 ReleaseCLEAN" "misc - Win32 ReleaseCLEAN" "ddgr_win32 - Win32 ReleaseCLEAN" "2dlib - Win32 ReleaseCLEAN" "texmap - Win32 ReleaseCLEAN" "ddvid_win32 - Win32 ReleaseCLEAN" "3d - Win32 ReleaseCLEAN" "ddio_common - Win32 ReleaseCLEAN" "ddio_win - Win32 ReleaseCLEAN" "module - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\boa.obj"
	-@erase "$(INTDIR)\CameraSlew.obj"
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\ChildView.obj"
	-@erase "$(INTDIR)\globals.obj"
	-@erase "$(INTDIR)\GrListBox.obj"
	-@erase "$(INTDIR)\LevelFrame.obj"
	-@erase "$(INTDIR)\LevelInfoDialog.obj"
	-@erase "$(INTDIR)\lightmap_info.obj"
	-@erase "$(INTDIR)\loadlevel.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\ned_DrawWorld.obj"
	-@erase "$(INTDIR)\ned_GameTexture.obj"
	-@erase "$(INTDIR)\ned_GrWnd.obj"
	-@erase "$(INTDIR)\ned_HFile.obj"
	-@erase "$(INTDIR)\ned_LevelWnd.obj"
	-@erase "$(INTDIR)\ned_Object.obj"
	-@erase "$(INTDIR)\ned_OrthoWnd.obj"
	-@erase "$(INTDIR)\ned_PerspWnd.obj"
	-@erase "$(INTDIR)\ned_Render.obj"
	-@erase "$(INTDIR)\ned_Renderer.obj"
	-@erase "$(INTDIR)\ned_RendOpenGL.obj"
	-@erase "$(INTDIR)\ned_TableRead.obj"
	-@erase "$(INTDIR)\ned_Util.obj"
	-@erase "$(INTDIR)\NewEditor.obj"
	-@erase "$(INTDIR)\NewEditor.res"
	-@erase "$(INTDIR)\ProgressDialog.obj"
	-@erase "$(INTDIR)\room.obj"
	-@erase "$(INTDIR)\RoomFrm.obj"
	-@erase "$(INTDIR)\selectedroom.obj"
	-@erase "$(INTDIR)\SelManager.obj"
	-@erase "$(INTDIR)\SettingsDialog.obj"
	-@erase "$(INTDIR)\special_face.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TablefileManager.obj"
	-@erase "$(INTDIR)\TableView.obj"
	-@erase "$(INTDIR)\TextureDialogBar.obj"
	-@erase "$(INTDIR)\TexturePalette.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\Vclip.obj"
	-@erase "$(OUTDIR)\NewEditor.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=xicl6.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\lib" /I "..\lib\win" /I "..\lib\win\directx" /I "..\\" /I "..\editor" /D "_WINDOWS" /D "WIN32" /D "RELEASE" /D "NEWEDITOR" /Fp"$(INTDIR)\NewEditor.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\NewEditor.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\NewEditor.bsc" 
BSC32_SBRS= \
	
LINK32=xilink6.exe
LINK32_FLAGS=wsock32.lib winmm.lib ..\lib\win\directx\ddraw.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\NewEditor.pdb" /machine:I386 /out:"$(OUTDIR)\NewEditor.exe" 
LINK32_OBJS= \
	"$(INTDIR)\boa.obj" \
	"$(INTDIR)\CameraSlew.obj" \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\ChildView.obj" \
	"$(INTDIR)\globals.obj" \
	"$(INTDIR)\GrListBox.obj" \
	"$(INTDIR)\LevelFrame.obj" \
	"$(INTDIR)\LevelInfoDialog.obj" \
	"$(INTDIR)\lightmap_info.obj" \
	"$(INTDIR)\loadlevel.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\ned_DrawWorld.obj" \
	"$(INTDIR)\ned_GameTexture.obj" \
	"$(INTDIR)\ned_GrWnd.obj" \
	"$(INTDIR)\ned_HFile.obj" \
	"$(INTDIR)\ned_LevelWnd.obj" \
	"$(INTDIR)\ned_Object.obj" \
	"$(INTDIR)\ned_OrthoWnd.obj" \
	"$(INTDIR)\ned_PerspWnd.obj" \
	"$(INTDIR)\ned_Render.obj" \
	"$(INTDIR)\ned_Renderer.obj" \
	"$(INTDIR)\ned_RendOpenGL.obj" \
	"$(INTDIR)\ned_TableRead.obj" \
	"$(INTDIR)\ned_Util.obj" \
	"$(INTDIR)\NewEditor.obj" \
	"$(INTDIR)\ProgressDialog.obj" \
	"$(INTDIR)\room.obj" \
	"$(INTDIR)\RoomFrm.obj" \
	"$(INTDIR)\selectedroom.obj" \
	"$(INTDIR)\SelManager.obj" \
	"$(INTDIR)\SettingsDialog.obj" \
	"$(INTDIR)\special_face.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TablefileManager.obj" \
	"$(INTDIR)\TableView.obj" \
	"$(INTDIR)\TextureDialogBar.obj" \
	"$(INTDIR)\TexturePalette.obj" \
	"$(INTDIR)\Vclip.obj" \
	"$(INTDIR)\NewEditor.res" \
	"..\bitmap\Release\bitmap.lib" \
	"..\cfile\Release\cfile.lib" \
	"..\fix\Release\fix.lib" \
	"..\mem\Release\mem.lib" \
	"..\vecmat\Release\vecmat.lib" \
	"..\win32\Release\win32.lib" \
	"..\misc\Release\misc.lib" \
	"..\ddgr_win32\Release\ddgr_win32.lib" \
	"..\2dlib\Release\2dlib.lib" \
	"..\texmap\Release\texmap.lib" \
	"..\ddvid_win32\Release\ddvid_win32.lib" \
	"..\3d\Release\3d.lib" \
	"..\ddio_common\Release\ddio_common.lib" \
	"..\ddio_win\Release\ddio_win.lib" \
	"..\lib\module.lib"

"$(OUTDIR)\NewEditor.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "NewEditor - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\NewEditor.exe"

!ELSE 

ALL : "module - Win32 Debug" "ddio_win - Win32 Debug" "ddio_common - Win32 Debug" "3d - Win32 Debug" "ddvid_win32 - Win32 Debug" "texmap - Win32 Debug" "2dlib - Win32 Debug" "ddgr_win32 - Win32 Debug" "misc - Win32 Debug" "win32 - Win32 Debug" "vecmat - Win32 Debug" "mem - Win32 Debug" "fix - Win32 Debug" "cfile - Win32 Debug" "bitmap - Win32 Debug" "$(OUTDIR)\NewEditor.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"bitmap - Win32 DebugCLEAN" "cfile - Win32 DebugCLEAN" "fix - Win32 DebugCLEAN" "mem - Win32 DebugCLEAN" "vecmat - Win32 DebugCLEAN" "win32 - Win32 DebugCLEAN" "misc - Win32 DebugCLEAN" "ddgr_win32 - Win32 DebugCLEAN" "2dlib - Win32 DebugCLEAN" "texmap - Win32 DebugCLEAN" "ddvid_win32 - Win32 DebugCLEAN" "3d - Win32 DebugCLEAN" "ddio_common - Win32 DebugCLEAN" "ddio_win - Win32 DebugCLEAN" "module - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\boa.obj"
	-@erase "$(INTDIR)\CameraSlew.obj"
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\ChildView.obj"
	-@erase "$(INTDIR)\globals.obj"
	-@erase "$(INTDIR)\GrListBox.obj"
	-@erase "$(INTDIR)\LevelFrame.obj"
	-@erase "$(INTDIR)\LevelInfoDialog.obj"
	-@erase "$(INTDIR)\lightmap_info.obj"
	-@erase "$(INTDIR)\loadlevel.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\ned_DrawWorld.obj"
	-@erase "$(INTDIR)\ned_GameTexture.obj"
	-@erase "$(INTDIR)\ned_GrWnd.obj"
	-@erase "$(INTDIR)\ned_HFile.obj"
	-@erase "$(INTDIR)\ned_LevelWnd.obj"
	-@erase "$(INTDIR)\ned_Object.obj"
	-@erase "$(INTDIR)\ned_OrthoWnd.obj"
	-@erase "$(INTDIR)\ned_PerspWnd.obj"
	-@erase "$(INTDIR)\ned_Render.obj"
	-@erase "$(INTDIR)\ned_Renderer.obj"
	-@erase "$(INTDIR)\ned_RendOpenGL.obj"
	-@erase "$(INTDIR)\ned_TableRead.obj"
	-@erase "$(INTDIR)\ned_Util.obj"
	-@erase "$(INTDIR)\NewEditor.obj"
	-@erase "$(INTDIR)\NewEditor.res"
	-@erase "$(INTDIR)\ProgressDialog.obj"
	-@erase "$(INTDIR)\room.obj"
	-@erase "$(INTDIR)\RoomFrm.obj"
	-@erase "$(INTDIR)\selectedroom.obj"
	-@erase "$(INTDIR)\SelManager.obj"
	-@erase "$(INTDIR)\SettingsDialog.obj"
	-@erase "$(INTDIR)\special_face.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TablefileManager.obj"
	-@erase "$(INTDIR)\TableView.obj"
	-@erase "$(INTDIR)\TextureDialogBar.obj"
	-@erase "$(INTDIR)\TexturePalette.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\Vclip.obj"
	-@erase "$(OUTDIR)\NewEditor.exe"
	-@erase "$(OUTDIR)\NewEditor.ilk"
	-@erase "$(OUTDIR)\NewEditor.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=xicl6.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\lib" /I "..\lib\win" /I "..\lib\win\directx" /I "..\\" /I "..\editor" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "MONO" /D "NEWEDITOR" /D "_AFXDLL" /Fp"$(INTDIR)\NewEditor.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\NewEditor.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\NewEditor.bsc" 
BSC32_SBRS= \
	
LINK32=xilink6.exe
LINK32_FLAGS=wsock32.lib winmm.lib ..\lib\win\directx\ddraw.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\NewEditor.pdb" /debug /machine:I386 /out:"$(OUTDIR)\NewEditor.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\boa.obj" \
	"$(INTDIR)\CameraSlew.obj" \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\ChildView.obj" \
	"$(INTDIR)\globals.obj" \
	"$(INTDIR)\GrListBox.obj" \
	"$(INTDIR)\LevelFrame.obj" \
	"$(INTDIR)\LevelInfoDialog.obj" \
	"$(INTDIR)\lightmap_info.obj" \
	"$(INTDIR)\loadlevel.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\ned_DrawWorld.obj" \
	"$(INTDIR)\ned_GameTexture.obj" \
	"$(INTDIR)\ned_GrWnd.obj" \
	"$(INTDIR)\ned_HFile.obj" \
	"$(INTDIR)\ned_LevelWnd.obj" \
	"$(INTDIR)\ned_Object.obj" \
	"$(INTDIR)\ned_OrthoWnd.obj" \
	"$(INTDIR)\ned_PerspWnd.obj" \
	"$(INTDIR)\ned_Render.obj" \
	"$(INTDIR)\ned_Renderer.obj" \
	"$(INTDIR)\ned_RendOpenGL.obj" \
	"$(INTDIR)\ned_TableRead.obj" \
	"$(INTDIR)\ned_Util.obj" \
	"$(INTDIR)\NewEditor.obj" \
	"$(INTDIR)\ProgressDialog.obj" \
	"$(INTDIR)\room.obj" \
	"$(INTDIR)\RoomFrm.obj" \
	"$(INTDIR)\selectedroom.obj" \
	"$(INTDIR)\SelManager.obj" \
	"$(INTDIR)\SettingsDialog.obj" \
	"$(INTDIR)\special_face.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TablefileManager.obj" \
	"$(INTDIR)\TableView.obj" \
	"$(INTDIR)\TextureDialogBar.obj" \
	"$(INTDIR)\TexturePalette.obj" \
	"$(INTDIR)\Vclip.obj" \
	"$(INTDIR)\NewEditor.res" \
	"..\bitmap\Debug\bitmap.lib" \
	"..\cfile\Debug\cfile.lib" \
	"..\fix\Debug\fix.lib" \
	"..\mem\Debug\mem.lib" \
	"..\vecmat\Debug\vecmat.lib" \
	"..\win32\Debug\win32.lib" \
	"..\misc\Debug\misc.lib" \
	"..\ddgr_win32\Debug\ddgr_win32.lib" \
	"..\2dlib\Debug\2dlib.lib" \
	"..\texmap\Debug\texmap.lib" \
	"..\ddvid_win32\Debug\ddvid_win32.lib" \
	"..\3d\Debug\3d.lib" \
	"..\ddio_common\Debug\ddio_common.lib" \
	"..\ddio_win\Debug\ddio_win.lib" \
	"..\module\Debug\module.lib"

"$(OUTDIR)\NewEditor.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("NewEditor.dep")
!INCLUDE "NewEditor.dep"
!ELSE 
!MESSAGE Warning: cannot find "NewEditor.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "NewEditor - Win32 Release" || "$(CFG)" == "NewEditor - Win32 Debug"
SOURCE=..\boa.cpp

"$(INTDIR)\boa.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\CameraSlew.cpp

"$(INTDIR)\CameraSlew.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ChildFrm.cpp

"$(INTDIR)\ChildFrm.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ChildView.cpp

"$(INTDIR)\ChildView.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\globals.cpp

"$(INTDIR)\globals.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\GrListBox.cpp

"$(INTDIR)\GrListBox.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\LevelFrame.cpp

"$(INTDIR)\LevelFrame.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\LevelInfoDialog.cpp

"$(INTDIR)\LevelInfoDialog.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=..\lightmap_info.cpp

"$(INTDIR)\lightmap_info.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\loadlevel.cpp

"$(INTDIR)\loadlevel.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\MainFrm.cpp

"$(INTDIR)\MainFrm.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ned_DrawWorld.cpp

"$(INTDIR)\ned_DrawWorld.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ned_GameTexture.cpp

"$(INTDIR)\ned_GameTexture.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ned_GrWnd.cpp

"$(INTDIR)\ned_GrWnd.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ned_HFile.cpp

"$(INTDIR)\ned_HFile.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ned_LevelWnd.cpp

"$(INTDIR)\ned_LevelWnd.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ned_Object.cpp

"$(INTDIR)\ned_Object.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ned_OrthoWnd.cpp

"$(INTDIR)\ned_OrthoWnd.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ned_PerspWnd.cpp

"$(INTDIR)\ned_PerspWnd.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ned_Render.cpp

"$(INTDIR)\ned_Render.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ned_Renderer.cpp

"$(INTDIR)\ned_Renderer.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ned_RendOpenGL.cpp

"$(INTDIR)\ned_RendOpenGL.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ned_TableRead.cpp

"$(INTDIR)\ned_TableRead.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ned_Util.cpp

"$(INTDIR)\ned_Util.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\NewEditor.cpp

"$(INTDIR)\NewEditor.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\NewEditor.rc

"$(INTDIR)\NewEditor.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\ProgressDialog.cpp

"$(INTDIR)\ProgressDialog.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=..\room.cpp

"$(INTDIR)\room.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\RoomFrm.cpp

"$(INTDIR)\RoomFrm.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=..\editor\selectedroom.cpp

"$(INTDIR)\selectedroom.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\editor\SelManager.cpp

"$(INTDIR)\SelManager.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\SettingsDialog.cpp

"$(INTDIR)\SettingsDialog.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=..\special_face.cpp

"$(INTDIR)\special_face.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

"$(INTDIR)\StdAfx.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\TablefileManager.cpp

"$(INTDIR)\TablefileManager.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\TableView.cpp

"$(INTDIR)\TableView.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\TextureDialogBar.cpp

"$(INTDIR)\TextureDialogBar.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\TexturePalette.cpp

"$(INTDIR)\TexturePalette.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=..\Vclip.cpp

"$(INTDIR)\Vclip.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!IF  "$(CFG)" == "NewEditor - Win32 Release"

"bitmap - Win32 Release" : 
   cd "\descent3\main\bitmap"
   $(MAKE) /$(MAKEFLAGS) /F .\bitmap.mak CFG="bitmap - Win32 Release" 
   cd "..\NewEditor"

"bitmap - Win32 ReleaseCLEAN" : 
   cd "\descent3\main\bitmap"
   $(MAKE) /$(MAKEFLAGS) /F .\bitmap.mak CFG="bitmap - Win32 Release" RECURSE=1 CLEAN 
   cd "..\NewEditor"

!ELSEIF  "$(CFG)" == "NewEditor - Win32 Debug"

"bitmap - Win32 Debug" : 
   cd "\descent3\main\bitmap"
   $(MAKE) /$(MAKEFLAGS) /F .\bitmap.mak CFG="bitmap - Win32 Debug" 
   cd "..\NewEditor"

"bitmap - Win32 DebugCLEAN" : 
   cd "\descent3\main\bitmap"
   $(MAKE) /$(MAKEFLAGS) /F .\bitmap.mak CFG="bitmap - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\NewEditor"

!ENDIF 

!IF  "$(CFG)" == "NewEditor - Win32 Release"

"cfile - Win32 Release" : 
   cd "\descent3\main\cfile"
   $(MAKE) /$(MAKEFLAGS) /F .\cfile.mak CFG="cfile - Win32 Release" 
   cd "..\NewEditor"

"cfile - Win32 ReleaseCLEAN" : 
   cd "\descent3\main\cfile"
   $(MAKE) /$(MAKEFLAGS) /F .\cfile.mak CFG="cfile - Win32 Release" RECURSE=1 CLEAN 
   cd "..\NewEditor"

!ELSEIF  "$(CFG)" == "NewEditor - Win32 Debug"

"cfile - Win32 Debug" : 
   cd "\descent3\main\cfile"
   $(MAKE) /$(MAKEFLAGS) /F .\cfile.mak CFG="cfile - Win32 Debug" 
   cd "..\NewEditor"

"cfile - Win32 DebugCLEAN" : 
   cd "\descent3\main\cfile"
   $(MAKE) /$(MAKEFLAGS) /F .\cfile.mak CFG="cfile - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\NewEditor"

!ENDIF 

!IF  "$(CFG)" == "NewEditor - Win32 Release"

"fix - Win32 Release" : 
   cd "\descent3\main\fix"
   $(MAKE) /$(MAKEFLAGS) /F .\fix.mak CFG="fix - Win32 Release" 
   cd "..\NewEditor"

"fix - Win32 ReleaseCLEAN" : 
   cd "\descent3\main\fix"
   $(MAKE) /$(MAKEFLAGS) /F .\fix.mak CFG="fix - Win32 Release" RECURSE=1 CLEAN 
   cd "..\NewEditor"

!ELSEIF  "$(CFG)" == "NewEditor - Win32 Debug"

"fix - Win32 Debug" : 
   cd "\descent3\main\fix"
   $(MAKE) /$(MAKEFLAGS) /F .\fix.mak CFG="fix - Win32 Debug" 
   cd "..\NewEditor"

"fix - Win32 DebugCLEAN" : 
   cd "\descent3\main\fix"
   $(MAKE) /$(MAKEFLAGS) /F .\fix.mak CFG="fix - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\NewEditor"

!ENDIF 

!IF  "$(CFG)" == "NewEditor - Win32 Release"

"mem - Win32 Release" : 
   cd "\descent3\main\mem"
   $(MAKE) /$(MAKEFLAGS) /F .\mem.mak CFG="mem - Win32 Release" 
   cd "..\NewEditor"

"mem - Win32 ReleaseCLEAN" : 
   cd "\descent3\main\mem"
   $(MAKE) /$(MAKEFLAGS) /F .\mem.mak CFG="mem - Win32 Release" RECURSE=1 CLEAN 
   cd "..\NewEditor"

!ELSEIF  "$(CFG)" == "NewEditor - Win32 Debug"

"mem - Win32 Debug" : 
   cd "\descent3\main\mem"
   $(MAKE) /$(MAKEFLAGS) /F .\mem.mak CFG="mem - Win32 Debug" 
   cd "..\NewEditor"

"mem - Win32 DebugCLEAN" : 
   cd "\descent3\main\mem"
   $(MAKE) /$(MAKEFLAGS) /F .\mem.mak CFG="mem - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\NewEditor"

!ENDIF 

!IF  "$(CFG)" == "NewEditor - Win32 Release"

"vecmat - Win32 Release" : 
   cd "\descent3\main\vecmat"
   $(MAKE) /$(MAKEFLAGS) /F .\vecmat.mak CFG="vecmat - Win32 Release" 
   cd "..\NewEditor"

"vecmat - Win32 ReleaseCLEAN" : 
   cd "\descent3\main\vecmat"
   $(MAKE) /$(MAKEFLAGS) /F .\vecmat.mak CFG="vecmat - Win32 Release" RECURSE=1 CLEAN 
   cd "..\NewEditor"

!ELSEIF  "$(CFG)" == "NewEditor - Win32 Debug"

"vecmat - Win32 Debug" : 
   cd "\descent3\main\vecmat"
   $(MAKE) /$(MAKEFLAGS) /F .\vecmat.mak CFG="vecmat - Win32 Debug" 
   cd "..\NewEditor"

"vecmat - Win32 DebugCLEAN" : 
   cd "\descent3\main\vecmat"
   $(MAKE) /$(MAKEFLAGS) /F .\vecmat.mak CFG="vecmat - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\NewEditor"

!ENDIF 

!IF  "$(CFG)" == "NewEditor - Win32 Release"

"win32 - Win32 Release" : 
   cd "\descent3\main\win32"
   $(MAKE) /$(MAKEFLAGS) /F .\win32.mak CFG="win32 - Win32 Release" 
   cd "..\NewEditor"

"win32 - Win32 ReleaseCLEAN" : 
   cd "\descent3\main\win32"
   $(MAKE) /$(MAKEFLAGS) /F .\win32.mak CFG="win32 - Win32 Release" RECURSE=1 CLEAN 
   cd "..\NewEditor"

!ELSEIF  "$(CFG)" == "NewEditor - Win32 Debug"

"win32 - Win32 Debug" : 
   cd "\descent3\main\win32"
   $(MAKE) /$(MAKEFLAGS) /F .\win32.mak CFG="win32 - Win32 Debug" 
   cd "..\NewEditor"

"win32 - Win32 DebugCLEAN" : 
   cd "\descent3\main\win32"
   $(MAKE) /$(MAKEFLAGS) /F .\win32.mak CFG="win32 - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\NewEditor"

!ENDIF 

!IF  "$(CFG)" == "NewEditor - Win32 Release"

"misc - Win32 Release" : 
   cd "\descent3\main\misc"
   $(MAKE) /$(MAKEFLAGS) /F .\misc.mak CFG="misc - Win32 Release" 
   cd "..\NewEditor"

"misc - Win32 ReleaseCLEAN" : 
   cd "\descent3\main\misc"
   $(MAKE) /$(MAKEFLAGS) /F .\misc.mak CFG="misc - Win32 Release" RECURSE=1 CLEAN 
   cd "..\NewEditor"

!ELSEIF  "$(CFG)" == "NewEditor - Win32 Debug"

"misc - Win32 Debug" : 
   cd "\descent3\main\misc"
   $(MAKE) /$(MAKEFLAGS) /F .\misc.mak CFG="misc - Win32 Debug" 
   cd "..\NewEditor"

"misc - Win32 DebugCLEAN" : 
   cd "\descent3\main\misc"
   $(MAKE) /$(MAKEFLAGS) /F .\misc.mak CFG="misc - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\NewEditor"

!ENDIF 

!IF  "$(CFG)" == "NewEditor - Win32 Release"

"ddgr_win32 - Win32 Release" : 
   cd "\descent3\main\ddgr_win32"
   $(MAKE) /$(MAKEFLAGS) /F .\ddgr_win32.mak CFG="ddgr_win32 - Win32 Release" 
   cd "..\NewEditor"

"ddgr_win32 - Win32 ReleaseCLEAN" : 
   cd "\descent3\main\ddgr_win32"
   $(MAKE) /$(MAKEFLAGS) /F .\ddgr_win32.mak CFG="ddgr_win32 - Win32 Release" RECURSE=1 CLEAN 
   cd "..\NewEditor"

!ELSEIF  "$(CFG)" == "NewEditor - Win32 Debug"

"ddgr_win32 - Win32 Debug" : 
   cd "\descent3\main\ddgr_win32"
   $(MAKE) /$(MAKEFLAGS) /F .\ddgr_win32.mak CFG="ddgr_win32 - Win32 Debug" 
   cd "..\NewEditor"

"ddgr_win32 - Win32 DebugCLEAN" : 
   cd "\descent3\main\ddgr_win32"
   $(MAKE) /$(MAKEFLAGS) /F .\ddgr_win32.mak CFG="ddgr_win32 - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\NewEditor"

!ENDIF 

!IF  "$(CFG)" == "NewEditor - Win32 Release"

"2dlib - Win32 Release" : 
   cd "\descent3\main\2dlib"
   $(MAKE) /$(MAKEFLAGS) /F .\2dlib.mak CFG="2dlib - Win32 Release" 
   cd "..\NewEditor"

"2dlib - Win32 ReleaseCLEAN" : 
   cd "\descent3\main\2dlib"
   $(MAKE) /$(MAKEFLAGS) /F .\2dlib.mak CFG="2dlib - Win32 Release" RECURSE=1 CLEAN 
   cd "..\NewEditor"

!ELSEIF  "$(CFG)" == "NewEditor - Win32 Debug"

"2dlib - Win32 Debug" : 
   cd "\descent3\main\2dlib"
   $(MAKE) /$(MAKEFLAGS) /F .\2dlib.mak CFG="2dlib - Win32 Debug" 
   cd "..\NewEditor"

"2dlib - Win32 DebugCLEAN" : 
   cd "\descent3\main\2dlib"
   $(MAKE) /$(MAKEFLAGS) /F .\2dlib.mak CFG="2dlib - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\NewEditor"

!ENDIF 

!IF  "$(CFG)" == "NewEditor - Win32 Release"

"texmap - Win32 Release" : 
   cd "\descent3\main\texmap"
   $(MAKE) /$(MAKEFLAGS) /F .\texmap.mak CFG="texmap - Win32 Release" 
   cd "..\NewEditor"

"texmap - Win32 ReleaseCLEAN" : 
   cd "\descent3\main\texmap"
   $(MAKE) /$(MAKEFLAGS) /F .\texmap.mak CFG="texmap - Win32 Release" RECURSE=1 CLEAN 
   cd "..\NewEditor"

!ELSEIF  "$(CFG)" == "NewEditor - Win32 Debug"

"texmap - Win32 Debug" : 
   cd "\descent3\main\texmap"
   $(MAKE) /$(MAKEFLAGS) /F .\texmap.mak CFG="texmap - Win32 Debug" 
   cd "..\NewEditor"

"texmap - Win32 DebugCLEAN" : 
   cd "\descent3\main\texmap"
   $(MAKE) /$(MAKEFLAGS) /F .\texmap.mak CFG="texmap - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\NewEditor"

!ENDIF 

!IF  "$(CFG)" == "NewEditor - Win32 Release"

"ddvid_win32 - Win32 Release" : 
   cd "\descent3\main\ddvid_win32"
   $(MAKE) /$(MAKEFLAGS) /F .\ddvid_win32.mak CFG="ddvid_win32 - Win32 Release" 
   cd "..\NewEditor"

"ddvid_win32 - Win32 ReleaseCLEAN" : 
   cd "\descent3\main\ddvid_win32"
   $(MAKE) /$(MAKEFLAGS) /F .\ddvid_win32.mak CFG="ddvid_win32 - Win32 Release" RECURSE=1 CLEAN 
   cd "..\NewEditor"

!ELSEIF  "$(CFG)" == "NewEditor - Win32 Debug"

"ddvid_win32 - Win32 Debug" : 
   cd "\descent3\main\ddvid_win32"
   $(MAKE) /$(MAKEFLAGS) /F .\ddvid_win32.mak CFG="ddvid_win32 - Win32 Debug" 
   cd "..\NewEditor"

"ddvid_win32 - Win32 DebugCLEAN" : 
   cd "\descent3\main\ddvid_win32"
   $(MAKE) /$(MAKEFLAGS) /F .\ddvid_win32.mak CFG="ddvid_win32 - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\NewEditor"

!ENDIF 

!IF  "$(CFG)" == "NewEditor - Win32 Release"

"3d - Win32 Release" : 
   cd "\descent3\main\3d"
   $(MAKE) /$(MAKEFLAGS) /F .\3d.mak CFG="3d - Win32 Release" 
   cd "..\NewEditor"

"3d - Win32 ReleaseCLEAN" : 
   cd "\descent3\main\3d"
   $(MAKE) /$(MAKEFLAGS) /F .\3d.mak CFG="3d - Win32 Release" RECURSE=1 CLEAN 
   cd "..\NewEditor"

!ELSEIF  "$(CFG)" == "NewEditor - Win32 Debug"

"3d - Win32 Debug" : 
   cd "\descent3\main\3d"
   $(MAKE) /$(MAKEFLAGS) /F .\3d.mak CFG="3d - Win32 Debug" 
   cd "..\NewEditor"

"3d - Win32 DebugCLEAN" : 
   cd "\descent3\main\3d"
   $(MAKE) /$(MAKEFLAGS) /F .\3d.mak CFG="3d - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\NewEditor"

!ENDIF 

!IF  "$(CFG)" == "NewEditor - Win32 Release"

"ddio_common - Win32 Release" : 
   cd "\descent3\main\ddio_common"
   $(MAKE) /$(MAKEFLAGS) /F .\ddio_common.mak CFG="ddio_common - Win32 Release" 
   cd "..\NewEditor"

"ddio_common - Win32 ReleaseCLEAN" : 
   cd "\descent3\main\ddio_common"
   $(MAKE) /$(MAKEFLAGS) /F .\ddio_common.mak CFG="ddio_common - Win32 Release" RECURSE=1 CLEAN 
   cd "..\NewEditor"

!ELSEIF  "$(CFG)" == "NewEditor - Win32 Debug"

"ddio_common - Win32 Debug" : 
   cd "\descent3\main\ddio_common"
   $(MAKE) /$(MAKEFLAGS) /F .\ddio_common.mak CFG="ddio_common - Win32 Debug" 
   cd "..\NewEditor"

"ddio_common - Win32 DebugCLEAN" : 
   cd "\descent3\main\ddio_common"
   $(MAKE) /$(MAKEFLAGS) /F .\ddio_common.mak CFG="ddio_common - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\NewEditor"

!ENDIF 

!IF  "$(CFG)" == "NewEditor - Win32 Release"

"ddio_win - Win32 Release" : 
   cd "\descent3\main\ddio_win"
   $(MAKE) /$(MAKEFLAGS) /F .\ddio_win.mak CFG="ddio_win - Win32 Release" 
   cd "..\NewEditor"

"ddio_win - Win32 ReleaseCLEAN" : 
   cd "\descent3\main\ddio_win"
   $(MAKE) /$(MAKEFLAGS) /F .\ddio_win.mak CFG="ddio_win - Win32 Release" RECURSE=1 CLEAN 
   cd "..\NewEditor"

!ELSEIF  "$(CFG)" == "NewEditor - Win32 Debug"

"ddio_win - Win32 Debug" : 
   cd "\descent3\main\ddio_win"
   $(MAKE) /$(MAKEFLAGS) /F .\ddio_win.mak CFG="ddio_win - Win32 Debug" 
   cd "..\NewEditor"

"ddio_win - Win32 DebugCLEAN" : 
   cd "\descent3\main\ddio_win"
   $(MAKE) /$(MAKEFLAGS) /F .\ddio_win.mak CFG="ddio_win - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\NewEditor"

!ENDIF 

!IF  "$(CFG)" == "NewEditor - Win32 Release"

"module - Win32 Release" : 
   cd "\descent3\main\module"
   $(MAKE) /$(MAKEFLAGS) /F .\module.mak CFG="module - Win32 Release" 
   cd "..\NewEditor"

"module - Win32 ReleaseCLEAN" : 
   cd "\descent3\main\module"
   $(MAKE) /$(MAKEFLAGS) /F .\module.mak CFG="module - Win32 Release" RECURSE=1 CLEAN 
   cd "..\NewEditor"

!ELSEIF  "$(CFG)" == "NewEditor - Win32 Debug"

"module - Win32 Debug" : 
   cd "\descent3\main\module"
   $(MAKE) /$(MAKEFLAGS) /F .\module.mak CFG="module - Win32 Debug" 
   cd "..\NewEditor"

"module - Win32 DebugCLEAN" : 
   cd "\descent3\main\module"
   $(MAKE) /$(MAKEFLAGS) /F .\module.mak CFG="module - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\NewEditor"

!ENDIF 


!ENDIF 

