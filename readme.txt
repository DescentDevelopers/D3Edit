/*
 THE COMPUTER CODE CONTAINED HEREIN IS THE SOLE PROPERTY OF OUTRAGE
 ENTERTAINMENT, INC. ("OUTRAGE").  OUTRAGE, IN DISTRIBUTING THE CODE TO
 END-USERS, AND SUBJECT TO ALL OF THE TERMS AND CONDITIONS HEREIN, GRANTS A
 ROYALTY-FREE, PERPETUAL LICENSE TO SUCH END-USERS FOR USE BY SUCH END-USERS
 IN USING, DISPLAYING,  AND CREATING DERIVATIVE WORKS THEREOF, SO LONG AS
 SUCH USE, DISPLAY OR CREATION IS FOR NON-COMMERCIAL, ROYALTY OR REVENUE
 FREE PURPOSES.  IN NO EVENT SHALL THE END-USER USE THE COMPUTER CODE
 CONTAINED HEREIN FOR REVENUE-BEARING PURPOSES.  THE END-USER UNDERSTANDS
 AND AGREES TO THE TERMS HEREIN AND ACCEPTS THE SAME BY USE OF THIS FILE.
 COPYRIGHT 1996-2000 OUTRAGE ENTERTAINMENT, INC.  ALL RIGHTS RESERVED.
 */

Here it is! Version 1.1 of the D3Edit Source code. Check out the webpage at http://d3edit.warpcore.org. If you have any questions, email us at d3edit@warpcore.org.

* D3Edit has been developed using Microsoft Visual C++ 6.0, and MFC. The
  D3edit executable runs under WIN32.
* A lot of the code included here is actually part of the D3 source. 
  Especially the libraries. You might notice a lot of functions that 
  never appear to be used in D3 Edit. * It's true, they aren't used, but
  it would have taken a lot of time to remove the stuff we didn't need.
* If you notice a bunch of source files that have no blank lines between 
  functions, and are hard to read, well... blame me (Kevin). I was 
  merging the MAC source code into our Source Control system at Outrage, 
  and I wrote a little app to convert the CR/LF from MAC to PC. My 
  program had a bug I didn't notice until I had 'converted' hundreds of 
  files and checked them in. :(
* The coding standards that were in place when this code was originally 
  written weren't very strongly adhered to, so you may notice some 
  inconsistencies within the code. If you are making modifications to the 
  source, all I ask is that you make a reasonable effort to adhere to the 
  same format as was used in the code you are making modifications to. 
  Mostly we followed the coding style that Microsoft uses in MFC.
* You will need the DirectX headers and libraries to compile D3edit. We 
  cannot include them because of distribution restrictions. You can find 
  and download the DirectX SDK from http://msdn.microsoft.com/directx/. 
  As of the time of this writing, you can download only the library and 
  header files from: 
  http://download.microsoft.com/download/win98SE/DXSDK/7.0/W9X/EN-US/dx7libhdr.exe

* Once you download the library and header files, place them in the 
  d3edit\lib\win\directx directory.
* Once you have opened up the project in MSVC, you will need to set 
  "NewEditor" as the active project. You can choose a debug or release 
  build as well.
* We are using CVS version control software to track changes. We have 
  allowed anonymous read-only access to the repository. 
* If you feel you have something to contribute to the project and would 
  like read/write access, email d3edit@warpcore.org. If we don't know 
  you, we may want to see some examples of the changes you would like to 
  make before we grant access. 
* More information on CVS can be found at http://www.sourcegear.com/CVS/support.
* To get the latest source code via CVS, go into the directory where you 
  want the d3edit source, and type the following:

cvs -d :pserver:anonymous@warpcore.org:/home/d3edit/cvsroot login

When prompted for a password, enter "anonymous".

cvs -d :pserver:anonymous@warpcore.org:/home/d3edit/cvsroot co d3edit

CVS will then download the latest version of the source into your directory.