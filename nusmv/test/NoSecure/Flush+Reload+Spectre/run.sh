#cd ../cmake-build-debug
#make
#sudo make install

# cd ../test/
mkdir tmp
rm -rf tmp/*
python auto.py
dir=`ls tmp/`
mkdir ce
rm -rf ce/*
for i in $dir
	do
         ../../../NuSMV tmp/$i > ce/$i.ce
     done
python graph.py >FRS.dot
dot -Tpng -s1 FRS.dot -o FRS.png


