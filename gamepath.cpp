/*
 THE COMPUTER CODE CONTAINED HEREIN IS THE SOLE PROPERTY OF OUTRAGE
 ENTERTAINMENT, INC. ("OUTRAGE").  OUTRAGE, IN DISTRIBUTING THE CODE TO
 END-USERS, AND SUBJECT TO ALL OF THE TERMS AND CONDITIONS HEREIN, GRANTS A
 ROYALTY-FREE, PERPETUAL LICENSE TO SUCH END-USERS FOR USE BY SUCH END-USERS
 IN USING, DISPLAYING,  AND CREATING DERIVATIVE WORKS THEREOF, SO LONG AS
 SUCH USE, DISPLAY OR CREATION IS FOR NON-COMMERCIAL, ROYALTY OR REVENUE
 FREE PURPOSES.  IN NO EVENT SHALL THE END-USER USE THE COMPUTER CODE
 CONTAINED HEREIN FOR REVENUE-BEARING PURPOSES.  THE END-USER UNDERSTANDS
 AND AGREES TO THE TERMS HEREIN AND ACCEPTS THE SAME BY USE OF THIS FILE.
 COPYRIGHT 1996-2000 OUTRAGE ENTERTAINMENT, INC.  ALL RIGHTS RESERVED.
 */

#include "gamepath.h"
#include <stdlib.h>
#include <string.h>
#include "pserror.h"
#include "pstypes.h"

game_path GamePaths[MAX_GAME_PATHS];
int Num_game_paths = 0;

// Frees gamepath n for future use
void FreeGamePath(int n) {
  if (!GamePaths[n].used)
    return;

  mem_free(GamePaths[n].pathnodes);
  mprintf((0, "Path %d lost some\n", n));

  GamePaths[n].num_nodes = 0;
  GamePaths[n].used = 0;
  Num_game_paths--;
}

void InitGamePaths() {
  static f_game_paths_init = false;
  int i;

  if (f_game_paths_init) {
    // Clear out the current path info
    for (i = 0; i < MAX_GAME_PATHS; i++) {
      FreeGamePath(i);
    }
  }

  f_game_paths_init = true;

  for (i = 0; i < MAX_GAME_PATHS; i++) {
    GamePaths[i].num_nodes = 0;
    GamePaths[i].used = 0;
  }

  Num_game_paths = 0;
}

// searches through GamePath index and returns index of path matching name
// returns -1 if not found
int FindGamePathName(char *name) {
  int i;

  for (i = 0; i < MAX_GAME_PATHS; i++) {
    if (GamePaths[i].used && !stricmp(GamePaths[i].name, name))
      return i;
  }
  return -1;
}
