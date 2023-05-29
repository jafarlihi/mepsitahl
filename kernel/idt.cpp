#include "idt.hpp"
#include "libk.hpp"
#include "console.hpp"
#include <stdint.h>

typedef struct {
  uint64_t r15;
  uint64_t r14;
  uint64_t r13;
  uint64_t r12;
  uint64_t r11;
  uint64_t r10;
  uint64_t r9;
  uint64_t r8;
  uint64_t rsi;
  uint64_t rdi;
  uint64_t rbp;
  uint64_t rdx;
  uint64_t rcx;
  uint64_t rbx;
  uint64_t rax;
} __attribute__((packed)) registers;

typedef struct {
  uint64_t cr8;
  uint64_t cr4;
  uint64_t cr3;
  uint64_t cr2;
  uint64_t cr0;
} __attribute__((packed)) control_registers;

typedef struct {
  control_registers sys_ctrl_regs;
  registers regs;
  uint64_t trap_number;
  uint64_t error_code;
  uint64_t rip;
  uint64_t cs;
  uint64_t rflags;
  uint64_t rsp;
  uint64_t ss;
} __attribute__((packed)) interrupt_stack_frame;

typedef struct idt_entry {
  uint16_t low_offset;
  uint16_t target_selector;
  uint8_t ist_ign_res;
  uint8_t attr;
  uint16_t mid_offset;
  uint32_t high_offset;
  uint32_t reserved;
} __attribute__((packed)) idt_entry;

typedef struct idt_pointer {
  uint16_t limit;
  uintptr_t addr;
} __attribute__((packed)) idt_pointer;

__attribute((aligned(0x10))) static idt_entry idt64_table[256];
static idt_pointer idt64_table_pointer;

static const char *exception_strings[] = {
  "#DE: Integer Divide-by-Zero Exception",
  "#DB: Debug exception",
  "Non-maskable interrupt",
  "#BP: Breakpoint Exception (INT 3)",
  "#OF: Overflow Exception (INTO instruction)",
  "#BR: Bound-Range Exception (BOUND instruction)",
  "#UD: Invalid opcode exception",
  "#NM: Device-Not-Available Exception",
  "#DF: Double-Fault Exception",
  "Coprocessor segment overrun (reserved in AMD64)",
  "#TS: Invalid-TSS Exception",
  "#NP: Segment-Not-Present Exception",
  "#SS: Stack exception",
  "#GP: General-Protection exception",
  "#PF: Page-Fault exception",
  "(Reserved)",
  "#MF: x87 FPU Floating-Point error",
  "#AC: Alignment-Check exception",
  "#MC: Machine-Check exception",
  "#XM: SIMD Floating-Point exception",
  "#VE: Virtualisation Exception",
  "#CP: Control-Protection Exception",
};

extern "C" void isr0(void);
extern "C" void isr1(void);
extern "C" void isr2(void);
extern "C" void isr3(void);
extern "C" void isr4(void);
extern "C" void isr5(void);
extern "C" void isr6(void);
extern "C" void isr7(void);
extern "C" void isr8(void);
extern "C" void isr9(void);
extern "C" void isr10(void);
extern "C" void isr11(void);
extern "C" void isr12(void);
extern "C" void isr13(void);
extern "C" void isr14(void);
extern "C" void isr15(void);
extern "C" void isr16(void);
extern "C" void isr17(void);
extern "C" void isr18(void);
extern "C" void isr19(void);
extern "C" void isr20(void);
extern "C" void isr21(void);
extern "C" void isr22(void);
extern "C" void isr23(void);
extern "C" void isr24(void);
extern "C" void isr25(void);
extern "C" void isr26(void);
extern "C" void isr27(void);
extern "C" void isr28(void);
extern "C" void isr29(void);
extern "C" void isr30(void);
extern "C" void isr31(void);
extern "C" void isr32(void);
extern "C" void isr33(void);

__attribute__((always_inline)) static void load_idt(idt_pointer *idt_ptr) {
  asm volatile ("lidt %0 \n" :: "m" (*idt_ptr) : "memory");
}

static void config_isr(uint8_t isr_number, uintptr_t isr) {
  idt_entry entry = {
    .low_offset = (uint16_t)extract_bit_chunk(0, 15, isr),
    .target_selector = 8,
    .ist_ign_res = 0,
    .attr = 0x8e,
    .mid_offset = (uint16_t)extract_bit_chunk(16, 31, isr),
    .high_offset = (uint16_t)extract_bit_chunk(32, 63, isr),
    .reserved = 0
  };
  idt64_table[isr_number] = entry;
}

void init_idt(void) {
  idt64_table_pointer.addr = (uintptr_t)&idt64_table;
  idt64_table_pointer.limit = sizeof(idt_entry) * ARR_SIZE(idt64_table) - 1;

  config_isr(0, (uintptr_t) &isr0);
  config_isr(1, (uintptr_t) &isr1);
  config_isr(2, (uintptr_t) &isr2);
  config_isr(3, (uintptr_t) &isr3);
  config_isr(4, (uintptr_t) &isr4);
  config_isr(5, (uintptr_t) &isr5);
  config_isr(6, (uintptr_t) &isr6);
  config_isr(7, (uintptr_t) &isr7);
  config_isr(8, (uintptr_t) &isr8);
  config_isr(9, (uintptr_t) &isr9);
  config_isr(10, (uintptr_t) &isr10);
  config_isr(11, (uintptr_t) &isr11);
  config_isr(12, (uintptr_t) &isr12);
  config_isr(13, (uintptr_t) &isr13);
  config_isr(14, (uintptr_t) &isr14);
  config_isr(15, (uintptr_t) &isr15);
  config_isr(16, (uintptr_t) &isr16);
  config_isr(17, (uintptr_t) &isr17);
  config_isr(18, (uintptr_t) &isr18);
  config_isr(19, (uintptr_t) &isr19);
  config_isr(20, (uintptr_t) &isr20);
  config_isr(21, (uintptr_t) &isr21);
  config_isr(22, (uintptr_t) &isr22);
  config_isr(23, (uintptr_t) &isr23);
  config_isr(24, (uintptr_t) &isr24);
  config_isr(25, (uintptr_t) &isr25);
  config_isr(26, (uintptr_t) &isr26);
  config_isr(27, (uintptr_t) &isr27);
  config_isr(28, (uintptr_t) &isr28);
  config_isr(29, (uintptr_t) &isr29);
  config_isr(30, (uintptr_t) &isr30);
  config_isr(31, (uintptr_t) &isr31);
  config_isr(32, (uintptr_t) &isr32);
  config_isr(33, (uintptr_t) &isr33);

  load_idt(&idt64_table_pointer);

  asm volatile ("sti");
}

extern "C" void isr_handler(interrupt_stack_frame *interrupt_frame) {
  asm volatile ("cli");
  //char trap_number[sizeof(interrupt_frame->trap_number)];
  //memcpy(trap_number, &interrupt_frame->trap_number, sizeof(interrupt_frame->trap_number));
  //char error_code[sizeof(interrupt_frame->trap_number)];
  //memcpy(trap_number, &interrupt_frame->error_code, sizeof(interrupt_frame->error_code));
  console->print_line("Interrupt processed");
  asm volatile ("sti");
}
