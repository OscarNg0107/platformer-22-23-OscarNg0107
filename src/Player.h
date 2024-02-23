//
// Created by OscarNg on 2023/3/18.
//
#include "Character.h"

#ifndef PLATFORMERSFML_PLAYER_H
#define PLATFORMERSFML_PLAYER_H

class Player : public Character
{
 public:
  Player();
  ~Player();

  enum PlayerState
  {
    IDLE, RUNNING, JUMPING, FALLING, DEAD
  };

  void setNumberofLife(int noOfLife);
  int getNumberOfLife();
  bool isStraightJump();
  void setStraightJump(bool boolean);
  bool playerIsJumping();
  void setIsJumping(bool boolean);
  bool isCanJump();
  void setCanJump(bool boolean);
  PlayerState getPlayerState();
  void setPlayerState(PlayerState playerState);

  float horizontal_force = 0;

 private:
  int life = 3;
  bool isJumping = false;
  bool straightJump = false;
  bool can_jump = false;
  PlayerState playerState = IDLE;
};

#endif // PLATFORMERSFML_PLAYER_H
