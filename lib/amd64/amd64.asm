# ====================================
#
#   MPSYS mp-boot
#   (C) MPSYS all rights reserved.
#
#   Purpose: Assembler API.
#
# ====================================

[global mp_flush_tlb]

mp_flush_tlb:
    invlpg
    ret