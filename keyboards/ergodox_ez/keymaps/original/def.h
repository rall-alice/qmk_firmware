#ifndef ERGO_ORIGINAL_DEF
#define ERGO_ORIGINAL_DEF

#include <sendstring_jis.h>

#define MCR_LOMG_PRESS 100
#define LP_MCR_START  80
#define DEVEL_STR_REPEAT_MAX 8 

// Long Press Macros
enum {
  M_C_D = LP_MCR_START, // ,|.
  M_SC_CO               // ;|:
};

enum {
  COMM_IN = 0,
  COMM_OUT
};

const char* devel_comment_list[] = {
  [COMM_IN] = "/*",
  [COMM_OUT] = "*/"
};

enum {
  PRIVATE  = 0,
  PROTECTED,
	PUBLIC
};

const char* devel_p_key_list[] = {
  [PRIVATE] = "private",
  [PROTECTED] = "protected",
  [PUBLIC] = "public"
};

const macro_t *get_press_macro(uint8_t id, uint8_t isLong);

#endif
