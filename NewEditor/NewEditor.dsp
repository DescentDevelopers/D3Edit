# Microsoft Developer Studio Project File - Name="NewEditor" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=NewEditor - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "NewEditor.mak".
!MESSAGE 
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

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/DescentIII/Main/NewEditor", UXLAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "NewEditor - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "." /I "..\lib" /I "..\lib\win" /I "..\lib\win\directx" /I "..\\" /I "..\editor" /D "_WINDOWS" /D "WIN32" /D "RELEASE" /D "NEWEDITOR" /YX /FD /c
# SUBTRACT CPP /u
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 nafxcw.lib libcmt.lib wsock32.lib winmm.lib ..\lib\win\directx\ddraw.lib ..\lib\win\directx\dinput.lib ..\lib\win\directx\dxguid.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"nafxcw.lib libcmt.lib" /out:"Release/d3edit.exe"
# SUBTRACT LINK32 /verbose /debug /nodefaultlib

!ELSEIF  "$(CFG)" == "NewEditor - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I "..\lib" /I "..\lib\win" /I "..\lib\win\directx" /I "..\\" /I "..\editor" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "MONO" /D "NEWEDITOR" /D "_AFXDLL" /D "_G_TEST_" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 wsock32.lib winmm.lib ..\lib\win\directx\ddraw.lib ..\lib\win\directx\dinput.lib ..\lib\win\directx\dxguid.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "NewEditor - Win32 Release"
# Name "NewEditor - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\ambient.cpp
# End Source File
# Begin Source File

SOURCE=.\BendDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\bnode.cpp
# End Source File
# Begin Source File

SOURCE=..\boa.cpp
# End Source File
# Begin Source File

SOURCE=.\CameraSlew.cpp
# End Source File
# Begin Source File

SOURCE=..\Editor\DallasFlagDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\Editor\DallasGenericPromptDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\Editor\DallasImportDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\Editor\DallasMainDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\Editor\DallasSoundDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\Editor\DallasStrmAudioDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\Editor\DallasTextureDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\Editor\DallasUserTypesDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\Editor\DallasUtilities.cpp
# End Source File
# Begin Source File

SOURCE=..\Editor\DallasVectorPromptDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\DoorwayDialogBar.cpp
# End Source File
# Begin Source File

SOURCE=..\editor\ebnode.cpp
# End Source File
# Begin Source File

SOURCE=.\EditLineDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\editor_lighting.cpp
# End Source File
# Begin Source File

SOURCE=.\editor_object_lighting.cpp
# End Source File
# Begin Source File

SOURCE=..\editor\edoors.cpp
# End Source File
# Begin Source File

SOURCE=..\editor\EPath.cpp
# End Source File
# Begin Source File

SOURCE=..\editor\Erooms.cpp
# End Source File
# Begin Source File

SOURCE=.\ExtrudeDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\FileNewDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\gamepath.cpp
# End Source File
# Begin Source File

SOURCE=.\globals.cpp
# End Source File
# Begin Source File

SOURCE=.\GoalDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\GrListBox.cpp
# End Source File
# Begin Source File

SOURCE=..\editor\Group.cpp
# End Source File
# Begin Source File

SOURCE=.\HogBrowser.cpp
# End Source File
# Begin Source File

SOURCE=..\editor\HRoom.cpp
# End Source File
# Begin Source File

SOURCE=..\editor\HTexture.cpp
# End Source File
# Begin Source File

SOURCE=.\LatheDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\LevelFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\LevelInfoDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\LightingDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\LightingProgress.cpp
# End Source File
# Begin Source File

SOURCE=..\lightmap_info.cpp
# End Source File
# Begin Source File

SOURCE=.\ListDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\loadlevel.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=..\matcen.cpp
# End Source File
# Begin Source File

SOURCE=.\MatcenDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\MissionHogConfigDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ned_Door.cpp
# End Source File
# Begin Source File

SOURCE=.\ned_DrawWorld.cpp
# End Source File
# Begin Source File

SOURCE=.\ned_GameTexture.cpp
# End Source File
# Begin Source File

SOURCE=.\ned_Geometry.cpp
# End Source File
# Begin Source File

SOURCE=.\ned_GrWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\ned_HFile.cpp
# End Source File
# Begin Source File

SOURCE=.\ned_LevelGoal.cpp
# End Source File
# Begin Source File

SOURCE=.\ned_LevelWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\ned_newstyle.cpp
# End Source File
# Begin Source File

SOURCE=.\ned_Object.cpp
# End Source File
# Begin Source File

SOURCE=.\ned_OrthoWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\ned_PathNode.cpp
# End Source File
# Begin Source File

SOURCE=.\ned_PerspWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\ned_polymodel.cpp
# End Source File
# Begin Source File

SOURCE=.\ned_Render.cpp
# End Source File
# Begin Source File

SOURCE=.\ned_Renderer.cpp
# End Source File
# Begin Source File

SOURCE=.\ned_RendOpenGL.cpp
# End Source File
# Begin Source File

SOURCE=.\ned_Sound.cpp
# End Source File
# Begin Source File

SOURCE=.\ned_TableRead.cpp
# End Source File
# Begin Source File

SOURCE=.\ned_Trigger.cpp
# End Source File
# Begin Source File

SOURCE=.\ned_Util.cpp
# End Source File
# Begin Source File

SOURCE=.\NewEditor.cpp
# End Source File
# Begin Source File

SOURCE=.\NewEditor.rc
# End Source File
# Begin Source File

SOURCE=.\object_lighting.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectDialogBar.cpp
# End Source File
# Begin Source File

SOURCE=..\editor\ObjectListCombo.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectPalette.cpp
# End Source File
# Begin Source File

SOURCE=.\PathDialogBar.cpp
# End Source File
# Begin Source File

SOURCE=..\postrender.cpp
# End Source File
# Begin Source File

SOURCE=.\ProgressDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\rad_cast.cpp
# End Source File
# Begin Source File

SOURCE=.\rad_init.cpp
# End Source File
# Begin Source File

SOURCE=.\RefFrameDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\room.cpp
# End Source File
# Begin Source File

SOURCE=.\RoomDialogBar.cpp
# End Source File
# Begin Source File

SOURCE=.\RoomFrm.cpp
# End Source File
# Begin Source File

SOURCE=..\editor\RoomListCombo.cpp
# End Source File
# Begin Source File

SOURCE=.\RoomProperties.cpp
# End Source File
# Begin Source File

SOURCE=..\editor\RoomUVs.cpp
# End Source File
# Begin Source File

SOURCE=.\ScriptCompiler.cpp
# End Source File
# Begin Source File

SOURCE=..\Editor\ScriptCompilerAPI.cpp
# End Source File
# Begin Source File

SOURCE=..\editor\selectedroom.cpp
# End Source File
# Begin Source File

SOURCE=..\editor\SelManager.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingsDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\ship.cpp
# End Source File
# Begin Source File

SOURCE=.\SoundDialogBar.cpp
# End Source File
# Begin Source File

SOURCE=..\editor\SoundListCombo.cpp
# End Source File
# Begin Source File

SOURCE=..\special_face.cpp
# End Source File
# Begin Source File

SOURCE=.\SplashScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# End Source File
# Begin Source File

SOURCE=.\TablefileManager.cpp
# End Source File
# Begin Source File

SOURCE=.\TableView.cpp
# End Source File
# Begin Source File

SOURCE=..\terrain.cpp
# End Source File
# Begin Source File

SOURCE=.\TerrainDialogBar.cpp
# End Source File
# Begin Source File

SOURCE=..\terrainrender.cpp
# End Source File
# Begin Source File

SOURCE=..\TerrainSearch.cpp
# End Source File
# Begin Source File

SOURCE=.\TexAlignDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\TextureDialogBar.cpp
# End Source File
# Begin Source File

SOURCE=.\TexturePalette.cpp
# End Source File
# Begin Source File

SOURCE=.\TipOfTheDay.cpp
# End Source File
# Begin Source File

SOURCE=.\TriggerDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\editor\TriggerListCombo.cpp
# End Source File
# Begin Source File

SOURCE=..\Vclip.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BendDialog.h
# End Source File
# Begin Source File

SOURCE=.\CameraSlew.h
# End Source File
# Begin Source File

SOURCE=..\editor\DallasFlagDlg.h
# End Source File
# Begin Source File

SOURCE=..\editor\DallasGenericPromptDlg.h
# End Source File
# Begin Source File

SOURCE=..\editor\DallasImportDlg.h
# End Source File
# Begin Source File

SOURCE=..\editor\DallasMainDlg.h
# End Source File
# Begin Source File

SOURCE=..\editor\DallasSoundDlg.h
# End Source File
# Begin Source File

SOURCE=..\editor\DallasStrmAudioDlg.h
# End Source File
# Begin Source File

SOURCE=..\editor\DallasTextureDlg.h
# End Source File
# Begin Source File

SOURCE=..\editor\DallasUserTypesDlg.h
# End Source File
# Begin Source File

SOURCE=..\editor\DallasUtilities.h
# End Source File
# Begin Source File

SOURCE=..\editor\DallasVectorPromptDialog.h
# End Source File
# Begin Source File

SOURCE=.\DoorwayDialogBar.h
# End Source File
# Begin Source File

SOURCE=.\EditLineDialog.h
# End Source File
# Begin Source File

SOURCE=.\editor_lighting.h
# End Source File
# Begin Source File

SOURCE=.\ExtrudeDialog.h
# End Source File
# Begin Source File

SOURCE=.\FileNewDialog.h
# End Source File
# Begin Source File

SOURCE=.\FolderDialog.h
# End Source File
# Begin Source File

SOURCE=.\globals.h
# End Source File
# Begin Source File

SOURCE=.\GoalDialog.h
# End Source File
# Begin Source File

SOURCE=.\GrListBox.h
# End Source File
# Begin Source File

SOURCE=.\HogBrowser.h
# End Source File
# Begin Source File

SOURCE=..\editor\HRoom.h
# End Source File
# Begin Source File

SOURCE=.\LatheDialog.h
# End Source File
# Begin Source File

SOURCE=.\LevelFrame.h
# End Source File
# Begin Source File

SOURCE=.\LevelInfoDialog.h
# End Source File
# Begin Source File

SOURCE=.\LightingDialog.h
# End Source File
# Begin Source File

SOURCE=.\LightingProgress.h
# End Source File
# Begin Source File

SOURCE=.\ListDialog.h
# End Source File
# Begin Source File

SOURCE=..\LoadLevel.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MatcenDialog.h
# End Source File
# Begin Source File

SOURCE=.\MissionHogConfigDlg.h
# End Source File
# Begin Source File

SOURCE=.\ned_Door.h
# End Source File
# Begin Source File

SOURCE=.\ned_DrawWorld.h
# End Source File
# Begin Source File

SOURCE=.\ned_GameTexture.h
# End Source File
# Begin Source File

SOURCE=.\ned_Geometry.h
# End Source File
# Begin Source File

SOURCE=.\ned_GLLoad.h
# End Source File
# Begin Source File

SOURCE=.\ned_GrWnd.h
# End Source File
# Begin Source File

SOURCE=.\ned_HFile.h
# End Source File
# Begin Source File

SOURCE=.\ned_LevelWnd.h
# End Source File
# Begin Source File

SOURCE=.\ned_Object.h
# End Source File
# Begin Source File

SOURCE=.\ned_OrthoWnd.h
# End Source File
# Begin Source File

SOURCE=.\ned_PathNode.h
# End Source File
# Begin Source File

SOURCE=.\ned_PerspWnd.h
# End Source File
# Begin Source File

SOURCE=.\ned_Rend.h
# End Source File
# Begin Source File

SOURCE=.\ned_RendOpenGL.h
# End Source File
# Begin Source File

SOURCE=.\ned_Sound.h
# End Source File
# Begin Source File

SOURCE=.\ned_TableFile.h
# End Source File
# Begin Source File

SOURCE=.\ned_Trigger.h
# End Source File
# Begin Source File

SOURCE=.\ned_Util.h
# End Source File
# Begin Source File

SOURCE=.\NewEditor.h
# End Source File
# Begin Source File

SOURCE=.\object_lighting.h
# End Source File
# Begin Source File

SOURCE=.\ObjectDialogBar.h
# End Source File
# Begin Source File

SOURCE=.\ObjectPalette.h
# End Source File
# Begin Source File

SOURCE=.\PathDialogBar.h
# End Source File
# Begin Source File

SOURCE=.\ProgressDialog.h
# End Source File
# Begin Source File

SOURCE=.\radiosity.h
# End Source File
# Begin Source File

SOURCE=.\RefFrameDialog.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RoomDialogBar.h
# End Source File
# Begin Source File

SOURCE=.\RoomFrm.h
# End Source File
# Begin Source File

SOURCE=.\RoomProperties.h
# End Source File
# Begin Source File

SOURCE=.\ScriptCompiler.h
# End Source File
# Begin Source File

SOURCE=..\editor\ScriptCompilerAPI.h
# End Source File
# Begin Source File

SOURCE=..\editor\selectedroom.h
# End Source File
# Begin Source File

SOURCE=..\editor\SelManager.h
# End Source File
# Begin Source File

SOURCE=.\SettingsDialog.h
# End Source File
# Begin Source File

SOURCE=.\SoundDialogBar.h
# End Source File
# Begin Source File

SOURCE=..\editor\SoundListCombo.h
# End Source File
# Begin Source File

SOURCE=.\SplashScreen.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TablefileManager.h
# End Source File
# Begin Source File

SOURCE=.\TableView.h
# End Source File
# Begin Source File

SOURCE=.\TerrainDialogBar.h
# End Source File
# Begin Source File

SOURCE=.\TexAlignDialog.h
# End Source File
# Begin Source File

SOURCE=.\TextureDialogBar.h
# End Source File
# Begin Source File

SOURCE=.\TexturePalette.h
# End Source File
# Begin Source File

SOURCE=.\TipOfTheDay.h
# End Source File
# Begin Source File

SOURCE=.\TriggerDialog.h
# End Source File
# Begin Source File

SOURCE=..\vclip.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp

!IF  "$(CFG)" == "NewEditor - Win32 Release"

!ELSEIF  "$(CFG)" == "NewEditor - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp

!IF  "$(CFG)" == "NewEditor - Win32 Release"

!ELSEIF  "$(CFG)" == "NewEditor - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp

!IF  "$(CFG)" == "NewEditor - Win32 Release"

!ELSEIF  "$(CFG)" == "NewEditor - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\bmp00004.bmp

!IF  "$(CFG)" == "NewEditor - Win32 Release"

!ELSEIF  "$(CFG)" == "NewEditor - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\bmp00005.bmp

!IF  "$(CFG)" == "NewEditor - Win32 Release"

!ELSEIF  "$(CFG)" == "NewEditor - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\bmp00006.bmp

!IF  "$(CFG)" == "NewEditor - Win32 Release"

!ELSEIF  "$(CFG)" == "NewEditor - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\D3Launch.ico
# End Source File
# Begin Source File

SOURCE=.\res\DallasTreeIcons.bmp
# End Source File
# Begin Source File

SOURCE=.\res\down.ico
# End Source File
# Begin Source File

SOURCE=.\res\edge_con.bmp

!IF  "$(CFG)" == "NewEditor - Win32 Release"

!ELSEIF  "$(CFG)" == "NewEditor - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\edge_con.ico
# End Source File
# Begin Source File

SOURCE=.\res\edge_exp.bmp

!IF  "$(CFG)" == "NewEditor - Win32 Release"

!ELSEIF  "$(CFG)" == "NewEditor - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\edge_exp.ico
# End Source File
# Begin Source File

SOURCE=.\res\face_con.bmp

!IF  "$(CFG)" == "NewEditor - Win32 Release"

!ELSEIF  "$(CFG)" == "NewEditor - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\face_con.ico
# End Source File
# Begin Source File

SOURCE=.\res\face_exp.bmp

!IF  "$(CFG)" == "NewEditor - Win32 Release"

!ELSEIF  "$(CFG)" == "NewEditor - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\face_exp.ico
# End Source File
# Begin Source File

SOURCE=.\res\face_pla.bmp

!IF  "$(CFG)" == "NewEditor - Win32 Release"

!ELSEIF  "$(CFG)" == "NewEditor - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\face_pla.ico
# End Source File
# Begin Source File

SOURCE=.\res\face_spl.bmp

!IF  "$(CFG)" == "NewEditor - Win32 Release"

!ELSEIF  "$(CFG)" == "NewEditor - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\face_spl.ico
# End Source File
# Begin Source File

SOURCE=.\res\face_tri.bmp

!IF  "$(CFG)" == "NewEditor - Win32 Release"

!ELSEIF  "$(CFG)" == "NewEditor - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\face_tri.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00003.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00004.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00005.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00006.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00007.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00008.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00009.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00010.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00011.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00012.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00013.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00014.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00015.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00016.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00017.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00018.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00019.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00020.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00021.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00022.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00023.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00024.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00025.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00026.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00027.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00028.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00029.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00030.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00031.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\left.ico
# End Source File
# Begin Source File

SOURCE=.\res\modify_b.bmp

!IF  "$(CFG)" == "NewEditor - Win32 Release"

!ELSEIF  "$(CFG)" == "NewEditor - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\modify_b.ico
# End Source File
# Begin Source File

SOURCE=.\res\modify_e.bmp

!IF  "$(CFG)" == "NewEditor - Win32 Release"

!ELSEIF  "$(CFG)" == "NewEditor - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\modify_e.ico
# End Source File
# Begin Source File

SOURCE=.\res\modify_l.bmp

!IF  "$(CFG)" == "NewEditor - Win32 Release"

!ELSEIF  "$(CFG)" == "NewEditor - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\modify_l.ico
# End Source File
# Begin Source File

SOURCE=.\res\modify_s.bmp

!IF  "$(CFG)" == "NewEditor - Win32 Release"

!ELSEIF  "$(CFG)" == "NewEditor - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\modify_s.ico
# End Source File
# Begin Source File

SOURCE=.\res\NewEditor.ico
# End Source File
# Begin Source File

SOURCE=.\res\NewEditor.rc2
# End Source File
# Begin Source File

SOURCE=.\res\right.ico
# End Source File
# Begin Source File

SOURCE=.\res\room_con.bmp

!IF  "$(CFG)" == "NewEditor - Win32 Release"

!ELSEIF  "$(CFG)" == "NewEditor - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\room_con.ico
# End Source File
# Begin Source File

SOURCE=.\res\room_exp.bmp

!IF  "$(CFG)" == "NewEditor - Win32 Release"

!ELSEIF  "$(CFG)" == "NewEditor - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\rotatele.ico
# End Source File
# Begin Source File

SOURCE=.\res\rotateri.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\up.ico
# End Source File
# Begin Source File

SOURCE=.\res\vertex_r.bmp

!IF  "$(CFG)" == "NewEditor - Win32 Release"

!ELSEIF  "$(CFG)" == "NewEditor - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\vertex_s.bmp

!IF  "$(CFG)" == "NewEditor - Win32 Release"

!ELSEIF  "$(CFG)" == "NewEditor - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\vertex_s.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\blah.txt
# End Source File
# End Target
# End Project
