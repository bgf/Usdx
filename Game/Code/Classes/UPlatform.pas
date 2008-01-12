unit UPlatform;

// Comment by Eddie:
// This unit defines an interface for platform specific utility functions.
// The Interface is implemented in separate files for each platform:
// UPlatformWindows, UPlatformLinux and UPlatformWindows.

interface

{$IFDEF FPC}
  {$MODE Delphi}
{$ENDIF}

{$I switches.inc}

uses Classes;

type
  TDirectoryEntry = Record
                      Name        : WideString;
                      IsDirectory : Boolean;
                      IsFile      : Boolean;
                    end;
 
  TDirectoryEntryArray = Array of TDirectoryEntry;
	
  IPlatform = Interface
  ['{63A5EBC3-3F4D-4F23-8DFB-B5165FCA23DF}']
    Function  DirectoryFindFiles(Dir, Filter : WideString; ReturnAllSubDirs : Boolean) : TDirectoryEntryArray;
    function  TerminateIfAlreadyRunning(var WndTitle : String) : Boolean;
    function  FindSongFile(Dir, Mask: widestring): widestring;
    procedure halt;
    function  GetLogPath        : WideString;
    function  GetGameSharedPath : WideString;
    function  GetGameUserPath   : WideString;
  end;

  function Platform : IPlatform;

implementation

uses
  SysUtils,
  {$IFDEF MSWINDOWS}
  UPlatformWindows;
  {$ENDIF}
  {$IFDEF LINUX}
  UPlatformLinux;
  {$ENDIF}
  {$IFDEF DARWIN}
  UPlatformMacOSX;
  {$ENDIF}


// I have modified it to use the Platform_singleton in this location ( in the implementaiton )
// so that this variable can NOT be overwritten from anywhere else in the application.
// the accessor function platform, emulates all previous calls to work the same way.  
var
  Platform_singleton : IPlatform;

function Platform : IPlatform;
begin
  result := Platform_singleton;
end;


initialization
  {$IFDEF MSWINDOWS}
    Platform_singleton := TPlatformWindows.Create;
  {$ENDIF}
  {$IFDEF LINUX}
    Platform_singleton := TPlatformLinux.Create;
  {$ENDIF}
  {$IFDEF DARWIN}
    Platform_singleton := TPlatformMacOSX.Create;
  {$ENDIF}

finalization
    Platform_singleton := nil;
end.
