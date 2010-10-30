; This list contains the files that will be uninstalled

; Delete provided Game Exe and provided Tools
 Delete "$INSTDIR\${exe}.exe"

; Delete other provided/created stuff
 Delete "$INSTDIR\acinerella.dll"
 Delete "$INSTDIR\bass.dll"
 Delete "$INSTDIR\Changelog.german.txt"
 Delete "$INSTDIR\Changelog.txt"
 Delete "$INSTDIR\documentation.pdf"
 Delete "$INSTDIR\License.txt"
 Delete "$INSTDIR\ReadMe.txt"
 Delete "$INSTDIR\ReadMe old.txt"
 Delete "$INSTDIR\SDL.dll"
 Delete "$INSTDIR\sqlite3.dll"

 Delete "$INSTDIR\config.ini"
 Delete "$INSTDIR\Error.log"
 Delete "$INSTDIR\covers.cache"
 Delete "$INSTDIR\Ultrastar.db"
 Delete "$INSTDIR\Uninstall.exe"

${If} ${AtLeastWinVista}

; Delete gdf.dll
 Delete "$WINDIR\gdf.dll"

${EndIf}

; Delete provided Covers 
 Delete "$INSTDIR\Covers\Covers.ini"
 Delete "$INSTDIR\Covers\NoCover.jpg"
 
; Delete provided Fonts
  Delete "$INSTDIR\Fonts\Bold.fnt"
  Delete "$INSTDIR\Fonts\Bold_0.png"
  Delete "$INSTDIR\Fonts\Bold_1.png"
  Delete "$INSTDIR\Fonts\FontO.fnt"
  Delete "$INSTDIR\Fonts\FontO2.fnt"
  Delete "$INSTDIR\Fonts\FontO2_0.png"
  Delete "$INSTDIR\Fonts\FontO2_1.png"
  Delete "$INSTDIR\Fonts\FontO2_2.png"
  Delete "$INSTDIR\Fonts\FontO2_3.png"
  Delete "$INSTDIR\Fonts\FontO2_4.png"
  ;Delete "$INSTDIR\Fonts\FontO2_5.png"
  ;Delete "$INSTDIR\Fonts\FontO2_6.png"
  Delete "$INSTDIR\Fonts\FontO_0.png"
  Delete "$INSTDIR\Fonts\FontO_1.png"
  Delete "$INSTDIR\Fonts\FontO_2.png"
  Delete "$INSTDIR\Fonts\FontO_3.png"
  Delete "$INSTDIR\Fonts\FontO_4.png"
  Delete "$INSTDIR\Fonts\FontO_5.png"
  Delete "$INSTDIR\Fonts\HighResNumbersO.fnt"
  Delete "$INSTDIR\Fonts\HighResNumbersO_0.png"
  Delete "$INSTDIR\Fonts\HighResNumbersO_1.png"
  Delete "$INSTDIR\Fonts\HighResNumbersO_2.png"
  Delete "$INSTDIR\Fonts\HighResNumbersO_3.png"
  Delete "$INSTDIR\Fonts\HighResNumbersO_4.png"
  Delete "$INSTDIR\Fonts\Normal.fnt"
  Delete "$INSTDIR\Fonts\Normal_0.png" 

; Delete provided languages
 Delete "$INSTDIR\Languages\readme.txt"
 Delete "$INSTDIR\Languages\Languages.xls"
 Delete "$INSTDIR\Languages\Dutch.ini"
 Delete "$INSTDIR\Languages\English.ini"
 Delete "$INSTDIR\Languages\German.ini"
 Delete "$INSTDIR\Languages\Italian.ini"
 
; Delete provided plugins
 Delete "$INSTDIR\Plugins\Blind.dll"
 Delete "$INSTDIR\Plugins\Duell.dll"
 Delete "$INSTDIR\Plugins\Hold_The_Line.dll"
 Delete "$INSTDIR\Plugins\TeamDuell.dll"
 Delete "$INSTDIR\Plugins\Until5000.dll"
 Delete "$INSTDIR\Plugins\HauDenLukas.dll"

; Delete provided Blue Sensation Skin
 Delete "$INSTDIR\Skins\Blue Sensation\blue sensation.ini"
 Delete "$INSTDIR\Skins\Blue Sensation\blue simple.ini"
 Delete "$INSTDIR\Skins\Blue Sensation\city.ini"
 Delete "$INSTDIR\Skins\Blue Sensation\flower.ini"
 Delete "$INSTDIR\Skins\Blue Sensation\[bg-load]blue.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[bg-load]city.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[bg-load]flower.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[bg-load]sensation.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[bg-main]blue.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[bg-main]city.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[bg-main]flower.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[bg-main]sensation.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[bg-menu]blue.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[bg-menu]city.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[bg-menu]flower.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[bg-menu]sensation.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[bg-option]blue.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[bg-option]city.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[bg-option]flower.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[bg-option]sensation.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[bg-party]sensation.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[bg-song]blue.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[bg-song]city.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[bg-song]flower.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[bg-song]sensation.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[bg-top5]blue.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[bg-top5]city.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[bg-top5]flower.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[bg-top5]sensation.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[button]13.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[button]alt.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[button]az.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[button]enter.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[button]esc.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[button]j.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[button]m.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[button]navi.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[button]p.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[effect]goldenNoteStar.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[effect]perfectNoteStar.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[helper]buttonFade.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[helper]buttonFade2.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[helper]rectangle.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[icon]calcmedley.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[icon]cd.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[icon]challenge.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[icon]classic.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[icon]error.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[icon]main.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[icon]medley.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[icon]options.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[icon]party.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[icon]question.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[icon]score.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[icon]search.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[icon]songmenu.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[icon]song_duet.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[icon]stats.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[icon]video.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[main]button.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[main]buttonf.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[main]buttonmenu1.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[main]buttonmenu2.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[main]buttonmenu3.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[main]buttonmenu4.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[main]buttonmenu5.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[main]buttonmenu6.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[main]buttonmenu7.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[main]buttonmenu8.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[main]buttonmenu8a.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[main]buttonmenu9.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[main]mainBar.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[main]playerNumberBox.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[main]selectbg.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[main]songCover.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[main]songSelection1.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[main]songSelection2.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[menu]jumpToBg.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[menu]PopUpBg.JPG"
 Delete "$INSTDIR\Skins\Blue Sensation\[menu]PopUpFg.JPG"
 Delete "$INSTDIR\Skins\Blue Sensation\[menu]songMenuBg.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[menu]songMenuSelectBg.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[option]button.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[party]Joker.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[party]playerButton.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[party]playerTeamButton.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[party]pointer.bmp"
 Delete "$INSTDIR\Skins\Blue Sensation\[party]roundBG1.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[party]roundBG2.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[party]roundBG3.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[party]roundBG4.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[party]roundTeamButton.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[party]scoreBG1.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[party]scoreBG2.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[party]scoreDecoration.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[party]teamPoints.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[party]winDecoration1.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[party]winTeamButton1.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[party]winTeamButton2.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[party]winTeamButton3.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[score]box.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[score]endcap.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[score]level.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[score]levelRound.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[score]Line.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[sing]lineBonusPopUp.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[sing]LyricsBall.bmp"
 Delete "$INSTDIR\Skins\Blue Sensation\[sing]lyricsHelpBar.bmp"
 Delete "$INSTDIR\Skins\Blue Sensation\[sing]notesBgLeft.bmp"
 Delete "$INSTDIR\Skins\Blue Sensation\[sing]notesBgMid.bmp"
 Delete "$INSTDIR\Skins\Blue Sensation\[sing]notesBgRight.bmp"
 Delete "$INSTDIR\Skins\Blue Sensation\[sing]notesLeft.bmp"
 Delete "$INSTDIR\Skins\Blue Sensation\[sing]notesMid.bmp"
 Delete "$INSTDIR\Skins\Blue Sensation\[sing]notesRight.bmp"
 Delete "$INSTDIR\Skins\Blue Sensation\[sing]p.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[sing]scoreBg.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[sing]singBarBack.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[sing]singBarBar.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[sing]singBarFront.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[sing]textBar.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[sing]timeBar.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[sing]timeBar1.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[sing]timeBarBG.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[special]bar1.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[special]bar2.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[stat]detailBG1.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[stat]mainBG1.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[stat]mainBG2.jpg"
 Delete "$INSTDIR\Skins\Blue Sensation\[stat]mainBG3.jpg"

; Delete provided Deluxe Skin
 Delete "$INSTDIR\Skins\Deluxe\Blue.ini"
 Delete "$INSTDIR\Skins\Deluxe\Fall.ini"
 Delete "$INSTDIR\Skins\Deluxe\Summer.ini"
 Delete "$INSTDIR\Skins\Deluxe\Winter.ini"
 Delete "$INSTDIR\Skins\Deluxe\[bg-load]blue.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[bg-load]fall.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[bg-load]summer.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[bg-load]winter.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[bg-main]blue.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[bg-main]fall.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[bg-main]summer.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[bg-main]winter.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[button]13.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[button]alt.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[button]az.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[button]enter.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[button]esc.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[button]j.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[button]m.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[button]navi.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[button]p.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[effect]goldenNoteStar.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[effect]perfectNoteStar.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[helper]buttonFade.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[helper]rectangle.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[icon]calcmedley.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[icon]cd.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[icon]error.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[icon]main.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[icon]medley.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[icon]options.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[icon]party.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[icon]question.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[icon]score.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[icon]search.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[icon]songmenu.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[icon]song_duet.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[icon]stats.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[icon]video.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[main]button.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[main]buttonf.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[main]mainBar.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[main]playerNumberBox.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[main]selectbg.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[main]songCover.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[main]songSelection1.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[main]songSelection2.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[menu]jumpToBg.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[menu]PopUpBg.JPG"
 Delete "$INSTDIR\Skins\Deluxe\[menu]PopUpFg.JPG"
 Delete "$INSTDIR\Skins\Deluxe\[menu]songMenuBg.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[menu]songMenuSelectBg.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[party]Joker.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[party]playerButton.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[party]playerTeamButton.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[party]pointer.bmp"
 Delete "$INSTDIR\Skins\Deluxe\[party]roundBG1.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[party]roundBG2.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[party]roundBG3.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[party]roundBG4.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[party]roundTeamButton.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[party]scoreBG1.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[party]scoreBG2.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[party]scoreDecoration.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[party]teamPoints.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[party]winDecoration1.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[party]winTeamButton1.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[party]winTeamButton2.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[party]winTeamButton3.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[score]box.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[score]endcap.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[score]level.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[score]levelRound.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[score]Line.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[sing]lineBonusPopUp.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[sing]LyricsBall.bmp"
 Delete "$INSTDIR\Skins\Deluxe\[sing]lyricsHelpBar.bmp"
 Delete "$INSTDIR\Skins\Deluxe\[sing]notesBgLeft.bmp"
 Delete "$INSTDIR\Skins\Deluxe\[sing]notesBgMid.bmp"
 Delete "$INSTDIR\Skins\Deluxe\[sing]notesBgRight.bmp"
 Delete "$INSTDIR\Skins\Deluxe\[sing]notesLeft.bmp"
 Delete "$INSTDIR\Skins\Deluxe\[sing]notesMid.bmp"
 Delete "$INSTDIR\Skins\Deluxe\[sing]notesRight.bmp"
 Delete "$INSTDIR\Skins\Deluxe\[sing]p.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[sing]scoreBg.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[sing]singBarBack.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[sing]singBarBar.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[sing]singBarFront.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[sing]textBar.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[sing]timeBar.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[sing]timeBar1.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[sing]timeBarBG.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[special]bar1.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[special]bar2.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[stat]detailBG1.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[stat]mainBG1.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[stat]mainBG2.jpg"
 Delete "$INSTDIR\Skins\Deluxe\[stat]mainBG3.jpg"

; Delete provided iStar Skin
 Delete "$INSTDIR\Skins\iStar\Apple.ini"
 Delete "$INSTDIR\Skins\iStar\[bg-load]blue.jpg"
 Delete "$INSTDIR\Skins\iStar\[bg-main]blue.jpg"
 Delete "$INSTDIR\Skins\iStar\[bg-menu]blue.jpg"
 Delete "$INSTDIR\Skins\iStar\[button]13.jpg"
 Delete "$INSTDIR\Skins\iStar\[button]alt.jpg"
 Delete "$INSTDIR\Skins\iStar\[button]az.jpg"
 Delete "$INSTDIR\Skins\iStar\[button]enter.jpg"
 Delete "$INSTDIR\Skins\iStar\[button]esc.jpg"
 Delete "$INSTDIR\Skins\iStar\[button]j.jpg"
 Delete "$INSTDIR\Skins\iStar\[button]m.jpg"
 Delete "$INSTDIR\Skins\iStar\[button]navi.jpg"
 Delete "$INSTDIR\Skins\iStar\[button]p.jpg"
 Delete "$INSTDIR\Skins\iStar\[effect]goldenNoteStar.jpg"
 Delete "$INSTDIR\Skins\iStar\[effect]perfectNoteStar.jpg"
 Delete "$INSTDIR\Skins\iStar\[helper]buttonFade.jpg"
 Delete "$INSTDIR\Skins\iStar\[helper]buttonFade2.jpg"
 Delete "$INSTDIR\Skins\iStar\[helper]buttonFade3.JPG"
 Delete "$INSTDIR\Skins\iStar\[helper]buttonFade4.JPG"
 Delete "$INSTDIR\Skins\iStar\[helper]rectangle.jpg"
 Delete "$INSTDIR\Skins\iStar\[icon]calcmedley.jpg"
 Delete "$INSTDIR\Skins\iStar\[icon]cd.jpg"
 Delete "$INSTDIR\Skins\iStar\[icon]error.jpg"
 Delete "$INSTDIR\Skins\iStar\[icon]main.jpg"
 Delete "$INSTDIR\Skins\iStar\[icon]medley.jpg"
 Delete "$INSTDIR\Skins\iStar\[icon]options.jpg"
 Delete "$INSTDIR\Skins\iStar\[icon]party.jpg"
 Delete "$INSTDIR\Skins\iStar\[icon]question.jpg"
 Delete "$INSTDIR\Skins\iStar\[icon]score.jpg"
 Delete "$INSTDIR\Skins\iStar\[icon]search.jpg"
 Delete "$INSTDIR\Skins\iStar\[icon]songmenu.jpg"
 Delete "$INSTDIR\Skins\iStar\[icon]song_duet.jpg"
 Delete "$INSTDIR\Skins\iStar\[icon]stats.jpg"
 Delete "$INSTDIR\Skins\iStar\[icon]video.jpg"
 Delete "$INSTDIR\Skins\iStar\[main]button.jpg"
 Delete "$INSTDIR\Skins\iStar\[main]buttonf.jpg"
 Delete "$INSTDIR\Skins\iStar\[main]buttonmenu1.jpg"
 Delete "$INSTDIR\Skins\iStar\[main]buttonmenu2.jpg"
 Delete "$INSTDIR\Skins\iStar\[main]buttonmenu3.jpg"
 Delete "$INSTDIR\Skins\iStar\[main]buttonmenu31.jpg"
 Delete "$INSTDIR\Skins\iStar\[main]buttonmenu32.jpg"
 Delete "$INSTDIR\Skins\iStar\[main]buttonmenu33.jpg"
 Delete "$INSTDIR\Skins\iStar\[main]buttonmenu34.jpg"
 Delete "$INSTDIR\Skins\iStar\[main]buttonmenu4.jpg"
 Delete "$INSTDIR\Skins\iStar\[main]buttonmenu4a.jpg"
 Delete "$INSTDIR\Skins\iStar\[main]buttonmenu4b.jpg"
 Delete "$INSTDIR\Skins\iStar\[main]buttonmenu4c.jpg"
 Delete "$INSTDIR\Skins\iStar\[main]buttonmenu5.jpg"
 Delete "$INSTDIR\Skins\iStar\[main]buttonmenu6.jpg"
 Delete "$INSTDIR\Skins\iStar\[main]buttonmenu6a.jpg"
 Delete "$INSTDIR\Skins\iStar\[main]buttonmenu6b.jpg"
 Delete "$INSTDIR\Skins\iStar\[main]buttonmenu6c.jpg"
 Delete "$INSTDIR\Skins\iStar\[main]buttonmenu6d.jpg"
 Delete "$INSTDIR\Skins\iStar\[main]buttonmenu6e.jpg"
 Delete "$INSTDIR\Skins\iStar\[main]buttonmenu7.jpg"
 Delete "$INSTDIR\Skins\iStar\[main]buttonmenu8.jpg"
 Delete "$INSTDIR\Skins\iStar\[main]buttonmenu8a.jpg"
 Delete "$INSTDIR\Skins\iStar\[main]buttonmenu8b.jpg"
 Delete "$INSTDIR\Skins\iStar\[main]buttonmenu9.jpg"
 Delete "$INSTDIR\Skins\iStar\[main]buttonmenu9a.jpg"
 Delete "$INSTDIR\Skins\iStar\[main]mainBar.jpg"
 Delete "$INSTDIR\Skins\iStar\[main]playerNumberBox.jpg"
 Delete "$INSTDIR\Skins\iStar\[main]selectbg.jpg"
 Delete "$INSTDIR\Skins\iStar\[main]songCover.jpg"
 Delete "$INSTDIR\Skins\iStar\[main]songSelection1.jpg"
 Delete "$INSTDIR\Skins\iStar\[main]songSelection2.jpg"
 Delete "$INSTDIR\Skins\iStar\[menu]jumpToBg.jpg"
 Delete "$INSTDIR\Skins\iStar\[menu]PopUpBg.JPG"
 Delete "$INSTDIR\Skins\iStar\[menu]PopUpFg.JPG"
 Delete "$INSTDIR\Skins\iStar\[menu]songMenuBg.jpg"
 Delete "$INSTDIR\Skins\iStar\[menu]songMenuSelectBg.jpg"
 Delete "$INSTDIR\Skins\iStar\[party]Joker.jpg"
 Delete "$INSTDIR\Skins\iStar\[party]playerButton.jpg"
 Delete "$INSTDIR\Skins\iStar\[party]playerTeamButton.jpg"
 Delete "$INSTDIR\Skins\iStar\[party]pointer.bmp"
 Delete "$INSTDIR\Skins\iStar\[party]roundBG1.jpg"
 Delete "$INSTDIR\Skins\iStar\[party]roundBG2.jpg"
 Delete "$INSTDIR\Skins\iStar\[party]roundBG3.jpg"
 Delete "$INSTDIR\Skins\iStar\[party]roundBG4.jpg"
 Delete "$INSTDIR\Skins\iStar\[party]roundTeamButton.jpg"
 Delete "$INSTDIR\Skins\iStar\[party]scoreBG1.jpg"
 Delete "$INSTDIR\Skins\iStar\[party]scoreBG2.jpg"
 Delete "$INSTDIR\Skins\iStar\[party]scoreDecoration.jpg"
 Delete "$INSTDIR\Skins\iStar\[party]teamPoints.jpg"
 Delete "$INSTDIR\Skins\iStar\[party]winDecoration1.jpg"
 Delete "$INSTDIR\Skins\iStar\[party]winTeamButton1.jpg"
 Delete "$INSTDIR\Skins\iStar\[party]winTeamButton2.jpg"
 Delete "$INSTDIR\Skins\iStar\[party]winTeamButton3.jpg"
 Delete "$INSTDIR\Skins\iStar\[score]box.jpg"
 Delete "$INSTDIR\Skins\iStar\[score]endcap.jpg"
 Delete "$INSTDIR\Skins\iStar\[score]level.jpg"
 Delete "$INSTDIR\Skins\iStar\[score]levelRound.jpg"
 Delete "$INSTDIR\Skins\iStar\[score]Line.jpg"
 Delete "$INSTDIR\Skins\iStar\[sing]lineBonusPopUp.jpg"
 Delete "$INSTDIR\Skins\iStar\[sing]LyricsBall.bmp"
 Delete "$INSTDIR\Skins\iStar\[sing]lyricsHelpBar.bmp"
 Delete "$INSTDIR\Skins\iStar\[sing]notesBgLeft.bmp"
 Delete "$INSTDIR\Skins\iStar\[sing]notesBgMid.bmp"
 Delete "$INSTDIR\Skins\iStar\[sing]notesBgRight.bmp"
 Delete "$INSTDIR\Skins\iStar\[sing]notesLeft.bmp"
 Delete "$INSTDIR\Skins\iStar\[sing]notesMid.bmp"
 Delete "$INSTDIR\Skins\iStar\[sing]notesRight.bmp"
 Delete "$INSTDIR\Skins\iStar\[sing]p.jpg"
 Delete "$INSTDIR\Skins\iStar\[sing]scoreBg.jpg"
 Delete "$INSTDIR\Skins\iStar\[sing]singBarBack.jpg"
 Delete "$INSTDIR\Skins\iStar\[sing]singBarBar.jpg"
 Delete "$INSTDIR\Skins\iStar\[sing]singBarFront.jpg"
 Delete "$INSTDIR\Skins\iStar\[sing]textBar.jpg"
 Delete "$INSTDIR\Skins\iStar\[sing]timeBar.jpg"
 Delete "$INSTDIR\Skins\iStar\[sing]timeBar1.jpg"
 Delete "$INSTDIR\Skins\iStar\[sing]timeBarBG.jpg"
 Delete "$INSTDIR\Skins\iStar\[special]bar1.jpg"
 Delete "$INSTDIR\Skins\iStar\[special]bar2.jpg"
 Delete "$INSTDIR\Skins\iStar\[stat]detailBG1.jpg"
 Delete "$INSTDIR\Skins\iStar\[stat]mainBG1.jpg"
 Delete "$INSTDIR\Skins\iStar\[stat]mainBG2.jpg"
 Delete "$INSTDIR\Skins\iStar\[stat]mainBG3.jpg"

; Delete provided sounds
 Delete "$INSTDIR\Sounds\Applause.mp3"
 Delete "$INSTDIR\Sounds\Common back.mp3"
 Delete "$INSTDIR\Sounds\Common start.mp3"
 Delete "$INSTDIR\Sounds\credits-outro-tune.mp3"
 Delete "$INSTDIR\Sounds\dismissed.mp3"
 Delete "$INSTDIR\Sounds\menu swoosh.mp3"
 Delete "$INSTDIR\Sounds\option change col.mp3"
 Delete "$INSTDIR\Sounds\rimshot022b.mp3"
 Delete "$INSTDIR\Sounds\PLUGIN_HauDenLukas_Bell.mp3"
 Delete "$INSTDIR\Sounds\select music change music 50.mp3"
 Delete "$INSTDIR\Sounds\select music change music.mp3"
 Delete "$INSTDIR\Sounds\wome-credits-tune.mp3"
  
; Delete provided Themes
 Delete "$INSTDIR\Themes\Blue Sensation.ini"
 Delete "$INSTDIR\Themes\Deluxe.ini"
 Delete "$INSTDIR\Themes\iStar.ini"

; Delete only empty directories:

StrCpy $0 "$INSTDIR\Covers"
Call un.DeleteIfEmpty

StrCpy $0 "$INSTDIR\Fonts"
Call un.DeleteIfEmpty

StrCpy $0 "$INSTDIR\Languages"
Call un.DeleteIfEmpty

StrCpy $0 "$INSTDIR\Plugins"
Call un.DeleteIfEmpty

StrCpy $0 "$INSTDIR\Skins\Blue Sensation"
Call un.DeleteIfEmpty

StrCpy $0 "$INSTDIR\Skins\Deluxe"
Call un.DeleteIfEmpty

StrCpy $0 "$INSTDIR\Skins\iStar"
Call un.DeleteIfEmpty

StrCpy $0 "$INSTDIR\Skins"
Call un.DeleteIfEmpty

StrCpy $0 "$INSTDIR\Songs"
Call un.DeleteIfEmpty

StrCpy $0 "$INSTDIR\Sounds"
Call un.DeleteIfEmpty

StrCpy $0 "$INSTDIR\Themes"
Call un.DeleteIfEmpty

StrCpy $0 "$INSTDIR\Screenshots"
Call un.DeleteIfEmpty

StrCpy $0 "$INSTDIR\Playlists"
Call un.DeleteIfEmpty

StrCpy $0 "$INSTDIR\Recordings"
Call un.DeleteIfEmpty

StrCpy $0 "$INSTDIR\SessionLog"
Call un.DeleteIfEmpty

StrCpy $0 "$INSTDIR"
Call un.DeleteIfEmpty


; Delete created Icons in startmenu

 SetShellVarContext all

 Delete "$SMPROGRAMS\$ICONS_GROUP\Uninstall.lnk"
 Delete "$SMPROGRAMS\$ICONS_GROUP\Deinstallieren.lnk"
 Delete "$SMPROGRAMS\$ICONS_GROUP\Website.lnk"
 Delete "$SMPROGRAMS\$ICONS_GROUP\Internetseite.lnk"
 Delete "$SMPROGRAMS\$ICONS_GROUP\UltraStar Deluxe CMD Edition spielen.lnk"
 Delete "$SMPROGRAMS\$ICONS_GROUP\Play UltraStar Deluxe CMD Edition.lnk"
 Delete "$SMPROGRAMS\$ICONS_GROUP\Readme.lnk"
 Delete "$SMPROGRAMS\$ICONS_GROUP\Lies mich.lnk"
 Delete "$SMPROGRAMS\$ICONS_GROUP\Lizenz.lnk"
 Delete "$SMPROGRAMS\$ICONS_GROUP\License.lnk"

; Delete created Icon on Desktop

Delete "$Desktop\Play UltraStar Deluxe CMD Edition.lnk"
Delete "$Desktop\UltraStar Deluxe CMD Edition spielen.lnk"

StrCpy $0 "$SMPROGRAMS\$ICONS_GROUP"
Call un.DeleteIfEmpty
