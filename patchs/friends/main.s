.3ds
.thumb

.open "code.bin", "patched_code.bin", 0x100000

.org 0x102536
  b 0x102556

.org 0x101968
  b 0x101974

.org 0x16129a
  .area 38
    .asciiz "https://nasc.pretendo.cc/ac/"
  .endarea

.org 0x1612C0
  .area 37
    .asciiz "http://nasc.nextendo.online/ac"
  .endarea
.close
