from distutils.core         import setup
from distutils.extension    import Extension
from Cython.Distutils       import build_ext
import gaugette.ssd1306

ext = Extension("OledDisp", sources=["oleddisp.pyx"], include_dirs=[gaugette.ssd1306.get_include()], language='c++');

setup(ext_modules=[ext], cmdclass={'build_ext': build_ext});