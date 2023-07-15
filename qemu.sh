mkdir -p build
meson setup --cross-file=uefi.cross-file build
cd build
ninja

cp /usr/share/ovmf/x64/OVMF.fd .
mkdir -p esp/EFI/BOOT/
cp BOOTX64.EFI esp/EFI/BOOT

qemu-system-x86_64 -drive if=pflash,format=raw,file=OVMF.fd -M accel=kvm:tcg -net none -serial stdio -drive format=raw,file=fat:rw:esp
