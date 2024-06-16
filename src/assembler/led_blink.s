add x0, x0, #0x3f200004
add x1, x1, #0x00001000
str w1, [x0]
add x2, x2, #0x00004000

str w2, [x0, #6]
ldr x4, #1000000
subs x4, x4, #1
b.ne #0x18
str w3, [x0, #6]

str w2, [x0, #9]
ldr x4, #1000000
subs x4, x4, #1
b.ne #0x2c
str w3, [x0, #9]

b #0x10
