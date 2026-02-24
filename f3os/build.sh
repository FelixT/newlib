mkdir build

cd build

i686-elf-gcc -c ../f3os/syscalls.c -o syscalls.o -ffreestanding -nostdlib
i686-elf-gcc -c ../f3os/crt0.c -o crt0.o -ffreestanding -nostdlib

../configure \
  --target=i686-elf \
  --prefix=/Users/felix/opt/cross/ \
  --disable-multilib \
  --disable-newlib-supplied-syscalls \

make all-target-newlib -j$(nproc)
sudo make install-target-newlib

cp crt0.o ~/opt/cross/i686-elf/lib/crt0.o
cp syscalls.o ~/opt/cross/i686-elf/lib/syscalls.o


# Build and run program:
#i686-elf-gcc \
#  -o ../f3os/test.elf crt0.o ../f3os/test.c syscalls.o \
#  -I$HOME/opt/cross/i686-elf/include -L$HOME/opt/cross/i686-elf/lib \
#  -lc -lm -nostdlib -T ../f3os/test_linker.ld
