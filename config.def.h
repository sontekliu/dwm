/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 8;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const Bool viewontag         = True;     /* Switch view on tag switch */
static const char *fonts[]          = { "monospace:size=14",
					"WenQuanYi Micro Hei:size=14:style=Regular:antialias=true:auto:autohint=true",
					"Symbols Nerd Font:pixelsize=16:style=Regular:antialias=true:auto:autohint=true",
					"JoyPixels:pixelsize=16:style=Regular:antialias=true:auto:autohint=true"
				      };
static const char dmenucmd[]        = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#ffffff";
static const char col_cyan[]        = "#1e81b0";
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

static const char *autostartscript = "$HOME/myconfig/dwm/script/autostart.sh";
/* 调整任务栏的高度 */

/* tagging */
static const char *tags[] = { " 󰣇 ", "  ", "  ", "  ", "  ", "  ", " 󰨞 ", "  ", "  " };

/* launcher commands (They must be NULL terminated) */
static const char* chrome[] = { "google-chrome-stable", "https://google.com", NULL };

static const Launcher launchers[] = {
       /* command       name to display */
	{ chrome,         "Chrome" },
};

/* Lockfile */
static char lockfile[] = "/tmp/dwm.lock";

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *rofi[] = { "rofi", "-show", "drun", "-theme", "glue_pro_blue.rasi"};
static const char *rofirun[] = { "rofi", "-show", "run", "-theme", "glue_pro_blue.rasi"};

static const char *termcmd[]  = { "st", NULL };
static const char *i3lock[]  = { "i3lock", NULL };
static const char *flameshot[]  = { "flameshot", "gui", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

static const Key keys[] = {
	/* modifier                     	key        		function        	argument */
	{ MODKEY,                       	XK_d,      		spawn,          	{.v = rofi } },  		 /* super + d 			| 启动菜单窗口, rofi drun*/
	{ MODKEY|ShiftMask,                     XK_d,      		spawn,          	{.v = rofirun } },  		 /* super + shift + d 	        | 启动菜单窗口, rofi run*/
	{ MODKEY,                       	XK_Return, 		spawn,          	{.v = termcmd } },               /* super + enter 		| 启动终端，此处是 st */
	{ MODKEY|ShiftMask,             	XK_l, 	   		spawn,          	{.v = i3lock } },                /* super + shift + l   	| 锁屏 */
	{ MODKEY|ShiftMask,             	XK_a, 	   		spawn,          	{.v = flameshot } },             /* super + shift + a   	| 截图 */
	{ MODKEY,                       	XK_a, 	   		togglescratch,  	{.v = scratchpadcmd } },	 /* super + a 			| 启动临时窗口 */
	{ MODKEY,                       	XK_b,      		togglebar,      	{0} },			         /* super + b 			| 隐藏顶部状态栏 */
	{ MODKEY|ShiftMask,             	XK_f,      		fullscreen,     	{0} },				 /* super + shift +f 		| 全屏当前窗口 */
	{ MODKEY|ControlMask|ShiftMask,		XK_e, quit,           				{0} }, 				 /* super + ctl + shift + e 	| 退出DWM */
	{ MODKEY|ControlMask|ShiftMask, 	XK_r, quit,           				{1} }, 				 /* super + ctl + shift + r 	| 重新加载DWM */
	{ MODKEY|ShiftMask,             	XK_q,      		killclient,     	{0} }, 				 /* super + shift + q           | 关闭窗口*/
	{ MODKEY,                       	XK_j,      		focusstack,     	{.i = +1 } },			 /* super + j 			| 移动到下一个窗口 */
	{ MODKEY,                       	XK_k,      		focusstack,     	{.i = -1 } },			 /* super + k			| 移动到上一个窗口 */
	{ MODKEY,                       	XK_h,      		setmfact,       	{.f = -0.05} },			 /* super + h			| 减小主窗口大小 */
	{ MODKEY,                       	XK_l,      		setmfact,       	{.f = +0.05} },			 /* super + l			| 增大主窗口大小 */
	{ MODKEY|ShiftMask,             	XK_Return, 		zoom,           	{0} },				 /* super + shift + return	| 当前聚焦窗口切换为主窗口 */
	{ MODKEY,                       	XK_t,      		setlayout,      	{.v = &layouts[0]} },		 /* super + t			| 默认平铺布局 */
	{ MODKEY,                       	XK_f,      		setlayout,      	{.v = &layouts[1]} },		 /* super + f			| 浮动布局 */
	{ MODKEY,                       	XK_m,      		setlayout,      	{.v = &layouts[2]} },		 /* super + m			| 蝶式布局 */
	{ MODKEY,                       	XK_space,  		setlayout,      	{0} },				 /* super + space		| 布局切换 */
	{ MODKEY|ShiftMask,             	XK_space,  		togglefloating, 	{0} },				 /* super + shift + space	| 将窗口切换成浮动 */
	{ MODKEY,                       	XK_0,      		view,           	{.ui = ~0 } },			 /* super + 0			| 显示所有 tag 的窗口 */
	{ MODKEY|ShiftMask,             	XK_0,      		tag,            	{.ui = ~0 } },			 /* super + shift + 0		| 当前聚焦窗口显示到所有 tag */
	{ MODKEY,                       	XK_minus,  		setgaps,        	{.i = -1 } },			 /* super + -			| 缩小窗口间的间距 */
	{ MODKEY,                       	XK_equal,  		setgaps,        	{.i = +1 } },			 /* super + +			| 增加窗口间的间距 */
	{ MODKEY|ShiftMask,             	XK_equal,  		setgaps,        	{.i = 0  } },			 /* super + =			| 窗口间的间距缩小为 0 */
	{ MODKEY,                       	XK_i,      		incnmaster,     	{.i = +1 } },			 /* super + i			| 增加主窗口的个数 */
	{ MODKEY|ShiftMask,             	XK_i,      		incnmaster,     	{.i = -1 } },			 /* super + shift + i		| 减少主窗口的个数 */
	{ MODKEY,                       	XK_Tab,    		view,           	{0} },				 /* super + tab			| 刚刚访问的两个 tag 切换 */
	{ MODKEY,                       	XK_comma,  		focusmon,       	{.i = -1 } },			 /* super + ,			| 光标移动到另外一个显示器 */
	{ MODKEY,                       	XK_period, 		focusmon,       	{.i = +1 } },			 /* super + .			| 光标移动到另外一个显示器 */
	{ MODKEY|ShiftMask,             	XK_comma,  		tagmon,         	{.i = -1 } },			 /* super + shift + , 		| 将聚焦窗口移动到另外一个显示器*/
	{ MODKEY|ShiftMask,             	XK_period, 		tagmon,         	{.i = +1 } },			 /* super + shift + , 		| 将聚焦窗口移动到另外一个显示器*/
	TAGKEYS(                        	XK_1,                      0)
	TAGKEYS(                        	XK_2,                      1)
	TAGKEYS(                        	XK_3,                      2)
	TAGKEYS(                        	XK_4,                      3)
	TAGKEYS(                        	XK_5,                      4)
	TAGKEYS(                        	XK_6,                      5)
	TAGKEYS(                        	XK_7,                      6)
	TAGKEYS(                        	XK_8,                      7)
	TAGKEYS(                        	XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
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

