SAMPLES=10
cd build
make -j
cd ..

# time bin/PA testcases/scene05_bunny_200.txt output/scene05.bmp $SAMPLES
time bin/PA testcases/scene06_bunny_1k.txt output/scene06_bunny_1k.bmp $SAMPLES
# time bin/PA testcases/scene06_bunny_1k_vn.txt output/scene06_bunny_1k_vn.bmp $SAMPLES
# time bin/PA testcases/scene09_norm.txt output/scene09_norm.bmp $SAMPLES
# time bin/PA testcases/scene12.txt output/scene12.bmp $SAMPLES
# time bin/PA testcases/scene13.txt output/scene13.bmp $SAMPLES
# time bin/PA testcases/scene12_720p.txt output/scene12_720p.bmp $SAMPLES
# time bin/PA testcases/scene15_bunny_200.txt output/scene15_bunny_200.bmp $SAMPLES
# time bin/PA testcases/scene16_global_diff.txt output/scene16_global_diff.bmp $SAMPLES
# time bin/PA testcases/scene16_global.txt output/scene16_global.bmp $SAMPLES
# time bin/PA testcases/scene17_bump.txt output/scene17_bump.bmp $SAMPLES