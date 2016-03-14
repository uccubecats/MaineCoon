export LD_LIBRARY_PATH=/home/tyler/Desktop/pysrc:$LD_LIBRARY_PATH
g++ -fPIC fuzzy.cpp -Lfuzzylite -lfuzzylite -Ifuzzylite -o libPyFuzzy.so -shared
