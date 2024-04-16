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
#ifndef _LEVELGOAL_H_
#define _LEVELGOAL_H_

#include "object.h"
#include "CFILE.H"
#include <malloc.h>
#include "mem.h"
#include "levelgoal_external.h"

class litem {
public:
  litem() {
    m_type = LIT_OBJECT;
    m_handle = OBJECT_HANDLE_NONE;
    m_f_done = false;
  };

  char m_type;
  int m_handle;
  bool m_f_done;
};

class lgoal {
private:
  char *m_name;
  char *m_item_name;
  char *m_desc;
  char *m_completion_message;

  int m_num_items;
  litem m_item[MAX_GOAL_ITEMS];

  char m_g_list;
  char m_modified;
  bool m_goal_completed; // since flags in a multiplayer game (client) get set to 0, then
                         // reset, we need to use this to store whether the goal has
                         // been completed, else we *possibly* can complete the goal more than
                         // once.
  int m_priority;
  unsigned int m_flags;

  void GoalComplete(int handle, bool announce);
  void SendMultiUpdate(int handle);

public:
  lgoal() {
    m_name = NULL;
    m_item_name = NULL;
    m_desc = NULL;
    m_num_items = 0;
    m_completion_message = NULL;
    m_priority = 0;
    m_g_list = 0;
    m_flags = LGF_ENABLED | LGF_TELCOM_LISTS;
    m_modified = 0;
    m_goal_completed = false;
  };
  ~lgoal() {
    if (m_name)
      mem_free(m_name);
    if (m_item_name)
      mem_free(m_item_name);
    if (m_desc)
      mem_free(m_desc);
  };

  int AddItem();
  bool DeleteItem(int index);
  bool ItemInfo(int index, char operation, char *type, int *handle, bool *done);

  void Reset(bool f_from_editor);

  bool SetName(int handle, char *name);
  bool SetItemName(char *iname);
  bool SetDesc(char *desc);
  bool SetCompletionMessage(char *message);

  int GetName(char *name, int buffer_size);
  int GetItemName(char *iname, int buffer_size);
  int GetDesc(char *desc, int buffer_size);
  int GetCompletionMessage(char *message, int buffer_size);

  bool Priority(int handle, char operation, int *value);
  bool GoalList(char operation, char *value);
  bool GetStatus(int handle, char operation, int *value, bool f_save_load = false, bool announce = true);

  void SendStateToPlayer(int index, int pnum);
  void ResetModified(void);

  int GetNumItems();
};

// Goals are sorted by priority and completion
class levelgoals {
private:
  int m_num_goals;
  lgoal m_goal[MAX_LEVEL_GOALS];
  int m_flags;

  int m_num_active_primaries;
  int m_active_primaries[MAX_LEVEL_GOALS];
  int m_num_active_secondaries;
  int m_active_secondaries[MAX_LEVEL_GOALS];

public:
  levelgoals() {
    m_num_goals = 0;
    m_num_active_secondaries = 0;
    m_num_active_primaries = 0;
  };

  int AddGoal(bool f_from_editor);
  bool DeleteGoal(int index);

  int GoalAddItem(int goal_index);
  bool GoalDeleteItem(int goal_index, int item_index);
  bool GoalItemInfo(int goal_index, int index, char operation, char *type, int *handle, bool *done);

  bool GoalSetName(int goal_index, char *name);
  bool GoalSetItemName(int goal_index, char *iname);
  bool GoalSetDesc(int goal_index, char *desc);
  bool GoalSetCompletionMessage(int goal_index, char *message);

  int GoalGetName(int goal_index, char *name, int buffer_size);
  int GoalGetItemName(int goal_index, char *iname, int buffer_size);
  int GoalGetDesc(int goal_index, char *desc, int buffer_size);
  int GoalGetCompletionMessage(int goal_index, char *message, int buffer_size);

  bool GoalPriority(int goal_index, char operation, int *value);
  bool GoalGoalList(int goal_index, char operation, char *value);
  bool GoalStatus(int goal_index, char operation, int *value, bool announce = true);

  int GoalFindId(char *goal_name);

  int GoalGetNumItems(int goal_index);

  int GetNumGoals();

  bool SaveLevelGoalInfo(CFILE *fptr);
  bool LoadLevelGoalInfo(CFILE *fptr);

  bool LGStatus(char operation, int *value);

  int GetNumActivePrimaryGoals();
  int GetActivePrimaryGoal(int p_index);

  int GetNumActiveSecondaryGoals();
  int GetActiveSecondaryGoal(int s_index);

  void DoFrame();
  void CleanupAfterLevel();
  void InitLevel();
  void Inform(char type, int comp_type, int handle);

  void ResetModifiedFlags(void);
  void MultiSendChangedGoals(int pnum);
};

extern levelgoals Level_goals;

#endif