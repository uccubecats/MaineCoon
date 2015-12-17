@echo off
cd ..
cd src/hrdint/oleddisp
@echo Building the GpuPixelMapper module...
python "oleddispsetup.py" build_ext --inplace --compiler=mingw32
@echo Building the GpuPixelMapper module...
pause
cd ../../../scripts