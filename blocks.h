// Modify this file to change what commands output to your statusbar, and
// recompile using the make command.
static const Block blocks[] = {
    /*Icon*/ /*Command*/ /*Update Interval*/ /*Update Signal*/
    {"", "getplayerctl '^c#6272A4^no active player^c#f8f8f2^'", 1, 0},
    {"", "db-volume", 2, 10},
    {"", "db-bat", 1, 0},
    {"", "muttupd", 10, 0},
    {"", "rssupd", 10, 0},
    {"", "date '+%b %d, %a * %I:%M:%S %p]['", 1, 0},
};

// sets delimeter between status commands. NULL character ('\0') means no
// delimeter.
static char delim[] = "][";
static unsigned int delimLen = 2;
