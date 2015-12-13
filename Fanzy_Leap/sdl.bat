@set path=d:\GnuWin32\bin;%PATH%;
xgettext --force-po -o StringData.pot StringData.cpp
msginit -l zh_CN -o StringData.po -i StringData.pot
@set path=d:\Poedit\bin;%PATH%; 
poedit StringData.po
del StringData.po