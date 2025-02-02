.3ds
.thumb

.include "adr.s"

.open "code.bin", "patched_code.bin", 0x100000

.org 0x10e4f8
  .area 152
    get_account_url:
      push { r0, r1, r2, r3, r4, lr }
      mov r4, r0
      mov r0, sp
      add r1, sp, #0x8
      add r2, sp, #0x4
      bl frd_get_server_types
      mov r0, sp
      ldrb r0, [r0]
      
      cmp r0, #0x0
      beq @set_nintendo_url
      cmp r0, #0x1 
      beq @set_pretendo_url
      cmp r0, #0x2
      beq @set_nextendo_url

      b @end

    @set_nintendo_url:
      adr r1, nintendo_url
      b @end

    @set_pretendo_url:
      adr r1, pretendo_url
      b @end

    @set_nextendo_url:
      adr r1, nextendo_url
      b @end

    @end:
      mov r2, #0x0
      add r0, r4, #0x4
      bl set_base_account_url
      mov r0, #0x0
      pop { r0, r1, r2, r3, r4, pc }

    nintendo_url:
      .asciiz "https://account.nintendo.net/v1/api/"

    .align 4
    pretendo_url:
      .asciiz "https://account.pretendo.cc/v1/api/"

    .align 4
    nextendo_url:
      .asciiz "http://account.nextendo.online/v1/api/"
  .endarea
.close
