#include "mspacmab.h"



// WARNING: This function may have set the stack pointer
// Ms. Pac-Man documented disassembly
// 
// The copyright holders for the core program
// included within this file are:
//  (c) 1980 NAMCO
//  (c) 1980 Bally/Midway
//  (c) 1981 General Computer Corporation (GCC)
// 
// Research and compilation of the documentation by
//  Scott Lawrence
//  pacman@umlautllama.com  @yorgle
// 
// Documentation and Hack Contributors:
//     Don Hodges                 http://www.donhodges.com
//     David Caldwell             http://www.porkrind.org
//     Frederic Vecoven           http://www.vecoven.com (Music, Sound)
//     Fred K "Juice"
//     Marcel "The Sil" Silvius   http://home.kabelfoon.nl/~msilvius/
//     Mark Spaeth                http://rgvac.978.org/asm
//     Dave Widel                 http://www.widel.com/
//     M.A.B. from Vigasoco
//     Sebastien Bechet
// 
// 
// DISCLAIMER:
//  This project is a learning experience.  The goal is to try
//  to figure out how the original programmers and subsequent
//  GCC programmers wrote Pac-Man, Crazy Otto, and Ms. Pac-Man.
//  This disassembly and comments are not sanctioned in any
//  way by any of the copyright holders of these programs.
// 
// Over time, this document may transform from a documented disassembly
//  of the bootleg ms-pacman roms into a re-assemblable source file.
// 
// This is also made to determine which spaces in the roms are available
//  for patches and extra functionality for your own hacks.
// 
//  NOTE:  This disassembly is based on the base "bootleg" 
//   version of Ms. Pac-Man.   ("boot1" through "boot6")
//  rom images used:
//   0x0000 - 0x0fff  boot1
//   0x1000 - 0x1fff  boot2
//   0x2000 - 0x2fff  boot3
//   0x3000 - 0x3fff  boot4
//   0x8000 - 0x8fff  boot5
//   0x9000 - 0x9fff  boot6
// 
// More information about the actual Ms. Pac-Man aux board is below.
// 
// 
// 
//  IF YOU ARE AWARE OF ANY BITS OF CODE THAT ARE NOT DOCUMENTED
//  HERE, OR KNOW OF MORE RAM ADDRESSES OR SUCH, PLEASE EMAIL
//  ME SO THAT I MAY INTEGRATE YOUR INFORMATION INTO HERE.
// 
//     THANKS!
// 
// 2020-01-19
//     converting mspacmab old work to ghidra, adding RAM memory, 
//     structures and fn prototypes. Currently some stupid bugs (ghidra 9.1.1)
//     with Non-Returning Function (see `POP HL` insert_task() fn)
// 
// 2014-01-18
//  tried to document HACK2 (standard speedup hack) but it makes no sense
//  added more info about #f2 LOOP and ANIMATIONS in general
// 
// 2014-01-16
//  Completely documented DrawText (2c5e)
// 
// 2014-01-12
//  Text string decodings (0x3713, 0x3d00) for readibility
//  Animation code engine at 0x34a9
//  Animation code lists at 0x8251, Rosetta stone at 0x8395
// 
// 2014-01-06
//  Don Hodges' documentation work added
//  bugfix section added.
//   HACK8 -> BUGFIX01
//   HACK9 -> BUGFIX02
//   HACK10 -> HACK8
//   HACK11 -> HACK9
// 
// 2014-01-02
//  Added "OTTOPATCH" information from Crazy Otto source
// 
// 2009-12-16
//  Added some Crazy Otto notes
// 
// 2009-01-18
//  Added content from Don Hodges for much of the undocumented code
// 
// 2008-06-20
//  Added content from Frederic Vecoven for all of the sound code
// 
// 2007-09-03
//  added more notes about mspac blocks in 8000/9000
//  RAM layout, data tables from M.A.B. in the VIGASOCO project (pac)
// 
// 2004-12-28
//  added Interrupt Mode 1/2 documentation
// 
// 2004-12-22
//  added HACK12 - the C000 text mirror bug fix
// 
// 2004-03-21
//  added information for most of the reference tables for map-related-data
// 
// 2004-03-15
//  working on figuring out RST 28 
// 
// 2004-03-09
//  added comments about how the text rendering works (at 0x2c5e)
//  added more details about the text string look up table
//  added information about midway logo rendering at 0x964a
//  changed all of the RST 28 calls to have data after them
// 
// 2004-03-03
//  mapped out most of the patches in 8000-81ef range
//  (some are unused ff's, some I couldn't find...)
// 
// 2004-03-02
//  HACK10: Dave Widel's fast intermission fix (based on Dock Cutlip's code)
//   (now HACK8)
//  HACK11: Dave Widel's coin light blink with power pellets
//   (now HACK9)
// 
// 2004-02-18
//  HACK8: Mark Spaeth's "20 byte" level 255 Pac-Man rom fix (BUGFIX01)
//  HACK9: Mark Spaeth's Ms. Pac-Man level fix (BUGFIX02)
// 
// 2004-01-10
//  figured out some of the sound generation triggering
// 
// 2004-01-09
//  added notes about HACK7 : eliminating all of the startup tests
//  figured out the easter egg routine as well as storage method for data
// 
// 2004-01-05
//  added notes about HACK6 : the standard "HARD" romset
//  changed all of the HACK numbers
// 
// 2004-01-04
//  added notes from Fred K's roms about skipping the self test  HACK4
//  added notes about the pause routine HACK5
//  added notes from Fred K about 018c game loop
// 
// 2004-01-03
//  added note about 0068-008c being junk - INCORRECT! (ed.)
// 
// 2004-01-02
//  added in more information about controllers
//  added info about the always-on fast upgrade  HACK2
//  added info about the P1P2 cheat HACK3
// 
// 2004-01-01
//  integrated in Mark Spaeth's random fruit doc.
// 
// 2003-07-16
//  added in red ghost AI code documentation (2730, 9561)
// 
// 2003-03-26
//  changed some 'kick the dog' text
//  added a note about the checksum hack ; HACK1
// 
// 2003-03
//  cleaned up some notes, added the "Made By Namco" egg notes
// 
// + 2001-07-13
//      more notes from David Widel.  Ram variables, $2a23m $8768
// 
// + 2001-06-25,26
//     integrated in some notes from David Widel (THANKS!)
// 
// 2001-03-06
//     integrated in Fred K's pacman notes.
// 
// 2001-03-04
//     corrected text strings in the lookup table at 36a5
//     commented some of the text string routines
// 
// 2001-02-28
//     added text string lookup tables
//     added indirect lookup at 36a5
//     added more commenting over from the pacman.asm file
// 
// 2001-02-27
//     table data pulled out, and bogus opcodes removed.
//     more score information found as well
// 
// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// Documented Hacks
// 
//  these are common hacks done to this codebase
// 
//  HACK1
//   Skips the traditional bad-rom checksum routine.
// 
//  HACK2
//   Traditional "Fast Chip" hack
// 
//  HACK3
//   Dock Cutlip's Fast/Invincibility hack.
//   Press P1 start for super speed
//   Press P2 start for invincibility
// 
//  HACK4
//   Self-Test skip
//   Reclaims rom space 3006 - 30c0 for custom code use
// 
//  HACK5
//   Game pause routine
//   Press P1 start to pause
//   Press P2 start to unpause
// 
//  HACK6
//   The standard "HARD" romset.
//   Unknown exactly what the changes are. (data table)
// 
//  HACK7
//   Skips the Test startup display
//   (Alternate) just skips the grid.
// 
//  HACK8 (formerly HACK10)
//   Dave Widel's faster intermission fix
//   Based on Dock Cutlip's code
//   Pac moves at normal speeds in intermissions
//   (this is a hack, not a fix, since it's based on a hack/mod
// 
//  HACK9 (formerly HACK11)
//   Dave Widel's coin light blink with power pellets
//   Coin lights blink when power pellets blink now
// 
// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// Documented bugfixes
// 
//  these are bugfixes to the code base
// 
//  BUGFIX01 - Level 255 Pac-Man kill screen killer
//   from: Mark Spaeth
//   notes: Mark Spaeth's level 255 Pac-Man fix
//    Mspac never gets to 255, so this fix is pac-only
// 
//  BUGFIX02 - Level 141 Ms. Pac-Man kill screen killer
//   ref: http://www.funspotnh.com/discus/messages/10/508.html?1077146991
//   from: Mark Spaeth
//   notes: This fix is Ms. Pac only, but will work for pac as well.
// 
//  BUGFIX03 - Blue Maze
//   from: Don Hodges
//   ref: http://donhodges.com/ms_pacman_bugs.htm
//   symptoms: Sometimes when starting Ms Pac, the first
//    board is blue.
// 
//  BUGFIX04 - Marquee left side animation fix
//   from: Don Hodges
//   ref: http://donhodges.com/ms_pacman_bugs.htm
//   symptoms: incorrect character in the intro screen
//   causes the intro marquee to not work on the left side
// 
//  BUGFIX05 - Map discoloration fix
//   from: Don Hodges
//   ref: http://donhodges.com/ms_pacman_bugs.htm
//   symptoms: The marquee doesn't light correctly,
//    Other characters glitch on gameplay maps
// 
// 
// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// 
// Known Ms. Pac variants:
// 
// Pac variants:
//  Puckman              Namco "original"
//  Hanglyman            Maze disappears sometimes, vertical tunnel?
//  Pac-Man              Namco/Midway
//  Pac-Man Hard         (table changes)
//  Pac-Man Plus         Midway upgrade - New ghosts, 
//                           harder gameplay, disappearing map
// 
// (pre-release GCC versions:)
//  Crazy Otto           10/12/1981 (P1) Pac-man intro, legs, monsters, 
//                                       GENCOMP logo,
//                                       no eyes when ghosts return to jail
//  Crazy Otto           10/20/1981 (P2) Marquee (Mspac) intro, legs,
//                                       ghosts, Midway logo
//  Super Pac-Man        10/29/1981 (P3) Same as P2, with no legs, monsters
//  Super Pac-Man        10/29/1981 (P4) Same as P3, ghosts
//  Miss Pac-Man         11/12/1981 (P5) Marquee, "Pac-Woman" graphics, monsters
//  Ms. Pac-Man          11/25/1981 (P6) Same as P5, MsPac graphics, Bonnie
// 
// ' (Released versions)
//  Ms. Pac-Man          12/18/1981  Original GCC/Midway w/ aux board
//                                       (hardware protected)
//  Ms. Pac-Man          Bootleg (various) decoded aux board
//                                       (no hardware protection)
//  Ms. Pac-Man Attack   four new maps, broken fruit movement
//  Miss Pac Plus        four new maps (same as Attack, reversed)
// and of course, the "fast" and "cheat" versions of those above.
// 
// 
// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// 
// 
// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// 
// JUNK REGIONS OF ROMSPACE
// 
// 
//  There are a few regions of rom space that are unused by
//  the ms-pac program.  These can be used for your own patches,
//  or for data, or whatever.
// 
//  This list is most definitely incomplete.
//  Not all of these regions have been tested.
//  The list is inclusive of the start and end byte listed below.
// 
//  Some routines (like the self-test) can be dropped to give
//  you more romspace to work with.  You should be careful
//  however in that some chunks of romspace might not be free
//  with some rom hacks.
//  (0f3c - 0f4b for example)
// 
//  003b - 0041   7 bytes Tested
//  0f3c - 0fff 195 bytes Untested, nops
//  1fa9 - 1fff  87 bytes Untested, nops, 48 used for HACK3 cheat
//  2fba - 2fff  70 bytes Untested, nops
//  3ce0 - 3cff  32 bytes Untested, nops
//  8000 - 81ef 1f0 bytes Untested, bootleg hardware ONLY!
//  97c4 - 97cf   c bytes Untested, FF's
//  97d0 - 97f0  30 bytes Untested, message
//  9800 - 9fff     400 bytes not available on "pure" mspac.
//   
//   Similarly, there are chunks of code in the 0x0000-0x3fff area that are previously
//   used for Pac functionality that has been replaced by the aux roms, which can be
//   re-purposed.
//   
//   If you're working with a bootleg romset, then the roms specific
//   to the Aux Board, namely "BOOT5" 0x8000-0x8fff, has a lot of space
//   previously used by the patching mechanism, in 0x8000-0x87ff, which 
//   can be re-used for other code/tables.
// 
// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// 
// Ms Pacman Aux board information (GCC/Midway Pac-Man "Upgrade")
// 
// ED note:  The U5, U6 and U7 notes below have yet to be confirmed.
// 
//  It turns out the bootleg is the decrypted version with the
//  checksum check removed and interrupt mode changed to 1.
// 
//  u7= boot 4($3000-$3fff) other than 4 bytes(checksum check
//  and interupt mode)
// 
//  u6= boot 6($9000-$9fff). The second half of u6 gets mirrored
//  Renders to the second half of boot5($8800-$8fff) where it
//  is used.
//  u5= first half of boot5($8000-$87ff)
// 
//  $8000-$81ef contain 8 byte patches that are overlayed on
//  locations in $0000-$2fff
// 
//  The Ms Pacman aux board is not activated with the
//  mainboard.  As near as I can tell it requires a sequence
//  of bytes starting at around 3176 and ending with 3196. The
//  location of the bytes doesn't seem to matter, just that
//  those bytes are executed. That sequence of bytes includes
//  a write to 5006 so I'm using that to bankswitch, but that
//  is not accurate. The actual change is I believe at $317D.
//  The aux board can also be deactivated. A read to any
//  of the several 8 byte chunks listed will cause the Ms Pac
//  roms to disappear and Pacman to show up.  As a result I
//  couldn't verify what they contained. They should be the
//  same as the pacman roms, but I don't see how it could
//  matter. These areas can be accessed by the random number
//  generator at $2a23 and the board is deactivated but is
//  immediately reactivated. So the net result is no change.
//  The exact trigger for this is not yet known.
// 
//  deactivation, 8 bytes starting at:
//  $38,$3b0,$1600,$2120,$3ff0,$8000
// 
//  David Widel
//  d_widel@hotmail.com
// 
// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// 
// Ghost names:
// 
//           Pac-Man         Otto            Ms pre      Ms Release
// 
// Red         Shadow/Blinky   Mad Dog/Plato   Blinky      Blinky
// Pink        Speedy/Pinky    Killer/Darwin   Pinky       Pinky
// Cyan        Bashful/Inky    Brute/Freud     Inky        Inky
// Orange      Pokey/Clyde     Sam/Newton      Bonnie      Sue
// 
// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// 
// ram:
//  4c00 unknown
//  4c01 unknown
// 
// Sprite variables
// 
//  4c02 red ghost sprite number
//  4c03 red ghost color entry
//  4c04 pink ghost sprite number
//  4c05 pink ghost color entry
//  4c06 blue ghost sprite number
//  4c07 blue ghost color entry
//  4c08 orange ghost sprite number
//  4c09 orange ghost color entry
//  4c0a pacman sprite number
//  4c0b pacman color entry
//  4c0c fruit sprite number
//  4c0d fruit sprite entry
// 
//  4c20 sprite data that goes to the hardware sprite system
// 
//  4c22-4c2f sprite positions for spriteram2
//  4c32-4c3f sprite number and color for spriteram
//  
//  4C40-4C41 used for moving fruit positions
//  4C42-4C43 used to hold address of the fruit path
//  4c44-4c7f unused/unknown
// 
// Tasks and Timers
// 
//  4c80 \ pointer to the end of the tasks list
//  4c81 /
//  4c82 \ pointer to the beginning of the tasks list
//  4c83 /
//  4c84 8 bit counter (0x00 to 0xff) used by sound routines
//  4c85 8 bit counter (0xff to 0x00) (unused)
//  4c86 counter 0: 0..5 10..15 20..25  ..  90..95 - hundreths
//  4c87 counter 1: 0..9 10..19 20..29  ..  50..59 - seconds
//  4c88 counter 2: 0..9 10..19 20..29  ..  50..59 - minutes
//  4c89 counter 3: 0..9 10..19 20..29  ..  90..99 - hours
// 
//  4c8a number of counter limits changes in this frame (to init time)
//   0x01 1 hundredth
//   0x02 10 hundredths
//   0x03 1 second
//   0x04 10 seconds
//   0x05 1 minute
//   0x06 10 minutes
//   0x07 1 hour
//   0x08 10 hours
//   0x09 100 hours
//  4c8b random number generation (unused)
//  4c8c random number generation (unused)
// 
//  4c90-4cbf scheduled tasks list (run inside IRQ)
//   16 entries, 3 bytes per entry
//   Format:
//   byte 0: scheduled time
//                       7 6 5 4 3 2 1 0
//                       | | | | | | | |
//                       | | ------------ number of time units to wait
//                       | |
//                       ---------------- time units
//                                               0x40 -> 10 hundredths
//                                               0x80 -> 1 second
//                                               0xc0 -> 10 seconds
//   byte 1: index for the jump table
//   byte 2: parameter for b
//   these tasks are assigned using RST #30, with the three data bytes immediatly after the call
// used for the timer, index and parameter
//   these tasks are decoded at routine starting at #0221  
// 
//  4cc0-4ccf tasks to execute outside of IRQ
//   0xFF fill for empty task
//   16 entries, 2 bytes per entry
//   Format:
//   byte 0: routine number
//   byte 1: parameter
//   these tasks are assigned using RST #28, with the two data bytes immedately after the call used
// for the routine number and parameter
//   alternately, tasks can be assigned by manually loading B and C with routine and parameter, and
// then executing call #0042
//   tasks are decoded at routine starting at #238D
// 
// Game variables
// ** note - need to be sorted
// 
//     4DD2    FRUITP  fruit position
//     4DD4    FVALUE  value of the current fruit (0=no fruit)
//     4C40    COUNT current place in fruit path
//     4E0C    FIRSTF  flag to indicate that first fruit has been released
//     4E0D    SECONDF flag to indicate that second fruit has been eaten
//     4C41    BCNT    current place within bounce
//     4C42    PATH    pointer to the path the fruit is currently following
//     4E0E    DOTSEAT how many dots the current player has eaten
//     4EBC    BNOISE  set bit 5 of BNOISE to make the bounce sound
// 
//  4d00 red ghost Y position (bottom to top = decreases)
//  4d01 red ghost X position (left to right = decreases)
//  4d02 pink ghost Y position (bottom to top = decreases)
//  4d03 pink ghost X position (left to right = decreases)
//  4d04 blue ghost Y position (bottom to top = decreases)
//  4d05 blue ghost X position (left to right = decreases)
//  4d06 orange ghost Y position (bottom to top = decreases)
//  4d07 orange ghost X position (left to right = decreases)
// 
//  4d08 pacman Y position
//  4d09 pacman X position
// 
//  4d0a red ghost Y tile pos (mid of tile) (bottom to top = decrease)
//  4d0b red ghost X tile pos (mid of tile) (left to right = decrease)
//  4d0c pink ghost Y tile pos (mid of tile) (bottom to top = decrease)
//  4d0d pink ghost X tile pos (mid of tile) (left to right = decrease)
//  4d0e blue ghost Y tile pos (mid of tile) (bottom to top = decrease)
//  4d0f blue ghost X tile pos (mid of tile) (left to right = decrease)
//  4d10 orange ghost Y tile pos (mid of tile) (bottom to top = decrease)
//  4d11 orange ghost X tile pos (mid of tile) (left to right = decrease)
//  4d12 pacman tile pos in demo and cut scenes
//  4d13 pacman tile pos in demo and cut scenes
// 
//  for the following, last move was 
//   (A) 0x00 = left/right, 0x01 = down, 0xff = up
//   (B) 0x00 = up/down, 0x01 = left, 0xff = right
//  4d14 red ghost Y tile changes (A)
//  4d15 red ghost X tile changes (B)
//  4d16 pink ghost Y tile changes (A)
//  4d17 pink ghost X tile changes (B)
//  4d18 blue ghost Y tile changes (A)
//  4d19 blue ghost X tile changes (B)
//  4d1a orange ghost Y tile changes (A)
//  4d1b orange ghost X tile changes (B)
//  4d1c pacman Y tile changes (A)
//  4d1d pacman X tile changes (B)
// 
//  4d1e red ghost y tile changes
//  4d1f red ghost x tile changes
//  4d20 pink ghost y tile changes
//  4d21 pink ghost x tile changes
//  4d22 blue ghost y tile changes
//  4d23 blue ghost x tile changes
//  4d24 orange ghost y tile changes
//  4d25 orange ghost x tile changes
//  4d26 wanted pacman tile changes
//  4d27 wanted pacman tile changes
// 
//   character orientations:
//   0 = right, 1 = down, 2 = left, 3 = up
//  4d28 previous red ghost orientation (stored middle of movement)
//  4d29 previous pink ghost orientation (stored middle of movement)
//  4d2a previous blue ghost orientation (stored middle of movement)
//  4d2b previous orange ghost orientation (stored middle of movement)
//  4d2c red ghost orientation (stored middle of movement)
//  4d2d pink ghost orientation (stored middle of movement)
//  4d2e blue ghost orientation (stored middle of movement)
//  4d2f orange ghost orientation (stored middle of movement)
// 
//  4d30 pacman orientation
// 
//   these are updated after a move
//  4d31 red ghost Y tile position 2 (See 4d0a)
//  4d32 red ghost X tile position 2 (See 4d0b)
//  4d33 pink ghost Y tile position 2
//  4d34 pink ghost X tile position 2
//  4d35 blue ghost Y tile position 2
//  4d36 blue ghost X tile position 2
//  4d37 orange ghost Y tile position 2
//  4d38 orange ghost X tile position 2
// 
//  4d39 pacman Y tile position (0x22..0x3e) (bottom-top = decrease)
//  4d3a pacman X tile position (0x1e..0x3d) (left-right = decrease)
// 
//  4d3c wanted pacman orientation
// 
//  path finding algorithm:
//  4d3b  best orientation found 
//  4d3d  saves the opposite orientation
//  4d3e-4d3f  saves the current tile position
//  4d40-4d41  saves the destination tile position
//  4d42-4d43  temp resulting position
//  4d44-4d45  minimum distance^2 found
// 
//  4dc7  current orientation we're trying
//  4d46-4d85  speed bit patterns (difficulty dependant)
//  4D46-4D49       speed bit patterns for pacman in normal state
//  4D4A-4D4D       speed bit patterns for pacman in big pill state
//  4D4E-4D51       speed bit patterns for second difficulty flag
//  4D52-4D55       speed bit patterns for first difficulty flag
//  4D56-4D59       speed bit patterns for red ghost normal state
//  4D5A-4D5D       speed bit patterns for red ghost blue state
//  4D5E-4D61       speed bit patterns for red ghost tunnel areas
//  4D62-4D65       speed bit patterns for pink ghost normal state
//  4D66-4D69       speed bit patterns for pink ghost blue state
//  4D6A-4D6D       speed bit patterns for pink ghost tunnel areas
//  4D6E-4D71       speed bit patterns for blue ghost normal state
//  4D72-4D75       speed bit patterns for blue ghost blue state
//  4D76-4D79       speed bit patterns for blue ghost tunnel areas
//  4D7A-4D7D       speed bit patterns for orange ghost normal state
//  4D7E-4D81       speed bit patterns for orange ghost blue state
//  4D82-4D83       speed bit patterns for orange ghost tunnel areas
// 
//  4d86-4d93
//      Difficulty related table. Each entry is 2 bytes, and
//      contains a counter value.  when the counter at 4DC2
//      reaches each entry value, the ghosts changes their
//      orientation and 4DC1 increments it's value to point to
//      the next entry
// 
//  4d94 counter related to ghost movement inside home
//  4d95-4d96 number of units before ghost leaves home (no change w/ pills)
//  4d97-4d98 inactivity counter for units of the above
// 
//  4d99 - 4d9c
//      These values are normally 0, but are changed to 1 when a ghost has
//      entered a tunnel slowdown area
//  4d99 aux var used by red ghost to check positions
//  4d9a aux var used by pink ghost to check positions
//  4d9b aux var used by blue ghost to check positions
//  4d9c aux var used by orange ghost to check positions
// 
//  4d9d delay to update pacman movement
//   not 0xff - the game doesn't move pacman, but decrements instead
//   0x01 when eating pill
//   0x06 when eating big pill
//   0xff when not eating a pill
//  4d9e related to number of pills eaten before last pacman move
//  4d9f eaten pills counter after pacman has died in a level
//   used to make ghosts go out of home after # pills eaten
// 
//   ghost substates:
//   0 = at home
//   1 = going for pac-man
//   2 = crossing the door
//   3 = going to the door
// 
//  4da0 red ghost substate (if alive)
//  4da1 pink ghost substate (if alive)
//  4da2 blue ghost substate (if alive)
//  4da3 orange ghost substate (if alive)
//  4da4 # of ghost killed but no collision for yet [0..4]
//  4da5 pacman dead animation state (0 if not dead)
//  4da6 power pill effect (1=active, 0=no effect)
// 
//  4da7 red ghost blue flag (0=not blue)
//  4da8 pink ghost blue flag (0=not blue)
//  4da9 blue ghost blue flag (0=not blue)
//  4daa orange ghost blue flag (0=not blue)
// 
//  4dab killing ghost state
//   0 = nothing
//   1 = kill red ghost
//   2 = kill pink ghost
//   3 = kill blue ghost
//   4 = kill orange ghost
// 
//   ghost states:
//   0 = alive
//   1 = dead
//   2 = entering home after being killed
//   3 = go left after entering home after dead (blue)
//   3 = go right after entering home after dead (orange)
//  4dac red ghost state
//  4dad pink ghost state
//  4dae blue ghost state
//  4daf orange ghost state
// 
//  4db0 related to difficulty, appears to be unused 
// 
//   with these, if they're set, ghosts change orientation
//  4db1 red ghost change orientation flag
//  4db2 pink ghost change orientation flag
//  4db3 blue ghost change orientation flag
//  4db4 orange ghost change orientation flag
//  4bd5 pacman change orientation flag
// 
// Difficulty settings
// 
//  4db6 1st difficulty flag (rel 4dbb) (cruise elroy 1)
//   0: red ghost goes to upper right corner on scatter
//   1: red ghost goes for pacman on scatter
//   1: red ghost goes faster
//  4db7 2nd difficulty flag (rel 4dbc) (cruise elroy 2)
//   when set, red uses a faster bit speed pattern
//   0: not set
//   1: faster movement
//  4db8 pink ghost counter to go out of home limit (rel 4e0f)
//  4db9 blue ghost counter to go out of home limit (rel 4e10)
//  4dba orange ghost counter to go out of home limit (rel 4e11)
//  4dbb remainder of pills when first diff. flag is set (cruise elroy 1)
//  4dbc remainder of pills when second diff. flag is set (cruise elroy 2)
//  4dbd-4dbe Time the ghosts stay blue when pacman eats a big pill
// 
//  4dbf 1=pacman about to enter a tunnel, otherwise 0
// 
// Counters
// 
//  4dc0 changes every 8 frames; used for ghost animations
//  4dc1 orientation changes index [0..7]. used to get value 4d86-4d93
//   0: random ghost movement, 1: normal movement (?)
//  4dc2-4dc3 counter related to ghost orientation changes
//  4dc4 counter 0..8 to handle things once every 8 times
//  4dc5-4dc6 counter started after pacman killed
//  4dc7 counter for current orientation we're trying
//  4dc8 counter used to change ghost colors under big pill effects
// 
//  4dc9-4dca pointer to pick a random value from the ROM (routine 2a23)
// 
//  4dcb-4dcc counter while ghosts are blue. effect ceases at 0
//  4dce counter started after insert coin (LED and 1UP/2UP blink)
//  4dcf counter to handle power pill flashes
//  4dd0 current number of killed ghosts (0..4) (rel 4da5)
// 
//  4dd1 killed ghost animation state
//   if 4da4 != 0:
//    4dd1 = 0: killed, showing points per kill
//    4dd1 = 1: wating
//    4dd1 = 2: clearing killed ghost, changing state to 0
//  4dd2-4dd3 fruit position (sometimes for other sprite)
// 
//  4dd4 entry to fruit points or 0 if no fruit
//  4dd6 used for LED state( 1: game waits for 1P/2P start button press)
// 
// Main States
// 
//  4e00 main routine number
//   0: init
//   1: demo
//   2: coin inserted
//   3: playing
//  4e01 main routine 0, subroutine #
//  4e02 main routine 1, subroutine # (related to blue maze bug)
//  4e03 main routine 2, subroutine #
//  4e04 level state subroutine #
//   3=ghost move, 2=ghost wait for start
//   (set to 2 to pause game)
// 
//  4e06 state in first cutscene (pac-man only)
//  4e07 state in second cutscene (pac-man only)
//  4e08 state in third cutscene (pac-man only)
// 
//  4e09 current player number:  0=P1, 1=P2
// 
//  4e0a-4e0b pointer to current difficulty settings
// 
//  4C40 COUNT current place in fruit path
//  4E0C FIRSTF  flag to indicate that first fruit has been released
//  4E0D SECONDF flag to indicate that second fruit has been eaten
//  4C41 BCNT current place within bounce
//  4C42 PATH pointer to the path the fruit is currently following
//  4E0E DOTSEAT how many dots the current player has eaten
//  4EBC BNOISE set bit 5 of BNOISE to make the bounce sound
// 
//  4e0c first fruit flag (1 if fruit has appeared)
//  4e0d second fruit flag (1 if fruit has appeared)
//  4e0e number of pills eaten in this level
//  4e0f counter incremented if orange, blue and pink ghosts are home
//   and pacman is eating pills.
//   used to make pink ghost leave home (rel 4db8)
//  4e10 counter incremented if orange, blue and pink ghosts are home
//   and pacman is eating pills.
//   used to make blue ghost leave home (rel 4db9)
//  4e11 counter incremented if orange, blue and pink ghosts are home
//   and pacman is eating pills.
//   used to make orange ghost leave home (rel 4db9)
//  4e12 1 after dying in a level, reset to 0 if ghosts have left home
//   because of 4d9f
// 
//  4e13 current level
//  4e14 real number of lives
//  4e15 number of lives displayed
// 
//  4e16-4e33 0x13 pill data entries. each bit means if a pill is there
//   or not (1=yes 0=no)
//   the pills start at upper right corner, go down, then left.
//   first pill is bit 7 of 4e16
//  4e34-4e37 power pills data entries
//  4e38-4e65 copy of level data (430a-4e37)
// 
// coins, credits
// 
//  4e66 last 4 SERVICE1 to detect transitions
//  4e67 last 4 COIN2 to detect transitions
//  4e68 last 4 COIN1 to detect transitions
// 
//  4e69 coin counter (coin->credts, this gets decremented)
//  4e6a coin counter timeout, used to write coin counters
// 
//   these are copied from the dipswitches
//  4e6b number of coins per credit
//  4e6c number of coins inserted
//  4e6d number of credits per coin
//  4e6e number of credits, 0xff for free play
//  4e6f number of lives
//  4e70 number of players (0=1 player, 1=2 players)
//  4e71 bonus/life
//   0x10 = 10000 0x15 = 15000
//   0x20 = 20000 0xff = none
//  4e72 cocktail mode (0=no, 1=yes)
//  4e73-4e74 pointer to difficulty settings
//   4e73: 68=normal 7d=hard checked at start of game
//  4e75 ghost names mode (0 or 1)
// 
//   SCORE AABBCC
//  4e80-4e82 score P1 80=CC 81=BB 82=CC
//  4e83 P1 got bonus life?  1=yes
//  4e84-4e86 score P2 84=CC 85=BB 86=CC
//  4e87 P2 got bonus life?  1=yes
//  4e88-4e8a high score 88=CC 89=BB 8A=CC
// 
// Sound Registers
// 
//       ;; these 16 values are copied to the hardware every vblank interrupt.
// 
// CH1_FREQ0       EQU     4e8c    ; 20 bits
// CH1_FREQ1       EQU     4e8d
// CH1_FREQ2       EQU     4e8e
// CH1_FREQ3       EQU     4e8f
// CH1_FREQ4       EQU     4e90
// CH1_VOL         EQU     4e91
// CH2_FREQ1       EQU     4e92    ; 16 bits
// CH2_FREQ2       EQU     4e93
// CH2_FREQ3       EQU     4e94
// CH2_FREQ4       EQU     4e95
// CH2_VOL         EQU     4e96
// CH3_FREQ1       EQU     4e97    ; 16 bits
// CH3_FREQ2       EQU     4e98
// CH3_FREQ3       EQU     4e99
// CH3_FREQ4       EQU     4e9a
// CH3_VOL         EQU     4e9b
// 
// SOUND_COUNTER   EQU     4c84    ; counter, incremented each VBLANK
//                               ; (used to adjust sound volume)
// 
// EFFECT_TABLE_1  EQU     3b30    ; channel 1 effects. 8 bytes per effect
// EFFECT_TABLE_2  EQU     3b40    ; channel 2 effects. 8 bytes per effect
// EFFECT_TABLE_3  EQU     3b80    ; channel 3 effects. 8 bytes per effect
// 
// #if MSPACMAN
// SONG_TABLE_1    EQU     9685    ; channel 1 song table
// SONG_TABLE_2    EQU     967d    ; channel 2 song table
// SONG_TABLE_3    EQU     968d    ; channel 3 song table
// #else
// SONG_TABLE_1    EQU     3bc8
// SONG_TABLE_2    EQU     3bcc
// SONG_TABLE_3    EQU     3bd0
// #endif
// 
// CH1_E_NUM       EQU     4e9c    ; effects to play sequentially (bitmask)
// CH1_E_1         EQU     4e9d    ; unused
// CH1_E_CUR_BIT   EQU     4e9e    ; current effect
// CH1_E_TABLE0    EQU     4e9f    ; table of parameters, initially copied from ROM
// CH1_E_TABLE1    EQU     4ea0
// CH1_E_TABLE2    EQU     4ea1
// CH1_E_TABLE3    EQU     4ea2
// CH1_E_TABLE4    EQU     4ea3
// CH1_E_TABLE5    EQU     4ea4
// CH1_E_TABLE6    EQU     4ea5
// CH1_E_TABLE7    EQU     4ea6
// CH1_E_TYPE      EQU     4ea7
// CH1_E_DURATION  EQU     4ea8
// CH1_E_DIR       EQU     4ea9
// CH1_E_BASE_FREQ EQU     4eaa
// CH1_E_VOL       EQU     4eab
// 
// 4EAC repeats the above for channel 2
// 4EBC repeats the above for channel 3
// 
// CH1_W_NUM       EQU     4ecc    ; wave to play (bitmask)
// CH1_W_1         EQU     4ecd    ; unused
// CH1_W_CUR_BIT   EQU     4ece    ; current wave
// CH1_W_SEL       EQU     4ecf
// CH1_W_4         EQU     4ed0
// CH1_W_5         EQU     4ed1
// CH1_W_OFFSET1   EQU     4ed2    ; address in ROM to find the next byte
// CH1_W_OFFSET2   EQU     4ed3    ; (16 bits)
// CH1_W_8         EQU     4ed4
// CH1_W_9         EQU     4ed5
// CH1_W_A         EQU     4ed6
// CH1_W_TYPE      EQU     4ed7
// CH1_W_DURATION  EQU     4ed8
// CH1_W_DIR       EQU     4ed9
// CH1_W_BASE_FREQ EQU     4eda
// CH1_W_VOL       EQU     4edb
// 
// 4EDC repeats the above for channel 2
// 4EEC repeats the above for channel 3
// 
// 
// Runtime
// 
//  4F00  Is set to 1 during intermissions and parts of the attract mode, otherwise 0
//  4F01-4FBF Stack
//  4FC0-4FEF Unused
//  4FF0-4FFF Sprite RAM
// 
// 
// 
// 
// Memory mapped ports:
// Read ports:
//  port# Name ; condition & change   Example value
//  ----------------------------------------------------------------------
//  5000 IN0 ; When Nothing pressed    #FF
//    ; Joystick 1 UP clears bit 0  #FE
//    ; Joystick 1 LEFT clears bit 1  #FD
//    ; Joystick 1 RIGHT clears bit 2  #FB
//    ; Joystick 1 DOWN clears bit 3  #F7
//    ; Rack test clears bit 4  #EF
//    ; Coin 1 inserted clears bit 5  #DF
//    ; Coin 2 inserted clears bit 6  #BF
//    ; Service 1 pressed clears bit 7 #7F
// 
//  5040 IN1 ; When Nothing pressed   #FF
//    ; Joystick 2 UP clears bit 0  #FE
//    ; Joystick 2 LEFT clears bit 1  #FD
//    ; Joystick 2 RIGHT clears bit 2  #FB
//    ; Joystick 2 DOWN clears bit 3  #F7
//    ; service mode switch clears bit 4 #EF
//    ; Player 1 start button clears bit 5 #DF
//    ; Player 2 start button clears bit 6 #BF
//    ; Cocktail cabinet DIP clears bit 7 #7F
// 
//  5080 DSW 1 ; controls free play/coins per credit, # of lives per game, 
//    ; points needed for bonus, rack test, game freeze
// 
// 
// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// 
//      PAC-MAN SPRITE CODES
// 
//      00-07   fruits
//      08-0D   naked ghosts for cutscenes
//      0E-0F   empty
//      10-1B   big pacman
//      1C-1D   ghost in panic mode
//      1E-1F   empty
//      20-27   ghosts
//      28-2B   points
//      2C-2F   pacmans
//      30      big pacman
//      31      explosion
//      32-33   broken ghost
//      34-3F   pacman dead
// 
// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// 
//  MS. PAC-MAN SPRITE CODES
// 
//  00  cherry
//  01 strawberry
//  02 peach
//  03 pretzel
//  04  apple
//  05  pear
//  06 banana
//  07  sack that is dropped from stork in act 3
//  08  100
//  09 200
//  0A 500
//  0B 700
//  0C 1000
//  0D 2000
//  0E 5000
//  0F junior pac-man seen in act 3
//  10-17 parts of ACT director's sign
//  18 stork
//  19-1B  pac-man
//  1C-1D ghost in panic mode
//  1E heart
//  1F empty
//  20-27 ghosts
//  28 200
//  29 400
//  2A 800
//  2B 1600
//  2C stork
//  2D ms pacman 
//  2E pac-man
//  2F ms pacman
//  30 stork head + beak
//  31 ms pacman
//  32 pac-man
//  33-3F ms pacman (used during dying animation)
//  40-7F same as 00-3F, but upside down
//  
// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// 
//      PACMAN TILE CODES
// 
//      00-0F   hex digits
//      10-15   pills
//      16-1F   empty
//      ...
//      40-5B   space + ASCII chars
//      5C      copyright
//      5D-5F   PTS
//      ...
//      C0-FF   map obstacles
// 
//      SPECIAL COLOR ENTRIES
// 
//      18      for ghost's door
//      1A      for pacman's and ghost's initial map positions
//      1B      for tunnel area
// 
//      PACMAN TILE CONFIGURATION
// 
//      tile position x can go from 0x1e to 0x3d.
//      0x1d == wraparound -> 0x3d
//      0x3e == wraparound -> 0x1e
//      tile position y can go from 0x22 to 0x3e.
//      Why?
//      Because of the graphics hardware.
//      With that configuration, you can convert directly between 
//  tile position to hardware sprite positions
// 
// 
// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// 

void reset(void)

{
  ushort uVar1;
  byte c;
  task_core_e index;
  char cVar2;
  byte n;
  in0_t *piVar3;
  byte *s;
  
                    // 
                    //   rst 0 - initialization
                    //   init
  disableMaskableInterrupts();
                    // PAC
                    // 0001  3e3f      ld      a,#3f
                    // 
  piVar3 = &hardware_IN0;
  cVar2 = '\b';
  c = 0;
  do {
    *piVar3 = (in0_t)0x0;
    piVar3 = (in0_t *)((ushort)piVar3 & 0xff00 | (ushort)(byte)((char)piVar3 + 1));
    cVar2 = cVar2 + -1;
  } while (cVar2 != '\0');
  s = hardware_video_ram;
  cVar2 = '\x04';
  do {
    write_volatile_1(hardware_DSW2_watchdog,c);
    write_volatile_1(hardware_coin_counter,c);
    c = 0x40;
    do {
      *s = 0x40;
      n = (char)s + 1;
      uVar1 = (ushort)s & 0xff00;
      s = (byte *)(uVar1 | n);
    } while (n != 0);
    s = (byte *)((ushort)(byte)((char)(uVar1 >> 8) + 1) << 8);
    cVar2 = cVar2 + -1;
  } while (cVar2 != '\0');
  cVar2 = '\x04';
  do {
    write_volatile_1(hardware_DSW2_watchdog,c);
    write_volatile_1(hardware_coin_counter,0);
    c = 0xf;
    do {
      *s = 0xf;
      n = (char)s + 1;
      uVar1 = (ushort)s & 0xff00;
      s = (byte *)(uVar1 | n);
    } while (n != 0);
    s = (byte *)((ushort)(byte)((char)(uVar1 >> 8) + 1) << 8);
    cVar2 = cVar2 + -1;
  } while (cVar2 != '\0');
  setInterruptMode(1);
  write_volatile_1(hardware_coin_counter,0);
  hardware_IN0 = (in0_t)0x1;
  enableMaskableInterrupts();
  halt();
  write_volatile_1(hardware_DSW2_watchdog,1);
  c = 0;
  ARRAY_ram_4f5c._98_2_ = 0x2359;
  memset((byte *)&hardware_IN0,0,8);
  n = 0xbe;
  ARRAY_ram_4f5c._98_2_ = 0x235f;
  s = (byte *)memset((byte *)&start_of_sprites_address,c,0xbe);
  ARRAY_ram_4f5c._98_2_ = 0x2360;
  s = (byte *)memset(s,c,n);
  ARRAY_ram_4f5c._98_2_ = 0x2361;
  s = (byte *)memset(s,c,n);
  ARRAY_ram_4f5c._98_2_ = 0x2362;
  memset(s,c,n);
  ARRAY_ram_4f5c._98_2_ = 0x2368;
  memset((byte *)&hardware_IN1,c,0x40);
  write_volatile_1(hardware_DSW2_watchdog,c);
  ARRAY_ram_4f5c._98_2_ = 0x236e;
  c = T06_clears_color_RAM();
  write_volatile_1(hardware_DSW2_watchdog,c);
  ARRAY_ram_4f5c._98_2_ = 0x2376;
  c = T00_clear_whole_screen_or_maze(0);
  write_volatile_1(hardware_DSW2_watchdog,c);
  p_task_list_next_free = tasks_to_execute_outside_of_irq;
  p_task_list_begin = tasks_to_execute_outside_of_irq;
  ARRAY_ram_4f5c._98_2_ = 0x2387;
  memset((byte *)tasks_to_execute_outside_of_irq,0xff,0x40);
  hardware_IN0 = (in0_t)0x1;
  enableMaskableInterrupts();
  s = _STACK_END;
  do {
    do {
      index = p_task_list_begin->value;
    } while ((char)index < '\0');
    p_task_list_begin->value = ~clear_whole_screen_or_maze;
    uVar1 = (ushort)p_task_list_begin & 0xff00;
    *(undefined *)(uVar1 | (byte)((char)p_task_list_begin + 1)) = 0xff;
    c = (char)p_task_list_begin + 2;
    p_task_list_begin = (task_core_t *)(uVar1 | c);
    if (c == 0) {
      p_task_list_begin = (task_core_t *)CONCAT11((char)(uVar1 >> 8),0xc0);
    }
    *(undefined2 *)(s + -2) = 0x238d;
                    // WARNING: Return address prevents inlining here
    *(undefined2 *)(s + -4) = 0x23a8;
    jump_table_fn(*(undefined **)(s + -4),index);
    s = s + -2;
  } while( true );
}



// rst 8 - memset()
// Fill HL to HL+B with A

void * memset(byte *s,byte c,byte n)

{
  do {
    *s = c;
    s = s + 1;
    n = n - 1;
  } while (n != 0);
  return s;
}



void RET(void)

{
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void T10_setup_difficulty(undefined2 param_1)

{
  char cVar1;
  byte *pbVar2;
  
  cVar1 = (char)((ushort)param_1 >> 8);
  if (cVar1 == '\0') {
    cVar1 = *(char *)pointer_to_current_difficulty_settings;
  }
  pbVar2 = &difficulty1_6_bytes_t_ARRAY_ram_0796[0].speed_and_orientation_index +
           (byte)(cVar1 * '\x06');
  copy_difficulty_related_data(difficulty2_t_ARRAY_ram_330f[0].field_0x0 + (byte)(*pbVar2 * '*'));
  related_to_difficulty = pbVar2[1];
  set_pink_ghost_counter_to_go_out_of_home_limit
            (&difficulty4_ghost_out_of_home_t_ARRAY_ram_0843[0].counter_for_pink +
             (byte)(pbVar2[2] * '\x03'));
  _red_ghost_remainder_of_pills_when_first_difficulty_flag_is_set =
       *(undefined2 *)
        (&difficulty3_t_ARRAY_ram_084f[0].numbre_of_pills_difficulty_flag1 +
        (byte)(pbVar2[3] * '\x02'));
  time_the_ghosts_stay_blue_when_pacman_eats_a_big_pill =
       *(word *)((short)&time_ghost_stay_blue + (ushort)(byte)(pbVar2[4] * '\x02'));
  number_of_units_before_ghost_leaves_home =
       *(word *)((short)&number_of_unit_before_ghosts_leaves_home +
                (ushort)(byte)(pbVar2[5] * '\x02'));
  T1B_draw_fruits_right_screen();
  return;
}



// rst 10  (for dereferencing pointers to bytes)
// HL = HL + A, , A := (HL)
// HL = base address of table
// A  = index
// after the call, A gets the data in HL+A
// 
// For resume :
// 
// return lookup_table[index] ou return HL[A]
// 
// after the call :
// HL = HL + A
// A = *HL
// 

byte dereference_pointer_to_byte(byte *lookup_table,byte index)

{
  return *(byte *)CONCAT11((char)((ushort)lookup_table >> 8) + CARRY1(index,(byte)lookup_table),
                           index + (byte)lookup_table);
}



// rst 18 (for dereferencing pointers to words)
// hl = hl + 2*b,  (hl) -> e, (++hl) -> d, de -> hl
// HL = base address of table
// B  = index
// after the call, HL gets the data in HL+(2*B).  DE becomes HL+2B
// modified: DE, A
// 
// return lookup_table[index] or return HL[2*B]

dereference_word_t dereference_pointer_to_word(word *lookup_table,byte index)

{
  byte bVar1;
  
  bVar1 = dereference_pointer_to_byte((byte *)lookup_table,index * '\x02');
  return (dereference_word_t)
         CONCAT23(CONCAT11(*(undefined *)((short)lookup_table + 1),bVar1),
                  CONCAT21((undefined *)((short)lookup_table + 1),bVar1));
}



// WARNING: This is an inlined function
// rst 20 (jump table)
// 
// Uses A as a vector to jump to the location indicated by 2*A after the call
// For example, if A has #00 and the two bytes following the call are #AB and #CD, the program will
// jump to #CDAB
// 

void jump_table_fn(undefined *lookup_table,byte index)

{
  byte bVar1;
  
  bVar1 = dereference_pointer_to_byte(lookup_table,index * '\x02');
                    // WARNING: Could not recover jumptable at 0x0027. Too many branches
                    // WARNING: Treating indirect jump as call
  (*(code *)CONCAT11(lookup_table[1],bVar1))(lookup_table + 1);
  return;
}



// WARNING: This is an inlined function
// rst 28
// takes the 2 bytes after the call as data and inserts them into the task list
// 

void insert_task(task_core_t *task)

{
  ushort uVar1;
  undefined uVar2;
  byte bVar3;
  
  uVar2 = task->param;
  p_task_list_next_free->value = task->value;
  uVar1 = (ushort)p_task_list_next_free & 0xff00;
  *(undefined *)(uVar1 | (byte)((char)p_task_list_next_free + 1)) = uVar2;
  bVar3 = (char)p_task_list_next_free + 2;
  p_task_list_next_free = (task_core_t *)(uVar1 | bVar3);
  if (bVar3 == 0) {
    p_task_list_next_free = (task_core_t *)CONCAT11((char)(uVar1 >> 8),0xc0);
  }
  return;
}



// WARNING: This is an inlined function

void add_timed_task(task_timed_t *task)

{
  byte rev_index;
  byte rev_index_found_empty;
  task_timed_t *tt_seek;
  
  tt_seek = scheduled_tasks_list_to_execute_inside_of_irq;
  rev_index = 16;
  do {
    if (*(char *)tt_seek == '\0') {
                    // empty space found
      rev_index_found_empty = 3;
      do {
                    // copy task_timed_t to task list
        *(code *)tt_seek = *(code *)task;
        task = (task_timed_t *)&task->index;
        tt_seek = (task_timed_t *)((ushort)tt_seek & 0xff00 | (ushort)(byte)((char)tt_seek + 1));
        rev_index_found_empty = rev_index_found_empty - 1;
      } while (rev_index_found_empty != 0);
                    // WARNING: Could not recover jumptable at 0x0064. Too many branches
                    // WARNING: Treating indirect jump as call
                    // jmp after task ptr...
      (*(code *)task)();
      return;
    }
    tt_seek = (task_timed_t *)((ushort)tt_seek & 0xff00 | (ushort)(byte)((char)tt_seek + 3));
    rev_index = rev_index - 1;
  } while (rev_index != 0);
  return;
}



void vblank(bool test_mode)

{
                    // rst 38 (vblank)
                    // INTERRUPT MODE 1 handler
                    // 
                    // ;; INTERRUPT MODE 2 (original hardware, non-bootlegs, puckman, pac plus)
                    // ;0038  af xor a
                    // ;0039  320050 ld (#5000),a
                    // ;003c  320750 ld (#5007),a   
                    // ;003f  c33800 jp #0038
                    // 
  if (test_mode != false) {
    interrupt_vector();
    return;
  }
  interrupt_vector_pacman_only();
  return;
}



// continuation of rst 28 from #002E
// this sub can be called with call #0042, if B and C are loaded manually
// 
// B and C have the data bytes
// 

void add_to_task_list(task_core_e task_value,byte task_param)

{
  ushort uVar1;
  byte bVar2;
  
  p_task_list_next_free->value = task_value;
  uVar1 = (ushort)p_task_list_next_free & 0xff00;
  *(byte *)(uVar1 | (byte)((char)p_task_list_next_free + 1)) = task_param;
  bVar2 = (char)p_task_list_next_free + 2;
  p_task_list_next_free = (task_core_t *)(uVar1 | bVar2);
  if (bVar2 == 0) {
    p_task_list_next_free = (task_core_t *)CONCAT11((char)(uVar1 >> 8),0xc0);
  }
  return;
}



// converts pac-mans sprites positions into a grid position
// 

byte * convert_xy_to_screen_position(sprite_coord_yx_t coord)

{
  char cVar1;
  
  cVar1 = (char)((ushort)coord >> 8);
  return hardware_screen_maze_area +
         (ushort)(byte)((char)coord - 0x20) +
         CONCAT11(((byte)(cVar1 * '\b') >> 7) << 1 | (byte)(cVar1 * '\x10') >> 7,cVar1 * ' ');
}



// WARNING: This function may have set the stack pointer
// part of the interrupt routine (non-test)
// continuation of RST 38 partially...  (vblank)
// (gets called from the #1f9b patch, from #0038)
// 

void interrupt_vector(void)

{
  ushort uVar1;
  undefined2 uVar2;
  undefined2 in_AF;
  byte c;
  task_core_e index_00;
  short index;
  char cVar3;
  sound_channel_20bits_t *psVar4;
  floating_sprite_coord_t *pfVar5;
  ushort uVar6;
  byte n;
  sound_channel_20bits_t *psVar7;
  hardware_floating_sprite_t *phVar8;
  floating_sprite_coord_t *pfVar9;
  in0_t *piVar10;
  byte *s;
  
  write_volatile_1(hardware_DSW2_watchdog,(byte)((ushort)in_AF >> 8));
  hardware_IN0 = (in0_t)0x0;
  disableMaskableInterrupts();
                    // save registers. they are restored starting at #01BF
                    // 
                    //  VBLANK - 1 (SOUND)
                    //  load the sound into the hardware
                    // 
  psVar7 = &channel1;
  psVar4 = &hardware_wave_info;
  index = 0x10;
  do {
    psVar4->freq0 = psVar7->freq0;
    psVar4 = (sound_channel_20bits_t *)&psVar4->freq1;
    psVar7 = (sound_channel_20bits_t *)&psVar7->freq1;
    index = index + -1;
  } while (index != 0);
                    //  voice 1 wave select
                    // 
  hardware_wave_select_1 = channel_1_wave.sel;
  if (channel_1_wave.num == 0) {
    hardware_wave_select_1 = channel_1_effect.table[0];
  }
                    //  voice 2 wave select
                    // 
  hardware_wave_select_2 = channel_2_wave.sel;
  if (channel_2_wave.num == 0) {
    hardware_wave_select_2 = channel_2_effect.table[0];
  }
                    //  voice 3 wave select
                    // 
  hardware_wave_select_3 = channel_3_wave.sel;
  if (channel_3_wave.num == 0) {
    hardware_wave_select_3 = channel_3_effect.table[0];
  }
                    // copy last frame calculated sprite data into sprite buffer
  phVar8 = &red_ghost_sprite;
  pfVar5 = sprite_positions_for_spriteram2;
  index = 28;
  do {
    pfVar5->x = *(byte *)phVar8;
    uVar2 = sprite_number_and_color_for_spriteram[1];
    pfVar5 = (floating_sprite_coord_t *)&pfVar5->y;
    phVar8 = (hardware_floating_sprite_t *)&phVar8->color;
    index = index + -1;
  } while (index != 0);
                    // update sprite data, adjusting to hardware
  sprite_positions_for_spriteram2[0] =
       sprite_positions_for_spriteram2[0] & 0xff00 |
       (ushort)(byte)((sprite_positions_for_spriteram2[0].x << 1 |
                      sprite_positions_for_spriteram2[0].x >> 7) << 1 |
                     (sprite_positions_for_spriteram2[0].x << 1) >> 7);
  c = (sprite_positions_for_spriteram2[1].x << 1 | sprite_positions_for_spriteram2[1].x >> 7) << 1 |
      (sprite_positions_for_spriteram2[1].x << 1) >> 7;
  uVar1 = sprite_positions_for_spriteram2[1] & 0xff00;
  sprite_positions_for_spriteram2[1] = uVar1 | c;
  sprite_positions_for_spriteram2[2].x =
       (sprite_positions_for_spriteram2[2].x << 1 | sprite_positions_for_spriteram2[2].x >> 7) << 1
       | (sprite_positions_for_spriteram2[2].x << 1) >> 7;
  sprite_positions_for_spriteram2[3].x =
       (sprite_positions_for_spriteram2[3].x << 1 | sprite_positions_for_spriteram2[3].x >> 7) << 1
       | (sprite_positions_for_spriteram2[3].x << 1) >> 7;
  sprite_positions_for_spriteram2[4] =
       sprite_positions_for_spriteram2[4] & 0xff00 |
       (ushort)(byte)((sprite_positions_for_spriteram2[4].x << 1 |
                      sprite_positions_for_spriteram2[4].x >> 7) << 1 |
                     (sprite_positions_for_spriteram2[4].x << 1) >> 7);
  sprite_positions_for_spriteram2[5].x =
       (sprite_positions_for_spriteram2[5].x << 1 | sprite_positions_for_spriteram2[5].x >> 7) << 1
       | (sprite_positions_for_spriteram2[5].x << 1) >> 7;
  if (killed_ghost_animation_state == 1) {
    uVar6 = (ushort)(byte)(number_of_ghost_killed_but_no_collision_for_yet * '\x02');
    sprite_positions_for_spriteram2[1] =
         *(ushort *)
          (&start_of_sprite_buffer__sprite_data_that_goes_to_the_hardware_sprite_system.x + uVar6);
    sprite_number_and_color_for_spriteram[1] =
         *(undefined2 *)(&sprite_positions_for_spriteram2[7].x + uVar6);
    (&start_of_sprite_buffer__sprite_data_that_goes_to_the_hardware_sprite_system.x)[uVar6] = c;
    (&start_of_sprite_buffer__sprite_data_that_goes_to_the_hardware_sprite_system.y)[uVar6] =
         (byte)(uVar1 >> 8);
    (&sprite_positions_for_spriteram2[7].x)[uVar6] = (byte)uVar2;
    (&sprite_positions_for_spriteram2[7].y)[uVar6] = (byte)((ushort)uVar2 >> 8);
  }
  uVar2 = sprite_number_and_color_for_spriteram[0];
  uVar1 = sprite_positions_for_spriteram2[0];
  if (power_pill_effect != false) {
                    // power pill active
    sprite_positions_for_spriteram2[0] = sprite_positions_for_spriteram2[4];
    sprite_number_and_color_for_spriteram[0] = sprite_number_and_color_for_spriteram[4];
    sprite_positions_for_spriteram2[4] = uVar1;
    sprite_number_and_color_for_spriteram[4] = uVar2;
  }
  pfVar5 = sprite_positions_for_spriteram2;
  phVar8 = hardware_floating_sprite_ram_config;
  index = 12;
  do {
                    // green eyed ghost bug encountered here
                    // 4FF2,3 -
                    // 4FF2,3 - red ghost (8x,11)
                    // 4FF4,5 - pink ghost (8x,11)
                    // 4FF6,7 - blue ghost (8x,11)
                    // 4FF8,9 - orange ghost (8x,11)
                    // 
    *(byte *)phVar8 = pfVar5->x;
    phVar8 = (hardware_floating_sprite_t *)&phVar8->color;
    pfVar5 = (floating_sprite_coord_t *)&pfVar5->y;
    index = index + -1;
  } while (index != 0);
  pfVar9 = sprite_number_and_color_for_spriteram;
  pfVar5 = hardware_floating_sprite_ram_coords;
  index = 12;
  do {
    pfVar5->x = pfVar9->x;
    pfVar5 = (floating_sprite_coord_t *)&pfVar5->y;
    pfVar9 = (floating_sprite_coord_t *)&pfVar9->y;
    index = index + -1;
  } while (index != 0);
                    // Core game loop
  update_timers_and_random_number();
  execute_TIMED_task();
  change_game_mode();
  if (game_mode != INIT) {
    check_for_double_size_pacman();
    no_cocktail_mode_update_sprites();
    cocktail_mode_update_sprites();
    rack_input__add_credits();
    debounce_coin_input__add_credits();
    blink_coin_lights();
  }
                    // print player 1 and player two
                    // check for game mode 3
                    // draw cprt stuff
                    // 
  c = game_mode + ~INIT;
  if (c == 0) {
    channel_2_effect.num = c;
    channel_3_effect.num = c;
  }
                    //  VBLANK - 2 (SOUND)
                    //  Process sound
                    // 
  process_effect_all_voices();
  backup_sprites__then__check_cocktail_animation_end__then__mspacman_channel_1_song_table();
                    // restore registers.  they were saved at #0096
                    // 
  if ((game_mode != INIT) &&
     (((byte)hardware_IN1 & 0x10) == 0
                    // HACK7
                    // 01d1  00        nop
                    // 01d2  00        nop
                    // 01d3  00        nop
                    // )) {
    disableMaskableInterrupts();
    piVar10 = &hardware_IN0;
    cVar3 = '\b';
    do {
      *piVar10 = (in0_t)0x0;
      piVar10 = (in0_t *)((ushort)piVar10 & 0xff00 | (ushort)(byte)((char)piVar10 + 1));
      c = 0;
      cVar3 = cVar3 + -1;
    } while (cVar3 != '\0');
    s = hardware_video_ram;
    cVar3 = '\x04';
    do {
      write_volatile_1(hardware_DSW2_watchdog,c);
      write_volatile_1(hardware_coin_counter,c);
      c = 0x40;
      do {
        *s = 0x40;
        n = (char)s + 1;
        uVar1 = (ushort)s & 0xff00;
        s = (byte *)(uVar1 | n);
      } while (n != 0);
      s = (byte *)((ushort)(byte)((char)(uVar1 >> 8) + 1) << 8);
      cVar3 = cVar3 + -1;
    } while (cVar3 != '\0');
    cVar3 = '\x04';
    do {
      write_volatile_1(hardware_DSW2_watchdog,c);
      write_volatile_1(hardware_coin_counter,0);
      c = 0xf;
      do {
        *s = 0xf;
        n = (char)s + 1;
        uVar1 = (ushort)s & 0xff00;
        s = (byte *)(uVar1 | n);
      } while (n != 0);
      s = (byte *)((ushort)(byte)((char)(uVar1 >> 8) + 1) << 8);
      cVar3 = cVar3 + -1;
    } while (cVar3 != '\0');
    setInterruptMode(1);
    write_volatile_1(hardware_coin_counter,0);
    hardware_IN0 = (in0_t)0x1;
    enableMaskableInterrupts();
    halt();
    write_volatile_1(hardware_DSW2_watchdog,1);
    c = 0;
    ARRAY_ram_4f5c._98_2_ = 0x2359;
    memset((byte *)&hardware_IN0,0,8);
    n = 0xbe;
    ARRAY_ram_4f5c._98_2_ = 0x235f;
    s = (byte *)memset((byte *)&start_of_sprites_address,c,0xbe);
    ARRAY_ram_4f5c._98_2_ = 0x2360;
    s = (byte *)memset(s,c,n);
    ARRAY_ram_4f5c._98_2_ = 0x2361;
    s = (byte *)memset(s,c,n);
    ARRAY_ram_4f5c._98_2_ = 0x2362;
    memset(s,c,n);
    ARRAY_ram_4f5c._98_2_ = 0x2368;
    memset((byte *)&hardware_IN1,c,0x40);
    write_volatile_1(hardware_DSW2_watchdog,c);
    ARRAY_ram_4f5c._98_2_ = 0x236e;
    T06_clears_color_RAM();
    write_volatile_1(hardware_DSW2_watchdog,c);
    ARRAY_ram_4f5c._98_2_ = 0x2376;
    T00_clear_whole_screen_or_maze(0);
    write_volatile_1(hardware_DSW2_watchdog,c);
    p_task_list_next_free = tasks_to_execute_outside_of_irq;
    p_task_list_begin = tasks_to_execute_outside_of_irq;
    ARRAY_ram_4f5c._98_2_ = 0x2387;
    memset((byte *)tasks_to_execute_outside_of_irq,0xff,0x40);
    hardware_IN0 = (in0_t)0x1;
    enableMaskableInterrupts();
    s = _STACK_END;
    do {
      do {
        index_00 = p_task_list_begin->value;
      } while ((short)((ushort)index_00 << 8) < 0);
      p_task_list_begin->value = ~clear_whole_screen_or_maze;
      uVar1 = (ushort)p_task_list_begin & 0xff00;
      *(undefined *)(uVar1 | (byte)((char)p_task_list_begin + 1)) = 0xff;
      c = (char)p_task_list_begin + 2;
      p_task_list_begin = (task_core_t *)(uVar1 | c);
      if (c == 0) {
        p_task_list_begin = (task_core_t *)CONCAT11((char)(uVar1 >> 8),0xc0);
      }
      *(undefined2 *)(s + -2) = 0x238d;
                    // WARNING: Return address prevents inlining here
      *(undefined2 *)(s + -4) = 0x23a8;
      jump_table_fn(*(undefined **)(s + -4),index_00);
      s = s + -2;
    } while( true );
  }
  enableMaskableInterrupts();
  hardware_IN0 = (in0_t)0x1;
  return;
}



// called from #018C
// this sub increments the timers and random numbers from #4C84 to #4C8C
// 

void update_timers_and_random_number(void)

{
  byte bVar1;
  byte bVar2;
  char cVar3;
  byte *pbVar4;
  byte *pbVar5;
  
  sound_counter = sound_counter + 1;
  pbVar5 = &sound_counter_decrement;
  sound_counter_decrement = sound_counter_decrement - 1;
  pbVar4 = BYTE_ARRAY_ram_0219;
  bVar2 = 1;
  cVar3 = '\x04';
  do {
    pbVar5 = pbVar5 + 1;
    *pbVar5 = *pbVar5 + 1;
    task_timer = bVar2;
    if ((*pbVar5 & 0xf) != *pbVar4) break;
    bVar1 = *pbVar5 + 0x10 & 0xf0;
    *pbVar5 = bVar1;
    task_timer = bVar2 + 1;
    if (bVar1 != pbVar4[1]) break;
    bVar2 = bVar2 + 2;
    *pbVar5 = 0;
    pbVar4 = pbVar4 + 2;
    cVar3 = cVar3 + -1;
    task_timer = bVar2;
  } while (cVar3 != '\0');
                    // set up psuedo random number generator values, #4C8A, #4C8B, #4C8C
                    // 
  random_number_generation_unused1 = random_number_generation_unused1 * '\x05' + 1;
  random_number_generation_unused2 = random_number_generation_unused2 * '\r' + 1;
  return;
}



// checks timed tasks
// counts down timer and executes the task if the timer has expired
// called from #018F
// 

void execute_TIMED_task(void)

{
  byte index;
  ushort uVar1;
  task_timed_t *ptVar2;
  
  ptVar2 = scheduled_tasks_list_to_execute_inside_of_irq;
  uVar1 = CONCAT11(0x10,task_timer);
  do {
    index = *(byte *)ptVar2;
    if ((index != 0) && ((byte)((index >> 7) << 1 | ((index & 0xc0) << 1) >> 7) < (byte)uVar1)) {
      *(byte *)ptVar2 = *(byte *)ptVar2 - 1;
      if ((*(byte *)ptVar2 & 0x3f) == 0) {
        *(byte *)ptVar2 = 0;
        *(ushort *)((undefined *)register0x44 + -2) = uVar1;
        *(task_timed_t **)((undefined *)register0x44 + -4) = ptVar2;
        index = *(byte *)((ushort)ptVar2 & 0xff00 | (ushort)(byte)((char)ptVar2 + 1));
        *(undefined2 *)((undefined *)register0x44 + -6) = 0x25b;
                    // WARNING: Return address prevents inlining here
        *(undefined2 *)((undefined *)register0x44 + -8) = 0x247;
        jump_table_fn(*(undefined **)((undefined *)register0x44 + -8),index);
        ptVar2 = *(task_timed_t **)((undefined *)register0x44 + -6);
        uVar1 = *(ushort *)((undefined *)register0x44 + -4);
        register0x44 = (BADSPACEBASE *)((undefined *)register0x44 + -2);
      }
    }
    ptVar2 = (task_timed_t *)((ushort)ptVar2 & 0xff00 | (ushort)(byte)((char)ptVar2 + 3));
    index = (char)(uVar1 >> 8) - 1;
    uVar1 = uVar1 & 0xff | (ushort)index << 8;
  } while (index != 0);
  return;
}



void TT06_clear_ready_message(char *param_1)

{
                    // WARNING: Return address prevents inlining here
                    // timed task #06 - clears ready message
                    // 
  insert_task(&clear_ready_message);
  return;
}



// debounce rack input / add credits (if 99 or over, return)

byte rack_input__add_credits(void)

{
  byte bVar1;
  
  hardware_coin_lockout_global =
       number_of_credits_xff_for_free_play << 1 | number_of_credits_xff_for_free_play < 0x99;
  if (number_of_credits_xff_for_free_play >= 0x99) {
    return number_of_credits_xff_for_free_play;
  }
  bVar1 = (char)hardware_IN0 << 1;
  last_4_SERVICE1_to_detect_transitions =
       (last_4_SERVICE1_to_detect_transitions & 7) << 1 | (byte)hardware_IN0 >> 7;
  if (last_4_SERVICE1_to_detect_transitions == 0xc) {
    coints_to_credits_routine();
  }
  last_4_COIN2_to_detect_transitions = (last_4_COIN2_to_detect_transitions & 7) << 1 | bVar1 >> 7;
  if (last_4_COIN2_to_detect_transitions == 0xc) {
    counter__coin = counter__coin + 1;
  }
  last_4_COIN1_to_detect_transitions =
       (last_4_COIN1_to_detect_transitions & 7) << 1 | (bVar1 << 1) >> 7;
  if ((byte)(last_4_COIN1_to_detect_transitions - 0xc) != 0) {
    return last_4_COIN1_to_detect_transitions - 0xc;
  }
  counter__coin = counter__coin + 1;
  return 0;
}



// debounce coin input / add credits

void debounce_coin_input__add_credits(void)

{
  byte bVar1;
  
  if (counter__coin == 0) {
    return;
  }
  bVar1 = counter__coin;
  if (counter_coin_timeout == 0) {
    write_volatile_1(hardware_coin_counter,1);
    coints_to_credits_routine();
  }
  if (counter_coin_timeout == 8) {
    write_volatile_1(hardware_coin_counter,0);
  }
  if ((byte)(counter_coin_timeout - 0xf) != 0) {
    counter_coin_timeout = counter_coin_timeout + 1;
    return;
  }
  counter__coin = bVar1 - 1;
  counter_coin_timeout = counter_coin_timeout - 0xf;
  return;
}



void coints_to_credits_routine(void)

{
  bool bVar1;
  byte bVar2;
  bool bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  
  bVar4 = number_of_coins_per_credit - (number_of_coins_inserted + 1);
  if (bVar4 == 0) {
    bVar5 = number_of_credits_per_coin + number_of_credits_xff_for_free_play;
    bVar1 = ((number_of_credits_per_coin & 0xf) + (number_of_credits_xff_for_free_play & 0xf) & 0x10
            ) != 0;
    bVar3 = CARRY1(number_of_credits_per_coin,number_of_credits_xff_for_free_play);
    if (true) {
      bVar6 = BCDadjust(bVar5,bVar3,bVar1);
      bVar5 = BCDadjustCarry(bVar5,bVar3,bVar1);
      bVar3 = (bool)(bVar5 & 0x3b);
      hasEvenParity(bVar6);
      bVar5 = bVar6;
    }
    else {
      bVar6 = bVar5 >> 4;
      bVar2 = bVar5 & 0xf;
      if (((bVar3 != false || bVar1) || 9 < bVar6) || 9 < bVar2) {
        if (false) {
          if ((((bVar3 == false && bVar1) && bVar6 < 9) && 5 < bVar2) && bVar2 < 0x10) {
            bVar5 = bVar5 - 6;
          }
          else {
            if ((((bVar3 == true && !bVar1) && 6 < bVar6) && bVar6 < 0x10) && bVar2 < 10) {
              bVar5 = bVar5 + 0xa0;
            }
            else {
              if (((((bVar3 == true && bVar1) && 5 < bVar6) && bVar6 < 0x10) && 5 < bVar2) &&
                  bVar2 < 0x10) {
                bVar5 = bVar5 + 0x9a;
              }
            }
          }
        }
        else {
          if ((((bVar3 == false && !bVar1) && bVar6 < 9) && 9 < bVar2) && bVar2 < 0x10) {
            bVar5 = bVar5 + 6;
          }
          else {
            if (((bVar3 == false && bVar1) && bVar6 < 10) && bVar2 < 4) {
              bVar5 = bVar5 + 6;
            }
            else {
              if ((((bVar3 == false && !bVar1) && 9 < bVar6) && bVar6 < 0x10) && bVar2 < 10) {
                bVar5 = bVar5 + 0x60;
                bVar3 = true;
              }
              else {
                if (((((bVar3 == false && !bVar1) && 8 < bVar6) && bVar6 < 0x10) && 9 < bVar2) &&
                    bVar2 < 0x10) {
                  bVar5 = bVar5 + 0x66;
                  bVar3 = true;
                }
                else {
                  if ((((bVar3 == false && bVar1) && 9 < bVar6) && bVar6 < 0x10) && bVar2 < 4) {
                    bVar5 = bVar5 + 0x66;
                    bVar3 = true;
                  }
                  else {
                    if (((bVar3 == true && !bVar1) && bVar6 < 3) && bVar2 < 10) {
                      bVar5 = bVar5 + 0x60;
                    }
                    else {
                      if ((((bVar3 == true && !bVar1) && bVar6 < 3) && 9 < bVar2) && bVar2 < 0x10) {
                        bVar5 = bVar5 + 0x66;
                      }
                      else {
                        if (((bVar3 == true && bVar1) && bVar6 < 4) && bVar2 < 4) {
                          bVar5 = bVar5 + 0x66;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    if ((bVar3 & 1U) != 0) {
      bVar5 = 0x99;
    }
    number_of_coins_inserted = bVar4;
    number_of_credits_xff_for_free_play = bVar5;
    channel_1_effect.num = channel_1_effect.num | 2;
    return;
  }
  number_of_coins_inserted = number_of_coins_inserted + 1;
  return;
}



void blink_coin_lights(void)

{
  bool bVar1;
  byte bVar2;
  byte *pbVar3;
  byte *pbVar4;
  
                    //  blink coin lights, print player 1 and player 2, check for mode 3
                    // called from #01AA
                    // 
  counter__started_after_insert_coin = counter__started_after_insert_coin + 1;
  if ((counter__started_after_insert_coin & 0xf) == 0) {
    bVar2 = counter__started_after_insert_coin >> 1;
                    //  blink coin lights to pellets ; HACK9
                    //  030c  3aa74d ld a,(#4da7)
                    //  030f  4f ld c,a
                    //  0310  180b jr #0317
                    // 
    hardware_start_lamp_1_player_leds =
         ~LED_state |
         (((bVar2 | counter__started_after_insert_coin * -0x80) >> 1 | bVar2 << 7) >> 1 |
         ((bVar2 & 2) >> 1) << 7) >> 1 | ((bVar2 & 4) >> 2) << 7;
    hardware_start_lamp_2_players_leds = number_of_credits_xff_for_free_play - 1;
    bVar2 = number_of_credits_xff_for_free_play == 0 |
            (hardware_start_lamp_2_players_leds == 0) << 6;
    if (number_of_credits_xff_for_free_play == 0) {
      hardware_start_lamp_2_players_leds = 0;
      bVar2 = 0x44;
      hardware_start_lamp_1_player_leds = 0;
    }
    if (!(bool)(bVar2 >> 6)) {
      hardware_start_lamp_2_players_leds = hardware_start_lamp_1_player_leds;
    }
  }
  pbVar3 = sprites_related_stuff2 + 0x18;
  pbVar4 = sprites_related_stuff2 + 5;
  if ((game_mode != PLAYING) && (subroutine_COIN_INSERTED_state < 2)) {
    draw_1UP(sprites_related_stuff2 + 0x18);
    draw_2UP(pbVar4);
    return;
  }
                    //  display and blink 1UP/2UP depending on player up
                    // 
  if (current_player_number == 0) {
    bVar1 = (counter__started_after_insert_coin & 0x10) == 0;
    bVar2 = bVar1 << 6 | 0x10;
    if (bVar1) {
      draw_1UP(sprites_related_stuff2 + 0x18);
    }
    if ((bVar2 >> 6 & 1) == 0) {
      clear_1UP(pbVar3);
    }
  }
  else {
    bVar1 = (counter__started_after_insert_coin & 0x10) == 0;
    bVar2 = bVar1 << 6 | 0x10;
    if (bVar1) {
      draw_2UP(sprites_related_stuff2 + 5);
    }
    if ((bVar2 >> 6 & 1) == 0) {
      clear_2UP(pbVar4);
    }
  }
  if (number_of_players == 0) {
    clear_2UP(pbVar4);
  }
  return;
}



void draw_1UP(undefined *param_1)

{
  *param_1 = 0x50;
  param_1[1] = 0x55;
  param_1[2] = 0x31;
  return;
}



void draw_2UP(undefined *param_1)

{
  *param_1 = 0x50;
  param_1[1] = 0x55;
  param_1[2] = 0x32;
  return;
}



void clear_1UP(undefined *param_1)

{
  *param_1 = 0x40;
  param_1[1] = 0x40;
  param_1[2] = 0x40;
  return;
}



void clear_2UP(undefined *param_1)

{
  *param_1 = 0x40;
  param_1[1] = 0x40;
  param_1[2] = 0x40;
  return;
}



// draws big pacman in intermission. used for pac-man only, not ms.pac
// called from #019b
// 

void check_for_double_size_pacman(void)

{
  char cVar1;
  
  if (state_in_first_cutscene < 5) {
    return;
  }
                    // draw big pac (pac-man only, during 1st cutscene)
                    // 
  orange_ghost_coord.y = (byte)pacman_coord;
  cVar1 = (char)((ushort)pacman_coord >> 8);
  pink_ghost_coord.x = cVar1 + 8;
  blue_ghost_coord.x = cVar1 - 8;
  pink_ghost_coord.y = orange_ghost_coord.y - 0x10;
  blue_ghost_coord.y = orange_ghost_coord.y - 0x10;
  orange_ghost_coord.x = pink_ghost_coord.x;
  fruit_coord.y = orange_ghost_coord.y;
  fruit_coord.x = blue_ghost_coord.x;
  return;
}



void change_game_mode(void)

{
                    // WARNING: Return address prevents inlining here
  jump_table_fn((undefined *)change_game_mode_fn_table,game_mode);
  return;
}



// arrive here after power on

void execute_INIT_task_state(void)

{
                    // WARNING: Return address prevents inlining here
  jump_table_fn((undefined *)execute_INIT_task_state_fn_table,subroutine_INIT_state);
  return;
}



// arrive here after powering on
// this sets up the following tasks
// 

void I00_add_first_tasks(void)

{
                    // WARNING: Return address prevents inlining here
  insert_task(&task_clear_whole_screen);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_clear_color_RAM);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_select_maze_color);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_setup_config_from_dip_switch);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_print_highscore);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_reset_sprites_to_default);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_clear_fruit_and_pacman_position);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_set_game_to_demo_mode);
  subroutine_INIT_state = subroutine_INIT_state + 1;
  hardware_sound_enable = true;
  return;
}



void execute_DEMO_task_state(undefined param_1)

{
                    // attract mode main routine
                    // 
  T1D_draw_credit_qty(param_1);
  if (number_of_credits_xff_for_free_play != 0) {
    game_mode = game_mode + DEMO;
    subroutine_DEMO_state = 0;
    subroutine_PLAYING_state = 0;
    return;
  }
                    // table lookup
                    // OTTOPATCH
                    // PATCH FOR NEW ATTRACT MODE
                    // 
  execute_DEMO_task_state_patch();
  return;
}



// ms. pac code resumes here
// arrive here from #3E67 when subroutine # = 00
// sets up the attract mode
// 

void demo_mode_prepare_screen(undefined2 param_1)

{
                    // WARNING: Return address prevents inlining here
  insert_task(&task_clear_whole_screen_or_maze);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_select_maze_color);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_reset_sprites_to_default_values);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_clear_fruit_and_pacman_position);
  add_task_to_print_text(MS_PACMAN);
  return;
}



// pac-man only attract mode code from #0471 to #0579
// 

void pacman_draw_red_ghost(void)

{
  pacman_only_used_during_attract_mode(0x1,hardware_screen_maze_area + 0x2c4);
  add_task_to_print_text(MS_PACMAN);
  return;
}



void pacman_draw__shadow(undefined param_1)

{
  pacman_used_in_demo_mode('\x14');
  return;
}



void pacman_draw_blinky(undefined param_1)

{
  pacman_used_in_demo_mode('\r');
  return;
}



void pacman_draw_pink_ghost(void)

{
  pacman_only_used_during_attract_mode(3,hardware_screen_maze_area + 0x2c7);
  add_task_to_print_text(MS_PACMAN);
  return;
}



void pacman_draw__speedy(undefined param_1)

{
  pacman_used_in_demo_mode('\x16');
  return;
}



void pacman_draw_pinky(undefined param_1)

{
  pacman_used_in_demo_mode('\x0f');
  return;
}



void pacman_draw_blue_ghost(void)

{
  pacman_only_used_during_attract_mode(5,hardware_screen_maze_area + 0x2ca);
  add_task_to_print_text(MS_PACMAN);
  return;
}



void pacman_draw__bashful(undefined param_1)

{
  pacman_used_in_demo_mode('3');
  return;
}



void pacman_draw_inky(undefined param_1)

{
  pacman_used_in_demo_mode('/');
  return;
}



void pacman_draw_orange_ghost(void)

{
  pacman_only_used_during_attract_mode(7,hardware_screen_maze_area + 0x2cd);
  add_task_to_print_text(MS_PACMAN);
  return;
}



void pacman_draw__pokey(undefined param_1)

{
  pacman_used_in_demo_mode('5');
  return;
}



void pacman_draw_clyde(undefined2 param_1)

{
                    // pac-man only ???
                    // arrive here from #04D5
                    // 
  add_to_task_list(draw_text_or_graphics,ghost_names_mode + 0x31);
                    // WARNING: Return address prevents inlining here
  add_timed_task(&task_increase_subroutine_DEMO_state);
  subroutine_DEMO_state = subroutine_DEMO_state + 1;
  return;
}



void pacman_draw_10pts(void)

{
                    // WARNING: Return address prevents inlining here
  insert_task(&task_draw_text_or_graphics_ten_points);
  add_task_to_print_text(FIVTY_POINTS);
  return;
}



void pacman_get_demo_ready(char *param_1,undefined2 param_2)

{
  undefined uVar1;
  char cVar2;
  byte *pbVar3;
  
  uVar1 = C_MIDWAY_MFG_CO;
  add_task_to_print_text(C_MIDWAY_MFG_CO);
  P00_reset_game_data(uVar1);
  *param_1 = *param_1 + -1;
                    // WARNING: Return address prevents inlining here
  insert_task(&task_clear_full_data_game);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_reset_ghost_home_counter);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_setup_difficulty);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_reset_sprites_to_default_values);
  real_number_of_lives = 1;
  number_of_players = 0;
  number_of_lives_displayed = 0;
  hardware_screen_maze_area[26][26] = 0x14;
  cVar2 = '\x1c';
  pbVar3 = hardware_screen_maze_area;
  do {
    pbVar3[0x11] = 0xfc;
    pbVar3[0x13] = 0xfc;
    pbVar3 = pbVar3 + 0x20;
    cVar2 = cVar2 + -1;
  } while (cVar2 != '\0');
  return;
}



void pacman_3rd_intermission_end(void)

{
  char cVar1;
  byte *pbVar2;
  
  cVar1 = '\x1c';
  pbVar2 = hardware_screen_maze_area;
  do {
    pbVar2[0x11] = 0xfc;
    pbVar2[0x13] = 0xfc;
    pbVar2 = pbVar2 + 0x20;
    cVar1 = cVar1 + -1;
  } while (cVar1 != '\0');
  return;
}



void pacman_draw_start_and_run_demo(void)

{
                    // called during attract mode, pac-man only, not ms. pac
                    // 
  if (pacman_position_tile_position.x == 0x21) {
    red_ghost_substate_if_alive = GOING_FOR_PACMAN;
    TT02_increase_subroutine_DEMO_state();
    return;
  }
                    // a core game loop used in pac-man demo mode only, not used in ms. pac
                    // 
  update_ghost_and_pacman_state();
  update_ghost_and_pacman_state();
  is_time_to_change_ghost_animation();
  handle_power_pill_flashes();
  pacman_only_set_color_for_dead_ghost();
  pacman_used_during_attract_mode();
  is_reverse_red_ghost_direction_time();
  is_reverse_pink_ghost_direction_time();
  is_reverse_blue_ghost_direction_time();
  is_reverse_orange_ghost_direction_time();
  return;
}



void pacman_check_to_release_pink(void)

{
  if (red_ghost_tile_position_2.x == 0x20) {
    pink_ghost_substate_if_alive = GOING_FOR_PACMAN;
    TT02_increase_subroutine_DEMO_state();
    return;
  }
  update_ghost_and_pacman_state();
  update_ghost_and_pacman_state();
  is_time_to_change_ghost_animation();
  handle_power_pill_flashes();
  pacman_only_set_color_for_dead_ghost();
  pacman_used_during_attract_mode();
  is_reverse_red_ghost_direction_time();
  is_reverse_pink_ghost_direction_time();
  is_reverse_blue_ghost_direction_time();
  is_reverse_orange_ghost_direction_time();
  return;
}



void pacman_check_to_release_inky(void)

{
  if (red_ghost_tile_position_2.x == 0x22) {
    blue_ghost_substate_if_alive = GOING_FOR_PACMAN;
    TT02_increase_subroutine_DEMO_state();
    return;
  }
  update_ghost_and_pacman_state();
  update_ghost_and_pacman_state();
  is_time_to_change_ghost_animation();
  handle_power_pill_flashes();
  pacman_only_set_color_for_dead_ghost();
  pacman_used_during_attract_mode();
  is_reverse_red_ghost_direction_time();
  is_reverse_pink_ghost_direction_time();
  is_reverse_blue_ghost_direction_time();
  is_reverse_orange_ghost_direction_time();
  return;
}



void pacman_check_to_release_orange_ghost(void)

{
  if (red_ghost_tile_position_2.x == 0x24) {
    orange_ghost_substate_if_alive = GOING_FOR_PACMAN;
    TT02_increase_subroutine_DEMO_state();
    return;
  }
  update_ghost_and_pacman_state();
  update_ghost_and_pacman_state();
  is_time_to_change_ghost_animation();
  handle_power_pill_flashes();
  pacman_only_set_color_for_dead_ghost();
  pacman_used_during_attract_mode();
  is_reverse_red_ghost_direction_time();
  is_reverse_pink_ghost_direction_time();
  is_reverse_blue_ghost_direction_time();
  is_reverse_orange_ghost_direction_time();
  return;
}



void pacman_check_for_demo_completion(void)

{
  if ((byte)(killed_ghost_animation_state + counter__current_number_of_killed_ghosts) != '\x06') {
    update_ghost_and_pacman_state();
    update_ghost_and_pacman_state();
    is_time_to_change_ghost_animation();
    handle_power_pill_flashes();
    pacman_only_set_color_for_dead_ghost();
    pacman_used_during_attract_mode();
    is_reverse_red_ghost_direction_time();
    is_reverse_pink_ghost_direction_time();
    is_reverse_blue_ghost_direction_time();
    is_reverse_orange_ghost_direction_time();
    return;
  }
  subroutine_DEMO_state = subroutine_DEMO_state + 1;
  return;
}



void pacman_end_demo_and_return(void)

{
                    // arrive here in demo mode from #3ECD
                    // 
  execute_PLAYING_task_state();
  return;
}



// called from #046D and other places.  C is preloaded with the text code to display
// 

void add_task_to_print_text(text_e text)

{
  add_to_task_list(draw_text_or_graphics,text);
                    // WARNING: Return address prevents inlining here
  add_timed_task(&task_increase_subroutine_DEMO_state);
  subroutine_DEMO_state = subroutine_DEMO_state + 1;
  return;
}



// BUGFIX03 - Blue maze - Don Hodges
// 41 is 1/10 second rather than 1 second
// called from # 0246 from jump table based on game state
// or, timed task number #02 has been encountered, arrive from #0246
// also arrive from #3E93 during marquee mode in demo
// 

void TT02_increase_subroutine_DEMO_state(void)

{
  subroutine_DEMO_state = subroutine_DEMO_state + 1;
  return;
}



// pac-man only - used in demo mode for introducing ghost names
// called from several places after C has been preloaded with ghost name code
// 

void pacman_used_in_demo_mode(char param_1)

{
  add_to_task_list(draw_text_or_graphics,ghost_names_mode + param_1);
                    // WARNING: Return address prevents inlining here
  add_timed_task(&task_increase_subroutine_DEMO_state);
  TT02_increase_subroutine_DEMO_state();
  return;
}



// pac-man only, used during attract mode when pac-man moves toward energizer followed by the 4
// ghosts
// 

undefined pacman_used_during_attract_mode(void)

{
  dereference_word_t dVar1;
  
  if (pacman_change_orientation_flag == false) {
    return pacman_change_orientation_flag;
  }
                    // pac-man only, used during attract mode when pac-man reaches the energizer
                    // 
  pacman_change_orientation_flag = false;
  wanted_pacman_orientation = pacman_orientation ^ 2;
  dVar1 = dereference_pointer_to_word((word *)&move_right,wanted_pacman_orientation);
  wanted_pacman_tile_changes = (short)((uint5)dVar1 >> 0x18);
  return SUB51(dVar1,0);
}



// pac-man only, used during attract mode to draw the stationary ghosts during introductions
// HL is preloaded with starting screen address,
// A is preloaded with the ghost color code
// 

void pacman_only_used_during_attract_mode(undefined param_1,undefined *param_2)

{
  undefined *puVar1;
  
  *param_2 = 0xb1;
  *(undefined *)((ushort)param_2 & 0xff00 | (ushort)(byte)((char)param_2 + 1)) = 0xb3;
  puVar1 = (undefined *)((ushort)param_2 & 0xff00 | (ushort)(byte)((char)param_2 + 2));
  *puVar1 = 0xb5;
  puVar1 = puVar1 + 0x1e;
  *puVar1 = 0xb0;
  *(undefined *)((ushort)puVar1 & 0xff00 | (ushort)(byte)((char)puVar1 + 1)) = 0xb2;
  puVar1 = (undefined *)((ushort)puVar1 & 0xff00 | (ushort)(byte)((char)puVar1 + 2));
  *puVar1 = 0xb4;
  puVar1 = puVar1 + 0x400;
  *puVar1 = param_1;
  *(undefined *)((ushort)puVar1 & 0xff00 | (ushort)(byte)((char)puVar1 - 1)) = param_1;
  puVar1 = (undefined *)((ushort)puVar1 & 0xff00 | (ushort)(byte)((char)puVar1 - 2));
  *puVar1 = param_1;
  puVar1 = puVar1 + -0x1e;
  *puVar1 = param_1;
  *(undefined *)((ushort)puVar1 & 0xff00 | (ushort)(byte)((char)puVar1 - 1)) = param_1;
  *(undefined *)((ushort)puVar1 & 0xff00 | (ushort)(byte)((char)puVar1 - 2)) = param_1;
  return;
}



// arrive from #03CB
// arrive here when credit has been inserted and game is waiting for start button to be pressed
// 

byte execute_COIN_INSERTED_task_state(void)

{
  byte bVar1;
  
  bVar1 = subroutine_COIN_INSERTED_state;
                    // WARNING: Return address prevents inlining here
  jump_table_fn((undefined *)coin_inserted_task_fn_table,subroutine_COIN_INSERTED_state);
  return bVar1;
}



byte C00_init_screen(undefined param_1)

{
  byte bVar1;
  
  T1D_draw_credit_qty(param_1);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_clear_whole_screen_or_maze);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_select_maze_color);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_draw_text_or_graphics);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_draw_text_or_graphics);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_clear_fruit_and_pacman_values);
  subroutine_COIN_INSERTED_state = subroutine_COIN_INSERTED_state + 1;
  LED_state = 1;
  if (bonus_life == 0xff) {
    LED_state = 1;
    return 0xff;
  }
  bVar1 = bonus_life;
                    // WARNING: Return address prevents inlining here
  insert_task(&task_draw_text_or_graphics);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_draw_extra_life_points);
  return bVar1;
}



// display 1/2 player and check start buttons
// 

void C01_draw_credits_qty_and_check_1P_OR_2P_button_for_start(undefined param_1)

{
  bool bVar1;
  bool bVar2;
  byte bVar3;
  byte bVar4;
  byte index;
  
  T1D_draw_credit_qty(param_1);
  index = ONE_OR_TWO_PLAYERS;
  if (number_of_credits_xff_for_free_play == 1) {
    index = ONE_PLAYER_ONLY;
  }
  DrawText(index);
  if ((number_of_credits_xff_for_free_play == 1) || (((byte)hardware_IN1 & 0x40) != 0)) {
    if (((byte)hardware_IN1 & 0x20) != 0) {
      return;
    }
    number_of_players = 0;
  }
  else {
    number_of_players = 1;
  }
  if (number_of_coins_per_credit != 0) {
    index = number_of_credits_xff_for_free_play;
    if (number_of_players != 0) {
      index = number_of_credits_xff_for_free_play + 0x99;
      bVar1 = ((number_of_credits_xff_for_free_play & 0xf) + 9 & 0x10) != 0;
      bVar2 = 0x66 < number_of_credits_xff_for_free_play;
      if (true) {
        bVar4 = BCDadjust(index,bVar2,bVar1);
        BCDadjustCarry(index,bVar2,bVar1);
        hasEvenParity(bVar4);
        index = bVar4;
      }
      else {
        bVar4 = index >> 4;
        bVar3 = index & 0xf;
        if (((bVar2 || bVar1) || 9 < bVar4) || 9 < bVar3) {
          if (false) {
            if ((((!bVar2 && bVar1) && bVar4 < 9) && 5 < bVar3) && bVar3 < 0x10) {
              index = number_of_credits_xff_for_free_play + 0x93;
            }
            else {
              if ((((bVar2 && !bVar1) && 6 < bVar4) && bVar4 < 0x10) && bVar3 < 10) {
                index = number_of_credits_xff_for_free_play + 0x39;
              }
              else {
                if (((((bVar2 && bVar1) && 5 < bVar4) && bVar4 < 0x10) && 5 < bVar3) && bVar3 < 0x10
                   ) {
                  index = number_of_credits_xff_for_free_play + 0x33;
                }
              }
            }
          }
          else {
            if ((((bVar2 || bVar1) || 8 < bVar4) || bVar3 < 10) || 0xf < bVar3) {
              if (((!bVar2 && bVar1) && bVar4 < 10) && bVar3 < 4) {
                index = number_of_credits_xff_for_free_play + 0x9f;
              }
              else {
                if ((((bVar2 || bVar1) || bVar4 < 10) || 0xf < bVar4) || 9 < bVar3) {
                  if (((((bVar2 || bVar1) || bVar4 < 9) || 0xf < bVar4) || bVar3 < 10) ||
                      0xf < bVar3) {
                    if ((((!bVar2 && bVar1) && 9 < bVar4) && bVar4 < 0x10) && bVar3 < 4) {
                      index = number_of_credits_xff_for_free_play - 1;
                    }
                    else {
                      if (((bVar2 && !bVar1) && bVar4 < 3) && bVar3 < 10) {
                        index = number_of_credits_xff_for_free_play - 7;
                      }
                      else {
                        if ((((bVar2 && !bVar1) && bVar4 < 3) && 9 < bVar3) && bVar3 < 0x10) {
                          index = number_of_credits_xff_for_free_play - 1;
                        }
                        else {
                          if (((bVar2 && bVar1) && bVar4 < 4) && bVar3 < 4) {
                            index = number_of_credits_xff_for_free_play - 1;
                          }
                        }
                      }
                    }
                  }
                  else {
                    index = number_of_credits_xff_for_free_play - 1;
                  }
                }
                else {
                  index = number_of_credits_xff_for_free_play - 7;
                }
              }
            }
            else {
              index = number_of_credits_xff_for_free_play + 0x9f;
            }
          }
        }
      }
    }
    number_of_credits_xff_for_free_play = index + 0x99;
    bVar1 = ((index & 0xf) + 9 & 0x10) != 0;
    bVar2 = 0x66 < index;
    if (true) {
      index = BCDadjust(number_of_credits_xff_for_free_play,bVar2,bVar1);
      BCDadjustCarry(number_of_credits_xff_for_free_play,bVar2,bVar1);
      hasEvenParity(index);
      number_of_credits_xff_for_free_play = index;
    }
    else {
      bVar4 = number_of_credits_xff_for_free_play >> 4;
      bVar3 = number_of_credits_xff_for_free_play & 0xf;
      if (((bVar2 || bVar1) || 9 < bVar4) || 9 < bVar3) {
        if (false) {
          if ((((!bVar2 && bVar1) && bVar4 < 9) && 5 < bVar3) && bVar3 < 0x10) {
            number_of_credits_xff_for_free_play = index + 0x93;
          }
          else {
            if ((((bVar2 && !bVar1) && 6 < bVar4) && bVar4 < 0x10) && bVar3 < 10) {
              number_of_credits_xff_for_free_play = index + 0x39;
            }
            else {
              if (((((bVar2 && bVar1) && 5 < bVar4) && bVar4 < 0x10) && 5 < bVar3) && bVar3 < 0x10)
              {
                number_of_credits_xff_for_free_play = index + 0x33;
              }
            }
          }
        }
        else {
          if ((((bVar2 || bVar1) || 8 < bVar4) || bVar3 < 10) || 0xf < bVar3) {
            if (((!bVar2 && bVar1) && bVar4 < 10) && bVar3 < 4) {
              number_of_credits_xff_for_free_play = index + 0x9f;
            }
            else {
              if ((((bVar2 || bVar1) || bVar4 < 10) || 0xf < bVar4) || 9 < bVar3) {
                if (((((bVar2 || bVar1) || bVar4 < 9) || 0xf < bVar4) || bVar3 < 10) || 0xf < bVar3)
                {
                  if ((((!bVar2 && bVar1) && 9 < bVar4) && bVar4 < 0x10) && bVar3 < 4) {
                    number_of_credits_xff_for_free_play = index - 1;
                  }
                  else {
                    if (((bVar2 && !bVar1) && bVar4 < 3) && bVar3 < 10) {
                      number_of_credits_xff_for_free_play = index - 7;
                    }
                    else {
                      if ((((bVar2 && !bVar1) && bVar4 < 3) && 9 < bVar3) && bVar3 < 0x10) {
                        number_of_credits_xff_for_free_play = index - 1;
                      }
                      else {
                        if (((bVar2 && bVar1) && bVar4 < 4) && bVar3 < 4) {
                          number_of_credits_xff_for_free_play = index - 1;
                        }
                      }
                    }
                  }
                }
                else {
                  number_of_credits_xff_for_free_play = index - 1;
                }
              }
              else {
                number_of_credits_xff_for_free_play = index - 7;
              }
            }
          }
          else {
            number_of_credits_xff_for_free_play = index + 0x9f;
          }
        }
      }
    }
    T1D_draw_credit_qty(param_1);
  }
  LED_state = 0;
  subroutine_COIN_INSERTED_state = subroutine_COIN_INSERTED_state + 1;
  channel_1_wave.num = 1;
  channel_2_wave.num = 1;
  return;
}



// arrive from #05E8 when start button has been pressed

void C02_init_screen_ready_for_play(void)

{
                    // WARNING: Return address prevents inlining here
  insert_task(&task_clear_whole_screen_or_maze);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_select_maze_color);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_draw_maze);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_clears_pills_and_power_pills);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_draw_pellets);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_draw_text_or_graphics);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_draw_text_or_graphics);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_print_high_score_text_then_players_score);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_draw_fruits_right_screen);
  current_level = 0;
  real_number_of_lives = number_of_lives;
  number_of_lives_displayed = number_of_lives;
                    // WARNING: Return address prevents inlining here
  insert_task(&task_draw_remaining_lives_bottom_screen);
                    // WARNING: Return address prevents inlining here
  add_timed_task(&task_increase_subroutine_COIN_INSETED_state);
  subroutine_COIN_INSERTED_state = subroutine_COIN_INSERTED_state + 1;
  return;
}



void TT01_increase_subroutine_COIN_INSERTED_state(void)

{
                    // also arrive here from #0246.   This is timed task #01
                    // 
  subroutine_COIN_INSERTED_state = subroutine_COIN_INSERTED_state + 1;
  return;
}



// draw lives displayed onto the screen

void C04_draw_remaining_lives_and_reset_states(byte param_1,undefined *param_2)

{
  number_of_lives_displayed = number_of_lives_displayed - 1;
  T1A_draw_remaining_lives_bottom_screen(param_1,(ushort)&number_of_lives_displayed,param_2);
  game_mode = game_mode + DEMO;
  subroutine_DEMO_state = 0;
  subroutine_COIN_INSERTED_state = 0;
  subroutine_PLAYING_state = 0;
  return;
}



// arrive here from #03CB or from #057C, when someone or demo is playing
// 

void execute_PLAYING_task_state(void)

{
                    // WARNING: Return address prevents inlining here
  jump_table_fn((undefined *)playing_task_fn_table,subroutine_PLAYING_state);
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void setup_difficulty(undefined2 param_1)

{
  char cVar1;
  byte *pbVar2;
  
                    // arrive here from #000D
                    // sets up game difficulty
                    // 
  cVar1 = (char)((ushort)param_1 >> 8);
  if (cVar1 == '\0') {
    cVar1 = *(char *)pointer_to_current_difficulty_settings;
  }
  pbVar2 = &difficulty1_6_bytes_t_ARRAY_ram_0796[0].speed_and_orientation_index +
           (byte)(cVar1 * '\x06');
  copy_difficulty_related_data(difficulty2_t_ARRAY_ram_330f[0].field_0x0 + (byte)(*pbVar2 * '*'));
  related_to_difficulty = pbVar2[1];
  set_pink_ghost_counter_to_go_out_of_home_limit
            (&difficulty4_ghost_out_of_home_t_ARRAY_ram_0843[0].counter_for_pink +
             (byte)(pbVar2[2] * '\x03'));
  _red_ghost_remainder_of_pills_when_first_difficulty_flag_is_set =
       *(undefined2 *)
        (&difficulty3_t_ARRAY_ram_084f[0].numbre_of_pills_difficulty_flag1 +
        (byte)(pbVar2[3] * '\x02'));
  time_the_ghosts_stay_blue_when_pacman_eats_a_big_pill =
       *(word *)((short)&time_ghost_stay_blue + (ushort)(byte)(pbVar2[4] * '\x02'));
  number_of_units_before_ghost_leaves_home =
       *(word *)((short)&number_of_unit_before_ghosts_leaves_home +
                (ushort)(byte)(pbVar2[5] * '\x02'));
  T1B_draw_fruits_right_screen();
  return;
}



// called from #0737
// copies difficulty-related data into #4d46 through #4d94
// includes 4d58 which is blinky's normal speed
// include 4d86 which controls timing of reversals
// 

void copy_difficulty_related_data(undefined *difficulty_table)

{
  short counter;
  pacman_speed_bit_patterns_t *pacman_state_;
  undefined *difficulty_table_;
  undefined *difficulty_table__;
  
  pacman_state_ = &pacman_state;
  counter = 0x1c;
  do {
    difficulty_table_ = difficulty_table;
    *(undefined *)&pacman_state_->normal_state = *difficulty_table_;
    pacman_state_ = (pacman_speed_bit_patterns_t *)((short)&pacman_state_->normal_state + 1);
    counter = counter + -1;
    difficulty_table = difficulty_table_ + 1;
  } while (counter != 0);
  counter = 0xc;
  difficulty_table_ = difficulty_table_ + -0xb;
  do {
    difficulty_table__ = difficulty_table_;
    *(undefined *)&pacman_state_->normal_state = *difficulty_table__;
    pacman_state_ = (pacman_speed_bit_patterns_t *)((short)&pacman_state_->normal_state + 1);
    counter = counter + -1;
    difficulty_table_ = difficulty_table__ + 1;
  } while (counter != 0);
  counter = 0xc;
  difficulty_table_ = difficulty_table__ + -0xb;
  do {
    difficulty_table__ = difficulty_table_;
    *(undefined *)&pacman_state_->normal_state = *difficulty_table__;
    pacman_state_ = (pacman_speed_bit_patterns_t *)((short)&pacman_state_->normal_state + 1);
    counter = counter + -1;
    difficulty_table_ = difficulty_table__ + 1;
  } while (counter != 0);
  counter = 0xc;
  difficulty_table__ = difficulty_table__ + -0xb;
  do {
    *(undefined *)&pacman_state_->normal_state = *difficulty_table__;
    pacman_state_ = (pacman_speed_bit_patterns_t *)((short)&pacman_state_->normal_state + 1);
    difficulty_table__ = difficulty_table__ + 1;
    counter = counter + -1;
  } while (counter != 0);
  counter = 0xe;
  do {
    *(undefined *)&pacman_state_->normal_state = *difficulty_table__;
    pacman_state_ = (pacman_speed_bit_patterns_t *)((short)&pacman_state_->normal_state + 1);
    difficulty_table__ = difficulty_table__ + 1;
    counter = counter + -1;
  } while (counter != 0);
  return;
}



void set_pink_ghost_counter_to_go_out_of_home_limit(undefined *src)

{
  short counter;
  byte *dst;
  
                    // called from #0749
                    // 
  dst = &pink_ghost_counter_to_go_out_of_home_limit;
  counter = 3;
  do {
    *dst = *src;
    dst = dst + 1;
    src = src + 1;
    counter = counter + -1;
  } while (counter != 0);
  return;
}



// main routine #3.  arrive here at the start of the game when a new game is started

void P00_reset_game_data(undefined param_1)

{
  short sVar1;
  undefined1 *puVar2;
  word *pwVar3;
  
  memset(&current_player_number,0,0xb);
  T12_clears_pills_and_power_pills_arrays();
  pointer_to_current_difficulty_settings = (word)p_difficulty_settings;
  pwVar3 = &pointer_to_current_difficulty_settings;
  puVar2 = &copy_of_level_data;
  sVar1 = 0x2e;
  do {
    *puVar2 = *(undefined *)pwVar3;
    puVar2 = puVar2 + 1;
    pwVar3 = (word *)((short)pwVar3 + 1);
    sVar1 = sVar1 + -1;
  } while (sVar1 != 0);
  subroutine_PLAYING_state = subroutine_PLAYING_state + 1;
  return;
}



void TT00_increase_subroutine_PLAYING_state(void)

{
                    // arrive here from #09CF
                    // this is also timed task #00, arrive from #0246
                    // 
  subroutine_PLAYING_state = subroutine_PLAYING_state + 1;
  return;
}



void P01_init_screen_then_goto_P09(void)

{
  if (game_mode == DEMO) {
    subroutine_PLAYING_state = 9;
    return;
  }
                    // WARNING: Return address prevents inlining here
  insert_task(&task_clear_full_data_game);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_draw_text_or_graphics);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_reset_sprites_to_default_values);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_reset_ghost_home_counter);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_setup_difficulty);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_draw_remaining_lives_bottom_screen);
                    // WARNING: Return address prevents inlining here
  add_timed_task(&task_increase_subroutine_PLAYING_state);
                    // WARNING: Return address prevents inlining here
  add_timed_task(&task_clear_ready_message);
  hardware_flipscreen = (bool)(current_player_number & cocktail_mode);
  TT00_increase_subroutine_PLAYING_state();
  return;
}



// demo or game is playing

void P03_check_rack_test(void)

{
  if (((byte)hardware_IN0 & 0x10) == 0) {
    subroutine_PLAYING_state = 0xe;
                    // WARNING: Return address prevents inlining here
    insert_task(&task_clears_sprites);
    return;
  }
                    //  routine to determine the number of pellets which must be eaten
                    // 
                    // OTTOPATCH
                    // PATCH TO ADJUST THE TOTAL DOT NUMBER
                    // 
  check_if_board_is_cleared(dots_eaten);
  return;
}



void goto_state_P0C(void)

{
  subroutine_PLAYING_state = 0xc;
                    // returns here if the level is complete
                    // 
  return;
}



// when player has died
// 

void P04_player_is_died_game_over(void)

{
  dying_in_a_level = true;
                    // 4e12 1 after dying in a level, reset to 0 if ghosts have left home
                    // because of 4d9f
                    // 
  T15_update_screen_pill_config_to_video_ram();
  if (((real_number_of_lives == 0) && (number_of_players != 0)) && (DAT_ram_4e42 != '\0')) {
    subroutine_PLAYING_state = subroutine_PLAYING_state + 1;
    add_to_task_list(draw_text_or_graphics,current_player_number + 3);
                    // WARNING: Return address prevents inlining here
    insert_task(&task_draw_text_or_graphics);
                    // WARNING: Return address prevents inlining here
    add_timed_task(&task_increase_subroutine_PLAYING_state);
    return;
  }
  subroutine_PLAYING_state = subroutine_PLAYING_state + GHOST_WAIT_FOR_START;
  return;
}



void P06_switch_player(undefined param_1)

{
  if ((number_of_players == 0) || (DAT_ram_4e42 == '\0')) {
    if (real_number_of_lives == 0) {
                    // change 0950 to
                    // always jump ahead
                    // for never-ending pac goodness
                    // 
      T1D_draw_credit_qty(param_1);
                    // WARNING: Return address prevents inlining here
      insert_task(&task_draw_text_or_graphics);
                    // WARNING: Return address prevents inlining here
      add_timed_task(&task_increase_subroutine_PLAYING_state);
      subroutine_PLAYING_state = subroutine_PLAYING_state + 1;
      return;
    }
  }
  else {
                    // arrive here from #094a when there 2 players, when a player dies
    __maybe_player_change_backup_current_player_game_settings();
    current_player_number = current_player_number ^ 1;
  }
  subroutine_PLAYING_state = 9;
  return;
}



// arrive from #06C1 when subroutine# (#4E04)= #08
// zeros some important variables
// arrive here after demo mode finishes (ms pac man dies in demo)
// 

void P08_end_of_demo(void)

{
  game_mode = DEMO;
  subroutine_DEMO_state = 0;
  subroutine_PLAYING_state = 0;
  current_player_number = 0;
  number_of_players = 0;
  hardware_flipscreen = false;
  return;
}



// state=9 when marquee mode ends or after player has been killed
// state=20 when a level has ended and a new one is about to begin
// 

void P09_prepare_screen_level(void)

{
                    // WARNING: Return address prevents inlining here
  insert_task(&task_clear_whole_screen_or_maze);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_select_maze_color);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_draw_maze);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_clear_full_data_game);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_clears_sprites);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_draw_pellets);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_reset_sprites_to_default_values);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_reset_ghost_home_counter);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_setup_difficulty);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_draw_remaining_lives_bottom_screen);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_draw_text_or_graphics);
  if (game_mode != PLAYING) {
                    // WARNING: Return address prevents inlining here
    insert_task(&task_draw_ext_or_graphics);
                    // WARNING: Return address prevents inlining here
    insert_task(&task_draw_draw_credit_qty);
  }
                    // WARNING: Return address prevents inlining here
  add_timed_task(&task_increase_subrouting_PLAYING_state);
  if (game_mode != DEMO) {
                    // WARNING: Return address prevents inlining here
    add_timed_task(&task_clear_ready_message);
  }
  hardware_flipscreen = (bool)(current_player_number & cocktail_mode);
  TT00_increase_subroutine_PLAYING_state();
  return;
}



// called after marquee mode is done during demo
// called from #06C1 when (#4E04 == #0B)
// 

void P0B_loop_state_P03(void)

{
  subroutine_PLAYING_state = GHOST_MOVE;
  return;
}



// WARNING: This is an inlined function
// called from #06C1 when (#4E04 == #0C)
// arrive here at end of level
// 

void P0C_end_of_level_clear_sound(task_timed_t *task)

{
                    // WARNING: Return address prevents inlining here
  add_timed_task(&task_increase_subroutine_PLAYING_state);
  subroutine_PLAYING_state = subroutine_PLAYING_state + 1;
  channel_2_effect.num = 0;
  channel_3_effect.num = 0;
  return;
}



// Called from #06C1 when (#4E04 == #0E)
// 

void P0E_flash_screen_on(void)

{
  add_to_task_list(select_maze_color,_flashing);
                    // WARNING: Return address prevents inlining here
  add_timed_task((task_timed_t *)0x9f0);
  clear_all_ghost_from_screen(0);
  subroutine_PLAYING_state = subroutine_PLAYING_state + 1;
  return;
}



void change_maze_color(byte color)

{
  add_to_task_list(select_maze_color,color);
                    // WARNING: Return address prevents inlining here
  add_timed_task((task_timed_t *)0x9f0);
  clear_all_ghost_from_screen(0);
  subroutine_PLAYING_state = subroutine_PLAYING_state + 1;
  return;
}



void P10_flash_screen_off(void)

{
                    // the following calls are made at end of level to flash the screen
                    // 
  change_maze_color(fruit);
  return;
}



void P0E_flash_screen_on(void)

{
  P0E_flash_screen_on();
  return;
}



void P10_flash_screen_off(void)

{
  P10_flash_screen_off();
  return;
}



void P0E_flash_screen_on(void)

{
  P0E_flash_screen_on();
  return;
}



void P10_flash_screen_off(void)

{
  P10_flash_screen_off();
  return;
}



void P0E_flash_screen_on(void)

{
  P0E_flash_screen_on();
  return;
}



void P10_flash_screen_off(void)

{
  P10_flash_screen_off();
  return;
}



// arrive here at end of level after screen has flashed several times
// called from #06C1 when (#4E04 == #14)
// 

void P1E_end_of_level_after_flash_screen(void)

{
                    // WARNING: Return address prevents inlining here
  insert_task(&task_clear_whole_screen_or_maze);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_clears_color_RAM);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_clear_full_data_game);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_clears_sprites);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_reset_sprites_to_default_values);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_reset_ghost_home_counter);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_setup_difficulty);
                    // WARNING: Return address prevents inlining here
  add_timed_task(&task_increase_subroutine_PLAYING_state);
  subroutine_PLAYING_state = subroutine_PLAYING_state + 1;
  return;
}



// arrive here at end of level
// called from #06C1 when (#4E04 == #16)
// clear sounds and run intermissions when needed
// 

void P20_end_of_level_clear_sounds_and_run_intermissions(void)

{
  byte index;
  
  channel_2_effect.num = 0;
  channel_3_effect.num = 0;
  index = current_level;
  if (0x13 < current_level) {
    index = 0x14;
  }
                    // WARNING: Return address prevents inlining here
  jump_table_fn((undefined *)next_level_state_lookup_fn_table,index);
  return;
}



void state_for_start(void)

{
  subroutine_PLAYING_state = subroutine_PLAYING_state + GHOST_WAIT_FOR_START;
  channel_1_wave.num = 0;
  channel_2_wave.num = 0;
  return;
}



// we're about to start the next board, (it's about to be drawn)
// called from #06C1 when (#4E04 == #18)
// 

void P22_prepare_next_level(undefined param_1)

{
  channel_1_wave.num = 0;
  channel_2_wave.num = 0;
  memset(&first_fruit_flag,0,7);
  T12_clears_pills_and_power_pills_arrays();
                    // BUGFIX01 (1 of 2)
                    // 0a90  c3800f jp #0f88
                    // 0a93  00 nop
                    // BUGFIX02 (1 of 2)
                    // 0a90  c3960f jp #0f96
                    // 0a93  00 nop
                    // 
  if (*(char *)pointer_to_current_difficulty_settings == '\x14') {
    subroutine_PLAYING_state = subroutine_PLAYING_state + 1;
    current_level = current_level + 1;
    return;
  }
  subroutine_PLAYING_state = subroutine_PLAYING_state + 1;
  pointer_to_current_difficulty_settings = pointer_to_current_difficulty_settings + 1;
  current_level = current_level + 1;
  return;
}



void P09_prepare_screen_level(void)

{
                    // called from #06C1 when (#4E04 == #20)
                    // 
  P09_prepare_screen_level();
  return;
}



void P0B_goto_state_P03_loop(void)

{
                    // called from #06C1 when (#4E04 == #22)
                    // 
  P0B_loop_state_P03();
  return;
}



// called from #0961
// transposes data from #4e0a through #4e37 into #4e38 through #4e66
// used to copy data in and out for 2 player games
// 

void __maybe_player_change_backup_current_player_game_settings(void)

{
  undefined uVar1;
  char cVar2;
  word *pwVar3;
  undefined1 *puVar4;
  
  cVar2 = '.';
  pwVar3 = &pointer_to_current_difficulty_settings;
  puVar4 = &copy_of_level_data;
  do {
    uVar1 = *puVar4;
    *puVar4 = *(undefined *)pwVar3;
    *(undefined *)pwVar3 = uVar1;
    pwVar3 = (word *)((short)pwVar3 + 1);
    puVar4 = puVar4 + 1;
    cVar2 = cVar2 + -1;
  } while (cVar2 != '\0');
  return;
}



void handle_ghost_flashing_and_colors_when_power_pills_are_eaten(void)

{
  byte bVar1;
  
  if (number_of_ghost_killed_but_no_collision_for_yet != 0) {
    return;
  }
                    // this subroutine never gets called when the green-eyed ghost bug occurs
                    // 
  if (counter__used_to_change_ghost_colors_under_big_pill_effects == 0) {
    counter__used_to_change_ghost_colors_under_big_pill_effects = 0xe;
    if ((power_pill_effect != false) && (counter_while_ghosts_are_blue < 0x100)) {
                    // arrive here when ghosts start flashing after being blue
                    // this sub controls the flashing and the return
                    // 
      bVar1 = channel_2_effect.num | 0x80;
      if (mspac_sprite.color == mspac) {
        bVar1 = channel_2_effect.num & 0x7f;
      }
      channel_2_effect.num = bVar1;
      mspac_sprite.color = mspac;
    }
    if (red_ghost_blue_flag == false) {
      if (red_ghost_sprite.color == red) {
        red_ghost_sprite.color = red;
      }
      else {
        red_ghost_sprite.color = red;
      }
    }
    else {
      if (counter_while_ghosts_are_blue < 0x100) {
        if (red_ghost_sprite.color == 0x11) {
          red_ghost_sprite.color = 0x12;
        }
        else {
          red_ghost_sprite.color = 0x11;
        }
      }
    }
    if (pink_ghost_blue_flag == false) {
      if (pink_ghost_sprite.color == pink) {
        pink_ghost_sprite.color = pink;
      }
      else {
        pink_ghost_sprite.color = pink;
      }
    }
    else {
      if (counter_while_ghosts_are_blue < 0x100) {
        if (pink_ghost_sprite.color == 0x11) {
          pink_ghost_sprite.color = 0x12;
        }
        else {
          pink_ghost_sprite.color = 0x11;
        }
      }
    }
    if (blue_ghost_blue_flag == false) {
      if (blue_sprite.color == inky) {
        blue_sprite.color = inky;
      }
      else {
        blue_sprite.color = inky;
      }
    }
    else {
      if (counter_while_ghosts_are_blue < 0x100) {
        if (blue_sprite.color == 0x11) {
          blue_sprite.color = 0x12;
        }
        else {
          blue_sprite.color = 0x11;
        }
      }
    }
    if (orange_ghost_blue_flag == false) {
      if (orange_ghost_sprite.color == orange_and_color_maze_level_10_11_12_13) {
        orange_ghost_sprite.color = orange_and_color_maze_level_10_11_12_13;
      }
      else {
        orange_ghost_sprite.color = orange_and_color_maze_level_10_11_12_13;
      }
    }
    else {
      if (counter_while_ghosts_are_blue < 0x100) {
        if (orange_ghost_sprite.color == 0x11) {
          orange_ghost_sprite.color = 0x12;
        }
        else {
          orange_ghost_sprite.color = 0x11;
        }
      }
    }
  }
  counter__used_to_change_ghost_colors_under_big_pill_effects =
       counter__used_to_change_ghost_colors_under_big_pill_effects - 1;
  return;
}



void pacman_only_set_color_for_dead_ghost(void)

{
  color_e color;
  
                    // called from #0900
                    // set the color for a dead ghost
                    // 
  color = 0x19;
  if (subroutine_DEMO_state == 0x22) {
    color = fruit;
  }
  if (red_ghost_state != ALIVE) {
    red_ghost_sprite.color = color;
  }
  if (pink_ghost_state != ALIVE) {
    pink_ghost_sprite.color = color;
  }
  if (blue_ghost_state != ALIVE) {
    blue_sprite.color = color;
  }
  if (orange_ghost_state == ALIVE) {
    return;
  }
  orange_ghost_sprite.color = color;
  return;
}



byte handle_power_pill_flashes(void)

{
  byte bVar1;
  ushort *puVar2;
  
  if ((byte)(counter__to_handle_power_pill_flashes + 1) != 10) {
    counter__to_handle_power_pill_flashes = counter__to_handle_power_pill_flashes + 1;
    return 10;
  }
  counter__to_handle_power_pill_flashes = 0;
  if (subroutine_PLAYING_state == GHOST_MOVE) {
    puVar2 = (ushort *)get_maze_data_from_current_level((byte *)power_pellet_per_map_lookup_table);
    bVar1 = BYTE_ARRAY_ARRAY_ram_4440[2][6];
    if (BYTE_ARRAY_ARRAY_ram_4440[2][6] == *(byte *)(*puVar2 | 0x400)) {
      bVar1 = 0;
    }
    *(byte *)(*puVar2 | 0x400) = bVar1;
    *(byte *)(puVar2[1] | 0x400) = bVar1;
    *(byte *)(puVar2[2] | 0x400) = bVar1;
    *(byte *)(puVar2[3] | 0x400) = bVar1;
    return 0x10;
  }
                    // arrive from #0C1C
                    // flash the pellets in the demo screen where pac is chased by 4 ghosts and then
                    // eats a power pill and eats them all
                    // this causes a very minor bug in pac-man and ms. pac man.
                    // potentially 2 screen elements can sometimes get colored wrong when player
                    // dies.
                    // in pac-man, a dot may disappear at #4678
                    // 
  BYTE_ARRAY_ARRAY_ram_4440[20][8] = 0x10;
  if (BYTE_ARRAY_ARRAY_ram_4440[26][26] == 0x10) {
    BYTE_ARRAY_ARRAY_ram_4440[20][8] = 0;
  }
  BYTE_ARRAY_ARRAY_ram_4440[26][26] = BYTE_ARRAY_ARRAY_ram_4440[20][8];
  counter__to_handle_power_pill_flashes = 0;
  return BYTE_ARRAY_ARRAY_ram_4440[20][8];
}



// handles ghost movements when they are moving around in or coming out of the ghost home
// 

void adjust_ghost_movement(undefined param_1)

{
  char cVar1;
  
                    // **** red ghost *****
  if (number_of_ghost_killed_but_no_collision_for_yet != 0) {
    return;
  }
  cVar1 = (char)counter_related_to_ghost_movement_inside_home >> 7;
  counter_related_to_ghost_movement_inside_home =
       counter_related_to_ghost_movement_inside_home << 1 | -cVar1;
  if (-cVar1 == 0) {
    return;
  }
  if (red_ghost_substate_if_alive == AT_HOME) {
    red_ghost_coord = update_coord(&red_ghost_coord,&move_up);
    red_ghost_previous_orientation = up;
    red_ghost_orientation = up;
    if (red_ghost_coord.y == 100) {
      red_ghost_xy_tile_pos = 0x2e2c;
      red_ghost_Y_tile_changes_A = 0x100;
      red_ghost_xy_tile_changes = 0x100;
      red_ghost_previous_orientation = left;
      red_ghost_orientation = left;
      red_ghost_substate_if_alive = GOING_FOR_PACMAN;
    }
  }
                    // **** pink ghost ****
  if (pink_ghost_substate_if_alive != GOING_FOR_PACMAN) {
    if (pink_ghost_substate_if_alive == AT_HOME) {
                    // pink ghost is moving up and down in the ghost house
      if (pink_ghost_coord.y == 0x78) {
        pink_ghost_coord.y = reverse_pink_ghost_direction();
      }
      if (pink_ghost_coord.y == 0x80) {
        reverse_pink_ghost_direction();
      }
      pink_ghost_previous_orientation = pink_ghost_orientation;
      pink_ghost_coord = update_coord(&pink_ghost_coord,&pink_ghost_xy_tile_changes);
    }
    else {
                    // pink ghost is moving up out of the ghost house
      pink_ghost_coord = update_coord(&pink_ghost_coord,&move_up);
      pink_ghost_orientation = up;
      pink_ghost_previous_orientation = up;
      if (pink_ghost_coord.y == 100) {
                    // pink ghost has made it out of the ghost house
        pink_ghost_xy_tile_pos = 0x2e2c;
        pink_ghost_Y_tile_changes_A = 0x100;
        pink_ghost_xy_tile_changes = 0x100;
        pink_ghost_previous_orientation = left;
        pink_ghost_orientation = left;
        pink_ghost_substate_if_alive = GOING_FOR_PACMAN;
      }
    }
  }
                    // **** blue ghost (inky) ****
  if (blue_ghost_substate_if_alive != GOING_FOR_PACMAN) {
    if (blue_ghost_substate_if_alive == AT_HOME) {
                    // inky is moving up and down in the ghost house
                    // 
      if (blue_ghost_coord.y == 0x78) {
        blue_ghost_coord.y = reverse_blue_ghost_direction(param_1);
      }
      if (blue_ghost_coord.y == 0x80) {
        reverse_blue_ghost_direction(param_1);
      }
      blue_ghost_previous_orientation = blue_ghost_orientation;
      blue_ghost_coord = update_coord(&blue_ghost_coord,&blue_ghost_xy_tile_changes);
    }
    else {
      if (blue_ghost_substate_if_alive == GOING_TO_THE_DOOR) {
                    // inky is on his way out of ghost house to right
        blue_ghost_coord = update_coord(&blue_ghost_coord,&move_right);
        blue_ghost_previous_orientation = right;
        blue_ghost_orientation = right;
        blue_ghost_coord.x = (byte)((ushort)blue_ghost_coord >> 8);
        if (blue_ghost_coord.x == 0x80) {
          blue_ghost_substate_if_alive = CROSSING_THE_DOOR;
        }
      }
      else {
                    // inky is moving up out of the ghost house
        blue_ghost_coord = update_coord(&blue_ghost_coord,&move_up);
        blue_ghost_previous_orientation = up;
        blue_ghost_orientation = up;
        if (blue_ghost_coord.y == 100) {
                    // inky has made it out of the ghost house
          blue_ghost_xy_tile_pos = 0x2e2c;
          blue_ghost_Y_tile_changes_A = 0x100;
          blue_ghost_xy_tile_changes = 0x100;
          blue_ghost_previous_orientation = left;
          blue_ghost_orientation = left;
          blue_ghost_substate_if_alive = GOING_FOR_PACMAN;
        }
      }
    }
  }
                    // **** orange ghost ****
  if (orange_ghost_substate_if_alive == GOING_FOR_PACMAN) {
    return;
  }
  if (orange_ghost_substate_if_alive == AT_HOME) {
                    // orange ghost is moving up and down in the ghost house
    if (orange_ghost_coord.y == 0x78) {
      orange_ghost_coord.y = reverse_orange_ghost_direction(param_1);
    }
    if (orange_ghost_coord.y == 0x80) {
      reverse_orange_ghost_direction(param_1);
    }
    orange_ghost_previous_orientation = orange_ghost_orientation;
    orange_ghost_coord = update_coord(&orange_ghost_coord,&orange_ghost_xy_tile_changes);
    return;
  }
  if (orange_ghost_substate_if_alive == GOING_TO_THE_DOOR) {
                    // orange ghost is moving left, on his way out of ghost house
    orange_ghost_coord = update_coord(&orange_ghost_coord,&move_left);
    orange_ghost_coord.x = (byte)((ushort)orange_ghost_coord >> 8);
    if (orange_ghost_coord.x != 0x80) {
      orange_ghost_previous_orientation = left;
      orange_ghost_orientation = left;
      return;
    }
    orange_ghost_previous_orientation = left;
    orange_ghost_orientation = left;
    orange_ghost_substate_if_alive = CROSSING_THE_DOOR;
    return;
  }
                    // orange ghost is moving up and out of ghost house
  orange_ghost_coord = update_coord(&orange_ghost_coord,&move_up);
  if (orange_ghost_coord.y != 100) {
    orange_ghost_previous_orientation = up;
    orange_ghost_orientation = up;
    return;
  }
  orange_ghost_xy_tile_pos = 0x2e2c;
  orange_ghost_Y_tile_change_A = 0x100;
  orange_ghost_xy_tile_changes = 0x100;
  orange_ghost_previous_orientation = left;
  orange_ghost_orientation = left;
  orange_ghost_substate_if_alive = GOING_FOR_PACMAN;
                    // orange ghost has made it out of the ghost house
  return;
}



void is_time_to_change_ghost_animation(void)

{
  if ((byte)(counter__to_handle_things_once_every_8_times + 1) != 8) {
    counter__to_handle_things_once_every_8_times = counter__to_handle_things_once_every_8_times + 1;
    return;
  }
  counter__change_every_8_frames = counter__change_every_8_frames ^ 1;
  counter__to_handle_things_once_every_8_times = 0;
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void is_time_to_reverse_ghost_direction(void)

{
                    // called from #08fa
                    // 
  if (power_pill_effect != false) {
    return;
  }
  if (counter__orientation_changes_index == 7) {
    return;
  }
  counter__related_to_ghost_orientation_changes = counter__related_to_ghost_orientation_changes + 1;
  if (counter__related_to_ghost_orientation_changes !=
      *(word *)((short)difficulty_related_table +
               (ushort)(byte)(counter__orientation_changes_index * '\x02'))) {
    return;
  }
  _red_ghost_change_orientation_flag = 0x101;
  _blue_ghost_change_orientation_flag = 0x101;
  counter__orientation_changes_index = 1;
                    // arrive here when ghosts reverse direction
                    // this differs from the pac-man code
                    // OTTOPATCH
                    // PATCH TO MAKE RED MONSTER GO AFTER OTTO TO AVOID PARKING
                    // 
                    //  Pac-Man code follows
                    // this undoes the double from line #0E41
                    //  end pac-man code
                    // 
  return;
}



void change_background(void)

{
                    // called from #0906
                    // changes the background sound based on # of pills eaten
                    // 
  if (pacman_dead_animation_state != 0) {
    channel_2_effect.num = 0;
    return;
  }
  if (0xe3 < dots_eaten) {
    channel_2_effect.num = channel_2_effect.num & 0xe0 | 0x10;
    return;
  }
  if (0xd3 < dots_eaten) {
    channel_2_effect.num = channel_2_effect.num & 0xe0 | 8;
    return;
  }
  if (0xb3 < dots_eaten) {
    channel_2_effect.num = channel_2_effect.num & 0xe0 | 4;
    return;
  }
  if (0x73 < dots_eaten) {
    channel_2_effect.num = channel_2_effect.num & 0xe0 | 2;
    return;
  }
  channel_2_effect.num = channel_2_effect.num & 0xe0 | 1;
  return;
}



void check_for_fruit_to_come_out(void)

{
  byte bVar1;
  byte bVar2;
  byte *lookup_table;
  bool *pbVar3;
  difficulty5_fruit_release_t *pdVar4;
  undefined **ppuVar5;
  byte in_R;
  dereference_word_t dVar6;
  
                    // called from #0909
                    // OTTOPATCH
                    // PATCH TO THE PRIMARY FRUIT ROUTINE, THIS ROUTINE IS CALLED ONCE PER
                    // GAME STEP (THE MINIMUM TIME IT TAKES A MONSTER TO MOVE A PIXEL)
                    // 
  if (number_of_ghost_killed_but_no_collision_for_yet != 0) {
    return;
  }
  if ((fruit_points == 0) || (fruit_coord.y == 0)) {
    if (dots_eaten == 0x40) {
      pbVar3 = &first_fruit_flag;
    }
    else {
      if (dots_eaten != 0xb0) {
        return;
      }
      pbVar3 = &second_fruit_flag;
    }
    if (*pbVar3 != false) {
      return;
    }
    *pbVar3 = *pbVar3 + '\x01';
    bVar2 = current_level;
    if (6 < current_level) {
      bVar1 = in_R & 0x1f;
      do {
        bVar2 = bVar1;
        bVar1 = bVar2 - 7;
      } while (6 < bVar2);
    }
    pdVar4 = fruit_shape_color_points;
    fruit_sprite._0_1_ =
         dereference_pointer_to_byte((byte *)fruit_shape_color_points,bVar2 * '\x03');
    fruit_sprite.color = pdVar4->color;
    fruit_points = pdVar4->point;
    ppuVar5 = fruits_paths_entry;
    setup_fruit_path();
    fruit_coord = *(undefined2 *)((short)ppuVar5 + 1);
    return;
  }
  dVar6 = dereference_pointer_to_word((word *)BYTE_ARRAY_ram_8841,current_place_within_bounce);
  fruit_coord = (short)((uint5)dVar6 >> 0x18) + fruit_coord;
  current_place_within_bounce = current_place_within_bounce + 1;
  if ((current_place_within_bounce & 0xf) != 0) {
    return;
  }
  bVar2 = current_place_in_fruit_path - 1;
  current_place_in_fruit_path = bVar2;
  if (-1 < (char)bVar2) {
    channel_3_effect.num = channel_3_effect.num | 0x20;
    bVar1 = dereference_pointer_to_byte
                      (pointer_to_the_path_the_fruit_is_currently_following,bVar2 >> 2);
    bVar2 = bVar2 & 3;
    while (bVar2 != 0) {
      bVar1 = bVar1 >> 2;
      bVar2 = bVar2 - 1;
    }
    current_place_within_bounce = (bVar1 & 3) << 4;
    return;
  }
  fruit_coord.x = (byte)((ushort)fruit_coord >> 8);
  if (0x3f < (byte)(fruit_coord.x + 0x20)) {
    if (pointer_to_the_path_the_fruit_is_currently_following == BYTE_ARRAY_ram_8808) {
      lookup_table = get_maze_data_from_current_level((byte *)fruit_paths_exit);
      bVar2 = dereference_pointer_to_byte(lookup_table,(in_R & 3) * '\x05');
      pointer_to_the_path_the_fruit_is_currently_following = (byte *)CONCAT11(lookup_table[1],bVar2)
      ;
      current_place_in_fruit_path = lookup_table[2];
    }
    else {
      pointer_to_the_path_the_fruit_is_currently_following = BYTE_ARRAY_ram_8808;
      current_place_in_fruit_path = 0x1d;
    }
    current_place_within_bounce = 0x1f;
    return;
  }
  fruit_sprite.color = fruit;
  TT04_clear_fruit_points();
  return;
}



void TT04_clear_fruit_points(void)

{
  fruit_points = 0;
  return;
}



// this is timed task #05, arrive from #0246

void TT05_clear_fruit_position(void)

{
  fruit_coord = 0;
  return;
}



void update_ghost_and_pacman_state(void)

{
                    // called from #052C, #052F, #08EB and #08EE
                    // 
  is_pacman_dead();
  if (pacman_dead_animation_state != 0) {
    return;
  }
  check_for_ghosts_being_eaten_and_set_ghost_states_accordingly();
  state_red_ghost_update();
  state_pink_ghost_update();
  state_blue_ghost_update();
  state_orange_ghost_update();
  if (number_of_ghost_killed_but_no_collision_for_yet != 0) {
    ghost_stuff_after_eaten_or();
    return;
  }
  check_for_collision_with_regular_ghost();
  check_for_collision_with_blue_ghost();
  if (number_of_ghost_killed_but_no_collision_for_yet != 0) {
    return;
  }
  handles_pacman_movement();
  control_movement_red_ghost();
  control_movement_pink_ghost();
  control_movement_blue_ghost();
  control_movement_orange_ghost();
  if (subroutine_PLAYING_state != GHOST_MOVE) {
    return;
  }
  control_blue_ghost_timer();
  leave_house_check_pink_ghost();
  leave_house_check_blue_ghost();
  leave_house_check_orange_ghost();
  return;
}



void check_for_ghosts_being_eaten_and_set_ghost_states_accordingly(void)

{
  killing_ghost_state_e kVar1;
  killing_ghost_state_e kVar2;
  
                    // called from #101F
                    // 
  kVar2 = killing_ghost_state;
  if (killing_ghost_state == NOTHING) {
    return;
  }
  kVar1 = killing_ghost_state + ~NOTHING;
  if (kVar1 == NOTHING) {
    killing_ghost_state = kVar1;
    red_ghost_state = kVar2;
    return;
  }
  kVar2 = killing_ghost_state + ~KILL_RED_GHOST;
  if (kVar2 == NOTHING) {
    killing_ghost_state = kVar2;
    pink_ghost_state = kVar1;
    return;
  }
  kVar1 = killing_ghost_state + ~KILL_PINK_GHOST;
  if (kVar1 == NOTHING) {
    killing_ghost_state = kVar1;
    blue_ghost_state = kVar2;
    return;
  }
  killing_ghost_state = killing_ghost_state + ~KILL_BLUE_GHOST;
  orange_ghost_state = kVar1;
  return;
}



void state_red_ghost_update(void)

{
                    // called from #1022
                    // 
                    // WARNING: Return address prevents inlining here
  jump_table_fn((undefined *)state_red_ghost_update_fn_table,red_ghost_state);
  return;
}



void state_pink_ghost_update(void)

{
                    // WARNING: Return address prevents inlining here
  jump_table_fn((undefined *)state_pink_ghost_update_fn_table,pink_ghost_state);
  return;
}



void state_blue_ghost_update(void)

{
                    // called from #1028
                    // 
                    // WARNING: Return address prevents inlining here
  jump_table_fn((undefined *)state_blue_ghost_fn_table,blue_ghost_state);
  return;
}



void state_orange_ghost_update(void)

{
                    // WARNING: Return address prevents inlining here
  jump_table_fn((undefined *)state_orange_ghost_fn_table,orange_ghost_state);
  return;
}



void state_red_ghost_eyes(void)

{
                    // arrive here from #1097 when red ghost is dead (eyes)
                    // 
  handles_red_ghost_movement();
  if (red_ghost_coord != -0x7f9c) {
    return;
  }
  red_ghost_state = red_ghost_state + DEAD;
  return;
}



void state_red_ghost_eyes_above(void)

{
                    // arrive here from #1097 when red ghost eyes are above and entering the ghost
                    // house when returning home
                    // 
  red_ghost_coord = update_coord(&red_ghost_coord,&move_down);
  if (red_ghost_coord.y != 0x80) {
    red_ghost_previous_orientation = down;
    red_ghost_orientation = down;
    return;
  }
  if ((ghost_state_e)(pink_ghost_state | blue_ghost_state | orange_ghost_state) != 0) {
    red_ghost_xy_tile_pos = 0x2e2f;
    red_ghost_previous_orientation = down;
    red_ghost_orientation = down;
    red_ghost_tile_position_2 = 0x2e2f;
    red_ghost_substate_if_alive = AT_HOME;
    red_ghost_blue_flag = false;
    red_ghost_state = ALIVE;
    return;
  }
  red_ghost_xy_tile_pos = 0x2e2f;
  red_ghost_previous_orientation = down;
  red_ghost_orientation = down;
  red_ghost_tile_position_2 = 0x2e2f;
  red_ghost_substate_if_alive = AT_HOME;
  red_ghost_blue_flag = false;
  red_ghost_state = ALIVE;
  channel_2_effect.num = channel_2_effect.num & 0xbf;
  return;
}



// arrive here from #10A1 when pink ghost is dead (eyes)
// 

void state_pink_ghost_eyes(void)

{
  handles_pink_ghost_movement();
  if (pink_ghost_coord != -0x7f9c) {
    return;
  }
  pink_ghost_state = pink_ghost_state + DEAD;
  return;
}



// arrive here from #10A1 when pink ghost eyes are above and entering the ghost house when returning
// home
// 

void state_pink_ghost_eyes_above(void)

{
  pink_ghost_coord = update_coord(&pink_ghost_coord,&move_down);
  if (pink_ghost_coord.y != 0x80) {
    pink_ghost_previous_orientation = down;
    pink_ghost_orientation = down;
    return;
  }
  if ((ghost_state_e)(red_ghost_state | blue_ghost_state | orange_ghost_state) != 0) {
    pink_ghost_xy_tile_pos = 0x2e2f;
    pink_ghost_previous_orientation = down;
    pink_ghost_orientation = down;
    pink_ghost_tile_position_2 = 0x2e2f;
    pink_ghost_substate_if_alive = AT_HOME;
    pink_ghost_blue_flag = false;
    pink_ghost_state = ALIVE;
    return;
  }
  pink_ghost_xy_tile_pos = 0x2e2f;
  pink_ghost_previous_orientation = down;
  pink_ghost_orientation = down;
  pink_ghost_tile_position_2 = 0x2e2f;
  pink_ghost_substate_if_alive = AT_HOME;
  pink_ghost_blue_flag = false;
  pink_ghost_state = ALIVE;
  channel_2_effect.num = channel_2_effect.num & 0xbf;
  return;
}



void state_blue_ghost_eyes(void)

{
                    // arrive here from #10AB when blue ghost (inky) is dead (eyes)
                    // 
  handles_blue_ghost_movement();
  if (blue_ghost_coord != -0x7f9c) {
    return;
  }
  blue_ghost_state = blue_ghost_state + DEAD;
  return;
}



void state_blue_ghost_eyes_above(void)

{
                    // arrive here from #10AB when blue ghost (inky) eyes are above and entering the
                    // ghost house when returning home
                    // 
  blue_ghost_coord = update_coord(&blue_ghost_coord,&move_down);
  if (blue_ghost_coord.y != 0x80) {
    blue_ghost_previous_orientation = down;
    blue_ghost_orientation = down;
    return;
  }
  blue_ghost_previous_orientation = down;
  blue_ghost_orientation = down;
  blue_ghost_state = blue_ghost_state + DEAD;
  return;
}



void state_blue_ghost_eyes_in_house(void)

{
                    // arrive here from #10AB when inky ghost eyes have arrived in ghost house and
                    // when moving to left side of ghost house
                    // 
  blue_ghost_coord = update_coord(&blue_ghost_coord,&move_left);
  blue_ghost_coord.x = (byte)((ushort)blue_ghost_coord >> 8);
  if (blue_ghost_coord.x != 0x90) {
    blue_ghost_previous_orientation = left;
    blue_ghost_orientation = left;
    return;
  }
  if ((ghost_state_e)(red_ghost_state | pink_ghost_state | orange_ghost_state) != 0) {
    blue_ghost_xy_tile_pos = 0x302f;
    blue_ghost_previous_orientation = down;
    blue_ghost_orientation = down;
    blue_ghost_tile_position_2 = 0x302f;
    blue_ghost_substate_if_alive = AT_HOME;
    blue_ghost_blue_flag = false;
    blue_ghost_state = ALIVE;
    return;
  }
  blue_ghost_xy_tile_pos = 0x302f;
  blue_ghost_previous_orientation = down;
  blue_ghost_orientation = down;
  blue_ghost_tile_position_2 = 0x302f;
  blue_ghost_substate_if_alive = AT_HOME;
  blue_ghost_blue_flag = false;
  blue_ghost_state = ALIVE;
  channel_2_effect.num = channel_2_effect.num & 0xbf;
  return;
}



void state_orange_ghost_eyes(void)

{
                    // arrive here from #10B7 when orange ghost is dead (eyes)
                    // 
  handles_orange_ghost_movement();
  if (orange_ghost_coord != -0x7f9c) {
    return;
  }
  orange_ghost_state = orange_ghost_state + DEAD;
  return;
}



void state_orange_ghost_eyes_above(void)

{
                    // arrive here from #10B7 when orange ghost eyes are above and entering the
                    // ghost house when returning home
                    // 
  orange_ghost_coord = update_coord(&orange_ghost_coord,&move_down);
  if (orange_ghost_coord.y != 0x80) {
    orange_ghost_previous_orientation = down;
    orange_ghost_orientation = down;
    return;
  }
  orange_ghost_previous_orientation = down;
  orange_ghost_orientation = down;
  orange_ghost_state = orange_ghost_state + DEAD;
  return;
}



void state_orange_ghost_eyes_in_house(void)

{
                    // arrive here from #10B7 when orange ghost eyes have arrived in ghost house and
                    // when moving to right side of ghost house
                    // 
  orange_ghost_coord = update_coord(&orange_ghost_coord,&move_right);
  orange_ghost_coord.x = (byte)((ushort)orange_ghost_coord >> 8);
  if (orange_ghost_coord.x != 0x70) {
    orange_ghost_previous_orientation = right;
    orange_ghost_orientation = right;
    return;
  }
  if ((ghost_state_e)(red_ghost_state | pink_ghost_state | blue_ghost_state) != 0) {
    orange_ghost_xy_tile_pos = 0x2c2f;
    orange_ghost_previous_orientation = down;
    orange_ghost_orientation = down;
    orange_ghost_tile_position_2 = 0x2c2f;
    orange_ghost_substate_if_alive = AT_HOME;
    orange_ghost_blue_flag = false;
    orange_ghost_state = ALIVE;
    return;
  }
  orange_ghost_xy_tile_pos = 0x2c2f;
  orange_ghost_previous_orientation = down;
  orange_ghost_orientation = down;
  orange_ghost_tile_position_2 = 0x2c2f;
  orange_ghost_substate_if_alive = AT_HOME;
  orange_ghost_blue_flag = false;
  orange_ghost_state = ALIVE;
  channel_2_effect.num = channel_2_effect.num & 0xbf;
  return;
}



// called from #1035
// arrive here when a ghost is eaten, or after the point score for eating a ghost is set to vanish
// 

void ghost_stuff_after_eaten_or(void)

{
                    // WARNING: Return address prevents inlining here
  jump_table_fn((undefined *)ghost_stuff_after_eaten_or_fn_table,killed_ghost_animation_state);
  return;
}



void ghost_stuff0(void)

{
  byte bVar1;
  byte bVar2;
  byte *pbVar3;
  
  bVar1 = number_of_ghost_killed_but_no_collision_for_yet * '\x02';
  pbVar3 = (byte *)(&start_of_sprites_address.field_0x0 + (ushort)bVar1);
  if (killed_ghost_animation_state == 0) {
    bVar2 = counter__current_number_of_killed_ghosts + 0x27;
    if ((current_player_number & cocktail_mode) != 0) {
      bVar2 = bVar2 | 0xc0;
    }
    *pbVar3 = bVar2;
    (&start_of_sprites_address.color)[(ushort)bVar1] = color_maze_level_14_15_16_17_and_ghosts_door;
    mspac_sprite.color = fruit;
                    // WARNING: Return address prevents inlining here
    add_timed_task(&task_increase_killed_ghost_animation_state);
    return;
  }
  *pbVar3 = 0x20;
  killing_ghost_state = number_of_ghost_killed_but_no_collision_for_yet;
  mspac_sprite.color = mspac;
  number_of_ghost_killed_but_no_collision_for_yet = 0;
  killed_ghost_animation_state = 0;
  channel_2_effect.num = channel_2_effect.num | 0x40;
  return;
}



void TT03_increase_killed_ghost_animation_state(void)

{
  killed_ghost_animation_state = killed_ghost_animation_state + 1;
  return;
}



void is_pacman_dead(void)

{
                    // called from #1017
                    // 
                    // WARNING: Return address prevents inlining here
  jump_table_fn((undefined *)dead_animation_fn_table,pacman_dead_animation_state);
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void D01_dead_animation_state_1_2_3_4(void)

{
  _dead_animation_counter = _dead_animation_counter + 1;
  if (_dead_animation_counter != 0x78) {
    return;
  }
  pacman_dead_animation_state = 5;
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void D05_dead_animation_state(void)

{
                    // adjust mspac sprite animation while dying
                    // 
  clear_all_ghost_from_screen(0);
  mspac_sprite._0_1_ = 0x34;
  if ((current_player_number & cocktail_mode) != 0) {
    mspac_sprite._0_1_ = 0xf4;
  }
  _dead_animation_counter = _dead_animation_counter + 1;
  if (_dead_animation_counter != 0xb4) {
    return;
  }
  pacman_dead_animation_state = pacman_dead_animation_state + 1;
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void animate_dead_mspac(byte param_1,short param_2)

{
  if ((current_player_number & cocktail_mode) != 0) {
    param_1 = param_1 | 0xc0;
  }
  _dead_animation_counter = _dead_animation_counter + 1;
  if (_dead_animation_counter != param_2) {
    mspac_sprite._0_1_ = param_1;
    return;
  }
  mspac_sprite._0_1_ = param_1;
  pacman_dead_animation_state = pacman_dead_animation_state + 1;
  return;
}



void D06_dead_animation_state(void)

{
  channel_3_effect.num = channel_3_effect.num | 0x10;
  animate_dead_mspac(0x35,0xc3);
  return;
}



void D07_dead_animation_state(void)

{
  animate_dead_mspac(0x36,0xd2);
  return;
}



void D08_dead_animation_state(void)

{
  animate_dead_mspac(0x37,0xe1);
  return;
}



void D09_dead_animation_state(void)

{
  animate_dead_mspac(0x38,0xf0);
  return;
}



void D0A_dead_animation_state(void)

{
  animate_dead_mspac(0x39,0xff);
  return;
}



void D0B_dead_animation_state(void)

{
  animate_dead_mspac(0x3a,0x10e);
  return;
}



void D0C_dead_animation_state(void)

{
  animate_dead_mspac(0x3b,0x11d);
  return;
}



void D0D_dead_animation_state(void)

{
  animate_dead_mspac(0x3c,300);
  return;
}



void D0E_dead_animation_state(void)

{
  animate_dead_mspac(0x3d,0x13b);
  return;
}



void D0F_dead_animation_state(void)

{
  channel_3_effect.num = 0;
  animate_dead_mspac(0x3e,0x159);
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void D10_dead_animation_state(void)

{
  mspac_sprite._0_1_ = 0x3f;
  _dead_animation_counter = _dead_animation_counter + 1;
  if (_dead_animation_counter != 0x1b8) {
    mspac_sprite._0_1_ = 0x3f;
    return;
  }
                    // decrement lives
                    // this gets called after the death animation, but before the screen gets
                    // redrawn.
                    // -- probably a good hook point for 'insert coin to contunue' --
                    // 
  real_number_of_lives = real_number_of_lives - 1;
  number_of_lives_displayed = number_of_lives_displayed - 1;
  T1E_clear_fruit_and_pacman_position();
  subroutine_PLAYING_state = subroutine_PLAYING_state + 1;
  return;
}



// routine to control blue time
// ret immediately to make ghosts stay blue till eaten
// 

void control_blue_ghost_timer(void)

{
  if (power_pill_effect == false) {
    return;
  }
  if ((byte)(red_ghost_blue_flag | pink_ghost_blue_flag | blue_ghost_blue_flag |
            orange_ghost_blue_flag) != 0) {
    counter_while_ghosts_are_blue = counter_while_ghosts_are_blue - 1;
    if ((byte)((byte)(counter_while_ghosts_are_blue >> 8) | (byte)counter_while_ghosts_are_blue) !=
        0) {
      return;
    }
  }
                    // arrive here when power pill effect is over, either by timer or by eating all
                    // ghosts
                    // 
  if (red_ghost_state == ALIVE) {
    red_ghost_blue_flag = (bool)red_ghost_state;
  }
  if (pink_ghost_state == ALIVE) {
    pink_ghost_blue_flag = (bool)pink_ghost_state;
  }
  if (blue_ghost_state == ALIVE) {
    blue_ghost_blue_flag = (bool)blue_ghost_state;
  }
  if (orange_ghost_state == ALIVE) {
    orange_ghost_blue_flag = (bool)orange_ghost_state;
  }
  mspac_sprite.color = mspac;
  power_pill_effect = false;
  counter__used_to_change_ghost_colors_under_big_pill_effects = 0;
  counter_while_ghosts_are_blue = 0;
  counter__current_number_of_killed_ghosts = 0;
  channel_2_effect.num = channel_2_effect.num & 0x5f;
  return;
}



void is_time_to_leave_house(void)

{
                    // arrive here from call at #08F1
                    // 
  if (dots_eaten != related_to_number_of_pills_eaten_before_last_pacman_move) {
    inactivity_counter_for_units_of_the_above = 0;
    return;
  }
  if (inactivity_counter_for_units_of_the_above + 1 != number_of_units_before_ghost_leaves_home) {
    inactivity_counter_for_units_of_the_above = inactivity_counter_for_units_of_the_above + 1;
    return;
  }
  inactivity_counter_for_units_of_the_above = 0;
  if (pink_ghost_substate_if_alive == AT_HOME) {
    release_pink_ghost_from_the_ghost_house(0);
    return;
  }
  if (blue_ghost_substate_if_alive != AT_HOME) {
    if (orange_ghost_substate_if_alive == AT_HOME) {
      releases_orange_ghost_from_the_ghost_house(0);
    }
    return;
  }
  release_blue_ghost_from_the_ghost_house(0);
  return;
}



// arrive here from #01A1
// during core game loop
// 

void cocktail_mode_update_sprites(void)

{
  if ((current_player_number & cocktail_mode) == 0) {
    return;
  }
                    // yes, handle sprite flips
                    // 
  sprites_coords_xy[0].y = red_ghost_coord.y + 8;
  sprites_coords_xy[0].x = ~red_ghost_coord.x + 7;
  sprites_coords_xy[1].y = pink_ghost_coord.y + 8;
  sprites_coords_xy[1].x = ~pink_ghost_coord.x + 7;
  sprites_coords_xy[2].y = blue_ghost_coord.y + 8;
  sprites_coords_xy[2].x = ~blue_ghost_coord.x + 8;
  sprites_coords_xy[3].y = orange_ghost_coord.y + 8;
  sprites_coords_xy[3].x = ~orange_ghost_coord.x + 8;
  sprites_coords_xy[4].y = pacman_coord.y + 8;
  sprites_coords_xy[4].x = ~pacman_coord.x + 8;
  sprites_coords_xy[5].y = fruit_coord.y + 8;
  sprites_coords_xy[5].x = ~fruit_coord.x + 8;
  update_pacman_orientation();
  return;
}



// called from #019E during core game loop
// display the sprites in the intro and game and cutscenes
// 

void no_cocktail_mode_update_sprites(void)

{
  byte bVar1;
  byte bVar2;
  char cVar3;
  undefined **ppuVar4;
  hardware_floating_sprite_t *phVar5;
  undefined *puStack2;
  
  bVar2 = current_player_number & cocktail_mode;
  if (bVar2 != 0) {
    return;
  }
  phVar5 = &start_of_sprites_address;
  sprites_coords_xy[0].y = ~red_ghost_coord.y + 9;
  sprites_coords_xy[0].x = red_ghost_coord.x + 6;
  sprites_coords_xy[1].y = ~pink_ghost_coord.y + 9;
  sprites_coords_xy[1].x = pink_ghost_coord.x + 6;
  sprites_coords_xy[2].y = ~blue_ghost_coord.y + 9;
  sprites_coords_xy[2].x = blue_ghost_coord.x + 7;
  sprites_coords_xy[3].y = ~orange_ghost_coord.y + 9;
  sprites_coords_xy[3].x = orange_ghost_coord.x + 7;
  sprites_coords_xy[4].y = ~pacman_coord.y + 9;
  sprites_coords_xy[4].x = pacman_coord.x + 7;
  sprites_coords_xy[5].y = ~fruit_coord.y + 9;
  sprites_coords_xy[5].x = fruit_coord.x + 7;
  if (pacman_dead_animation_state == 0) {
    if (number_of_ghost_killed_but_no_collision_for_yet != 0) goto LAB_ram_15b4;
    ppuVar4 = &puStack2;
    ppuVar4 = &puStack2;
    ppuVar4 = &puStack2;
    ppuVar4 = &puStack2;
    ppuVar4 = &puStack2;
    ppuVar4 = &puStack2;
    puStack2 = &return_address;
                    // WARNING: Return address prevents inlining here
    jump_table_fn((undefined *)orientation_fn_table,pacman_orientation);
    register0x44 = (BADSPACEBASE *)&puStack2;
    if (bVar2 != 0) {
      if ((mspac_sprite._0_1_ & 0xc0) == 0) {
        mspac_sprite._0_1_ = mspac_sprite._0_1_ | 0xc0;
        register0x44 = (BADSPACEBASE *)ppuVar4;
      }
      else {
        if (pacman_orientation == left) {
          register0x44 = (BADSPACEBASE *)ppuVar4;
          if ((mspac_sprite._0_1_ & 0x80) != 0) {
            mspac_sprite._0_1_ = mspac_sprite._0_1_ ^ 0xc0;
            register0x44 = (BADSPACEBASE *)ppuVar4;
          }
        }
        else {
          register0x44 = (BADSPACEBASE *)ppuVar4;
          if ((pacman_orientation == up) &&
             (register0x44 = (BADSPACEBASE *)ppuVar4, (mspac_sprite._0_1_ & 0x40) != 0)) {
            mspac_sprite._0_1_ = mspac_sprite._0_1_ ^ 0xc0;
            register0x44 = (BADSPACEBASE *)ppuVar4;
          }
        }
      }
    }
  }
  bVar1 = counter__change_every_8_frames;
  cVar3 = counter__change_every_8_frames + 0x1c;
  *(char *)(phVar5 + 1) = cVar3;
  *(char *)(phVar5 + 2) = cVar3;
  *(char *)(phVar5 + 3) = cVar3;
  *(char *)(phVar5 + 4) = cVar3;
  if ((red_ghost_state != ALIVE) || (red_ghost_blue_flag == false)) {
    *(character_orientation_e *)(phVar5 + 1) = red_ghost_orientation * '\x02' + bVar1 + ' ';
  }
  if ((pink_ghost_state != ALIVE) || (pink_ghost_blue_flag == false)) {
    *(character_orientation_e *)(phVar5 + 2) = pink_ghost_orientation * '\x02' + bVar1 + ' ';
  }
  if ((blue_ghost_state != ALIVE) || (blue_ghost_blue_flag == false)) {
    *(character_orientation_e *)(phVar5 + 3) = blue_ghost_orientation * '\x02' + bVar1 + ' ';
  }
  if ((orange_ghost_state != ALIVE) || (orange_ghost_blue_flag == false)) {
    *(character_orientation_e *)(phVar5 + 4) = orange_ghost_orientation * '\x02' + bVar1 + ' ';
  }
LAB_ram_15b4:
  *(undefined2 *)((undefined *)register0x44 + -2) = 0x15b7;
  pacman_only_check_for_and_handle_big_pac_man_sprites_in_1st_cutscene
            (phVar5,((undefined *)register0x44)[-2]);
  *(undefined2 *)((undefined *)register0x44 + -2) = 0x15ba;
  pacman_only_check_for_and_handle_big_pac_man_sprites_in_2nd_cutscene
            (phVar5,((undefined *)register0x44)[-2]);
  *(undefined2 *)((undefined *)register0x44 + -2) = 0x15bd;
  pacman_only_check_for_and_handle_big_pac_man_sprites_in_3rd_cutscene
            (phVar5,((undefined *)register0x44)[-2]);
  if (bVar2 != 0) {
    red_ghost_sprite._0_1_ = red_ghost_sprite._0_1_ | 0xc0;
    pink_ghost_sprite._0_1_ = pink_ghost_sprite._0_1_ | 0xc0;
    blue_sprite._0_1_ = blue_sprite._0_1_ | 0xc0;
    orange_ghost_sprite._0_1_ = orange_ghost_sprite._0_1_ | 0xc0;
    fruit_sprite._0_1_ = fruit_sprite._0_1_ | 0xc0;
    return;
  }
  return;
}



// also arrive here if player 2 and cocktail mode from #148D

void update_pacman_orientation(undefined2 param_1,short param_2)

{
  byte bVar1;
  char cVar2;
  char cVar3;
  undefined **ppuVar4;
  undefined *puStack2;
  
  cVar3 = (char)((ushort)param_1 >> 8);
  if (pacman_dead_animation_state == 0) {
    if (number_of_ghost_killed_but_no_collision_for_yet != 0) goto LAB_ram_15b4;
    ppuVar4 = &puStack2;
    ppuVar4 = &puStack2;
    ppuVar4 = &puStack2;
    ppuVar4 = &puStack2;
    ppuVar4 = &puStack2;
    ppuVar4 = &puStack2;
    puStack2 = &return_address;
                    // WARNING: Return address prevents inlining here
    jump_table_fn((undefined *)orientation_fn_table,pacman_orientation);
    register0x44 = (BADSPACEBASE *)&puStack2;
    if (cVar3 != '\0') {
      if ((mspac_sprite._0_1_ & 0xc0) == 0) {
        mspac_sprite._0_1_ = mspac_sprite._0_1_ | 0xc0;
        register0x44 = (BADSPACEBASE *)ppuVar4;
      }
      else {
        if (pacman_orientation == left) {
          register0x44 = (BADSPACEBASE *)ppuVar4;
          if ((mspac_sprite._0_1_ & 0x80) != 0) {
            mspac_sprite._0_1_ = mspac_sprite._0_1_ ^ 0xc0;
            register0x44 = (BADSPACEBASE *)ppuVar4;
          }
        }
        else {
          register0x44 = (BADSPACEBASE *)ppuVar4;
          if ((pacman_orientation == up) &&
             (register0x44 = (BADSPACEBASE *)ppuVar4, (mspac_sprite._0_1_ & 0x40) != 0)) {
            mspac_sprite._0_1_ = mspac_sprite._0_1_ ^ 0xc0;
            register0x44 = (BADSPACEBASE *)ppuVar4;
          }
        }
      }
    }
  }
                    // the next section of code toggles the sprites for the ghosts based on the
                    // counter that flips every 8 frames
                    // 
  bVar1 = counter__change_every_8_frames;
  cVar2 = counter__change_every_8_frames + 0x1c;
                    // toggle between #1C and #1D (edible ghost sprites) for all ghosts ... those
                    // that are not edible are changed again later
                    // 
  *(char *)(param_2 + 2) = cVar2;
  *(char *)(param_2 + 4) = cVar2;
  *(char *)(param_2 + 6) = cVar2;
  *(char *)(param_2 + 8) = cVar2;
  if ((red_ghost_state != ALIVE) || (red_ghost_blue_flag == false)) {
    *(char *)(param_2 + 2) = red_ghost_orientation * '\x02' + bVar1 + ' ';
  }
  if ((pink_ghost_state != ALIVE) || (pink_ghost_blue_flag == false)) {
    *(char *)(param_2 + 4) = pink_ghost_orientation * '\x02' + bVar1 + ' ';
  }
  if ((blue_ghost_state != ALIVE) || (blue_ghost_blue_flag == false)) {
    *(char *)(param_2 + 6) = blue_ghost_orientation * '\x02' + bVar1 + ' ';
  }
  if ((orange_ghost_state != ALIVE) || (orange_ghost_blue_flag == false)) {
    *(char *)(param_2 + 8) = orange_ghost_orientation * '\x02' + bVar1 + ' ';
  }
LAB_ram_15b4:
  *(undefined2 *)((undefined *)register0x44 + -2) = 0x15b7;
  pacman_only_check_for_and_handle_big_pac_man_sprites_in_1st_cutscene
            (param_2,((undefined *)register0x44)[-2]);
  *(undefined2 *)((undefined *)register0x44 + -2) = 0x15ba;
  pacman_only_check_for_and_handle_big_pac_man_sprites_in_2nd_cutscene
            (param_2,((undefined *)register0x44)[-2]);
  *(undefined2 *)((undefined *)register0x44 + -2) = 0x15bd;
  pacman_only_check_for_and_handle_big_pac_man_sprites_in_3rd_cutscene
            (param_2,((undefined *)register0x44)[-2]);
  if (cVar3 != '\0') {
                    // 2 player and cocktail
                    // 
    red_ghost_sprite._0_1_ = red_ghost_sprite._0_1_ | 0xc0;
    pink_ghost_sprite._0_1_ = pink_ghost_sprite._0_1_ | 0xc0;
    blue_sprite._0_1_ = blue_sprite._0_1_ | 0xc0;
    orange_ghost_sprite._0_1_ = orange_ghost_sprite._0_1_ | 0xc0;
    fruit_sprite._0_1_ = fruit_sprite._0_1_ | 0xc0;
    return;
  }
  return;
}



void pacman_only_check_for_and_handle_big_pac_man_sprites_in_1st_cutscene(short param_1)

{
  byte bVar1;
  char cVar2;
  
                    // called from #15B4
                    // 
  if (state_in_first_cutscene < 5) {
    return;
  }
                    // pac-man only, not used in ms. pac
                    // arrive here when the big pac-man needs to be animated in the 1st cutscene
                    // 
  bVar1 = pacman_coord.x & 0xf;
  if (bVar1 < 0xc) {
    if (bVar1 < 8) {
      if (bVar1 < 4) {
        cVar2 = '\x14';
      }
      else {
        cVar2 = '\x10';
      }
    }
    else {
      cVar2 = '\x14';
    }
  }
  else {
    cVar2 = '\x18';
  }
  *(char *)(param_1 + 4) = cVar2;
  *(char *)(param_1 + 6) = cVar2 + '\x01';
  *(char *)(param_1 + 8) = cVar2 + '\x02';
  *(char *)(param_1 + 0xc) = cVar2 + '\x03';
  *(undefined *)(param_1 + 10) = 0x3f;
  *(undefined *)(param_1 + 5) = 0x16;
  *(undefined *)(param_1 + 7) = 0x16;
  *(undefined *)(param_1 + 9) = 0x16;
  *(undefined *)(param_1 + 0xd) = 0x16;
  return;
}



void pacman_only_check_for_and_handle_big_pac_man_sprites_in_2nd_cutscene(short param_1)

{
  byte bVar1;
  
                    // called from #15B7
                    // 
  bVar1 = state_in_second_cutscene;
  if (state_in_second_cutscene == 0) {
    return;
  }
                    // pac-man only, not used in ms. pac
                    // arrive here during 2nd cutscene
                    // 
  if (pacman_position_tile_position.x == 0x3d) {
    *(undefined *)(param_1 + 0xb) = 0;
  }
  if (bVar1 < 10) {
    return;
  }
  *(undefined *)(param_1 + 2) = 0x32;
  *(undefined *)(param_1 + 3) = 0x1d;
  if (bVar1 < 0xc) {
    return;
  }
  *(undefined *)(param_1 + 2) = 0x33;
  return;
}



void pacman_only_check_for_and_handle_big_pac_man_sprites_in_3rd_cutscene(short param_1)

{
  byte bVar1;
  
                    // called from #15BA
                    // 
  bVar1 = state_in_third_cutscene;
  if (state_in_third_cutscene == 0) {
    return;
  }
                    // pac-man only, not used is ms. pac
                    // arrive here during 3rd cutscene
                    // 
  if (pacman_position_tile_position.x == 0x3d) {
    *(undefined *)(param_1 + 0xb) = 0;
  }
  if (bVar1 == 0) {
    return;
  }
  *(char *)(param_1 + 2) = counter__change_every_8_frames + 8;
  if (bVar1 < 3) {
    return;
  }
  bVar1 = (red_ghost_coord.x & 8) >> 3;
  *(char *)(param_1 + 0xc) = bVar1 + 10;
  *(char *)(param_1 + 2) = bVar1 + 0xc;
  *(undefined *)(param_1 + 0xd) = 0x1e;
  return;
}



// arrive here when pac man is facing right from #1513
// MOVING EAST
// 

void O00_moving_east(void)

{
  mspac_sprite._0_1_ = ~((pacman_coord.x & 7) >> 1) + 0x30;
  if ((mspac_sprite._0_1_ & 1) == 0) {
    mspac_sprite._0_1_ = 0x37;
  }
  return;
}



// arrive here when pac man is facing down from #1513
// MOVING SOUTH
// 

void O01_moving_south(void)

{
  mspac_sprite._0_1_ = ((pacman_coord.y & 7) >> 1) + 0x30;
  if ((mspac_sprite._0_1_ & 1) == 0) {
    mspac_sprite._0_1_ = 0x34;
  }
  return;
}



// arrive here when pac man is facing left from #1513
// MOVING WEST
// 

void O02_moving_west(void)

{
                    // arrive from #16D9 when ms pac is facing left
                    // MSPAC MOVING WEST
                    // 
  mspac_sprite._0_1_ = ((pacman_coord.x & 7) >> 1) + 0xac;
  if ((mspac_sprite._0_1_ & 1) == 0) {
    mspac_sprite._0_1_ = 0x35;
  }
  return;
}



// arrive here when pac man is facing up from #1513
// MOVING NORTH
// 

void O03_moving_north(void)

{
  mspacman_moving_north();
  return;
}



void check_for_collision_with_regular_ghost(void)

{
                    //  normal ghost collision detect
                    //  called from #1039
                    // 
  number_of_ghost_killed_but_no_collision_for_yet = 4;
  if (((((orange_ghost_state != ALIVE) ||
        (orange_ghost_tile_position_2 != pacman_position_tile_position)) &&
       ((number_of_ghost_killed_but_no_collision_for_yet = 3, blue_ghost_state != ALIVE ||
        (blue_ghost_tile_position_2 != pacman_position_tile_position)))) &&
      ((number_of_ghost_killed_but_no_collision_for_yet = 2, pink_ghost_state != ALIVE ||
       (pink_ghost_tile_position_2 != pacman_position_tile_position)))) &&
     ((number_of_ghost_killed_but_no_collision_for_yet = 1, red_ghost_state != ALIVE ||
      (red_ghost_tile_position_2 != pacman_position_tile_position)))) {
    number_of_ghost_killed_but_no_collision_for_yet = 0;
  }
                    // HACK3
                    // 1764 c3b01f    jp      #1fb0
                    // 
  if (number_of_ghost_killed_but_no_collision_for_yet == 0) {
    pacman_dead_animation_state = number_of_ghost_killed_but_no_collision_for_yet;
    return;
  }
  if ((&power_pill_effect)[number_of_ghost_killed_but_no_collision_for_yet] == false) {
    pacman_dead_animation_state = number_of_ghost_killed_but_no_collision_for_yet;
    return;
  }
                    // else arrive here when eating a blue ghost
                    // 
  pacman_dead_animation_state = 0;
  counter__current_number_of_killed_ghosts = counter__current_number_of_killed_ghosts + 1;
  T19_update_score_then_draw();
  channel_3_effect.num = channel_3_effect.num | 8;
  return;
}



void check_for_collision_with_blue_ghost(void)

{
                    //  end normal ghost collision detect
                    //  blue (edible) ghost collision detect
                    // called from #103C
                    // 
  if (number_of_ghost_killed_but_no_collision_for_yet != 0) {
    return;
  }
  if (power_pill_effect == false) {
    return;
  }
  number_of_ghost_killed_but_no_collision_for_yet = 4;
  if (((((orange_ghost_state != ALIVE) || (3 < (byte)(orange_ghost_coord.y - pacman_coord.y))) ||
       (3 < (byte)(orange_ghost_coord.x - pacman_coord.x))) &&
      ((((number_of_ghost_killed_but_no_collision_for_yet = 3, blue_ghost_state != ALIVE ||
         (3 < (byte)(blue_ghost_coord.y - pacman_coord.y))) ||
        (3 < (byte)(blue_ghost_coord.x - pacman_coord.x))) &&
       (((number_of_ghost_killed_but_no_collision_for_yet = 2, pink_ghost_state != ALIVE ||
         (3 < (byte)(pink_ghost_coord.y - pacman_coord.y))) ||
        (3 < (byte)(pink_ghost_coord.x - pacman_coord.x))))))) &&
     (((number_of_ghost_killed_but_no_collision_for_yet = 1, red_ghost_state != ALIVE ||
       (3 < (byte)(red_ghost_coord.y - pacman_coord.y))) ||
      (3 < (byte)(red_ghost_coord.x - pacman_coord.x))))) {
    number_of_ghost_killed_but_no_collision_for_yet = 0;
  }
  if (number_of_ghost_killed_but_no_collision_for_yet == 0) {
    pacman_dead_animation_state = number_of_ghost_killed_but_no_collision_for_yet;
    return;
  }
  if ((&power_pill_effect)[number_of_ghost_killed_but_no_collision_for_yet] == false) {
    pacman_dead_animation_state = number_of_ghost_killed_but_no_collision_for_yet;
    return;
  }
  pacman_dead_animation_state = 0;
  counter__current_number_of_killed_ghosts = counter__current_number_of_killed_ghosts + 1;
  T19_update_score_then_draw();
  channel_3_effect.num = channel_3_effect.num | 8;
  return;
}



// end of blue ghost collision detection
// called from #1044
// 

void handles_pacman_movement(void)

{
  ushort uVar1;
  bool bVar2;
  in0_t iVar3;
  byte bVar4;
  byte bVar5;
  char cVar6;
  ushort uVar7;
  byte *pbVar8;
  sprite_coord_yx_t *sprite_location;
  
                    // Hack code:
                    // HACK8 (1 of 3)
                    // HACK3
                    // HACK5
                    // end hack code
                    // 
                    // Hack code
                    // HACK2 (1 of 2)
                    // 180b  01
                    // i'm not entirely sure how this works.  it mangles
                    // the opcodes starting at 180b to be:
                    // 080b 01ca11    ld      bc,11cah
                    // 080e 1835      jr      1845h
                    // 0810 c9        ret
                    // which makes little to no sense, but it works
                    // end hack code
                    // 
  if (delay_pacman_movement != PACMAN_NOT_EATING) {
    delay_pacman_movement = delay_pacman_movement + PACMAN_NOT_EATING;
    return;
  }
  if (power_pill_effect == false) {
    uVar1 = pacman_state.normal_state._2_2_ * 2;
                    // movement when power pill not active
                    // 
    uVar7 = (ushort)pacman_state.normal_state * 2 +
            (ushort)CARRY2(pacman_state.normal_state._2_2_,pacman_state.normal_state._2_2_);
    if (CARRY2((ushort)pacman_state.normal_state,(ushort)pacman_state.normal_state) == false) {
      pacman_state.normal_state._0_2_ = uVar7;
      pacman_state.normal_state._2_2_ = uVar1;
      return;
    }
    pacman_state.normal_state._2_1_ = (char)uVar1;
    pacman_state.normal_state._2_2_ =
         uVar1 & 0xff00 | (ushort)(byte)(pacman_state.normal_state._2_1_ + 1);
    pacman_state.normal_state._0_2_ = uVar7;
  }
  else {
    uVar1 = pacman_state.big_pill_state._2_2_ * 2;
                    // movement when power pill active
                    // 
    uVar7 = (ushort)pacman_state.big_pill_state * 2 +
            (ushort)CARRY2(pacman_state.big_pill_state._2_2_,pacman_state.big_pill_state._2_2_);
    if (CARRY2((ushort)pacman_state.big_pill_state,(ushort)pacman_state.big_pill_state) == false) {
      pacman_state.big_pill_state._0_2_ = uVar7;
      pacman_state.big_pill_state._2_2_ = uVar1;
      return;
    }
    pacman_state.big_pill_state._2_1_ = (char)uVar1;
    pacman_state.big_pill_state._2_2_ =
         uVar1 & 0xff00 | (ushort)(byte)(pacman_state.big_pill_state._2_1_ + 1);
    pacman_state.big_pill_state._0_2_ = uVar7;
  }
                    // all pacman movement
                    // 
  related_to_number_of_pills_eaten_before_last_pacman_move = dots_eaten;
  if ((pacman_position_tile_position.x < 0x21) || (0x3a < pacman_position_tile_position.x)) {
                    // this sub is only called while player is in a tunnel
                    // 
    pacman_about_to_enter_a_tunnel = true;
    if ((game_mode == DEMO) || (0xf < subroutine_PLAYING_state)) goto LAB_ram_1a19;
    iVar3 = hardware_IN0;
    if ((current_player_number & cocktail_mode) != 0) {
      iVar3 = (in0_t)hardware_IN1;
                    // check player 1 or player 2 input
                    // the program jumps to one of two locations to check
                    // player input based on whether it's player 1 or player 2 currently playing,
                    // and cocktail mode is enabled
                    // if player 2 is playing and cocktail mode enabled, 187b will fall through to
                    // 187d.
                    // if player 1 is playing or cocktail mode is disabled, 187b will jump to 1883
                    // 
    }
    if (((byte)iVar3 & 2) == 0) {
      pacman_orientation = left;
      pacman_XY_tile_changes_AB = move_left;
    }
    else {
      if (((byte)iVar3 & 4) == 0) {
        pacman_orientation = right;
        pacman_XY_tile_changes_AB = move_right;
      }
    }
  }
  else {
                    // arrive here via #1861, this handles normal (not tunnel) movement
                    // 
    if ((game_mode == DEMO) || (0xf < subroutine_PLAYING_state)) {
LAB_ram_1a19:
                    // arrive here from #18b0 when game is in demo mode
                    // 
      if (pacman_XY_tile_changes_AB.y == 0) {
      }
      else {
        pacman_coord.x = pacman_coord.y;
      }
      if ((pacman_coord.x & 7) == 4) {
        bVar4 = 0;
        is_sprite_using_tunnel(5);
        if (!(bool)(bVar4 & 1)) {
                    // WARNING: Return address prevents inlining here
          insert_task(&task_pacman_AI_movement_when_demo);
        }
        pacman_tile_pos_in_demo_and_cut_scenes =
             update_coord(&pacman_tile_pos_in_demo_and_cut_scenes,&wanted_pacman_tile_changes);
        pacman_XY_tile_changes_AB = wanted_pacman_tile_changes;
        pacman_orientation = wanted_pacman_orientation;
      }
      pacman_coord = update_coord(&pacman_coord,&pacman_XY_tile_changes_AB);
      goto LAB_ram_1985;
    }
    iVar3 = hardware_IN0;
    if ((current_player_number & cocktail_mode) != 0) {
      iVar3 = (in0_t)hardware_IN1;
                    // p1/p2 check.  see 187b above for info.
                    // p2 movement check
                    // 
    }
    if (((byte)iVar3 & 2) == 0) {
                    // Player move Left
                    // 
      wanted_pacman_orientation = left;
      wanted_pacman_tile_changes = move_left;
      cVar6 = '\0';
    }
    else {
      if (((byte)iVar3 & 4) == 0) {
                    // player move Right
                    // 
        wanted_pacman_orientation = right;
        wanted_pacman_tile_changes = move_right;
        cVar6 = '\0';
      }
      else {
        if (((byte)iVar3 & 1) == 0) {
                    // player move Up
                    // 
          wanted_pacman_orientation = up;
          wanted_pacman_tile_changes = move_up;
          cVar6 = '\0';
        }
        else {
          if (((byte)iVar3 & 8) == 0) {
                    // player move Down
                    // 
            wanted_pacman_tile_changes = move_down;
            wanted_pacman_orientation = down;
            cVar6 = '\0';
          }
          else {
                    // no change in movement - joystick is centered
                    // 
            wanted_pacman_tile_changes = pacman_XY_tile_changes_AB;
            cVar6 = '\x01';
          }
        }
      }
    }
                    // movement checks return to here
                    // 
    sprite_location = &pacman_position_tile_position;
    bVar4 = get_from_screen_position(&pacman_position_tile_position,&wanted_pacman_tile_changes);
    if ((bVar4 & 0xc0) == 0xc0) {
      cVar6 = cVar6 + -1;
      if (cVar6 != '\0') {
        bVar4 = get_from_screen_position(sprite_location,&pacman_XY_tile_changes_AB);
        if ((bVar4 & 0xc0) == 0xc0) {
                    // code seems to be why pacman turns corners fast.  it gives an extra boost to
                    // the new direction
                    // 
          if ((bool)(pacman_orientation & 1)) {
            if ((pacman_coord.y & 7) == 4) {
              return;
            }
          }
          else {
            if ((pacman_coord.x & 7) == 4) {
              return;
            }
          }
        }
        goto LAB_ram_1950;
      }
      if ((bool)(pacman_orientation & 1)) {
        if ((pacman_coord.y & 7) == 4) {
          return;
        }
      }
      else {
        if ((pacman_coord.x & 7) == 4) {
          return;
        }
      }
    }
                    // arrive when changing direction (???)
                    // 
    pacman_XY_tile_changes_AB = wanted_pacman_tile_changes;
    if (cVar6 != '\x01') {
      pacman_orientation = wanted_pacman_orientation;
    }
  }
LAB_ram_1950:
  pacman_coord = update_coord(&pacman_coord,&pacman_XY_tile_changes_AB);
  bVar4 = SUB21(pacman_coord,0);
  bVar5 = (byte)((ushort)pacman_coord >> 8);
  if ((bool)(pacman_orientation & 1)) {
                    // handle up/down movement turns
                    // 
    if ((bVar5 & 7) != 4) {
      if ((bVar5 & 7) < 4) {
                    // arrive here when cornering up from the right side
                    // or when cornering down from the right side
                    // 
        pacman_coord = (sprite_coord_yx_t)
                       ((ushort)pacman_coord & 0xff | (ushort)(byte)(bVar5 + 1) << 8);
      }
      else {
                    // cornering up from the left side, or down from the left side
                    // 
        pacman_coord = (sprite_coord_yx_t)
                       ((ushort)pacman_coord & 0xff | (ushort)(byte)(bVar5 - 1) << 8);
      }
    }
  }
  else {
    if ((bVar4 & 7) != 4) {
      if ((bVar4 & 7) < 4) {
                    // cornering right from down , cornering left from down
                    // 
        pacman_coord = (sprite_coord_yx_t)
                       ((ushort)pacman_coord & 0xff00 | (ushort)(byte)(bVar4 + 1));
      }
      else {
                    // cornering up to the left or up to the right
                    // 
        pacman_coord = (sprite_coord_yx_t)
                       ((ushort)pacman_coord & 0xff00 | (ushort)(byte)(bVar4 - 1));
      }
    }
  }
LAB_ram_1985:
                    // arrive here from several locations
                    // HL has the expected new position of a sprite
                    // 
  pacman_position_tile_position = convert_sprite_position_to_tile_position(pacman_coord);
  bVar2 = pacman_about_to_enter_a_tunnel;
  pacman_about_to_enter_a_tunnel = false;
  if (bVar2 != false) {
    pacman_about_to_enter_a_tunnel = false;
    return;
  }
                    // check for items eaten
                    // 
  if ((((fruit_coord.y != 0) && (fruit_points != 0)) &&
      ((byte)(((char)((ushort)pacman_coord >> 8) - (char)((ushort)fruit_coord >> 8)) + 3U) < 6
                    // check for fruit being eaten ... jumped from #19AD
                    // HL has pacman X,Y
                    // )) && ((byte)((SUB21(pacman_coord,0) - fruit_coord.y) + 3) < 6)) {
                    // else a fruit is being eaten
                    // 
    fruit_sprite.color = red;
    fruit_sprite._0_1_ = fruit_points + 2;
                    // arrive here when fruit is eaten
                    // 
    add_to_task_list(update_score_then_draw,fruit_points);
    TT04_clear_fruit_points();
                    // WARNING: Return address prevents inlining here
    add_timed_task(&task_clear_fruit_position);
    channel_3_effect.num = channel_3_effect.num | 4;
  }
                    // arrive here when no fruit eaten from fruit eating check subroutine
                    // 
  delay_pacman_movement = PACMAN_NOT_EATING;
  pbVar8 = convert_xy_to_screen_position(pacman_position_tile_position);
  bVar4 = *pbVar8;
  if ((bVar4 != 0x10) && (bVar4 != 0x14)) {
    return;
  }
                    // arrive here when a dot or energizer has been eaten
                    // A has either #10 or #14 loaded
                    // 
  dots_eaten = dots_eaten + 1;
  bVar5 = (bVar4 & 0xf) >> 1;
  *pbVar8 = 0x40;
  add_to_task_list(update_score_then_draw,(bVar4 & 0xf) >> 2);
                    // task #19 will update score.  B has code for items scored, draw score on
                    // screen, check for high score and extra lives
                    // 
  delay_pacman_movement = bVar5 + PACMAN_EATING_PILL;
  if (delay_pacman_movement != PACMAN_EATING_PILL) {
    delay_pacman_movement = delay_pacman_movement * '\x02';
  }
  update_timers_for_ghosts_to_leave_ghost_house(delay_pacman_movement);
  can_pacman_eat_big_pill();
  if (!(bool)(dots_eaten & 1)) {
    channel_3_effect.num = channel_3_effect.num & 0xfd | 1;
    return;
  }
  channel_3_effect.num = channel_3_effect.num & 0xfe | 2;
  return;
}



void can_pacman_eat_big_pill(void)

{
                    // called from #1A03 after a dot has been eaten
                    // 
  if (delay_pacman_movement != PACMAN_EATING_BIG_PILL) {
    return;
  }
  red_ghost_sprite._0_1_ = 0x1c;
  red_ghost_sprite.color = 0x11;
  pink_ghost_sprite._0_1_ = 0x1c;
  pink_ghost_sprite.color = 0x11;
  blue_sprite._0_1_ = 0x1c;
  blue_sprite.color = 0x11;
  orange_ghost_sprite._0_1_ = 0x1c;
  orange_ghost_sprite.color = 0x11;
  power_pill_effect = true;
  red_ghost_blue_flag = true;
  pink_ghost_blue_flag = true;
  blue_ghost_blue_flag = true;
  orange_ghost_blue_flag = true;
  red_ghost_change_orientation_flag = true;
  pink_ghost_change_orientation_flag = true;
  blue_ghost_change_orientation_flag = true;
  orange_ghost_change_orientation_flag = true;
  pacman_change_orientation_flag = true;
  counter__used_to_change_ghost_colors_under_big_pill_effects = 0;
  counter_while_ghosts_are_blue = time_the_ghosts_stay_blue_when_pacman_eats_a_big_pill;
  counter__current_number_of_killed_ghosts = 0;
  channel_2_effect.num = channel_2_effect.num & 0x7f | 0x20;
  return;
}



void pacman_eat_big_pill(void)

{
                    // else an engergizer has been eaten
                    // this is also called even on boards where energizers have "no effect"
                    // ;
                    // Patch to fix the green-eye bug
                    // by Don Hodges 1/19/2009
                    // part 1/2 (rest at #1FB0):
                    // jump to new sub to only color ghosts when enough time
                    // 
  red_ghost_sprite._0_1_ = 0x1c;
  red_ghost_sprite.color = 0x11;
  pink_ghost_sprite._0_1_ = 0x1c;
  pink_ghost_sprite.color = 0x11;
  blue_sprite._0_1_ = 0x1c;
  blue_sprite.color = 0x11;
  orange_ghost_sprite._0_1_ = 0x1c;
  orange_ghost_sprite.color = 0x11;
  power_pill_effect = true;
  red_ghost_blue_flag = true;
  pink_ghost_blue_flag = true;
  blue_ghost_blue_flag = true;
  orange_ghost_blue_flag = true;
  red_ghost_change_orientation_flag = true;
  pink_ghost_change_orientation_flag = true;
  blue_ghost_change_orientation_flag = true;
  orange_ghost_change_orientation_flag = true;
  pacman_change_orientation_flag = true;
  counter__used_to_change_ghost_colors_under_big_pill_effects = 0;
  counter_while_ghosts_are_blue = time_the_ghosts_stay_blue_when_pacman_eats_a_big_pill;
  counter__current_number_of_killed_ghosts = 0;
  channel_2_effect.num = channel_2_effect.num & 0x7f | 0x20;
  return;
}



void update_timers_for_ghosts_to_leave_ghost_house(void)

{
                    // called from #1A00
                    // 
  if (dying_in_a_level != false) {
    eaten_pills_counter_after_pacman_has_died_in_a_level =
         eaten_pills_counter_after_pacman_has_died_in_a_level + 1;
    return;
  }
  if (orange_ghost_substate_if_alive != AT_HOME) {
    return;
  }
  if (blue_ghost_substate_if_alive != AT_HOME) {
    can_orange_ghost_leave_home = can_orange_ghost_leave_home + 1;
    return;
  }
  if (pink_ghost_substate_if_alive != AT_HOME) {
    can_blue_ghost_leave_home = can_blue_ghost_leave_home + 1;
    return;
  }
  can_pink_ghost_leave_home = can_pink_ghost_leave_home + 1;
  return;
}



void control_movement_red_ghost(void)

{
  ushort uVar1;
  byte bVar2;
  short sVar3;
  sprite_coord_yx_t sVar4;
  
                    // called from several locations
                    // 
  if (red_ghost_substate_if_alive == AT_HOME) {
    return;
  }
  if (red_ghost_state != ALIVE) {
    return;
  }
  check_and_set_difficulty_flags();
  check_ghost_entering_tunnel_slowdown(red_ghost_tile_position_2,&delay_red_ghost_movement);
  if (delay_red_ghost_movement != 0) {
    uVar1 = red_ghost_state.specific_state._2_2_ * 2;
    sVar3 = (ushort)red_ghost_state.specific_state * 2 +
            (ushort)CARRY2(red_ghost_state.specific_state._2_2_,red_ghost_state.specific_state._2_2_
                          );
    if (CARRY2((ushort)red_ghost_state.specific_state,(ushort)red_ghost_state.specific_state) ==
        false) {
      red_ghost_state.specific_state._0_2_ = sVar3;
      red_ghost_state.specific_state._2_2_ = uVar1;
      return;
    }
    red_ghost_state.specific_state._2_1_ = (char)uVar1;
    red_ghost_state.specific_state._2_2_ =
         uVar1 & 0xff00 | (ushort)(byte)(red_ghost_state.specific_state._2_1_ + 1);
    red_ghost_state.specific_state._0_2_ = sVar3;
    handles_red_ghost_movement();
    return;
  }
  if (red_ghost_blue_flag == false) {
    if (red_ghost_second_difficulty_flag != false) {
      uVar1 = pacman_state.second_difficulty_flag._2_2_ * 2;
      sVar3 = (ushort)pacman_state.second_difficulty_flag * 2 +
              (ushort)CARRY2(pacman_state.second_difficulty_flag._2_2_,
                             pacman_state.second_difficulty_flag._2_2_);
      if (CARRY2((ushort)pacman_state.second_difficulty_flag,
                 (ushort)pacman_state.second_difficulty_flag) == false) {
        pacman_state.second_difficulty_flag._0_2_ = sVar3;
        pacman_state.second_difficulty_flag._2_2_ = uVar1;
        return;
      }
      pacman_state.second_difficulty_flag._2_1_ = (char)uVar1;
      pacman_state.second_difficulty_flag._2_2_ =
           uVar1 & 0xff00 | (ushort)(byte)(pacman_state.second_difficulty_flag._2_1_ + 1);
      pacman_state.second_difficulty_flag._0_2_ = sVar3;
      handles_red_ghost_movement();
      return;
    }
    if (red_ghost_first_difficulty_flag == false) {
      uVar1 = red_ghost_state.normal_state._2_2_ * 2;
      sVar3 = (ushort)red_ghost_state.normal_state * 2 +
              (ushort)CARRY2(red_ghost_state.normal_state._2_2_,red_ghost_state.normal_state._2_2_);
      if (CARRY2((ushort)red_ghost_state.normal_state,(ushort)red_ghost_state.normal_state) != false
         ) {
        red_ghost_state.normal_state._2_1_ = (char)uVar1;
        red_ghost_state.normal_state._2_2_ =
             uVar1 & 0xff00 | (ushort)(byte)(red_ghost_state.normal_state._2_1_ + 1);
        if (red_ghost_Y_tile_changes_A.y == left_right) {
        }
        else {
          red_ghost_coord.x = red_ghost_coord.y;
        }
        red_ghost_state.normal_state._0_2_ = sVar3;
        if ((red_ghost_coord.x & 7) == 4) {
          bVar2 = 0;
          is_sprite_using_tunnel(1);
          if (!(bool)(bVar2 & 1)) {
            if (red_ghost_blue_flag == false) {
              sVar4 = convert_xy_to_color_screen_position(red_ghost_xy_tile_pos);
              if (*(char *)sVar4 != '\x1a') {
                    // WARNING: Return address prevents inlining here
                insert_task(&task_red_ghost_AI);
              }
            }
            else {
                    // WARNING: Return address prevents inlining here
              insert_task(&task_red_ghost_movement_when_power_pill);
            }
          }
          is_reverse_red_ghost_direction_time();
          red_ghost_xy_tile_pos = update_coord(&red_ghost_xy_tile_pos,&red_ghost_xy_tile_changes);
          red_ghost_Y_tile_changes_A = red_ghost_xy_tile_changes;
          red_ghost_previous_orientation = red_ghost_orientation;
        }
        red_ghost_coord =
             update_coord(&red_ghost_coord,(sprite_coord_yx_t *)&red_ghost_Y_tile_changes_A);
        red_ghost_tile_position_2 = convert_sprite_position_to_tile_position(red_ghost_coord);
        return;
      }
      red_ghost_state.normal_state._0_2_ = sVar3;
      red_ghost_state.normal_state._2_2_ = uVar1;
      return;
    }
    uVar1 = pacman_state.first_difficulty_flag._2_2_ * 2;
    sVar3 = (ushort)pacman_state.first_difficulty_flag * 2 +
            (ushort)CARRY2(pacman_state.first_difficulty_flag._2_2_,
                           pacman_state.first_difficulty_flag._2_2_);
    if (CARRY2((ushort)pacman_state.first_difficulty_flag,(ushort)pacman_state.first_difficulty_flag
              ) == false) {
      pacman_state.first_difficulty_flag._0_2_ = sVar3;
      pacman_state.first_difficulty_flag._2_2_ = uVar1;
      return;
    }
    pacman_state.first_difficulty_flag._2_1_ = (char)uVar1;
    pacman_state.first_difficulty_flag._2_2_ =
         uVar1 & 0xff00 | (ushort)(byte)(pacman_state.first_difficulty_flag._2_1_ + 1);
    pacman_state.first_difficulty_flag._0_2_ = sVar3;
    handles_red_ghost_movement();
    return;
  }
  uVar1 = red_ghost_state.speed_state._2_2_ * 2;
  sVar3 = (ushort)red_ghost_state.speed_state * 2 +
          (ushort)CARRY2(red_ghost_state.speed_state._2_2_,red_ghost_state.speed_state._2_2_);
  if (CARRY2((ushort)red_ghost_state.speed_state,(ushort)red_ghost_state.speed_state) == false) {
    red_ghost_state.speed_state._0_2_ = sVar3;
    red_ghost_state.speed_state._2_2_ = uVar1;
    return;
  }
  red_ghost_state.speed_state._2_1_ = (char)uVar1;
  red_ghost_state.speed_state._2_2_ =
       uVar1 & 0xff00 | (ushort)(byte)(red_ghost_state.speed_state._2_1_ + 1);
  red_ghost_state.speed_state._0_2_ = sVar3;
  handles_red_ghost_movement();
  return;
}



void handles_red_ghost_movement(void)

{
  byte bVar1;
  sprite_coord_yx_t sVar2;
  
                    // called from #10C0 and several other places
                    // handles red ghost movement
                    // 
  if (red_ghost_Y_tile_changes_A.y == left_right) {
  }
  else {
    red_ghost_coord.x = red_ghost_coord.y;
  }
  if ((red_ghost_coord.x & 7) == 4) {
    bVar1 = 0;
    is_sprite_using_tunnel(1);
    if (!(bool)(bVar1 & 1)) {
      if (red_ghost_blue_flag == false) {
        sVar2 = convert_xy_to_color_screen_position(red_ghost_xy_tile_pos);
        if (*(char *)sVar2 != '\x1a') {
                    // WARNING: Return address prevents inlining here
          insert_task(&task_red_ghost_AI);
        }
      }
      else {
                    // WARNING: Return address prevents inlining here
        insert_task(&task_red_ghost_movement_when_power_pill);
      }
    }
    is_reverse_red_ghost_direction_time();
    red_ghost_xy_tile_pos = update_coord(&red_ghost_xy_tile_pos,&red_ghost_xy_tile_changes);
    red_ghost_Y_tile_changes_A = red_ghost_xy_tile_changes;
    red_ghost_previous_orientation = red_ghost_orientation;
  }
  red_ghost_coord = update_coord(&red_ghost_coord,(sprite_coord_yx_t *)&red_ghost_Y_tile_changes_A);
  red_ghost_tile_position_2 = convert_sprite_position_to_tile_position(red_ghost_coord);
  return;
}



void control_movement_pink_ghost(void)

{
  ushort uVar1;
  byte bVar2;
  short sVar3;
  sprite_coord_yx_t sVar4;
  
                    // control movement patterns for pink ghost
                    // called from #104A
                    // 
  if (pink_ghost_substate_if_alive != GOING_FOR_PACMAN) {
    return;
  }
  if (pink_ghost_state != ALIVE) {
    return;
  }
  check_ghost_entering_tunnel_slowdown(pink_ghost_tile_position_2,&delay_pink_ghost_movement);
  if (delay_pink_ghost_movement != 0) {
    uVar1 = pink_ghost_state.specific_state._2_2_ * 2;
    sVar3 = (ushort)pink_ghost_state.specific_state * 2 +
            (ushort)CARRY2(pink_ghost_state.specific_state._2_2_,
                           pink_ghost_state.specific_state._2_2_);
    if (CARRY2((ushort)pink_ghost_state.specific_state,(ushort)pink_ghost_state.specific_state) ==
        false) {
      pink_ghost_state.specific_state._0_2_ = sVar3;
      pink_ghost_state.specific_state._2_2_ = uVar1;
      return;
    }
    pink_ghost_state.specific_state._2_1_ = (char)uVar1;
    pink_ghost_state.specific_state._2_2_ =
         uVar1 & 0xff00 | (ushort)(byte)(pink_ghost_state.specific_state._2_1_ + 1);
    pink_ghost_state.specific_state._0_2_ = sVar3;
    handles_pink_ghost_movement();
    return;
  }
  if (pink_ghost_blue_flag == false) {
    uVar1 = pink_ghost_state.normal_state._2_2_ * 2;
    sVar3 = (ushort)pink_ghost_state.normal_state * 2 +
            (ushort)CARRY2(pink_ghost_state.normal_state._2_2_,pink_ghost_state.normal_state._2_2_);
    if (CARRY2((ushort)pink_ghost_state.normal_state,(ushort)pink_ghost_state.normal_state) != false
       ) {
      pink_ghost_state.normal_state._2_1_ = (char)uVar1;
      pink_ghost_state.normal_state._2_2_ =
           uVar1 & 0xff00 | (ushort)(byte)(pink_ghost_state.normal_state._2_1_ + 1);
      if (pink_ghost_Y_tile_changes_A.y == left_right) {
      }
      else {
        pink_ghost_coord.x = pink_ghost_coord.y;
      }
      pink_ghost_state.normal_state._0_2_ = sVar3;
      if ((pink_ghost_coord.x & 7) == 4) {
        bVar2 = 0;
        is_sprite_using_tunnel(2);
        if (!(bool)(bVar2 & 1)) {
          if (pink_ghost_blue_flag == false) {
            sVar4 = convert_xy_to_color_screen_position(pink_ghost_xy_tile_pos);
            if (*(char *)sVar4 != '\x1a') {
                    // WARNING: Return address prevents inlining here
              insert_task(&task_pink_ghost_AI);
            }
          }
          else {
                    // WARNING: Return address prevents inlining here
            insert_task(&task_pink_movement_when_power_pill);
          }
        }
        is_reverse_pink_ghost_direction_time();
        pink_ghost_xy_tile_pos = update_coord(&pink_ghost_xy_tile_pos,&pink_ghost_xy_tile_changes);
        pink_ghost_Y_tile_changes_A = pink_ghost_xy_tile_changes;
        pink_ghost_previous_orientation = pink_ghost_orientation;
      }
      pink_ghost_coord =
           update_coord(&pink_ghost_coord,(sprite_coord_yx_t *)&pink_ghost_Y_tile_changes_A);
      pink_ghost_tile_position_2 = convert_sprite_position_to_tile_position(pink_ghost_coord);
      return;
    }
    pink_ghost_state.normal_state._0_2_ = sVar3;
    pink_ghost_state.normal_state._2_2_ = uVar1;
    return;
  }
  uVar1 = pink_ghost_state.speed_state._2_2_ * 2;
  sVar3 = (ushort)pink_ghost_state.speed_state * 2 +
          (ushort)CARRY2(pink_ghost_state.speed_state._2_2_,pink_ghost_state.speed_state._2_2_);
  if (CARRY2((ushort)pink_ghost_state.speed_state,(ushort)pink_ghost_state.speed_state) == false) {
    pink_ghost_state.speed_state._0_2_ = sVar3;
    pink_ghost_state.speed_state._2_2_ = uVar1;
    return;
  }
  pink_ghost_state.speed_state._2_1_ = (char)uVar1;
  pink_ghost_state.speed_state._2_2_ =
       uVar1 & 0xff00 | (ushort)(byte)(pink_ghost_state.speed_state._2_1_ + 1);
  pink_ghost_state.speed_state._0_2_ = sVar3;
  handles_pink_ghost_movement();
  return;
}



void handles_pink_ghost_movement(void)

{
  byte bVar1;
  sprite_coord_yx_t sVar2;
  
  if (pink_ghost_Y_tile_changes_A.y == left_right) {
  }
  else {
    pink_ghost_coord.x = pink_ghost_coord.y;
  }
  if ((pink_ghost_coord.x & 7) == 4) {
    bVar1 = 0;
    is_sprite_using_tunnel(2);
    if (!(bool)(bVar1 & 1)) {
      if (pink_ghost_blue_flag == false) {
        sVar2 = convert_xy_to_color_screen_position(pink_ghost_xy_tile_pos);
        if (*(char *)sVar2 != '\x1a') {
                    // WARNING: Return address prevents inlining here
          insert_task(&task_pink_ghost_AI);
        }
      }
      else {
                    // WARNING: Return address prevents inlining here
        insert_task(&task_pink_movement_when_power_pill);
      }
    }
    is_reverse_pink_ghost_direction_time();
    pink_ghost_xy_tile_pos = update_coord(&pink_ghost_xy_tile_pos,&pink_ghost_xy_tile_changes);
    pink_ghost_Y_tile_changes_A = pink_ghost_xy_tile_changes;
    pink_ghost_previous_orientation = pink_ghost_orientation;
  }
  pink_ghost_coord =
       update_coord(&pink_ghost_coord,(sprite_coord_yx_t *)&pink_ghost_Y_tile_changes_A);
  pink_ghost_tile_position_2 = convert_sprite_position_to_tile_position(pink_ghost_coord);
  return;
}



void control_movement_blue_ghost(void)

{
  ushort uVar1;
  byte bVar2;
  short sVar3;
  sprite_coord_yx_t sVar4;
  
                    // check movement patterns for inky
                    // called from #104D
                    // 
  if (blue_ghost_substate_if_alive != GOING_FOR_PACMAN) {
    return;
  }
  if (blue_ghost_state != ALIVE) {
    return;
  }
  check_ghost_entering_tunnel_slowdown(blue_ghost_tile_position_2,&delay_blue_ghost_movement);
  if (delay_blue_ghost_movement != 0) {
    uVar1 = blue_ghost_state.specific_state._2_2_ * 2;
    sVar3 = (ushort)blue_ghost_state.specific_state * 2 +
            (ushort)CARRY2(blue_ghost_state.specific_state._2_2_,
                           blue_ghost_state.specific_state._2_2_);
    if (CARRY2((ushort)blue_ghost_state.specific_state,(ushort)blue_ghost_state.specific_state) ==
        false) {
      blue_ghost_state.specific_state._0_2_ = sVar3;
      blue_ghost_state.specific_state._2_2_ = uVar1;
      return;
    }
    blue_ghost_state.specific_state._2_1_ = (char)uVar1;
    blue_ghost_state.specific_state._2_2_ =
         uVar1 & 0xff00 | (ushort)(byte)(blue_ghost_state.specific_state._2_1_ + 1);
    blue_ghost_state.specific_state._0_2_ = sVar3;
    handles_blue_ghost_movement();
    return;
  }
  if (blue_ghost_blue_flag == false) {
    uVar1 = blue_ghost_state.normal_state._2_2_ * 2;
    sVar3 = (ushort)blue_ghost_state.normal_state * 2 +
            (ushort)CARRY2(blue_ghost_state.normal_state._2_2_,blue_ghost_state.normal_state._2_2_);
    if (CARRY2((ushort)blue_ghost_state.normal_state,(ushort)blue_ghost_state.normal_state) != false
       ) {
      blue_ghost_state.normal_state._2_1_ = (char)uVar1;
      blue_ghost_state.normal_state._2_2_ =
           uVar1 & 0xff00 | (ushort)(byte)(blue_ghost_state.normal_state._2_1_ + 1);
      if (blue_ghost_Y_tile_changes_A.y == left_right) {
      }
      else {
        blue_ghost_coord.x = blue_ghost_coord.y;
      }
      blue_ghost_state.normal_state._0_2_ = sVar3;
      if ((blue_ghost_coord.x & 7) == 4) {
        bVar2 = 0;
        is_sprite_using_tunnel(3);
        if (!(bool)(bVar2 & 1)) {
          if (blue_ghost_blue_flag == false) {
            sVar4 = convert_xy_to_color_screen_position(blue_ghost_xy_tile_pos);
            if (*(char *)sVar4 != '\x1a') {
                    // WARNING: Return address prevents inlining here
              insert_task(&task_blue_ghost_AI);
            }
          }
          else {
                    // WARNING: Return address prevents inlining here
            insert_task(&task_blue_ghost_movement_when_power_pill);
          }
        }
        is_reverse_blue_ghost_direction_time();
        blue_ghost_xy_tile_pos = update_coord(&blue_ghost_xy_tile_pos,&blue_ghost_xy_tile_changes);
        blue_ghost_Y_tile_changes_A = blue_ghost_xy_tile_changes;
        blue_ghost_previous_orientation = blue_ghost_orientation;
      }
      blue_ghost_coord =
           update_coord(&blue_ghost_coord,(sprite_coord_yx_t *)&blue_ghost_Y_tile_changes_A);
      blue_ghost_tile_position_2 = convert_sprite_position_to_tile_position(blue_ghost_coord);
      return;
    }
    blue_ghost_state.normal_state._0_2_ = sVar3;
    blue_ghost_state.normal_state._2_2_ = uVar1;
    return;
  }
  uVar1 = blue_ghost_state.speed_state._2_2_ * 2;
  sVar3 = (ushort)blue_ghost_state.speed_state * 2 +
          (ushort)CARRY2(blue_ghost_state.speed_state._2_2_,blue_ghost_state.speed_state._2_2_);
  if (CARRY2((ushort)blue_ghost_state.speed_state,(ushort)blue_ghost_state.speed_state) == false) {
    blue_ghost_state.speed_state._0_2_ = sVar3;
    blue_ghost_state.speed_state._2_2_ = uVar1;
    return;
  }
  blue_ghost_state.speed_state._2_1_ = (char)uVar1;
  blue_ghost_state.speed_state._2_2_ =
       uVar1 & 0xff00 | (ushort)(byte)(blue_ghost_state.speed_state._2_1_ + 1);
  blue_ghost_state.speed_state._0_2_ = sVar3;
  handles_blue_ghost_movement();
  return;
}



void handles_blue_ghost_movement(void)

{
  byte bVar1;
  sprite_coord_yx_t sVar2;
  
  if (blue_ghost_Y_tile_changes_A.y == left_right) {
  }
  else {
    blue_ghost_coord.x = blue_ghost_coord.y;
  }
  if ((blue_ghost_coord.x & 7) == 4) {
    bVar1 = 0;
    is_sprite_using_tunnel(3);
    if (!(bool)(bVar1 & 1)) {
      if (blue_ghost_blue_flag == false) {
        sVar2 = convert_xy_to_color_screen_position(blue_ghost_xy_tile_pos);
        if (*(char *)sVar2 != '\x1a') {
                    // WARNING: Return address prevents inlining here
          insert_task(&task_blue_ghost_AI);
        }
      }
      else {
                    // WARNING: Return address prevents inlining here
        insert_task(&task_blue_ghost_movement_when_power_pill);
      }
    }
    is_reverse_blue_ghost_direction_time();
    blue_ghost_xy_tile_pos = update_coord(&blue_ghost_xy_tile_pos,&blue_ghost_xy_tile_changes);
    blue_ghost_Y_tile_changes_A = blue_ghost_xy_tile_changes;
    blue_ghost_previous_orientation = blue_ghost_orientation;
  }
  blue_ghost_coord =
       update_coord(&blue_ghost_coord,(sprite_coord_yx_t *)&blue_ghost_Y_tile_changes_A);
  blue_ghost_tile_position_2 = convert_sprite_position_to_tile_position(blue_ghost_coord);
  return;
}



void control_movement_orange_ghost(void)

{
  ushort uVar1;
  byte bVar2;
  short sVar3;
  sprite_coord_yx_t sVar4;
  
                    // control movement patterns for orange ghost
                    // called from #1050
                    // 
  if (orange_ghost_substate_if_alive != GOING_FOR_PACMAN) {
    return;
  }
  if (orange_ghost_state != ALIVE) {
    return;
  }
  check_ghost_entering_tunnel_slowdown(orange_ghost_tile_position_2,&delay_orange_ghost_movement);
  if (delay_orange_ghost_movement != 0) {
    uVar1 = orange_ghost_state.specific_state._2_2_ * 2;
    sVar3 = (ushort)orange_ghost_state.specific_state * 2 +
            (ushort)CARRY2(orange_ghost_state.specific_state._2_2_,
                           orange_ghost_state.specific_state._2_2_);
    if (CARRY2((ushort)orange_ghost_state.specific_state,(ushort)orange_ghost_state.specific_state)
        == false) {
      orange_ghost_state.specific_state._0_2_ = sVar3;
      orange_ghost_state.specific_state._2_2_ = uVar1;
      return;
    }
    orange_ghost_state.specific_state._2_1_ = (char)uVar1;
    orange_ghost_state.specific_state._2_2_ =
         uVar1 & 0xff00 | (ushort)(byte)(orange_ghost_state.specific_state._2_1_ + 1);
    orange_ghost_state.specific_state._0_2_ = sVar3;
    handles_orange_ghost_movement();
    return;
  }
  if (orange_ghost_blue_flag == false) {
    uVar1 = orange_ghost_state.normal_state._2_2_ * 2;
    sVar3 = (ushort)orange_ghost_state.normal_state * 2 +
            (ushort)CARRY2(orange_ghost_state.normal_state._2_2_,
                           orange_ghost_state.normal_state._2_2_);
    if (CARRY2((ushort)orange_ghost_state.normal_state,(ushort)orange_ghost_state.normal_state) !=
        false) {
      orange_ghost_state.normal_state._2_1_ = (char)uVar1;
      orange_ghost_state.normal_state._2_2_ =
           uVar1 & 0xff00 | (ushort)(byte)(orange_ghost_state.normal_state._2_1_ + 1);
      if (orange_ghost_Y_tile_change_A.y == left_right) {
      }
      else {
        orange_ghost_coord.x = orange_ghost_coord.y;
      }
      orange_ghost_state.normal_state._0_2_ = sVar3;
      if ((orange_ghost_coord.x & 7) == 4) {
        bVar2 = 0;
        is_sprite_using_tunnel(4);
        if (!(bool)(bVar2 & 1)) {
          if (orange_ghost_blue_flag == false) {
            sVar4 = convert_xy_to_color_screen_position(orange_ghost_xy_tile_pos);
            if (*(char *)sVar4 != '\x1a') {
                    // WARNING: Return address prevents inlining here
              insert_task(&task_orange_ghost_AI);
            }
          }
          else {
                    // WARNING: Return address prevents inlining here
            insert_task(&task_orange_ghost_movement_when_power_pill);
          }
        }
        is_reverse_orange_ghost_direction_time();
        orange_ghost_xy_tile_pos =
             update_coord(&orange_ghost_xy_tile_pos,&orange_ghost_xy_tile_changes);
        orange_ghost_Y_tile_change_A = orange_ghost_xy_tile_changes;
        orange_ghost_previous_orientation = orange_ghost_orientation;
      }
      orange_ghost_coord =
           update_coord(&orange_ghost_coord,(sprite_coord_yx_t *)&orange_ghost_Y_tile_change_A);
      orange_ghost_tile_position_2 = convert_sprite_position_to_tile_position(orange_ghost_coord);
      return;
    }
    orange_ghost_state.normal_state._0_2_ = sVar3;
    orange_ghost_state.normal_state._2_2_ = uVar1;
    return;
  }
  uVar1 = orange_ghost_state.speed_state._2_2_ * 2;
  sVar3 = (ushort)orange_ghost_state.speed_state * 2 +
          (ushort)CARRY2(orange_ghost_state.speed_state._2_2_,orange_ghost_state.speed_state._2_2_);
  if (CARRY2((ushort)orange_ghost_state.speed_state,(ushort)orange_ghost_state.speed_state) == false
     ) {
    orange_ghost_state.speed_state._0_2_ = sVar3;
    orange_ghost_state.speed_state._2_2_ = uVar1;
    return;
  }
  orange_ghost_state.speed_state._2_1_ = (char)uVar1;
  orange_ghost_state.speed_state._2_2_ =
       uVar1 & 0xff00 | (ushort)(byte)(orange_ghost_state.speed_state._2_1_ + 1);
  orange_ghost_state.speed_state._0_2_ = sVar3;
  handles_orange_ghost_movement();
  return;
}



void handles_orange_ghost_movement(void)

{
  byte bVar1;
  sprite_coord_yx_t sVar2;
  
  if (orange_ghost_Y_tile_change_A.y == left_right) {
  }
  else {
    orange_ghost_coord.x = orange_ghost_coord.y;
  }
  if ((orange_ghost_coord.x & 7) == 4) {
    bVar1 = 0;
    is_sprite_using_tunnel(4);
    if (!(bool)(bVar1 & 1)) {
      if (orange_ghost_blue_flag == false) {
        sVar2 = convert_xy_to_color_screen_position(orange_ghost_xy_tile_pos);
        if (*(char *)sVar2 != '\x1a') {
                    // WARNING: Return address prevents inlining here
          insert_task(&task_orange_ghost_AI);
        }
      }
      else {
                    // WARNING: Return address prevents inlining here
        insert_task(&task_orange_ghost_movement_when_power_pill);
      }
    }
    is_reverse_orange_ghost_direction_time();
    orange_ghost_xy_tile_pos = update_coord(&orange_ghost_xy_tile_pos,&orange_ghost_xy_tile_changes)
    ;
    orange_ghost_Y_tile_change_A = orange_ghost_xy_tile_changes;
    orange_ghost_previous_orientation = orange_ghost_orientation;
  }
  orange_ghost_coord =
       update_coord(&orange_ghost_coord,(sprite_coord_yx_t *)&orange_ghost_Y_tile_change_A);
  orange_ghost_tile_position_2 = convert_sprite_position_to_tile_position(orange_ghost_coord);
  return;
}



// called from #1A3A while in demo mode
// called from #1BF9 when red ghost movement checking.
// 
// A is preloaded with #01 if the ghost/pacman is on the edge of the screen, 
// the carry flag is set, else it is cleared
// 
// is_red_ghost_using_tunnel (1)
// is_pink_ghost_using_tunnel (2)
// is_blue_ghost_using_tunnel (3)
// is_orange_ghost_using_tunnel (4)
// is_pacman_using_tunnel_in_demo (5)
// 

void is_sprite_using_tunnel(byte sprite_tile_coord_index)

{
  byte y;
  sprite_coord_yx_t *tile_coord;
  
  tile_coord = (sprite_coord_yx_t *)(&pacman_coord.x + (byte)(sprite_tile_coord_index * '\x02'));
  y = tile_coord->y;
  if (y == 0x1d) {
    tile_coord->y = 0x3d;
  }
  else {
    if (y == 0x3e) {
      tile_coord->y = 0x1e;
    }
    else {
      if ((0x20 < y) && (tile_coord->y < 0x3b)) {
        return;
      }
    }
  }
  return;
}



void is_reverse_red_ghost_direction_time(void)

{
  character_orientation_e index;
  dereference_word_t dVar1;
  
                    // check for reverse direction of red ghost
                    // 
  if (red_ghost_change_orientation_flag == false) {
    return;
  }
                    // reverse direction of red ghost
                    // 
  red_ghost_change_orientation_flag = false;
  index = red_ghost_previous_orientation ^ 2;
  red_ghost_orientation = index;
  dVar1 = dereference_pointer_to_word((word *)&move_right,index);
  red_ghost_xy_tile_changes = (undefined2)((uint5)dVar1 >> 0x18);
  if (subroutine_DEMO_state != 0x22) {
    return;
  }
  red_ghost_Y_tile_changes_A = red_ghost_xy_tile_changes;
  red_ghost_previous_orientation = index;
  return;
}



void reverse_red_ghost_direction(void)

{
  character_orientation_e index;
  dereference_word_t dVar1;
  
  index = red_ghost_previous_orientation ^ 2;
  red_ghost_orientation = index;
  dVar1 = dereference_pointer_to_word((word *)&move_right,index);
  red_ghost_xy_tile_changes = (undefined2)((uint5)dVar1 >> 0x18);
  if (subroutine_DEMO_state != 0x22) {
    return;
  }
  red_ghost_Y_tile_changes_A = red_ghost_xy_tile_changes;
  red_ghost_previous_orientation = index;
  return;
}



void is_reverse_pink_ghost_direction_time(void)

{
  character_orientation_e index;
  dereference_word_t dVar1;
  
                    // check for reverse direction of pink ghost
                    // 
  if (pink_ghost_change_orientation_flag == false) {
    return;
  }
                    // reverse direction of pink ghost
                    // 
  pink_ghost_change_orientation_flag = false;
  index = pink_ghost_previous_orientation ^ 2;
  pink_ghost_orientation = index;
  dVar1 = dereference_pointer_to_word((word *)&move_right,index);
  pink_ghost_xy_tile_changes = (undefined2)((uint5)dVar1 >> 0x18);
  if (subroutine_DEMO_state != 0x22) {
    return;
  }
  pink_ghost_Y_tile_changes_A = pink_ghost_xy_tile_changes;
  pink_ghost_previous_orientation = index;
  return;
}



void reverse_pink_ghost_direction(void)

{
  character_orientation_e index;
  dereference_word_t dVar1;
  
  index = pink_ghost_previous_orientation ^ 2;
  pink_ghost_orientation = index;
  dVar1 = dereference_pointer_to_word((word *)&move_right,index);
  pink_ghost_xy_tile_changes = (undefined2)((uint5)dVar1 >> 0x18);
  if (subroutine_DEMO_state != 0x22) {
    return;
  }
  pink_ghost_Y_tile_changes_A = pink_ghost_xy_tile_changes;
  pink_ghost_previous_orientation = index;
  return;
}



void is_reverse_blue_ghost_direction_time(void)

{
  character_orientation_e index;
  dereference_word_t dVar1;
  
                    // check for reverse direction of inky
                    // 
  if (blue_ghost_change_orientation_flag == false) {
    return;
  }
                    // reverse direction of inky
                    // yes, A := #00
                    // 
  blue_ghost_change_orientation_flag = false;
  index = blue_ghost_previous_orientation ^ 2;
  blue_ghost_orientation = index;
  dVar1 = dereference_pointer_to_word((word *)&move_right,index);
  blue_ghost_xy_tile_changes = (undefined2)((uint5)dVar1 >> 0x18);
  if (subroutine_DEMO_state != 0x22) {
    return;
  }
  blue_ghost_Y_tile_changes_A = blue_ghost_xy_tile_changes;
  blue_ghost_previous_orientation = index;
  return;
}



void reverse_blue_ghost_direction(undefined param_1)

{
  character_orientation_e index;
  dereference_word_t dVar1;
  
  index = blue_ghost_previous_orientation ^ 2;
  blue_ghost_orientation = index;
  dVar1 = dereference_pointer_to_word((word *)&move_right,index);
  blue_ghost_xy_tile_changes = (undefined2)((uint5)dVar1 >> 0x18);
  if (subroutine_DEMO_state != 0x22) {
    return;
  }
  blue_ghost_Y_tile_changes_A = blue_ghost_xy_tile_changes;
  blue_ghost_previous_orientation = index;
  return;
}



void is_reverse_orange_ghost_direction_time(void)

{
  character_orientation_e index;
  dereference_word_t dVar1;
  
                    // check for reverse direction of orange ghost
                    // 
  if (orange_ghost_change_orientation_flag == false) {
    return;
  }
                    // reverse direction of orange ghost
                    // 
  orange_ghost_change_orientation_flag = false;
  index = orange_ghost_previous_orientation ^ 2;
  orange_ghost_orientation = index;
  dVar1 = dereference_pointer_to_word((word *)&move_right,index);
  orange_ghost_xy_tile_changes = (undefined2)((uint5)dVar1 >> 0x18);
  if (subroutine_DEMO_state != 0x22) {
    return;
  }
  orange_ghost_Y_tile_change_A = orange_ghost_xy_tile_changes;
  orange_ghost_previous_orientation = index;
  return;
}



void reverse_orange_ghost_direction(undefined param_1)

{
  character_orientation_e index;
  dereference_word_t dVar1;
  
  index = orange_ghost_previous_orientation ^ 2;
  orange_ghost_orientation = index;
  dVar1 = dereference_pointer_to_word((word *)&move_right,index);
  orange_ghost_xy_tile_changes = (undefined2)((uint5)dVar1 >> 0x18);
  if (subroutine_DEMO_state != 0x22) {
    return;
  }
  orange_ghost_Y_tile_change_A = orange_ghost_xy_tile_changes;
  orange_ghost_previous_orientation = index;
  return;
}



void vblank_continuation(bool test_mode)

{
                    //  new for INTERRUPT MODE 1
                    //  rst 38 continuation  (vblank)
                    //  This code not found in original hardware
                    // 
  if (test_mode != false) {
                    // not in test mode
                    // 
    interrupt_vector();
    return;
  }
                    // in test mode
                    // 
  interrupt_vector_pacman_only();
  return;
}



// this is a common function
// 
// IY is preloaded with sprite locations
// IX is preloaded with offset to add
// result is stored into HL
// 
// HL := (IX) + (IY)

sprite_coord_yx_t update_coord(sprite_coord_yx_t *sprite_location,sprite_coord_yx_t *seek_location)

{
  return (sprite_coord_yx_t)
         CONCAT11(sprite_location->x + seek_location->x,sprite_location->y + seek_location->y);
}



// load A with screen value of position computed in (IX) + (IY)

byte get_from_screen_position(sprite_coord_yx_t *sprite_location,sprite_coord_yx_t *seek_location)

{
  byte *screen_position;
  sprite_coord_yx_t coord;
  
  coord = update_coord(sprite_location,seek_location);
  screen_position = convert_xy_to_screen_position(coord);
  return *screen_position;
}



// converts a sprite position into a tile position
// HL is preloaded with sprite position
// at end, HL is loaded with tile position
// 

sprite_coord_yx_t convert_sprite_position_to_tile_position(sprite_coord_yx_t sprite_position)

{
  return (sprite_coord_yx_t)
         CONCAT11((byte)((ushort)sprite_position >> 0xb) + 0x1e,((byte)sprite_position >> 3) + 0x20)
  ;
}



// converts pac-mans sprite position into a grid position
// HL has sprite position at start, grid position at end

byte * convert_xy_to_screen_position(sprite_coord_yx_t coord)

{
  char cVar1;
  
  cVar1 = (char)((ushort)coord >> 8);
  return hardware_screen_maze_area +
         (ushort)(byte)((char)coord - 0x20) +
         CONCAT11(((byte)(cVar1 * '\b') >> 7) << 1 | (byte)(cVar1 * '\x10') >> 7,cVar1 * ' ');
}



// converts pac-man or ghost Y,X position in HL to a color screen location

sprite_coord_yx_t convert_xy_to_color_screen_position(sprite_coord_yx_t coord)

{
  byte *pbVar1;
  
  pbVar1 = convert_xy_to_screen_position(coord);
  return (sprite_coord_yx_t)(pbVar1 + 0x400);
}



// checks for ghost entering a slowdown area in a tunnel
// 

void check_ghost_entering_tunnel_slowdown(sprite_coord_yx_t coord,byte *delay)

{
  sprite_coord_yx_t sVar1;
  
  sVar1 = convert_xy_to_color_screen_position(coord);
                    // arrive here from #2060
                    // A is loaded with the color of the tile the ghost is on
                    // 
  if ((*(byte *)sVar1 & 0x40) != 0) {
    *delay = 1;
    return;
  }
  *delay = 0;
  return;
}



void leave_house_check_pink_ghost(void)

{
                    // called from #105C
                    // 
  if (pink_ghost_substate_if_alive != AT_HOME) {
    return;
  }
  if (dying_in_a_level != false) {
    if (eaten_pills_counter_after_pacman_has_died_in_a_level != 7) {
      return;
    }
    release_pink_ghost_from_the_ghost_house();
    return;
  }
  if (can_pink_ghost_leave_home < pink_ghost_counter_to_go_out_of_home_limit) {
    return;
  }
  pink_ghost_substate_if_alive = CROSSING_THE_DOOR;
  return;
}



// releases pink ghost from the ghost house

void release_pink_ghost_from_the_ghost_house(void)

{
  pink_ghost_substate_if_alive = CROSSING_THE_DOOR;
  return;
}



void leave_house_check_blue_ghost(void)

{
                    // called from #105F
                    // 
  if (blue_ghost_substate_if_alive != AT_HOME) {
    return;
  }
  if (dying_in_a_level != false) {
    if (eaten_pills_counter_after_pacman_has_died_in_a_level != 0x11) {
      return;
    }
    release_blue_ghost_from_the_ghost_house();
    return;
  }
  if (can_blue_ghost_leave_home < blue_ghost_counter_to_go_out_of_home_limit) {
    return;
  }
  blue_ghost_substate_if_alive = GOING_TO_THE_DOOR;
  return;
}



// releases blue ghost (inky) from the ghost house

void release_blue_ghost_from_the_ghost_house(void)

{
  blue_ghost_substate_if_alive = GOING_TO_THE_DOOR;
  return;
}



void leave_house_check_orange_ghost(void)

{
                    // called from #1062
                    // 
  if (orange_ghost_substate_if_alive != AT_HOME) {
    return;
  }
  if (dying_in_a_level != false) {
    if (eaten_pills_counter_after_pacman_has_died_in_a_level != 0x20) {
      return;
    }
    eaten_pills_counter_after_pacman_has_died_in_a_level = 0;
    dying_in_a_level = false;
    return;
  }
  if (can_orange_ghost_leave_home < orange_ghost_counter_to_go_out_of_home_limit) {
    return;
  }
  orange_ghost_substate_if_alive = GOING_TO_THE_DOOR;
  return;
}



// releases orange ghost from the ghost house

void releases_orange_ghost_from_the_ghost_house(void)

{
  orange_ghost_substate_if_alive = GOING_TO_THE_DOOR;
  return;
}



// checks for and sets the difficulty flags based on number of pellets eaten

void check_and_set_difficulty_flags(void)

{
  if (orange_ghost_substate_if_alive == AT_HOME) {
    return;
  }
  if (red_ghost_first_difficulty_flag == false) {
    if (red_ghost_remainder_of_pills_when_first_difficulty_flag_is_set < (byte)(-dots_eaten - 0xc))
    {
      return;
    }
    red_ghost_first_difficulty_flag = true;
  }
  if (red_ghost_second_difficulty_flag != false) {
    return;
  }
  if (red_ghost_remainder_of_pills_when_second_difficulty_flag_is_set < (byte)(-dots_eaten - 0xc)) {
    return;
  }
  red_ghost_second_difficulty_flag = true;
  return;
}



void state_for_1st_intermission(void)

{
  ushort uVar1;
  byte bVar2;
  char cVar3;
  byte bVar4;
  byte index;
  byte in_C;
  undefined uVar5;
  undefined2 uVar6;
  ushort uVar7;
  byte *pbVar8;
  short sVar9;
  char *pcVar10;
  undefined *puVar11;
  undefined1 *puVar12;
  byte *lookup_table;
  byte **ppbVar13;
  dereference_word_t dVar14;
  word *lookup_table_00;
  
  if (intermission_mode != true) {
                    // WARNING: Return address prevents inlining here
    insert_task(&task_draw_they_meet);
    hardware_screen_maze_area[22][4] = 1;
    BYTE_ARRAY_ARRAY_ram_4440[22][4] = 0x16;
    intermissions_and_attract_mode_animation_main_routine(0);
    return;
  }
  if (false) {
    generate_animations(in_C);
  }
  uVar7 = CONCAT11(6,in_C);
  ppbVar13 = animation_current + 5;
  do {
    uVar5 = (undefined)uVar7;
    index = (byte)(uVar7 >> 8);
    lookup_table = *ppbVar13;
    bVar2 = *lookup_table;
    if (bVar2 == 0xf0) {
intermissions_and_attract_mode_animation_main_routine_animation_code_F0_loop:
      bVar2 = dereference_pointer_to_byte(lookup_table,1);
      uVar6 = CONCAT11(index,bVar2);
      dVar14 = dereference_pointer_to_word(WORD_ARRAY_ram_4f2e,index);
      pbVar8 = (byte *)((uint5)dVar14 >> 8);
      bVar2 = animation_code_f0_loop_sub_stuff((char)uVar6 + (char)((uint5)dVar14 >> 0x20));
      *pbVar8 = bVar2;
      lookup_table_00 = (word *)animation_code_f0_and_f1_sub_stuff(uVar6);
      dVar14 = dereference_pointer_to_word(lookup_table_00,(byte)((ushort)uVar6 >> 8));
      index = (byte)((ushort)uVar6 >> 8);
      *(char *)((uint5)dVar14 >> 8) = (char)((uint5)dVar14 >> 0x20) + (char)uVar6;
      bVar2 = dereference_pointer_to_byte(lookup_table,2);
      uVar6 = CONCAT11(index,bVar2);
      dVar14 = dereference_pointer_to_word(WORD_ARRAY_ram_4f2e,index);
      sVar9 = (short)((uint5)dVar14 >> 8);
      bVar2 = animation_code_f0_loop_sub_stuff((char)uVar6 + (char)((uint5)dVar14 >> 0x18));
      *(byte *)(sVar9 + -1) = bVar2;
      lookup_table_00 = (word *)animation_code_f0_and_f1_sub_stuff(uVar6);
      dVar14 = dereference_pointer_to_word(lookup_table_00,(byte)((ushort)uVar6 >> 8));
      *(char *)((short)((uint5)dVar14 >> 8) + -1) = (char)((uint5)dVar14 >> 0x18) + (char)uVar6;
      pcVar10 = &DAT_ram_4f0f;
      index = (byte)((ushort)uVar6 >> 8);
      bVar2 = dereference_pointer_to_byte(&DAT_ram_4f0f,index);
      cVar3 = bVar2 + 1;
      while( true ) {
        dVar14 = dereference_pointer_to_word(WORD_ARRAY_ram_4f3e,index);
        bVar2 = dereference_pointer_to_byte((byte *)((uint5)dVar14 >> 0x18),cVar3 >> 1);
        if (bVar2 != 0xff) break;
        cVar3 = '\0';
      }
      *pcVar10 = cVar3;
      bVar4 = dereference_pointer_to_byte(lookup_table,3);
      dVar14 = dereference_pointer_to_word(&WORD_ram_4f4e,index);
      lookup_table = (byte *)((uint5)dVar14 >> 8);
      *lookup_table = bVar4;
      uVar7 = CONCAT11(index,current_player_number);
      if ((cocktail_mode & current_player_number) != 0) {
        bVar2 = bVar2 ^ 0xc0;
      }
      lookup_table[-1] = bVar2;
      pcVar10 = &animation_cmd_setn;
      bVar2 = dereference_pointer_to_byte(&animation_cmd_setn,index);
      *pcVar10 = bVar2 - 1;
      sVar9 = 0;
      if ((byte)(bVar2 - 1) == '\0') {
        sVar9 = 4;
      }
    }
    else {
      if (bVar2 == 0xf1) {
        lookup_table_00 = (word *)animation_code_f0_and_f1_sub_stuff(uVar7);
        uVar6 = CONCAT11(lookup_table[1],lookup_table[2]);
intermissions_and_attract_mode_animation_main_routine_cleanup_for_return_from_f0_f1_f3:
        dVar14 = dereference_pointer_to_word(lookup_table_00,(byte)(uVar7 >> 8));
        puVar11 = (undefined *)((uint5)dVar14 >> 8);
        *puVar11 = (char)((ushort)uVar6 >> 8);
        puVar11[-1] = (char)uVar6;
        sVar9 = 3;
      }
      else {
        if (bVar2 == 0xf2) {
          uVar1 = uVar7 & 0xff00;
          uVar7 = uVar1 | lookup_table[1];
          puVar12 = &animation_cmd_setn;
          dereference_pointer_to_byte(&animation_cmd_setn,(byte)(uVar1 >> 8));
          *puVar12 = (char)uVar7;
          sVar9 = 2;
        }
        else {
          if (bVar2 == 0xf3) {
            puVar11 = &DAT_ram_4f0f;
            dereference_pointer_to_byte(&DAT_ram_4f0f,index);
            *puVar11 = 0;
            lookup_table_00 = WORD_ARRAY_ram_4f3e;
            uVar6 = *(undefined2 *)(lookup_table + 1);
            goto 
            intermissions_and_attract_mode_animation_main_routine_cleanup_for_return_from_f0_f1_f3;
          }
          if (bVar2 == 0xf5) {
            channel_3_effect.num = lookup_table[1];
            sVar9 = 2;
          }
          else {
            if (bVar2 == 0xf6) {
              pcVar10 = &animation_cmd_setn;
              bVar2 = dereference_pointer_to_byte(&animation_cmd_setn,index);
              *pcVar10 = bVar2 - 1;
              sVar9 = 0;
              if ((byte)(bVar2 - 1) == '\0') {
                sVar9 = 1;
              }
            }
            else {
              if (bVar2 == 0xf7) {
                    // WARNING: Return address prevents inlining here
                insert_task(&task_text_or_graphics_draw_space);
                uVar7 = CONCAT11(index,uVar5);
                sVar9 = 1;
              }
              else {
                if (bVar2 == 0xf8) {
                  hardware_screen_maze_area[22][4] = 0x40;
                  sVar9 = 1;
                }
                else {
                  if (bVar2 != 0xff) {
                    halt();
                    goto 
                    intermissions_and_attract_mode_animation_main_routine_animation_code_F0_loop;
                  }
                  lookup_table = &__stack_data_maybe_size_0x14;
                  dereference_pointer_to_byte(&__stack_data_maybe_size_0x14,index);
                  *lookup_table = 1;
                  sVar9 = 0;
                  if ((BYTE_ram_4f20 & BYTE_ram_4f21 & BYTE_ram_4f22 & BYTE_ram_4f23 & BYTE_ram_4f24
                      & BYTE_ram_4f25) != 0) {
                    if (subroutine_DEMO_state == 0) {
                    // WARNING: Return address prevents inlining here
                      add_timed_task(&task_increase_subroutine_PLAYING_state);
                      subroutine_PLAYING_state = subroutine_PLAYING_state + 1;
                      return;
                    }
                    intermission_mode = false;
                    TT02_increase_subroutine_DEMO_state();
                    return;
                  }
                }
              }
            }
          }
        }
      }
    }
    lookup_table = *ppbVar13;
    *(char *)ppbVar13 = (char)(lookup_table + sVar9);
    *(undefined *)((short)ppbVar13 + 1) = (char)((ushort)(lookup_table + sVar9) >> 8);
    ppbVar13 = ppbVar13 + -1;
    bVar2 = (char)(uVar7 >> 8) - 1;
    uVar7 = uVar7 & 0xff | (ushort)bVar2 << 8;
    if (bVar2 == 0) {
      return;
    }
  } while( true );
}



void pacman_junk0(void)

{
  if (pacman_position_tile_position.x == 0x21) {
    red_ghost_substate_if_alive = GOING_FOR_PACMAN;
    red_ghost_second_difficulty_flag = true;
    pacman_3rd_intermission_end();
    state_in_first_cutscene = state_in_first_cutscene + 1;
    return;
  }
  handles_pacman_movement();
  handles_pacman_movement();
  control_movement_red_ghost();
  control_movement_red_ghost();
  is_time_to_change_ghost_animation();
  return;
}



void TT07_increase_state_in_1st_cutescene(void)

{
  state_in_first_cutscene = state_in_first_cutscene + 1;
  return;
}



void pacman_junk1(void)

{
  if (pacman_position_tile_position.x == 0x1e) {
    TT07_increase_state_in_1st_cutescene();
    return;
  }
  handles_pacman_movement();
  handles_pacman_movement();
  control_movement_red_ghost();
  control_movement_red_ghost();
  is_time_to_change_ghost_animation();
  return;
}



void pacman_junk2(undefined2 param_1)

{
  if (red_ghost_tile_position_2.x == 0x1e) {
    pacman_eat_big_pill();
    channel_2_effect.num = 0;
    channel_3_effect.num = 0;
    pacman_used_during_attract_mode();
    pacman_orientation = wanted_pacman_orientation;
    pacman_XY_tile_changes_AB = param_1;
                    // WARNING: Return address prevents inlining here
    add_timed_task((task_timed_t *)0x216a);
    TT07_increase_state_in_1st_cutescene();
    return;
  }
  control_movement_red_ghost();
  control_movement_red_ghost();
  is_time_to_change_ghost_animation();
  return;
}



void pacman_junk4(void)

{
  if (red_ghost_tile_position_2.x == 0x2f) {
    TT07_increase_state_in_1st_cutescene();
    return;
  }
  control_movement_red_ghost();
  control_movement_red_ghost();
  is_time_to_change_ghost_animation();
  return;
}



void pacman_junk5(void)

{
  if (red_ghost_tile_position_2.x == 0x3d) {
    TT07_increase_state_in_1st_cutescene();
    return;
  }
  handles_pacman_movement();
  handles_pacman_movement();
  control_movement_red_ghost();
  control_movement_red_ghost();
  is_time_to_change_ghost_animation();
  return;
}



void pacman_junk6(void)

{
  handles_pacman_movement();
  handles_pacman_movement();
  if ((byte)(pacman_position_tile_position.x - 0x3d) != 0) {
    return;
  }
  state_in_first_cutscene = pacman_position_tile_position.x - 0x3d;
                    // WARNING: Return address prevents inlining here
  add_timed_task(&task_increase_subroutine_PLAYING_state);
  subroutine_PLAYING_state = subroutine_PLAYING_state + 1;
  return;
}



void state_for_2nd_intermission(void)

{
                    // arrive here from #0A44 when 2nd intermission begins
                    // 
  mspacman_state_for_2nd_intermission_patch();
  return;
}



void pacman_2nd_intermission_junk0(undefined *param_1)

{
  BYTE_ARRAY_ARRAY_ram_4440[14][10] = 1;
  BYTE_ARRAY_ARRAY_ram_4440[14][11] = 1;
  BYTE_ARRAY_ARRAY_ram_4440[15][14] = 1;
  BYTE_ARRAY_ARRAY_ram_4440[15][15] = 1;
  pacman_3rd_intermission_end();
  *param_1 = 0x60;
  param_1[1] = 0x61;
                    // WARNING: Return address prevents inlining here
  add_timed_task(&task_increase_state_in_2nd_cutescene);
  TT08_increase_state_in_2nd_cutescene();
  return;
}



void pacman_2nd_intermission_junk2(void)

{
  if (pacman_position_tile_position.x == 0x2c) {
    red_ghost_substate_if_alive = GOING_FOR_PACMAN;
    red_ghost_second_difficulty_flag = true;
    state_in_second_cutscene = state_in_second_cutscene + 1;
    return;
  }
  handles_pacman_movement();
  handles_pacman_movement();
  control_movement_red_ghost();
  control_movement_red_ghost();
  is_time_to_change_ghost_animation();
  return;
}



void TT08_increase_state_in_2nd_cutescene(void)

{
  state_in_second_cutscene = state_in_second_cutscene + 1;
  return;
}



void pacman_2nd_intermission_junk3(void)

{
  if ((red_ghost_coord.x != 0x77) && (red_ghost_coord.x != 0x78)) {
    handles_pacman_movement();
    handles_pacman_movement();
    control_movement_red_ghost();
    control_movement_red_ghost();
    is_time_to_change_ghost_animation();
    return;
  }
  pacman_state.second_difficulty_flag._0_2_ = 0x2084;
  pacman_state.second_difficulty_flag._2_2_ = 0x2084;
  TT08_increase_state_in_2nd_cutescene();
  return;
}



void pacman_2nd_intermission_junk4(undefined *param_1)

{
  if (red_ghost_coord.x == 0x78) {
    *param_1 = 0x62;
    param_1[1] = 99;
    TT08_increase_state_in_2nd_cutescene();
    return;
  }
  handles_pacman_movement();
  handles_pacman_movement();
  control_movement_red_ghost();
  is_time_to_change_ghost_animation();
  return;
}



void pacman_2nd_intermission_junk5(undefined *param_1)

{
  if (red_ghost_coord.x == 0x7b) {
    *param_1 = 100;
    param_1[1] = 0x65;
    param_1[0x20] = 0x66;
    param_1[0x21] = 0x67;
    TT08_increase_state_in_2nd_cutescene();
    return;
  }
  handles_pacman_movement();
  handles_pacman_movement();
  control_movement_red_ghost();
  is_time_to_change_ghost_animation();
  return;
}



void pacman_2nd_intermission_junk6(undefined *param_1)

{
  if (red_ghost_coord.x == 0x7e) {
    *param_1 = 0x68;
    param_1[1] = 0x69;
    param_1[0x20] = 0x6a;
    param_1[0x21] = 0x6b;
    TT08_increase_state_in_2nd_cutescene();
    return;
  }
  handles_pacman_movement();
  handles_pacman_movement();
  control_movement_red_ghost();
  is_time_to_change_ghost_animation();
  return;
}



void pacman_2nd_intermission_junk7(void)

{
  if (red_ghost_coord.x == 0x80) {
                    // WARNING: Return address prevents inlining here
    add_timed_task(&task_increase_state_in_2nd_cutescene);
    TT08_increase_state_in_2nd_cutescene();
    return;
  }
  handles_pacman_movement();
  handles_pacman_movement();
  control_movement_red_ghost();
  is_time_to_change_ghost_animation();
  return;
}



void pacman_2nd_intermission_junk9(undefined *param_1)

{
  red_ghost_coord.x = red_ghost_coord.x + 2;
  *param_1 = 0x6c;
  param_1[1] = 0x6d;
  param_1[0x20] = 0x40;
  param_1[0x21] = 0x40;
                    // WARNING: Return address prevents inlining here
  add_timed_task(&task_increase_state_in_2nd_cutescene);
  TT08_increase_state_in_2nd_cutescene();
  return;
}



void pacman_2nd_intermission_junk11(void)

{
                    // WARNING: Return address prevents inlining here
  add_timed_task(&task_increase_state_in_2nd_cutescene);
  TT08_increase_state_in_2nd_cutescene();
  return;
}



void pacman_2nd_intermission_junk13(void)

{
  subroutine_PLAYING_state = subroutine_PLAYING_state + GHOST_WAIT_FOR_START;
  state_in_second_cutscene = 0;
  return;
}



void state_for_3rd_intermission(void)

{
                    // arrive here from #0A44 for 3rd intermission
                    // 
  mspacman_state_for_3rd_intermission_patch();
  return;
}



void TT09_increase_state_in_3rd_cutescene(void)

{
  state_in_third_cutscene = state_in_third_cutscene + 1;
  return;
}



void pacman_3rd_intermission_junk0(void)

{
                    // pac-man only
                    // referenced in #229D
                    // 
  if ((red_ghost_coord.x != 0xff) && (red_ghost_coord.x != 0xfe)) {
    handles_pacman_movement();
    handles_pacman_movement();
    control_movement_red_ghost();
    control_movement_red_ghost();
    is_time_to_change_ghost_animation();
    return;
  }
  red_ghost_coord.x = red_ghost_coord.x + 2;
  red_ghost_change_orientation_flag = true;
  is_reverse_red_ghost_direction_time();
                    // WARNING: Return address prevents inlining here
  add_timed_task(&task_increase_state_in_3rd_cutescene);
  TT09_increase_state_in_3rd_cutescene();
  return;
}



void pacman_3rd_intermission_junk2(void)

{
                    // pac-man only
                    // referenced in #22A1
                    // 
  if (red_ghost_tile_position_2.x != 0x2d) {
    fruit_coord.y = red_ghost_coord.y;
    fruit_coord.x = red_ghost_coord.x - 8;
    handles_pacman_movement();
    handles_pacman_movement();
    control_movement_red_ghost();
    control_movement_red_ghost();
    is_time_to_change_ghost_animation();
    return;
  }
  state_in_third_cutscene = state_in_third_cutscene + 1;
  return;
}



void pacman_3rd_intermission_junk3(void)

{
  if (red_ghost_tile_position_2.x != 0x1e) {
    fruit_coord.y = red_ghost_coord.y;
    fruit_coord.x = red_ghost_coord.x - 8;
    handles_pacman_movement();
    handles_pacman_movement();
    control_movement_red_ghost();
    control_movement_red_ghost();
    is_time_to_change_ghost_animation();
    return;
  }
  state_in_third_cutscene = state_in_third_cutscene + 1;
  return;
}



void pacman_3rd_intermission_junk4(void)

{
                    // pac-man only
                    // refereneced in line #22A5
                    // 
  state_in_third_cutscene = 0;
                    // WARNING: Return address prevents inlining here
  add_timed_task(&task_increase_state_in_3rd_cutescene);
  subroutine_PLAYING_state = subroutine_PLAYING_state + 1;
  return;
}



// WARNING: This function may have set the stack pointer
// Main program start (reset)
// irq off, sound off, flip off, etc.

void startup_test(void)

{
  ushort uVar1;
  byte c;
  task_core_e index;
  char cVar2;
  byte n;
  in0_t *piVar3;
  byte *s;
  
  piVar3 = &hardware_IN0;
  cVar2 = '\b';
  c = 0;
  do {
    *piVar3 = (in0_t)0x0;
    piVar3 = (in0_t *)((ushort)piVar3 & 0xff00 | (ushort)(byte)((char)piVar3 + 1));
    cVar2 = cVar2 + -1;
  } while (cVar2 != '\0');
                    //  Clear screen
                    //  40 -> 4000-43ff (Video RAM)
                    // 
  s = hardware_video_ram;
  cVar2 = '\x04';
  do {
    write_volatile_1(hardware_DSW2_watchdog,c);
    write_volatile_1(hardware_coin_counter,c);
    c = space;
    do {
      *s = space;
      n = (char)s + 1;
      uVar1 = (ushort)s & 0xff00;
      s = (byte *)(uVar1 | n);
    } while (n != 0);
    s = (byte *)((ushort)(byte)((char)(uVar1 >> 8) + 1) << 8);
    cVar2 = cVar2 + -1;
  } while (cVar2 != '\0');
                    //  0f -> 4400 - 47ff (Color RAM)
                    // 
  cVar2 = '\x04';
  do {
    write_volatile_1(hardware_DSW2_watchdog,c);
    write_volatile_1(hardware_coin_counter,0);
    c = color_reset_maybe_black;
    do {
      *s = color_reset_maybe_black;
      n = (char)s + 1;
      uVar1 = (ushort)s & 0xff00;
      s = (byte *)(uVar1 | n);
    } while (n != 0);
    s = (byte *)((ushort)(byte)((char)(uVar1 >> 8) + 1) << 8);
    cVar2 = cVar2 + -1;
  } while (cVar2 != '\0');
                    //  test the interrupt hardware now
                    // INTERRUPT MODE 1
                    // 
  setInterruptMode(1);
                    // Pac's routine: (Puckman, Pac-Man Plus)
                    // INTERRUPT MODE 2
                    // interrupt mode 2
                    // 233d  3efa      ld      a,#fa
                    // interrupt vector -> 0xfa #3ffa vector to #3000
                    // see also "INTERRUPT MODE 2" above...
                    // 
  write_volatile_1(hardware_coin_counter,0);
  hardware_IN0 = (in0_t)0x1;
  enableMaskableInterrupts();
  halt();
                    //  main program init
                    //  perhaps a contiuation from 3295
                    // 
  write_volatile_1(hardware_DSW2_watchdog,1);
                    //  reset custom registers.  Set them to 0
                    // 
  c = 0;
  ARRAY_ram_4f5c._98_2_ = 0x2359;
  memset((byte *)&hardware_IN0,0,8);
                    //  clear ram
                    // 
  n = 0xbe;
  ARRAY_ram_4f5c._98_2_ = 0x235f;
  s = (byte *)memset((byte *)&start_of_sprites_address,c,0xbe);
  ARRAY_ram_4f5c._98_2_ = 0x2360;
  s = (byte *)memset(s,c,n);
  ARRAY_ram_4f5c._98_2_ = 0x2361;
  s = (byte *)memset(s,c,n);
  ARRAY_ram_4f5c._98_2_ = 0x2362;
  memset(s,c,n);
                    //  clear sound registers, color ram, screen, task list
                    // 
  ARRAY_ram_4f5c._98_2_ = 0x2368;
  memset((byte *)&hardware_IN1,c,0x40);
  write_volatile_1(hardware_DSW2_watchdog,c);
  ARRAY_ram_4f5c._98_2_ = 0x236e;
  c = T06_clears_color_RAM();
  write_volatile_1(hardware_DSW2_watchdog,c);
  ARRAY_ram_4f5c._98_2_ = 0x2376;
  c = T00_clear_whole_screen_or_maze(0);
  write_volatile_1(hardware_DSW2_watchdog,c);
  p_task_list_next_free = tasks_to_execute_outside_of_irq;
  p_task_list_begin = tasks_to_execute_outside_of_irq;
  ARRAY_ram_4f5c._98_2_ = 0x2387;
  memset((byte *)tasks_to_execute_outside_of_irq,0xff,0x40);
  hardware_IN0 = (in0_t)0x1;
  enableMaskableInterrupts();
  s = _STACK_END;
  do {
    do {
      index = p_task_list_begin->value;
    } while ((char)index < '\0');
    p_task_list_begin->value = ~clear_whole_screen_or_maze;
    uVar1 = (ushort)p_task_list_begin & 0xff00;
    *(undefined *)(uVar1 | (byte)((char)p_task_list_begin + 1)) = 0xff;
    c = (char)p_task_list_begin + 2;
    p_task_list_begin = (task_core_t *)(uVar1 | c);
    if (c == 0) {
      p_task_list_begin = (task_core_t *)CONCAT11((char)(uVar1 >> 8),0xc0);
    }
    *(undefined2 *)(s + -2) = 0x238d;
                    // WARNING: Return address prevents inlining here
    *(undefined2 *)(s + -4) = 0x23a8;
    jump_table_fn(*(undefined **)(s + -4),index);
    s = s + -2;
  } while( true );
}



// process the task list, a core game loop
// 

void execute_CORE_task(void)

{
  ushort uVar1;
  task_core_e index;
  byte bVar2;
  
  do {
    do {
      index = p_task_list_begin->value;
    } while ((char)index < '\0');
    p_task_list_begin->value = ~clear_whole_screen_or_maze;
    uVar1 = (ushort)p_task_list_begin & 0xff00;
    *(undefined *)(uVar1 | (byte)((char)p_task_list_begin + 1)) = 0xff;
    bVar2 = (char)p_task_list_begin + 2;
    p_task_list_begin = (task_core_t *)(uVar1 | bVar2);
    if (bVar2 == 0) {
      p_task_list_begin = (task_core_t *)CONCAT11((char)(uVar1 >> 8),0xc0);
    }
    *(undefined2 *)((undefined *)register0x44 + -2) = 0x238d;
                    // WARNING: Return address prevents inlining here
    *(undefined2 *)((undefined *)register0x44 + -4) = 0x23a8;
    jump_table_fn(*(undefined **)((undefined *)register0x44 + -4),index);
    register0x44 = (BADSPACEBASE *)((undefined *)register0x44 + -2);
  } while( true );
}



void T16_increase_main_subroutine_number(void)

{
  subroutine_PLAYING_state = subroutine_PLAYING_state + 1;
  return;
}



// task #00, called from #23A7

void T00_clear_whole_screen_or_maze(byte param)

{
                    // WARNING: Return address prevents inlining here
  jump_table_fn((undefined *)clear_fn_table,param);
  return;
}



void clear_hardware_video_ram(void)

{
  byte c;
  char cVar1;
  byte n;
  byte *s;
  
  c = space;
  cVar1 = '\x04';
  n = 0;
  s = hardware_video_ram;
  do {
    s = (byte *)memset(s,c,n);
    cVar1 = cVar1 + -1;
  } while (cVar1 != '\0');
  return;
}



// clears the maze only

void clear_hardware_video_maze_only(void)

{
  byte c;
  char cVar1;
  byte n;
  byte *s;
  
  c = space;
  s = hardware_screen_maze_area;
  cVar1 = '\x04';
  n = 0x80;
  do {
    s = (byte *)memset(s,c,n);
    cVar1 = cVar1 + -1;
  } while (cVar1 != '\0');
  return;
}



// clears color ram

void T06_clears_color_RAM(void)

{
  byte c;
  char cVar1;
  byte n;
  byte *s;
  
  c = 0;
  cVar1 = '\x04';
  n = 0;
  s = hardware_color_ram;
  do {
    s = (byte *)memset(s,c,n);
    cVar1 = cVar1 + -1;
  } while (cVar1 != '\0');
  return;
}



// Draw out the maze to the screen

void T02_draw_maze(void)

{
  byte bVar1;
  byte *pbVar2;
  byte *pbVar3;
  
  pbVar3 = hardware_video_ram;
  pbVar2 = get_current_maze_table();
  while( true ) {
    bVar1 = *pbVar2;
    if (bVar1 == 0) break;
    if (-1 < (char)bVar1) {
      pbVar3 = pbVar3 + ((ushort)bVar1 - 1);
      pbVar2 = pbVar2 + 1;
      bVar1 = *pbVar2;
    }
    pbVar3 = pbVar3 + 1;
    *pbVar3 = bVar1;
    *(byte *)((short)&cmd_1_setpos_t_ram_83e0 +
             ((ushort)(byte)(((byte)pbVar3 & 0x1f) * '\x02') - (short)pbVar3)) = bVar1 ^ 1;
    pbVar2 = pbVar2 + 1;
  }
  return;
}



// draw out the player pills
// 

void T03_draw_pellets(void)

{
                    // 
  get_maze_data_from_current_level((byte *)pellet_map_loopkup_table);
  return;
}



// update the current screen pill config to video ram
// 

void T15_update_screen_pill_config_to_video_ram(void)

{
                    // ; OTTOPATCH
                    // ORG 248AH
                    // JP DOTSA2
  get_maze_data_from_current_level((byte *)pellet_map_loopkup_table);
  return;
}



// sets up the pill_data_entries[30] to 0xFF and power_pills_data_entries[4] to 0x14
// 

void T12_clears_pills_and_power_pills_arrays(void)

{
  byte *s;
  
  s = (byte *)memset(pill_data_entries,0xff,0x1e);
  memset(s,0x14,4);
  return;
}



void T01_select_maze_color(undefined2 param_1)

{
  color_e c;
  char cVar1;
  byte n;
  char cVar2;
  char cVar3;
  byte *s;
  byte *lookup_table;
  
                    // sets up the maze color
                    // called from #23A7 as task #01
                    // 
  cVar3 = (char)((ushort)param_1 >> 8);
  c = white;
                    // OTTOPATCH
                    // PATCH TO CALL AMAZING NEW COLOR ROUTINE INSTEAD OF USING THE SAME DULL BLUE
                    // 
  if ((cVar3 != '\x02') &&
     ((subroutine_DEMO_state == 0 || (c = red, subroutine_DEMO_state == 0x10)))) {
                    // controls the color of the mazes
                    // 
    n = current_level;
    if (-1 < (char)(((char)(current_level - 0x15) < '\0') << 7)) {
      cVar2 = current_level - 0x15;
      do {
        cVar1 = cVar2;
        cVar2 = cVar1 + -0x10;
      } while (-1 < (char)((cVar2 < '\0') << 7));
      n = cVar1 + 5;
    }
    c = color_palette_table_for_mazes[n];
  }
                    // arrive back here from ms pac patch
                    // 
  s = BYTE_ARRAY_ARRAY_ram_4440;
  cVar2 = '\x04';
  n = 0x80;
  do {
    s = (byte *)memset(s,c,n);
    cVar2 = cVar2 + -1;
  } while (cVar2 != '\0');
  memset(BYTE_ARRAY_ARRAY_ram_47c0,0xf,0x40);
  if (cVar3 != '\x01') {
    return;
  }
                    // sets bit 6 in the color grid of certain screen locations on the first three
                    // levels.
                    // This color bit is ignored when actually coloring the grid, so it is invisible
                    // onscreen.
                    // When a ghost encounters one of these specially painted areas, he slows down.
                    // This is used to slow down the ghosts when they use the tunnels on these
                    // levels.
                    // called from #24F9
                    // 
  if ((char)(((char)(current_level - 3) < '\0') << 7) < '\0') {
    s = get_maze_data_from_current_level((byte *)tunnel_slow_down_lookup_table);
    lookup_table = hardware_color_ram;
    while( true ) {
      n = *s;
      s = s + 1;
      if (n == 0) break;
      dereference_pointer_to_byte(lookup_table,n);
      *lookup_table = *lookup_table | 0x40;
    }
  }
                    // ms. pac resumes here
                    // 
  BYTE_ARRAY_ARRAY_ram_4440[15][9] = 0x18;
  BYTE_ARRAY_ARRAY_ram_4440[16][13] = 0x18;
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void T04_reset_sprites_to_default_values(undefined2 param_1)

{
  character_orientation_e cVar1;
  
                    // called from #23A7 for task #04
                    // resets a bunch of memories to predefined values
                    // 
  red_ghost_sprite._0_1_ = 0x20;
  pink_ghost_sprite._0_1_ = 0x20;
  blue_sprite._0_1_ = 0x20;
  orange_ghost_sprite._0_1_ = 0x20;
  mspac_sprite._0_1_ = 0x2c;
  fruit_sprite._0_1_ = 0x3f;
  red_ghost_sprite.color = red;
  pink_ghost_sprite.color = pink;
  blue_sprite.color = inky;
  orange_ghost_sprite.color = orange_and_color_maze_level_10_11_12_13;
  mspac_sprite.color = mspac;
  fruit_sprite.color = fruit;
  if ((char)((ushort)param_1 >> 8) == '\0') {
    red_ghost_sprite._0_1_ = 0x20;
    red_ghost_sprite.color = red;
    pink_ghost_sprite._0_1_ = 0x20;
    pink_ghost_sprite.color = pink;
    blue_sprite._0_1_ = 0x20;
    blue_sprite.color = inky;
    orange_ghost_sprite._0_1_ = 0x20;
    orange_ghost_sprite.color = orange_and_color_maze_level_10_11_12_13;
    mspac_sprite._0_1_ = 0x2c;
    mspac_sprite.color = mspac;
    fruit_sprite._0_1_ = 0x3f;
    fruit_sprite.color = fruit;
    red_ghost_coord = 0x8064;
    pink_ghost_coord = 0x807c;
    blue_ghost_coord = 0x907c;
    orange_ghost_coord = 0x707c;
    pacman_coord = (code *)0x80c4;
    red_ghost_xy_tile_pos = 0x2e2c;
    pink_ghost_xy_tile_pos = 0x2e2f;
    blue_ghost_xy_tile_pos = 0x302f;
    orange_ghost_xy_tile_pos = 0x2c2f;
    pacman_tile_pos_in_demo_and_cut_scenes = 0x2e38;
    red_ghost_Y_tile_changes_A = 0x100;
    pink_ghost_Y_tile_changes_A = 1;
    blue_ghost_Y_tile_changes_A = 0xff;
    orange_ghost_Y_tile_change_A = 0xff;
    pacman_XY_tile_changes_AB = 0x100;
    red_ghost_xy_tile_changes = 0x100;
    pink_ghost_xy_tile_changes = 1;
    blue_ghost_xy_tile_changes = 0xff;
    orange_ghost_xy_tile_changes = 0xff;
    wanted_pacman_tile_changes = 0x100;
    _red_ghost_previous_orientation = 0x102;
    _blue_ghost_previous_orientation = 0x303;
    _red_ghost_orientation = 0x102;
    _blue_ghost_orientation = 0x303;
    pacman_orientation = left;
    red_ghost_tile_position_2 = 0x2e2c;
    pink_ghost_tile_position_2 = 0x2e2f;
    blue_ghost_tile_position_2 = 0x302f;
    orange_ghost_tile_position_2 = 0x2c2f;
    pacman_position_tile_position = 0x2e38;
    wanted_pacman_orientation = left;
    fruit_coord = 0;
    return;
  }
                    // pac-man only, sets up sprites for character introduction screen
                    // 
  red_ghost_coord = 0x94;
  pink_ghost_coord = 0x94;
  blue_ghost_coord = 0x94;
  orange_ghost_coord = 0x94;
  red_ghost_xy_tile_pos = 0x1e32;
  pink_ghost_xy_tile_pos = 0x1e32;
  blue_ghost_xy_tile_pos = 0x1e32;
  orange_ghost_xy_tile_pos = 0x1e32;
  red_ghost_tile_position_2 = 0x1e32;
  pink_ghost_tile_position_2 = 0x1e32;
  blue_ghost_tile_position_2 = 0x1e32;
  orange_ghost_tile_position_2 = 0x1e32;
  red_ghost_Y_tile_changes_A = 0x100;
  pink_ghost_Y_tile_changes_A = 0x100;
  blue_ghost_Y_tile_changes_A = 0x100;
  orange_ghost_Y_tile_change_A = 0x100;
  red_ghost_xy_tile_changes = 0x100;
  pink_ghost_xy_tile_changes = 0x100;
  blue_ghost_xy_tile_changes = 0x100;
  orange_ghost_xy_tile_changes = 0x100;
  pacman_XY_tile_changes_AB = 0x100;
  wanted_pacman_tile_changes = 0x100;
  cVar1 = left;
  memset(&red_ghost_previous_orientation,2,9);
  pacman_coord = TT00_increase_subroutine_PLAYING_state;
  pacman_tile_pos_in_demo_and_cut_scenes = 0x1f32;
  pacman_position_tile_position = 0x1f32;
  wanted_pacman_orientation = cVar1;
  return;
}



// called from #136E after mspac has died
// called from #23A7 as task #1E
// 

void T1E_clear_fruit_and_pacman_position(void)

{
  red_ghost_coord = 0;
  pink_ghost_coord = 0;
  blue_ghost_coord = 0;
  orange_ghost_coord = 0;
  pacman_coord = 0;
  fruit_coord = 0;
  return;
}



void clear_all_ghost_from_screen(undefined2 param_1)

{
  red_ghost_coord = param_1;
  pink_ghost_coord = param_1;
  blue_ghost_coord = param_1;
  orange_ghost_coord = param_1;
                    // called from #09F6
                    // 
  return;
}



void T05_reset_ghost_home_counter(undefined2 param_1)

{
                    // task #05 called from #23A7
                    // 
  if ((char)((ushort)param_1 >> 8) == '\x01') {
    counter_related_to_ghost_movement_inside_home = 0x55;
    return;
  }
  counter_related_to_ghost_movement_inside_home = 0x55;
  red_ghost_substate_if_alive = GOING_FOR_PACMAN;
  return;
}



void T07_set_game_to_demo_mode(void)

{
  game_mode = DEMO;
  subroutine_INIT_state = 0;
                    // sets demo mode
                    // 
  return;
}



void T11_clear_full_data_game(void)

{
  sprite_coord_yx_t *psVar1;
  
                    // task #11 called from #23A7
                    // 
  psVar1 = &red_ghost_coord;
  do {
    psVar1->y = 0;
    psVar1 = (sprite_coord_yx_t *)&psVar1->x;
  } while (psVar1 != (sprite_coord_yx_t *)&game_mode);
  return;
}



// called from #23A7 as task #1F
// writes points needed for extra life digits to screen
// 

void T1F_draw_extra_life_points(void)

{
  hardware_screen_maze_area[8][22] = (bonus_life & 0xf) + 0x30;
  if (bonus_life >> 4 == 0) {
    return;
  }
  hardware_screen_maze_area[9][26] = (bonus_life >> 4) + 0x30;
  return;
}



void T14_setup_config_from_dip_switches(void)

{
  byte bVar1;
  byte bVar2;
  dereference_word_t dVar3;
  
                    // check dip switches 0 and 1 .  Free play or coins per credit
                    // 
  bVar2 = read_volatile_1(hardware_DSW1);
  number_of_credits_per_coin = bVar2 & 3;
  if (number_of_credits_per_coin == 0) {
    number_of_credits_xff_for_free_play = 0xff;
  }
  number_of_coins_per_credit = (number_of_credits_per_coin >> 1) + (bVar2 & 1);
  number_of_credits_per_coin = number_of_coins_per_credit & 2 ^ number_of_credits_per_coin;
                    // check dip switches 2 and 3.  number of starting lives per game
                    // 
  bVar1 = bVar2 >> 2 & 3;
  number_of_lives = bVar1 + 1;
  if (number_of_lives == 4) {
    number_of_lives = bVar1 + 2;
  }
                    // check dip switches 4 and 5.  points for bonus pac man
                    // 
  bonus_life = dereference_pointer_to_byte(&bonus_points_option,bVar2 >> 4 & 3);
                    // check dip switch 7 for ghost names during attract mode
                    // 
  ghost_names_mode = (bool)(~(bVar2 >> 7) & 1);
                    // check dip switch 6 for difficulty
                    // 
  dVar3 = dereference_pointer_to_word
                    ((word *)&difficulty_settings_lookup_table,~((bVar2 << 1) >> 7) & 1);
                    // check bit 7 on IN1 for upright / cocktail
                    // 
  cocktail_mode = (bool)(~((byte)hardware_IN1 >> 7) & 1);
  p_difficulty_settings = (undefined *)((uint5)dVar3 >> 0x18);
  return;
}



// red ghost logic: (not edible)

void T08_red_ghost_AI(void)

{
  character_orientation_e orientation;
  sprite_coord_yx_t destination_tile;
  sprite_coord_yx_t current_position_tile;
  undefined3 uVar1;
  
  if ((((counter__orientation_changes_index & 1) == 0) && (red_ghost_first_difficulty_flag == false)
      ) && (subroutine_PLAYING_state == GHOST_MOVE)) {
    orientation = red_ghost_orientation;
    current_position_tile = red_ghost_xy_tile_pos;
                    // random red ghost directions
                    // 
                    // ; OTTPATCH
                    // ;PATCH TO MAKE THE MONSTERS MOVE RANDOMLY
                    // ORG 274BH
                    // CALL RCORNER
    destination_tile = (sprite_coord_yx_t)pick_quadrant();
    uVar1 = distance_check(current_position_tile,destination_tile,orientation);
    red_ghost_xy_tile_changes = (short)uVar1;
    red_ghost_orientation = (character_orientation_e)((uint3)uVar1 >> 0x10);
    return;
  }
                    // normal movement get direction for red ghost
                    // 
  uVar1 = distance_check(red_ghost_xy_tile_pos,pacman_position_tile_position,red_ghost_orientation);
  red_ghost_xy_tile_changes = (short)uVar1;
  red_ghost_orientation = (character_orientation_e)((uint3)uVar1 >> 0x10);
  return;
}



// pink ghost AI start

void T09_pink_ghost_AI(void)

{
  character_orientation_e orientation;
  sprite_coord_yx_t destination_tile;
  sprite_coord_yx_t current_position_tile;
  undefined3 uVar1;
  
  if (((counter__orientation_changes_index & 1) == 0) && (subroutine_PLAYING_state == GHOST_MOVE)) {
    orientation = pink_ghost_orientation;
    current_position_tile = pink_ghost_xy_tile_pos;
                    // pink ghost random movement
                    // 
    destination_tile = (sprite_coord_yx_t)pick_quadrant();
    uVar1 = distance_check(current_position_tile,destination_tile,orientation);
    pink_ghost_xy_tile_changes = (short)uVar1;
    pink_ghost_orientation = (character_orientation_e)((uint3)uVar1 >> 0x10);
    return;
  }
                    // pink ghost normal movement
                    // 
                    // hard hack: HACK6
                    // 2795  00        nop
                    // 
  uVar1 = distance_check(pink_ghost_xy_tile_pos,
                         (sprite_coord_yx_t)
                         (pacman_XY_tile_changes_AB * 4 + pacman_position_tile_position),
                         pink_ghost_orientation);
  pink_ghost_xy_tile_changes = (short)uVar1;
  pink_ghost_orientation = (character_orientation_e)((uint3)uVar1 >> 0x10);
  return;
}



// blue ghost (inky) AI
// 

void T0A_blue_ghost_AI(void)

{
  character_orientation_e orientation;
  sprite_coord_yx_t current_position_tile;
  short sVar1;
  undefined3 uVar2;
  
  if (((counter__orientation_changes_index & 1) == 0) && (subroutine_PLAYING_state == GHOST_MOVE)) {
    current_position_tile = blue_ghost_xy_tile_pos;
                    // random (?) blue ghost (inky) movement
                    // 
    orientation = pick_quadrant_for_blue_ghost_direction();
    uVar2 = distance_check(current_position_tile,(sprite_coord_yx_t)0x2040,orientation);
    blue_ghost_xy_tile_changes = (short)uVar2;
    blue_ghost_orientation = (character_orientation_e)((uint3)uVar2 >> 0x10);
    return;
  }
                    // normal blue ghost (inky) movement
                    // 
                    // H loads with (0 = facing up or down, 01 = facing left, FF = facing right)
                    // L loads with (0= facing left or right, 01 = facing down, FF = facing up)
                    // 
  sVar1 = pacman_XY_tile_changes_AB * 2 + pacman_position_tile_position;
  uVar2 = distance_check(blue_ghost_xy_tile_pos,
                         (sprite_coord_yx_t)
                         CONCAT11((char)((ushort)sVar1 >> 8) * '\x02' -
                                  (char)((ushort)red_ghost_xy_tile_pos >> 8),
                                  (char)sVar1 * '\x02' - (char)red_ghost_xy_tile_pos),
                         blue_ghost_orientation);
  blue_ghost_xy_tile_changes = (short)uVar2;
  blue_ghost_orientation = (character_orientation_e)((uint3)uVar2 >> 0x10);
  return;
}



void T0B_orange_ghost_AI(void)

{
  character_orientation_e orientation;
  sprite_coord_yx_t current_position_tile;
  word wVar1;
  undefined3 uVar2;
  
  orientation = counter__orientation_changes_index;
  if (((counter__orientation_changes_index & 1) != 0) ||
     (orientation = subroutine_PLAYING_state, subroutine_PLAYING_state != GHOST_MOVE)) {
    wVar1 = get_distance(&orange_ghost_xy_tile_pos,&pacman_position_tile_position);
    if (0x3f < wVar1) {
      uVar2 = distance_check(orange_ghost_xy_tile_pos,pacman_position_tile_position,
                             orange_ghost_orientation);
      orange_ghost_xy_tile_changes = (short)uVar2;
      orange_ghost_orientation = (character_orientation_e)((uint3)uVar2 >> 0x10);
      return;
    }
  }
  current_position_tile = orange_ghost_xy_tile_pos;
  pick_quadrant_for_orange_ghost_direction();
  uVar2 = distance_check(current_position_tile,(sprite_coord_yx_t)channel_2_height_effects,
                         orientation);
  orange_ghost_xy_tile_changes = (short)uVar2;
  orange_ghost_orientation = (character_orientation_e)((uint3)uVar2 >> 0x10);
  return;
}



// task = #0C
// check red ghost movement when power pill active
// 

void T0C_red_ghost_movement_when_power_pill(void)

{
  sprite_coord_yx_t sVar1;
  undefined3 uVar2;
  
  if (red_ghost_state != ALIVE) {
    uVar2 = distance_check(red_ghost_xy_tile_pos,(sprite_coord_yx_t)0x2e2c,red_ghost_orientation);
    red_ghost_xy_tile_changes = (sprite_coord_yx_t)(short)uVar2;
    red_ghost_orientation = (character_orientation_e)((uint3)uVar2 >> 0x10);
    return;
  }
  sVar1 = red_ghost_xy_tile_pos;
  red_ghost_orientation = get_best_orientation(red_ghost_orientation,red_ghost_xy_tile_pos);
  red_ghost_xy_tile_changes = sVar1;
  return;
}



// task = #0D
// check pink ghost movement when power pill active
// 

void T0D_pink_ghost_movement_when_power_pill(void)

{
  sprite_coord_yx_t sVar1;
  undefined3 uVar2;
  
  if (pink_ghost_state != ALIVE) {
    uVar2 = distance_check(pink_ghost_xy_tile_pos,(sprite_coord_yx_t)0x2e2c,pink_ghost_orientation);
    pink_ghost_xy_tile_changes = (sprite_coord_yx_t)(short)uVar2;
    pink_ghost_orientation = (character_orientation_e)((uint3)uVar2 >> 0x10);
    return;
  }
  sVar1 = pink_ghost_xy_tile_pos;
  pink_ghost_orientation = get_best_orientation(pink_ghost_orientation,pink_ghost_xy_tile_pos);
  pink_ghost_xy_tile_changes = sVar1;
  return;
}



void T0E_blue_ghost_movement_when_power_pill(void)

{
  sprite_coord_yx_t sVar1;
  undefined3 uVar2;
  
                    // check blue ghost (inky)
                    // 
  if (blue_ghost_state != ALIVE) {
    uVar2 = distance_check(blue_ghost_xy_tile_pos,(sprite_coord_yx_t)0x2e2c,blue_ghost_orientation);
    blue_ghost_xy_tile_changes = (sprite_coord_yx_t)(short)uVar2;
    blue_ghost_orientation = (character_orientation_e)((uint3)uVar2 >> 0x10);
    return;
  }
  sVar1 = blue_ghost_xy_tile_pos;
  blue_ghost_orientation = get_best_orientation(blue_ghost_orientation,blue_ghost_xy_tile_pos);
  blue_ghost_xy_tile_changes = sVar1;
  return;
}



void T0F_orange_ghost_movement_when_power_pill(void)

{
  sprite_coord_yx_t sVar1;
  undefined3 uVar2;
  
                    // check orange ghost
                    // 
  if (orange_ghost_state != ALIVE) {
    uVar2 = distance_check(orange_ghost_xy_tile_pos,(sprite_coord_yx_t)0x2e2c,
                           orange_ghost_orientation);
    orange_ghost_xy_tile_changes = (sprite_coord_yx_t)(short)uVar2;
    orange_ghost_orientation = (character_orientation_e)((uint3)uVar2 >> 0x10);
    return;
  }
  sVar1 = orange_ghost_xy_tile_pos;
  orange_ghost_orientation = get_best_orientation(orange_ghost_orientation,orange_ghost_xy_tile_pos)
  ;
  orange_ghost_xy_tile_changes = sVar1;
  return;
}



// called from #23A7 for task #17
// arrive here only during demo mode ?
// controls pacman AI during demo mode
// pac-man will avoid the pink ghost normally, except after eating a power pill
// pac-man will chase the pink ghost when the red ghost is blue, even if the pink ghost is not

void T17_pacman_AI_movement_when_demo(void)

{
  undefined3 uVar1;
  
  if (red_ghost_blue_flag != false) {
    uVar1 = distance_check(pacman_tile_pos_in_demo_and_cut_scenes,pink_ghost_xy_tile_pos,
                           wanted_pacman_orientation);
    wanted_pacman_tile_changes = (short)uVar1;
    wanted_pacman_orientation = (character_orientation_e)((uint3)uVar1 >> 0x10);
    return;
  }
                    // pacman will run away from pink ghost
                    // 
  uVar1 = distance_check(pacman_tile_pos_in_demo_and_cut_scenes,
                         (sprite_coord_yx_t)
                         CONCAT11((char)((ushort)pacman_position_tile_position >> 8) * '\x02' -
                                  (char)((ushort)pink_ghost_xy_tile_pos >> 8),
                                  (char)pacman_position_tile_position * '\x02' -
                                  SUB21(pink_ghost_xy_tile_pos,0)),wanted_pacman_orientation);
  wanted_pacman_tile_changes = (short)uVar1;
  wanted_pacman_orientation = (character_orientation_e)((uint3)uVar1 >> 0x10);
  return;
}



// called from routines above with HL loaded with ghost position and A loaded with ghost direction
// used when ghosts are blue (edible)
// load A with new direction, and HL with tile offset for this direction
// 

character_orientation_e
get_best_orientation(character_orientation_e current_orientation,sprite_coord_yx_t ghost_position)

{
  byte rnd;
  sprite_coord_yx_t *seek_location;
  sprite_coord_yx_t *ghost_location;
  
  opposite_orientation = current_orientation ^ 2;
  current_tile_position = ghost_position;
  rnd = random();
  best_orientation_found = rnd & 3;
  seek_location = (sprite_coord_yx_t *)(&move_right.y + (byte)(best_orientation_found * '\x02'));
  ghost_location = &current_tile_position;
  do {
    if (opposite_orientation != best_orientation_found) {
      rnd = get_from_screen_position(ghost_location,seek_location);
      if ((rnd & 0xc0) != 0xc0) {
        return best_orientation_found;
      }
    }
                    // random direction == opposite direction, or a wall is in the way of the
                    // direction computed
    seek_location = seek_location + 1;
    best_orientation_found = best_orientation_found + down & 3;
  } while( true );
}



// distance check - used for ghost logic and for pacman logic in the demo
// this subroutine determines the best direction to take based upon the input.
// DE is preloaded with the destination tile
// HL is preloaded with the current position tile
// A is preloaded with the current direction of the ghost
// the output is the best new direction which is stored into A
// and the best new tile changes stored into HL
// 

uint3 distance_check(sprite_coord_yx_t current_position_tile,sprite_coord_yx_t destination_tile,
                    character_orientation_e orientation)

{
  byte *pbVar1;
  word wVar2;
  sprite_coord_yx_t *seek_location;
  sprite_coord_yx_t *sprite_location;
  
  opposite_orientation = orientation ^ 2;
  minimum_distance_square_found = 0xffff;
  seek_location = &move_right;
  sprite_location = &current_tile_position;
  current_orientation_we_are_trying = right;
  best_orientation_found = orientation;
  current_tile_position = current_position_tile;
  destination_tile_position = destination_tile;
  do {
    if (opposite_orientation != current_orientation_we_are_trying) {
      temp_resulting_position = update_coord(sprite_location,seek_location);
      pbVar1 = convert_xy_to_screen_position(temp_resulting_position);
      if ((*pbVar1 & 0xc0) != 0xc0) {
        wVar2 = get_distance(&temp_resulting_position,&destination_tile_position);
        if (wVar2 <= minimum_distance_square_found) {
          best_orientation_found = current_orientation_we_are_trying;
          minimum_distance_square_found = wVar2;
        }
      }
    }
    seek_location = seek_location + 1;
    current_orientation_we_are_trying = current_orientation_we_are_trying + down;
  } while (current_orientation_we_are_trying != 4);
  return CONCAT12(best_orientation_found,
                  *(undefined2 *)(&move_right.y + (byte)(best_orientation_found * '\x02'))) &
         0x7fffff;
}



// sub called for orange ghost logic and during distance check
// loads HL with the sum of the square of the X and Y distances between pac and ghost
// 

word get_distance(sprite_coord_yx_t *ghost_position,sprite_coord_yx_t *pacman_position)

{
  byte ghost_x_or_y_coord;
  byte delta;
  word square_delta_y;
  word square_delta_x;
  
  ghost_x_or_y_coord = ghost_position->y;
  delta = pacman_position->y - ghost_x_or_y_coord;
  if (pacman_position->y < ghost_x_or_y_coord) {
    delta = ghost_x_or_y_coord - pacman_position->y;
  }
  square_delta_y = square(delta);
  ghost_x_or_y_coord = ghost_position->x;
  delta = pacman_position->x - ghost_x_or_y_coord;
  if (pacman_position->x < ghost_x_or_y_coord) {
    delta = ghost_x_or_y_coord - pacman_position->x;
  }
  square_delta_x = square(delta);
  return square_delta_x + square_delta_y;
}



// takes the value in A and squares it, places result into HL

word square(byte value)

{
  char cVar1;
  ushort uVar2;
  word return_value;
  
  cVar1 = '\b';
  uVar2 = (ushort)value << 8;
  do {
    return_value = uVar2 * 2;
    if (CARRY2(uVar2,uVar2) != false) {
      return_value = return_value + value;
    }
    cVar1 = cVar1 + -1;
    uVar2 = return_value;
  } while (cVar1 != '\0');
  return return_value;
}



// Random number generator
// 
// random number generator, only active when ghosts are blue.
// n=(n*5+1) && #1fff.  n is used as an address to read a byte from a rom.
// #4dc9, #4dca=n  and a=rnd number. n is reset to 0 at #26a9 when you die,
// start of first level, end of every level.  Later a is anded with 3.
// 
// ...pick a random value from the ROM

byte random(void)

{
  pointer_to_pick_a_random_value_from_the_ROM =
       pointer_to_pick_a_random_value_from_the_ROM * 5 + 1 & 0x1fff;
  return *(byte *)pointer_to_pick_a_random_value_from_the_ROM;
}



// WARNING: Unknown calling convention yet parameter storage is locked

void T13_clears_sprites(void)

{
  byte bVar1;
  byte *pbVar2;
  
  pbVar2 = hardware_screen_maze_area;
  while (pbVar2 != sprites_related_stuff2) {
    bVar1 = *pbVar2;
    if (((bVar1 == 0x10) || (bVar1 == 0x12)) || (bVar1 == 0x14)) {
      *pbVar2 = 0x40;
      pbVar2 = pbVar2 + 1;
    }
    else {
      pbVar2 = pbVar2 + 1;
    }
  }
  return;
}



// arrive here from #1780 when a ghost is eaten.
// B contains the # of ghosts eaten +1 (2-5)
// or arrive from #23A7 for a task
// B is loaded with code of scoring item

void T19_update_score_then_draw(undefined2 param_1)

{
  bool bVar1;
  bool bVar2;
  byte bVar3;
  bool bVar4;
  bool bVar5;
  byte bVar6;
  byte bVar7;
  byte bVar8;
  char cVar10;
  short sVar9;
  byte *pbVar11;
  undefined2 uVar12;
  byte *pbVar13;
  byte *pbVar14;
  dereference_word_t dVar15;
  
  if (game_mode == DEMO) {
    return;
  }
                    // this updates the score when something is eaten
                    // (from the table at 2b17)
                    // A is loaded with the code for item eaten
                    // 
  dVar15 = dereference_pointer_to_word(&score_table,(byte)((ushort)param_1 >> 8));
  uVar12 = (undefined2)((uint5)dVar15 >> 0x18);
  pbVar13 = (byte *)((uint5)dVar15 >> 8);
  get_score_from_current_player(SUB51(dVar15,0));
  bVar7 = (byte)uVar12;
  bVar8 = *pbVar13;
  bVar6 = bVar7 + bVar8;
  bVar1 = ((bVar7 & 0xf) + (bVar8 & 0xf) & 0x10) != 0;
  bVar4 = CARRY1(bVar7,bVar8);
  if (true) {
    bVar7 = BCDadjust(bVar6,bVar4,bVar1);
    bVar8 = BCDadjustCarry(bVar6,bVar4,bVar1);
    bVar4 = (bool)(bVar8 & 0x3b);
    hasEvenParity(bVar7);
    bVar6 = bVar7;
  }
  else {
    bVar8 = bVar6 >> 4;
    bVar7 = bVar6 & 0xf;
    if (((bVar4 != false || bVar1) || 9 < bVar8) || 9 < bVar7) {
      if (false) {
        if ((((bVar4 == false && bVar1) && bVar8 < 9) && 5 < bVar7) && bVar7 < 0x10) {
          bVar6 = bVar6 - 6;
        }
        else {
          if ((((bVar4 == true && !bVar1) && 6 < bVar8) && bVar8 < 0x10) && bVar7 < 10) {
            bVar6 = bVar6 + 0xa0;
          }
          else {
            if (((((bVar4 == true && bVar1) && 5 < bVar8) && bVar8 < 0x10) && 5 < bVar7) &&
                bVar7 < 0x10) {
              bVar6 = bVar6 + 0x9a;
            }
          }
        }
      }
      else {
        if ((((bVar4 == false && !bVar1) && bVar8 < 9) && 9 < bVar7) && bVar7 < 0x10) {
          bVar6 = bVar6 + 6;
        }
        else {
          if (((bVar4 == false && bVar1) && bVar8 < 10) && bVar7 < 4) {
            bVar6 = bVar6 + 6;
          }
          else {
            if ((((bVar4 == false && !bVar1) && 9 < bVar8) && bVar8 < 0x10) && bVar7 < 10) {
              bVar6 = bVar6 + 0x60;
              bVar4 = true;
            }
            else {
              if (((((bVar4 == false && !bVar1) && 8 < bVar8) && bVar8 < 0x10) && 9 < bVar7) &&
                  bVar7 < 0x10) {
                bVar6 = bVar6 + 0x66;
                bVar4 = true;
              }
              else {
                if ((((bVar4 == false && bVar1) && 9 < bVar8) && bVar8 < 0x10) && bVar7 < 4) {
                  bVar6 = bVar6 + 0x66;
                  bVar4 = true;
                }
                else {
                  if (((bVar4 == true && !bVar1) && bVar8 < 3) && bVar7 < 10) {
                    bVar6 = bVar6 + 0x60;
                  }
                  else {
                    if ((((bVar4 == true && !bVar1) && bVar8 < 3) && 9 < bVar7) && bVar7 < 0x10) {
                      bVar6 = bVar6 + 0x66;
                    }
                    else {
                      if (((bVar4 == true && bVar1) && bVar8 < 4) && bVar7 < 4) {
                        bVar6 = bVar6 + 0x66;
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  *pbVar13 = bVar6;
  bVar7 = (byte)((ushort)uVar12 >> 8);
  bVar8 = pbVar13[1];
  bVar6 = bVar4 & 1;
  bVar1 = ((bVar7 & 0xf) + (bVar8 & 0xf) + bVar6 & 0x10) != 0;
  bVar4 = CARRY1(bVar7,bVar8);
  bVar2 = CARRY1(bVar7 + bVar8,bVar6);
  bVar5 = bVar4 || bVar2;
  bVar6 = bVar7 + bVar8 + bVar6;
  if (true) {
    bVar7 = BCDadjust(bVar6,bVar5,bVar1);
    bVar8 = BCDadjustCarry(bVar6,bVar5,bVar1);
    bVar5 = (bool)(bVar8 & 0x3b);
    hasEvenParity(bVar7);
    bVar6 = bVar7;
  }
  else {
    bVar8 = bVar6 >> 4;
    bVar7 = bVar6 & 0xf;
    if ((((bVar4 || bVar2) || bVar1) || 9 < bVar8) || 9 < bVar7) {
      if (false) {
        if (((((!bVar4 && !bVar2) && bVar1) && bVar8 < 9) && 5 < bVar7) && bVar7 < 0x10) {
          bVar6 = bVar6 - 6;
        }
        else {
          if ((((bVar5 && !bVar1) && 6 < bVar8) && bVar8 < 0x10) && bVar7 < 10) {
            bVar6 = bVar6 + 0xa0;
          }
          else {
            if (((((bVar5 && bVar1) && 5 < bVar8) && bVar8 < 0x10) && 5 < bVar7) && bVar7 < 0x10) {
              bVar6 = bVar6 + 0x9a;
            }
          }
        }
      }
      else {
        if (((((bVar4 || bVar2) || bVar1) || 8 < bVar8) || bVar7 < 10) || 0xf < bVar7) {
          if ((((!bVar4 && !bVar2) && bVar1) && bVar8 < 10) && bVar7 < 4) {
            bVar6 = bVar6 + 6;
          }
          else {
            if (((((bVar4 || bVar2) || bVar1) || bVar8 < 10) || 0xf < bVar8) || 9 < bVar7) {
              if ((((((bVar4 || bVar2) || bVar1) || bVar8 < 9) || 0xf < bVar8) || bVar7 < 10) ||
                  0xf < bVar7) {
                if (((((!bVar4 && !bVar2) && bVar1) && 9 < bVar8) && bVar8 < 0x10) && bVar7 < 4) {
                  bVar6 = bVar6 + 0x66;
                  bVar5 = true;
                }
                else {
                  if (((bVar5 && !bVar1) && bVar8 < 3) && bVar7 < 10) {
                    bVar6 = bVar6 + 0x60;
                  }
                  else {
                    if ((((bVar5 && !bVar1) && bVar8 < 3) && 9 < bVar7) && bVar7 < 0x10) {
                      bVar6 = bVar6 + 0x66;
                    }
                    else {
                      if (((bVar5 && bVar1) && bVar8 < 4) && bVar7 < 4) {
                        bVar6 = bVar6 + 0x66;
                      }
                    }
                  }
                }
              }
              else {
                bVar6 = bVar6 + 0x66;
                bVar5 = true;
              }
            }
            else {
              bVar6 = bVar6 + 0x60;
              bVar5 = true;
            }
          }
        }
        else {
          bVar6 = bVar6 + 6;
        }
      }
    }
  }
  pbVar13[1] = bVar6;
  pbVar13 = pbVar13 + 2;
  bVar8 = *pbVar13;
  bVar7 = bVar5 & 1;
  bVar1 = ((bVar8 & 0xf) + bVar7 & 0x10) != 0;
  bVar4 = CARRY1(bVar8,bVar7);
  bVar8 = bVar8 + bVar7;
  if (true) {
    bVar7 = BCDadjust(bVar8,bVar4,bVar1);
    BCDadjustCarry(bVar8,bVar4,bVar1);
    hasEvenParity(bVar7);
    bVar8 = bVar7;
  }
  else {
    bVar7 = bVar8 >> 4;
    bVar3 = bVar8 & 0xf;
    if (((bVar4 != false || bVar1) || 9 < bVar7) || 9 < bVar3) {
      if (false) {
        if ((((bVar4 == false && bVar1) && bVar7 < 9) && 5 < bVar3) && bVar3 < 0x10) {
          bVar8 = bVar8 - 6;
        }
        else {
          if ((((bVar4 == true && !bVar1) && 6 < bVar7) && bVar7 < 0x10) && bVar3 < 10) {
            bVar8 = bVar8 + 0xa0;
          }
          else {
            if (((((bVar4 == true && bVar1) && 5 < bVar7) && bVar7 < 0x10) && 5 < bVar3) &&
                bVar3 < 0x10) {
              bVar8 = bVar8 + 0x9a;
            }
          }
        }
      }
      else {
        if ((((bVar4 == false && !bVar1) && bVar7 < 9) && 9 < bVar3) && bVar3 < 0x10) {
          bVar8 = bVar8 + 6;
        }
        else {
          if (((bVar4 == false && bVar1) && bVar7 < 10) && bVar3 < 4) {
            bVar8 = bVar8 + 6;
          }
          else {
            if ((((bVar4 == false && !bVar1) && 9 < bVar7) && bVar7 < 0x10) && bVar3 < 10) {
              bVar8 = bVar8 + 0x60;
            }
            else {
              if (((((bVar4 == false && !bVar1) && 8 < bVar7) && bVar7 < 0x10) && 9 < bVar3) &&
                  bVar3 < 0x10) {
                bVar8 = bVar8 + 0x66;
              }
              else {
                if ((((bVar4 == false && bVar1) && 9 < bVar7) && bVar7 < 0x10) && bVar3 < 4) {
                  bVar8 = bVar8 + 0x66;
                }
                else {
                  if (((bVar4 == true && !bVar1) && bVar7 < 3) && bVar3 < 10) {
                    bVar8 = bVar8 + 0x60;
                  }
                  else {
                    if ((((bVar4 == true && !bVar1) && bVar7 < 3) && 9 < bVar3) && bVar3 < 0x10) {
                      bVar8 = bVar8 + 0x66;
                    }
                    else {
                      if (((bVar4 == true && bVar1) && bVar7 < 4) && bVar3 < 4) {
                        bVar8 = bVar8 + 0x66;
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  *pbVar13 = bVar8;
  if ((byte)(bonus_life - 1) < (byte)((ushort)(CONCAT11(bVar8,bVar6) * 0x10) >> 8)) {
    check_for_extra_life();
  }
  draw_player_score_on_screen();
  pbVar13 = pbVar13 + 3;
                    // check for high score change
                    // 
  pbVar14 = high_score + 2;
  cVar10 = '\x03';
  while( true ) {
    if (*pbVar13 < *pbVar14) {
      return;
    }
    if (*pbVar13 != *pbVar14) break;
    pbVar13 = pbVar13 + -1;
    pbVar14 = pbVar14 + -1;
    cVar10 = cVar10 + -1;
    if (cVar10 == '\0') {
      return;
    }
  }
                    // arrive when player score beats the current high score
                    // 
  get_score_from_current_player();
  sVar9 = 3;
  pbVar13 = high_score;
  do {
    pbVar11 = pbVar13;
    *pbVar11 = *pbVar14;
    pbVar14 = pbVar14 + 1;
    sVar9 = sVar9 + -1;
    pbVar13 = pbVar11 + 1;
  } while (sVar9 != 0);
  draw_score_to_screen(0x304,pbVar11);
  return;
}



void draw_player_score_on_screen(byte *param_1)

{
  byte bVar1;
  char cVar2;
  
                    // called from #2A86
                    // 
  cVar2 = '\x03';
  do {
    bVar1 = *param_1 >> 1;
    draw_digit_to_screen
              ((((bVar1 | *param_1 << 7) >> 1 | bVar1 << 7) >> 1 | ((bVar1 & 2) >> 1) << 7) >> 1 |
               ((bVar1 & 4) >> 2) << 7);
    draw_digit_to_screen(*param_1);
    param_1 = param_1 + -1;
    cVar2 = cVar2 + -1;
  } while (cVar2 != '\0');
  return;
}



void draw_score_to_screen(short param_1,byte *param_2)

{
  byte bVar1;
  char cVar2;
  
  do {
    cVar2 = (char)((ushort)param_1 >> 8);
                    //  draw the score to the screen
                    // DE has the address of msb of the score
                    // HL has starting screen position
                    // B has #03, and C has #04 or #06
                    // 
    bVar1 = *param_2 >> 1;
    draw_digit_to_screen
              ((((bVar1 | *param_2 << 7) >> 1 | bVar1 << 7) >> 1 | ((bVar1 & 2) >> 1) << 7) >> 1 |
               ((bVar1 & 4) >> 2) << 7);
    draw_digit_to_screen(*param_2);
    param_2 = param_2 + -1;
    param_1 = (ushort)(byte)(cVar2 - 1U) << 8;
  } while ((byte)(cVar2 - 1U) != 0);
  return;
}



void draw_digit_to_screen(byte param_1,byte param_2,byte *param_3)

{
  param_1 = param_1 & 0xf;
  if ((param_1 == 0) && (param_1 = param_2, param_2 != 0)) {
    param_1 = 0x40;
  }
  *param_3 = param_1;
  return;
}



// prints "high score", player 1 and player 2 score
// this is task #18 called from #23A7

void T18_print_high_score_text_then_players_score(void)

{
  byte bVar1;
  char cVar2;
  byte *pbVar3;
  
  DrawText(HIGH_SCORE);
  memset(score_P1,0,8);
  draw_score_to_screen(0x304,score_P1 + 2);
  cVar2 = '\x03';
  pbVar3 = score_P2 + 2;
  if (number_of_players == 0) {
    draw_score_to_screen(0x306,score_P2 + 2);
    return;
  }
  do {
    bVar1 = *pbVar3 >> 1;
    draw_digit_to_screen
              ((((bVar1 | *pbVar3 << 7) >> 1 | bVar1 << 7) >> 1 | ((bVar1 & 2) >> 1) << 7) >> 1 |
               ((bVar1 & 4) >> 2) << 7);
    draw_digit_to_screen(*pbVar3);
    pbVar3 = pbVar3 + -1;
    cVar2 = cVar2 + -1;
  } while (cVar2 != '\0');
  return;
}



// called from #2A65, #2A9B

void get_score_from_current_player(void)

{
  if (current_player_number == 0) {
    return;
  }
  return;
}



// [The 8th fruit is a legacy thing from pacman, which used 8 bonus items. it is not used in mspac]
// 
// arrive here from #2A83 when checking for extra life
// DE has the address of the third byte of the player's score
// 

void check_for_extra_life(short param_1)

{
  char cVar1;
  byte bVar2;
  byte *pbVar3;
  
  pbVar3 = (byte *)(param_1 + 1);
  if ((*pbVar3 & 1) != 0) {
    return;
  }
                    // else start bonus life routine
                    // 
  *pbVar3 = *pbVar3 | 1;
  channel_1_effect.num = channel_1_effect.num | 1;
  real_number_of_lives = real_number_of_lives + 1;
  bVar2 = number_of_lives_displayed + 1;
  pbVar3 = hardware_video_ram + 0x1a;
  cVar1 = '\x05';
  number_of_lives_displayed = bVar2;
  if ((bVar2 != 0) && (bVar2 < 6)) {
    do {
      draw_extra_life(' ',(char *)pbVar3);
      pbVar3 = pbVar3 + -2;
      cVar1 = cVar1 + -1;
      bVar2 = bVar2 - 1;
    } while (bVar2 != 0);
  }
  while (cVar1 = cVar1 + -1, -1 < cVar1) {
    draw_blank_for_next_extra_life(pbVar3);
    pbVar3 = pbVar3 + -2;
  }
  return;
}



// draw remaining lives at bottom of screen

void T1A_draw_remaining_lives_bottom_screen(byte param_1,ushort param_2,undefined *param_3)

{
  main_state_e mVar1;
  char cVar2;
  char cVar3;
  byte bVar5;
  undefined *puVar4;
  byte *pbVar6;
  
  if (game_mode == DEMO) {
    return;
  }
  mVar1 = game_mode;
  colors_the_bottom_two_rows_of_10_the_color_9_yellow((undefined *)0x2b73);
  *param_3 = mVar1;
  puVar4 = (undefined *)(param_2 & 0xff00 | (ushort)param_1);
  *puVar4 = *puVar4;
  pbVar6 = hardware_video_ram + 0x1a;
  cVar2 = '\x05';
  cVar3 = '\x05';
  if ((number_of_lives_displayed != 0) &&
     (bVar5 = number_of_lives_displayed, cVar3 = cVar2, number_of_lives_displayed < 6)) {
    do {
      draw_extra_life(' ',(char *)pbVar6);
      pbVar6 = pbVar6 + -2;
      cVar2 = cVar2 + -1;
      bVar5 = bVar5 - 1;
      cVar3 = cVar2;
    } while (bVar5 != 0);
  }
  while (cVar3 = cVar3 + -1, -1 < cVar3) {
    draw_blank_for_next_extra_life(pbVar6);
    pbVar6 = pbVar6 + -2;
  }
  return;
}



void draw_blank_for_next_extra_life(undefined *param_1)

{
                    // Draws colors onscreen for a 2x2 grid.
                    // It requires that A is loaded with the code for the color,
                    // and HL is loaded with the memory address of the position on screen where the
                    // first color is to be drawn.
                    // If a clear value is to be drawn, the first address is called (#2B7E).
                    // If A is preloaded with a color, then the second address is called (#2B80).
                    // 
  *param_1 = 0x40;
  param_1[1] = 0x40;
  param_1[0x20] = 0x40;
  param_1[0x21] = 0x40;
  return;
}



void draw_color_subroutine(undefined param_1,undefined *param_2)

{
  *param_2 = param_1;
  param_2[1] = param_1;
  param_2[0x20] = param_1;
  param_2[0x21] = param_1;
  return;
}



void draw_extra_life(char param_1,char *param_2)

{
                    // Draws the four parts of a fruit onscreen.  Also used to draw extra pac man
                    // lives at bottom of screen.
                    // It requires that A is loaded with the code for the first part of the fruit,
                    // and HL is loaded with the memory address of the first position on screen
                    // where it is to be drawn.
                    // 
  *param_2 = param_1;
  param_2[1] = param_1 + '\x01';
  param_2[0x20] = param_1 + '\x02';
  param_2[0x21] = param_1 + '\x03';
  return;
}



void T1D_draw_credit_qty(undefined param_1)

{
                    //  display number of credits
                    // 
  if (number_of_credits_xff_for_free_play == 0xff) {
    DrawText(FREE_PLAY_2);
    return;
  }
  DrawText(CREDIT);
  if ((number_of_credits_xff_for_free_play & 0xf0) != 0) {
    hardware_video_ram[1][20] = (number_of_credits_xff_for_free_play >> 4) + 0x30;
  }
  hardware_video_ram[1][19] = (number_of_credits_xff_for_free_play & 0xf) + 0x30;
  return;
}



// this subroutine takes 5 bytes after the call and uses them to copy the 3rd byte into several
// memories first 2 bytes are the initial address to copy into called from #2B70 to color the bottom
// area yellow where extra lives are drawn
// 

void colors_the_bottom_two_rows_of_10_the_color_9_yellow(undefined *args)

{
  ushort uVar1;
  char nb_rows;
  ushort uVar2;
  byte bVar3;
  undefined *ptr_;
  undefined *ptr;
  
  ptr = *(undefined **)args;
  uVar1 = *(ushort *)(args + 2);
  nb_rows = args[4];
  uVar2 = uVar1;
  ptr_ = ptr;
  do {
    do {
      *ptr = (char)uVar2;
      ptr = ptr + 1;
      bVar3 = (char)(uVar2 >> 8) - 1;
      uVar2 = uVar2 & 0xff | (ushort)bVar3 << 8;
    } while (bVar3 != 0);
    ptr = ptr_ + 0x20;
    nb_rows = nb_rows + -1;
    uVar2 = uVar1;
    ptr_ = ptr;
  } while (nb_rows != '\0');
  return;
}



void T1B_draw_fruits_right_screen(void)

{
  byte bVar1;
  char cVar2;
  fruit_t *pfVar3;
  byte *pbVar4;
  undefined *puVar5;
  
                    // called from #23A7 as task #1B
                    // called from #0792
                    // 
  if (game_mode == DEMO) {
    return;
  }
                    //  draw the fruit
                    // 
  bVar1 = current_level + 1;
                    // jumped from #2BF4 for fruit drawing subroutine
                    // A has the level number
                    // keeps the fruit level at banana after level 7
                    // 
  if (7 < bVar1) {
    bVar1 = 7;
  }
  pfVar3 = fruit_table;
  cVar2 = '\a';
  pbVar4 = hardware_video_ram + 4;
  do {
    draw_extra_life(pfVar3->sprit_number,(char *)pbVar4);
    puVar5 = (undefined *)
             ((ushort)pbVar4 & 0xff | (ushort)(byte)((char)((ushort)pbVar4 >> 8) + 4) << 8);
    pbVar4 = &pfVar3->color;
    draw_color_subroutine(*pbVar4,puVar5);
    pfVar3 = (fruit_t *)(pbVar4 + 1);
    pbVar4 = (byte *)(((ushort)puVar5 & 0xff | (ushort)(byte)((char)((ushort)puVar5 >> 8) - 4) << 8)
                     + 2);
    cVar2 = cVar2 + -1;
    bVar1 = bVar1 - 1;
  } while (bVar1 != 0);
  while (cVar2 = cVar2 + -1, -1 < cVar2) {
    draw_blank_for_next_extra_life(pbVar4);
    puVar5 = (undefined *)
             ((ushort)pbVar4 & 0xff | (ushort)(byte)((char)((ushort)pbVar4 >> 8) + 4) << 8);
    draw_color_subroutine(0,puVar5);
    pbVar4 = (byte *)(((ushort)puVar5 & 0xff | (ushort)(byte)((char)((ushort)puVar5 >> 8) - 4) << 8)
                     + 2);
  }
  return;
}



byte FUN_ram_2c44(byte param_1)

{
  bool bVar1;
  bool bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  
                    // unknown subroutine [unused ???]
                    // can't find a call to here
                    // 
  bVar5 = param_1 & 0xf;
  if (true) {
    bVar6 = BCDadjust(bVar5,0,0);
    BCDadjustCarry(bVar5,0,0);
    hasEvenParity(bVar6);
    bVar5 = bVar6;
  }
  else {
    if (9 < bVar5) {
      if (false) {
        if (false) {
          bVar5 = bVar5 - 6;
        }
        else {
          if (false) {
            bVar5 = bVar5 + 0xa0;
          }
          else {
            if (false) {
              bVar5 = bVar5 + 0x9a;
            }
          }
        }
      }
      else {
        if (bVar5 < 10 || 0xf < bVar5) {
          if (false) {
            bVar5 = bVar5 + 6;
          }
          else {
            if (false) {
              bVar5 = bVar5 + 0x60;
            }
            else {
              if (false) {
                bVar5 = bVar5 + 0x66;
              }
              else {
                if (false) {
                  bVar5 = bVar5 + 0x66;
                }
                else {
                  if (false) {
                    bVar5 = bVar5 + 0x60;
                  }
                  else {
                    if (false) {
                      bVar5 = bVar5 + 0x66;
                    }
                    else {
                      if (false) {
                        bVar5 = bVar5 + 0x66;
                      }
                    }
                  }
                }
              }
            }
          }
        }
        else {
          bVar5 = bVar5 + 6;
        }
      }
    }
  }
  bVar6 = param_1 & 0xf0;
  if (bVar6 != 0) {
    param_1 = param_1 >> 4;
    bVar7 = 0;
    do {
      bVar6 = bVar7 + 0x16;
      bVar1 = ((bVar7 & 0xf) + 6 & 0x10) != 0;
      bVar2 = 0xe9 < bVar7;
      if (true) {
        bVar7 = BCDadjust(bVar6,bVar2,bVar1);
        BCDadjustCarry(bVar6,bVar2,bVar1);
        hasEvenParity(bVar7);
        bVar6 = bVar7;
      }
      else {
        bVar3 = bVar6 >> 4;
        bVar4 = bVar6 & 0xf;
        if (((bVar2 || bVar1) || 9 < bVar3) || 9 < bVar4) {
          if (false) {
            if ((((!bVar2 && bVar1) && bVar3 < 9) && 5 < bVar4) && bVar4 < 0x10) {
              bVar6 = bVar7 + 0x10;
            }
            else {
              if ((((bVar2 && !bVar1) && 6 < bVar3) && bVar3 < 0x10) && bVar4 < 10) {
                bVar6 = bVar7 + 0xb6;
              }
              else {
                if (((((bVar2 && bVar1) && 5 < bVar3) && bVar3 < 0x10) && 5 < bVar4) && bVar4 < 0x10
                   ) {
                  bVar6 = bVar7 + 0xb0;
                }
              }
            }
          }
          else {
            if ((((bVar2 || bVar1) || 8 < bVar3) || bVar4 < 10) || 0xf < bVar4) {
              if (((!bVar2 && bVar1) && bVar3 < 10) && bVar4 < 4) {
                bVar6 = bVar7 + 0x1c;
              }
              else {
                if ((((bVar2 || bVar1) || bVar3 < 10) || 0xf < bVar3) || 9 < bVar4) {
                  if (((((bVar2 || bVar1) || bVar3 < 9) || 0xf < bVar3) || bVar4 < 10) ||
                      0xf < bVar4) {
                    if ((((!bVar2 && bVar1) && 9 < bVar3) && bVar3 < 0x10) && bVar4 < 4) {
                      bVar6 = bVar7 + 0x7c;
                    }
                    else {
                      if (((bVar2 && !bVar1) && bVar3 < 3) && bVar4 < 10) {
                        bVar6 = bVar7 + 0x76;
                      }
                      else {
                        if ((((bVar2 && !bVar1) && bVar3 < 3) && 9 < bVar4) && bVar4 < 0x10) {
                          bVar6 = bVar7 + 0x7c;
                        }
                        else {
                          if (((bVar2 && bVar1) && bVar3 < 4) && bVar4 < 4) {
                            bVar6 = bVar7 + 0x7c;
                          }
                        }
                      }
                    }
                  }
                  else {
                    bVar6 = bVar7 + 0x7c;
                  }
                }
                else {
                  bVar6 = bVar7 + 0x76;
                }
              }
            }
            else {
              bVar6 = bVar7 + 0x1c;
            }
          }
        }
      }
      param_1 = param_1 - 1;
      bVar7 = bVar6;
    } while (param_1 != 0);
  }
  bVar7 = bVar6 + bVar5;
  bVar1 = ((bVar6 & 0xf) + (bVar5 & 0xf) & 0x10) != 0;
  bVar2 = CARRY1(bVar6,bVar5);
  if (true) {
    bVar5 = BCDadjust(bVar7,bVar2,bVar1);
    BCDadjustCarry(bVar7,bVar2,bVar1);
    hasEvenParity(bVar5);
    bVar7 = bVar5;
  }
  else {
    bVar5 = bVar7 >> 4;
    bVar6 = bVar7 & 0xf;
    if (((bVar2 != false || bVar1) || 9 < bVar5) || 9 < bVar6) {
      if (false) {
        if ((((bVar2 == false && bVar1) && bVar5 < 9) && 5 < bVar6) && bVar6 < 0x10) {
          bVar7 = bVar7 - 6;
        }
        else {
          if ((((bVar2 == true && !bVar1) && 6 < bVar5) && bVar5 < 0x10) && bVar6 < 10) {
            bVar7 = bVar7 + 0xa0;
          }
          else {
            if (((((bVar2 == true && bVar1) && 5 < bVar5) && bVar5 < 0x10) && 5 < bVar6) &&
                bVar6 < 0x10) {
              bVar7 = bVar7 + 0x9a;
            }
          }
        }
      }
      else {
        if ((((bVar2 == false && !bVar1) && bVar5 < 9) && 9 < bVar6) && bVar6 < 0x10) {
          bVar7 = bVar7 + 6;
        }
        else {
          if (((bVar2 == false && bVar1) && bVar5 < 10) && bVar6 < 4) {
            bVar7 = bVar7 + 6;
          }
          else {
            if ((((bVar2 == false && !bVar1) && 9 < bVar5) && bVar5 < 0x10) && bVar6 < 10) {
              bVar7 = bVar7 + 0x60;
            }
            else {
              if (((((bVar2 == false && !bVar1) && 8 < bVar5) && bVar5 < 0x10) && 9 < bVar6) &&
                  bVar6 < 0x10) {
                bVar7 = bVar7 + 0x66;
              }
              else {
                if ((((bVar2 == false && bVar1) && 9 < bVar5) && bVar5 < 0x10) && bVar6 < 4) {
                  bVar7 = bVar7 + 0x66;
                }
                else {
                  if (((bVar2 == true && !bVar1) && bVar5 < 3) && bVar6 < 10) {
                    bVar7 = bVar7 + 0x60;
                  }
                  else {
                    if ((((bVar2 == true && !bVar1) && bVar5 < 3) && 9 < bVar6) && bVar6 < 0x10) {
                      bVar7 = bVar7 + 0x66;
                    }
                    else {
                      if (((bVar2 == true && bVar1) && bVar5 < 4) && bVar6 < 4) {
                        bVar7 = bVar7 + 0x66;
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return bVar7;
}



void DrawText(byte index)

{
  byte bVar1;
  short sVar2;
  byte bVar3;
  char cVar4;
  short sVar5;
  short *psVar6;
  byte *pbVar7;
  byte *pbVar8;
  char *pcVar9;
  dereference_word_t dVar10;
  
  dVar10 = dereference_pointer_to_word((word *)&text_lookup_table,index);
  psVar6 = (short *)((uint5)dVar10 >> 0x18);
                    // 1. get start offset into vid/color buffer
                    // load two bytes in as a pointer
                    // indexOffset = de
                    // 
                    // 2. use offset for start of color, save to stack
                    // ix = 0x4400 + indexOffset
                    // 
  pbVar8 = hardware_color_ram + *psVar6;
                    // 3. use offset for start of character ram
                    // ix = characterRam + indexOffset
                    // de
                    // if (hl) & 0x80 then offsetPerCharacter = -0x20
                    // 
                    // TODO: IX = hardware_video_ram
                    // 
  pcVar9 = (char *)(*psVar6 + 0x4000);
  sVar5 = -1;
                    // it should be noted that since the high bit on the offset address
                    // is used to denote that the string goes into the top or bottom
                    // two rows, it ends up relying on the unused ram mirroring.
                    // that is to say that it actually ends up drawing up around C000
                    // instead of 4000.  A patch is below as HACK12
                    // (this skips the offsetPerCharacter with -20 if necessary)
                    // 
  if ((*(byte *)((short)psVar6 + 1) & 0x80) == 0) {
    sVar5 = -32;
  }
  psVar6 = psVar6 + 1;
  sVar2 = 0;
  if (CARRY1(index,index)) {
    while (cVar4 = (char)((ushort)sVar2 >> 8), *(char *)psVar6 != '/'
                    // character = *characterToDraw
                    // if( color = 0x2f ) goto FinishUpBlankTextDraw
                    // characterRam[ix] = 0x40 ("@", which is '' in Pac-Man)
                    // characterToDraw++
                    // b++
                    // ) {
      *pcVar9 = '@';
      psVar6 = (short *)((short)psVar6 + 1);
      pcVar9 = pcVar9 + sVar5;
      sVar2 = (ushort)(byte)(cVar4 + 1) << 8;
    }
                    // while (*hl != 0x2f) hl++
                    // goto SingleOrMultiColorCheck +1
                    // 
    pbVar7 = (byte *)((short)psVar6 + 1);
    sVar2 = (ushort)(byte)(cVar4 + 1) << 8;
    do {
      bVar1 = *pbVar7;
      pbVar7 = pbVar7 + 1;
      sVar2 = sVar2 + -1;
    } while (bVar1 == 0x2f || sVar2 != 0);
  }
  else {
    while (*(char *)psVar6 != '/'
                    // 'a' = (hl)
                    // if ch == 0x2f, goto SingleOrMultiColorCheck:
                    // ram[ix+0] = 'a'
                    // (+= but it really subtracts 1 or 0x20, contents of 'de')
                    // 'b'++
                    // goto textRenderLoop0
                    // ) {
      *pcVar9 = *(char *)psVar6;
      psVar6 = (short *)((short)psVar6 + 1);
      pcVar9 = pcVar9 + sVar5;
      sVar2 = (ushort)(byte)((char)((ushort)sVar2 >> 8) + 1) << 8;
    }
                    // ix = startColorRamPos
                    // 
    pbVar7 = (byte *)((short)psVar6 + 1);
  }
                    // color = *colorToUse
                    // if (color) is > 80, goto TextSingleColorRender
                    // 
  bVar1 = *pbVar7;
  if ((char)bVar1 < '\0') {
    do {
                    //  same as above, but all the same color
                    // colorRam[ix] = color
                    // move ix to the next screen position( -=1 or -=0x20)
                    // if b>0 then goto TextSingleColorRender
                    // return
                    // 
      *pbVar8 = bVar1;
      pbVar8 = pbVar8 + sVar5;
      bVar3 = (char)((ushort)sVar2 >> 8) - 1;
      sVar2 = (ushort)bVar3 << 8;
    } while (bVar3 != 0);
    return;
  }
  do {
                    // color = *colorToUse
                    // colorToUse++
                    // move ix to the next screen position ( -=1 or -=0x20)
                    // if b>0 then goto TextMultiColorRender
                    // return
                    // 
    *pbVar8 = *pbVar7;
    pbVar7 = pbVar7 + 1;
    pbVar8 = pbVar8 + sVar5;
    bVar1 = (char)((ushort)sVar2 >> 8) - 1;
    sVar2 = (ushort)bVar1 << 8;
  } while (bVar1 != 0);
  return;
}



// ;; HACK12 - fixes the C000 top/bottom draw mirror issue
// ; 2c62  c300d0 jp hack12
// 
// ; hack12:   ;;; up at 0xd000 for this example
// ; d000  5e        ld e, (hl)  ; patch (2c62)
// ; d001  23        inc hl  ; patch (2c63)
// ; d002  7e        ld a, (hl)  ; patch (2c64 almost)
// ; d003  e67f      and #0x7f  ; mask off the top/bottom flag
// ; d005  57        ld d, a  ; d cleared of that bit now (C000-safe!)
// ; d006  7e        ld a, (hl)  ; set aside A for part 2, below
// ; d007  c3652c    jp #2c65  ; resume
// 
// 
// PROCESS WAVE (all voices) (SOUND)
// called from #01BC
// 

void backup_sprites__then__check_cocktail_animation_end__then__mspacman_channel_1_song_table(void)

{
  byte bVar1;
  short sVar2;
  hardware_floating_sprite_t *phVar3;
  hardware_floating_sprite_t *phVar4;
  
  if (intermission_mode != false) {
    phVar3 = &red_ghost_sprite;
    phVar4 = &sprites_copy;
    sVar2 = 0xc;
    do {
      *(undefined *)phVar3 = *(undefined *)phVar4;
      phVar3 = (hardware_floating_sprite_t *)&phVar3->color;
      phVar4 = (hardware_floating_sprite_t *)&phVar4->color;
      sVar2 = sVar2 + -1;
    } while (sVar2 != 0);
  }
  if (((current_player_number & cocktail_mode) != 0) && (mspac_sprite._0_1_ == '?')) {
    mspac_sprite._0_1_ = -1;
  }
  bVar1 = process_wave_one_voice
                    ((undefined ***)mspacman_channel_1_song_table,
                     (sound_channel_16bits_t *)&channel1,&channel_1_wave);
  if (channel_1_wave.num != 0) {
    channel1.vol = bVar1;
  }
  bVar1 = process_wave_one_voice
                    ((undefined ***)mspacman_channel_2_song_table,&channel2,&channel_2_wave);
  if (channel_2_wave.num != 0) {
    channel2.vol = bVar1;
  }
  bVar1 = process_wave_one_voice
                    ((undefined ***)mspacman_channel_3_song_table,&channel3,&channel_3_wave);
  if (channel_3_wave.num != 0) {
    channel3.vol = bVar1;
    return;
  }
  return;
}



// PROCESS EFFECT (all voices)

void process_effect_all_voices(void)

{
  channel1.vol = process_effect_one_voice
                           (channel_1_two_effects,(sound_channel_16bits_t *)&channel1,
                            &channel_1_effect);
  channel2.vol = process_effect_one_voice(channel_2_height_effects,&channel2,&channel_2_effect);
  channel3.vol = process_effect_one_voice(channel_3_six_effects,&channel3,&channel_3_effect);
  channel1.freq4 = 0;
  return;
}



// Process wave (one voice)

byte process_wave_one_voice
               (undefined ***song_table,sound_channel_16bits_t *sound_channel,wave_t *wave_table)

{
  byte bVar1;
  char cVar2;
  byte index;
  byte *pbVar3;
  ushort uVar4;
  
  if (wave_table->num == 0) {
    if (wave_table->cur_bit == 0) {
      return wave_table->cur_bit;
    }
    wave_table->cur_bit = 0;
    wave_table->dir = 0;
    wave_table->base_freq = 0;
    wave_table->vol = 0;
    sound_channel->freq0 = 0;
    sound_channel->freq1 = 0;
    sound_channel->freq2 = 0;
    sound_channel->freq3 = 0;
    return 0;
  }
  cVar2 = '\b';
  index = 0x80;
  do {
    if ((index & wave_table->num) != 0) {
                    //  Process wave bis : process one wave, represented by 1 bit (in E)
                    // 
      if ((wave_table->cur_bit & index) == 0) {
        wave_table->cur_bit = index;
        index = mspacman_select_song();
        return index;
      }
      index = wave_table->duration - 1;
      wave_table->duration = index;
      if (index == 0) {
        while( true ) {
          index = *wave_table->next_byte;
          pbVar3 = wave_table->next_byte + 1;
          *(char *)&wave_table->next_byte = (char)pbVar3;
          *(undefined *)((short)&wave_table->next_byte + 1) = (char)((ushort)pbVar3 >> 8);
          if (index < 0xf0) break;
          *(undefined2 *)((undefined *)register0x44 + -2) = 0x2d6c;
                    // WARNING: Return address prevents inlining here
          *(undefined2 *)((undefined *)register0x44 + -4) = 0x2d85;
          jump_table_fn(*(undefined **)((undefined *)register0x44 + -4),index & 0xf);
          register0x44 = (BADSPACEBASE *)((undefined *)register0x44 + -2);
        }
        if ((index & 0x1f) != 0) {
          wave_table->dir = index;
        }
        bVar1 = *(byte *)&wave_table->field_0x9;
        if ((wave_table->type & 8) != 0) {
          bVar1 = 0;
        }
        wave_table->vol = bVar1;
        *(undefined2 *)((undefined *)register0x44 + -2) = 0x2dc6;
        bVar1 = dereference_pointer_to_byte
                          (song_lookup_tables,
                           ((index >> 7) << 1 | (index << 1) >> 7) << 1 |
                           ((index << 1 | index >> 7) << 1) >> 7,((undefined *)register0x44)[-2]);
        wave_table->duration = bVar1;
        if ((index & 0x1f) != 0) {
          *(undefined2 *)((undefined *)register0x44 + -2) = 0x2dd4;
          index = dereference_pointer_to_byte
                            (BYTE_ARRAY_ARRAY_ram_3bb8,index & 0xf,((undefined *)register0x44)[-2]);
          wave_table->base_freq = index;
        }
      }
      uVar4 = (ushort)wave_table->base_freq;
      index = wave_table->dir & 0x10;
      if (index != 0) {
        index = 1;
      }
      cVar2 = index + *(char *)&wave_table->field_0x4;
      while (cVar2 != '\0') {
        uVar4 = uVar4 * 2;
        cVar2 = cVar2 + -1;
      }
      bVar1 = (byte)uVar4;
      sound_channel->freq0 = bVar1;
      index = bVar1 >> 1;
      sound_channel->freq1 =
           (((index | bVar1 << 7) >> 1 | index << 7) >> 1 | ((index & 2) >> 1) << 7) >> 1 |
           ((index & 4) >> 2) << 7;
      bVar1 = (byte)(uVar4 >> 8);
      sound_channel->freq2 = bVar1;
      index = bVar1 >> 1;
      sound_channel->freq3 =
           (((index | bVar1 << 7) >> 1 | index << 7) >> 1 | ((index & 2) >> 1) << 7) >> 1 |
           ((index & 4) >> 2) << 7;
      index = wave_table->type;
                    // WARNING: Return address prevents inlining here
      *(undefined2 *)((undefined *)register0x44 + -2) = 0x2f02;
      jump_table_fn(*(undefined **)((undefined *)register0x44 + -2),index);
      return index;
    }
    index = index >> 1;
    cVar2 = cVar2 + -1;
  } while (cVar2 != '\0');
  return 0;
}



// Process effect (one voice)

byte process_effect_one_voice
               (undefined *effects_table,sound_channel_16bits_t *sound_channel,effect_t *effect)

{
  byte bVar1;
  char cVar3;
  short sVar2;
  byte index;
  byte *pbVar4;
  byte bVar5;
  byte *pbVar6;
  ushort uVar7;
  
  if (effect->num == 0) {
    if (effect->cur_bit == 0) {
      return effect->cur_bit;
    }
    effect->cur_bit = 0;
    effect->dir = 0;
    effect->base_freq = 0;
    effect->vol = 0;
    sound_channel->freq0 = 0;
    sound_channel->freq1 = 0;
    sound_channel->freq2 = 0;
    sound_channel->freq3 = 0;
    return 0;
  }
                    // find effect. Effect num is not zero, find which bits are set
  cVar3 = '\b';
  index = 0x80;
  while ((index & effect->num) == 0) {
    index = index >> 1;
    cVar3 = cVar3 + -1;
    if (cVar3 == '\0') {
      return 0;
    }
  }
                    // Process effect bis : process one effect, represented by 1 bit (in E)
  if ((effect->cur_bit & index) == 0) {
    effect->cur_bit = index;
                    // locate the 8 bytes for this effect in the rom tables
    index = (cVar3 - 1U) * '\x02';
    bVar5 = (index | cVar3 - 1U >> 7) << 1;
    pbVar6 = effects_table + (byte)((bVar5 | index >> 7) << 1 | bVar5 >> 7);
    pbVar4 = effect->table;
    sVar2 = 8;
    do {
      *pbVar4 = *pbVar6;
      pbVar4 = pbVar4 + 1;
      index = (byte)pbVar4;
      pbVar6 = pbVar6 + 1;
      sVar2 = sVar2 + -1;
    } while (sVar2 != 0);
    effect->duration = effect->table[3] & 0x7f;
    effect->base_freq = effect->table[1];
    bVar5 = effect->table[6];
    bVar1 = bVar5 >> 4;
    effect->type = bVar1;
    if ((bVar1 & 8) == 0) {
      effect->vol = bVar5;
      effect->dir = 0;
    }
  }
                    //  compute effect
                    // 
  bVar5 = effect->duration - 1;
  effect->duration = bVar5;
  if (bVar5 == 0) {
    if ((effect->table[5] != 0) &&
       (bVar5 = effect->table[5] - 1, effect->table[5] = bVar5, bVar5 == 0)) {
      effect->num = ~index & effect->num;
      index = process_effect_one_voice(effects_table,sound_channel,effect);
      return index;
    }
    effect->duration = effect->table[3] & 0x7f;
    if ((effect->table[3] & 0x80) != 0) {
      effect->table[2] = -effect->table[2];
      index = effect->dir;
      effect->dir = effect->dir | 1;
      if ((index & 1) == 0) goto LAB_ram_2ecd;
      effect->dir = effect->dir & 0xfe;
    }
    index = effect->table[1] + effect->table[4];
    effect->table[1] = index;
    effect->base_freq = index;
    index = effect->table[6] + effect->table[7];
    effect->table[6] = index;
    if ((effect->type & 8) == 0) {
      effect->vol = index;
    }
  }
LAB_ram_2ecd:
                    //  update freq
                    // 
  index = effect->base_freq + effect->table[2];
  effect->base_freq = index;
  uVar7 = (ushort)index;
  index = effect->table[0] & 0x70;
  if (index != 0) {
    index = index >> 4;
    do {
      uVar7 = uVar7 * 2;
      index = index - 1;
    } while (index != 0);
  }
  bVar5 = (byte)uVar7;
  sound_channel->freq0 = bVar5;
  index = bVar5 >> 1;
  sound_channel->freq1 =
       (((index | bVar5 << 7) >> 1 | index << 7) >> 1 | ((index & 2) >> 1) << 7) >> 1 |
       ((index & 4) >> 2) << 7;
  bVar5 = (byte)(uVar7 >> 8);
  sound_channel->freq2 = bVar5;
  index = bVar5 >> 1;
  sound_channel->freq3 =
       (((index | bVar5 << 7) >> 1 | index << 7) >> 1 | ((index & 2) >> 1) << 7) >> 1 |
       ((index & 4) >> 2) << 7;
  index = effect->type;
                    // WARNING: Return address prevents inlining here
  jump_table_fn((undefined *)effect_fn_table,index);
  return index;
}



char wave_init_param(undefined *param_1,short param_2)

{
  if (*(char *)(param_2 + 2) == '\0') {
    return *(char *)(param_2 + 2);
  }
  *(undefined *)(param_2 + 2) = 0;
  *(undefined *)(param_2 + 0xd) = 0;
  *(undefined *)(param_2 + 0xe) = 0;
  *(undefined *)(param_2 + 0xf) = 0;
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  return '\0';
}



byte effect_TYPE0_get_volume(effect_t *effect)

{
  return effect->vol;
}



void effect_TYPE1_volume_decrease(effect_t *effect)

{
  byte bVar1;
  
                    //  type 1
                    // 
  bVar1 = effect->vol & 0xf;
  if (bVar1 == 0) {
    return;
  }
  effect->vol = bVar1 - 1;
  return;
}



void effect_TYPE2_volume_decrease_1_2(effect_t *effect)

{
  byte bVar1;
  
                    //  type 2
                    // 
  if ((sound_counter & 1) != 0) {
    return;
  }
  bVar1 = effect->vol & 0xf;
  if (bVar1 == 0) {
    return;
  }
  effect->vol = bVar1 - 1;
  return;
}



void effect_TYPE3_volume_decrease_1_4(effect_t *effect)

{
  byte bVar1;
  
                    //  type 3
                    // 
  if ((sound_counter & 3) != 0) {
    return;
  }
  bVar1 = effect->vol & 0xf;
  if (bVar1 == 0) {
    return;
  }
  effect->vol = bVar1 - 1;
  return;
}



void effect_TYPE4_volume_decrease_1_8(effect_t *effect)

{
  byte bVar1;
  
                    //  type 4
                    // 
  if ((sound_counter & 7) != 0) {
    return;
  }
  bVar1 = effect->vol & 0xf;
  if (bVar1 == 0) {
    return;
  }
  effect->vol = bVar1 - 1;
  return;
}



// WARNING: Unknown calling convention yet parameter storage is locked

void NOP(void)

{
                    //  type 5-15
                    // 
  return;
}



void NOP(void)

{
  return;
}



void NOP(void)

{
  return;
}



void NOP(void)

{
  return;
}



void NOP(void)

{
  return;
}



void NOP(void)

{
  return;
}



void NOP(void)

{
  return;
}



void NOP(void)

{
  return;
}



void NOP(void)

{
  return;
}



void NOP(void)

{
  return;
}



void NOP(void)

{
  return;
}



// Special byte F0 : this is followed by 2 bytes, the new offset (to allow loops)

void wave_cmd0_jmp_offset(wave_t *wave)

{
  undefined *puVar1;
  
  puVar1 = wave->next_byte;
  *(undefined *)&wave->next_byte = *puVar1;
  *(undefined *)((short)&wave->next_byte + 1) = puVar1[1];
  return;
}



// Special byte F1 : followed by one byte (wave select)
// 

void wave_cmd1_wave_select(wave_t *wave)

{
  byte bVar1;
  byte *pbVar2;
  
  bVar1 = *wave->next_byte;
  pbVar2 = wave->next_byte + 1;
  *(char *)&wave->next_byte = (char)pbVar2;
  *(undefined *)((short)&wave->next_byte + 1) = (char)((ushort)pbVar2 >> 8);
  wave->sel = bVar1;
  return;
}



// Special byte F2 : followed by one byte (Frequency increment)

void wave_cmd2_freq_incr(wave_t *wave)

{
  undefined uVar1;
  undefined *puVar2;
  
  uVar1 = *wave->next_byte;
  puVar2 = wave->next_byte + 1;
  *(char *)&wave->next_byte = (char)puVar2;
  *(undefined *)((short)&wave->next_byte + 1) = (char)((ushort)puVar2 >> 8);
  *(undefined *)&wave->field_0x4 = uVar1;
  return;
}



// Special byte F3 : followed by one byte (Volume)

void wave_cmd3_volume(wave_t *wave)

{
  undefined uVar1;
  undefined *puVar2;
  
  uVar1 = *wave->next_byte;
  puVar2 = wave->next_byte + 1;
  *(char *)&wave->next_byte = (char)puVar2;
  *(undefined *)((short)&wave->next_byte + 1) = (char)((ushort)puVar2 >> 8);
  *(undefined *)&wave->field_0x9 = uVar1;
  return;
}



// Special byte F4 : followed by one byte (Type)

void wave_cmd4_type(wave_t *wave)

{
  byte bVar1;
  byte *pbVar2;
  
  bVar1 = *wave->next_byte;
  pbVar2 = wave->next_byte + 1;
  *(char *)&wave->next_byte = (char)pbVar2;
  *(undefined *)((short)&wave->next_byte + 1) = (char)((ushort)pbVar2 >> 8);
  wave->type = bVar1;
  return;
}



// Special byte FF : mark the end of the song

byte wave_cmdF_end_of_song(undefined *param_1,byte *param_2)

{
  byte bVar1;
  
  *param_2 = ~param_2[2] & *param_2;
  bVar1 = wave_init_param(param_1,(short)param_2);
  return bVar1;
}



// WARNING: This function may have set the stack pointer
// 3000 - 3fff
// this rom is somehow overlayed from U7 on the aux board.
// rst 38 continuation (initalization routine portion)
// the rom checksum routine
// 

void interrupt_vector_pacman_only(void)

{
  ushort uVar1;
  char cVar2;
  task_core_e index;
  ushort in_AF;
  byte c;
  byte n;
  char cVar7;
  ushort uVar3;
  ushort uVar4;
  short sVar5;
  ushort uVar6;
  ushort uVar8;
  char *pcVar9;
  byte bVar14;
  byte *s;
  hardware_floating_sprite_t *phVar10;
  byte *pbVar11;
  undefined2 uVar12;
  undefined *puVar13;
  byte **ppbVar15;
  byte **ppbVar16;
  word *pwVar17;
  
  pcVar9 = (char *)0x0;
  do {
    do {
      c = 0;
      cVar7 = '\x10';
      do {
                    // HACK4
                    // 3000  31c04f    ld      sp,#4fc0
                    // 3003  c3c130    jp      #30c1
                    // 
        write_volatile_1(hardware_DSW2_watchdog,(byte)(in_AF >> 8));
        do {
          c = c + *pcVar9;
          cVar2 = (char)pcVar9;
          n = cVar2 + 2;
          uVar8 = (ushort)pcVar9 & 0xff00;
          pcVar9 = (char *)(uVar8 | (ushort)n);
        } while (1 < n);
        bVar14 = (char)(uVar8 >> 8) + 1;
        pcVar9 = (char *)CONCAT11(bVar14,n);
        in_AF = (ushort)n << 8;
        cVar7 = cVar7 + -1;
      } while (cVar7 != '\0');
                    // ; PAC and ms pac non-bootleg
                    // ;301a  2015 jr  nz, #3031 ; check for bad checksum
                    // ;
                    // 
      write_volatile_1(hardware_coin_counter,c);
      in_AF = (ushort)bVar14 << 8;
    } while (bVar14 != 0x30);
    c = cVar2 + 3;
    pcVar9 = (char *)(ushort)c;
    in_AF = CONCAT11(c,c < 2);
  } while (c < 2);
                    //  RAM TEST (4c00)
                    // 
  ppbVar15 = (byte **)&DAT_ram_3154;
  do {
    uVar8 = 0xff00;
    do {
      s = *ppbVar15;
      uVar6 = (ushort)ppbVar15[1];
      uVar8 = uVar8 & 0xff00 | uVar8 >> 8;
      do {
                    // write to RAM
                    // 
        write_volatile_1(hardware_DSW2_watchdog,(byte)(in_AF >> 8));
        do {
          do {
            uVar3 = uVar8;
            c = (byte)uVar3 & (byte)uVar6;
            *s = c;
            c = c + 0x33;
            uVar4 = uVar3 & 0xff00;
            n = (char)s + 1;
            uVar1 = (ushort)s & 0xff00;
            s = (byte *)(uVar1 | n);
            uVar8 = uVar4 | c;
          } while ((n & 0xf) != 0);
          uVar8 = uVar4 | (byte)(c * '\x05' + 0x31);
        } while (n != 0);
        s = (byte *)((ushort)(byte)((char)(uVar1 >> 8) + 1) << 8);
        c = (char)(uVar6 >> 8) - 1;
        uVar6 = uVar6 & 0xff | (ushort)c << 8;
        in_AF = 0;
      } while (c != 0);
      s = *ppbVar15;
      uVar8 = (ushort)ppbVar15[1];
      uVar4 = uVar4 | uVar3 >> 8;
      do {
                    // check RAM again
                    // 
        write_volatile_1(hardware_DSW2_watchdog,0);
        do {
          do {
            n = (byte)uVar8;
            c = (byte)uVar4 & n;
            uVar6 = (ushort)c;
            uVar1 = uVar4 & 0xff00;
            if ((*s & n) != c) {
                    // bad RAM
                    // 
              uVar4 = (ushort)(n & 1 ^ 1);
              in_AF = uVar4 << 8;
              uVar4 = uVar8 & 0xff00 | uVar4;
              goto LAB_ram_30bd;
            }
            c = (*s & n) + 0x33;
            uVar4 = uVar1 | c;
            n = (char)s + 1;
            uVar6 = (ushort)s & 0xff00;
            s = (byte *)(uVar6 | n);
          } while ((n & 0xf) != 0);
          c = c * '\x05' + 0x31;
          uVar4 = uVar1 | c;
        } while (n != 0);
        s = (byte *)((ushort)(byte)((char)(uVar6 >> 8) + 1) << 8);
        n = (char)(uVar8 >> 8) - 1;
        uVar8 = uVar8 & 0xff | (ushort)n << 8;
      } while (n != 0);
      cVar7 = (char)(uVar1 >> 8);
      in_AF = (ushort)(byte)(cVar7 - 0x10) << 8;
      cVar7 = cVar7 + -0x11;
      uVar8 = CONCAT11(cVar7,c);
    } while (cVar7 != '\0');
    uVar8 = (ushort)*ppbVar15;
    uVar4 = (ushort)ppbVar15[1];
    ppbVar16 = ppbVar15 + 2;
    in_AF = uVar8 & 0xff00;
    ppbVar15 = ppbVar15 + 2;
  } while (((char)(uVar8 >> 8) != 'D') ||
          (in_AF = uVar4 << 8 ^ 0xf000, ppbVar15 = ppbVar16, (char)uVar4 != -0x10));
  uVar6 = CONCAT11(1,c);
LAB_ram_30bd:
                    // display bad ROM
                    // 
                    // clear all program RAM
                    // 
  phVar10 = &start_of_sprites_address;
  cVar7 = '\x04';
  do {
    write_volatile_1(hardware_DSW2_watchdog,(byte)(in_AF >> 8));
    do {
      *(undefined *)phVar10 = 0;
      c = (char)phVar10 + 1;
      uVar8 = (ushort)phVar10 & 0xff00;
      phVar10 = (hardware_floating_sprite_t *)(uVar8 | c);
    } while (c != 0);
    phVar10 = (hardware_floating_sprite_t *)((ushort)(byte)((char)(uVar8 >> 8) + 1) << 8);
    cVar7 = cVar7 + -1;
  } while (cVar7 != '\0');
                    // set all video ram to 0x40 - clear screen
  pbVar11 = hardware_video_ram;
  cVar7 = '\x04';
  do {
    write_volatile_1(hardware_DSW2_watchdog,(byte)(in_AF >> 8));
    do {
      *pbVar11 = 0x40;
      c = (char)pbVar11 + 1;
      uVar8 = (ushort)pbVar11 & 0xff00;
      pbVar11 = (byte *)(uVar8 | c);
    } while (c != 0);
    pbVar11 = (byte *)((ushort)(byte)((char)(uVar8 >> 8) + 1) << 8);
    in_AF = 0x4000;
    cVar7 = cVar7 + -1;
  } while (cVar7 != '\0');
                    // set all color ram to 0x0f
  cVar7 = '\x04';
  do {
    write_volatile_1(hardware_DSW2_watchdog,(byte)(in_AF >> 8));
    do {
      *pbVar11 = 0xf;
      c = (char)pbVar11 + 1;
      uVar8 = (ushort)pbVar11 & 0xff00;
      pbVar11 = (byte *)(uVar8 | c);
    } while (c != 0);
    pbVar11 = (byte *)((ushort)(byte)((char)(uVar8 >> 8) + 1) << 8);
    in_AF = 0xf00;
    cVar7 = cVar7 + -1;
  } while (cVar7 != '\0');
                    //  change 30f0 - 30f2 to "00 nop" to skip checksum check. ; HACK4
                    //   if you do that, 30fb - 3173 can be reclaimed for other code use.
                    // 30f0  00 nop
                    // 30f1  00 nop
                    // 30f2  00 nop
                    // 
  c = (char)(uVar6 >> 8) - 1;
  ARRAY_ram_4f5c._98_2_ = uVar6 & 0xff | (ushort)c << 8;
  if (c != 0) {
                    // HACK 0
                    // run the game!
                    // 
    hardware_screen_maze_area[11][16] = (char)uVar4 + 0x30;
    ARRAY_ram_4f5c._94_2_ = 0x3108;
    ARRAY_ram_4f5c._96_2_ = s;
    DrawText(BAD_R_M);
    c = (byte)((ushort)ARRAY_ram_4f5c._96_2_ >> 8);
    uVar12 = DAT_ram_316c;
    if (((0x3f < c) && (uVar12 = DAT_ram_316e, c < 0x4c)) && (uVar12 = DAT_ram_3170, 0x43 < c)) {
      uVar12 = DAT_ram_3172;
    }
    hardware_screen_maze_area[16][4] = (byte)uVar12;
    hardware_screen_maze_area[19][16] = (byte)((ushort)uVar12 >> 8);
    sVar5 = ((ushort)((byte)hardware_IN1 | (byte)hardware_IN0) & 1) << 8;
    if ((((byte)hardware_IN1 | (byte)hardware_IN0) & 1) == 0) {
      sVar5 = ((ARRAY_ram_4f5c._98_2_ & 0xf0) >> 4) << 8;
      hardware_screen_maze_area[11]._17_2_ =
           (ushort)((byte)ARRAY_ram_4f5c._98_2_ & 0xf) << 8 | (ARRAY_ram_4f5c._98_2_ & 0xf0) >> 4;
    }
    do {
      write_volatile_1(hardware_DSW2_watchdog,(byte)((ushort)sVar5 >> 8));
      sVar5 = ((ushort)(byte)hardware_IN1 & 0x10) << 8;
    } while (((byte)hardware_IN1 & 0x10) == 0);
    startup_test((byte)hardware_IN1 & 0x10);
    return;
  }
                    //  eliminate startup tests ; HACK7
                    // 30f5  00 nop
                    // 30f6  00 nop
                    // 30f7  00 nop
                    // 
  ARRAY_ram_4f5c._98_2_ = 0x30f8;
  DrawText(MEMORY_OK);
                    //  start the main section... (tests first)
                    // 
  s = &hardware_coin_lockout_global;
  do {
    *s = 1;
    c = (char)s - 1;
    s = (byte *)((ushort)s & 0xff00 | (ushort)c);
  } while (c != 0);
  hardware_flipscreen = false;
  c = 0xfc;
                    // pac:
                    // set vector TO #8D WHEN INTERRUPT
                    // 
  do {
    write_volatile_1(hardware_DSW2_watchdog,c);
                    // Skip test mode: HACK7
                    // set stack pointer
                    // skip over the test mode
                    // 
    game_mode = INIT;
    subroutine_INIT_state = 1;
    hardware_IN0 = (in0_t)0x1;
    enableMaskableInterrupts();
                    //  test mode sound checks
                    //  this gets called if the test switch is on at bootup
                    // 
    if (true) {
      channel_1_effect.num = 2;
    }
    if ((~(byte)hardware_IN1 & 0x60) != 0) {
      channel_1_effect.num = 1;
    }
    if ((~(byte)hardware_IN1 & 1) != 0) {
      channel_3_effect.num = 8;
    }
    if (true) {
      channel_3_effect.num = 4;
    }
    if (true) {
      channel_3_effect.num = 0x10;
    }
    if (true) {
      channel_3_effect.num = 0x20;
    }
    c = read_volatile_1(hardware_DSW1);
    ARRAY_ram_4f5c._98_2_ = 0x31ea;
    DrawText((c & 3) + FREE_PLAY_25);
    c = read_volatile_1(hardware_DSW1);
    c = c >> 4 & 3;
    if (c == 3) {
      ARRAY_ram_4f5c._98_2_ = 0x31fc;
      DrawText(BONUS_NONE);
    }
    else {
      ARRAY_ram_4f5c._98_2_ = uVar4 & 0xff00 | (ushort)(byte)(c << 1);
      ARRAY_ram_4f5c._96_2_ = (byte *)0x3207;
      DrawText(BONUS);
      ARRAY_ram_4f5c._96_2_ = (byte *)0x320c;
      DrawText(T_000);
      uVar4 = ARRAY_ram_4f5c._98_2_ & 0xff;
      hardware_screen_maze_area[17][14] = bonus_table_text[uVar4];
      hardware_screen_maze_area[18][18] = bonus_table_text[uVar4 + 1];
    }
    c = read_volatile_1(hardware_DSW1);
    c = c >> 2 & 3;
    hardware_screen_maze_area[13][0] = c + 0x31;
    if (hardware_screen_maze_area[13][0] == 0x34) {
      hardware_screen_maze_area[13][0] = c + 0x32;
    }
                    // pac:
                    // 322a  320c42    ld      (#420c),a
                    // 
    ARRAY_ram_4f5c._98_2_ = 0x3232;
    DrawText(MS_PAC_MEN);
    ARRAY_ram_4f5c._98_2_ = 0x323e;
    DrawText(TABLE - ((char)hardware_IN1 >> 7));
    c = (byte)hardware_IN1 & 0x10;
  } while (((byte)hardware_IN1 & 0x10) == 0);
  hardware_IN0 = (in0_t)0x0;
  disableMaskableInterrupts();
  s = &hardware_coin_counter;
  do {
    *s = 0;
    c = (char)s - 1;
    s = (byte *)((ushort)s & 0xff00 | (ushort)c);
    sVar5 = 0;
  } while (c != 0);
                    // eliminate just the test grid: HACK7 (alternate)
                    // 3253  31c04f    ld      sp,#4fc0
                    // 3262  c38632    jp      #3286
                    // preload the stack with some data for the grid test
                    // prep for the test grid
                    // 
  pwVar17 = &WORD_ram_3ae2;
  cVar7 = '\x03';
  do {
    puVar13 = (undefined *)*pwVar17;
    uVar8 = pwVar17[1];
    do {
      write_volatile_1(hardware_DSW2_watchdog,(byte)((ushort)sVar5 >> 8));
      sVar5 = pwVar17[2];
      do {
                    //  draw the test grid to the screen
                    // 
        *puVar13 = 0x3c;
        puVar13[1] = (char)(uVar8 >> 8);
        puVar13 = puVar13 + 2;
        c = (char)((ushort)sVar5 >> 8) - 1;
        sVar5 = (ushort)c << 8;
      } while (c != 0);
      uVar6 = pwVar17[2];
      do {
        *puVar13 = (char)uVar6;
        puVar13[1] = 0x3f;
        puVar13 = puVar13 + 2;
        c = (char)(uVar6 >> 8) - 1;
        uVar6 = uVar6 & 0xff | (ushort)c << 8;
      } while (c != 0);
      c = (char)uVar8 - 1;
      uVar8 = uVar8 & 0xff00 | (ushort)c;
      sVar5 = 0x3f00;
    } while (c != 0);
    sVar5 = pwVar17[2];
    pwVar17 = pwVar17 + 3;
    cVar7 = cVar7 + -1;
  } while (cVar7 != '\0');
  cVar7 = '\b';
  do {
    ARRAY_ram_4f5c._98_2_ = 0x3284;
    sleep2800((char)((ushort)sVar5 >> 8));
    cVar7 = cVar7 + -1;
  } while (cVar7 != '\0');
  do {
                    // loop until service switch turned off
                    // 
    write_volatile_1(hardware_DSW2_watchdog,(byte)((ushort)sVar5 >> 8));
    sVar5 = ((ushort)(byte)hardware_IN1 & 0x10) << 8;
  } while (((byte)hardware_IN1 & 0x10) == 0);
                    //   check the condition to display the easter egg
                    // This piece of code is found in the original Midway Pac-Man ROMs @ #3289.
                    // Place the game in the test grid screen (Monitor Convergence screen) by
                    // switching test mode on.
                    // Then, hold down the player 1 and player 2 buttons and then quickly jiggle the
                    // test switch out &
                    // back into test. Next move the joystick:
                    // Up 4 times
                    // Left 4 times
                    // Right 4 times
                    // Down 4 times
                    //     - Widel/Mowerman
                    // 
  c = (byte)hardware_IN1 & 0x60;
  if (((byte)hardware_IN1 & 0x60) == 0) {
    cVar7 = '\b';
    do {
      ARRAY_ram_4f5c._98_2_ = 0x329d;
      sleep2800(c);
      cVar7 = cVar7 + -1;
    } while (cVar7 != '\0');
    c = (byte)hardware_IN1 & 0x10;
    if (((byte)hardware_IN1 & 0x10) == 0) {
      uVar8 = 1;
      do {
        sVar5 = 0x400;
        do {
          do {
            write_volatile_1(hardware_DSW2_watchdog,c);
            ARRAY_ram_4f5c._98_2_ = 0x32b1;
            sleep2800(c);
            c = (byte)hardware_IN0 & (byte)uVar8;
          } while (c != 0);
          do {
            ARRAY_ram_4f5c._98_2_ = 0x32ba;
            sleep2800(c);
            write_volatile_1(hardware_DSW2_watchdog,c);
            c = (byte)hardware_IN0 ^ 0xff;
          } while (hardware_IN0 != (in0_t)0xff);
          n = (char)((ushort)sVar5 >> 8) - 1;
          sVar5 = (ushort)n << 8;
        } while (n != 0);
        c = (byte)uVar8 << 1 | (byte)uVar8 >> 7;
        uVar8 = (ushort)c;
      } while (c < 0x10);
                    //  draw the "Made By Namco" easter egg
                    // clear the screen...
                    // 
      s = hardware_video_ram;
      cVar7 = '\x04';
      do {
        c = 0x40;
        do {
          *s = 0x40;
          n = (char)s + 1;
          uVar8 = (ushort)s & 0xff00;
          s = (byte *)(uVar8 | n);
        } while (n != 0);
        s = (byte *)((ushort)(byte)((char)(uVar8 >> 8) + 1) << 8);
        cVar7 = cVar7 + -1;
      } while (cVar7 != '\0');
      ARRAY_ram_4f5c._98_2_ = 0x32df;
      draw_easter_egg__Made_By_Namco();
      do {
                    // wait for service switch to be off
                    // 
        write_volatile_1(hardware_DSW2_watchdog,c);
        c = (byte)hardware_IN1 & 0x10;
      } while (((byte)hardware_IN1 & 0x10) == 0);
    }
  }
  write_volatile_1(hardware_DSW2_watchdog,c);
  c = 0;
  ARRAY_ram_4f5c._98_2_ = 0x2359;
  memset((byte *)&hardware_IN0,0,8);
  n = 0xbe;
  ARRAY_ram_4f5c._98_2_ = 0x235f;
  s = (byte *)memset((byte *)&start_of_sprites_address,c,0xbe);
  ARRAY_ram_4f5c._98_2_ = 0x2360;
  s = (byte *)memset(s,c,n);
  ARRAY_ram_4f5c._98_2_ = 0x2361;
  s = (byte *)memset(s,c,n);
  ARRAY_ram_4f5c._98_2_ = 0x2362;
  memset(s,c,n);
  ARRAY_ram_4f5c._98_2_ = 0x2368;
  memset((byte *)&hardware_IN1,c,0x40);
  write_volatile_1(hardware_DSW2_watchdog,c);
  ARRAY_ram_4f5c._98_2_ = 0x236e;
  T06_clears_color_RAM();
  write_volatile_1(hardware_DSW2_watchdog,c);
  ARRAY_ram_4f5c._98_2_ = 0x2376;
  T00_clear_whole_screen_or_maze(0);
  write_volatile_1(hardware_DSW2_watchdog,c);
  p_task_list_next_free = tasks_to_execute_outside_of_irq;
  p_task_list_begin = tasks_to_execute_outside_of_irq;
  ARRAY_ram_4f5c._98_2_ = 0x2387;
  memset((byte *)tasks_to_execute_outside_of_irq,0xff,0x40);
  hardware_IN0 = (in0_t)0x1;
  enableMaskableInterrupts();
  s = _STACK_END;
  do {
    do {
      index = p_task_list_begin->value;
    } while ((short)((ushort)index << 8) < 0);
    p_task_list_begin->value = ~clear_whole_screen_or_maze;
    uVar8 = (ushort)p_task_list_begin & 0xff00;
    *(undefined *)(uVar8 | (byte)((char)p_task_list_begin + 1)) = 0xff;
    c = (char)p_task_list_begin + 2;
    p_task_list_begin = (task_core_t *)(uVar8 | c);
    if (c == 0) {
      p_task_list_begin = (task_core_t *)CONCAT11((char)(uVar8 >> 8),0xc0);
    }
    *(undefined2 *)(s + -2) = 0x238d;
                    // WARNING: Return address prevents inlining here
    *(undefined2 *)(s + -4) = 0x23a8;
    jump_table_fn(*(undefined **)(s + -4),index);
    s = s + -2;
  } while( true );
}



void sleep2800(byte watchdog)

{
  short delay;
  
                    // delay timer
                    // 
  write_volatile_1(hardware_DSW2_watchdog,watchdog);
  delay = 0x2800;
  do {
    delay = delay + -1;
  } while ((byte)((byte)((ushort)delay >> 8) | (byte)delay) != 0);
  return;
}



//  resume in the middle of original pac, in entry 4. see above.
// 
//  ; entry 4, 5, etc is here.
// 
// ; orignal pac rom:
// ; data - level map information
// 
// 3435:                40 FC D0-D2 D2 D2 D2 D2 D2 D2 D2
// 3440: D4 FC FC FC DA 02 DC FC-FC FC D0 D2 D2 D2 D2 D6
// 3450: D8 D2 D2 D2 D2 D4 FC DA-09 DC FC FC FC DA 02 DC
// 3460: FC FC FC DA 05 DE E4 05-DC FC DA 02 E6 E8 EA 02
// 3470: E6 EA 02 DC FC FC FC DA-02 DC FC FC FC DA 02 E6
// 3480: EA 02 E7 EB 02 E6 EA 02-DC FC DA 02 DE FC E4 02
// 3490: DE E4 02 DC FC FC FC DA-02 DC FC FC FC DA 02 DE
// 34A0: E4 05 DE E4 02 DC FC DA-02 DE FC E4 02 DE E4 02
// 34B0: DC FC FC FC DA 02 DC FC-FC FC DA 02 DE F2 E8 E8
// 34C0: EA 02 DE E4 02 DC FC DA-02 E7 E9 EB 02 E7 EB 02
// 34D0: E7 D2 D2 D2 EB 02 E7 D2-D2 D2 EB 02 E7 E9 E9 E9
// 34E0: EB 02 DE E4 02 DC FC DA-1B DE E4 02 DC FC DA 02
// 34F0: E6 E8 F8 02 F6 E8 E8 E8-E8 E8 E8 F8 02 F6 E8 E8
// 3500: E8 EA 02 E6 F8 02 F6 E8-E8 F4 E4 02 DC FC DA 02
// 3510: DE FC E4 02 F7 E9 E9 F5-F3 E9 E9 F9 02 F7 E9 E9
// 3520: E9 EB 02 DE E4 02 F7 E9-E9 F5 E4 02 DC FC DA 02
// 3530: DE FC E4 05 DE E4 0B DE-E4 05 DE E4 02 DC FC DA
// 3540: 02 DE FC E4 02 E6 EA 02-DE E4 02 EC D3 D3 D3 EE
// 3550: 02 E6 EA 02 DE E4 02 E6-EA 02 DE E4 02 DC FC DA
// 3560: 02 E7 E9 EB 02 DE E4 02-E7 EB 02 DC FC FC FC DA
// 3570: 02 DE E4 02 E7 EB 02 DE-E4 02 E7 EB 02 DC FC DA
// 3580: 06 DE E4 05 F0 FC FC FC-DA 02 DE E4 05 DE E4 05
// 3590: DC FC FA E8 E8 E8 EA 02-DE F2 E8 E8 EA 02 CE FC
// 35A0: FC FC DA 02 DE F2 E8 E8-EA 02 DE F2 E8 E8 EA 02
// 35B0: DC 00 00 00 00
// 
// ; original pac rom:
// ; data - level pill information
// 
// 35B5:                62 01 02-01 01 01 01 0C 01 01 04
// 35C0: 01 01 01 04 04 03 0C 03-03 03 04 04 03 0C 03 01
// 35D0: 01 01 03 04 04 03 0C 06-03 04 04 03 0C 06 03 04
// 35E0: 01 01 01 01 01 01 01 01-01 01 01 01 01 01 01 01
// 35F0: 01 01 01 01 01 01 01 01-01 03 04 04 0F 03 06 04
// 3600: 04 0F 03 06 04 04 01 01-01 0C 03 01 01 01 03 04
// 3610: 04 03 0C 03 03 03 04 04-03 0C 03 03 03 04 01 01
// 3620: 01 01 03 0C 01 01 01 03-01 01 01 08 18 08 18 04
// 3630: 01 01 01 01 03 0C 01 01-01 03 01 01 01 04 04 03
// 3640: 0C 03 03 03 04 04 03 0C-03 03 03 04 04 01 01 01
// 3650: 0C 03 01 01 01 03 04 04-0F 03 06 04 04 0F 03 06
// 3660: 04 01 01 01 01 01 01 01-01 01 01 01 01 01 01 01
// 3670: 01 01 01 01 01 01 01 01-01 01 03 04 04 03 0C 06
// 3680: 03 04 04 03 0C 06 03 04-04 03 0C 03 01 01 01 03
// 3690: 04 04 03 0C 03 03 03 04-01 02 01 01 01 01 0C 01
// 36A0: 01 04 01 01 01
// ; end pac-man only
// 
// 
// the following resumes Ms Pac
// the whole section from 0x3435-0x36a2 differs from Pac roms.
// 
// 
// arrive here from #2108 when 1st intermission begins
// 

void mspacman_state_for_1st_intermission_patch(void)

{
  ushort uVar1;
  byte bVar2;
  char cVar3;
  byte bVar4;
  byte index;
  byte in_C;
  undefined uVar5;
  undefined2 uVar6;
  ushort uVar7;
  byte *pbVar8;
  short sVar9;
  char *pcVar10;
  undefined *puVar11;
  undefined1 *puVar12;
  byte *lookup_table;
  byte **ppbVar13;
  dereference_word_t dVar14;
  word *lookup_table_00;
  
  if (intermission_mode != true) {
                    // WARNING: Return address prevents inlining here
    insert_task(&task_draw_they_meet);
    hardware_screen_maze_area[22][4] = 1;
    BYTE_ARRAY_ARRAY_ram_4440[22][4] = 0x16;
    intermissions_and_attract_mode_animation_main_routine(0);
    return;
  }
  if (false) {
    generate_animations(in_C);
  }
  uVar7 = CONCAT11(6,in_C);
  ppbVar13 = animation_current + 5;
  do {
    uVar5 = (undefined)uVar7;
    index = (byte)(uVar7 >> 8);
    lookup_table = *ppbVar13;
    bVar2 = *lookup_table;
    if (bVar2 == 0xf0) {
intermissions_and_attract_mode_animation_main_routine_animation_code_F0_loop:
      bVar2 = dereference_pointer_to_byte(lookup_table,1);
      uVar6 = CONCAT11(index,bVar2);
      dVar14 = dereference_pointer_to_word(WORD_ARRAY_ram_4f2e,index);
      pbVar8 = (byte *)((uint5)dVar14 >> 8);
      bVar2 = animation_code_f0_loop_sub_stuff((char)uVar6 + (char)((uint5)dVar14 >> 0x20));
      *pbVar8 = bVar2;
      lookup_table_00 = (word *)animation_code_f0_and_f1_sub_stuff(uVar6);
      dVar14 = dereference_pointer_to_word(lookup_table_00,(byte)((ushort)uVar6 >> 8));
      index = (byte)((ushort)uVar6 >> 8);
      *(char *)((uint5)dVar14 >> 8) = (char)((uint5)dVar14 >> 0x20) + (char)uVar6;
      bVar2 = dereference_pointer_to_byte(lookup_table,2);
      uVar6 = CONCAT11(index,bVar2);
      dVar14 = dereference_pointer_to_word(WORD_ARRAY_ram_4f2e,index);
      sVar9 = (short)((uint5)dVar14 >> 8);
      bVar2 = animation_code_f0_loop_sub_stuff((char)uVar6 + (char)((uint5)dVar14 >> 0x18));
      *(byte *)(sVar9 + -1) = bVar2;
      lookup_table_00 = (word *)animation_code_f0_and_f1_sub_stuff(uVar6);
      dVar14 = dereference_pointer_to_word(lookup_table_00,(byte)((ushort)uVar6 >> 8));
      *(char *)((short)((uint5)dVar14 >> 8) + -1) = (char)((uint5)dVar14 >> 0x18) + (char)uVar6;
      pcVar10 = &DAT_ram_4f0f;
      index = (byte)((ushort)uVar6 >> 8);
      bVar2 = dereference_pointer_to_byte(&DAT_ram_4f0f,index);
      cVar3 = bVar2 + 1;
      while( true ) {
        dVar14 = dereference_pointer_to_word(WORD_ARRAY_ram_4f3e,index);
        bVar2 = dereference_pointer_to_byte((byte *)((uint5)dVar14 >> 0x18),cVar3 >> 1);
        if (bVar2 != 0xff) break;
        cVar3 = '\0';
      }
      *pcVar10 = cVar3;
      bVar4 = dereference_pointer_to_byte(lookup_table,3);
      dVar14 = dereference_pointer_to_word(&WORD_ram_4f4e,index);
      lookup_table = (byte *)((uint5)dVar14 >> 8);
      *lookup_table = bVar4;
      uVar7 = CONCAT11(index,current_player_number);
      if ((cocktail_mode & current_player_number) != 0) {
        bVar2 = bVar2 ^ 0xc0;
      }
      lookup_table[-1] = bVar2;
      pcVar10 = &animation_cmd_setn;
      bVar2 = dereference_pointer_to_byte(&animation_cmd_setn,index);
      *pcVar10 = bVar2 - 1;
      sVar9 = 0;
      if ((byte)(bVar2 - 1) == '\0') {
        sVar9 = 4;
      }
    }
    else {
      if (bVar2 == 0xf1) {
        lookup_table_00 = (word *)animation_code_f0_and_f1_sub_stuff(uVar7);
        uVar6 = CONCAT11(lookup_table[1],lookup_table[2]);
intermissions_and_attract_mode_animation_main_routine_cleanup_for_return_from_f0_f1_f3:
        dVar14 = dereference_pointer_to_word(lookup_table_00,(byte)(uVar7 >> 8));
        puVar11 = (undefined *)((uint5)dVar14 >> 8);
        *puVar11 = (char)((ushort)uVar6 >> 8);
        puVar11[-1] = (char)uVar6;
        sVar9 = 3;
      }
      else {
        if (bVar2 == 0xf2) {
          uVar1 = uVar7 & 0xff00;
          uVar7 = uVar1 | lookup_table[1];
          puVar12 = &animation_cmd_setn;
          dereference_pointer_to_byte(&animation_cmd_setn,(byte)(uVar1 >> 8));
          *puVar12 = (char)uVar7;
          sVar9 = 2;
        }
        else {
          if (bVar2 == 0xf3) {
            puVar11 = &DAT_ram_4f0f;
            dereference_pointer_to_byte(&DAT_ram_4f0f,index);
            *puVar11 = 0;
            lookup_table_00 = WORD_ARRAY_ram_4f3e;
            uVar6 = *(undefined2 *)(lookup_table + 1);
            goto 
            intermissions_and_attract_mode_animation_main_routine_cleanup_for_return_from_f0_f1_f3;
          }
          if (bVar2 == 0xf5) {
            channel_3_effect.num = lookup_table[1];
            sVar9 = 2;
          }
          else {
            if (bVar2 == 0xf6) {
              pcVar10 = &animation_cmd_setn;
              bVar2 = dereference_pointer_to_byte(&animation_cmd_setn,index);
              *pcVar10 = bVar2 - 1;
              sVar9 = 0;
              if ((byte)(bVar2 - 1) == '\0') {
                sVar9 = 1;
              }
            }
            else {
              if (bVar2 == 0xf7) {
                    // WARNING: Return address prevents inlining here
                insert_task(&task_text_or_graphics_draw_space);
                uVar7 = CONCAT11(index,uVar5);
                sVar9 = 1;
              }
              else {
                if (bVar2 == 0xf8) {
                  hardware_screen_maze_area[22][4] = 0x40;
                  sVar9 = 1;
                }
                else {
                  if (bVar2 != 0xff) {
                    halt();
                    goto 
                    intermissions_and_attract_mode_animation_main_routine_animation_code_F0_loop;
                  }
                  lookup_table = &__stack_data_maybe_size_0x14;
                  dereference_pointer_to_byte(&__stack_data_maybe_size_0x14,index);
                  *lookup_table = 1;
                  sVar9 = 0;
                  if ((BYTE_ram_4f20 & BYTE_ram_4f21 & BYTE_ram_4f22 & BYTE_ram_4f23 & BYTE_ram_4f24
                      & BYTE_ram_4f25) != 0) {
                    if (subroutine_DEMO_state == 0) {
                    // WARNING: Return address prevents inlining here
                      add_timed_task(&task_increase_subroutine_PLAYING_state);
                      subroutine_PLAYING_state = subroutine_PLAYING_state + 1;
                      return;
                    }
                    intermission_mode = false;
                    TT02_increase_subroutine_DEMO_state();
                    return;
                  }
                }
              }
            }
          }
        }
      }
    }
    lookup_table = *ppbVar13;
    *(char *)ppbVar13 = (char)(lookup_table + sVar9);
    *(undefined *)((short)ppbVar13 + 1) = (char)((ushort)(lookup_table + sVar9) >> 8);
    ppbVar13 = ppbVar13 + -1;
    bVar2 = (char)(uVar7 >> 8) - 1;
    uVar7 = uVar7 & 0xff | (ushort)bVar2 << 8;
    if (bVar2 == 0) {
      return;
    }
  } while( true );
}



// arrive here from #21A1 when 2nd intermission begins
// 

void mspacman_state_for_2nd_intermission_patch(void)

{
  ushort uVar1;
  byte bVar2;
  char cVar3;
  byte bVar4;
  byte index;
  byte in_C;
  undefined uVar5;
  undefined2 uVar6;
  ushort uVar7;
  byte *pbVar8;
  short sVar9;
  char *pcVar10;
  undefined *puVar11;
  undefined1 *puVar12;
  byte *lookup_table;
  byte **ppbVar13;
  dereference_word_t dVar14;
  word *lookup_table_00;
  
  if (intermission_mode != true) {
                    // WARNING: Return address prevents inlining here
    insert_task(&task_draw_text_or_graphics);
    hardware_screen_maze_area[22][4] = 2;
    BYTE_ARRAY_ARRAY_ram_4440[22][4] = 0x16;
    intermissions_and_attract_mode_animation_main_routine(0xc);
    return;
  }
  if (false) {
    generate_animations(in_C);
  }
  uVar7 = CONCAT11(6,in_C);
  ppbVar13 = animation_current + 5;
  do {
    uVar5 = (undefined)uVar7;
    index = (byte)(uVar7 >> 8);
    lookup_table = *ppbVar13;
    bVar2 = *lookup_table;
    if (bVar2 == 0xf0) {
intermissions_and_attract_mode_animation_main_routine_animation_code_F0_loop:
      bVar2 = dereference_pointer_to_byte(lookup_table,1);
      uVar6 = CONCAT11(index,bVar2);
      dVar14 = dereference_pointer_to_word(WORD_ARRAY_ram_4f2e,index);
      pbVar8 = (byte *)((uint5)dVar14 >> 8);
      bVar2 = animation_code_f0_loop_sub_stuff((char)uVar6 + (char)((uint5)dVar14 >> 0x20));
      *pbVar8 = bVar2;
      lookup_table_00 = (word *)animation_code_f0_and_f1_sub_stuff(uVar6);
      dVar14 = dereference_pointer_to_word(lookup_table_00,(byte)((ushort)uVar6 >> 8));
      index = (byte)((ushort)uVar6 >> 8);
      *(char *)((uint5)dVar14 >> 8) = (char)((uint5)dVar14 >> 0x20) + (char)uVar6;
      bVar2 = dereference_pointer_to_byte(lookup_table,2);
      uVar6 = CONCAT11(index,bVar2);
      dVar14 = dereference_pointer_to_word(WORD_ARRAY_ram_4f2e,index);
      sVar9 = (short)((uint5)dVar14 >> 8);
      bVar2 = animation_code_f0_loop_sub_stuff((char)uVar6 + (char)((uint5)dVar14 >> 0x18));
      *(byte *)(sVar9 + -1) = bVar2;
      lookup_table_00 = (word *)animation_code_f0_and_f1_sub_stuff(uVar6);
      dVar14 = dereference_pointer_to_word(lookup_table_00,(byte)((ushort)uVar6 >> 8));
      *(char *)((short)((uint5)dVar14 >> 8) + -1) = (char)((uint5)dVar14 >> 0x18) + (char)uVar6;
      pcVar10 = &DAT_ram_4f0f;
      index = (byte)((ushort)uVar6 >> 8);
      bVar2 = dereference_pointer_to_byte(&DAT_ram_4f0f,index);
      cVar3 = bVar2 + 1;
      while( true ) {
        dVar14 = dereference_pointer_to_word(WORD_ARRAY_ram_4f3e,index);
        bVar2 = dereference_pointer_to_byte((byte *)((uint5)dVar14 >> 0x18),cVar3 >> 1);
        if (bVar2 != 0xff) break;
        cVar3 = '\0';
      }
      *pcVar10 = cVar3;
      bVar4 = dereference_pointer_to_byte(lookup_table,3);
      dVar14 = dereference_pointer_to_word(&WORD_ram_4f4e,index);
      lookup_table = (byte *)((uint5)dVar14 >> 8);
      *lookup_table = bVar4;
      uVar7 = CONCAT11(index,current_player_number);
      if ((cocktail_mode & current_player_number) != 0) {
        bVar2 = bVar2 ^ 0xc0;
      }
      lookup_table[-1] = bVar2;
      pcVar10 = &animation_cmd_setn;
      bVar2 = dereference_pointer_to_byte(&animation_cmd_setn,index);
      *pcVar10 = bVar2 - 1;
      sVar9 = 0;
      if ((byte)(bVar2 - 1) == '\0') {
        sVar9 = 4;
      }
    }
    else {
      if (bVar2 == 0xf1) {
        lookup_table_00 = (word *)animation_code_f0_and_f1_sub_stuff(uVar7);
        uVar6 = CONCAT11(lookup_table[1],lookup_table[2]);
intermissions_and_attract_mode_animation_main_routine_cleanup_for_return_from_f0_f1_f3:
        dVar14 = dereference_pointer_to_word(lookup_table_00,(byte)(uVar7 >> 8));
        puVar11 = (undefined *)((uint5)dVar14 >> 8);
        *puVar11 = (char)((ushort)uVar6 >> 8);
        puVar11[-1] = (char)uVar6;
        sVar9 = 3;
      }
      else {
        if (bVar2 == 0xf2) {
          uVar1 = uVar7 & 0xff00;
          uVar7 = uVar1 | lookup_table[1];
          puVar12 = &animation_cmd_setn;
          dereference_pointer_to_byte(&animation_cmd_setn,(byte)(uVar1 >> 8));
          *puVar12 = (char)uVar7;
          sVar9 = 2;
        }
        else {
          if (bVar2 == 0xf3) {
            puVar11 = &DAT_ram_4f0f;
            dereference_pointer_to_byte(&DAT_ram_4f0f,index);
            *puVar11 = 0;
            lookup_table_00 = WORD_ARRAY_ram_4f3e;
            uVar6 = *(undefined2 *)(lookup_table + 1);
            goto 
            intermissions_and_attract_mode_animation_main_routine_cleanup_for_return_from_f0_f1_f3;
          }
          if (bVar2 == 0xf5) {
            channel_3_effect.num = lookup_table[1];
            sVar9 = 2;
          }
          else {
            if (bVar2 == 0xf6) {
              pcVar10 = &animation_cmd_setn;
              bVar2 = dereference_pointer_to_byte(&animation_cmd_setn,index);
              *pcVar10 = bVar2 - 1;
              sVar9 = 0;
              if ((byte)(bVar2 - 1) == '\0') {
                sVar9 = 1;
              }
            }
            else {
              if (bVar2 == 0xf7) {
                    // WARNING: Return address prevents inlining here
                insert_task(&task_text_or_graphics_draw_space);
                uVar7 = CONCAT11(index,uVar5);
                sVar9 = 1;
              }
              else {
                if (bVar2 == 0xf8) {
                  hardware_screen_maze_area[22][4] = 0x40;
                  sVar9 = 1;
                }
                else {
                  if (bVar2 != 0xff) {
                    halt();
                    goto 
                    intermissions_and_attract_mode_animation_main_routine_animation_code_F0_loop;
                  }
                  lookup_table = &__stack_data_maybe_size_0x14;
                  dereference_pointer_to_byte(&__stack_data_maybe_size_0x14,index);
                  *lookup_table = 1;
                  sVar9 = 0;
                  if ((BYTE_ram_4f20 & BYTE_ram_4f21 & BYTE_ram_4f22 & BYTE_ram_4f23 & BYTE_ram_4f24
                      & BYTE_ram_4f25) != 0) {
                    if (subroutine_DEMO_state == 0) {
                    // WARNING: Return address prevents inlining here
                      add_timed_task(&task_increase_subroutine_PLAYING_state);
                      subroutine_PLAYING_state = subroutine_PLAYING_state + 1;
                      return;
                    }
                    intermission_mode = false;
                    TT02_increase_subroutine_DEMO_state();
                    return;
                  }
                }
              }
            }
          }
        }
      }
    }
    lookup_table = *ppbVar13;
    *(char *)ppbVar13 = (char)(lookup_table + sVar9);
    *(undefined *)((short)ppbVar13 + 1) = (char)((ushort)(lookup_table + sVar9) >> 8);
    ppbVar13 = ppbVar13 + -1;
    bVar2 = (char)(uVar7 >> 8) - 1;
    uVar7 = uVar7 & 0xff | (ushort)bVar2 << 8;
    if (bVar2 == 0) {
      return;
    }
  } while( true );
}



// arrive here from #229A when 3rd intermission begins
// 

void mspacman_state_for_3rd_intermission_patch(void)

{
  ushort uVar1;
  byte bVar2;
  char cVar3;
  byte bVar4;
  byte index;
  byte in_C;
  undefined uVar5;
  undefined2 uVar6;
  ushort uVar7;
  byte *pbVar8;
  short sVar9;
  char *pcVar10;
  undefined *puVar11;
  undefined1 *puVar12;
  byte *lookup_table;
  byte **ppbVar13;
  dereference_word_t dVar14;
  word *lookup_table_00;
  
  if (intermission_mode != true) {
                    // WARNING: Return address prevents inlining here
    insert_task(&task_draw_text_or_graphics);
    hardware_screen_maze_area[22][4] = 3;
    BYTE_ARRAY_ARRAY_ram_4440[22][4] = 0x16;
    intermissions_and_attract_mode_animation_main_routine(0x18);
    return;
  }
  if (false) {
    generate_animations(in_C);
  }
  uVar7 = CONCAT11(6,in_C);
  ppbVar13 = animation_current + 5;
  do {
    uVar5 = (undefined)uVar7;
    index = (byte)(uVar7 >> 8);
    lookup_table = *ppbVar13;
    bVar2 = *lookup_table;
    if (bVar2 == 0xf0) {
intermissions_and_attract_mode_animation_main_routine_animation_code_F0_loop:
      bVar2 = dereference_pointer_to_byte(lookup_table,1);
      uVar6 = CONCAT11(index,bVar2);
      dVar14 = dereference_pointer_to_word(WORD_ARRAY_ram_4f2e,index);
      pbVar8 = (byte *)((uint5)dVar14 >> 8);
      bVar2 = animation_code_f0_loop_sub_stuff((char)uVar6 + (char)((uint5)dVar14 >> 0x20));
      *pbVar8 = bVar2;
      lookup_table_00 = (word *)animation_code_f0_and_f1_sub_stuff(uVar6);
      dVar14 = dereference_pointer_to_word(lookup_table_00,(byte)((ushort)uVar6 >> 8));
      index = (byte)((ushort)uVar6 >> 8);
      *(char *)((uint5)dVar14 >> 8) = (char)((uint5)dVar14 >> 0x20) + (char)uVar6;
      bVar2 = dereference_pointer_to_byte(lookup_table,2);
      uVar6 = CONCAT11(index,bVar2);
      dVar14 = dereference_pointer_to_word(WORD_ARRAY_ram_4f2e,index);
      sVar9 = (short)((uint5)dVar14 >> 8);
      bVar2 = animation_code_f0_loop_sub_stuff((char)uVar6 + (char)((uint5)dVar14 >> 0x18));
      *(byte *)(sVar9 + -1) = bVar2;
      lookup_table_00 = (word *)animation_code_f0_and_f1_sub_stuff(uVar6);
      dVar14 = dereference_pointer_to_word(lookup_table_00,(byte)((ushort)uVar6 >> 8));
      *(char *)((short)((uint5)dVar14 >> 8) + -1) = (char)((uint5)dVar14 >> 0x18) + (char)uVar6;
      pcVar10 = &DAT_ram_4f0f;
      index = (byte)((ushort)uVar6 >> 8);
      bVar2 = dereference_pointer_to_byte(&DAT_ram_4f0f,index);
      cVar3 = bVar2 + 1;
      while( true ) {
        dVar14 = dereference_pointer_to_word(WORD_ARRAY_ram_4f3e,index);
        bVar2 = dereference_pointer_to_byte((byte *)((uint5)dVar14 >> 0x18),cVar3 >> 1);
        if (bVar2 != 0xff) break;
        cVar3 = '\0';
      }
      *pcVar10 = cVar3;
      bVar4 = dereference_pointer_to_byte(lookup_table,3);
      dVar14 = dereference_pointer_to_word(&WORD_ram_4f4e,index);
      lookup_table = (byte *)((uint5)dVar14 >> 8);
      *lookup_table = bVar4;
      uVar7 = CONCAT11(index,current_player_number);
      if ((cocktail_mode & current_player_number) != 0) {
        bVar2 = bVar2 ^ 0xc0;
      }
      lookup_table[-1] = bVar2;
      pcVar10 = &animation_cmd_setn;
      bVar2 = dereference_pointer_to_byte(&animation_cmd_setn,index);
      *pcVar10 = bVar2 - 1;
      sVar9 = 0;
      if ((byte)(bVar2 - 1) == '\0') {
        sVar9 = 4;
      }
    }
    else {
      if (bVar2 == 0xf1) {
        lookup_table_00 = (word *)animation_code_f0_and_f1_sub_stuff(uVar7);
        uVar6 = CONCAT11(lookup_table[1],lookup_table[2]);
intermissions_and_attract_mode_animation_main_routine_cleanup_for_return_from_f0_f1_f3:
        dVar14 = dereference_pointer_to_word(lookup_table_00,(byte)(uVar7 >> 8));
        puVar11 = (undefined *)((uint5)dVar14 >> 8);
        *puVar11 = (char)((ushort)uVar6 >> 8);
        puVar11[-1] = (char)uVar6;
        sVar9 = 3;
      }
      else {
        if (bVar2 == 0xf2) {
          uVar1 = uVar7 & 0xff00;
          uVar7 = uVar1 | lookup_table[1];
          puVar12 = &animation_cmd_setn;
          dereference_pointer_to_byte(&animation_cmd_setn,(byte)(uVar1 >> 8));
          *puVar12 = (char)uVar7;
          sVar9 = 2;
        }
        else {
          if (bVar2 == 0xf3) {
            puVar11 = &DAT_ram_4f0f;
            dereference_pointer_to_byte(&DAT_ram_4f0f,index);
            *puVar11 = 0;
            lookup_table_00 = WORD_ARRAY_ram_4f3e;
            uVar6 = *(undefined2 *)(lookup_table + 1);
            goto 
            intermissions_and_attract_mode_animation_main_routine_cleanup_for_return_from_f0_f1_f3;
          }
          if (bVar2 == 0xf5) {
            channel_3_effect.num = lookup_table[1];
            sVar9 = 2;
          }
          else {
            if (bVar2 == 0xf6) {
              pcVar10 = &animation_cmd_setn;
              bVar2 = dereference_pointer_to_byte(&animation_cmd_setn,index);
              *pcVar10 = bVar2 - 1;
              sVar9 = 0;
              if ((byte)(bVar2 - 1) == '\0') {
                sVar9 = 1;
              }
            }
            else {
              if (bVar2 == 0xf7) {
                    // WARNING: Return address prevents inlining here
                insert_task(&task_text_or_graphics_draw_space);
                uVar7 = CONCAT11(index,uVar5);
                sVar9 = 1;
              }
              else {
                if (bVar2 == 0xf8) {
                  hardware_screen_maze_area[22][4] = 0x40;
                  sVar9 = 1;
                }
                else {
                  if (bVar2 != 0xff) {
                    halt();
                    goto 
                    intermissions_and_attract_mode_animation_main_routine_animation_code_F0_loop;
                  }
                  lookup_table = &__stack_data_maybe_size_0x14;
                  dereference_pointer_to_byte(&__stack_data_maybe_size_0x14,index);
                  *lookup_table = 1;
                  sVar9 = 0;
                  if ((BYTE_ram_4f20 & BYTE_ram_4f21 & BYTE_ram_4f22 & BYTE_ram_4f23 & BYTE_ram_4f24
                      & BYTE_ram_4f25) != 0) {
                    if (subroutine_DEMO_state == 0) {
                    // WARNING: Return address prevents inlining here
                      add_timed_task(&task_increase_subroutine_PLAYING_state);
                      subroutine_PLAYING_state = subroutine_PLAYING_state + 1;
                      return;
                    }
                    intermission_mode = false;
                    TT02_increase_subroutine_DEMO_state();
                    return;
                  }
                }
              }
            }
          }
        }
      }
    }
    lookup_table = *ppbVar13;
    *(char *)ppbVar13 = (char)(lookup_table + sVar9);
    *(undefined *)((short)ppbVar13 + 1) = (char)((ushort)(lookup_table + sVar9) >> 8);
    ppbVar13 = ppbVar13 + -1;
    bVar2 = (char)(uVar7 >> 8) - 1;
    uVar7 = uVar7 & 0xff | (ushort)bVar2 << 8;
    if (bVar2 == 0) {
      return;
    }
  } while( true );
}



// arrive here from #3E67 after Blinky has been introduced
// 

void demo_mode_move_Blinky_around(void)

{
  intermissions_and_attract_mode_animation_main_routine(0x24);
  return;
}



// arrive here from #3E67 after Pinky has been introduced
// 

void demo_mode_move_Pinky_across(void)

{
  intermissions_and_attract_mode_animation_main_routine(0x30);
  return;
}



// arrive here from #3E67 after Inky has been introduced
// 

void demo_mode_move_Inky_across(void)

{
  intermissions_and_attract_mode_animation_main_routine(0x3c);
  return;
}



// arrive here from #3E67 after Sue has been introduced
// 

void demo_mode_move_Sue_across(void)

{
  intermissions_and_attract_mode_animation_main_routine(0x48);
  return;
}



void demo_mode_move_mspacman_across(void)

{
                    // arrive here from #3e67 after Ms. Pac Man has been introduced
                    // 
  intermissions_and_attract_mode_animation_main_routine(0x54);
  return;
}



// main routine to handle intermissions and attract mode ANIMATIONS
// 

void intermissions_and_attract_mode_animation_main_routine(byte word_intermission_index)

{
  ushort uVar1;
  byte animation_code;
  char cVar2;
  byte bVar3;
  byte index;
  undefined uVar4;
  undefined2 uVar5;
  ushort uVar6;
  byte *pbVar7;
  short sVar8;
  char *pcVar9;
  undefined *puVar10;
  undefined1 *puVar11;
  byte *lookup_table;
  byte **ppbVar12;
  dereference_word_t dVar13;
  word *lookup_table_00;
  
  if (intermission_mode == false) {
    generate_animations(word_intermission_index);
  }
  uVar6 = CONCAT11(6,word_intermission_index);
  ppbVar12 = animation_current + 5;
  do {
                    // get the next ANIMATION code.. (codes return to here when done)
                    // 
    uVar4 = (undefined)uVar6;
    index = (byte)(uVar6 >> 8);
    lookup_table = *ppbVar12;
    animation_code = *lookup_table;
    if (animation_code == 0xf0) {
animation_code_F0_loop:
                    // for value == #F0 - LOOP
                    // 
      animation_code = dereference_pointer_to_byte(lookup_table,1);
      uVar5 = CONCAT11(index,animation_code);
      dVar13 = dereference_pointer_to_word(WORD_ARRAY_ram_4f2e,index);
      pbVar7 = (byte *)((uint5)dVar13 >> 8);
      animation_code = animation_code_f0_loop_sub_stuff((char)uVar5 + (char)((uint5)dVar13 >> 0x20))
      ;
      *pbVar7 = animation_code;
      lookup_table_00 = (word *)animation_code_f0_and_f1_sub_stuff(uVar5);
      dVar13 = dereference_pointer_to_word(lookup_table_00,(byte)((ushort)uVar5 >> 8));
      index = (byte)((ushort)uVar5 >> 8);
      *(char *)((uint5)dVar13 >> 8) = (char)((uint5)dVar13 >> 0x20) + (char)uVar5;
      animation_code = dereference_pointer_to_byte(lookup_table,2);
      uVar5 = CONCAT11(index,animation_code);
      dVar13 = dereference_pointer_to_word(WORD_ARRAY_ram_4f2e,index);
      sVar8 = (short)((uint5)dVar13 >> 8);
      animation_code = animation_code_f0_loop_sub_stuff((char)uVar5 + (char)((uint5)dVar13 >> 0x18))
      ;
      *(byte *)(sVar8 + -1) = animation_code;
      lookup_table_00 = (word *)animation_code_f0_and_f1_sub_stuff(uVar5);
      dVar13 = dereference_pointer_to_word(lookup_table_00,(byte)((ushort)uVar5 >> 8));
      *(char *)((short)((uint5)dVar13 >> 8) + -1) = (char)((uint5)dVar13 >> 0x18) + (char)uVar5;
      pcVar9 = &DAT_ram_4f0f;
      index = (byte)((ushort)uVar5 >> 8);
      animation_code = dereference_pointer_to_byte(&DAT_ram_4f0f,index);
      cVar2 = animation_code + 1;
      while( true ) {
        dVar13 = dereference_pointer_to_word(WORD_ARRAY_ram_4f3e,index);
        animation_code = dereference_pointer_to_byte((byte *)((uint5)dVar13 >> 0x18),cVar2 >> 1);
        if (animation_code != 0xff) break;
        cVar2 = '\0';
      }
      *pcVar9 = cVar2;
      bVar3 = dereference_pointer_to_byte(lookup_table,3);
      dVar13 = dereference_pointer_to_word(&WORD_ram_4f4e,index);
      lookup_table = (byte *)((uint5)dVar13 >> 8);
      *lookup_table = bVar3;
      uVar6 = CONCAT11(index,current_player_number);
      if ((cocktail_mode & current_player_number) != 0) {
        animation_code = animation_code ^ 0xc0;
      }
      lookup_table[-1] = animation_code;
      pcVar9 = &animation_cmd_setn;
      animation_code = dereference_pointer_to_byte(&animation_cmd_setn,index);
      *pcVar9 = animation_code - 1;
      sVar8 = 0;
      if ((byte)(animation_code - 1) == '\0') {
        sVar8 = 4;
      }
    }
    else {
      if (animation_code == 0xf1) {
                    // for value == #F1 - SETPOS
                    // 
        lookup_table_00 = (word *)animation_code_f0_and_f1_sub_stuff(uVar6);
        uVar5 = CONCAT11(lookup_table[1],lookup_table[2]);
cleanup_for_return_from_f0_f1_f3:
                    // It's my gyess that the jr at 3588 and the lack of code #F4
                    // are related.  In fitting with the style of the other F-commands,
                    // they all end with a jr to 0x358a, including this one.
                    // I think that in the source code, they removed whatever #F4
                    // was, but forgot to erase the jr just before it, so you end up with
                    // a jr to the next instruction.  -scott
                    // 
        dVar13 = dereference_pointer_to_word(lookup_table_00,(byte)(uVar6 >> 8));
        puVar10 = (undefined *)((uint5)dVar13 >> 8);
        *puVar10 = (char)((ushort)uVar5 >> 8);
        puVar10[-1] = (char)uVar5;
        sVar8 = 3;
      }
      else {
        if (animation_code == 0xf2) {
                    // for value = #F2 - SETN
                    // 
          uVar1 = uVar6 & 0xff00;
          uVar6 = uVar1 | lookup_table[1];
          puVar11 = &animation_cmd_setn;
          dereference_pointer_to_byte(&animation_cmd_setn,(byte)(uVar1 >> 8));
          *puVar11 = (char)uVar6;
          sVar8 = 2;
        }
        else {
          if (animation_code == 0xf3) {
                    // for value == #F3 - SETCHAR
                    // 
            puVar10 = &DAT_ram_4f0f;
            dereference_pointer_to_byte(&DAT_ram_4f0f,index);
            *puVar10 = 0;
            lookup_table_00 = WORD_ARRAY_ram_4f3e;
            uVar5 = *(undefined2 *)(lookup_table + 1);
            goto cleanup_for_return_from_f0_f1_f3;
          }
          if (animation_code == 0xf5) {
                    // for value == #F5 - PLAYSOUND
                    // 
            channel_3_effect.num = lookup_table[1];
            sVar8 = 2;
          }
          else {
            if (animation_code == 0xf6) {
                    // for value == #F6 - PAUSE
                    // 
              pcVar9 = &animation_cmd_setn;
              animation_code = dereference_pointer_to_byte(&animation_cmd_setn,index);
              *pcVar9 = animation_code - 1;
              sVar8 = 0;
              if ((byte)(animation_code - 1) == '\0') {
                sVar8 = 1;
              }
            }
            else {
              if (animation_code == 0xf7) {
                    // for value == #F7 - SHOWACT ?
                    // 
                    // WARNING: Return address prevents inlining here
                insert_task(&task_text_or_graphics_draw_space);
                uVar6 = CONCAT11(index,uVar4);
                sVar8 = 1;
              }
              else {
                if (animation_code == 0xf8) {
                    // for value == #F8 - CLEARACT
                    // 
                  hardware_screen_maze_area[22][4] = 0x40;
                  sVar8 = 1;
                }
                else {
                  if (animation_code != 0xff) {
                    halt();
                    goto animation_code_F0_loop;
                  }
                    // for value == #FF (end code)
                    // 
                  lookup_table = &__stack_data_maybe_size_0x14;
                  dereference_pointer_to_byte(&__stack_data_maybe_size_0x14,index);
                  *lookup_table = 1;
                  sVar8 = 0;
                  if ((BYTE_ram_4f20 & BYTE_ram_4f21 & BYTE_ram_4f22 & BYTE_ram_4f23 & BYTE_ram_4f24
                      & BYTE_ram_4f25) != 0) {
                    if (subroutine_DEMO_state == 0) {
                    // WARNING: Return address prevents inlining here
                      add_timed_task(&task_increase_subroutine_PLAYING_state);
                      subroutine_PLAYING_state = subroutine_PLAYING_state + 1;
                      return;
                    }
                    intermission_mode = false;
                    TT02_increase_subroutine_DEMO_state();
                    return;
                  }
                }
              }
            }
          }
        }
      }
    }
                    // finish up for the above
                    // 
                    // DE = relative seek to the next animation code
                    // original pac rom:
                    // data - level pill information
                    // 
    lookup_table = *ppbVar12;
    *(char *)ppbVar12 = (char)(lookup_table + sVar8);
    *(undefined *)((short)ppbVar12 + 1) = (char)((ushort)(lookup_table + sVar8) >> 8);
    ppbVar12 = ppbVar12 + -1;
    animation_code = (char)(uVar6 >> 8) - 1;
    uVar6 = uVar6 & 0xff | (ushort)animation_code << 8;
    if (animation_code == 0) {
      return;
    }
  } while( true );
}



byte animation_code_f0_loop_sub_stuff(byte param_1)

{
  if ((char)param_1 < '\0') {
                    // arrive here when ghost is moving up the left side of the marquee
    param_1 = param_1 | 0xf0;
  }
  else {
    param_1 = param_1 & 0xf;
  }
  return param_1;
}



// arrive here at intermissions and attract mode called from above, with C preloaded with an offset
// depending on which intermission / attract mode we are in

void generate_animations(byte animation_seek_index)

{
  short len;
  undefined **dst;
  undefined *src;
  
  if (subroutine_DEMO_state == 0) {
    channel_1_wave.num = 2;
    channel_2_wave.num = 2;
  }
                    // this is used to generate the animations with the animation programs stored in
                    // the tables
  src = (undefined *)((short)animation_intermission1 + (ushort)animation_seek_index);
  dst = animation_current;
  len = 0xc;
  do {
    *(undefined *)dst = *src;
    dst = (undefined **)((short)dst + 1);
    src = src + 1;
    len = len + -1;
  } while (len != 0);
  intermission_mode = true;
  number_of_ghost_killed_but_no_collision_for_yet = 1;
  pacman_dead_animation_state = 0;
  memset(&__stack_data_maybe_size_0x14,0,0x14);
  return;
}



word animation_code_f0_and_f1_sub_stuff(undefined2 param_1)

{
  if ((char)((ushort)param_1 >> 8) == '\x06') {
    return (word)&counter__started_after_pacman_killed;
  }
  return 0x4cfe;
}



void mspacman_select_song(ushort param_1,word *param_2,byte *param_3,short param_4)

{
  byte bVar1;
  char cVar2;
  undefined uVar3;
  byte index;
  ushort uVar4;
  byte *pbVar5;
  undefined *puVar6;
  dereference_word_t dVar7;
  undefined2 uStack4;
  ushort uStack2;
  
  index = (char)(param_1 >> 8) - 1;
  uStack2 = param_1 & 0xff | (ushort)index << 8;
                    // adapt B to the current level to find out the song number
                    // 
  if (index == 1) {
    index = 1;
    if ((current_level != 1) && (index = 2, current_level != 4)) {
      index = 3;
    }
  }
  else {
    index = 0;
  }
  uStack4 = 0x366b;
  dVar7 = dereference_pointer_to_word(param_2,index);
  pbVar5 = (byte *)((uint5)dVar7 >> 0x18);
  puVar6 = (undefined *)register0x44;
  while( true ) {
    index = *pbVar5;
    *(undefined *)(param_4 + 6) = (char)(pbVar5 + 1);
    *(undefined *)(param_4 + 7) = (char)((ushort)(pbVar5 + 1) >> 8);
    if (index < 0xf0) break;
    *(undefined2 *)(puVar6 + -2) = 0x2d6c;
                    // WARNING: Return address prevents inlining here
    *(undefined2 *)(puVar6 + -4) = 0x2d85;
    jump_table_fn(*(undefined **)(puVar6 + -4),index & 0xf);
    pbVar5 = *(byte **)(param_4 + 6);
    puVar6 = puVar6 + -2;
  }
                    //  process regular byte (A=byte to process, it's not a special byte)
                    // 
  if ((index & 0x1f) != 0) {
    *(byte *)(param_4 + 0xd) = index;
  }
  uVar3 = *(undefined *)(param_4 + 9);
  if ((*(byte *)(param_4 + 0xb) & 8) != 0) {
    uVar3 = 0;
  }
  *(undefined *)(param_4 + 0xf) = uVar3;
  *(undefined2 *)(puVar6 + -2) = 0x2dc6;
  bVar1 = dereference_pointer_to_byte
                    (song_lookup_tables,
                     ((index >> 7) << 1 | (index << 1) >> 7) << 1 |
                     ((index << 1 | index >> 7) << 1) >> 7,puVar6[-2]);
                    // Note: this is just A = 2**A
                    // 
  *(byte *)(param_4 + 0xc) = bVar1;
  if ((index & 0x1f) != 0) {
    *(undefined2 *)(puVar6 + -2) = 0x2dd4;
    index = dereference_pointer_to_byte(BYTE_ARRAY_ARRAY_ram_3bb8,index & 0xf,puVar6[-2]);
    *(byte *)(param_4 + 0xe) = index;
  }
                    //  compute wave frequency
                    // 
  uVar4 = (ushort)*(byte *)(param_4 + 0xe);
  index = *(byte *)(param_4 + 0xd) & 0x10;
  if (index != 0) {
    index = 1;
  }
  cVar2 = index + *(char *)(param_4 + 4);
  while (cVar2 != '\0') {
    uVar4 = uVar4 * 2;
    cVar2 = cVar2 + -1;
  }
  bVar1 = (byte)uVar4;
                    // HL = HL * 2**B
                    // now extract the nibbles from HL
                    // 
  *param_3 = bVar1;
  index = bVar1 >> 1;
  param_3[1] = (((index | bVar1 << 7) >> 1 | index << 7) >> 1 | ((index & 2) >> 1) << 7) >> 1 |
               ((index & 4) >> 2) << 7;
  bVar1 = (byte)(uVar4 >> 8);
  param_3[2] = bVar1;
  index = bVar1 >> 1;
  param_3[3] = (((index | bVar1 << 7) >> 1 | index << 7) >> 1 | ((index & 2) >> 1) << 7) >> 1 |
               ((index & 4) >> 2) << 7;
  index = *(byte *)(param_4 + 0xb);
                    // WARNING: Return address prevents inlining here
  *(undefined2 *)(puVar6 + -2) = 0x2f02;
  jump_table_fn(*(undefined **)(puVar6 + -2),index);
  return;
}



void clear_fruit_position(void)

{
  fruit_coord = 0;
                    // arrive here from #100B, continuation of task #05
                    // 
  return;
}



void FUN_ram_367f(void)

{
                    // can't find a call to here ???
                    // 
  mspac_sprite._0_1_ = ~((pacman_coord.y & 0xf) >> 2) + 0x1c;
  if (mspac_sprite._0_1_ == '\x18') {
    mspac_sprite._0_1_ = '6';
  }
  return;
}



void draw_easter_egg__Made_By_Namco(void)

{
  ushort uVar1;
  byte bVar2;
  byte bVar3;
  byte *pbVar4;
  byte bVar5;
  byte *pbVar6;
  
                    // 
                    // 
                    //  ; Draw the "Made By Namco" text (egg)
                    // 
                    // 
  pbVar6 = hardware_screen_maze_area + 0x62;
  pbVar4 = easter_egg__namco;
  while( true ) {
    *pbVar6 = 0x14;
    bVar2 = *pbVar4;
    if (bVar2 == 0) break;
    pbVar4 = pbVar4 + 1;
    bVar5 = (byte)pbVar6;
    bVar3 = bVar2 + bVar5;
    uVar1 = (ushort)pbVar6 & 0xff00;
    pbVar6 = (byte *)(uVar1 | bVar3);
    if (CARRY1(bVar2,bVar5) != false) {
      pbVar6 = (byte *)CONCAT11((char)(uVar1 >> 8) + '\x01',bVar3);
    }
  }
  return;
}



// new code for ms-pacman.  used during demo mode, when there are no credits
// 

void execute_DEMO_task_state_patch(void)

{
  if (subroutine_DEMO_state != 0x10) {
    flashing_bulbs_around_the_marquee();
  }
                    // WARNING: Return address prevents inlining here
  jump_table_fn((undefined *)demo_mode_fn_table,subroutine_DEMO_state);
  return;
}



void demo_mode_display_MS_pacman(void)

{
                    // WARNING: Return address prevents inlining here
                    // arrive here from #3E67 when sub# == 2
                    // 
  insert_task(&task_draw_text_or_graphics_ms_pacman);
  _STACK_START = 0x60;
  TT02_increase_subroutine_DEMO_state();
  return;
}



void demo_mode_draw_the_midway_logo_and_copyright(void)

{
                    // draw the midway logo and cprt for the attract screen
                    // 
  draw_the_midway_logo_and_copyright();
  TT02_increase_subroutine_DEMO_state();
  return;
}



void demo_mode_display_Blinky(void)

{
                    // WARNING: Return address prevents inlining here
  insert_task(&task_draw_text_or_graphics_blinky);
  TT02_increase_subroutine_DEMO_state();
  return;
}



void demo_mode_clear_with_display_Pinky(char param_1)

{
                    // WARNING: Return address prevents inlining here
  insert_task(&task_draw_text_or_graphics_space);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_draw_text_or_graphics_pinky);
  TT02_increase_subroutine_DEMO_state();
  return;
}



void demo_mode_display_Inky(void)

{
                    // WARNING: Return address prevents inlining here
  insert_task(&task_draw_text_or_graphics_inky);
  TT02_increase_subroutine_DEMO_state();
  return;
}



void demo_mode_display_Sue(void)

{
                    // WARNING: Return address prevents inlining here
  insert_task(&task_draw_text_or_graphics_sue);
  TT02_increase_subroutine_DEMO_state();
  return;
}



void demo_mode_display_Ms_pacman(void)

{
                    // WARNING: Return address prevents inlining here
  insert_task(&task_draw_text_or_graphics_ms_pac_man);
  TT02_increase_subroutine_DEMO_state();
  return;
}



void demo_mode_display_with(void)

{
                    // WARNING: Return address prevents inlining here
  insert_task(&task_draw_text_or_graphics_with);
  TT02_increase_subroutine_DEMO_state();
  return;
}



void demo_mode_display_Starring(undefined2 param_1)

{
                    // WARNING: Return address prevents inlining here
  insert_task(&task_draw_text_or_graphics_starring);
  TT02_increase_subroutine_DEMO_state();
  return;
}



void demo_mode_start_demo_mode_where_mspacman_plays_herself(void)

{
                    // demo mode when ms pac plays herself in the maze
                    // 
  real_number_of_lives = 0;
  pacman_end_demo_and_return();
  return;
}



// this sub controls the flashing bulbs around the marquee in the attract screen
// 

void flashing_bulbs_around_the_marquee(void)

{
  byte bVar1;
  byte bVar2;
  ushort uVar3;
  short sVar4;
  
  bVar1 = _STACK_START + 1;
  _STACK_START = bVar1 & 0xf;
  bVar2 = bVar1 & 0xe;
  uVar3 = (ushort)bVar2;
  if ((bVar1 & 1) != 0) {
    **(undefined **)(BYTE_ARRAY_ram_3f80 + uVar3 + 1) = 0x87;
    **(undefined **)(BYTE_ARRAY_ram_3f80 + uVar3 + 0x11) = 0x87;
    **(undefined **)(BYTE_ARRAY_ram_3f80 + uVar3 + 0x21) = 0x8a;
    **(undefined **)(BYTE_ARRAY_ram_3f80 + uVar3 + 0x31) = 0x81;
    **(undefined **)(BYTE_ARRAY_ram_3f80 + uVar3 + 0x41) = 0x81;
    **(undefined **)(BYTE_ARRAY_ram_3f80 + uVar3 + 0x51) = 0x84;
    return;
  }
  sVar4._1_1_ = 0;
  if ((char)(bVar2 - 1) < '\x01') {
    sVar4._1_1_ = 0xff;
  }
  sVar4 = CONCAT11(sVar4._1_1_,bVar2 - 2);
  **(char **)(BYTE_ARRAY_ram_3f80 + sVar4 + 1) = **(char **)(BYTE_ARRAY_ram_3f80 + sVar4 + 1) + -1;
  **(undefined **)(BYTE_ARRAY_ram_3f80 + sVar4 + 3) = 0x88;
  **(char **)(BYTE_ARRAY_ram_3f80 + sVar4 + 0x11) =
       **(char **)(BYTE_ARRAY_ram_3f80 + sVar4 + 0x11) + -1;
  **(undefined **)(BYTE_ARRAY_ram_3f80 + sVar4 + 0x13) = 0x88;
  **(char **)(BYTE_ARRAY_ram_3f80 + sVar4 + 0x21) =
       **(char **)(BYTE_ARRAY_ram_3f80 + sVar4 + 0x21) + -1;
  **(undefined **)(BYTE_ARRAY_ram_3f80 + sVar4 + 0x23) = 0x8b;
  **(char **)(BYTE_ARRAY_ram_3f80 + sVar4 + 0x31) =
       **(char **)(BYTE_ARRAY_ram_3f80 + sVar4 + 0x31) + -1;
  **(undefined **)(BYTE_ARRAY_ram_3f80 + sVar4 + 0x33) = 0x82;
  **(char **)(BYTE_ARRAY_ram_3f80 + sVar4 + 0x41) =
       **(char **)(BYTE_ARRAY_ram_3f80 + sVar4 + 0x41) + -1;
  **(undefined **)(BYTE_ARRAY_ram_3f80 + sVar4 + 0x43) = 0x82;
  **(char **)(BYTE_ARRAY_ram_3f80 + sVar4 + 0x51) =
       **(char **)(BYTE_ARRAY_ram_3f80 + sVar4 + 0x51) + -1;
                    // BUGFIX04 - Marquee left side animation fix - Don Hodges
                    // 3f7c 36 85
  **(undefined **)(BYTE_ARRAY_ram_3f80 + sVar4 + 0x53) = 0x83;
  return;
}



// end data
// 
// resume program
// 
// arrive from #168C when ms pac is facing right
// MSPAC MOVING EAST

void mspac_moving_east(void)

{
  mspac_sprite._0_1_ = ~((pacman_coord.x & 7) >> 1) + 0x30;
  if ((mspac_sprite._0_1_ & 1) == 0) {
    mspac_sprite._0_1_ = 0x37;
  }
  return;
}



void O01_moving_south(void)

{
                    // arrive from #16B1 when ms pac is facing down
                    // MSPAC MOVING SOUTH
                    // 
  mspac_sprite._0_1_ = ((pacman_coord.y & 7) >> 1) + 0x30;
  if ((mspac_sprite._0_1_ & 1) == 0) {
    mspac_sprite._0_1_ = 0x34;
  }
  return;
}



// arrive from #16FA when ms pac is facing up
// MSPAC MOVING NORTH
// 

void mspacman_moving_north(void)

{
  mspac_sprite._0_1_ = ~((pacman_coord.y & 7) >> 1) - 0xc;
  if ((mspac_sprite._0_1_ & 1) == 0) {
    mspac_sprite._0_1_ = 0x36;
  }
  return;
}



void check_for_fruit_to_come_out(void)

{
  byte bVar1;
  byte bVar2;
  byte *lookup_table;
  bool *pbVar3;
  difficulty5_fruit_release_t *pdVar4;
  undefined **ppuVar5;
  byte in_R;
  dereference_word_t dVar6;
  
                    // subroutine called from #0909, per intermediate jump at #0EAD
                    // 
  if (number_of_ghost_killed_but_no_collision_for_yet != 0) {
    return;
  }
  if ((fruit_points == 0) || (fruit_coord.y == 0)) {
                    // arrive here from #86FE
                    // to check to see if it is time for a new fruit to be released
                    // only called when a fruit is not already onscreen
                    // 
    if (dots_eaten == 0x40) {
      pbVar3 = &first_fruit_flag;
    }
    else {
      if (dots_eaten != 0xb0) {
        return;
      }
      pbVar3 = &second_fruit_flag;
    }
    if (*pbVar3 != false) {
      return;
    }
    *pbVar3 = *pbVar3 + '\x01';
                    //  Ms. Pacman Random Fruit Probabilities
                    //  (c) 2002 Mark Spaeth
                    //  http://rgvac.978.org/files/MsPacFruit.txt
                    // A hotly contested issue on rgvac. here's an explanation
                    // of how the random fruit selection routine works in Ms.
                    // Pacman, and the probabilities associated with the routine:
                    // 
    bVar2 = current_level;
    if (6 < current_level) {
                    //  selector for random fruits
                    //  uses r register to get a random number
                    // 
      bVar1 = in_R & 0x1f;
      do {
        bVar2 = bVar1;
                    //  Compute ((R % 32) % 7)
                    // 
        bVar1 = bVar2 - 7;
      } while (6 < bVar2);
    }
    pdVar4 = fruit_shape_color_points;
    fruit_sprite._0_1_ =
         dereference_pointer_to_byte((byte *)fruit_shape_color_points,bVar2 * '\x03');
    fruit_sprite.color = pdVar4->color;
    fruit_points = pdVar4->point;
                    // So, a little more background...
                    // The 'R' register is the dram refresh address register
                    // that is not initalized on startup, so it has garbage
                    // in it.  During every instruction fetch, the counter is
                    // incremented.  Assume on average 4 clock cycles per
                    // instruction, with the clock running at 3.072 Mhz, this
                    // counter is incremented every 1.3us, so if you read it
                    // at any time, it's gonna be pretty damn random.  Of
                    // course, it doesn't just get read at any time, since
                    // the fruit select routine is called during the vertical
                    // blank every 1/60sec, but since the instruction
                    // counts between reads are not all the say, it's still
                    // random to better than 1/60 sec, which is still too fast
                    // for any player to count off.
                    // So, now, assuming that the counter is random, the bottom
                    // 5 bits are hacked off giving a number 0-31 (each with
                    // probability 1/32), and this number modulo 7 is used to
                    // determine which fruit appears...
                    // So...
                    // 0, 7,14,21,28  ->  Cherry         100 pts @ 5/32 = 15.625 %
                    // 1, 8,15,22,29  ->  Strawberry     200 pts @ 5/32 = 15.625 %
                    // 2, 9,16,23,30  ->  Orange         500 pts @ 5/32 = 15.625 %
                    // 3,10,17,24,31  ->  Pretzel        700 pts @ 5/32 = 15.625 %
                    // 4,11,18,25     ->  Apple         1000 pts @ 4/32 = 12.5   %
                    // 5,12,19,26     ->  Pear          2000 pts @ 4/32 = 12.5   %
                    // 6,13,20,27     ->  Banana        5000 pts @ 4/32 = 12.5   %
                    // Also interesting to note is that the expected value of
                    // the random fruit is 1234.375 points, which is useful
                    // in determining a good estimate of what the killscreen
                    // score should be.  The standard deviation of this
                    // distribution is 1532.891 / sqrt(n), where n is the
                    // number of random fruits eaten, so at the level 243 (?)
                    // killscreen, (243-7)*2 = 472 fruits have been eaten,
                    // and the SD falls to 21.726, so it should be pretty easy
                    // to tell if the fruit distribution has been tampered
                    // with.  This SD across 472 fruits is +/- 10k from the
                    // mean, is approximaely the difference between the top
                    // 3 players in twin galaxies, but given the game crash
                    // issue, the number of levels the game lets you play is
                    // probably a more poingant indicator than the fruits
                    // given.
                    // How to cheat:
                    // -------------
                    // Of course, if you want to be cutesy you can play with
                    // the distribution, by say changing 876b to 0x3f, thus
                    // doing 0-63 mod 7 to choose the fruit, bumping the
                    // average up to 1337.5, but at an extra 100 points a
                    // fruit, thats 47,200 points on average, and without a
                    // close statistical analysis like the one I've provided
                    // (which shows that this is almost 5 standard deviations
                    // above the mean), you could probably get away with it
                    // in competition.
                    // If you really wanted to be cheezy, you could change
                    // 0x876b to 0x06, so that only cherry, orange, apple,
                    // and banana come up, and all have equal probability.
                    // That would bump your fruit average up to 1650, but the
                    // absence of strawberries, pretzels, and pears would be
                    // pretty obvious.
                    // These changes would't require any other changes in the
                    // code, but it's also possible to completely rewrite the
                    // routine, in a different part of the code space to do
                    // something different, but that's an exercise left to
                    // the reader.  (Perhaps the simplest would be to add 3
                    // after the mod 32 operation, so that Pretzel-Banana are
                    // slightly more likely than Cherry-Orange).
                    // If you really want to be lame, you can edit the scoring
                    // table at 0x2b17 (many pacman bootlegs did this).
                    // Seriously, you could probably add 10 points to each
                    // value, and the 'judges' couldn't tell whether or not
                    // you were eating a dot while eating the fruit in many
                    // situations, and you could get almost 5000 extra points
                    // )
                    // One other 'cool' thing to do would be to chage 0x8763
                    // to 0x08, which would utilize the 8th fruit on the 8th
                    // board, and subsequently would give you even odds on
                    // all of the fruit, but since the junior icon and the
                    // banana are both 5000, the average skews WAY up to 1812.5
                    // points.
                    // [To keep things fair, though, note that the junior
                    // fruit uses color code 0x00, which is to say, all black,
                    // so you'd have to find the invisible fruit.  Since the
                    // fruit patterns are pretty well known, that's probably
                    // not that big of a deal for top players.]
                    //  select the proper fruit path from the table at 87f8
                    // 
    ppuVar5 = fruits_paths_entry;
    setup_fruit_path();
    fruit_coord = *(undefined2 *)((short)ppuVar5 + 1);
    return;
  }
  dVar6 = dereference_pointer_to_word((word *)BYTE_ARRAY_ram_8841,current_place_within_bounce);
  fruit_coord = (short)((uint5)dVar6 >> 0x18) + fruit_coord;
  current_place_within_bounce = current_place_within_bounce + 1;
  if ((current_place_within_bounce & 0xf) != 0) {
    return;
  }
  bVar2 = current_place_in_fruit_path - 1;
  current_place_in_fruit_path = bVar2;
  if (-1 < (char)bVar2) {
    channel_3_effect.num = channel_3_effect.num | 0x20;
    bVar1 = dereference_pointer_to_byte
                      (pointer_to_the_path_the_fruit_is_currently_following,bVar2 >> 2);
    bVar2 = bVar2 & 3;
    while (bVar2 != 0) {
      bVar1 = bVar1 >> 2;
      bVar2 = bVar2 - 1;
    }
    current_place_within_bounce = (bVar1 & 3) << 4;
    return;
  }
                    // For reference, the score table is at 0x2b17
                    // arrive here from #871D
                    // 
  fruit_coord.x = (byte)((ushort)fruit_coord >> 8);
  if (0x3f < (byte)(fruit_coord.x + 0x20)) {
    if (pointer_to_the_path_the_fruit_is_currently_following == BYTE_ARRAY_ram_8808) {
      lookup_table = get_maze_data_from_current_level((byte *)fruit_paths_exit);
      bVar2 = dereference_pointer_to_byte(lookup_table,(in_R & 3) * '\x05');
      pointer_to_the_path_the_fruit_is_currently_following = (byte *)CONCAT11(lookup_table[1],bVar2)
      ;
      current_place_in_fruit_path = lookup_table[2];
    }
    else {
                    // arrive here from #87C8
                    // 
      pointer_to_the_path_the_fruit_is_currently_following = BYTE_ARRAY_ram_8808;
      current_place_in_fruit_path = 0x1d;
    }
    current_place_within_bounce = 0x1f;
    return;
  }
                    // arrive here from #87BC, when fruit exits screen on its own (not eaten)
                    // 
  fruit_sprite.color = fruit;
  TT04_clear_fruit_points();
  return;
}



void setup_fruit_path(byte *param_1)

{
  byte bVar1;
  byte *lookup_table;
  byte in_R;
  
  lookup_table = get_maze_data_from_current_level(param_1);
  bVar1 = dereference_pointer_to_byte(lookup_table,(in_R & 3) * '\x05');
  current_place_in_fruit_path = lookup_table[2];
  current_place_within_bounce = 0x1f;
  pointer_to_the_path_the_fruit_is_currently_following = CONCAT11(lookup_table[1],bVar1);
  return;
}



byte * get_current_maze_table(void)

{
  byte *pbVar1;
  
                    // select the proper maze
                    // called from #241C
                    // 
  pbVar1 = get_maze_data_from_current_level((byte *)maze_lookup_table);
  return pbVar1;
}



// check the number of pellets to see if the board is cleared
// 

void check_if_board_is_cleared(undefined param_1)

{
  byte *pbVar1;
  
  pbVar1 = get_maze_data_from_current_level((byte *)pellet_count_lookup_table);
  if (dots_eaten == *pbVar1) {
    goto_state_P0C();
    return;
  }
                    //  pacman original:
                    // load A with number of pellets eaten
                    // == 244 ?
                    // No, jump ahead
                    // Yes, then end of level.  Load HL with main subroutine #
                    // store #0C into main sub #to signal end of level
                    // return
                    // returns here if level is not complete
                    // core game loop
                    // 
  update_ghost_and_pacman_state();
  update_ghost_and_pacman_state();
  is_time_to_leave_house();
  adjust_ghost_movement(param_1);
  is_time_to_change_ghost_animation();
  is_time_to_reverse_ghost_direction();
  handle_ghost_flashing_and_colors_when_power_pills_are_eaten();
  pacman_only_set_color_for_dead_ghost();
  handle_power_pill_flashes();
  change_background();
  check_for_fruit_to_come_out();
  return;
}



// Used to determine which maze to draw and other things
// load BC with a value based on the level and the value already loaded into HL.
// This keeps the game cycling between the 3rd and 4th mazes, which appear on levels 6 through 14.
// 

byte * get_maze_data_from_current_level(byte *maze_lookup_table)

{
  byte index;
  char cVar1;
  
  index = current_level;
  if (-1 < (char)(((char)(current_level - 0xd) < '\0') << 7)) {
    cVar1 = current_level - 0xd;
    do {
      cVar1 = cVar1;
      cVar1 = cVar1 + -8;
    } while (-1 < (char)((cVar1 < '\0') << 7));
    index = cVar1 + 5;
  }
  index = dereference_pointer_to_byte(map_order_table,index);
  return *(byte **)(maze_lookup_table + (byte)(index * '\x02'));
}



// draw routine for the ms-pac power pellets

void mspacman_died_pellet_routine_load(void)

{
  byte *pbVar1;
  byte *pbVar2;
  byte **ppbVar3;
  
  ppbVar3 = (byte **)get_maze_data_from_current_level((byte *)power_pellet_per_map_lookup_table);
  pbVar2 = power_pills_data_entries;
  do {
    pbVar1 = *ppbVar3;
    ppbVar3 = ppbVar3 + 1;
    *pbVar1 = *pbVar2;
    pbVar2 = pbVar2 + 1;
  } while (((ushort)pbVar2 & 3) != 0);
  return;
}



// ms pac man patch for pellet routine
// jumped from #24b4
// arrive here after ms. pac has died
// this sub is identical to subroutine above, except it saves the power pellets instead of drawing
// them
// 

void mspacman_died_pellet_routine_save(void)

{
  byte *pbVar1;
  byte *pbVar2;
  byte **ppbVar3;
  
  ppbVar3 = (byte **)get_maze_data_from_current_level((byte *)power_pellet_per_map_lookup_table);
  pbVar2 = power_pills_data_entries;
  do {
    pbVar1 = *ppbVar3;
    ppbVar3 = ppbVar3 + 1;
    *pbVar2 = *pbVar1;
    pbVar2 = pbVar2 + 1;
  } while (((ushort)pbVar2 & 3) != 0);
  return;
}



// arrive here for blue ghost logic when random mode enabled from #27BB

void pick_quadrant_for_blue_ghost_direction(void)

{
  pick_quadrant();
  return;
}



// arrive here for orange ghost logic when random mode enabled from #2803

undefined2 pick_quadrant_for_orange_ghost_direction(void)

{
  byte bVar1;
  byte *lookup_table;
  byte in_R;
  
  lookup_table = get_maze_data_from_current_level((byte *)ghost_destination_lookup_table);
  bVar1 = dereference_pointer_to_byte(lookup_table,in_R & 6);
  return CONCAT11(lookup_table[1],bVar1);
}



// pick a quadrant for the destination of a ghost, saved into DE

undefined2 pick_quadrant(void)

{
  byte bVar1;
  byte *lookup_table;
  byte in_R;
  
  lookup_table = get_maze_data_from_current_level((byte *)ghost_destination_lookup_table);
  bVar1 = dereference_pointer_to_byte(lookup_table,in_R & 6);
  return CONCAT11(lookup_table[1],bVar1);
}



// called from #23A7 for task = #1C
// prints text or graphics based on parameter loaded into B
// 

void T1C_draw_text_or_graphics(byte param)

{
  byte index;
  
  index = param;
  if (param == TILE_MSPACMAN) {
    param = prepare_draw_mspacman();
  }
  if (param == TILE_MIDWAY_LOGO_AND_COPYRIGHT_TEXT) {
    param = prepare_draw_midway_logo_and_copyright_text(index);
  }
  if (param == TILE_READY) {
    prepare_draw_READY();
  }
  DrawText(index);
  return;
}



byte prepare_draw_midway_logo_and_copyright_text(byte param_1)

{
  byte bVar1;
  
  draw_the_midway_logo_and_copyright();
  bVar1 = read_volatile_1(hardware_DSW1);
  if ((bVar1 & 0x30) != 0x30) {
    return param_1;
  }
  return 0x20;
}



void prepare_draw_mspacman(void)

{
  draw_multiple_tile(mspac_graph);
  return;
}



// subroutine for start button press
// called from #9610
// draws the MS PAC MAN which appears between "ADDITIONAL" and "AT 10,000 pts"

void draw_multiple_tile(mspac_graph_t *p_graph_tile)

{
  tile_e *ptr;
  color_e color;
  
  color = p_graph_tile->color;
  if (color != NONE) {
    ptr = p_graph_tile->ptr;
    *ptr = p_graph_tile->graphic_tile_code;
                    // TODO: here, seek to hardware_color_ram
    *(color_e *)((ushort)ptr | 0x400) = color;
    draw_multiple_tile(p_graph_tile + 1);
    return;
  }
  return;
}



// clears intermission indicator

void prepare_draw_READY(void)

{
  intermission_mode = false;
  return;
}



// draws title screen logo and text (sets as tasks).  called from #95F8
// this on pac draws the ghost (logo) and CLYDE" text

void draw_the_midway_logo_and_copyright(void)

{
  byte bVar1;
  byte *pbVar2;
  
                    // WARNING: Return address prevents inlining here
  insert_task(&task_draw_text_or_graphics_c_midway_mfg_co);
                    // WARNING: Return address prevents inlining here
  insert_task(&task_draw_text_or_graphics_t_1980_1981);
  pbVar2 = hardware_screen_maze_area + 0x25a;
  bVar1 = 0xbf;
  do {
    *pbVar2 = bVar1;
    pbVar2[0x400] = 1;
    pbVar2 = pbVar2 + -(ushort)(ARRAY_ram_a000 + 0x5bff < pbVar2);
    pbVar2[1] = bVar1 - 4;
    pbVar2[0x401] = 1;
    pbVar2 = pbVar2 + (pbVar2 + 1 <= ARRAY_ram_a000 + 0x5bff);
    pbVar2[1] = bVar1 - 8;
    pbVar2[0x401] = 1;
    pbVar2 = pbVar2 + (pbVar2 + 1 <= ARRAY_ram_a000 + 0x5bff);
    pbVar2[1] = bVar1 - 0xc;
    pbVar2[0x401] = 1;
    pbVar2 = pbVar2 + 0x401 + (-0x3e3 - (ushort)(ARRAY_ram_a000 + 0x5bff < pbVar2 + 1));
    bVar1 = bVar1 - 1;
  } while (bVar1 != 0xbb);
  return;
}



// something with sprites for cocktail?

void backup_sprites__then__check_cocktail_animation_end__then__mspacman_channel_1_song_table(void)

{
  byte bVar1;
  short sVar2;
  hardware_floating_sprite_t *phVar3;
  hardware_floating_sprite_t *phVar4;
  
  if (intermission_mode != false) {
    phVar3 = &red_ghost_sprite;
    phVar4 = &sprites_copy;
    sVar2 = 0xc;
    do {
      *(undefined *)phVar3 = *(undefined *)phVar4;
      phVar3 = (hardware_floating_sprite_t *)&phVar3->color;
      phVar4 = (hardware_floating_sprite_t *)&phVar4->color;
      sVar2 = sVar2 + -1;
    } while (sVar2 != 0);
  }
  if (((current_player_number & cocktail_mode) != 0) && (mspac_sprite._0_1_ == '?')) {
    mspac_sprite._0_1_ = -1;
  }
  bVar1 = process_wave_one_voice
                    ((undefined ***)mspacman_channel_1_song_table,
                     (sound_channel_16bits_t *)&channel1,&channel_1_wave);
  if (channel_1_wave.num != 0) {
    channel1.vol = bVar1;
  }
                    //  channel 2 song
                    // 
  bVar1 = process_wave_one_voice
                    ((undefined ***)mspacman_channel_2_song_table,&channel2,&channel_2_wave);
  if (channel_2_wave.num != 0) {
    channel2.vol = bVar1;
  }
                    //  channel 3 song
                    // 
  bVar1 = process_wave_one_voice
                    ((undefined ***)mspacman_channel_3_song_table,&channel3,&channel_3_wave);
  if (channel_3_wave.num != 0) {
    channel3.vol = bVar1;
    return;
  }
  return;
}


