from distutils.core         import setup
from distutils.extension    import Extension
from Cython.Distutils       import build_ext
import SSD1306

ext = Extension("OledDisp", sources=["pyoleddisp.pyx"], language='c++');

setup(ext_modules=[ext], cmdclass={'build_ext': build_ext});