ldr w0, address
ldr w1, fsel
str w1, [x0, #4]
ldr w2, gpset

loop:
str w2, [x0, #0x1c]
ldr w3, delayimm
delay1:
subs w3, w3, #1
b.ne delay1

str w2, [x0, #0x28]
ldr w3, delayimm
delay2:
subs w3, w3, #1
b.ne delay2

b loop

address:
.int 0x3f200000
fsel:
.int 0x8000
gpset:
.int 0x8000
delayimm:
.int 0x4FFFFF

