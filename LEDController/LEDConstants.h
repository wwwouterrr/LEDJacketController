#ifndef _LEDConstants_h
#define _LEDConstants_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <FastLED.h>
#include "Segment.h"
#include "Shape.h"
#include <map>

#define LED_PIN       23
#define BRIGHTNESS    150
#define LED_TYPE      WS2812B
#define COLOR_ORDER   GRB
#define NUM_LEDS      271
#define MIC_PIN       12

// 2d coordinates of LEDS
const PROGMEM uint8_t ledsArray[NUM_LEDS][2] = { {189, 242}, {184, 235}, {178, 228}, {173, 222}, {169, 216}, {164, 208}, {159, 202}, {154, 196}, {149, 189}, {145, 183}, {140, 176}, {135, 169}, {130, 162}, {125, 155}, {121, 149}, {116, 142}, {111, 135}, {107, 128}, {102, 121}, {98, 115}, {93, 109}, {88, 102}, {84, 95}, {79, 88}, {75, 81}, {70, 76}, {66, 69}, {61, 62}, {56, 54}, {51, 49}, {46, 43}, {42, 35}, {37, 28}, {33, 22}, {28, 15}, {23, 28}, {24, 35}, {26, 44}, {27, 51}, {28, 59}, {29, 68}, {30, 76}, {32, 83}, {33, 92}, {34, 100}, {35, 107}, {36, 116}, {37, 124}, {39, 131}, {40, 140}, {41, 148}, {42, 157}, {44, 164}, {44, 172}, {46, 181}, {47, 189}, {48, 196}, {50, 204}, {51, 213}, {53, 220}, {53, 229}, {54, 238}, {55, 245}, {57, 253}, {65, 248}, {70, 242}, {75, 235}, {81, 229}, {86, 222}, {91, 216}, {101, 217}, {105, 224}, {111, 231}, {115, 237}, {120, 243}, {125, 250}, {135, 254}, {135, 246}, {137, 237}, {137, 231}, {139, 222}, {140, 214}, {141, 205}, {141, 197}, {142, 191}, {145, 180}, {146, 173}, {147, 166}, {148, 158}, {149, 149}, {151, 140}, {152, 133}, {153, 125}, {154, 116}, {156, 109}, {157, 101}, {158, 92}, {159, 84}, {161, 76}, {162, 69}, {163, 60}, {165, 53}, {166, 44}, {167, 36}, {168, 28}, {162, 13}, {157, 21}, {153, 27}, {147, 34}, {143, 40}, {139, 47}, {133, 54}, {129, 60}, {124, 67}, {120, 74}, {115, 81}, {110, 88}, {106, 94}, {101, 101}, {97, 108}, {91, 115}, {88, 121}, {83, 128}, {78, 134}, {73, 142}, {69, 148}, {65, 154}, {60, 161}, {55, 167}, {51, 175}, {45, 180}, {41, 187}, {36, 194}, {31, 201}, {26, 208}, {22, 215}, {17, 221}, {12, 228}, {8, 235}, {2, 241}, {3, 255}, {11, 250}, {18, 246}, {26, 242}, {32, 239}, {39, 235}, {47, 231}, {60, 223}, {69, 220}, {75, 216}, {82, 214}, {88, 210}, {96, 206}, {103, 202}, {111, 198}, {118, 194}, {124, 191}, {132, 187}, {153, 179}, {160, 175}, {167, 172}, {175, 170}, {183, 165}, {190, 153}, {183, 150}, {175, 147}, {168, 143}, {160, 139}, {153, 136}, {146, 133}, {137, 128}, {130, 125}, {123, 121}, {116, 118}, {109, 114}, {107, 104}, {114, 100}, {121, 95}, {130, 91}, {137, 87}, {144, 82}, {149, 77}, {152, 70}, {148, 63}, {143, 56}, {137, 49}, {133, 43}, {129, 36}, {124, 29}, {120, 22}, {115, 15}, {112, 8}, {108, 2}, {85, 3}, {80, 8}, {76, 15}, {71, 22}, {66, 29}, {61, 35}, {57, 43}, {51, 52}, {47, 55}, {43, 62}, {38, 69}, {40, 78}, {46, 82}, {54, 87}, {60, 90}, {67, 95}, {74, 100}, {81, 105}, {80, 113}, {73, 118}, {66, 121}, {59, 125}, {52, 128}, {45, 132}, {35, 136}, {30, 139}, {22, 144}, {14, 146}, {7, 149}, {0, 154}, {8, 165}, {16, 168}, {23, 173}, {31, 175}, {38, 179}, {58, 189}, {65, 192}, {73, 197}, {80, 201}, {87, 204}, {94, 209}, {102, 211}, {109, 215}, {116, 219}, {123, 222}, {132, 226}, {144, 232}, {152, 235}, {160, 239}, {168, 244}, {174, 247}, {183, 251}, {190, 254}, {94, 198}, {94, 188}, {94, 180}, {94, 171}, {95, 165}, {95, 156}, {95, 148}, {95, 140}, {94, 132}, {94, 124}, {95, 115}, {95, 108}, {94, 100}, {95, 91}, {95, 83}, {94, 75}, {94, 66}, {95, 58}, {95, 50}, {95, 42}, {95, 35}, {95, 26}, {95, 17}, {95, 9}, {94, 0} };

// Todo: store in PROGMEM
const std::map <std::string, Shape> shapes{
	{" ", {{}}},
	{"A", {{{41, 60}, {29}, {110}, {193, 203}, {270}, {182, 192}, {79, 98}, {211, 216}, {257}, {169, 174}}}},
	{"B", {{{41, 60}, {193, 203}, {257, 270}, {211, 216}, {147, 174}}}},
	{"C", {{{193, 203}, {41, 54}, {228, 233}, {153, 162}, {186, 192}, {270}}}},
	{"D", {{{246, 270}, {48, 60}, {147, 152}, {233}, {246, 270}, {211, 216}}}},
	{"E", {{{41, 60}, {211, 216}, {193, 203}, {147, 157}, {233}}}},
	{"F", {{{41, 60}, {211, 216}, {193, 203}}}},
	{"G", {{{193, 203}, {41, 54}, {228, 233}, {153, 162}, {186, 192}, {270}, {163, 172}}}},
	{"H", {{{35, 60}, {79, 104}, {257}, {211, 216}, {169, 174}}}},
	{"I", {{{246, 270}}}},
	{"J", {{{246, 270}, {145, 152}, {233}, {60}}}},
	{"K", {{{246, 270}, {105, 119}, {4, 20}, {85}}}},
	{"L", {{{35, 60}, {147, 157}, {233}}}},
	{"M", {{{20, 54}, {85, 119}, {257}}}},
	{"N", {{{9, 60}, {257}, {85, 104}}}},
	{"O", {{{41, 54}, {228, 233}, {152, 157}, {85, 98}, {182, 192}, {270}, {193, 203}}}},
	{"P", {{{41, 60}, {193, 203}, {257, 270}, {211, 216}}}},
	{"Q", {{{41, 54}, {228, 233}, {152, 157}, {85, 98}, {182, 192}, {270}, {193, 203}, {5, 12}}}},
	{"R", {{{41, 60}, {193, 203}, {257, 270}, {211, 216}, {0, 19}}}},
	{"S", {{{228, 233}, {152, 157}, {85}, {10, 20}, {257}, {190, 210}, {270}, {29}}}},
	{"T", {{{120, 139}, {204, 210}, {168, 174}, {257}, {41}, {91}, {54}}}},
	{"U", {{{35, 54}, {81, 104}, {228, 233}, {152, 157}}}},
	{"V", {{{35, 54}, {110, 130}, {257}}}},
	{"W", {{{35, 54}, {85, 104}, {120, 130}, {10, 20}, {257}}}},
	{"X", {{{105, 134}, {5, 34}, {257}, {85}, {54}}}},
	{"Y", {{{21, 34}, {257}, {105, 133}, {54}}}},
	{"Z", {{{211, 222}, {48}, {257}, {120, 139}, {140, 152}, {60}, {54}}}},
	{"0", {{{41, 54}, {228, 233}, {152, 157}, {85, 98}, {182, 192}, {270}, {193, 203}, {110, 130}}}},
	{"1", {{{246, 270}, {193, 197}, {228, 233}, {152, 157}}}},
	{"2", {{{185, 198}, {270}, {110, 130}, {257}, {228, 233}, {153, 157}}}},
	{"3", {{{153, 192}}}},
	{"4", {{{193, 210}, {257}, {109, 132}, {54}}}},
	{"5", {{{223, 233}, {54}, {246, 257}, {182, 210}}}},
	{"6", {{{105, 130}, {257}, {228, 233}, {153, 174}}}},
	{"7", {{{204, 210}, {257}, {120, 139}, {54}, {225, 227}}}},
	{"8", {{{48, 54}, {228, 233}, {153, 157}, {85, 91}, {169, 216}, {270}, {257}}}},
	{"9", {{{246, 270}, {193, 210}}}},
	{"/", {{{257}, {110, 129}}}},
	{"\\",{{{257}, {10, 31}}}},
	{"%", {{{257}, {111, 129}, {14}, {26}}}},
	{">", {{{257}, {204, 216}}}},
	{"<", {{{257}, {169, 181}}}},
	{"*", {{{251, 264}, {169, 181}, {204, 216}, {13, 27}, {112, 126}}}},
	{"?", {{{232, 234}, {151, 153}, {249, 257}, {69, 70}, {175, 203}}}},
	{"!", {{{232, 234}, {151, 153}, {249, 270}, {69, 70}}}},
	{"k", {{{257}, {41, 98}, {175, 210}, {270}, {233}, {110}, {29}}}},								    // rocket 1
	{"l", {{{257}, {41, 98}, {175, 210}, {270}, {233}, {110}, {29}, {130, 146}, {0, 9}, {239, 245}}}},  // rocket 2
	{"l1",{{{63,35}}}},
	{"l2",{{{76,104}}}},
	{"l3",{{{139,121},{257},{119,105}}}},
	{"l4",{{{0,18},{257},{21,34}}}},
	{"l5",{{{140,146},{60},{147,151},{233},{153,157},{85},{158,162}}}},
	{"l6",{{{245,239},{79},{238,228},{54},{227,223}}}},
	{"l7",{{{140,146},{60},{147,151},{233},{153,157},{85},{158,184},{110},{186,192}}}},
	{"l8",{{{245,239},{79},{238,228},{54},{227,201},{29},{199,193}}}},
	{"a", {{{257, 270}}}},
	{"b", {{{257}, {105, 119}}}},
	{"c", {{{257}, {175, 181}}}},
	{"d", {{{257}, {163, 174}, {91}}}},
	{"e", {{{257}, {0, 19}, {85}}}},
	{"f", {{{246, 257}}}},
	{"g", {{{257}, {120, 139}, {54}}}},
	{"h", {{{257}, {211, 222}, {48}}}},
	{"i", {{{257}, {204, 210}}}},
	{"j", {{{257}, {20, 34}}}},
	{"m", {{{70, 151}, {257}, {233}, {60}, {54}}}},														// arrow left
	{"n", {{{0, 69}, {257}, {233, 245}, {85}, {79}}}}													// arrow right
};

#endif