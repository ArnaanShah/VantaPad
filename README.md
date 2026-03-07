# VantaPad 👽

<img width="1302" height="654" alt="VantaPadLogoImage" src="https://github.com/user-attachments/assets/2348d824-5976-495d-8eea-dfe12df2e56e" />

A Hackpad made as a part of [Hackclub's Blueprint](https://blueprint.hackclub.com/home) program. VantaPad is a sleek black macropad I will use for controlling simple functions on my computer that I currently do by hand. It is one of my first hardware projects and I built it so I could learn many valuable skills such as schematic design, PCB design, Firmware programming, and more.

## How to use
**Brief intro on how to get up and running with VantaPad**

1. Order all the parts based off the BOM
2. Solder your electrical components onto your PCB based on the models and schematics
3. Assemble your case using the hardware provided
4. Plug your microcontroller into your computer and flash your firmware
5. You're done! Read the rest of this doc to understand what it can do.

## Featyres 
**What I included on my build.**

- Black Case - A case in the shape of a hexagon with the logo embossed near the bottom.
- 6 Keys in 3x2 layout - Top row is used for controlling audio. Bottom row has macros for reopening tabs, auto clicking, and cycling layers.  
- 3 RGB LEDs - Lights up a constant looping effect that fades in and out through the front of the case. 
- Rotary Encoder - Layer 1 is Volume, Layer 2 is Tab Scrolling, Layer 3 is Brightness
- 128x32 OLED Display - Shows important info like what layer you're on. Also, shows idle animations and reactions when you press a key.
  
## PCB 
**The design around my PCB. This Includes the schematic I made, the PCB, and more.** 

I designed my PCB in KiCad 9.0! It was fun to use this app because it was pretty beginner friendly and intuitive. It also had some extra built in features so I didn't have to download another app.

Schematic: 

<img width="1783" height="1225" alt="SchematicImage" src="https://github.com/user-attachments/assets/4491e005-9162-469c-b241-5e3bb63cd14c" /> 

PCB:

<img width="1321" height="1080" alt="PCBImage" src="https://github.com/user-attachments/assets/30e7dabf-890f-4603-abc4-71eb7b9fd0c7" />

3d VIEW:

<img width="1848" height="1195" alt="Top3DPCBImage" src="https://github.com/user-attachments/assets/e94f7c59-11d2-4d6f-bdea-9abc10edda45" /> <img width="1790" height="1152" alt="Bottom3dPCBImage 2026-02-26 213746" src="https://github.com/user-attachments/assets/8bc98427-ab92-4869-b239-a926d7c368be" /> 

I used KiCad's built-in Image Converter to make a footprint of my logo:

<img width="2111" height="1003" alt="LogoFootprintImage" src="https://github.com/user-attachments/assets/d5defac8-bcf9-48b0-93ca-87eded2744c6" />

## CAD
**The CAD model I made.**

I modeled this project in Fusion 360 because I've used it before. My plan is that I can assemble the whole thing with 6 screws. 4 on the actual case and 2 connecting the PCB and PCB plate to the case. I added a 10 degree tilt to make it easier to see. There are 3 separate 3d printed parts; the top, the plate, and the bottom. The top has the VantaPad logo in a different color on it because it looks lit. 😎

Pictures 📸:
<img width="1707" height="818" alt="VantaPadAngledImage" src="https://github.com/user-attachments/assets/df1ffe37-30e1-4f40-a8a6-7bd2144d590e" />
<img width="1707" height="818" alt="VantaPadIsometricImage" src="https://github.com/user-attachments/assets/2dd27e0b-25c3-461d-91e8-696fb7808ba0" />
<img width="1707" height="818" alt="VantaPadFrontTopImage" src="https://github.com/user-attachments/assets/7c91b467-1b47-4856-8c26-241c2f9b17bb" />
<img width="1707" height="818" alt="VantaPadTopImage" src="https://github.com/user-attachments/assets/bba681ce-56ff-426f-9324-a7ee02abda20" />

## Firmware 
**Insight into the Firmware**

I wrote all the firmware in QMK. I spent a long time fixing problems when writing the code. These problems were things like the firmware not compiling, not knowing how to use all my extra features, and more. The QMK docs can be confusing but I found many resources online to help me. 

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
- The rotary encoder controls volume on the first layer, scrolls through browser tabs on the second layer, and controls my monitor's brightness on the third layer 
  - When you press down on the encoder it always mutes the volume
```
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_BASE]   = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_LAYER1] = { ENCODER_CCW_CW(LCTL(KC_PGUP), LCTL(KC_PGDN)) },
    [_LAYER2] = { ENCODER_CCW_CW(KC_BRID, KC_BRIU) },
};
```
- The OLED has 2 animations. Animation 1 is the constant looping animation where my alien is "breathing" with occasional blinks (every ~3 seconds). Animation 2 starts when any key is pressed and it basically makes the alien look surprised and have a lightning bolt above his head. 
<img width="2189" height="1045" alt="OLEDAnimationImage" src="https://github.com/user-attachments/assets/c00e82df-efb3-4324-a725-406b3e60984e" />

- The OLED also has some info on the left of the animation. This includes what layer it is currently using and also displays my name. 
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
## BOM
**What to buy to build this macropad. Does not include all the tools required to build it.**

| Name | Amount | Link |
|---|---|---|
| Cherry MX Switches | 6 | [Adafruit](https://www.adafruit.com/product/4952)|
| DSA Keycaps | 6 | [Adafruit](https://www.adafruit.com/product/4997?srsltid=AfmBOopDyFMg5RxxF-Evr6nBGQDyHVTH-dyfbuGdqPaHn7PWQv5c8-_Q) |
| M3 16mm SHCS Bolts | 5 | [Accu Components](https://accu-components.com/us/metric-cap-head-screws/3822-SSCF-M3-16-A2?srsltid=AfmBOopF9mJr7xpYuq4pjtawdEtUoNOIrShH98uHL0dEVVrOUcjwKY9b) |
| M3 12mm SHCS Bolt | 1 | [Accu Components](https://accu-components.com/us/metric-cap-head-screws/3820-SSCF-M3-12-A2) |
| M3 Hex Nuts | 6 | [Accu Components](https://accu-components.com/us/hexagon-nuts/7888-HPN-M3-A2) |
| In4148 DO-35 Diodes | 7 | [Adafruit](https://www.adafruit.com/product/1641?srsltid=AfmBOoragpyopdxH587co8w9Kl0W3cZMjn9bZIbP4UEYHfyiLFoC3nJv) |
| WS2812B RGB LEDS | 3 | [Adafruit](https://www.adafruit.com/product/4684?srsltid=AfmBOop-1QOhPkmYg3AzDhOUYgR5UXpQo03Vo2tT4txB9Lo8MBpf2Z1e) |
| 0.91" OLED Display | 1 | [Aliexpress](https://www.aliexpress.us/item/3256807215355950.html?src=google&pdp_npi=4%40dis%21USD%211.75%210.87%21%21%21%21%21%40%2112000040595474261%21ppc%21%21%21&src=google&albch=shopping&acnt=708-803-3821&isdl=y&slnk=&plac=&mtctp=&albbt=Google_7_shopping&aff_platform=google&aff_short_key=UneMJZVf&gclsrc=aw.ds&albagn=888888&ds_e_adid=&ds_e_matchtype=&ds_e_device=c&ds_e_network=x&ds_e_product_group_id=&ds_e_product_id=en3256807215355950&ds_e_product_merchant_id=5377576114&ds_e_product_country=US&ds_e_product_language=en&ds_e_product_channel=online&ds_e_product_store_id=&ds_url_v=2&albcp=19558607238&albag=&isSmbAutoCall=false&needSmbHouyi=false&gad_source=1&gad_campaignid=19566915268&gclid=Cj0KCQiAk6rNBhCxARIsAN5mQLsg54LCOzQhSObuPu2m54rcTcgSLZ9bMY2AuwFurhrSghMghQPbqsoaAguWEALw_wcB&gatewayAdapt=glo2usa)|
| EC11 Encoder | 1 | [Adafruit](https://www.adafruit.com/product/377)|
| Seeed Studio XIAO RP2040 | 1 | [Seeed Studio](https://www.seeedstudio.com/XIAO-RP2040-v1-0-p-5026.html) |
| 3d Printed Case | 1 | N/A |

## Extras 🪄
**Miscellaneous related things**

I made the logo design all in Figma and it's based off the "Space Alien" inside Halloween Stickers. 
<img width="2518" height="1283" alt="image" src="https://github.com/user-attachments/assets/3cb8275d-24d1-478b-8d50-900a7d6f02b5" />
It's honestly one of my favorite parts of the project because of how cute he is 😅

Changes I would still consider making down the line include: 
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

