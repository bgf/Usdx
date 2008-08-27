unit URingBuffer;

interface

{$IFDEF FPC}
  {$MODE Delphi}
{$ENDIF}

{$I switches.inc}

uses
  SysUtils;

type
  TRingBuffer = class
    private
      RingBuffer: PChar;
      BufferCount: integer;
      BufferSize: integer;
      WritePos: integer;
      ReadPos: integer;
    public
      constructor Create(Size: integer);
      destructor Destroy; override;
      function Read(Buffer: PChar; Count: integer): integer;
      function Write(Buffer: PChar; Count: integer): integer;
      procedure Flush();
  end;

implementation

uses
  Math;

constructor TRingBuffer.Create(Size: integer);
begin
  BufferSize := Size;

  GetMem(RingBuffer, Size);
  if (RingBuffer = nil) then
    raise Exception.Create('No memory');
end;

destructor TRingBuffer.Destroy;
begin
  FreeMem(RingBuffer);
end;

function TRingBuffer.Read(Buffer: PChar; Count: integer): integer;
var
  PartCount: integer;
begin
  // adjust output count
  if (Count > BufferCount) then
  begin
    //DebugWriteln('Read too much: ' + inttostr(count) +',count:'+ inttostr(BufferCount) + '/size:' + inttostr(BufferSize));
    Count := BufferCount;
  end;

  // check if there is something to do
  if (Count <= 0) then
  begin
    Result := Count;
    Exit;
  end;

  // copy data to output buffer

  // first step: copy from the area between the read-position and the end of the buffer
  PartCount := Min(Count, BufferSize - ReadPos);
  Move(RingBuffer[ReadPos], Buffer[0], PartCount);

  // second step: if we need more data, copy from the beginning of the buffer
  if (PartCount < Count) then
    Move(RingBuffer[0], Buffer[0], Count-PartCount);

  // mark the copied part of the buffer as free
  BufferCount := BufferCount - Count;
  ReadPos := (ReadPos + Count) mod BufferSize;

  Result := Count;
end;

function TRingBuffer.Write(Buffer: PChar; Count: integer): integer;
var
  PartCount: integer;
begin
  // check for a reasonable request
  if (Count <= 0) then
  begin
    Result := Count;
    Exit;
  end;

  // skip input data if the input buffer is bigger than the ring-buffer
  if (Count > BufferSize) then
  begin
    //DebugWriteln('Write skip data:' + inttostr(count) +',count:'+ inttostr(BufferCount) + '/size:' + inttostr(BufferSize));
    Buffer := @Buffer[Count - BufferSize];
    Count := BufferSize;
  end;

  // first step: copy to the area between the write-position and the end of the buffer
  PartCount := Min(Count, BufferSize - WritePos);
  Move(Buffer[0], RingBuffer[WritePos], PartCount);

  // second step: copy data to front of buffer
  if (PartCount < Count) then
    Move(Buffer[PartCount], RingBuffer[0], Count-PartCount);

  // update info
  BufferCount := Min(BufferCount + Count, BufferSize);
  WritePos := (WritePos + Count) mod BufferSize;
  // if the buffer is full, we have to reposition the read-position
  if (BufferCount = BufferSize) then
    ReadPos := WritePos;

  Result := Count;
end;

procedure TRingBuffer.Flush();
begin
  ReadPos := 0;
  WritePos := 0;
  BufferCount := 0;
end;

end.