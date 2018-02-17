## Description

I presume you have an IDE, in this example I use SW4STM32 (Eclipse), STM32CubeMX and prepared workspace, maybe with the name "ucg".
  
Start STM32CubeMX, open a new Project, select your board/MCU, activate SPI1 and choose the pins like this. ![Pinout](https://github.com/harebit/STM32CubeMX_and_ucglib/blob/master/Pinout.JPG)  
The configuration for SPI is "Transmit Only Master" for Mode and "Disable" for Harware NSS Signal.
"NSS" means Slave Select (or Chip Select) is active low, we will control the signal by software. Configure the rest of the Project Settings as you see in the pictures,  
![SPI-Config](https://github.com/harebit/STM32CubeMX_and_ucglib/blob/master/SPI-Config.JPG?raw=true)  ![GPIO](https://github.com/harebit/STM32CubeMX_and_ucglib/blob/master/GPIO.JPG?raw=true)  

give your project a name e.g. "dora", choose your IDE, here is SW4STM32 with a mark at "Generate Under Root" (it's a simpler structure, but only useful for one project in the workspace). Start "Generate Code" and open the project.  
 
Download ucglib from [github.com/olikraus/ucglib](https://github.com/olikraus/ucglib), we need only the folder "csrc".  
Import (_don't copy with the explorer_) to the folder "inc". Select "General -- File System" and from "\ucglib-master\csrc", select "ucg.h" and finish this. 
In the same way import "ucg_com_stm32_hal.h" from this repository.  
Then import all c-files from "\ucglib-master\csrc" to the folder "src", next import "main.c","ucg_com_stm32_hal.c" and "examples.c" from this repository.  

If you compile the project, you will get an error. "Flash overflowed", don't be worry!
The Flash overflowed because of too many fonts in the file "ucg_pixel_font_data.c", delete a lot of fonts (a simpler way is import the file "ucg_pixel_font_data.c" from this repository).  
In the file ucg.h we have to delete all declarations for the fonts that we have deleted (or download ucg.h from this repository).   

Now you can use all drivers for displays are listed in "src". I have a display with a ST7735 driver, but with a different count of pixel, so I make some amendments.  
With the driver "ucg_dev_tft_widthxheight_st7735.c" you can choosen the count of pixels, in my case I choose 132x132. You can download from this repository.  

Compile the project and program your controller.  

The display should look like this.![Nucleo-ST7735](https://github.com/harebit/STM32CubeMX_and_ucglib/blob/master/Nucleo-ST7735.JPG?raw=true)


harebit
