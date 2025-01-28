.3ds
.thumb

.open "code.bin", "patched_code.bin", 0x100000

.org 0x16129a
  .area 38
    .asciiz "http://nasc.nextendo.online/ac/"
  .endarea
.close