//
// Created by OscarNg on 2023/3/18.
//

#include "Player.h"

Player::Player()
{

}

Player::~Player()
{

}

void Player::setNumberofLife(int noOfLife)
{
  life = noOfLife;
}

int Player::getNumberOfLife()
{
  return life;
}


bool Player::playerIsJumping()
{
  return isJumping;
}
void Player::setIsJumping(bool boolean)
{
  Player::isJumping = boolean;
}
bool Player::isStraightJump()
{
  return straightJump;
}
void Player::setStraightJump(bool boolean)
{
  Player::straightJump = boolean;
}
bool Player::isCanJump()
{
  return can_jump;
}
void Player::setCanJump(bool boolean)
{
  can_jump = boolean;
}
Player::PlayerState Player::getPlayerState()
{
  return playerState;
}
void Player::setPlayerState(Player::PlayerState playerState)
{
  Player::playerState = playerState;
}
