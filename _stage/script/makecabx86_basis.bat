@echo off
mkdir ..\..\..\time\iexca2\
mkdir ..\..\..\time\iexca2\x86
del ..\..\..\time\iexca2\x86\iexca2.cab
del ..\..\..\time\iexca2\x86\iexca2.dll
del ..\..\..\time\iexca2\x86\aqua.dll
del ..\..\..\time\iexca2\x86\aura.dll
del ..\..\..\time\iexca2\x86\aurasqlite.dll
del ..\..\..\time\iexca2\x86\axis.dll
del ..\..\..\time\iexca2\x86\axisbzip2.dll
del ..\..\..\time\iexca2\x86\axisidn.dll
del ..\..\..\time\iexca2\x86\axisopenssl.dll
del ..\..\..\time\iexca2\x86\axiszlib.dll
del ..\..\..\time\iexca2\x86\base.dll
del ..\..\..\time\iexca2\x86\msvcp120d.dll
del ..\..\..\time\iexca2\x86\msvcr120d.dll
del ..\..\..\time\iexca2\x86\vcomp120d.dll
del ..\..\..\time\iexca2\x86\draw2d_gdiplus.dll
del ..\..\..\time\iexca2\x86\app.install.exe
copy ..\..\..\stage\x86\iexca2.dll ..\..\..\time\iexca2\x86\iexca2.dll
copy ..\..\..\stage\x86\aqua.dll ..\..\..\time\iexca2\x86\aqua.dll
copy ..\..\..\stage\x86\aura.dll ..\..\..\time\iexca2\x86\aura.dll
copy ..\..\..\stage\x86\aurasqlite.dll ..\..\..\time\iexca2\x86\aurasqlite.dll
copy ..\..\..\stage\x86\axis.dll ..\..\..\time\iexca2\x86\axis.dll
copy ..\..\..\stage\x86\axisbzip2.dll ..\..\..\time\iexca2\x86\axisbzip2.dll
copy ..\..\..\stage\x86\axisidn.dll ..\..\..\time\iexca2\x86\axisidn.dll
copy ..\..\..\stage\x86\axisopenssl.dll ..\..\..\time\iexca2\x86\axisopenssl.dll
copy ..\..\..\stage\x86\axiszlib.dll ..\..\..\time\iexca2\x86\axiszlib.dll
copy ..\..\..\stage\x86\base.dll ..\..\..\time\iexca2\x86\base.dll
copy ..\..\..\stage\x86\msvcp120d.dll ..\..\..\time\iexca2\x86\msvcp120d.dll
copy ..\..\..\stage\x86\msvcr120d.dll ..\..\..\time\iexca2\x86\msvcr120d.dll
copy ..\..\..\stage\x86\vcomp120d.dll ..\..\..\time\iexca2\x86\vcomp120d.dll
copy ..\..\..\stage\x86\draw2d_gdiplus.dll ..\..\..\time\iexca2\x86\draw2d_gdiplus.dll
copy ..\..\..\stage\x86\app.install.exe ..\..\..\time\iexca2\x86\app.install.exe
..\..\..\platform\thirdparty\binary\signtool sign /f "X:\sensitive\sensitive\certificate\ca2.p12" /p none ..\..\..\time\iexca2\x86\iexca2.dll
..\..\..\platform\thirdparty\binary\signtool sign /f "X:\sensitive\sensitive\certificate\ca2.p12" /p none ..\..\..\time\iexca2\x86\aqua.dll
..\..\..\platform\thirdparty\binary\signtool sign /f "X:\sensitive\sensitive\certificate\ca2.p12" /p none ..\..\..\time\iexca2\x86\aura.dll
..\..\..\platform\thirdparty\binary\signtool sign /f "X:\sensitive\sensitive\certificate\ca2.p12" /p none ..\..\..\time\iexca2\x86\aurasqlite.dll
..\..\..\platform\thirdparty\binary\signtool sign /f "X:\sensitive\sensitive\certificate\ca2.p12" /p none ..\..\..\time\iexca2\x86\axis.dll
..\..\..\platform\thirdparty\binary\signtool sign /f "X:\sensitive\sensitive\certificate\ca2.p12" /p none ..\..\..\time\iexca2\x86\axisbzip2.dll
..\..\..\platform\thirdparty\binary\signtool sign /f "X:\sensitive\sensitive\certificate\ca2.p12" /p none ..\..\..\time\iexca2\x86\axisidn.dll
..\..\..\platform\thirdparty\binary\signtool sign /f "X:\sensitive\sensitive\certificate\ca2.p12" /p none ..\..\..\time\iexca2\x86\axisopenssl.dll
..\..\..\platform\thirdparty\binary\signtool sign /f "X:\sensitive\sensitive\certificate\ca2.p12" /p none ..\..\..\time\iexca2\x86\axiszlib.dll
..\..\..\platform\thirdparty\binary\signtool sign /f "X:\sensitive\sensitive\certificate\ca2.p12" /p none ..\..\..\time\iexca2\x86\base.dll
..\..\..\platform\thirdparty\binary\signtool sign /f "X:\sensitive\sensitive\certificate\ca2.p12" /p none ..\..\..\time\iexca2\x86\msvcp120d.dll
..\..\..\platform\thirdparty\binary\signtool sign /f "X:\sensitive\sensitive\certificate\ca2.p12" /p none ..\..\..\time\iexca2\x86\msvcr120d.dll
..\..\..\platform\thirdparty\binary\signtool sign /f "X:\sensitive\sensitive\certificate\ca2.p12" /p none ..\..\..\time\iexca2\x86\vcomp120d.dll
..\..\..\platform\thirdparty\binary\signtool sign /f "X:\sensitive\sensitive\certificate\ca2.p12" /p none ..\..\..\time\iexca2\x86\draw2d_gdiplus.dll
..\..\..\platform\thirdparty\binary\signtool sign /f "X:\sensitive\sensitive\certificate\ca2.p12" /p none ..\..\..\time\iexca2\x86\app.install.exe
IF NOT EXIST ..\..\..\time\iexca2\x86\iexca2.cab ECHO Deleted iexca2.cab
..\..\..\platform\thirdparty\binary\cabarc N ..\..\..\time\iexca2\x86\iexca2.cab ..\..\..\time\iexca2\x86\iexca2.inf ..\..\..\time\iexca2\x86\msvcp120d.dll ..\..\..\time\iexca2\x86\msvcr120d.dll ..\..\..\time\iexca2\x86\vcomp120d.dll ..\..\..\time\iexca2\x86\draw2d_gdiplus.dll ..\..\..\time\iexca2\x86\aqua.dll ..\..\..\time\iexca2\x86\aura.dll ..\..\..\time\iexca2\x86\aurasqlite.dll ..\..\..\time\iexca2\x86\axis.dll ..\..\..\time\iexca2\x86\axisbzip2.dll ..\..\..\time\iexca2\x86\axisidn.dll ..\..\..\time\iexca2\x86\axisopenssl.dll ..\..\..\time\iexca2\x86\axiszlib.dll ..\..\..\time\iexca2\x86\base.dll ..\..\..\time\iexca2\x86\iexca2.dll ..\..\..\time\iexca2\x86\app.install.exe
IF NOT EXIST ..\..\..\time\iexca2\x86\iexca2.cab ECHO ERROR WAS HAPPEND!!! 
IF EXIST ;.\..\..\time\iexca2\x86\iexca2.cab ECHO Copy was successfully
..\..\..\platform\thirdparty\binary\signtool sign /f "X:\sensitive\sensitive\certificate\ca2.p12" /p none ..\..\..\time\iexca2\x86\iexca2.cab