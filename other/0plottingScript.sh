#mkdir digis
#mkdir clusters
mkdir rechits
cd /data/vami/projects/pilotBlade/uTCA-data/pp-ZeroBias/CMSSW_8_0_20_patch1/src
cmsenv
cd -
make clean
make -Wsign-compare
./PilotHistoMaker
cd digis/
mkdir Cs
mv *.C Cs/.
cd ..
cd clusters/
mkdir Cs
mv *.C Cs/.
cd ..
cd rechits/
mkdir Cs
mv *.C Cs/.
cd ..
