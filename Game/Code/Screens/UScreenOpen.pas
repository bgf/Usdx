unit UScreenOpen;

interface

uses UMenu, UMusic, SDL, SysUtils, UFiles, UTime, USongs, UIni, ULog, UTexture, UMenuText,
  ULyrics, Math, gl, UThemes;

type
  TScreenOpen = class(TMenu)
    private
      //TextF:    array[0..1] of integer;
      TextN:    integer;
    public
      Tex_Background:     TTexture;
      FadeOut:            boolean;
      Path:               string;
      BackScreen:         pointer;
      procedure AddBox(X, Y, W, H: real);
      constructor Create; override;
      procedure onShow; override;
      function ParseInput(PressedKey: Cardinal; ScanCode: byte; PressedDown: Boolean): Boolean; override;
//      function Draw: boolean; override;
//      procedure Finish;
  end;

implementation
uses UGraphic, UDraw, UMain, USkins;

function TScreenOpen.ParseInput(PressedKey: Cardinal; ScanCode: byte; PressedDown: Boolean): Boolean;
begin
  Result := true;
  if (PressedDown) then begin // Key Down
    case ScanCode of
      ord('a')..ord('z'), ord('A')..ord('Z'), ord('0')..ord('9'), 32, ord('-'), ord('.'), ord(':'), ord('\'):
        begin
          if Interaction = 0 then begin
            Text[TextN].Text := Text[TextN].Text + chr(ScanCode);
          end;
        end;
    end;

    case PressedKey of
      SDLK_Q:
        begin
          Result := false;
        end;
      8: // del
        begin
            if Interaction = 0 then
            begin
              Text[TextN].DeleteLastL;
            end;
        end;

      SDLK_ESCAPE :
        begin
          //Empty Filename and go to last Screen
            FileName := '';
            Music.PlayBack;
            FadeTo(BackScreen);
        end;

      SDLK_RETURN:
        begin
          if (Interaction = 2) then begin
            //Update Filename and go to last Screen
            FileName := Text[TextN].Text;
            Music.PlayBack;
            FadeTo(BackScreen);
          end
          else if (Interaction = 1) then
          begin
            //Empty Filename and go to last Screen
            FileName := '';
            Music.PlayBack;
            FadeTo(BackScreen);
          end;
        end;

      SDLK_LEFT:
        begin
          InteractPrev;
        end;

      SDLK_RIGHT:
        begin
          InteractNext;
        end;

      SDLK_DOWN:
        begin
        end;

      SDLK_UP:
        begin
        end;
    end;
  end;
end;

procedure TScreenOpen.AddBox(X, Y, W, H: real);
begin
  AddStatic(X,   Y,   W,   H,   0, 0, 0, Skin.GetTextureFileName('Bar'), 'JPG', 'Font Black');
  AddStatic(X+2, Y+2, W-4, H-4, 1, 1, 1, Skin.GetTextureFileName('Bar'), 'JPG', 'Font Black');
end;

constructor TScreenOpen.Create;
begin
  inherited Create;

  // linijka
{  AddStatic(20, 10, 80, 30, 0, 0, 0, 'Bar', 'JPG', 'Font Black');
  AddText(35, 17, 1, 6, 1, 1, 1, 'Linijka');
  TextSentence := AddText(120, 14, 1, 8, 0, 0, 0, '0 / 0');}

  // file list
//  AddBox(400, 100, 350, 450);

//  TextF[0] :=  AddText(430, 155,  0, 8, 0, 0, 0, 'a');
//  TextF[1] :=  AddText(430, 180,  0, 8, 0, 0, 0, 'a');

  // file name
  AddBox(20, 540, 500, 40);
  TextN := AddText(50, 548, 0, 8, 0, 0, 0, FileName);
  AddInteraction(iText, TextN);

  // buttons
  {AddButton(540, 540, 100, 40, Skin.SkinPath + Skin.ButtonF);
  AddButtonText(10, 5, 0, 0, 0, 'Cancel');

  AddButton(670, 540, 100, 40, Skin.SkinPath + Skin.ButtonF);
  AddButtonText(30, 5, 0, 0, 0, 'OK');}
  // buttons
  AddButton(540, 540, 100, 40, Skin.GetTextureFileName('ButtonF'), false);
  AddButtonText(10, 5, 0, 0, 0, 'Cancel');

  AddButton(670, 540, 100, 40, Skin.GetTextureFileName('ButtonF'), false);
  AddButtonText(30, 5, 0, 0, 0, 'OK');


end;

procedure TScreenOpen.onShow;
begin
  Interaction := 0;
end;

(*function TScreenEditSub.Draw: boolean;
var
  Min:    integer;
  Sec:    integer;
  Tekst:  string;
  Pet:    integer;
  AktBeat:  integer;
begin

end;

procedure TScreenEditSub.Finish;
begin
//
end;*)

end.