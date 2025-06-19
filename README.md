
# Embedded Assignment – PCB Design & FreeRTOS

This repository includes:

1. **nPM1100 Evaluation Board** (PCB Design – KiCad 9)
2. **FreeRTOS Task Communication Example**
---
## 1. nPM1100 Evaluation Board

- Designed in **KiCad 9**
- 3.0V output, 200mA charge current
- 35mm x 35mm, all SMD components (top-mounted)

**Files:**
- `npm1100_eval_schematic.kicad_sch(schematic)
- `npm1100_eval_layout.kicad_pcb(PCB layout)
- `npm1100_eval_bom.csv`
- 
## 2. FreeRTOS Task Example
Demonstrates task-to-task queue communication.
**Logic:**
- `Task1` sends (ID, value) every 500ms
- `Task2` acts based on value (kill/reset/boost priority)
- 
**File:**
- `freertos_queue_example.c`
---
## Tools Used

- KiCad 9  
- FreeRTOS  
- SnapEDA (footprints)
---
## Author

**BharathKumar M**
