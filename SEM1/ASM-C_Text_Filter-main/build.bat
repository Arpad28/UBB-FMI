nasm -fwin32 modul_1.asm -o modul_1.obj
nasm -fwin32 modul_2.asm -o modul_2.obj
cl main.c /link modul_1.obj modul_2.obj