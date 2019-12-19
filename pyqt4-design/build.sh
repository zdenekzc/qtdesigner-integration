test -f Makefile && make clean
python configure.py
make
python run.py
