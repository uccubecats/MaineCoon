@echo off
cd ..

@echo Building the OLEDDisplay module...
cd src/hrdint/oleddisp
python "oleddispsetup.py" build_ext --inplace --compiler=mingw32
del /s *.pyc
del /s *.pyd
rd /s /q build
@echo Building the OLEDDisplay module...

pause
cd ../../../scripts