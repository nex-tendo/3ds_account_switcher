.macro adr,reg,loc
  add reg, pc, loc - org() - 2 ; - 2 for the instruction
  .endmacro