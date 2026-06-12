# STM32F407 Interview Questions and Answers

## 1) What is the difference between .text, .rodata, .data, and .bss?
**Answer:**
- **.text**: Executable program instructions.
- **.rodata**: Read-only constants (strings, const data).
- **.data**: Initialized global/static variables (run in RAM, initial values stored in Flash image).
- **.bss**: Uninitialized (or zero-initialized) global/static variables (allocated in RAM, zeroed at startup).

## 2) If .data runs from RAM, why does it still occupy Flash size in the image?
**Answer:**
- Because startup code needs initial values for .data.
- The linker stores these initial values in Flash (LMA), and Reset_Handler copies them to RAM (VMA) before main().

## 3) What is the role of Reset_Handler during startup?
**Answer:**
- Set initial stack pointer.
- Copy .data from Flash to RAM.
- Zero .bss.
- Optionally run system init and C/C++ runtime init.
- Call main().

## 4) Why is the interrupt vector table usually placed at 0x08000000?
**Answer:**
- On STM32F4 default boot-from-Flash, the core expects vectors at the Flash base.
- First entry is initial MSP value, second is Reset_Handler address.

## 5) What is the difference between VMA and LMA?
**Answer:**
- **VMA (Virtual Memory Address):** where section executes at runtime.
- **LMA (Load Memory Address):** where section is stored in the load image.
- Example: .data has VMA in RAM and LMA in Flash.

## 6) Why does .data in Flash linker script use AT > FLASH but run in RAM?
**Answer:**
- `>RAM` defines runtime location.
- `AT>FLASH` defines where initializer bytes are stored in the binary.
- Startup copies from Flash source to RAM destination.

## 7) What happens if stack + heap + .bss + .data exceed RAM?
**Answer:**
- Linker may fail with region overflow.
- If it links but runtime usage exceeds limits, you can get stack corruption, hard faults, random behavior, or resets.

## 8) What is CCMRAM on STM32F407, and what are its limitations?
**Answer:**
- Core-Coupled Memory at 0x10000000, fast RAM for CPU access.
- Not DMA-accessible on STM32F4, so DMA buffers should usually be in normal SRAM.

## 9) Why must peripheral clocks be enabled before accessing GPIO registers?
**Answer:**
- Without enabling RCC clock for that peripheral, register accesses may read as zero, not latch writes, or cause undefined behavior.

## 10) Why are register fields often accessed with read-modify-write masks?
**Answer:**
- To change only target bits while preserving other bits.
- Typical sequence: clear field mask, then set new value.

## 11) What can go wrong if function definitions are placed in a header instead of a .c file?
**Answer:**
- Multiple translation units include that header.
- Linker may report multiple definition errors for non-static functions.
- Best practice: prototypes in .h, implementations in .c.

## 12) How would you verify where a function or variable is placed in memory?
**Answer:**
- Check linker map file (`*.map`).
- Use tools like `arm-none-eabi-objdump -h` and `arm-none-eabi-nm`.
- Inspect section placement and symbol addresses.

## 13) What is the difference between execution from Flash and execution from RAM?
**Answer:**
- **Flash execution:** non-volatile, persistent after power cycle, standard deployment.
- **RAM execution:** faster for some cases and debug experiments, but volatile (lost on reset/power cycle).

## 14) Why are peripheral register struct members declared volatile?
**Answer:**
- Hardware can change register values asynchronously.
- `volatile` prevents compiler from optimizing away required loads/stores.

## 15) In your current header, what is suspicious about `DISABLE` being 2 instead of 0?
**Answer:**
- Many APIs and condition checks assume enable/disable as 1/0.
- Using 2 can break logic like `if(flag)` or bit writes that expect binary state.
- Safer convention: `ENABLE 1`, `DISABLE 0`.

## 16) Where is this project code flashed with your FLASH linker script?
**Answer:**
- Vector table, .text, and .rodata are placed in internal Flash at **0x08000000**.
- Initialized .data values are stored in Flash, copied to RAM at startup.
- .bss, heap, and stack live in SRAM (0x20000000 region).

## 17) Why do you have both FLASH and RAM linker scripts?
**Answer:**
- **FLASH linker script:** normal production/debug flow where image is programmed to non-volatile Flash.
- **RAM linker script:** special debug/run mode where code sections are linked to RAM for temporary execution.
