!include "Library.nsh"
!include 'LogicLib.nsh'
!include "PathManip.nsh"

!define NUS_VERSION 0.3.0
!define SUB_VERSION beta-1
!define BUILD_DIR c:\lib\nus-${NUS_VERSION}

VIProductVersion "${NUS_VERSION}.0"
VIAddVersionKey "ProductName" "NUS Installer"
VIAddVersionKey "Comments" "This is the NUS installer. Double click to run it"
VIAddVersionKey "CompanyName" "NUS Project"
VIAddVersionKey "LegalTrademarks" "NUS Project"
VIAddVersionKey "LegalCopyright" "© NUS Project"
VIAddVersionKey "FileDescription" "NUS Installer"
VIAddVersionKey "FileVersion" "0.1.0"


Name "NUS - Nemesis Utilities System"

; The file to write
OutFile nus-setup-${NUS_VERSION}-${SUB_VERSION}.exe

SetCompressor /SOLID lzma

InstType "User"
InstType "Developer"

; The default installation directory
InstallDir C:\libraries\nus-${NUS_VERSION}

; Registry key to check for directory (so if you install again, it will 
; overwrite the old one automatically)
InstallDirRegKey HKLM "Software\NUS-${VERSION}" "Install_Dir"

;--------------------------------
PageEx License
	LicenseText "NUS License"
	LicenseData ..\COPYING
	LicenseForceSelection radiobuttons "I accept" "I decline"
PageExEnd
Page components
Page directory
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

;--------------------------------

; The stuff to install
Section "Runtime (required)" SecRuntime
	SectionIn RO

	; Set output path to the installation directory.
	SetOutPath $INSTDIR\lib
	
	!insertmacro InstallLib DLL 1 NOREBOOT_NOTPROTECTED ${BUILD_DIR}\lib\nbase-${NUS_VERSION}.dll $INSTDIR\lib\nbase-${NUS_VERSION}.dll $INSTDIR
	!insertmacro InstallLib DLL 1 NOREBOOT_NOTPROTECTED ${BUILD_DIR}\lib\nnetwork-${NUS_VERSION}.dll $INSTDIR\lib\nnetwork-${NUS_VERSION}.dll $INSTDIR
	!insertmacro InstallLib DLL 1 NOREBOOT_NOTPROTECTED ${BUILD_DIR}\lib\nxml-${NUS_VERSION}.dll $INSTDIR\lib\nxml-${NUS_VERSION}.dll $INSTDIR
	!insertmacro InstallLib DLL 1 NOREBOOT_NOTPROTECTED ${BUILD_DIR}\lib\nsecurity-${NUS_VERSION}.dll $INSTDIR\lib\nsecurity-${NUS_VERSION}.dll $INSTDIR
	!insertmacro InstallLib DLL 1 NOREBOOT_NOTPROTECTED ${BUILD_DIR}\lib\ndbal-${NUS_VERSION}.dll $INSTDIR\lib\ndbal-${NUS_VERSION}.dll $INSTDIR
	

	!insertmacro InstallLib DLL 1 NOREBOOT_NOTPROTECTED ${BUILD_DIR}\lib\libxml2.dll $INSTDIR\lib\libxml2.dll $INSTDIR
	!insertmacro InstallLib DLL 1 NOREBOOT_NOTPROTECTED ${BUILD_DIR}\lib\iconv.dll $INSTDIR\lib\iconv.dll $INSTDIR
	!insertmacro InstallLib DLL 1 NOREBOOT_NOTPROTECTED ${BUILD_DIR}\lib\zlib1.dll $INSTDIR\lib\zlib1.dll $INSTDIR
	!insertmacro InstallLib DLL 1 NOREBOOT_NOTPROTECTED ${BUILD_DIR}\lib\libeay32.dll $INSTDIR\lib\libeay32.dll $INSTDIR
	!insertmacro InstallLib DLL 1 NOREBOOT_NOTPROTECTED ${BUILD_DIR}\lib\ssleay32.dll $INSTDIR\lib\ssleay32.dll $INSTDIR

	; Write the installation path into the registry
	WriteRegStr HKLM Software\NUS-${NUS_VERSION} "Install_Dir" "$INSTDIR"
  
	; Write the uninstall keys for Windows
	WriteRegStr HKLM Software\Microsoft\Windows\CurrentVersion\Uninstall\NUS-${NUS_VERSION} "DisplayName" "NUS - Nemesis Utilities System ${NUS_VERSION}"
	WriteRegStr HKLM Software\Microsoft\Windows\CurrentVersion\Uninstall\NUS-${NUS_VERSION} "UninstallString" '"$INSTDIR\uninstall.exe"'
	WriteRegDWORD HKLM Software\Microsoft\Windows\CurrentVersion\Uninstall\NUS-${NUS_VERSION} "NoModify" 1
	WriteRegDWORD HKLM Software\Microsoft\Windows\CurrentVersion\Uninstall\NUS-${NUS_VERSION} "NoRepair" 1
	WriteUninstaller "uninstall.exe"

	Push $INSTDIR\lib
	Call AddToPath
SectionEnd


Section "Development files" SecDevel
	SetOutPath $INSTDIR\bin
	File ${BUILD_DIR}\bin\*.*
	
	Push $INSTDIR\bin
	Call AddToPath
	
	SetOutPath $INSTDIR\include
	File /r ${BUILD_DIR}\include\*.*

	SetOutPath $INSTDIR\lib
	File ${BUILD_DIR}\lib\*.lib
	
	SetOutPath $INSTDIR\src
	File /r ${BUILD_DIR}\src\*.*
SectionEnd

Section "CMake Modules"
	; This is pretty dumb IMHO, but it  works
	ReadRegStr $0 HKLM "SOFTWARE\Kitware\CMake 2.4.8" ""
	${If} $0 == ""
		ReadRegStr $0 HKLM "SOFTWARE\Kitware\CMake 2.4.7" ""
		${If} $0 == ""
			ReadRegStr $0 HKLM "SOFTWARE\Kitware\CMake 2.4.6" ""
			${If} $0 == ""
				ReadRegStr $0 HKLM "SOFTWARE\Kitware\CMake 2.4.5" ""
				${If} $0 == ""
					ReadRegStr $0 HKLM "SOFTWARE\Kitware\CMake 2.4.4" ""
					${If} $0 == ""
						ReadRegStr $0 HKLM "SOFTWARE\Kitware\CMake 2.4.3" ""
						${If} $0 == ""
							ReadRegStr $0 HKLM "SOFTWARE\Kitware\CMake 2.4.2" ""
							${If} $0 == ""
								ReadRegStr $0 HKLM "SOFTWARE\Kitware\CMake 2.4.1" ""
								${If} $0 == ""
									MessageBox MB_OK "CMake was not found, therefore the modules were not installed"
									return
								${EndIf}
							${EndIf}
						${EndIf}
					${EndIf}
				${EndIf}
			${EndIf}
		${EndIf}
	${EndIf}
	
	SetOutPath $0\share\cmake-2.4\Modules
	File /r ${BUILD_DIR}\share\nus\${NUS_VERSION}\cmake_modules\*.*
SectionEnd


Section "Start Menu Shortcuts"
	CreateDirectory "$SMPROGRAMS\NUS Library"
	CreateShortCut "$SMPROGRAMS\NUS Library\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
	CreateShortCut "$SMPROGRAMS\NUS Library\Home Page.lnk" "http://dev.angusyoung.org"
	CreateShortCut "$SMPROGRAMS\NUS Library\API Documentation.lnk" "http://dev.angusyoung.org/docs/${NUS_VERSION}/api/"
SectionEnd



Section "Uninstall"
	; Remove registry keys
	DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\NUS-${NUS_VERSION}"
	DeleteRegKey HKLM SOFTWARE\NUS-${NUS_VERSION}
  
	Delete "$INSTDIR\bin\*.*"
	Delete "$INSTDIR\lib\*.*"
	
	; Remove directories used
	RMDir /r /REBOOTOK "$INSTDIR\bin"
	RMDir /r /REBOOTOK "$INSTDIR\lib"
	RMDir /r /REBOOTOK "$INSTDIR\include"
	RMDir /r /REBOOTOK "$INSTDIR\share"
	RMDir /r /REBOOTOK "$INSTDIR\src"
	Delete $INSTDIR\uninstall.exe
	RMDir "$INSTDIR"

	Push $INSTDIR\bin	
	Call un.RemoveFromPath	
	
	Push $INSTDIR\lib
	Call un.RemoveFromPath	
SectionEnd


Function .onInit
	SectionSetInstTypes ${SecRuntime} 7
	SectionSetInstTypes ${SecDevel} 6
FunctionEnd
