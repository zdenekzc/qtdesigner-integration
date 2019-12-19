mkdir -p build
cd build
qmake-qt5 ../qt5-design.pro || exit 1
make || exit 1
./qt5-design