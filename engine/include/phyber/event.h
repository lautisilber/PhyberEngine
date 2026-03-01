#ifndef PHYBER_ENGINE_EVENT_H
#define PHYBER_ENGINE_EVENT_H

#include <stdint.h>

namespace Phyber {

typedef uint32_t EventType_t;
enum EventType : EventType_t {
    KEYBOARD, MOUSE_MOTION, MOUSE_BUTTON, MOUSE_WHEEL, QUIT_EVENT, UNSUPPORTED
};


struct KeyboardEvent {
    struct KeySymbol {
        enum PhysicalKey : uint32_t {
            PK_UNKNOWN = 0,
            PK_A = 4,
            PK_B = 5,
            PK_C = 6,
            PK_D = 7,
            PK_E = 8,
            PK_F = 9,
            PK_G = 10,
            PK_H = 11,
            PK_I = 12,
            PK_J = 13,
            PK_K = 14,
            PK_L = 15,
            PK_M = 16,
            PK_N = 17,
            PK_O = 18,
            PK_P = 19,
            PK_Q = 20,
            PK_R = 21,
            PK_S = 22,
            PK_T = 23,
            PK_U = 24,
            PK_V = 25,
            PK_W = 26,
            PK_X = 27,
            PK_Y = 28,
            PK_Z = 29,

            PK_1 = 30,
            PK_2 = 31,
            PK_3 = 32,
            PK_4 = 33,
            PK_5 = 34,
            PK_6 = 35,
            PK_7 = 36,
            PK_8 = 37,
            PK_9 = 38,
            PK_0 = 39,

            PK_RETURN = 40,
            PK_ESCAPE = 41,
            PK_BACKSPACE = 42,
            PK_TAB = 43,
            PK_SPACE = 44,

            PK_MINUS = 45,
            PK_EQUALS = 46,
            PK_LEFTBRACKET = 47,
            PK_RIGHTBRACKET = 48,
            PK_BACKSLASH = 49, /**< Located at the lower left of the return
                                            *   key on ISO keyboards and at the right end
                                            *   of the QWERTY row on ANSI keyboards.
                                            *   Produces REVERSE SOLIDUS (backslash) and
                                            *   VERTICAL LINE in a US layout, REVERSE
                                            *   SOLIDUS and VERTICAL LINE in a UK Mac
                                            *   layout, NUMBER SIGN and TILDE in a UK
                                            *   Windows layout, DOLLAR SIGN and POUND SIGN
                                            *   in a Swiss German layout, NUMBER SIGN and
                                            *   APOSTROPHE in a German layout, GRAVE
                                            *   ACCENT and POUND SIGN in a French Mac
                                            *   layout, and ASTERISK and MICRO SIGN in a
                                            *   French Windows layout.
                                            */
            PK_NONUSHASH = 50, /**< ISO USB keyboards actually use this code
                                            *   instead of 49 for the same key, but all
                                            *   OSes I've seen treat the two codes
                                            *   identically. So, as an implementor, unless
                                            *   your keyboard generates both of those
                                            *   codes and your OS treats them differently,
                                            *   you should generate PK_BACKSLASH
                                            *   instead of this code. As a user, you
                                            *   should not rely on this code because SDL
                                            *   will never generate it with most (all?)
                                            *   keyboards.
                                            */
            PK_SEMICOLON = 51,
            PK_APOSTROPHE = 52,
            PK_GRAVE = 53, /**< Located in the top left corner (on both ANSI
                                        *   and ISO keyboards). Produces GRAVE ACCENT and
                                        *   TILDE in a US Windows layout and in US and UK
                                        *   Mac layouts on ANSI keyboards, GRAVE ACCENT
                                        *   and NOT SIGN in a UK Windows layout, SECTION
                                        *   SIGN and PLUS-MINUS SIGN in US and UK Mac
                                        *   layouts on ISO keyboards, SECTION SIGN and
                                        *   DEGREE SIGN in a Swiss German layout (Mac:
                                        *   only on ISO keyboards), CIRCUMFLEX ACCENT and
                                        *   DEGREE SIGN in a German layout (Mac: only on
                                        *   ISO keyboards), SUPERSCRIPT TWO and TILDE in a
                                        *   French Windows layout, COMMERCIAL AT and
                                        *   NUMBER SIGN in a French Mac layout on ISO
                                        *   keyboards, and LESS-THAN SIGN and GREATER-THAN
                                        *   SIGN in a Swiss German, German, or French Mac
                                        *   layout on ANSI keyboards.
                                        */
            PK_COMMA = 54,
            PK_PERIOD = 55,
            PK_SLASH = 56,

            PK_CAPSLOCK = 57,

            PK_F1 = 58,
            PK_F2 = 59,
            PK_F3 = 60,
            PK_F4 = 61,
            PK_F5 = 62,
            PK_F6 = 63,
            PK_F7 = 64,
            PK_F8 = 65,
            PK_F9 = 66,
            PK_F10 = 67,
            PK_F11 = 68,
            PK_F12 = 69,

            PK_PRINTSCREEN = 70,
            PK_SCROLLLOCK = 71,
            PK_PAUSE = 72,
            PK_INSERT = 73, /**< insert on PC, help on some Mac keyboards (but
                                            does send code 73, not 117) */
            PK_HOME = 74,
            PK_PAGEUP = 75,
            PK_DELETE = 76,
            PK_END = 77,
            PK_PAGEDOWN = 78,
            PK_RIGHT = 79,
            PK_LEFT = 80,
            PK_DOWN = 81,
            PK_UP = 82,

            PK_NUMLOCKCLEAR = 83, /**< num lock on PC, clear on Mac keyboards
                                                */
            PK_KP_DIVIDE = 84,
            PK_KP_MULTIPLY = 85,
            PK_KP_MINUS = 86,
            PK_KP_PLUS = 87,
            PK_KP_ENTER = 88,
            PK_KP_1 = 89,
            PK_KP_2 = 90,
            PK_KP_3 = 91,
            PK_KP_4 = 92,
            PK_KP_5 = 93,
            PK_KP_6 = 94,
            PK_KP_7 = 95,
            PK_KP_8 = 96,
            PK_KP_9 = 97,
            PK_KP_0 = 98,
            PK_KP_PERIOD = 99,

            PK_NONUSBACKSLASH = 100, /**< This is the additional key that ISO
                                                *   keyboards have over ANSI ones,
                                                *   located between left shift and Y.
                                                *   Produces GRAVE ACCENT and TILDE in a
                                                *   US or UK Mac layout, REVERSE SOLIDUS
                                                *   (backslash) and VERTICAL LINE in a
                                                *   US or UK Windows layout, and
                                                *   LESS-THAN SIGN and GREATER-THAN SIGN
                                                *   in a Swiss German, German, or French
                                                *   layout. */
            PK_APPLICATION = 101, /**< windows contextual menu, compose */
            PK_POWER = 102, /**< The USB document says this is a status flag,
                                        *   not a physical key - but some Mac keyboards
                                        *   do have a power key. */
            PK_KP_EQUALS = 103,
            PK_F13 = 104,
            PK_F14 = 105,
            PK_F15 = 106,
            PK_F16 = 107,
            PK_F17 = 108,
            PK_F18 = 109,
            PK_F19 = 110,
            PK_F20 = 111,
            PK_F21 = 112,
            PK_F22 = 113,
            PK_F23 = 114,
            PK_F24 = 115,
            PK_EXECUTE = 116,
            PK_HELP = 117,    /**< AL Integrated Help Center */
            PK_MENU = 118,    /**< Menu (show menu) */
            PK_SELECT = 119,
            PK_STOP = 120,    /**< AC Stop */
            PK_AGAIN = 121,   /**< AC Redo/Repeat */
            PK_UNDO = 122,    /**< AC Undo */
            PK_CUT = 123,     /**< AC Cut */
            PK_COPY = 124,    /**< AC Copy */
            PK_PASTE = 125,   /**< AC Paste */
            PK_FIND = 126,    /**< AC Find */
            PK_MUTE = 127,
            PK_VOLUMEUP = 128,
            PK_VOLUMEDOWN = 129,

            PK_KP_COMMA = 133,
            PK_KP_EQUALSAS400 = 134,

            PK_INTERNATIONAL1 = 135, /**< used on Asian keyboards, see
                                                    footnotes in USB doc */
            PK_INTERNATIONAL2 = 136,
            PK_INTERNATIONAL3 = 137, /**< Yen */
            PK_INTERNATIONAL4 = 138,
            PK_INTERNATIONAL5 = 139,
            PK_INTERNATIONAL6 = 140,
            PK_INTERNATIONAL7 = 141,
            PK_INTERNATIONAL8 = 142,
            PK_INTERNATIONAL9 = 143,
            PK_LANG1 = 144, /**< Hangul/English toggle */
            PK_LANG2 = 145, /**< Hanja conversion */
            PK_LANG3 = 146, /**< Katakana */
            PK_LANG4 = 147, /**< Hiragana */
            PK_LANG5 = 148, /**< Zenkaku/Hankaku */
            PK_LANG6 = 149, /**< reserved */
            PK_LANG7 = 150, /**< reserved */
            PK_LANG8 = 151, /**< reserved */
            PK_LANG9 = 152, /**< reserved */

            PK_ALTERASE = 153,    /**< Erase-Eaze */
            PK_SYSREQ = 154,
            PK_CANCEL = 155,      /**< AC Cancel */
            PK_CLEAR = 156,
            PK_PRIOR = 157,
            PK_RETURN2 = 158,
            PK_SEPARATOR = 159,
            PK_OUT = 160,
            PK_OPER = 161,
            PK_CLEARAGAIN = 162,
            PK_CRSEL = 163,
            PK_EXSEL = 164,

            PK_KP_00 = 176,
            PK_KP_000 = 177,
            PK_THOUSANDSSEPARATOR = 178,
            PK_DECIMALSEPARATOR = 179,
            PK_CURRENCYUNIT = 180,
            PK_CURRENCYSUBUNIT = 181,
            PK_KP_LEFTPAREN = 182,
            PK_KP_RIGHTPAREN = 183,
            PK_KP_LEFTBRACE = 184,
            PK_KP_RIGHTBRACE = 185,
            PK_KP_TAB = 186,
            PK_KP_BACKSPACE = 187,
            PK_KP_A = 188,
            PK_KP_B = 189,
            PK_KP_C = 190,
            PK_KP_D = 191,
            PK_KP_E = 192,
            PK_KP_F = 193,
            PK_KP_XOR = 194,
            PK_KP_POWER = 195,
            PK_KP_PERCENT = 196,
            PK_KP_LESS = 197,
            PK_KP_GREATER = 198,
            PK_KP_AMPERSAND = 199,
            PK_KP_DBLAMPERSAND = 200,
            PK_KP_VERTICALBAR = 201,
            PK_KP_DBLVERTICALBAR = 202,
            PK_KP_COLON = 203,
            PK_KP_HASH = 204,
            PK_KP_SPACE = 205,
            PK_KP_AT = 206,
            PK_KP_EXCLAM = 207,
            PK_KP_MEMSTORE = 208,
            PK_KP_MEMRECALL = 209,
            PK_KP_MEMCLEAR = 210,
            PK_KP_MEMADD = 211,
            PK_KP_MEMSUBTRACT = 212,
            PK_KP_MEMMULTIPLY = 213,
            PK_KP_MEMDIVIDE = 214,
            PK_KP_PLUSMINUS = 215,
            PK_KP_CLEAR = 216,
            PK_KP_CLEARENTRY = 217,
            PK_KP_BINARY = 218,
            PK_KP_OCTAL = 219,
            PK_KP_DECIMAL = 220,
            PK_KP_HEXADECIMAL = 221,

            PK_LCTRL = 224,
            PK_LSHIFT = 225,
            PK_LALT = 226, /**< alt, option */
            PK_LGUI = 227, /**< windows, command (apple), meta */
            PK_RCTRL = 228,
            PK_RSHIFT = 229,
            PK_RALT = 230, /**< alt gr, option */
            PK_RGUI = 231, /**< windows, command (apple), meta */

            PK_MODE = 257,    /**< I'm not sure if this is really not covered
                                            *   by any of the above, but since there's a
                                            *   special KMOD_MODE for it I'm adding it here
                                            */

            PK_AUDIONEXT = 258,
            PK_AUDIOPREV = 259,
            PK_AUDIOSTOP = 260,
            PK_AUDIOPLAY = 261,
            PK_AUDIOMUTE = 262,
            PK_MEDIASELECT = 263,
            PK_WWW = 264,             /**< AL Internet Browser */
            PK_MAIL = 265,
            PK_CALCULATOR = 266,      /**< AL Calculator */
            PK_COMPUTER = 267,
            PK_AC_SEARCH = 268,       /**< AC Search */
            PK_AC_HOME = 269,         /**< AC Home */
            PK_AC_BACK = 270,         /**< AC Back */
            PK_AC_FORWARD = 271,      /**< AC Forward */
            PK_AC_STOP = 272,         /**< AC Stop */
            PK_AC_REFRESH = 273,      /**< AC Refresh */
            PK_AC_BOOKMARKS = 274,    /**< AC Bookmarks */

            PK_BRIGHTNESSDOWN = 275,
            PK_BRIGHTNESSUP = 276,
            PK_DISPLAYSWITCH = 277, /**< display mirroring/dual display
                                                    switch, video mode switch */
            PK_KBDILLUMTOGGLE = 278,
            PK_KBDILLUMDOWN = 279,
            PK_KBDILLUMUP = 280,
            PK_EJECT = 281,
            PK_SLEEP = 282,           /**< SC System Sleep */

            PK_APP1 = 283,
            PK_APP2 = 284,

            PK_AUDIOREWIND = 285,
            PK_AUDIOFASTFORWARD = 286,

            PK_SOFTLEFT = 287, /**< Usually situated below the display on phones and
                                                used as a multi-function feature key for selecting
                                                a software defined function shown on the bottom left
                                                of the display. */
            PK_SOFTRIGHT = 288, /**< Usually situated below the display on phones and
                                                used as a multi-function feature key for selecting
                                                a software defined function shown on the bottom right
                                                of the display. */
            PK_CALL = 289, /**< Used for accepting phone calls. */
            PK_ENDCALL = 290 /**< Used for rejecting phone calls. */

            // SDL_SCANCODE_COUNT = 512 /**< not a key, just marks the number of scancodes for array bounds */
        };

        enum VirtualKey : uint32_t {
            VK_UNKNOWN =                0x00000000u, /**< 0 */
            VK_RETURN =                 0x0000000du, /**< '\r' */
            VK_ESCAPE =                 0x0000001bu, /**< '\x1B' */
            VK_BACKSPACE =              0x00000008u, /**< '\b' */
            VK_TAB =                    0x00000009u, /**< '\t' */
            VK_SPACE =                  0x00000020u, /**< ' ' */
            VK_EXCLAIM =                0x00000021u, /**< '!' */
            VK_DBLAPOSTROPHE =          0x00000022u, /**< '"' */
            VK_HASH =                   0x00000023u, /**< '#' */
            VK_DOLLAR =                 0x00000024u, /**< '$' */
            VK_PERCENT =                0x00000025u, /**< '%' */
            VK_AMPERSAND =              0x00000026u, /**< '&' */
            VK_APOSTROPHE =             0x00000027u, /**< '\'' */
            VK_LEFTPAREN =              0x00000028u, /**< '(' */
            VK_RIGHTPAREN =             0x00000029u, /**< ')' */
            VK_ASTERISK =               0x0000002au, /**< '*' */
            VK_PLUS =                   0x0000002bu, /**< '+' */
            VK_COMMA =                  0x0000002cu, /**< ',' */
            VK_MINUS =                  0x0000002du, /**< '-' */
            VK_PERIOD =                 0x0000002eu, /**< '.' */
            VK_SLASH =                  0x0000002fu, /**< '/' */
            VK_0 =                      0x00000030u, /**< '0' */
            VK_1 =                      0x00000031u, /**< '1' */
            VK_2 =                      0x00000032u, /**< '2' */
            VK_3 =                      0x00000033u, /**< '3' */
            VK_4 =                      0x00000034u, /**< '4' */
            VK_5 =                      0x00000035u, /**< '5' */
            VK_6 =                      0x00000036u, /**< '6' */
            VK_7 =                      0x00000037u, /**< '7' */
            VK_8 =                      0x00000038u, /**< '8' */
            VK_9 =                      0x00000039u, /**< '9' */
            VK_COLON =                  0x0000003au, /**< ':' */
            VK_SEMICOLON =              0x0000003bu, /**< ';' */
            VK_LESS =                   0x0000003cu, /**< '<' */
            VK_EQUALS =                 0x0000003du, /**< '=' */
            VK_GREATER =                0x0000003eu, /**< '>' */
            VK_QUESTION =               0x0000003fu, /**< '?' */
            VK_AT =                     0x00000040u, /**< '@' */
            VK_LEFTBRACKET =            0x0000005bu, /**< '[' */
            VK_BACKSLASH =              0x0000005cu, /**< '\\' */
            VK_RIGHTBRACKET =           0x0000005du, /**< ']' */
            VK_CARET =                  0x0000005eu, /**< '^' */
            VK_UNDERSCORE =             0x0000005fu, /**< '_' */
            VK_GRAVE =                  0x00000060u, /**< '`' */
            VK_A =                      0x00000061u, /**< 'a' */
            VK_B =                      0x00000062u, /**< 'b' */
            VK_C =                      0x00000063u, /**< 'c' */
            VK_D =                      0x00000064u, /**< 'd' */
            VK_E =                      0x00000065u, /**< 'e' */
            VK_F =                      0x00000066u, /**< 'f' */
            VK_G =                      0x00000067u, /**< 'g' */
            VK_H =                      0x00000068u, /**< 'h' */
            VK_I =                      0x00000069u, /**< 'i' */
            VK_J =                      0x0000006au, /**< 'j' */
            VK_K =                      0x0000006bu, /**< 'k' */
            VK_L =                      0x0000006cu, /**< 'l' */
            VK_M =                      0x0000006du, /**< 'm' */
            VK_N =                      0x0000006eu, /**< 'n' */
            VK_O =                      0x0000006fu, /**< 'o' */
            VK_P =                      0x00000070u, /**< 'p' */
            VK_Q =                      0x00000071u, /**< 'q' */
            VK_R =                      0x00000072u, /**< 'r' */
            VK_S =                      0x00000073u, /**< 's' */
            VK_T =                      0x00000074u, /**< 't' */
            VK_U =                      0x00000075u, /**< 'u' */
            VK_V =                      0x00000076u, /**< 'v' */
            VK_W =                      0x00000077u, /**< 'w' */
            VK_X =                      0x00000078u, /**< 'x' */
            VK_Y =                      0x00000079u, /**< 'y' */
            VK_Z =                      0x0000007au, /**< 'z' */
            VK_LEFTBRACE =              0x0000007bu, /**< '{' */
            VK_PIPE =                   0x0000007cu, /**< '|' */
            VK_RIGHTBRACE =             0x0000007du, /**< '}' */
            VK_TILDE =                  0x0000007eu, /**< '~' */
            VK_DELETE =                 0x0000007fu, /**< '\x7F' */
            VK_PLUSMINUS =              0x000000b1u, /**< '\xB1' */
            VK_CAPSLOCK =               0x40000039u, /**< PK_TO_KEYCODE(PK_CAPSLOCK) */
            VK_F1 =                     0x4000003au, /**< PK_TO_KEYCODE(PK_F1) */
            VK_F2 =                     0x4000003bu, /**< PK_TO_KEYCODE(PK_F2) */
            VK_F3 =                     0x4000003cu, /**< PK_TO_KEYCODE(PK_F3) */
            VK_F4 =                     0x4000003du, /**< PK_TO_KEYCODE(PK_F4) */
            VK_F5 =                     0x4000003eu, /**< PK_TO_KEYCODE(PK_F5) */
            VK_F6 =                     0x4000003fu, /**< PK_TO_KEYCODE(PK_F6) */
            VK_F7 =                     0x40000040u, /**< PK_TO_KEYCODE(PK_F7) */
            VK_F8 =                     0x40000041u, /**< PK_TO_KEYCODE(PK_F8) */
            VK_F9 =                     0x40000042u, /**< PK_TO_KEYCODE(PK_F9) */
            VK_F10 =                    0x40000043u, /**< PK_TO_KEYCODE(PK_F10) */
            VK_F11 =                    0x40000044u, /**< PK_TO_KEYCODE(PK_F11) */
            VK_F12 =                    0x40000045u, /**< PK_TO_KEYCODE(PK_F12) */
            VK_PRINTSCREEN =            0x40000046u, /**< PK_TO_KEYCODE(PK_PRINTSCREEN) */
            VK_SCROLLLOCK =             0x40000047u, /**< PK_TO_KEYCODE(PK_SCROLLLOCK) */
            VK_PAUSE =                  0x40000048u, /**< PK_TO_KEYCODE(PK_PAUSE) */
            VK_INSERT =                 0x40000049u, /**< PK_TO_KEYCODE(PK_INSERT) */
            VK_HOME =                   0x4000004au, /**< PK_TO_KEYCODE(PK_HOME) */
            VK_PAGEUP =                 0x4000004bu, /**< PK_TO_KEYCODE(PK_PAGEUP) */
            VK_END =                    0x4000004du, /**< PK_TO_KEYCODE(PK_END) */
            VK_PAGEDOWN =               0x4000004eu, /**< PK_TO_KEYCODE(PK_PAGEDOWN) */
            VK_RIGHT =                  0x4000004fu, /**< PK_TO_KEYCODE(PK_RIGHT) */
            VK_LEFT =                   0x40000050u, /**< PK_TO_KEYCODE(PK_LEFT) */
            VK_DOWN =                   0x40000051u, /**< PK_TO_KEYCODE(PK_DOWN) */
            VK_UP =                     0x40000052u, /**< PK_TO_KEYCODE(PK_UP) */
            VK_NUMLOCKCLEAR =           0x40000053u, /**< PK_TO_KEYCODE(PK_NUMLOCKCLEAR) */
            VK_KP_DIVIDE =              0x40000054u, /**< PK_TO_KEYCODE(PK_KP_DIVIDE) */
            VK_KP_MULTIPLY =            0x40000055u, /**< PK_TO_KEYCODE(PK_KP_MULTIPLY) */
            VK_KP_MINUS =               0x40000056u, /**< PK_TO_KEYCODE(PK_KP_MINUS) */
            VK_KP_PLUS =                0x40000057u, /**< PK_TO_KEYCODE(PK_KP_PLUS) */
            VK_KP_ENTER =               0x40000058u, /**< PK_TO_KEYCODE(PK_KP_ENTER) */
            VK_KP_1 =                   0x40000059u, /**< PK_TO_KEYCODE(PK_KP_1) */
            VK_KP_2 =                   0x4000005au, /**< PK_TO_KEYCODE(PK_KP_2) */
            VK_KP_3 =                   0x4000005bu, /**< PK_TO_KEYCODE(PK_KP_3) */
            VK_KP_4 =                   0x4000005cu, /**< PK_TO_KEYCODE(PK_KP_4) */
            VK_KP_5 =                   0x4000005du, /**< PK_TO_KEYCODE(PK_KP_5) */
            VK_KP_6 =                   0x4000005eu, /**< PK_TO_KEYCODE(PK_KP_6) */
            VK_KP_7 =                   0x4000005fu, /**< PK_TO_KEYCODE(PK_KP_7) */
            VK_KP_8 =                   0x40000060u, /**< PK_TO_KEYCODE(PK_KP_8) */
            VK_KP_9 =                   0x40000061u, /**< PK_TO_KEYCODE(PK_KP_9) */
            VK_KP_0 =                   0x40000062u, /**< PK_TO_KEYCODE(PK_KP_0) */
            VK_KP_PERIOD =              0x40000063u, /**< PK_TO_KEYCODE(PK_KP_PERIOD) */
            VK_APPLICATION =            0x40000065u, /**< PK_TO_KEYCODE(PK_APPLICATION) */
            VK_POWER =                  0x40000066u, /**< PK_TO_KEYCODE(PK_POWER) */
            VK_KP_EQUALS =              0x40000067u, /**< PK_TO_KEYCODE(PK_KP_EQUALS) */
            VK_F13 =                    0x40000068u, /**< PK_TO_KEYCODE(PK_F13) */
            VK_F14 =                    0x40000069u, /**< PK_TO_KEYCODE(PK_F14) */
            VK_F15 =                    0x4000006au, /**< PK_TO_KEYCODE(PK_F15) */
            VK_F16 =                    0x4000006bu, /**< PK_TO_KEYCODE(PK_F16) */
            VK_F17 =                    0x4000006cu, /**< PK_TO_KEYCODE(PK_F17) */
            VK_F18 =                    0x4000006du, /**< PK_TO_KEYCODE(PK_F18) */
            VK_F19 =                    0x4000006eu, /**< PK_TO_KEYCODE(PK_F19) */
            VK_F20 =                    0x4000006fu, /**< PK_TO_KEYCODE(PK_F20) */
            VK_F21 =                    0x40000070u, /**< PK_TO_KEYCODE(PK_F21) */
            VK_F22 =                    0x40000071u, /**< PK_TO_KEYCODE(PK_F22) */
            VK_F23 =                    0x40000072u, /**< PK_TO_KEYCODE(PK_F23) */
            VK_F24 =                    0x40000073u, /**< PK_TO_KEYCODE(PK_F24) */
            VK_EXECUTE =                0x40000074u, /**< PK_TO_KEYCODE(PK_EXECUTE) */
            VK_HELP =                   0x40000075u, /**< PK_TO_KEYCODE(PK_HELP) */
            VK_MENU =                   0x40000076u, /**< PK_TO_KEYCODE(PK_MENU) */
            VK_SELECT =                 0x40000077u, /**< PK_TO_KEYCODE(PK_SELECT) */
            VK_STOP =                   0x40000078u, /**< PK_TO_KEYCODE(PK_STOP) */
            VK_AGAIN =                  0x40000079u, /**< PK_TO_KEYCODE(PK_AGAIN) */
            VK_UNDO =                   0x4000007au, /**< PK_TO_KEYCODE(PK_UNDO) */
            VK_CUT =                    0x4000007bu, /**< PK_TO_KEYCODE(PK_CUT) */
            VK_COPY =                   0x4000007cu, /**< PK_TO_KEYCODE(PK_COPY) */
            VK_PASTE =                  0x4000007du, /**< PK_TO_KEYCODE(PK_PASTE) */
            VK_FIND =                   0x4000007eu, /**< PK_TO_KEYCODE(PK_FIND) */
            VK_MUTE =                   0x4000007fu, /**< PK_TO_KEYCODE(PK_MUTE) */
            VK_VOLUMEUP =               0x40000080u, /**< PK_TO_KEYCODE(PK_VOLUMEUP) */
            VK_VOLUMEDOWN =             0x40000081u, /**< PK_TO_KEYCODE(PK_VOLUMEDOWN) */
            VK_KP_COMMA =               0x40000085u, /**< PK_TO_KEYCODE(PK_KP_COMMA) */
            VK_KP_EQUALSAS400 =         0x40000086u, /**< PK_TO_KEYCODE(PK_KP_EQUALSAS400) */
            VK_ALTERASE =               0x40000099u, /**< PK_TO_KEYCODE(PK_ALTERASE) */
            VK_SYSREQ =                 0x4000009au, /**< PK_TO_KEYCODE(PK_SYSREQ) */
            VK_CANCEL =                 0x4000009bu, /**< PK_TO_KEYCODE(PK_CANCEL) */
            VK_CLEAR =                  0x4000009cu, /**< PK_TO_KEYCODE(PK_CLEAR) */
            VK_PRIOR =                  0x4000009du, /**< PK_TO_KEYCODE(PK_PRIOR) */
            VK_RETURN2 =                0x4000009eu, /**< PK_TO_KEYCODE(PK_RETURN2) */
            VK_SEPARATOR =              0x4000009fu, /**< PK_TO_KEYCODE(PK_SEPARATOR) */
            VK_OUT =                    0x400000a0u, /**< PK_TO_KEYCODE(PK_OUT) */
            VK_OPER =                   0x400000a1u, /**< PK_TO_KEYCODE(PK_OPER) */
            VK_CLEARAGAIN =             0x400000a2u, /**< PK_TO_KEYCODE(PK_CLEARAGAIN) */
            VK_CRSEL =                  0x400000a3u, /**< PK_TO_KEYCODE(PK_CRSEL) */
            VK_EXSEL =                  0x400000a4u, /**< PK_TO_KEYCODE(PK_EXSEL) */
            VK_KP_00 =                  0x400000b0u, /**< PK_TO_KEYCODE(PK_KP_00) */
            VK_KP_000 =                 0x400000b1u, /**< PK_TO_KEYCODE(PK_KP_000) */
            VK_THOUSANDSSEPARATOR =     0x400000b2u, /**< PK_TO_KEYCODE(PK_THOUSANDSSEPARATOR) */
            VK_DECIMALSEPARATOR =       0x400000b3u, /**< PK_TO_KEYCODE(PK_DECIMALSEPARATOR) */
            VK_CURRENCYUNIT =           0x400000b4u, /**< PK_TO_KEYCODE(PK_CURRENCYUNIT) */
            VK_CURRENCYSUBUNIT =        0x400000b5u, /**< PK_TO_KEYCODE(PK_CURRENCYSUBUNIT) */
            VK_KP_LEFTPAREN =           0x400000b6u, /**< PK_TO_KEYCODE(PK_KP_LEFTPAREN) */
            VK_KP_RIGHTPAREN =          0x400000b7u, /**< PK_TO_KEYCODE(PK_KP_RIGHTPAREN) */
            VK_KP_LEFTBRACE =           0x400000b8u, /**< PK_TO_KEYCODE(PK_KP_LEFTBRACE) */
            VK_KP_RIGHTBRACE =          0x400000b9u, /**< PK_TO_KEYCODE(PK_KP_RIGHTBRACE) */
            VK_KP_TAB =                 0x400000bau, /**< PK_TO_KEYCODE(PK_KP_TAB) */
            VK_KP_BACKSPACE =           0x400000bbu, /**< PK_TO_KEYCODE(PK_KP_BACKSPACE) */
            VK_KP_A =                   0x400000bcu, /**< PK_TO_KEYCODE(PK_KP_A) */
            VK_KP_B =                   0x400000bdu, /**< PK_TO_KEYCODE(PK_KP_B) */
            VK_KP_C =                   0x400000beu, /**< PK_TO_KEYCODE(PK_KP_C) */
            VK_KP_D =                   0x400000bfu, /**< PK_TO_KEYCODE(PK_KP_D) */
            VK_KP_E =                   0x400000c0u, /**< PK_TO_KEYCODE(PK_KP_E) */
            VK_KP_F =                   0x400000c1u, /**< PK_TO_KEYCODE(PK_KP_F) */
            VK_KP_XOR =                 0x400000c2u, /**< PK_TO_KEYCODE(PK_KP_XOR) */
            VK_KP_POWER =               0x400000c3u, /**< PK_TO_KEYCODE(PK_KP_POWER) */
            VK_KP_PERCENT =             0x400000c4u, /**< PK_TO_KEYCODE(PK_KP_PERCENT) */
            VK_KP_LESS =                0x400000c5u, /**< PK_TO_KEYCODE(PK_KP_LESS) */
            VK_KP_GREATER =             0x400000c6u, /**< PK_TO_KEYCODE(PK_KP_GREATER) */
            VK_KP_AMPERSAND =           0x400000c7u, /**< PK_TO_KEYCODE(PK_KP_AMPERSAND) */
            VK_KP_DBLAMPERSAND =        0x400000c8u, /**< PK_TO_KEYCODE(PK_KP_DBLAMPERSAND) */
            VK_KP_VERTICALBAR =         0x400000c9u, /**< PK_TO_KEYCODE(PK_KP_VERTICALBAR) */
            VK_KP_DBLVERTICALBAR =      0x400000cau, /**< PK_TO_KEYCODE(PK_KP_DBLVERTICALBAR) */
            VK_KP_COLON =               0x400000cbu, /**< PK_TO_KEYCODE(PK_KP_COLON) */
            VK_KP_HASH =                0x400000ccu, /**< PK_TO_KEYCODE(PK_KP_HASH) */
            VK_KP_SPACE =               0x400000cdu, /**< PK_TO_KEYCODE(PK_KP_SPACE) */
            VK_KP_AT =                  0x400000ceu, /**< PK_TO_KEYCODE(PK_KP_AT) */
            VK_KP_EXCLAM =              0x400000cfu, /**< PK_TO_KEYCODE(PK_KP_EXCLAM) */
            VK_KP_MEMSTORE =            0x400000d0u, /**< PK_TO_KEYCODE(PK_KP_MEMSTORE) */
            VK_KP_MEMRECALL =           0x400000d1u, /**< PK_TO_KEYCODE(PK_KP_MEMRECALL) */
            VK_KP_MEMCLEAR =            0x400000d2u, /**< PK_TO_KEYCODE(PK_KP_MEMCLEAR) */
            VK_KP_MEMADD =              0x400000d3u, /**< PK_TO_KEYCODE(PK_KP_MEMADD) */
            VK_KP_MEMSUBTRACT =         0x400000d4u, /**< PK_TO_KEYCODE(PK_KP_MEMSUBTRACT) */
            VK_KP_MEMMULTIPLY =         0x400000d5u, /**< PK_TO_KEYCODE(PK_KP_MEMMULTIPLY) */
            VK_KP_MEMDIVIDE =           0x400000d6u, /**< PK_TO_KEYCODE(PK_KP_MEMDIVIDE) */
            VK_KP_PLUSMINUS =           0x400000d7u, /**< PK_TO_KEYCODE(PK_KP_PLUSMINUS) */
            VK_KP_CLEAR =               0x400000d8u, /**< PK_TO_KEYCODE(PK_KP_CLEAR) */
            VK_KP_CLEARENTRY =          0x400000d9u, /**< PK_TO_KEYCODE(PK_KP_CLEARENTRY) */
            VK_KP_BINARY =              0x400000dau, /**< PK_TO_KEYCODE(PK_KP_BINARY) */
            VK_KP_OCTAL =               0x400000dbu, /**< PK_TO_KEYCODE(PK_KP_OCTAL) */
            VK_KP_DECIMAL =             0x400000dcu, /**< PK_TO_KEYCODE(PK_KP_DECIMAL) */
            VK_KP_HEXADECIMAL =         0x400000ddu, /**< PK_TO_KEYCODE(PK_KP_HEXADECIMAL) */
            VK_LCTRL =                  0x400000e0u, /**< PK_TO_KEYCODE(PK_LCTRL) */
            VK_LSHIFT =                 0x400000e1u, /**< PK_TO_KEYCODE(PK_LSHIFT) */
            VK_LALT =                   0x400000e2u, /**< PK_TO_KEYCODE(PK_LALT) */
            VK_LGUI =                   0x400000e3u, /**< PK_TO_KEYCODE(PK_LGUI) */
            VK_RCTRL =                  0x400000e4u, /**< PK_TO_KEYCODE(PK_RCTRL) */
            VK_RSHIFT =                 0x400000e5u, /**< PK_TO_KEYCODE(PK_RSHIFT) */
            VK_RALT =                   0x400000e6u, /**< PK_TO_KEYCODE(PK_RALT) */
            VK_RGUI =                   0x400000e7u, /**< PK_TO_KEYCODE(PK_RGUI) */
            VK_MODE =                   0x40000101u, /**< PK_TO_KEYCODE(PK_MODE) */
            VK_SLEEP =                  0x40000102u, /**< PK_TO_KEYCODE(PK_SLEEP) */
            VK_WAKE =                   0x40000103u, /**< PK_TO_KEYCODE(PK_WAKE) */
            VK_CHANNEL_INCREMENT =      0x40000104u, /**< PK_TO_KEYCODE(PK_CHANNEL_INCREMENT) */
            VK_CHANNEL_DECREMENT =      0x40000105u, /**< PK_TO_KEYCODE(PK_CHANNEL_DECREMENT) */
            VK_MEDIA_PLAY =             0x40000106u, /**< PK_TO_KEYCODE(PK_MEDIA_PLAY) */
            VK_MEDIA_PAUSE =            0x40000107u, /**< PK_TO_KEYCODE(PK_MEDIA_PAUSE) */
            VK_MEDIA_RECORD =           0x40000108u, /**< PK_TO_KEYCODE(PK_MEDIA_RECORD) */
            VK_MEDIA_FAST_FORWARD =     0x40000109u, /**< PK_TO_KEYCODE(PK_MEDIA_FAST_FORWARD) */
            VK_MEDIA_REWIND =           0x4000010au, /**< PK_TO_KEYCODE(PK_MEDIA_REWIND) */
            VK_MEDIA_NEXT_TRACK =       0x4000010bu, /**< PK_TO_KEYCODE(PK_MEDIA_NEXT_TRACK) */
            VK_MEDIA_PREVIOUS_TRACK =   0x4000010cu, /**< PK_TO_KEYCODE(PK_MEDIA_PREVIOUS_TRACK) */
            VK_MEDIA_STOP =             0x4000010du, /**< PK_TO_KEYCODE(PK_MEDIA_STOP) */
            VK_MEDIA_EJECT =            0x4000010eu, /**< PK_TO_KEYCODE(PK_MEDIA_EJECT) */
            VK_MEDIA_PLAY_PAUSE =       0x4000010fu, /**< PK_TO_KEYCODE(PK_MEDIA_PLAY_PAUSE) */
            VK_MEDIA_SELECT =           0x40000110u, /**< PK_TO_KEYCODE(PK_MEDIA_SELECT) */
            VK_AC_NEW =                 0x40000111u, /**< PK_TO_KEYCODE(PK_AC_NEW) */
            VK_AC_OPEN =                0x40000112u, /**< PK_TO_KEYCODE(PK_AC_OPEN) */
            VK_AC_CLOSE =               0x40000113u, /**< PK_TO_KEYCODE(PK_AC_CLOSE) */
            VK_AC_EXIT =                0x40000114u, /**< PK_TO_KEYCODE(PK_AC_EXIT) */
            VK_AC_SAVE =                0x40000115u, /**< PK_TO_KEYCODE(PK_AC_SAVE) */
            VK_AC_PRINT =               0x40000116u, /**< PK_TO_KEYCODE(PK_AC_PRINT) */
            VK_AC_PROPERTIES =          0x40000117u, /**< PK_TO_KEYCODE(PK_AC_PROPERTIES) */
            VK_AC_SEARCH =              0x40000118u, /**< PK_TO_KEYCODE(PK_AC_SEARCH) */
            VK_AC_HOME =                0x40000119u, /**< PK_TO_KEYCODE(PK_AC_HOME) */
            VK_AC_BACK =                0x4000011au, /**< PK_TO_KEYCODE(PK_AC_BACK) */
            VK_AC_FORWARD =             0x4000011bu, /**< PK_TO_KEYCODE(PK_AC_FORWARD) */
            VK_AC_STOP =                0x4000011cu, /**< PK_TO_KEYCODE(PK_AC_STOP) */
            VK_AC_REFRESH =             0x4000011du, /**< PK_TO_KEYCODE(PK_AC_REFRESH) */
            VK_AC_BOOKMARKS =           0x4000011eu, /**< PK_TO_KEYCODE(PK_AC_BOOKMARKS) */
            VK_SOFTLEFT =               0x4000011fu, /**< PK_TO_KEYCODE(PK_SOFTLEFT) */
            VK_SOFTRIGHT =              0x40000120u, /**< PK_TO_KEYCODE(PK_SOFTRIGHT) */
            VK_CALL =                   0x40000121u, /**< PK_TO_KEYCODE(PK_CALL) */
            VK_ENDCALL =                0x40000122u, /**< PK_TO_KEYCODE(PK_ENDCALL) */
            VK_LEFT_TAB =               0x20000001u, /**< Extended key Left Tab */
            VK_LEVEL5_SHIFT =           0x20000002u, /**< Extended key Level 5 Shift */
            VK_MULTI_KEY_COMPOSE =      0x20000003u, /**< Extended key Multi-key Compose */
            VK_LMETA =                  0x20000004u, /**< Extended key Left Meta */
            VK_RMETA =                  0x20000005u, /**< Extended key Right Meta */
            VK_LHYPER =                 0x20000006u, /**< Extended key Left Hyper */
            VK_RHYPER =                 0x20000007u  /**< Extended key Right Hyper */
        };

        enum KeyModifier : uint16_t {
            KMOD_NONE   = 0x0000u, /**< no modifier is applicable. */
            KMOD_LSHIFT = 0x0001u, /**< the left Shift key is down. */
            KMOD_RSHIFT = 0x0002u, /**< the right Shift key is down. */
            KMOD_LEVEL5 = 0x0004u, /**< the Level 5 Shift key is down. */
            KMOD_LCTRL  = 0x0040u, /**< the left Ctrl (Control) key is down. */
            KMOD_RCTRL  = 0x0080u, /**< the right Ctrl (Control) key is down. */
            KMOD_LALT   = 0x0100u, /**< the left Alt key is down. */
            KMOD_RALT   = 0x0200u, /**< the right Alt key is down. */
            KMOD_LGUI   = 0x0400u, /**< the left GUI key (often the Windows key) is down. */
            KMOD_RGUI   = 0x0800u, /**< the right GUI key (often the Windows key) is down. */
            KMOD_NUM    = 0x1000u, /**< the Num Lock key (may be located on an extended keypad) is down. */
            KMOD_CAPS   = 0x2000u, /**< the Caps Lock key is down. */
            KMOD_MODE   = 0x4000u, /**< the !AltGr key is down. */
            KMOD_SCROLL = 0x8000u, /**< the Scroll Lock key is down. */
            KMOD_CTRL   = (0x0040u | 0x0080u),   /**< Any Ctrl key is down. */
            KMOD_SHIFT  = (0x0001u | 0x0002u), /**< Any Shift key is down. */
            KMOD_ALT    = (0x0100u | 0x0200u),     /**< Any Alt key is down. */
            KMOD_GUI    = (0x0400u | 0x0800u)     /**< Any GUI key is down. */
        };

        PhysicalKey physical_key; /**< the physical keyboard key affected */
        VirtualKey virtual_key;   /**< the virtual keyboard key affected */
        KeyModifier key_modifier; /**< curren key modifiers */
    };

    KeySymbol key;
    bool down;                /**< true if the button is pressed */
    bool repeat;              /**< Non-zero if this is a key repeat */
};

typedef uint8_t MouseButtonFlags_t;
enum MouseButtonFlags : MouseButtonFlags_t {
    BUTTON_LEFT     = 1,
    BUTTON_MIDDLE   = 2,
    BUTTON_RIGHT    = 3,
    BUTTON_X1       = 4, // side button 1
    BUTTON_X2       = 5  // side button 2
};

struct MouseMotionEvent {
    MouseButtonFlags_t button_state; /**< The mouse button state */
    float x, y, dx, dy;
};

struct MouseButtonEvent {
    MouseButtonFlags_t button; /**< The mouse button index */
    bool down;                 /**< true if the button is pressed */
    uint8_t clicks;             /**< 1 for single-click, 2 for double-click, etc. */
    float x, y;                /**< X, Y coordinates, relative to window */
};

struct MouseWheelEvent {
    enum Direction : uint8_t {
        NORMAL, FLIPPED
    };

    float x;             /**< The amount scrolled horizontally, positive to the right and negative to the left */
    float y;             /**< The amount scrolled vertically, positive away from the user and negative toward the user */
    Direction direction; /**< When FLIPPED the values in X and Y will be opposite. Multiply by -1 to change them back */
    float mouse_x;      /**< X coordinate, relative to window */
    float mouse_y;      /**< Y coordinate, relative to window */
    int32_t integer_x;   /**< The amount scrolled horizontally, accumulated to whole scroll "ticks" */
    int32_t integer_y;   /**< The amount scrolled vertically, accumulated to whole scroll "ticks" */
};


union Event {
    EventType_t type;

    KeyboardEvent keyboard;
    MouseMotionEvent mouse_motion;
    MouseButtonEvent mouse_button;
    MouseWheelEvent mouse_wheel;
};

extern bool poll_event(Event &event);

}



#endif /* PHYBER_ENGINE_EVENT_H */
