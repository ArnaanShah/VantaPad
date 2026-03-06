# \# VantaPad 👽

# 

# <INSERT LOGO HERE>

# 

# A Hackpad made as a part of Hackclub's Blueprint <LINK HACKCLUB BLUEPRINT HERE> program. VantaPad is a sleek black macropad I will use for controlling simple functions on my computer that I currently do by hand. It is one of my first hardware projects and it taught me many valuable skills such as schematic design, PCB design, Firmware programming, and more.

# 

# \## Features ✨

# \*\*Things included in my pad and what they do.\*\*

# 

# \- 3x2 Keypad ⌨️ - Top row is audio control. Bottom row reopens tabs, auto-clicks, and cycles layers  

# \- EC11 Encoder 🔄 - Volume, Tab Scrolling, Brightness

# \- 128x32 ssd1306 OLED Display 📺 - Layer Display, Idle animation, Key press reactions

# \- 3 WS2812B RGB LEDs 🚥 - Breathing effect that shines through the front of the case

# \- Minimal Black Case 🐈‍⬛ - A Hexagonal shape with the logo printed at the bottom

# 

# \## PCB 🛠️

# \*\*The design around my PCB. Includes the schematic, the PCB, and some additions.\*\* 

# 

# I designed my PCB in KiCad 9.0! I loved using this app because it was pretty beginner friendly and intuitive. It also possessed many useful features that meant I didn't have to download another app. 

# 

# Schematic:

# <INSERT IMAGE HERE>

# 

# PCB:

# <INSERT IMAGE HERE>

# 

# 3d VIEW:

# <INSERT IMAGE HERE>

# 

# I used KiCad's built-in Image Converter to make a footprint of my logo:

# <INSERT IMAGE HERE>

# 

# \## CAD 📐✏️

# \*\*The CAD model I made for the case.\*\*

# 

# I made the model of the case in Fusion 360 because I already had some previous experience with it. The case will join together using 6 screws. 4 in the corners of the case and 2 connecting the PCB to the case. The case has a 10 degree upwards tilt for ease of use as well. It has 3 separate parts, the top, the plate, and the bottom. The top has the VantaPad logo embossed near the bottom.

# 

# Renders 📸:

# <INSERT IMAGE ISOMETRIC HERE>

# <INSERT IMAGE TOP FRONT HERE>

# <INSERT IMAGE TOP HERE>

# 

# \## Firmware 💻

# \*\*Overview of the Firmware\*\*

# 

# I wrote the firmware in QMK. This took tons of trial and error but I am very pleased with the final result. The QMK docs can be confusing but I found many resources online that helped me as well. 

# 

# \- The 6 keys are mapped as shown but can be easily changed

# ```

# ║ Previous   ║ Next         ║ Pause       ║

# 

# ║ Reopen Tab ║ Auto Clicker ║ Layer Cycle ║

# ```

# ```// ---------- Keymaps ----------

# const uint16\_t PROGMEM keymaps\[]\[MATRIX\_ROWS]\[MATRIX\_COLS] = {

# &nbsp;   \[\_BASE] = LAYOUT(

# &nbsp;       KC\_MPRV, KC\_MNXT, KC\_MPLY, KC\_MUTE, // Top row + Encoder Button

# &nbsp;       REOPEN\_TAB, AUTO\_CLICKER, KC\_CYCLE\_LAYERS

# &nbsp;   ),

# };

# ```

# \- The rotary encoder controls volume 🔊 on the base layer, scrolls tabs 📑 on the second layer, and controls brightness 🔆 on the third layer 

# &nbsp; - Clicking the encoder always will mute the computer's volume

# ```

# const uint16\_t PROGMEM encoder\_map\[]\[NUM\_ENCODERS]\[2] = {

# &nbsp;   \[\_BASE]   = { ENCODER\_CCW\_CW(KC\_VOLD, KC\_VOLU) },

# &nbsp;   \[\_LAYER1] = { ENCODER\_CCW\_CW(LCTL(KC\_PGUP), LCTL(KC\_PGDN)) },

# &nbsp;   \[\_LAYER2] = { ENCODER\_CCW\_CW(KC\_BRID, KC\_BRIU) },

# };

# ```

# \- The OLED has 2 animations. Animation 1 is the idle animation ⏱️ where the VantaPad alien is slightly growing and shrinking (breathing) with occasional blinks 👀. Animation 2 occurs when a key is pressed and it makes the alien have a slight shocked 😮 face with a lightning bolt above its head for 900 ms. 

# <INSERT IMAGE OF THE ANIMATION HERE>

# \- The OLED also displays useful information ℹ️ to the side of the animation. This includes what layer it is currently using and also displays my name. 

# ```

# oled\_set\_cursor(0, 0);

# oled\_write\_P(PSTR("Arnaan Shah"), false);

# &nbsp;   

# oled\_set\_cursor(0, 2);

# switch (get\_highest\_layer(layer\_state)) {

# &nbsp;   case \_BASE:   oled\_write\_P(PSTR("Layer 1"), false); break;

# &nbsp;   case \_LAYER1: oled\_write\_P(PSTR("Layer 2"), false); break;

# &nbsp;   case \_LAYER2: oled\_write\_P(PSTR("Layer 3"), false); break;

# }

# ```

# 

# \- The RGB LEDS are set to display red and cycle a constant breathing animation

# ```

# void keyboard\_post\_init\_user(void) {

# &nbsp;   rgblight\_enable\_noeeprom();

# &nbsp;   rgblight\_sethsv\_noeeprom(0, 255, 100);

# &nbsp;   rgblight\_mode\_noeeprom(RGBLIGHT\_MODE\_BREATHING + 1); 

# }

# ```

# \## BOM 📦💲

# \*\*List of materials you'll need to buy to make this macropad. Most of these are easily accessible and the overall cost stayed low. Does not include all the tools required to build it.\*\*

# 

# \- 6x Cherry MX Switches

# \- 6x DSA Keycaps

# \- 5x M3x16mm SHCS Bolts

# \- 1X M3x12mm SHCS Bolts

# \- 6x M3 Hex Nuts

# \- 7x 1N4148 DO-35 Diodes

# \- 3x WS2812B LEDs

# \- 1x 0.91" 128x32 OLED Display

# \- 1x EC11 Rotary Encoder

# \- 1x XIAO RP2040

# \- 1x Case (3d printed parts)

# \## Extras 🪄

# \*\*Miscellaneous related things\*\*

# 

# I made the logo design all in Figma and it's based off the "Space Alien" inside Halloween Stickers. 

# <INSERT IMAGE OF LOGO HERE>

# It's honestly one of my favorite parts of the project 😅

# 

# Changes I would still consider making include: 

# 1\. More Information displayed on the OLED - WPM, Time, Date, Volume

# 2\. Adding more animations to the OLED - Spinning alien based on knob, startup screen

# 3\. Making the RGB react - Flash on key press, blink when auto-clicker's active

# 4\. Displaying the PCB through the case somehow

# 

# Some resources I used:

# \- Joe Scotto's Youtube Channel (LIFESAVER 🙏)

# \- QMK Docs

# \- r/MechanicalKeyboards subreddit 

# 

# \# Thanks for reading! If you have any feedback, comments, or questions I would love to hear them and you can always reach out to me!

# <INSERT GOODBYE IMAGE>

# 

# 



