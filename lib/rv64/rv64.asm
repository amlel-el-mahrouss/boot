# ====================================
#
#   MPSYS mp-boot
#   (C) MPSYS all rights reserved.
#
#   Purpose: Assembler API for RISC-V
#
# ====================================

.balign 4
.global mpboot_flush_tlb

mpboot_flush_tlb:
    csrr satp, t0
    csrw t0, satp

    ret