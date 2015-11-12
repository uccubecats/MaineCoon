#rm -r ../dist
mkdir ../dist
for file in $(find ../build -name "*.so" -executable -type f); do
	cp $file ../dist
done
for file in $(find ../build -maxdepth 1 ! -name "*.*" -executable -type f); do
	cp $file ../dist
	#./../dist/$file
done
