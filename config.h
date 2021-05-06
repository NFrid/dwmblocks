// the blocks themselves
static const Block blocks[] = {
  // Command,                                   Update Interval,  Update Signal
  // clang-format off
  { "getplayerctl '^c#6272A4^no active player^c#f8f8f2^'",  1,    0 },
  { "db-volume",                                            2,    10 },
  { "db-bat",                                               1,    0 },
  { "muttupd",                                              10,   0 },
  { "rssupd",                                               10,   0 },
  { "date '+^c#ff92d0^%b %-d, %a^c#f8f8f2^'",               60,   0 },
  { "date '+^c#8be9fd^%I:%M %p^c#f8f8f2^'",                 1,    0 },
  { "echo ''",                                              0,    0 },
  // clang-format on
};

// sets delimeter between status commands. NULL character ('\0') = no delim
static char delim[] = "][";
#define CMDLENGTH 150 // max length of command output

// need to define after, do not touch
#define STATUSLENGTH (LENGTH(blocks) * CMDLENGTH + 1)