/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[] = "-xos4-terminus2-*-*-*-*-*-*-*-*-m-*-iso8859-1"",""-*-terminus-medium-r-*-*-12-*-*-*-*-*-*-*";
static const char normbordercolor[] = "#444444";
static const char normbgcolor[]     = "#002b36";
static const char normfgcolor[]     = "#bbbbbb";
static const char selbordercolor[]  = "#FFFFFF";
static const char selbgcolor[]      = "#002b36";
static const char selfgcolor[]      = "#eeeeee";
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 10;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */
//static const int systray_spacing    = 2;
//static const Bool systray_enable    = True;

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const Rule rules[] = {
    /* class      instance    title       tags mask     isfloating   monitor */
    { "Iceweasel",NULL,       NULL,       1 << 1,       False,       False },
    { "Firefox",  NULL,       NULL,       1 << 1,       False,       False },
    { "stalonetray", NULL,    NULL,       ~0,           False,       False },
    { "trayer",   NULL,       NULL,       ~0,           False,       False }
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */



#include "movestack.c"
#include "gaplessgrid.c"
#include "bstack.c"
#include "bstackhoriz.c"
static const Layout layouts[] = {
    /* symbol     arrange function */
    { "###",      gaplessgrid }, /* first entry is default */
    { "[]=",      tile },    
    { "><>",      NULL },    /* no layout function means floating behavior */
    { "[M]",      monocle },
    { "===",      bstackhoriz },
    { "TTT",      bstack }
};


/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char * dmenucmd[]   = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char * termcmd[]    = { "x-terminal-emulator", NULL };
static const char * print[]      = { "scrot", NULL };
static const char * aprint[]     = { "scrot", "-s", NULL };
static const char * wprint[]     = { "scrot", "-u", NULL };
static const char * mcabbercmd[] = { "x-terminal-emulator", "-T", "mcabber", "-e", "mcabber", NULL };
static const char * mocpcmd[]    = { "x-terminal-emulator", "-e", "mocp", NULL };
static const char * lockcmd[]    = { "slock", NULL };
static const char * fmcmd[]      = { "x-terminal-emulator", "-e", "ranger", NULL };
static const char * mocmenucmd[] = { "moc-dmenu", NULL };
static const char * decr_sound[] = { "amixer", "-q", "set", "Master", "5-", NULL };
static const char * incr_sound[] = { "amixer", "-q", "set", "Master", "5+", NULL };
static const char * mute_sound[] = { "amixer", "-q", "set", "Master", "toggle", NULL };
static const char * exitcmd[]    = { "dwm-session", "stop", NULL };

static Key keys[] = {
    /* modifier                     key        function        argument */
    { MODKEY|ShiftMask,             XK_Down,   movestack,      {.i = +1 } },
    { MODKEY|ShiftMask,             XK_Up,     movestack,      {.i = -1 } },
    { 0,                            XK_Print,  spawn,          {.v = print } },
    { MODKEY,                       XK_Print,  spawn,          {.v = wprint } },
    { MODKEY|ControlMask,           XK_Print,  spawn,          {.v = aprint } },
    { MODKEY,                       XK_F10,    spawn,          {.v = mcabbercmd } },
    { MODKEY,                       XK_F11,    spawn,          {.v = mocpcmd } },
    { MODKEY,                       XK_F12,    spawn,          {.v = fmcmd} },
    { MODKEY|ControlMask,           XK_l,      spawn,          {.v = lockcmd } },
    { MODKEY,                       XK_F2,     spawn,          {.v = dmenucmd } },
    { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
    { MODKEY,                       XK_F1,     spawn,          {.v = mocmenucmd} },
    { MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
    { 0,                            XF86XK_AudioLowerVolume, spawn, {.v = decr_sound } },
    { 0,                            XF86XK_AudioRaiseVolume, spawn, {.v = incr_sound } },
    { 0,                            XF86XK_AudioMute,        spawn, {.v = mute_sound } },
    { MODKEY,                       XK_s,      swapfocus,      {0} },
    { MODKEY,                       XK_b,      togglebar,      {0} },
    { MODKEY,                       XK_Tab,    focusstack,     {.i = +1 } },
    { MODKEY,                       XK_grave,  focusstack,     {.i = -1 } },
    { MODKEY,                       XK_Down,   focusstack,     {.i = +1 } },
    { MODKEY,                       XK_Up,     focusstack,     {.i = -1 } },
    { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
    { MODKEY,                       XK_e,      view,           {0} },
    { MODKEY,                       XK_q,      killclient,     {0} },
    { MODKEY,                       XK_g,      setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[3]} },
    { MODKEY,                       XK_n,      setlayout,      {.v = &layouts[4]} },
    { MODKEY,                       XK_j,      setlayout,      {.v = &layouts[5]} },
    { MODKEY,                       XK_space,  setlayout,      {0} },
    { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
    { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
    { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    TAGKEYS(                        XK_1,                      0)
    TAGKEYS(                        XK_2,                      1)
    TAGKEYS(                        XK_3,                      2)
    TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
    TAGKEYS(                        XK_6,                      5)
    TAGKEYS(                        XK_7,                      6)
    TAGKEYS(                        XK_8,                      7)
    TAGKEYS(                        XK_9,                      8)
    { MODKEY|ShiftMask,             XK_e,      spawn,          {.v = exitcmd } },
    /* restart, not quit */
    { MODKEY|ShiftMask,             XK_r,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

