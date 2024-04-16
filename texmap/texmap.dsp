# Microsoft Developer Studio Project File - Name="texmap" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=texmap - Win32 GameGauge Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "texmap.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "texmap.mak" CFG="texmap - Win32 GameGauge Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "texmap - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "texmap - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/descent3/main", KFAAAAAA"
# PROP Scc_LocalPath ".."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "texmap - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir "."
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "./Debug"
# PROP Intermediate_Dir "./Debug"
# PROP Target_Dir "."
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /G5 /MDd /W3 /GX /ZI /Od /I "..\lib" /I "..\lib\win" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "MONO" /YX /FD /c
# SUBTRACT CPP /X /Fr
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "texmap - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "texmap__"
# PROP BASE Intermediate_Dir "texmap__"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "./Release"
# PROP Intermediate_Dir "./Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MDd /W3 /GX /Z7 /Od /I "..\lib" /I "..\lib\win" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# SUBTRACT BASE CPP /X /Fr
# ADD CPP /nologo /G5 /MT /W3 /GX /O2 /I "..\lib" /I "..\lib\win" /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /D "RELEASE" /YX /FD /c
# SUBTRACT CPP /X /Fr
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "texmap - Win32 Debug"
# Name "texmap - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\texture.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\drawquad.h
# End Source File
# Begin Source File

SOURCE=.\drawtex.h
# End Source File
# Begin Source File

SOURCE=.\flat_poly.h
# End Source File
# Begin Source File

SOURCE=.\leftedge.h
# End Source File
# Begin Source File

SOURCE=.\lmap_gouraud.h
# End Source File
# Begin Source File

SOURCE=.\quadleftedge.h
# End Source File
# Begin Source File

SOURCE=.\quadrightedge.h
# End Source File
# Begin Source File

SOURCE=.\rightedg.h
# End Source File
# Begin Source File

SOURCE=..\lib\texture.h
# End Source File
# Begin Source File

SOURCE=.\tmap_4444.h
# End Source File
# Begin Source File

SOURCE=.\tmap_alpha16.h
# End Source File
# Begin Source File

SOURCE=.\tmap_flat.h
# End Source File
# Begin Source File

SOURCE=.\tmap_flat16.h
# End Source File
# Begin Source File

SOURCE=.\tmap_lca.h
# End Source File
# Begin Source File

SOURCE=.\tmap_ll16.h
# End Source File
# Begin Source File

SOURCE=.\tmap_ll16a.h
# End Source File
# Begin Source File

SOURCE=.\tmap_lla.h
# End Source File
# Begin Source File

SOURCE=.\tmap_llta.h
# End Source File
# Begin Source File

SOURCE=.\tmap_mac_lca.h
# End Source File
# Begin Source File

SOURCE=.\tmap_mac_lla.h
# End Source File
# Begin Source File

SOURCE=.\tmap_mac_llta.h
# End Source File
# Begin Source File

SOURCE=.\tmap_mac_pla.h
# End Source File
# Begin Source File

SOURCE=.\tmap_mac_plta.h
# End Source File
# Begin Source File

SOURCE=.\tmap_mac_tri_flata.h
# End Source File
# Begin Source File

SOURCE=.\tmap_mac_tri_lla.h
# End Source File
# Begin Source File

SOURCE=.\tmap_pc.h
# End Source File
# Begin Source File

SOURCE=.\tmap_perflat.h
# End Source File
# Begin Source File

SOURCE=.\tmap_perflat16.h
# End Source File
# Begin Source File

SOURCE=.\tmap_pl16.h
# End Source File
# Begin Source File

SOURCE=.\tmap_pl16a.h
# End Source File
# Begin Source File

SOURCE=.\tmap_pla.h
# End Source File
# Begin Source File

SOURCE=.\tmap_plta.h
# End Source File
# Begin Source File

SOURCE=.\tmap_tri_flata.h
# End Source File
# Begin Source File

SOURCE=.\tmap_tri_lla.h
# End Source File
# Begin Source File

SOURCE=.\tmap_zbuf16.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
