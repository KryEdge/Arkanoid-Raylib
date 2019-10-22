@echo off

Xcopy $(SolutionDir)Assets $(OutDir)Assets /y /s 
Xcopy $(SolutionDir)libs\raylib\bin\raylib.dll $(OutDir) /y /s

echo Se han copiado los archivos
