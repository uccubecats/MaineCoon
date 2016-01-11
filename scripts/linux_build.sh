rm -r ../build
rm -r ../dist
mkdir ../build
cd ../build
cmake ../src
make
cd ../scripts
