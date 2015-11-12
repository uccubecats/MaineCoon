@echo off
del ..\dist
mkdir ..\dist
for /R ..\build %%F in (*.dll) do copy %%F ..\dist
copy ..\build\*.exe ..\dist
@echo on
for /R ..\dist %%F in (*.exe) do %%F