# VantaPad 👽

<img width="1302" height="654" alt="VantaPadLogoImage" src="https://github.com/user-attachments/assets/2348d824-5976-495d-8eea-dfe12df2e56e" />

A Hackpad made as a part of [Hackclub's Blueprint](https://blueprint.hackclub.com/home) program. VantaPad is a sleek black macropad I will use for controlling simple functions on my computer that I currently do by hand. It is one of my first hardware projects and it taught me many valuable skills such as schematic design, PCB design, Firmware programming, and more.

## Features ✨
**Things included in my pad and what they do.**

- 3x2 Keypad ⌨️ - Top row is audio control. Bottom row reopens tabs, auto-clicks, and cycles layers  
- EC11 Encoder 🔄 - Volume, Tab Scrolling, Brightness
- 128x32 ssd1306 OLED Display 📺 - Layer Display, Idle animation, Key press reactions
- 3 WS2812B RGB LEDs 🚥 - Breathing effect that shines through the front of the case
- Minimal Black Case 🐈‍⬛ - A Hexagonal shape with the logo printed at the bottom

## PCB 🛠️
**The design around my PCB. Includes the schematic, the PCB, and some additions.** 

I designed my PCB in KiCad 9.0! I loved using this app because it was pretty beginner friendly and intuitive. It also possessed many useful features that meant I didn't have to download another app. 

Schematic: <img width="1783" height="1225" alt="SchematicImage" src="https://github.com/user-attachments/assets/4491e005-9162-469c-b241-5e3bb63cd14c" /> 

PCB: <img width="1321" height="1080" alt="PCBImage" src="https://github.com/user-attachments/assets/30e7dabf-890f-4603-abc4-71eb7b9fd0c7" />

3d VIEW: <img width="1848" height="1195" alt="Top3DPCBImage" src="https://github.com/user-attachments/assets/e94f7c59-11d2-4d6f-bdea-9abc10edda45" /> <img width="1790" height="1152" alt="Bottom3dPCBImage 2026-02-26 213746" src="https://github.com/user-attachments/assets/8bc98427-ab92-4869-b239-a926d7c368be" /> 

I used KiCad's built-in Image Converter to make a footprint of my logo:
<img width="2111" height="1003" alt="LogoFootprintImage" src="https://github.com/user-attachments/assets/d5defac8-bcf9-48b0-93ca-87eded2744c6" />

## CAD 📐✏️
**The CAD model I made for the case.**

I made the model of the case in Fusion 360 because I already had some previous experience with it. The case will join together using 6 screws. 4 in the corners of the case and 2 connecting the PCB to the case. The case has a 10 degree upwards tilt for ease of use as well. It has 3 separate parts, the top, the plate, and the bottom. The top has the VantaPad logo embossed near the bottom.

Renders 📸:
<img width="1707" height="818" alt="VantaPadAngledImage" src="https://github.com/user-attachments/assets/df1ffe37-30e1-4f40-a8a6-7bd2144d590e" />
<img width="1707" height="818" alt="VantaPadIsometricImage" src="https://github.com/user-attachments/assets/2dd27e0b-25c3-461d-91e8-696fb7808ba0" />
<img width="1707" height="818" alt="VantaPadFrontTopImage" src="https://github.com/user-attachments/assets/7c91b467-1b47-4856-8c26-241c2f9b17bb" />
<img width="1707" height="818" alt="VantaPadTopImage" src="https://github.com/user-attachments/assets/bba681ce-56ff-426f-9324-a7ee02abda20" />

## Firmware 💻
**Overview of the Firmware**

I wrote the firmware in QMK. This took tons of trial and error but I am very pleased with the final result. The QMK docs can be confusing but I found many resources online that helped me as well. 

- The 6 keys are mapped as shown but can be easily changed
```
║ Previous   ║ Next         ║ Pause       ║

║ Reopen Tab ║ Auto Clicker ║ Layer Cycle ║
```
```// ---------- Keymaps ----------
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_MPRV, KC_MNXT, KC_MPLY, KC_MUTE, // Top row + Encoder Button
        REOPEN_TAB, AUTO_CLICKER, KC_CYCLE_LAYERS
    ),
};
```
- The rotary encoder controls volume 🔊 on the base layer, scrolls tabs 📑 on the second layer, and controls brightness 🔆 on the third layer 
  - Clicking the encoder always will mute the computer's volume
```
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_BASE]   = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_LAYER1] = { ENCODER_CCW_CW(LCTL(KC_PGUP), LCTL(KC_PGDN)) },
    [_LAYER2] = { ENCODER_CCW_CW(KC_BRID, KC_BRIU) },
};
```
- The OLED has 2 animations. Animation 1 is the idle animation ⏱️ where the VantaPad alien is slightly growing and shrinking (breathing) with occasional blinks 👀. Animation 2 occurs when a key is pressed and it makes the alien have a slight shocked 😮 face with a lightning bolt above its head for 900 ms. 
<img width="2189" height="1045" alt="OLEDAnimationImage" src="https://github.com/user-attachments/assets/c00e82df-efb3-4324-a725-406b3e60984e" />

- The OLED also displays useful information ℹ️ to the side of the animation. This includes what layer it is currently using and also displays my name. 
```
oled_set_cursor(0, 0);
oled_write_P(PSTR("Arnaan Shah"), false);
    
oled_set_cursor(0, 2);
switch (get_highest_layer(layer_state)) {
    case _BASE:   oled_write_P(PSTR("Layer 1"), false); break;
    case _LAYER1: oled_write_P(PSTR("Layer 2"), false); break;
    case _LAYER2: oled_write_P(PSTR("Layer 3"), false); break;
}
```

- The RGB LEDS are set to display red and cycle a constant breathing animation
```
void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(0, 255, 100);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 1); 
}
```
## BOM 📦💲
**List of materials you'll need to buy to make this macropad. Most of these are easily accessible and the overall cost stayed low. Does not include all the tools required to build it.**

- 6x Cherry MX Switches
- 6x DSA Keycaps
- 5x M3x16mm SHCS Bolts
- 1X M3x12mm SHCS Bolts
- 6x M3 Hex Nuts
- 7x 1N4148 DO-35 Diodes
- 3x WS2812B LEDs
- 1x 0.91" 128x32 OLED Display
- 1x EC11 Rotary Encoder
- 1x XIAO RP2040
- 1x Case (3d printed parts)
## Extras 🪄
**Miscellaneous related things**

I made the logo design all in Figma and it's based off the "Space Alien" inside Halloween Stickers. 
<img width="2518" height="1283" alt="image" src="https://github.com/user-attachments/assets/3cb8275d-24d1-478b-8d50-900a7d6f02b5" />
It's honestly one of my favorite parts of the project 😅

Changes I would still consider making include: 
1. More Information displayed on the OLED - WPM, Time, Date, Volume
2. Adding more animations to the OLED - Spinning alien based on knob, startup screen
3. Making the RGB react - Flash on key press, blink when auto-clicker's active
4. Displaying the PCB through the case somehow

Some resources I used:
- [Joe Scotto's Youtube Channel](https://www.youtube.com/@joe_scotto) (LIFESAVER 🙏)
- [QMK Docs](https://docs.qmk.fm)
- [r/MechanicalKeyboards subreddit](https://www.reddit.com/r/MechanicalKeyboards/) 

# Thanks for reading! If you have any feedback, comments, or questions I would love to hear them and you can always reach out to me!
<img width="1264" height="1052" alt="GoodbyeImage" src="https://github.com/user-attachments/assets/3a110fe8-0a22-4200-b3d4-2d0e3140142b" />

