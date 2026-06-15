## Bear Tamagotchi

- PCB-based tamagotchi virtual pet with XIAO-ESP32-C3 by Heona Liu

## About This Project
- This follows the tutorial by [TaniWankenobi](https://github.com/TaniWanKenobi)

# PCB Design:
Images of PCB Design are below:
![bear-pcb-image](image.png)

# Parts Used:
[XIAO-ESP32-C3](https://wiki.seeedstudio.com/XIAO_ESP32C3_Getting_Started/)
Buzzer: [XHXDZ 1207-P6.5MM](https://www.lcsc.com/product-detail/C49246964.html)
Switches: [BZCN TSC016A04518A](https://www.lcsc.com/product-detail/C2888493.html)
0.96" Oled Screen: [HS HS96L03W2C03](https://www.lcsc.com/product-detail/C5248080.html)


## Why I Made This Project
- I made this project because I am relatively new to hardware and thought this would be a good project to get some experience working with. This is also my first time using KiCad and working with the interface. First hardware project so everything was pretty much a learning process. It took many trial and errors like learning how to solve DRC errors, rerouting, and being very confused at some points.

# Things I Learned In Throughout Project:
- GND in the schematic usually faces down and power/voltage faces up.
- This was the first time I worked with KiCad Interface. I learned about how to flip pieces between f.cu and b.cu of the board. Additionally, I learned how to maneuver between the schematic and pcb version. I learned that there are differences between symbols and footprints. 
- After placing pieces, I learned about how to edit individual footprints when there were mismatches. I also learned how to reroute the connection between pieces. Placing vias allowed me to move between the front and back copper. 
- Then after everything is successfully rerouted, I ran DRC checker and worked my way to fix the DRC errors. After finally getting 0 errors, I exported gerber files and .STEP file to which I imported into OnShape. 

# Credits:
- This follows the tutorial by [TaniWankenobi](https://github.com/TaniWanKenobi)
- Case tutorial (for reference) by [Pcb Cupid](https://www.youtube.com/watch?v=7FC-pByCCXM) on YouTube

# BOM:
 