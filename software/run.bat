@echo off
set JAVA_HOME=C:\Progra~1\Java
set ROOT=%~dp0
set CORE=%ROOT%core

echo ROOT: %ROOT%
echo CORE: %CORE%
echo.

REM Compila Core.java e genera Core.h
echo Compilando Core.java e generando Core.h...
"%JAVA_HOME%\bin\javac.exe" -h "%CORE%" "%CORE%\Core.java"
if ERRORLEVEL 1 goto error

REM Compila Main.java (con classpath che include core)
echo Compilando Main.java...
"%JAVA_HOME%\bin\javac.exe" -cp "%ROOT%;%CORE%" "%ROOT%Main.java"
if ERRORLEVEL 1 goto error

REM Compila funzioni.c in DLL
echo Compilando funzioni.c in funzioni.dll...
cl /I"%JAVA_HOME%\include" /I"%JAVA_HOME%\include\win32" /LD "%CORE%\funzioni.c" /Fe:"%CORE%\funzioni.dll"
if ERRORLEVEL 1 goto error

REM Esegue il programma Java
echo Esecuzione del programma Java...
cd /d "%ROOT%"
java -Djava.library.path="%CORE%" -cp "%ROOT%;%CORE%" Main
if ERRORLEVEL 1 goto error

echo Tutto completato!
pause
goto end

:error
echo Si e' verificato un errore durante la compilazione o esecuzione!
pause

:end