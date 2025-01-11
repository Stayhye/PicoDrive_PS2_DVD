#include <stdlib.h>
#include <SDL_keysym.h>

#include "../libpicofe/input.h"
#include "../libpicofe/in_sdl.h"
#include "../libpicofe/plat.h"
#include "../common/input_pico.h"
#include "../common/plat_sdl.h"

const struct in_default_bind _in_sdl_defbinds[] = {
	{ SDLK_UP,     IN_BINDTYPE_PLAYER12, GBTN_UP },
	{ SDLK_DOWN,   IN_BINDTYPE_PLAYER12, GBTN_DOWN },
	{ SDLK_LEFT,   IN_BINDTYPE_PLAYER12, GBTN_LEFT },
	{ SDLK_RIGHT,  IN_BINDTYPE_PLAYER12, GBTN_RIGHT },
	{ SDLK_z,      IN_BINDTYPE_PLAYER12, GBTN_A },
	{ SDLK_x,      IN_BINDTYPE_PLAYER12, GBTN_B },
	{ SDLK_c,      IN_BINDTYPE_PLAYER12, GBTN_C },
	{ SDLK_a,      IN_BINDTYPE_PLAYER12, GBTN_X },
	{ SDLK_s,      IN_BINDTYPE_PLAYER12, GBTN_Y },
	{ SDLK_d,      IN_BINDTYPE_PLAYER12, GBTN_Z },
	{ SDLK_RETURN, IN_BINDTYPE_PLAYER12, GBTN_START },
	{ SDLK_f,      IN_BINDTYPE_PLAYER12, GBTN_MODE },
	{ SDLK_ESCAPE, IN_BINDTYPE_EMU, PEVB_MENU },
	{ SDLK_TAB,    IN_BINDTYPE_EMU, PEVB_RESET },
	{ SDLK_F1,     IN_BINDTYPE_EMU, PEVB_STATE_SAVE },
	{ SDLK_F2,     IN_BINDTYPE_EMU, PEVB_STATE_LOAD },
	{ SDLK_F3,     IN_BINDTYPE_EMU, PEVB_SSLOT_PREV },
	{ SDLK_F4,     IN_BINDTYPE_EMU, PEVB_SSLOT_NEXT },
	{ SDLK_F5,     IN_BINDTYPE_EMU, PEVB_SWITCH_RND },
	{ SDLK_F6,     IN_BINDTYPE_EMU, PEVB_PICO_PPREV },
	{ SDLK_F7,     IN_BINDTYPE_EMU, PEVB_PICO_PNEXT },
	{ SDLK_F8,     IN_BINDTYPE_EMU, PEVB_PICO_STORY },
	{ SDLK_F9,     IN_BINDTYPE_EMU, PEVB_PICO_PAD },
	{ SDLK_F10,    IN_BINDTYPE_EMU, PEVB_PICO_PENST },
	{ SDLK_BACKSPACE, IN_BINDTYPE_EMU, PEVB_FF },

	{ 0, 0, 0 }
};

const struct in_default_bind in_sdl_pico_ps2_map[] = {
	// Blue buttons
	{ SDLK_SPACE, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_SPACE },
	{ SDLK_EXCLAIM, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_EXCLAIM },
	{ SDLK_QUOTEDBL, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_QUOTEDBL },
	{ SDLK_HASH, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_HASH },
	{ SDLK_DOLLAR, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_DOLLAR },
	{ SDLK_AMPERSAND, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_AMPERSAND },
	{ SDLK_LEFTPAREN, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_LEFTPAREN },
	{ SDLK_RIGHTPAREN, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_RIGHTPAREN },
	{ SDLK_ASTERISK, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_ASTERISK },
	{ SDLK_PLUS, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_PLUS },
	{ SDLK_COMMA, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_COMMA },
	{ SDLK_MINUS, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_MINUS },
	{ SDLK_PERIOD, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_PERIOD },
	{ SDLK_SLASH, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_SLASH },
	{ SDLK_0, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_0 },
	{ SDLK_1, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_1 },
	{ SDLK_2, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_2 },
	{ SDLK_3, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_3 },
	{ SDLK_4, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_4 },
	{ SDLK_5, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_5 },
	{ SDLK_6, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_6 },
	{ SDLK_7, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_7 },
	{ SDLK_8, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_8 },
	{ SDLK_9, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_9 },
	{ SDLK_COLON, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_COLON },
	{ SDLK_SEMICOLON, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_SEMICOLON },
	{ SDLK_LESS, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_LESS },
	{ SDLK_EQUALS, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_EQUALS },
	{ SDLK_GREATER, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_GREATER },
	{ SDLK_QUESTION, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_QUESTION },
	{ SDLK_AT, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_AT },
	{ SDLK_BACKSLASH, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_DAKUTEN },
	{ SDLK_LEFTBRACKET, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_LEFTBRACKET },
	{ SDLK_RIGHTBRACKET, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_RIGHTBRACKET },
	{ SDLK_CARET, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_CARET },
	{ SDLK_UNDERSCORE, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_UNDERSCORE },
	{ SDLK_BACKQUOTE, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_YEN },
	{ SDLK_a, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_a },
	{ SDLK_b, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_b },
	{ SDLK_c, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_c },
	{ SDLK_d, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_d },
	{ SDLK_e, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_e },
	{ SDLK_f, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_f },
	{ SDLK_g, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_g },
	{ SDLK_h, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_h },
	{ SDLK_i, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_i },
	{ SDLK_j, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_j },
	{ SDLK_k, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_k },
	{ SDLK_l, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_l },
	{ SDLK_m, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_m },
	{ SDLK_n, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_n },
	{ SDLK_o, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_o },
	{ SDLK_p, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_p },
	{ SDLK_q, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_q },
	{ SDLK_r, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_r },
	{ SDLK_s, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_s },
	{ SDLK_t, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_t },
	{ SDLK_u, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_u },
	{ SDLK_v, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_v },
	{ SDLK_w, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_w },
	{ SDLK_x, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_x },
	{ SDLK_y, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_y },
	{ SDLK_z, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_z },
	{ SDLK_QUOTE, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_KE },
	{ SDLK_RSHIFT, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_RO },

	// Green button on top-left
	{ SDLK_ESCAPE, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_ESCAPE },

	// Orange buttons on left
	{ SDLK_LCTRL, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_CAPSLOCK }, // Also switches english input
	{ SDLK_LSHIFT, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_LSHIFT },

	// Green buttons on right
	{ SDLK_BACKSPACE, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_BACKSPACE },
	{ SDLK_INSERT, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_INSERT },
	{ SDLK_DELETE, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_DELETE },

	// Red button on bottom-right
	{ SDLK_RETURN, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_RETURN },

	// Orange buttons on bottom
	{ SDLK_END, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_SOUND },
	{ SDLK_HOME, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_HOME },
	{ SDLK_PAGEUP, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_CJK }, // CJK Scripts: Hiragana / Katakana / Kanji (Keyboard Pico); Hangul (Kibodeu Piko)
	{ SDLK_PAGEDOWN, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_ROMAJI }, // English Script

	// Others
	{ SDLK_LALT, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_ALT },
	{ SDLK_UP, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_UP },
	{ SDLK_DOWN, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_DOWN },
	{ SDLK_LEFT, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_LEFT },
	{ SDLK_RIGHT, IN_BINDTYPE_PICO_PS2, PEVB_PICO_PS2_RIGHT },

	{ 0, 0, 0 }
};
const struct in_default_bind *in_sdl_defbinds = _in_sdl_defbinds;

const struct menu_keymap _in_sdl_key_map[] = {
	{ SDLK_UP,	PBTN_UP },
	{ SDLK_DOWN,	PBTN_DOWN },
	{ SDLK_LEFT,	PBTN_LEFT },
	{ SDLK_RIGHT,	PBTN_RIGHT },
	{ SDLK_RETURN,	PBTN_MOK },
	{ SDLK_ESCAPE,	PBTN_MBACK },
	{ SDLK_COMMA,	PBTN_MA2 },
	{ SDLK_PERIOD,	PBTN_MA3 },
	{ SDLK_TAB,	PBTN_R },
	{ SDLK_BACKSPACE, PBTN_L },
};
const int in_sdl_key_map_sz = sizeof(_in_sdl_key_map) / sizeof(_in_sdl_key_map[0]);
const struct menu_keymap *in_sdl_key_map = _in_sdl_key_map;

const struct menu_keymap _in_sdl_joy_map[] = {
	{ SDLK_UP,	PBTN_UP },
	{ SDLK_DOWN,	PBTN_DOWN },
	{ SDLK_LEFT,	PBTN_LEFT },
	{ SDLK_RIGHT,	PBTN_RIGHT },
	/* joystick */
	{ SDLK_WORLD_0,	PBTN_MOK },
	{ SDLK_WORLD_1,	PBTN_MBACK },
	{ SDLK_WORLD_2,	PBTN_MA2 },
	{ SDLK_WORLD_3,	PBTN_MA3 },
};
const int in_sdl_joy_map_sz = sizeof(_in_sdl_joy_map) / sizeof(_in_sdl_joy_map[0]);
const struct menu_keymap *in_sdl_joy_map = _in_sdl_joy_map;

const char * const *in_sdl_key_names = NULL;

void plat_target_setup_input(void)
{
}
