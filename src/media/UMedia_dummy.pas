unit UMedia_dummy;

interface

{$IFDEF FPC}
  {$MODE Delphi}
{$ENDIF}

{$I switches.inc}

implementation

uses
     SysUtils,
     math,
     UMusic;

type
    TMedia_dummy = class( TInterfacedObject, IVideoPlayback, IVideoVisualization, IAudioPlayback, IAudioInput )
    private
      DummyOutputDeviceList: TAudioOutputDeviceList;
    public
      constructor Create();
      function  GetName: string;

      function Init(): boolean;
      function Finalize(): boolean;

      function  Open(const aFileName : string): boolean; // true if succeed
      procedure Close;

      procedure Play;
      procedure Pause;
      procedure Stop;

      procedure SetPosition(Time: real);
      function  GetPosition: real;

      procedure SetSyncSource(SyncSource: TSyncSource);

      procedure GetFrame(Time: Extended);
      procedure DrawGL(Screen: integer);

      // IAudioInput
      function InitializeRecord: boolean;
      function FinalizeRecord: boolean;
      procedure CaptureStart;
      procedure CaptureStop;
      procedure GetFFTData(var data: TFFTData);
      function GetPCMData(var data: TPCMData): Cardinal;

      // IAudioPlayback
      function InitializePlayback: boolean;
      function FinalizePlayback: boolean;

      function GetOutputDeviceList(): TAudioOutputDeviceList;
      procedure FadeIn(Time: real; TargetVolume: single);
      procedure SetAppVolume(Volume: single);
      procedure SetVolume(Volume: single);
      procedure SetLoop(Enabled: boolean);
      procedure Rewind;

      function Finished: boolean;
      function Length: real;

      function OpenSound(const Filename: string): TAudioPlaybackStream;
      procedure CloseSound(var PlaybackStream: TAudioPlaybackStream);
      procedure PlaySound(stream: TAudioPlaybackStream);
      procedure StopSound(stream: TAudioPlaybackStream);

      function CreateVoiceStream(Channel: integer; FormatInfo: TAudioFormatInfo): TAudioVoiceStream;
      procedure CloseVoiceStream(var VoiceStream: TAudioVoiceStream);
    end;

function  TMedia_dummy.GetName: string;
begin
  Result := 'dummy';
end;

procedure TMedia_dummy.GetFrame(Time: Extended);
begin
end;

procedure TMedia_dummy.DrawGL(Screen: integer);
begin
end;

constructor TMedia_dummy.Create();
begin
  inherited;
end;

function TMedia_dummy.Init(): boolean;
begin
  Result := true;
end;

function TMedia_dummy.Finalize(): boolean;
begin
  Result := true;
end;

function TMedia_dummy.Open(const aFileName : string): boolean; // true if succeed
begin
  Result := false;
end;

procedure TMedia_dummy.Close;
begin
end;

procedure TMedia_dummy.Play;
begin
end;

procedure TMedia_dummy.Pause;
begin
end;

procedure TMedia_dummy.Stop;
begin
end;

procedure TMedia_dummy.SetPosition(Time: real);
begin
end;

function  TMedia_dummy.GetPosition: real;
begin
  Result := 0;
end;

procedure TMedia_dummy.SetSyncSource(SyncSource: TSyncSource);
begin
end;

// IAudioInput
function TMedia_dummy.InitializeRecord: boolean;
begin
  Result := true;
end;

function TMedia_dummy.FinalizeRecord: boolean;
begin
  Result := true;
end;

procedure TMedia_dummy.CaptureStart;
begin
end;

procedure TMedia_dummy.CaptureStop;
begin
end;

procedure TMedia_dummy.GetFFTData(var data: TFFTData);
begin
end;

function  TMedia_dummy.GetPCMData(var data: TPCMData): Cardinal;
begin
  Result := 0;
end;

// IAudioPlayback
function TMedia_dummy.InitializePlayback: boolean;
begin
  SetLength(DummyOutputDeviceList, 1);
  DummyOutputDeviceList[0] := TAudioOutputDevice.Create();
  DummyOutputDeviceList[0].Name := '[Dummy Device]';
  Result := true;
end;

function TMedia_dummy.FinalizePlayback: boolean;
begin
  Result := true;
end;

function TMedia_dummy.GetOutputDeviceList(): TAudioOutputDeviceList;
begin
  Result := DummyOutputDeviceList;
end;

procedure TMedia_dummy.SetAppVolume(Volume: single);
begin
end;

procedure TMedia_dummy.SetVolume(Volume: single);
begin
end;

procedure TMedia_dummy.SetLoop(Enabled: boolean);
begin
end;

procedure TMedia_dummy.FadeIn(Time: real; TargetVolume: single);
begin
end;

procedure TMedia_dummy.Rewind;
begin
end;

function TMedia_dummy.Finished: boolean;
begin
  Result := false;
end;

function TMedia_dummy.Length: real;
begin
  Result := 60;
end;

function TMedia_dummy.OpenSound(const Filename: string): TAudioPlaybackStream;
begin
 Result := nil;
end;

procedure TMedia_dummy.CloseSound(var PlaybackStream: TAudioPlaybackStream);
begin
end;

procedure TMedia_dummy.PlaySound(stream: TAudioPlaybackStream);
begin
end;

procedure TMedia_dummy.StopSound(stream: TAudioPlaybackStream);
begin
end;

function TMedia_dummy.CreateVoiceStream(Channel: integer; FormatInfo: TAudioFormatInfo): TAudioVoiceStream;
begin
  Result := nil;
end;

procedure TMedia_dummy.CloseVoiceStream(var VoiceStream: TAudioVoiceStream);
begin
end;

initialization
  MediaManager.Add(TMedia_dummy.Create);

end.