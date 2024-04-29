// the blocks themselves
static const Block blocks[] = {
  // Command,                                   Update Interval,  Update Signal,
  // Sub To Signal
  // clang-format off
  { "getplayerctl '^c#6272A4^no active player^c#f8f8f2^'",  60,   21,  "playerctl -F metadata 2> /dev/null | subtosignal \"pkill -RTMIN+21 rootblocks\"" },
  { "db-volume",                                            60,   10,  "pactl subscribe | grep --line-buffered \"sink #\" | subtosignal \"pkill -RTMIN+10 rootblocks\"" },
  // { "echo \"^c#FF92D0^$(xkb-switch)^c#f8f8f2^\"",           60,   12,  "xkb-switch -W | subtosignal \"pkill -RTMIN+12 rootblocks\"" },
  // { "db-bat",                                               5,    20,  "upower -m | subtosignal \"pkill -RTMIN+20 rootblocks\"" },
  /* { "twnextdue",                                            10,   0,   "" }, */
  // { "muttupd",                                              10,   0,   "" },
  { "rssupd",                                               10,   0,   "" },
  { "date '+^c#ff92d0^%b %-d, %a^c#f8f8f2^'",               60,   0,   "" },
  { "date '+^c#8be9fd^%I:%M %p^c#f8f8f2^'",                 1,    0,   "" },
  // clang-format on
};

static char opening[] = " ";  // sets string added before status
static char delim[]   = "・"; // sets delimeter between status commands
static char ending[]  = "・"; // sets string appended after status

#define CMDLENGTH 250 // max length of command output
