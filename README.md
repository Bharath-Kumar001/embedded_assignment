I don't have prior work experience in PCB design, so there may be some mistakes in the schematic or layout. I’ve done my best to learn and apply the concepts while working on this project. The whole assignment was completed over 2-3 days, including learning KiCad basics, making the symbol and footprint for nPM1100, wiring the schematic, and doing the PCB layout.

This FreeRTOS example shows how two tasks talk using a queue. Task1 sends data (id & val) every 500ms. Task2 gets the data and reacts: id 0 → kills itself id 1: val 0 - boost its prio by 2 (only once) ,,val 1 - reset prio back if boosted,,val 2 -delete itself
Other values just get printed.
