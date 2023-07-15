project('uefi', 'c')

src = [
	'src/main.c'
]

inc = include_directories('efi')

executable('BOOTX64.EFI', src, include_directories: inc)
