# ====================================
#
#   MPSYS mp-boot
#   (C) MPSYS all rights reserved.
#
#   Purpose: Assembler API.
#
# ====================================

[global mpboot_flush_tlb]

mpboot_flush_tlb:
    invlpg
    ret