rem APPNAME �A�v���P�[�V������
rem CFGPATH     cfg.exe���u���Ă���f�B���N�g��
rem VDSPPATH    VisualDSP++�̃C���X�g�[���f�B���N�g��
rem JSPPATH     TOPPERS/JSP�̃f�B���N�g��
rem CPATH   Blackfin CPU�ˑ����̃f�B���N�g��
rem SPATH   �V�X�e���ˑ����̃f�B���N�g��

set APPNAME=sample1
set CFGPATH=X:\Work\jsp\cfg
set VDSPPATH=C:\Program Files\Analog Devices\VisualDSP 5.0
set JSPPATH=X:\Work\jsp
set CPATH=%JSPPATH%\config\blackfin
set SPATH=%CPATH%\ezkit_bf518;%CPATH%\_common_bf518

"%VDSPPATH%\pp.exe" %APPNAME%.cfg -D__ECC__ -D__ADSPLPBLACKFIN__ -I"%CPATH%;%SPATH%;%JSPPATH%\systask;%JSPPATH%\include;" > %APPNAME%_pp.cfg
"%CFGPATH%\cfg.exe" %APPNAME%_pp.cfg
del %APPNAME%_pp.cfg
