read ax
read bx
je 8 ax bx
jg 6 ax bx
sub ax bx
jmp 2
sub bx ax
jmp 2
print ax