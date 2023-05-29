.extern isr_handler

.global isr0
.global isr1
.global isr2
.global isr3
.global isr4
.global isr5
.global isr6
.global isr7
.global isr8
.global isr9
.global isr10
.global isr11
.global isr12
.global isr13
.global isr14
.global isr15
.global isr16
.global isr17
.global isr18
.global isr19
.global isr20
.global isr21
.global isr22
.global isr23
.global isr24
.global isr25
.global isr26
.global isr27
.global isr28
.global isr29
.global isr30
.global isr31
.global isr32
.global isr33

.macro pushaq
  push %rax
  push %rbx
  push %rcx
  push %rdx
  push %rbp
  push %rdi
  push %rsi
  push %r8
  push %r9
  push %r10
  push %r11
  push %r12
  push %r13
  push %r14
  push %r15
.endm

.macro popaq
  pop %r15
  pop %r14
  pop %r13
  pop %r12
  pop %r11
  pop %r10
  pop %r9
  pop %r8
  pop %rsi
  pop %rdi
  pop %rbp
  pop %rdx
  pop %rcx
  pop %rbx
  pop %rax
.endm

.macro pushacr
  mov %rax, %cr0
  push %rax
  mov %rax, %cr2
  push %rax
  mov %rax, %cr3
  push %rax
  mov %rax, %cr4
  push %rax
  mov %rax, %cr8
  push %rax
.endm

.macro isr_err n
  push \n
  pushaq
  pushacr
.endm

.macro isr n
  push $0x0
  push \n
  pushaq
  pushacr
.endm

.macro isr_restore
  add $40, %rsp
  popaq
  add $16, %rsp
.endm

.macro isr_body
  cld
  mov %rsp, %rdi
  call isr_handler
  isr_restore
  iretq
.endm

isr0:
  isr 0
  isr_body

isr1:
  isr 1
  isr_body

isr2:
  isr 2
  isr_body

isr3:
  isr 3
  isr_body

isr4:
  isr 4
  isr_body

isr5:
  isr 5
  isr_body

isr6:
  isr 6
  isr_body

isr7:
  isr 7
  isr_body

isr8:
  isr_err 8
  isr_body

isr9:
  isr 9
  isr_body

isr10:
  isr_err 10
  isr_body

isr11:
  isr_err 11
  isr_body

isr12:
  isr_err 12
  isr_body

isr13:
  isr_err 13
  isr_body

isr14:
  isr_err 14
  isr_body

isr15:
  isr 15
  isr_body

isr16:
  isr 16
  isr_body

isr17:
  isr_err 17
  isr_body

isr18:
  isr 18
  isr_body

isr19:
  isr 19
  isr_body

isr20:
  isr 20
  isr_body

isr21:
  isr 21
  isr_body

isr22:
  isr 22
  isr_body

isr23:
  isr 23
  isr_body

isr24:
  isr 24
  isr_body

isr25:
  isr 25
  isr_body

isr26:
  isr 26
  isr_body

isr27:
  isr 27
  isr_body

isr28:
  isr 28
  isr_body

isr29:
  isr 29
  isr_body

isr30:
  isr_err 30
  isr_body

isr31:
  isr 31
  isr_body

isr32:
  isr 32
  isr_body

isr33:
  isr 33
  isr_body
