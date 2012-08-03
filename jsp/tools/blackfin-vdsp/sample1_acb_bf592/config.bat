rem APPNAME アプリケーション名
rem CFGPATH     cfg.exeが置いてあるディレクトリ
rem VDSPPATH    VisualDSP++のインストールディレクトリ
rem JSPPATH     TOPPERS/JSPのディレクトリ
rem CPATH   Blackfin CPU依存部のディレクトリ
rem SPATH   システム依存部のディレクトリ

set APPNAME=sample1
set CFGPATH=X:\Work\jsp
set VDSPPATH=C:\Program Files\Analog Devices\VisualDSP 5.0
set JSPPATH=X:\Work\jsp
set CPATH=%JSPPATH%\config\blackfin
set SPATH=%CPATH%\ezkit_bf592;%CPATH%\_common_bf592

"%VDSPPATH%\pp.exe" %APPNAME%.cfg -D__ECC__ -D__ADSPLPBLACKFIN__ -I"%CPATH%;%SPATH%;%JSPPATH%\systask;%JSPPATH%\include;" > %APPNAME%_pp.cfg
"%CFGPATH%\cfg.exe" %APPNAME%_pp.cfg
del %APPNAME%_pp.cfg
