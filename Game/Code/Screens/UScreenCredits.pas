unit UScreenCredits;

interface

uses
  UMenu, SDL, UDisplay, UTexture, gl, UMusic, UFiles, SysUtils, UThemes, UGraphicClasses;

type
  TCreditsStages=(InitialDelay,Intro,MainPart,Outro);

  TScreenCredits = class(TMenu)
    public

      Credits_X:        Real;
      Credits_Time:     Cardinal;
      Credits_Alpha:    Cardinal;
      CTime: Cardinal;
      CTime_hold:       Cardinal;
      ESC_Alpha:        Integer;

      credits_entry_tex:          TTexture;
      credits_entry_dx_tex:       TTexture;
      credits_bg_tex:             TTexture;
      credits_bg_ovl:             TTexture;
//      credits_bg_logo: TTexture;
      credits_bg_scrollbox_left:  TTexture;
      credits_blindy:             TTexture;
      credits_canni:              TTexture;
      credits_ggkfc:              TTexture;
      credits_jaybinks:           TTexture;
      credits_linnex:             TTexture;
      credits_mog:                TTexture;
      credits_omgdutch:           TTexture;
      credits_skillmaster:        TTexture;
      credits_whiteshark:         TTexture;
      credits_brunzel:            TTexture;
      intro_layer01: TTexture;
      intro_layer02: TTexture;
      intro_layer03: TTexture;
      intro_layer04: TTexture;
      intro_layer05: TTexture;
      intro_layer06: TTexture;
      intro_layer07: TTexture;
      intro_layer08: TTexture;
      intro_layer09: TTexture;
      outro_bg:      TTexture;
      outro_esc:     TTexture;
      outro_exd:     TTexture;

      deluxe_slidein: cardinal;

      CurrentScrollText: String;
      NextScrollUpdate:  Real;
      EndofLastScrollingPart: Cardinal;
      CurrentScrollStart, CurrentScrollEnd: Integer;

      CRDTS_Stage: TCreditsStages;

      Fadeout:      boolean;
      constructor Create; override;
      function ParseInput(PressedKey: Cardinal; ScanCode: byte; PressedDown: Boolean): Boolean; override;
      function Draw: boolean; override;
      procedure onShow; override;
      procedure onHide; override;
      procedure DrawCredits;
      procedure Draw_FunkyText;
   end;

const
  Funky_Text: AnsiString =
    'Massive thanks to all the people who have made this possible: Corvus5, for the '+
    'original program; the USDX team, for creating this deluxe version; igel457 for '+
    'developing acinerella; the translators: Thursday, UltraClaudio79 and Bruut; the '+
    'beta-testers: b4St1@fuN, bohning, Thursday and many of you who have been so '+
    'active on the German forum: ultra-star.de. Additional thanks to MezzoX, merc, gpm, '+
    'BlindGuard and MasterPhW for your contributions and to our song makers '+
    'throughout the world - without the music, none of this would be possible.';
    //I hope to see the improvements in this mod implemented into the USDX version someday :)

  (* old one:                                                                                                              |
  'A small step in version number, a huge step for the community - USDX works '+
  'with any video format now. Thanks and greetings fly out to Mota '+
  '(we miss you!), Skar (additional skins), Atlassian.com, Zanadoo.com and '+
  'WhirlWind-Records.com. Massive thanks to the translators: Jonaspaulo, '+
  'Jacobo, Bres, W0nderboy, Dadone - and our betatesters: Theril, Tyris, '+
  'Murmeltier and Lemon. Greetings to Tronic from NuubSing (you guys rule!) and Corvus5.';
  *)

  Timings: array[0..22] of Cardinal=(
     20,   //  0 Delay vor Start

    149,   //  1 Ende erster Intro Zoom
    155,   //  2 Start 2. Action im Intro
    170,   //  3 Ende Separation im Intro
    271,   //  4 Anfang Zoomout im Intro
      0,   //  5 unused
    261,   //  6 Start fade-to-white im Intro

    271,   //  7 Start Main Part
    280,   //  8 Start On-Beat-Sternchen Main Part

    351,   //  9 Start blindy
    801,   // 10 Start canni
   1026,   // 11 Start ggkfc
   1251,   // 12 Start jaybinks
   1476,   // 13 Start linnex
   1701,   // 14 Start mog
   2151,   // 15 Start omgdutch
   2376,   // 16 Start SkillMaster
   2601,   // 17 Start WhiteShark
   2826,   // 18 Ende Whiteshark
   3096,   // 19 Start FadeOut Mainscreen
   3450,   // 20 Ende Credits Tune (3366)
     60,
    576);  // 22 start brunzel

implementation

uses Dialogs,Windows, UGraphic, UMain, UIni, USongs, Textgl, opengl, ULanguage, Math;

function TScreenCredits.ParseInput(PressedKey: Cardinal; ScanCode: byte; PressedDown: Boolean): Boolean;
begin
  Result := true;
  If (PressedDown) Then
  begin // Key Down
    case PressedKey of
      SDLK_ESCAPE,
      SDLK_BACKSPACE :
        begin
          FadeTo(@ScreenMain);
          Music.PlayBack;
        end;
{       SDLK_SPACE:
         begin
           setlength(CTime_hold,length(CTime_hold)+1);
           CTime_hold[high(CTime_hold)]:=CTime;
         end;
}
     end;//esac
    end; //fi
end;

constructor TScreenCredits.Create;
begin
  inherited Create;
  credits_bg_tex            := Texture.LoadTexture(true, 'CRDTS_BG', 'PNG', 'Plain', 0);
  credits_bg_ovl            := Texture.LoadTexture(true, 'CRDTS_OVL', 'PNG', 'Transparent', 0);

  credits_blindy      := Texture.LoadTexture(true, 'CRDTS_blindy',     'PNG', 'Font Black', 0);
  credits_canni       := Texture.LoadTexture(true, 'CRDTS_canni',      'PNG', 'Font Black', 0);
  SDL_Delay(1);
  credits_ggkfc       := Texture.LoadTexture(true, 'CRDTS_ggkfc',      'PNG', 'Font Black', 0);
  credits_jaybinks    := Texture.LoadTexture(true, 'CRDTS_jaybinks',   'PNG', 'Font Black', 0);
  credits_linnex      := Texture.LoadTexture(true, 'CRDTS_linnex',     'PNG', 'Font Black', 0);
  credits_mog         := Texture.LoadTexture(true, 'CRDTS_mog',        'PNG', 'Font Black', 0);
  SDL_Delay(1);
  credits_omgdutch    := Texture.LoadTexture(true, 'CRDTS_omgdutch',   'PNG', 'Font Black', 0);
  credits_skillmaster := Texture.LoadTexture(true, 'CRDTS_skillmaster','PNG', 'Font Black', 0);
  credits_whiteshark  := Texture.LoadTexture(true, 'CRDTS_whiteshark', 'PNG', 'Font Black', 0);
  credits_brunzel     := Texture.LoadTexture(true, 'CRDTS_brunzel', 'PNG', 'Font Black', 0);

  SDL_Delay(1);
  intro_layer01 := Texture.LoadTexture(true, 'INTRO_L01', 'PNG', 'Transparent', 0);
  intro_layer02 := Texture.LoadTexture(true, 'INTRO_L02', 'PNG', 'Transparent', 0);
  intro_layer03 := Texture.LoadTexture(true, 'INTRO_L03', 'PNG', 'Transparent', 0);
  intro_layer04 := Texture.LoadTexture(true, 'INTRO_L04', 'PNG', 'Transparent', 0);
  SDL_Delay(1);
  intro_layer05 := Texture.LoadTexture(true, 'INTRO_L05', 'PNG', 'Transparent', 0);
  intro_layer06 := Texture.LoadTexture(true, 'INTRO_L06', 'PNG', 'Transparent', 0);
  intro_layer07 := Texture.LoadTexture(true, 'INTRO_L07', 'PNG', 'Transparent', 0);
  intro_layer08 := Texture.LoadTexture(true, 'INTRO_L08', 'PNG', 'Transparent', 0);
  SDL_Delay(1);
  intro_layer09 := Texture.LoadTexture(true, 'INTRO_L09', 'PNG', 'Transparent', 0);

  outro_bg := Texture.LoadTexture(true, 'OUTRO_BG', 'PNG', 'Plain', 0);
  outro_esc := Texture.LoadTexture(true, 'OUTRO_ESC', 'PNG', 'Transparent', 0);
  outro_exd := Texture.LoadTexture(true, 'OUTRO_EXD', 'PNG', 'Plain', 0);
  SDL_Delay(1);
  CRDTS_Stage:=InitialDelay;
end;

function TScreenCredits.Draw: boolean;
begin
  DrawCredits;
  Result := true;
end;

procedure TScreenCredits.onShow;
begin
  CRDTS_Stage:=InitialDelay;
  Credits_X := 580;
  deluxe_slidein := 0;
  Credits_Alpha := 0;
  Music.Open(soundpath + 'wome-credits-tune.mp3'); //danke kleinster liebster weeeet�����!!
  Music.SetVolume(100);  //Whiteshark, you hear me now? :P
  CTime:=0;
//  setlength(CTime_hold,0);
end;

procedure TScreenCredits.onHide;
begin
  Music.Stop;
end;

Procedure TScreenCredits.Draw_FunkyText;
var
  S{,I, Len}: Integer;
  X,Y,A: Real;
  visibleText:    PChar;
  visibleString:  string;
begin
  SetFontSize(10);
  //Init ScrollingText
  if (CTime = Timings[7]) then
  begin
    //Set Position of Text
    Credits_X := 600;
    CurrentScrollStart:=1;
    CurrentScrollEnd:=1;
  end;

  if (CTime > Timings[7]) and (CurrentScrollStart < length(Funky_Text)) then
  begin
    X:=0;
    visibleText:=pchar(Copy(Funky_Text, CurrentScrollStart, CurrentScrollEnd));
    for S := 0 to length(visibleText)-1 do begin
      Y:=abs(sin((Credits_X+X)*0.93{*(((Credits_X+X))/1200)}/100*pi));
      SetFontPos(Credits_X+X,538-Y*(Credits_X+X)*(Credits_X+X)*(Credits_X+X)/1000000);
      if (Credits_X+X < 15) then A:=0;
      if (Credits_X+X >=15) then A:=Credits_X+X-15;
      if Credits_X+X > 32 then A:=17;
      glColor4f( 230/255-40/255+Y*(Credits_X+X)/900, 200/255-30/255+Y*(Credits_X+X)/1000, 155/255-20/255+Y*(Credits_X+X)/1100, A/17);
      glPrintLetter(visibleText[S]);
      visibleString := visibleText[S];
      X := X + glTextWidth(PChar(visibleString));
    end;
    if (Credits_X<0) and (CurrentScrollStart < length(Funky_Text)) then
    begin
      visibleString := Funky_Text[CurrentScrollStart];
      Credits_X:=Credits_X + glTextWidth(PChar(visibleString));
      inc(CurrentScrollStart);
    end;
    visibleText:=pchar(Copy(Funky_Text, CurrentScrollStart, CurrentScrollEnd));
    if (Credits_X+glTextWidth(visibleText) < 600) and (CurrentScrollEnd < length(Funky_Text)) then begin
      inc(CurrentScrollEnd);
    end;
  end;
{  // timing hack
    X:=5;
    SetFontStyle (2);
     SetFontItalic(False);
     SetFontSize(9);
     glColor4f(1, 1, 1, 1);
     for S:=0 to high(CTime_hold) do begin
     visibleText:=pchar(inttostr(CTime_hold[S]));
     SetFontPos (500, X);
     glPrint (Addr(visibleText[0]));
     X:=X+20;
     end;}
end;

procedure Start3D;
begin
      glMatrixMode(GL_PROJECTION);
      glPushMatrix;
      glLoadIdentity;
      glFrustum(-0.3*4/3,0.3*4/3,-0.3,0.3,1,1000);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity;
end;
procedure End3D;
begin
      glMatrixMode(GL_PROJECTION);
      glPopMatrix;
      glMatrixMode(GL_MODELVIEW);
end;

procedure TScreenCredits.DrawCredits;
var
  T,I: Cardinal;
  X: Real;
  Ver: PChar;
  RuntimeStr: AnsiString;
  Data: TFFTData;
  j,k,l:cardinal;
  f,g,h: Real;
  STime:cardinal;
  Delay:cardinal;
  Alpha:TAlpha;

  myPixel: longword;
  myColor: Cardinal;
  myScale: Real;
  myAngle: Real;
const  myLogoCoords: Array[0..27,0..1] of Cardinal = ((39,32),(84,32),(100,16),(125,24),
                                       (154,31),(156,58),(168,32),(203,36),
                                       (258,34),(251,50),(274,93),(294,84),
                                       (232,54),(278,62),(319,34),(336,92),
                                       (347,23),(374,32),(377,58),(361,83),
                                       (385,91),(405,91),(429,35),(423,51),
                                       (450,32),(485,34),(444,91),(486,93));

begin
//dis does teh muiwk y0r
Data := Music.GetFFTData;



  T := GetTickCount div 33;
  if T <> Credits_Time then
  begin
    Credits_Time := T;
    inc(CTime);
	inc(CTime_hold);
    Credits_X := Credits_X-2;
    if (CRDTS_Stage=InitialDelay) and (CTime=Timings[0]) then
    begin
//      CTime:=Timings[20];
//      CRDTS_Stage:=Outro;

      CRDTS_Stage:=Intro;
      CTime:=0;
      Music.Play;

    end;
    if (CRDTS_Stage=Intro) and (CTime=Timings[7]) then
    begin
      CRDTS_Stage:=MainPart;
    end;
    if (CRDTS_Stage=MainPart) and (CTime=Timings[20]) then
    begin
      CRDTS_Stage:=Outro;
    end;
  end;

  //draw background
  if CRDTS_Stage=InitialDelay then
      begin
        glClearColor(0,0,0,0);
        glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT);
      end
  else
  if CRDTS_Stage=Intro then
      begin
        Start3D;
        glPushMatrix;

        glClearColor(0,0,0,0);
        glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT);

        glEnable(GL_TEXTURE_2D);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);

        if CTime < Timings[1] then begin
          myScale:= 0.5+0.5*(Timings[1]-CTime)/(Timings[1]); // slowly move layers together
          myAngle:=cos((CTime)*pi/((Timings[1])*2)); // and make logo face towards camera
        end else begin // this is the part when the logo stands still
          myScale:=0.5;
          myAngle:=0;
        end;
        if CTime > Timings[2] then begin
          myScale:= 0.5+0.5*(CTime-Timings[2])/(Timings[3]-Timings[2]); // get some space between layers
          myAngle:=0;
        end;
//        if CTime > Timings[3] then myScale:=1; // keep the space between layers
        glTranslatef(0,0,-5+0.5*myScale);
        if CTime > Timings[3] then myScale:=1; // keep the space between layers
        if CTime > Timings[3] then begin // make logo rotate left and grow
//          myScale:=(CTime-Timings[4])/(Timings[7]-Timings[4]);
          glRotatef(20*sqr(CTime-Timings[3])/sqr((Timings[7]-Timings[3])/2),0,0,1);
          glScalef(1+sqr(CTime-Timings[3])/(32*(Timings[7]-Timings[3])),1+sqr(CTime-Timings[3])/(32*(Timings[7]-Timings[3])),1);
        end;
        if CTime < Timings[2] then
          glRotatef(30*myAngle,0.5*myScale+myScale,1+myScale,0);
//        glScalef(0.5,0.5,0.5);
        glScalef(4/3,-1,1);
        glColor4f(1, 1, 1, 1);

        glBindTexture(GL_TEXTURE_2D, intro_layer01.TexNum);
        glbegin(gl_quads);
          glTexCoord2f(0,0);glVertex3f(-1,   -1, -0.4 * myScale);
          glTexCoord2f(0,1);glVertex3f(-1,   1, -0.4 * myScale);
          glTexCoord2f(1,1); glVertex3f(1, 1, -0.4 * myScale);
          glTexCoord2f(1,0);glVertex3f(1, -1, -0.4 * myScale);
        glEnd;
        glBindTexture(GL_TEXTURE_2D, intro_layer02.TexNum);
        glbegin(gl_quads);
          glTexCoord2f(0,0);glVertex3f(-1,   -1, -0.3 * myScale);
          glTexCoord2f(0,1);glVertex3f(-1,   1, -0.3 * myScale);
          glTexCoord2f(1,1); glVertex3f(1, 1, -0.3 * myScale);
          glTexCoord2f(1,0);glVertex3f(1, -1, -0.3 * myScale);
        glEnd;
        glBindTexture(GL_TEXTURE_2D, intro_layer03.TexNum);
        glbegin(gl_quads);
          glTexCoord2f(0,0);glVertex3f(-1,   -1, -0.2 * myScale);
          glTexCoord2f(0,1);glVertex3f(-1,   1, -0.2 * myScale);
          glTexCoord2f(1,1); glVertex3f(1, 1, -0.2 * myScale);
          glTexCoord2f(1,0);glVertex3f(1, -1, -0.2 * myScale);
        glEnd;
        glBindTexture(GL_TEXTURE_2D, intro_layer04.TexNum);
        glbegin(gl_quads);
          glTexCoord2f(0,0);glVertex3f(-1,   -1, -0.1 * myScale);
          glTexCoord2f(0,1);glVertex3f(-1,   1, -0.1 * myScale);
          glTexCoord2f(1,1); glVertex3f(1, 1, -0.1 * myScale);
          glTexCoord2f(1,0);glVertex3f(1, -1, -0.1 * myScale);
        glEnd;
        glBindTexture(GL_TEXTURE_2D, intro_layer05.TexNum);
        glbegin(gl_quads);
          glTexCoord2f(0,0);glVertex3f(-1,   -1, 0 * myScale);
          glTexCoord2f(0,1);glVertex3f(-1,   1, 0 * myScale);
          glTexCoord2f(1,1); glVertex3f(1, 1, 0 * myScale);
          glTexCoord2f(1,0);glVertex3f(1, -1, 0 * myScale);
        glEnd;
        glBindTexture(GL_TEXTURE_2D, intro_layer06.TexNum);
        glbegin(gl_quads);
          glTexCoord2f(0,0);glVertex3f(-1,   -1, 0.1 * myScale);
          glTexCoord2f(0,1);glVertex3f(-1,   1, 0.1 * myScale);
          glTexCoord2f(1,1); glVertex3f(1, 1, 0.1 * myScale);
          glTexCoord2f(1,0);glVertex3f(1, -1, 0.1 * myScale);
        glEnd;
        glBindTexture(GL_TEXTURE_2D, intro_layer07.TexNum);
        glbegin(gl_quads);
          glTexCoord2f(0,0);glVertex3f(-1,   -1, 0.2 * myScale);
          glTexCoord2f(0,1);glVertex3f(-1,   1, 0.2 * myScale);
          glTexCoord2f(1,1); glVertex3f(1, 1, 0.2 * myScale);
          glTexCoord2f(1,0);glVertex3f(1, -1, 0.2 * myScale);
        glEnd;
        glBindTexture(GL_TEXTURE_2D, intro_layer08.TexNum);
        glbegin(gl_quads);
          glTexCoord2f(0,0);glVertex3f(-1,   -1, 0.3 * myScale);
          glTexCoord2f(0,1);glVertex3f(-1,   1, 0.3 * myScale);
          glTexCoord2f(1,1); glVertex3f(1, 1, 0.3 * myScale);
          glTexCoord2f(1,0);glVertex3f(1, -1, 0.3 * myScale);
        glEnd;
        glBindTexture(GL_TEXTURE_2D, intro_layer09.TexNum);
        glbegin(gl_quads);
          glTexCoord2f(0,0);glVertex3f(-1,   -1, 0.22 * myScale);
          glTexCoord2f(0,1);glVertex3f(-1,   1, 0.22 * myScale);
          glTexCoord2f(1,1); glVertex3f(1, 1, 0.22 * myScale);
          glTexCoord2f(1,0);glVertex3f(1, -1, 0.22 * myScale);
        glEnd;
        gldisable(gl_texture_2d);
        glDisable(GL_BLEND);

        glPopMatrix;
        End3D;

        // do some sparkling effects
        if (CTime < Timings[1]) and (CTime > Timings[21]) then
        begin
          for k:=1 to 3 do begin
             l:=410+floor((CTime-Timings[21])/(Timings[1]-Timings[21])*(536-410))+RandomRange(-5,5);
             j:=floor((Timings[1]-CTime)/22)+RandomRange(285,301);
             GoldenRec.Spawn(l, j, 1, 16, 0, -1, Flare, 0, 0);
          end;
        end;

        // fade to white at end
        if Ctime > Timings[6] then
        begin
          glColor4f(1,1,1,sqr(Ctime-Timings[6])*(Ctime-Timings[6])/sqr(Timings[7]-Timings[6]));
          glEnable(GL_BLEND);
          glBegin(GL_QUADS);
            glVertex2f(0,0);
            glVertex2f(0,600);
            glVertex2f(800,600);
            glVertex2f(800,0);
          glEnd;
          glDisable(GL_BLEND);
        end;

      end;
    if (CRDTS_Stage=MainPart) then
      // main credits screen background, scroller, logo and girl
      begin

        glEnable(GL_TEXTURE_2D);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);

        glColor4f(1, 1, 1, 1);
        glBindTexture(GL_TEXTURE_2D, credits_bg_tex.TexNum);
        glbegin(gl_quads);
          glTexCoord2f(0,0);glVertex2f(0,   0);
          glTexCoord2f(0,600/1024);glVertex2f(0,   600);
          glTexCoord2f(800/1024,600/1024); glVertex2f(800, 600);
          glTexCoord2f(800/1024,0);glVertex2f(800, 0);
        glEnd;
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_BLEND);

        // draw scroller
        Draw_FunkyText;

//#########################################################################
// draw credits names

// blindy (von links oben reindrehen, nach rechts unten rausdrehen)
    STime:=Timings[9]-10;
    Delay:=Timings[22]-Timings[9];
    if CTime > STime then
    begin
      k:=0;
      ESC_Alpha:=20;
      for j:=0 to 40 do
        if Data[j]>=Data[k] then k:=j;
      if Data[k]>0.25 then ESC_Alpha:=5 else inc(ESC_Alpha);
      if ESC_Alpha >20 then ESC_Alpha:=20;
      if ((CTime-STime)<20) then ESC_Alpha:=20;
      //k:=CTime-STime;
      if CTime <=STime+10 then j:=CTime-STime else j:=10;
      if (CTime >=STime+Delay-10) then if (CTime <=STime+Delay) then j:=(STime+Delay)-CTime else j:=0;
      glColor4f(1, 1, 1, ESC_Alpha/20*j/10);

      if (CTime >= STime+10) and (CTime<=STime+12) then begin
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 0, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 1, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 5, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 0, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 1, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 5, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 0, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 1, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 5, 0);
      end;

      glPushMatrix;
      gltranslatef(0,329,0);
      if CTime <= STime+10 then begin glrotatef((CTime-STime)*9+270,0,0,1);end;
      gltranslatef(223,0,0);
      if CTime >=STime+Delay-10 then if CTime <=STime+Delay then begin
        gltranslatef(223,0,0);
        glrotatef((CTime-(STime+Delay-10))*-9,0,0,1);
        gltranslatef(-223,0,0);
      end;
      glBindTexture(GL_TEXTURE_2D, credits_blindy.TexNum);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glEnable(GL_BLEND);
      glEnable(GL_TEXTURE_2D);
      glbegin(gl_quads);
        glTexCoord2f(0,0);glVertex2f(-163,   -129);
        glTexCoord2f(0,1);glVertex2f(-163,   129);
        glTexCoord2f(1,1); glVertex2f(163, 129);
        glTexCoord2f(1,0);glVertex2f(163, -129);
      glEnd;
      gldisable(gl_texture_2d);
      gldisable(GL_BLEND);
      glPopMatrix;
    end;

// brunzel
    STime:=Timings[22]-10;
    Delay:=Timings[10]-Timings[22];
    if CTime > STime then
    begin
      k:=0;
      ESC_Alpha:=20;
      for j:=0 to 40 do
        if Data[j]>=Data[k] then k:=j;
      if Data[k]>0.25 then ESC_Alpha:=5 else inc(ESC_Alpha);
      if ESC_Alpha >20 then ESC_Alpha:=20;
      if ((CTime-STime)<20) then ESC_Alpha:=20;
      //k:=CTime-STime;
      if CTime <=STime+10 then j:=CTime-STime else j:=10;
      if (CTime >=STime+Delay-10) then if (CTime <=STime+Delay) then j:=(STime+Delay)-CTime else j:=0;
      glColor4f(1, 1, 1, ESC_Alpha/20*j/10);

      if (CTime >= STime+10) and (CTime<=STime+12) then begin
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 0, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 1, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 5, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 0, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 1, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 5, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 0, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 1, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 5, 0);
      end;

      glPushMatrix;
      if CTime <= STime+10 then
      begin
        j:=CTime-STime;
        glscalef(j*j/100,j*j/100,j*j/100);
        gltranslatef(j/10*100+123,j/10*129+200,0);
        glrotatef(j/10*180+180,0,-1,1);
      end else
        gltranslatef(223,329,0);

      if CTime >=STime+Delay-10 then if CTime <=STime+Delay then begin
        j := (CTime-(STime+Delay-10))*-9;
        glscalef(j*j/400+1,j*j/400+1,j*j/400+1);
      end;
      glBindTexture(GL_TEXTURE_2D, credits_brunzel.TexNum);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glEnable(GL_BLEND);
      glEnable(GL_TEXTURE_2D);
      glbegin(gl_quads);
        glTexCoord2f(0,0);glVertex2f(-163,   -129);
        glTexCoord2f(0,1);glVertex2f(-163,   129);
        glTexCoord2f(1,1); glVertex2f(163, 129);
        glTexCoord2f(1,0);glVertex2f(163, -129);
      glEnd;
      gldisable(gl_texture_2d);
      gldisable(GL_BLEND);
      glPopMatrix;
    end;

// canni  (zoom von 0 auf volle gr�sse und drehung, zoom auf doppelte gr�sse und nach rechts oben schieben)
    STime:=Timings[10]-10;
    Delay:=Timings[11]-Timings[10]+5;
    if CTime > STime then
    begin
      k:=0;
      ESC_Alpha:=20;
      for j:=0 to 40 do
        if Data[j]>=Data[k] then k:=j;
      if Data[k]>0.25 then ESC_Alpha:=5 else inc(ESC_Alpha);
      if ESC_Alpha >20 then ESC_Alpha:=20;
      if ((CTime-STime)<20) then ESC_Alpha:=20;
      //k:=CTime-STime;
      if CTime <=STime+10 then j:=CTime-STime else j:=10;
      if (CTime >=STime+Delay-10) then if (CTime <=STime+Delay) then j:=(STime+Delay)-CTime else j:=0;
      glColor4f(1, 1, 1, ESC_Alpha/20*j/10);

      if (CTime >= STime+20) and (CTime<=STime+22) then begin
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 0, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 1, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 5, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 0, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 1, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 5, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 0, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 1, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 5, 0);
      end;

      glPushMatrix;
      gltranslatef(223,329,0);
      if CTime <= STime+20 then begin
        j:=CTime-Stime;
        glscalef(j*j/400,j*j/400,j*j/400);
        glrotatef(j*18.0,0,0,1);
      end;
      if CTime >=STime+Delay-10 then if CTime <=STime+Delay then begin
        j:=CTime-(STime+Delay-10);
        f:=j*10.0;
        gltranslatef(f*3,-f,0);
        glscalef(1+j/10,1+j/10,1+j/10);
        glrotatef(j*9.0,0,0,1);
      end;
      glBindTexture(GL_TEXTURE_2D, credits_canni.TexNum);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glEnable(GL_BLEND);
      glEnable(GL_TEXTURE_2D);
      glbegin(gl_quads);
        glTexCoord2f(0,0);glVertex2f(-163,   -129);
        glTexCoord2f(0,1);glVertex2f(-163,   129);
        glTexCoord2f(1,1); glVertex2f(163, 129);
        glTexCoord2f(1,0);glVertex2f(163, -129);
      glEnd;
      gldisable(gl_texture_2d);
      gldisable(GL_BLEND);
      glPopMatrix;
    end;

// ggkfc  (von links reinschieben, nach rechts oben rausschieben)
    STime:=Timings[11]-10;
    Delay:=Timings[12]-Timings[11]+5;
    if CTime > STime then
    begin
      k:=0;
      ESC_Alpha:=20;
      for j:=0 to 40 do
        if Data[j]>=Data[k] then k:=j;
      if Data[k]>0.25 then ESC_Alpha:=5 else inc(ESC_Alpha);
      if ESC_Alpha >20 then ESC_Alpha:=20;
      if ((CTime-STime)<20) then ESC_Alpha:=20;
      //k:=CTime-STime;
      if CTime <=STime+10 then j:=CTime-STime else j:=10;
      if (CTime >=STime+Delay-10) then if (CTime <=STime+Delay) then j:=(STime+Delay)-CTime else j:=0;
      glColor4f(1, 1, 1, ESC_Alpha/20*j/10);

      if (CTime >= STime+10) and (CTime<=STime+12) then begin
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 0, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 1, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 5, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 0, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 1, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 5, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 0, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 1, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 5, 0);
      end;

      glPushMatrix;
      gltranslatef(223,329,0);
      if CTime <= STime+10 then begin
        gltranslatef(((CTime-STime)*21.0)-210,0,0);
      end;
      if CTime >=STime+Delay-10 then if CTime <=STime+Delay then begin
        j:=(CTime-(STime+Delay-10))*21;
        gltranslatef(j,-j/2,0);
      end;
      glBindTexture(GL_TEXTURE_2D, credits_ggkfc.TexNum);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glEnable(GL_BLEND);
      glEnable(GL_TEXTURE_2D);
      glbegin(gl_quads);
        glTexCoord2f(0,0);glVertex2f(-163,   -129);
        glTexCoord2f(0,1);glVertex2f(-163,   129);
        glTexCoord2f(1,1); glVertex2f(163, 129);
        glTexCoord2f(1,0);glVertex2f(163, -129);
      glEnd;
      gldisable(gl_texture_2d);
      gldisable(GL_BLEND);
      glPopMatrix;
    end;

// jaybinks  (von unten reinklappen, nach rechts oben rausklappen)
    STime:=Timings[12]-10;
    Delay:=Timings[13]-Timings[12];
    if CTime > STime then
    begin
      k:=0;
      ESC_Alpha:=20;
      for j:=0 to 40 do
        if Data[j]>=Data[k] then k:=j;
      if Data[k]>0.25 then ESC_Alpha:=5 else inc(ESC_Alpha);
      if ESC_Alpha >20 then ESC_Alpha:=20;
      if ((CTime-STime)<20) then ESC_Alpha:=20;
      //k:=CTime-STime;
      if CTime <=STime+10 then j:=CTime-STime else j:=10;
      if (CTime >=STime+Delay-10) then if (CTime <=STime+Delay) then j:=(STime+Delay)-CTime else j:=0;
      glColor4f(1, 1, 1, ESC_Alpha/20*j/10);

      if (CTime >= STime+10) and (CTime<=STime+12) then begin
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 0, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 1, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 5, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 0, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 1, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 5, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 0, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 1, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 5, 0);
      end;

      glPushMatrix;
      gltranslatef(223,329,0);
      if CTime <= STime+10 then
        f:=258.0-25.8*(CTime-STime)
      else
        f:=0;

      if CTime >=STime+Delay-10 then if CTime <=STime+Delay then begin
        j:=CTime-(STime+Delay-10);
        g:=32.6*j;
      end else
        g:=0;
      glBindTexture(GL_TEXTURE_2D, credits_jaybinks.TexNum);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glEnable(GL_BLEND);
      glEnable(GL_TEXTURE_2D);
      glbegin(gl_quads);
        glTexCoord2f(0,0);glVertex2f(-163+g-f*1.5,   -129+f*1.5-g/2);
        glTexCoord2f(0,1);glVertex2f(-163+g*1.5,   129-(g*1.5*258/326));
        glTexCoord2f(1,1); glVertex2f(163+g, 129+g/4);
        glTexCoord2f(1,0);glVertex2f(163+f*1.5+g/4, -129+f*1.5-g/4);
      glEnd;
      gldisable(gl_texture_2d);
      gldisable(GL_BLEND);
      glPopMatrix;
    end;

// linnex  (just scrolls from left to right, no twinkling stars, no on-beat flashing)
    STime:=Timings[13]-10;
    Delay:=Timings[14]-Timings[13]+10;
    if CTime > STime then
    begin
      k:=0;
      ESC_Alpha:=20;
      for j:=0 to 40 do
        if Data[j]>=Data[k] then k:=j;
      if Data[k]>0.25 then ESC_Alpha:=5 else inc(ESC_Alpha);
      if ESC_Alpha >20 then ESC_Alpha:=20;
      if ((CTime-STime)<20) then ESC_Alpha:=20;
      //k:=CTime-STime;
      if CTime <=STime+10 then j:=CTime-STime else j:=10;
      if (CTime >=STime+Delay-10) then if (CTime <=STime+Delay) then j:=(STime+Delay)-CTime else j:=0;
      glColor4f(1, 1, 1, ESC_Alpha/20*j/10);

      if (CTime >= STime+10) and (CTime<=STime+12) then begin
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 0, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 1, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 5, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 0, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 1, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 5, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 0, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 1, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 5, 0);
      end;


      glPushMatrix;
      gltranslatef(223,329,0);
      if CTime <= STime+10 then begin
        gltranslatef(223,0,0);
        glrotatef((10-(CTime-STime))*9,0,0,1);
        gltranslatef(-223,0,0);
      end;
      if CTime >=STime+Delay-10 then if CTime <=STime+Delay then begin
        j:=CTime-(STime+Delay-10);
        f:=j*10.0;
        gltranslatef(-f*2,-f,0);
        glscalef(1-j/10,1-j/10,1-j/10);
        glrotatef(-j*9.0,0,0,1);
      end;
      glBindTexture(GL_TEXTURE_2D, credits_linnex.TexNum);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glEnable(GL_BLEND);
      glEnable(GL_TEXTURE_2D);
      glbegin(gl_quads);
        glTexCoord2f(0,0);glVertex2f(-163,   -129);
        glTexCoord2f(0,1);glVertex2f(-163,   129);
        glTexCoord2f(1,1); glVertex2f(163, 129);
        glTexCoord2f(1,0);glVertex2f(163, -129);
      glEnd;
      gldisable(gl_texture_2d);
      gldisable(GL_BLEND);
      glPopMatrix;
    end;

// Mog (von links reinklappen, nach rechts unten rausklappen)
    STime:=Timings[14]-10;
    Delay:=Timings[15]-Timings[14]+5;
    if CTime > STime then
    begin
      k:=0;
      ESC_Alpha:=20;
      for j:=0 to 40 do
        if Data[j]>=Data[k] then k:=j;
      if Data[k]>0.25 then ESC_Alpha:=5 else inc(ESC_Alpha);
      if ESC_Alpha >20 then ESC_Alpha:=20;
      if ((CTime-STime)<20) then ESC_Alpha:=20;
      //k:=CTime-STime;
      if CTime <=STime+10 then j:=CTime-STime else j:=10;
      if (CTime >=STime+Delay-10) then if (CTime <=STime+Delay) then j:=(STime+Delay)-CTime else j:=0;
      glColor4f(1, 1, 1, ESC_Alpha/20*j/10);

      if (CTime >= STime+10) and (CTime<=STime+12) then begin
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 0, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 1, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 5, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 0, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 1, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 5, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 0, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 1, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 5, 0);
      end;

      glPushMatrix;
      gltranslatef(223,329,0);
      if CTime <= STime+10 then
        f:=326.0-32.6*(CTime-STime)
      else
        f:=0;

      if CTime >=STime+Delay-10 then if CTime <=STime+Delay then begin
        j:=CTime-(STime+Delay-10);
        g:=32.6*j;
      end else
        g:=0;
      glBindTexture(GL_TEXTURE_2D, credits_mog.TexNum);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glEnable(GL_BLEND);
      glEnable(GL_TEXTURE_2D);
      glbegin(gl_quads);
        glTexCoord2f(0,0);glVertex2f(-163+g*1.5,   -129+g*1.5);
        glTexCoord2f(0,1);glVertex2f(-163+g*1.2,   129+g);
        glTexCoord2f(1,1); glVertex2f(163-f+g/2, 129+f*1.5+g/4);
        glTexCoord2f(1,0);glVertex2f(163-f+g*1.5, -129-f*1.5);
      glEnd;
      gldisable(gl_texture_2d);
      gldisable(GL_BLEND);
      glPopMatrix;
    end;

// omgdutch (von rechts oben reindrehen, nach links unten rausschieben und verkleinern und dabei drehen)
    STime:=Timings[15]-10;
    Delay:=Timings[16]-Timings[15]+5;
    if CTime > STime then
    begin
      k:=0;
      ESC_Alpha:=20;
      for j:=0 to 40 do
        if Data[j]>=Data[k] then k:=j;
      if Data[k]>0.25 then ESC_Alpha:=5 else inc(ESC_Alpha);
      if ESC_Alpha >20 then ESC_Alpha:=20;
      if ((CTime-STime)<20) then ESC_Alpha:=20;
      //k:=CTime-STime;
      if CTime <=STime+10 then j:=CTime-STime else j:=10;
      if (CTime >=STime+Delay-10) then if (CTime <=STime+Delay) then j:=(STime+Delay)-CTime else j:=0;
      glColor4f(1, 1, 1, ESC_Alpha/20*j/10);

      if (CTime >= STime+10) and (CTime<=STime+12) then begin
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 0, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 1, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 5, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 0, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 1, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 5, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 0, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 1, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 5, 0);
      end;

      glPushMatrix;
      gltranslatef(223,329,0);
      if CTime <= STime+10 then begin
        gltranslatef(223,0,0);
        glrotatef((10-(CTime-STime))*9,0,0,1);
        gltranslatef(-223,0,0);
      end;
      if CTime >=STime+Delay-10 then if CTime <=STime+Delay then begin
        j:=CTime-(STime+Delay-10);
        f:=j*10.0;
        gltranslatef(-f*2,-f,0);
        glscalef(1-j/10,1-j/10,1-j/10);
        glrotatef(-j*9.0,0,0,1);
      end;
      glBindTexture(GL_TEXTURE_2D, credits_omgdutch.TexNum);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glEnable(GL_BLEND);
      glEnable(GL_TEXTURE_2D);
      glbegin(gl_quads);
        glTexCoord2f(0,0);glVertex2f(-163,   -129);
        glTexCoord2f(0,1);glVertex2f(-163,   129);
        glTexCoord2f(1,1); glVertex2f(163, 129);
        glTexCoord2f(1,0);glVertex2f(163, -129);
      glEnd;
      gldisable(gl_texture_2d);
      gldisable(GL_BLEND);
      glPopMatrix;
    end;

// Skillmaster (von rechts unten reinschieben, nach rechts oben rausdrehen)
    STime:=Timings[16]-10;
    Delay:=Timings[17]-Timings[16]+5;
    if CTime > STime then
    begin
      k:=0;
      ESC_Alpha:=20;
      for j:=0 to 40 do
        if Data[j]>=Data[k] then k:=j;
      if Data[k]>0.25 then ESC_Alpha:=5 else inc(ESC_Alpha);
      if ESC_Alpha >20 then ESC_Alpha:=20;
      if ((CTime-STime)<20) then ESC_Alpha:=20;
      //k:=CTime-STime;
      if CTime <=STime+10 then j:=CTime-STime else j:=10;
      if (CTime >=STime+Delay-10) then if (CTime <=STime+Delay) then j:=(STime+Delay)-CTime else j:=0;
      glColor4f(1, 1, 1, ESC_Alpha/20*j/10);

      if (CTime >= STime+10) and (CTime<=STime+12) then begin
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 0, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 1, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 5, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 0, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 1, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 5, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 0, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 1, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 5, 0);
      end;

      glPushMatrix;
      gltranslatef(223,329,0);
      if CTime <= STime+10 then begin
        j:=STime+10-CTime;
        f:=j*10.0;
        gltranslatef(+f*2,+f/2,0);
      end;
      if CTime >=STime+Delay-10 then if CTime <=STime+Delay then begin
        j:=CTime-(STime+Delay-10);
        //f:=j*10.0;
        gltranslatef(0,-223,0);
        glrotatef(j*-9,0,0,1);
        gltranslatef(0,223,0);
        glrotatef(j*9,0,0,1);
      end;
      glBindTexture(GL_TEXTURE_2D, credits_skillmaster.TexNum);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glEnable(GL_BLEND);
      glEnable(GL_TEXTURE_2D);
      glbegin(gl_quads);
        glTexCoord2f(0,0);glVertex2f(-163,   -129);
        glTexCoord2f(0,1);glVertex2f(-163,   129);
        glTexCoord2f(1,1); glVertex2f(163, 129);
        glTexCoord2f(1,0);glVertex2f(163, -129);
      glEnd;
      gldisable(gl_texture_2d);
      gldisable(GL_BLEND);
      glPopMatrix;
    end;

// WhiteShark (von links unten reinklappen, nach rechts oben rausklappen)
    STime:=Timings[17]-10;
    Delay:=Timings[18]-Timings[17];
    if CTime > STime then
    begin
      k:=0;
      ESC_Alpha:=20;
      for j:=0 to 40 do
        if Data[j]>=Data[k] then k:=j;
      if Data[k]>0.25 then ESC_Alpha:=5 else inc(ESC_Alpha);
      if ESC_Alpha >20 then ESC_Alpha:=20;
      if ((CTime-STime)<20) then ESC_Alpha:=20;
      //k:=CTime-STime;
      if CTime <=STime+10 then j:=CTime-STime else j:=10;
      if (CTime >=STime+Delay-10) then if (CTime <=STime+Delay) then j:=(STime+Delay)-CTime else j:=0;
      glColor4f(1, 1, 1, ESC_Alpha/20*j/10);

      if (CTime >= STime+10) and (CTime<=STime+12) then begin
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 0, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 1, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 5, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 0, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 1, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 5, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 0, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 1, 0);
        GoldenRec.Spawn(RandomRange(65,390), RandomRange(200,460), 1, 16, 0, -1, PerfectLineTwinkle, 5, 0);
      end;

      glPushMatrix;
      gltranslatef(223,329,0);
      if CTime <= STime+10 then
        f:=326.0-32.6*(CTime-STime)
      else
        f:=0;

      if CTime >=STime+Delay-10 then if CTime <=STime+Delay then begin
        j:=CTime-(STime+Delay-10);
        g:=32.6*j;
      end else
        g:=0;
      glBindTexture(GL_TEXTURE_2D, credits_whiteshark.TexNum);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glEnable(GL_BLEND);
      glEnable(GL_TEXTURE_2D);
      glbegin(gl_quads);
        glTexCoord2f(0,0);glVertex2f(-163-f+g,   -129+f/4-g/2);
        glTexCoord2f(0,1);glVertex2f(-163-f/4+g,   129+g/2+f/4);
        glTexCoord2f(1,1); glVertex2f(163-f*1.2+g/4, 129+f/2-g/4);
        glTexCoord2f(1,0);glVertex2f(163-f*1.5+g/4, -129+f*1.5+g/4);
      glEnd;
      gldisable(gl_texture_2d);
      gldisable(GL_BLEND);
      glPopMatrix;
    end;


// ####################################################################
// do some twinkle stuff (kinda on beat)
    if (CTime>Timings[8]) and (CTime < Timings[19]) then begin
      k:=0;
      for j:=0 to 40 do
        if Data[j]>=Data[k] then k:=j;
      if Data[k]>0.2 then begin
         l:=RandomRange(6,16);
         j:=RandomRange(0,27);
         GoldenRec.Spawn(myLogoCoords[j,0], myLogoCoords[j,1], 16-l, l, 0, -1, PerfectNote, 0, 0);
      end;
    end;

//#################################################
// draw the rest of the main screen (girl and logo
        glEnable(GL_TEXTURE_2D);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        glColor4f(1, 1, 1, 1);
        glBindTexture(GL_TEXTURE_2D, credits_bg_ovl.TexNum);
        glbegin(gl_quads);
          glTexCoord2f(0,0);glVertex2f(800-393,   0);
          glTexCoord2f(0,600/1024);glVertex2f(800-393,   600);
          glTexCoord2f(393/512,600/1024); glVertex2f(800, 600);
          glTexCoord2f(393/512,0);glVertex2f(800, 0);
        glEnd;
{        glBindTexture(GL_TEXTURE_2D, credits_bg_logo.TexNum);
        glbegin(gl_quads);
          glTexCoord2f(0,0);glVertex2f(0,   0);
          glTexCoord2f(0,112/128);glVertex2f(0,   112);
          glTexCoord2f(497/512,112/128); glVertex2f(497, 112);
          glTexCoord2f(497/512,0);glVertex2f(497, 0);
        glEnd;
}
        gldisable(gl_texture_2d);
        glDisable(GL_BLEND);

        // fade out at end of main part
        if Ctime > Timings[19] then
        begin
          glColor4f(0,0,0,(Ctime-Timings[19])/(Timings[20]-Timings[19]));
          glEnable(GL_BLEND);
          glBegin(GL_QUADS);
            glVertex2f(0,0);
            glVertex2f(0,600);
            glVertex2f(800,600);
            glVertex2f(800,0);
          glEnd;
          glDisable(GL_BLEND);
        end;
      end
    else
    if (CRDTS_Stage=Outro) then
    begin
      if CTime=Timings[20] then begin
        CTime_hold:=0;
        Music.Stop;
        Music.Open(soundpath + 'credits-outro-tune.mp3');
        Music.Play;
        Music.SetVolume(20);
        Music.SetLoop(True);
      end;
      if CTime_hold > 231 then begin
        Music.Play;
        Ctime_hold:=0;
      end;
      glClearColor(0,0,0,0);
      glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT);

      // do something useful
        // outro background
        glEnable(GL_TEXTURE_2D);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);

        glColor4f(1, 1, 1, 1);
        glBindTexture(GL_TEXTURE_2D, outro_bg.TexNum);
        glbegin(gl_quads);
          glTexCoord2f(0,0);glVertex2f(0,   0);
          glTexCoord2f(0,600/1024);glVertex2f(0,   600);
          glTexCoord2f(800/1024,600/1024); glVertex2f(800, 600);
          glTexCoord2f(800/1024,0);glVertex2f(800, 0);
        glEnd;

        //outro overlays
        glColor4f(1, 1, 1, (1+sin(CTime/15))/3+1/3);
        glBindTexture(GL_TEXTURE_2D, outro_esc.TexNum);
        glbegin(gl_quads);
          glTexCoord2f(0,0);glVertex2f(0,   0);
          glTexCoord2f(0,223/256);glVertex2f(0,   223);
          glTexCoord2f(487/512,223/256); glVertex2f(487, 223);
          glTexCoord2f(487/512,0);glVertex2f(487, 0);
        glEnd;

        ESC_Alpha:=20;
        if (RandomRange(0,20) > 18) and (ESC_Alpha=20) then
          ESC_Alpha:=0
        else inc(ESC_Alpha);
        if ESC_Alpha > 20 then ESC_Alpha:=20;
        glColor4f(1, 1, 1, ESC_Alpha/20);
        glBindTexture(GL_TEXTURE_2D, outro_exd.TexNum);
        glbegin(gl_quads);
          glTexCoord2f(0,0);glVertex2f(800-310,   600-247);
          glTexCoord2f(0,247/256);glVertex2f(800-310,   600);
          glTexCoord2f(310/512,247/256); glVertex2f(800, 600);
          glTexCoord2f(310/512,0);glVertex2f(800, 600-247);
        glEnd;
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_BLEND);

        // outro scrollers?
        // ...
    end;

{  // draw credits runtime counter
   SetFontStyle (2);
    SetFontItalic(False);
    SetFontSize(9);
    SetFontPos (5, 5);
    glColor4f(1, 1, 1, 1);
//    RuntimeStr:='CTime: '+inttostr(floor(CTime/30.320663991914489602156136106092))+'.'+inttostr(floor(CTime/3.0320663991914489602156136106092)-floor(CTime/30.320663991914489602156136106092)*10);
    RuntimeStr:='CTime: '+inttostr(CTime);
    glPrint (Addr(RuntimeStr[1]));
}
  // make the stars shine
  Alpha[0] := 1;
  Alpha[1] := 1;
  GoldenRec.Draw(Alpha);

  //timing hack
//    Draw_FunkyText;
end;

end.