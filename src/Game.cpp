
#include <cmath>
#include <iostream>

#include "Game.h"

Game::Game(sf::RenderWindow& game_window) : window(game_window)
{
  srand(time(NULL));
}

Game::~Game() {}

bool Game::init()
{
  background.initialiseSprite(
    background_texture, "Data/Images/assets/Background_3.png");
  background.getSprite()->setScale(5.0f, 5.0f);
  background_texture.setRepeated(true);
  background.getSprite()->setTextureRect(sf::IntRect(
    0, 0, background_texture.getSize().x * 7, background_texture.getSize().y));
  background.getSprite()->setPosition(0, 0);
  if (!font.loadFromFile("Data/Fonts/open-sans/Chainwhacks-vm72E.ttf"))
  {
    std::cout << "font loading error";
  }
  camera.setSize(window.getSize().x, window.getSize().y);
  camera.setCenter(camera.getSize().x / 2, camera.getSize().y / 2);

  // Start menu
  title.init("Foxio", font, 300);
  title.getText()->setPosition(
    window.getSize().x / 2 - title.getText()->getGlobalBounds().width / 2,
    window.getSize().y / 3);
  title.getText()->setFillColor(sf::Color(255, 255, 255, 255));

  press_start_text.init("[Press Any Key]", font, 100);
  press_start_text.getText()->setPosition(
    window.getSize().x / 2 -
      press_start_text.getText()->getGlobalBounds().width / 2,
    window.getSize().y * 3 / 4);
  press_start_text.getText()->setFillColor(sf::Color(255, 255, 255, 125));

  // Main menu

  start_text.init("Start", font, 150);
  start_text.getText()->setPosition(
    window.getSize().x / 2 - start_text.getText()->getGlobalBounds().width / 2,
    window.getSize().y / 3);
  start_text.getText()->setFillColor(sf::Color(255, 255, 255, 125));

  quit_text.init("Quit", font, 150);
  quit_text.getText()->setPosition(
    window.getSize().x / 2 - quit_text.getText()->getGlobalBounds().width / 2,
    start_text.getText()->getPosition().y +
      start_text.getText()->getGlobalBounds().height * 2);
  quit_text.getText()->setFillColor(sf::Color(255, 255, 255, 125));

  // GUIDE

  a_key.initialiseSprite(a_key_texture, "Data/Images/assets/keyboard_A.png");
  a_key.getSprite()->setScale(5.0f, 5.0f);
  a_key.getSprite()->setPosition(100, 100);

  left_guide.init("Moving Left", font, 100);
  left_guide.getText()->setPosition(
    100 + a_key.getSprite()->getGlobalBounds().width * 1.5, 100);
  left_guide.getText()->setFillColor(sf::Color(255, 255, 255, 255));

  d_key.initialiseSprite(d_key_texture, "Data/Images/assets/keyboard_D.png");
  d_key.getSprite()->setScale(5.0f, 5.0f);
  d_key.getSprite()->setPosition(
    100, 100 + a_key.getSprite()->getGlobalBounds().height * 2);

  right_guide.init("Moving Right", font, 100);
  right_guide.getText()->setPosition(
    left_guide.getText()->getPosition().x, d_key.getSprite()->getPosition().y);
  right_guide.getText()->setFillColor(sf::Color(255, 255, 255, 255));

  space_key.initialiseSprite(
    space_key_texture, "Data/Images/assets/keyboard_Space.png");
  space_key.getSprite()->setScale(5.0f, 5.0f);
  space_key.getSprite()->setPosition(
    100, 100 + a_key.getSprite()->getGlobalBounds().height * 4);

  jump_guide.init("Jump", font, 100);
  jump_guide.getText()->setPosition(
    left_guide.getText()->getPosition().x +
      space_key.getSprite()->getGlobalBounds().width / 2 +
      a_key.getSprite()->getGlobalBounds().width / 2,
    space_key.getSprite()->getPosition().y);
  jump_guide.getText()->setFillColor(sf::Color(255, 255, 255, 255));

  coin_guide.initialiseSprite(
    coin_guide_texture, "Data/Images/assets/coin1.png");
  coin_guide.getSprite()->setScale(10.0f, 10.0f);
  coin_guide.getSprite()->setPosition(window.getSize().x / 2, 100);

  coins_guide_text.init("Collect Coins to\ngain scores", font, 100);
  coins_guide_text.getText()->setPosition(
    coin_guide.getSprite()->getPosition().x +
      coin_guide.getSprite()->getGlobalBounds().width * 1.5,
    100);
  coins_guide_text.getText()->setFillColor(sf::Color(255, 255, 255, 255));

  slime_guide.initialiseSprite(
    slime_guide_texture, "Data/Images/assets/Sprite Sheet - Blue Idle 1.png");
  slime_guide.getSprite()->setScale(4.0f, 4.0f);
  slime_guide.getSprite()->setPosition(
    window.getSize().x / 2,
    100 + a_key.getSprite()->getGlobalBounds().height * 2);

  enemy_guide.init(
    "The slime will kill you\nif you get hit by the \nslime.\nYou can kill it "
    "if you\nstep on it",
    font,
    100);
  enemy_guide.getText()->setPosition(
    coins_guide_text.getText()->getPosition().x,
    right_guide.getText()->getPosition().y);
  enemy_guide.getText()->setFillColor(sf::Color(255, 255, 255, 255));

  exit_guide.init("[Press Space to continue]", font, 100);
  exit_guide.getText()->setPosition(
    window.getSize().x / 2 - exit_guide.getText()->getGlobalBounds().width / 2,
    window.getSize().y - exit_guide.getText()->getGlobalBounds().height * 3);
  exit_guide.getText()->setFillColor(sf::Color(255, 255, 255, 125));

  // Player life screen
  life_icon.initialiseSprite(
    life_icon_texture, "Data/Images/assets/player-IDLE-1.png");
  life_icon.getSprite()->setScale(6.0f, 6.0f);
  life_icon.getSprite()->setPosition(
    window.getSize().x / 2 -
      life_icon.getSprite()->getGlobalBounds().width * 1.5,
    window.getSize().y / 2 -
      life_icon.getSprite()->getGlobalBounds().height / 2);

  life_left << player.getNumberOfLife();
  life_text.init("x " + life_left.str(), font, 150);
  life_text.getText()->setPosition(
    window.getSize().x / 2 - life_icon.getSprite()->getGlobalBounds().width / 2,
    window.getSize().y / 2 - life_text.getText()->getGlobalBounds().height / 2);
  life_text.getText()->setFillColor(sf::Color(255, 255, 255, 255));

  key_press_text.init("[Press Enter to continue]", font, 100);
  key_press_text.getText()->setPosition(
    window.getSize().x / 2 -
      key_press_text.getText()->getGlobalBounds().width / 2,
    window.getSize().y -
      key_press_text.getText()->getGlobalBounds().height * 3);
  key_press_text.getText()->setFillColor(sf::Color(255, 255, 255, 200));

  // In-Game

  score_number << score;
  scoreboard.init("Score:" + score_number.str(), font, 100);
  scoreboard.getText()->setPosition(
    camera.getCenter().x + camera.getSize().x / 2 - 600,
    scoreboard.getText()->getLocalBounds().height);
  scoreboard.getText()->setFillColor(sf::Color(125, 125, 125, 255));

  timer_time << last_round_time + timer.getElapsedTime().asSeconds();
  time_text.init(timer_time.str(), font, 100);
  time_text.getText()->setPosition(
    camera.getCenter().x - camera.getSize().x / 2 + 200,
    scoreboard.getText()->getGlobalBounds().height);
  time_text.getText()->setFillColor(sf::Color(125, 125, 125, 255));

  player.initialiseSprite(
    player_idle_texture, "Data/Images/assets/player-IDLE.png");
  player_idle_texture_rect = sf::IntRect(
    0, 0, player_idle_texture.getSize().x / 4, player_idle_texture.getSize().y);
  player_run_texture.loadFromFile("Data/Images/assets/payer-run.png");
  player_run_texture_rect = sf::IntRect(
    0, 0, player_run_texture.getSize().x / 6, player_run_texture.getSize().y);
  player_jump_texture.loadFromFile("Data/Images/assets/player-jump-1.png");
  player_fall_texture.loadFromFile("Data/Images/assets/player-fall.png");
  player_hurt_texture.loadFromFile("Data/Images/assets/player-hurt-2.png");
  player_texture_rect = sf::IntRect(
    0, 0, player_jump_texture.getSize().x, player_jump_texture.getSize().y);
  player.getSprite()->setTextureRect(player_idle_texture_rect);
  player.getSprite()->setScale(4.0f, 4.0f);
  player.getSprite()->setPosition(300, 0);
  player.setVisibility(true);
  player.setMovingDirection(0, 0);

  for (int i = 0; i < no_of_slimes; ++i)
  {
    slime[i].initialiseSprite(
      slime_texture, "Data/Images/assets/Sprite Sheet - Blue Idle.png");
    slime_texture_rect = sf::IntRect(
      0, 0, slime_texture.getSize().x / 7, slime_texture.getSize().y);
    slime[i].getSprite()->setScale(2.0f, 2.0f);
    slime[i].getSprite()->setPosition(
      slime_spwan_pos_x_list[i] * 64,
      slime_spwan_pos_y_list[i] * 64 -
        slime[i].getSprite()->getGlobalBounds().height);
    slime[i].setVisibility(true);
    slime[i].setMovingDirection(1, 0);
  }

  for (int i = 0; i < no_of_coins; ++i)
  {
    coins[i].initialiseSprite(coins_texture, "Data/Images/assets/Coin.png");
    coins_texture_rect = sf::IntRect(
      0, 0, coins_texture.getSize().x, coins_texture.getSize().y / 6);
    coins[i].getSprite()->setTextureRect(coins_texture_rect);
    coins[i].getSprite()->setScale(4.5f, 4.5f);
    coins[i].getSprite()->setPosition(
      coins_spwan_pos_x_list[i] * 64, coins_spwan_pos_y_list[i] * 64);
  }

  house.initialiseSprite(house_texture, "Data/Images/assets/house.png");
  house.getSprite()->setScale(5.0f, 5.0f);
  house.getSprite()->setPosition(
    map_width * 64 - house.getSprite()->getGlobalBounds().width,
    (map_height - 4) * 64 - house.getSprite()->getGlobalBounds().height);

  goal.initialiseSprite(goal_texture, "Data/Images/assets/door.png");
  goal.getSprite()->setScale(5.0f, 5.0f);
  goal.getSprite()->setPosition(
    (map_width - 5) * 64,
    (map_height - 4) * 64 - goal.getSprite()->getGlobalBounds().height);
  initMap();

  for (int i = 0; i < no_of_m_platform; ++i)
  {
    moving_platform[i].initialiseSprite(
      m_platform_texture, "Data/Images/assets/platform.png");
    moving_platform[i].getSprite()->setPosition(
      (178 * 64) +
        (moving_platform[0].getSprite()->getGlobalBounds().width + (64 * 6)) *
          i,
      window.getSize().y / 2);
  }
  moving_platform[0].setMovingDirection(0, 1);
  moving_platform[1].setMovingDirection(0, -1);
  moving_platform[2].setMovingDirection(0, 1.5);

  // Pause menu;
  pause_menu_background =
    sf::RectangleShape(sf::Vector2f(camera.getSize().x, camera.getSize().y));
  pause_menu_background.setFillColor(sf::Color(255, 255, 255, 125));

  pause_menu_text.init("Pause", font, 250);
  pause_menu_text.getText()->setPosition(
    camera.getSize().x / 2 -
      pause_menu_text.getText()->getGlobalBounds().width / 2,
    pause_menu_text.getText()->getGlobalBounds().height);
  pause_menu_text.getText()->setFillColor(sf::Color(0, 0, 0, 255));

  continue_text.init("continue", font, 100);
  continue_text.getText()->setPosition(
    camera.getSize().x / 2 -
      continue_text.getText()->getGlobalBounds().width / 2,
    camera.getSize().y / 2);
  continue_text.getText()->setFillColor(sf::Color(0, 200, 0, 150));

  quit_game_text.init("Quit", font, 100);
  quit_game_text.getText()->setPosition(
    camera.getSize().x / 2 -
      quit_game_text.getText()->getGlobalBounds().width / 2,
    camera.getSize().y / 2 +
      quit_game_text.getText()->getGlobalBounds().height * 2);
  quit_game_text.getText()->setFillColor(sf::Color(200, 0, 0, 150));

  // GAME_WON
  congrats_text.init("STAGE CLEAR", font, 300);
  congrats_text.getText()->setPosition(
    window.getSize().x / 2 -
      congrats_text.getText()->getGlobalBounds().width / 2,
    congrats_text.getText()->getGlobalBounds().height);
  congrats_text.getText()->setFillColor(sf::Color(255, 255, 255, 255));

  final_time_text.init("Clear time:" + timer_time.str(), font, 100);
  final_time_text.getText()->setPosition(
    window.getSize().x / 2 -
      final_time_text.getText()->getGlobalBounds().width / 2,
    congrats_text.getText()->getPosition().y +
      congrats_text.getText()->getGlobalBounds().height +
      final_time_text.getText()->getLocalBounds().height * 1.5);
  final_time_text.getText()->setFillColor(sf::Color(0, 255, 0, 255));

  final_score.init("Your score is: ", font, 150);
  final_score.getText()->setFillColor(sf::Color(255, 255, 255, 255));
  final_score.getText()->setPosition(
    window.getSize().x / 2 -
      final_score.getText()->getGlobalBounds().width / 2,
    final_time_text.getText()->getPosition().y + final_time_text.getText()->getGlobalBounds().height * 2);

  restart_text.init("Restart", font, 100);
  restart_text.getText()->setPosition(
    restart_text.getText()->getGlobalBounds().width,
    window.getSize().y - restart_text.getText()->getGlobalBounds().height * 2);
  restart_text.getText()->setFillColor(sf::Color(255, 255, 255, 125));

  back_to_menu_text.init("Back to main menu", font, 100);
  back_to_menu_text.getText()->setPosition(
    window.getSize().x -
      back_to_menu_text.getText()->getGlobalBounds().width * 1.2,
    window.getSize().y - restart_text.getText()->getGlobalBounds().height * 2);
  back_to_menu_text.getText()->setFillColor(sf::Color(255, 255, 255, 125));

  // GAME_OVER

  game_over_text.init("GAME OVER", font, 300);
  game_over_text.getText()->setPosition(
    window.getSize().x / 2 -
      game_over_text.getText()->getGlobalBounds().width / 2,
    game_over_text.getText()->getGlobalBounds().height);
  game_over_text.getText()->setFillColor(sf::Color(255, 255, 255, 255));

  return true;
}

void Game::update(float dt)
{
  if (gameState == MAIN_MENU)
  {
    if (main_menu_selected_text)
    {
      start_text.getText()->setFillColor(sf::Color(255, 255, 255, 255));
      quit_text.getText()->setFillColor(sf::Color(255, 255, 255, 125));
    }
    else
    {
      start_text.getText()->setFillColor(sf::Color(255, 255, 255, 125));
      quit_text.getText()->setFillColor(sf::Color(255, 255, 255, 255));
    }
  }

  if (gameState == IN_GAME)
  {
    if (!pause)
    {
      // timer update
      timer_time.str("");
      timer_time << last_round_time + paused_time +
                      timer.getElapsedTime().asSeconds();
      time_text.getText()->setString(timer_time.str());

      // gravity
      gravity_scaler += 0.1f;

      // gravity limit
      if (gravity_scaler > 8)
      {
        gravity_scaler = 8;
      }
    }

    // update player velocity for checks
    player_velocity_x = player.getMovingDirection().operator*(6).x;
    player_velocity_y = player.getMovingDirection().operator*(6).y;

    // update moving platforms' hitbox position
    for (int i = 0; i < no_of_m_platform; ++i)
    {
      platform_velocity_y[i] =
        moving_platform[i].getMovingDirection().operator*(6).y;
      platform_hitbox[i] = sf::IntRect(
        moving_platform[i].getSprite()->getPosition().x,
        moving_platform[i].getSprite()->getPosition().y +
          platform_velocity_y[i] * 2,
        moving_platform[i].getSprite()->getGlobalBounds().width,
        moving_platform[i].getSprite()->getGlobalBounds().height);
    }

    // camera and texts moving along

    if (
      (player.getSprite()->getPosition().x >= camera.getCenter().x + 300) &&
      player_velocity_x > 0)
    {
      camera.move(player_velocity_x, 0);
      scoreboard.getText()->move(player_velocity_x, 0);
      time_text.getText()->move(player_velocity_x, 0);
      if (
        camera.getCenter().x + camera.getSize().x / 2 >=
        background.getSprite()->getGlobalBounds().width)
      {
        camera.setCenter(
          background.getSprite()->getGlobalBounds().width -
            camera.getSize().x / 2,
          camera.getSize().y / 2);
        scoreboard.getText()->setPosition(
          camera.getCenter().x + camera.getSize().x / 2 - 600,
          scoreboard.getText()->getGlobalBounds().height);
        time_text.getText()->setPosition(
          camera.getCenter().x - camera.getSize().x / 2 + 200,
          scoreboard.getText()->getGlobalBounds().height);
      }
    }
    if (
      (player.getSprite()->getPosition().x <= camera.getCenter().x - 300) &&
      player_velocity_x < 0)
    {
      camera.move(player_velocity_x, 0);
      scoreboard.getText()->move(player_velocity_x, 0);
      time_text.getText()->move(player_velocity_x, 0);
      if (
        camera.getCenter().x - camera.getSize().x / 2 <=
        background.getSprite()->getPosition().x)
      {
        camera.setCenter(camera.getSize().x / 2, camera.getSize().y / 2);

        scoreboard.getText()->setPosition(
          camera.getCenter().x + camera.getSize().x / 2 - 600,
          scoreboard.getText()->getGlobalBounds().height);

        time_text.getText()->setPosition(
          camera.getCenter().x - camera.getSize().x / 2 + 200,
          scoreboard.getText()->getGlobalBounds().height);
      }
    }

    // player animation

    if (player.getPlayerState() == Player::IDLE)
    {
      if (idle_anim_click.getElapsedTime().asSeconds() > 0.2)
      {
        if (player_idle_texture_rect.left >= player_idle_texture.getSize().x * 3 / 4)
        {
          player_idle_texture_rect.left = 0;
        }
        else
        {
          player_idle_texture_rect.left += player_idle_texture.getSize().x / 4;
        }
        player.getSprite()->setTextureRect(player_idle_texture_rect);
        idle_anim_click.restart();
      }
    }
    else if (player.getPlayerState() == Player::RUNNING)
    {
      if (run_anim_clock.getElapsedTime().asSeconds() > 0.1)
      {
        if (player_run_texture_rect.left >= player_run_texture.getSize().x * 5 / 6)
        {
          player_run_texture_rect.left = 0;
        }
        else
        {
          player_run_texture_rect.left += player_run_texture.getSize().x / 6;
        }
        player.getSprite()->setTextureRect(player_run_texture_rect);
        run_anim_clock.restart();
      }
    }
    else if (
      player.getPlayerState() == Player::JUMPING ||
      player.getPlayerState() == Player::DEAD ||
      player.getPlayerState() == Player::FALLING)
    {
      player.getSprite()->setTextureRect(player_texture_rect);
    }

    // coins animation
    if (coin_anim_clock.getElapsedTime().asSeconds() > 0.2)
    {
      if (coins_texture_rect.top >= coins_texture.getSize().y * 5 / 6)
      {
        coins_texture_rect.top = 0;
      }
      else
      {
        coins_texture_rect.top += coins_texture.getSize().y / 6;
      }
      for (int i = 0; i < no_of_coins; ++i)
      {
        coins[i].getSprite()->setTextureRect(coins_texture_rect);
      }
      coin_anim_clock.restart();
    }

    // enemy animation
    if (slime_anim_clock.getElapsedTime().asSeconds() > 0.2)
    {
      if (slime_texture_rect.left >= slime_texture.getSize().x * 6 / 7)
      {
        slime_texture_rect.left = 0;
      }
      else
      {
        slime_texture_rect.left += slime_texture.getSize().x / 7;
      }
      for (int i = 0; i < no_of_slimes; ++i)
      {
        slime[i].getSprite()->setTextureRect(slime_texture_rect);
      }
      slime_anim_clock.restart();
    }

    if (!pause)
    {
      // player movement
      player.getSprite()->move(
        player.getMovingDirection().operator*(6).x,
        player.getMovingDirection().operator*(6).y);
      // player moving Left
      if (player.getMoveLeftBool() && !player.isDead())
      {
        if (!player.playerIsJumping())
        {
          player.setMovingDirection(-1.5f, player.getMovingDirection().y);
        }
        else if (player.playerIsJumping() && player_velocity_x > 0)
        {
          player.horizontal_force -= 0.05f;
        }
      }

      // player moving right
      else if (player.getMoveRightBool() && !player.isDead())
      {
        if (!player.playerIsJumping())
        {
          player.setMovingDirection(1.5f, player.getMovingDirection().y);
        }
        else if (player.playerIsJumping() && player_velocity_x < 0)
        {
          player.horizontal_force += 0.05f;
        }
      }

      // Standing
      else if (!player.getMoveRightBool() || !player.getMoveLeftBool())
      {
        if (!player.playerIsJumping())
        {
          player.setMovingDirection(0, player.getMovingDirection().y);
          player.setStraightJump(true);
        }
        else
        {
          player.setMovingDirection(
            player.horizontal_force, player.getMovingDirection().y);
        }
      }

      // continue moving when jump
      if (player.playerIsJumping())
      {
        if (player_velocity_x > 0 && player.horizontal_force < 1.5f)
        {
          player.setMovingDirection(
            1.5f + player.horizontal_force, player.getMovingDirection().y);
        }

        else if (player_velocity_x < 0 && player.horizontal_force > -1.5f)
        {
          player.setMovingDirection(
            -1.5f + player.horizontal_force, player.getMovingDirection().y);
        }
        else if (player.isStraightJump())
        {
          player.setMovingDirection(
            player.horizontal_force, player.getMovingDirection().y);
        }
      }

      // addition force limit
      if (player.horizontal_force >= 1.4f)
      {
        player.horizontal_force = 1.4f;
      }

      else if (player.horizontal_force <= -1.4f)
      {
        player.horizontal_force = -1.4f;
      }

      if (player_velocity_x < 0)
      {
        player.getSprite()->setOrigin(
          player.getSprite()->getLocalBounds().width, 0);
        player.getSprite()->setScale(-4.0f, 4.0f);
      }
      if (player_velocity_x > 0)
      {
        player.getSprite()->setOrigin(0, 0);
        player.getSprite()->setScale(4.0f, 4.0f);
      }
    }

    // player will not move outside the screen
    if (player.getSprite()->getPosition().x < 0)
    {
      player.getSprite()->setPosition(0, player.getSprite()->getPosition().y);
    }

    else if (
      player.getSprite()->getPosition().x +
        player.getSprite()->getGlobalBounds().width >=
      map_width * 64)
    {
      player.getSprite()->setPosition(
        map_width * 64 - player.getSprite()->getGlobalBounds().width,
        player.getSprite()->getPosition().y);
    }

    // update player hitboxes location for checks
    player_ground_hitbox = sf::IntRect(
      player.getSprite()->getPosition().x +
        player.getSprite()->getGlobalBounds().width / 4,
      player.getSprite()->getGlobalBounds().top +
        player.getSprite()->getGlobalBounds().height * 4 /5 + player_velocity_y,
      player.getSprite()->getGlobalBounds().width / 2 - 10,
      player.getSprite()->getGlobalBounds().height / 5);

    player_top_hitbox = sf::IntRect(
      player.getSprite()->getPosition().x +
        player.getSprite()->getGlobalBounds().width / 3 + player_velocity_x,
      player.getSprite()->getGlobalBounds().top + player_velocity_y,
      player.getSprite()->getGlobalBounds().width / 3,
      player.getSprite()->getGlobalBounds().height / 2);

    player_right_hitbox = sf::IntRect(
      player.getSprite()->getPosition().x +
        player.getSprite()->getGlobalBounds().width / 2,
      player.getSprite()->getGlobalBounds().top,
      player.getSprite()->getGlobalBounds().width / 4,
      player.getSprite()->getGlobalBounds().height * 0.8);

    player_left_hitbox = sf::IntRect(
      player.getSprite()->getPosition().x,
      player.getSprite()->getGlobalBounds().top,
      player.getSprite()->getGlobalBounds().width / 4,
      player.getSprite()->getGlobalBounds().height * 0.8);

    // player ground collision check to platform
    if (
      ((tilemap.collisionCheck(
         player_ground_hitbox,
         1,
         sf::Vector2u(64, 64),
         level,
         map_width,
         map_height)) ||
       (tilemap.collisionCheck(
         player_ground_hitbox,
         9,
         sf::Vector2u(64, 64),
         level,
         map_width,
         map_height)) ||
       (tilemap.collisionCheck(
         player_ground_hitbox,
         10,
         sf::Vector2u(64, 64),
         level,
         map_width,
         map_height)) ||
       (tilemap.collisionCheck(
         player_ground_hitbox,
         11,
         sf::Vector2u(64, 64),
         level,
         map_width,
         map_height)) ||
       (tilemap.collisionCheck(
         player_ground_hitbox,
         12,
         sf::Vector2u(64, 64),
         level,
         map_width,
         map_height))) &&
      gravity_scaler > 0 && !player.isDead())
    {
      gravity_scaler          = 0;
      player.horizontal_force = 0;
      player.setIsJumping(false);
      player.setCanJump(true);
      player.setMovingDirection(player.getMovingDirection().x, gravity_scaler);
      if (player.getMovingDirection().x == 0)
      {
        player.getSprite()->setTexture(player_idle_texture);
        player.setPlayerState(Player::IDLE);
      }
      else
      {
        player.getSprite()->setTexture(player_run_texture);
        player.setPlayerState(Player::RUNNING);
      }
    }
    else
    {
      if (!player.isOnMovingPlatform())
      {
        player.setCanJump(false);
        if (gravity_scaler > 0)
        {
          player.getSprite()->setTexture(player_fall_texture);
          player.setPlayerState(Player::FALLING);
        }
        player.setMovingDirection(
          player.getMovingDirection().x, gravity_scaler);
      }
    }

    // player head collision check to platform
    if (
      ((tilemap.collisionCheck(
         player_top_hitbox,
         1,
         sf::Vector2u(64, 64),
         level,
         map_width,
         map_height)) ||
       (tilemap.collisionCheck(
         player_top_hitbox,
         9,
         sf::Vector2u(64, 64),
         level,
         map_width,
         map_height)) ||
       (tilemap.collisionCheck(
         player_top_hitbox,
         10,
         sf::Vector2u(64, 64),
         level,
         map_width,
         map_height)) ||
       (tilemap.collisionCheck(
         player_top_hitbox,
         11,
         sf::Vector2u(64, 64),
         level,
         map_width,
         map_height))) &&
      gravity_scaler < 0 && !player.isDead())
    {
      gravity_scaler = 0;
      gravity_scaler += 2;
      player.setMovingDirection(player.getMovingDirection().x, gravity_scaler);
    }

    // player right collision check to platform
    if (
      ((tilemap.collisionCheck(
         player_right_hitbox,
         1,
         sf::Vector2u(64, 64),
         level,
         map_width,
         map_height)) ||
       (tilemap.collisionCheck(
         player_right_hitbox,
         9,
         sf::Vector2u(64, 64),
         level,
         map_width,
         map_height)) ||
       (tilemap.collisionCheck(
         player_right_hitbox,
         10,
         sf::Vector2u(64, 64),
         level,
         map_width,
         map_height)) ||
       (tilemap.collisionCheck(
         player_right_hitbox,
         11,
         sf::Vector2u(64, 64),
         level,
         map_width,
         map_height)) ||
       (tilemap.collisionCheck(
         player_right_hitbox,
         12,
         sf::Vector2u(64, 64),
         level,
         map_width,
         map_height))) &&
      !player.isDead())
    {
      if (player_velocity_x > 0)
      {
        player.getSprite()->setPosition(
          player.getSprite()->getPosition().x - player_velocity_x,
          player.getSprite()->getPosition().y);
      }
    }

    // player left collision check to platform
    if (
      ((tilemap.collisionCheck(
         player_left_hitbox,
         1,
         sf::Vector2u(64, 64),
         level,
         map_width,
         map_height)) ||
       (tilemap.collisionCheck(
         player_left_hitbox,
         9,
         sf::Vector2u(64, 64),
         level,
         map_width,
         map_height)) ||
       (tilemap.collisionCheck(
         player_left_hitbox,
         10,
         sf::Vector2u(64, 64),
         level,
         map_width,
         map_height)) ||
       (tilemap.collisionCheck(
         player_left_hitbox,
         11,
         sf::Vector2u(64, 64),
         level,
         map_width,
         map_height)) ||
       (tilemap.collisionCheck(
         player_left_hitbox,
         12,
         sf::Vector2u(64, 64),
         level,
         map_width,
         map_height))) &&
      !player.isDead())
    {
      if (player_velocity_x < 0)
      {
        player.getSprite()->setPosition(
          player.getSprite()->getPosition().x - player_velocity_x,
          player.getSprite()->getPosition().y);
      }
    }

    for (int i = 0; i < no_of_slimes; ++i)
    {
      // slime movement
      if (!pause)
      {
        slime[i].getSprite()->move(
          slime[i].getMovingDirection().operator*(3).x,
          slime[i].getMovingDirection().operator*(3).y);
      }
      slime_velocity_x = slime[i].getMovingDirection().operator*(6).x;

      slime_hitbox[i] = sf::IntRect(
        slime[i].getSprite()->getPosition().x + slime_velocity_x,
        slime[i].getSprite()->getPosition().y,
        slime[i].getSprite()->getGlobalBounds().width,
        slime[i].getSprite()->getGlobalBounds().height);

      slime_ground_hitbox[i] = sf::IntRect(
        slime[i].getSprite()->getPosition().x,
        slime[i].getSprite()->getPosition().y +
          slime[i].getSprite()->getGlobalBounds().height,
        slime[i].getSprite()->getGlobalBounds().width,
        slime[i].getSprite()->getGlobalBounds().height);

      // slime reverse moving direction
      if (
        tilemap.collisionCheck(
          slime_ground_hitbox[i],
          0,
          sf::Vector2u(64, 64),
          level,
          map_width,
          map_height) ||
        (tilemap.collisionCheck(
          slime_hitbox[i],
          12,
          sf::Vector2u(64, 64),
          level,
          map_width,
          map_height)))
      {
        slime[i].setMovingDirection(
          -slime[i].getMovingDirection().x, slime[i].getMovingDirection().y);
      }

      // player-slime collision check
      if (slime[i].getVisibility() && !player.isDead())
      {
        if (
          (movingSpriteCollisionCheck(player_left_hitbox, slime_hitbox[i]) ||
           (movingSpriteCollisionCheck(player_right_hitbox, slime_hitbox[i]))) &&
          player_velocity_y <= 0)
        {
          player.setDead(true);
        }

        if (
          movingSpriteCollisionCheck(player_ground_hitbox, slime_hitbox[i]) &&
          player_velocity_y > 0)
        {
          slime[i].setVisibility(false);
          gravity_scaler = -1.5;
          player.getSprite()->setTexture(player_jump_texture);
          player.setPlayerState(Player::JUMPING);
          scoreBoardUpdate(50);
        }
      }
    }

    for (int i = 0; i < no_of_m_platform; ++i)
    {
      // moving platforms movement
      if (!pause)
      {
        moving_platform[i].getSprite()->move(
          moving_platform[i].getMovingDirection().operator*(6).x,
          moving_platform[i].getMovingDirection().operator*(6).y);
      }

      // platforms reverse moving direction
      if (
        (moving_platform[i].getSprite()->getPosition().y >
         background.getSprite()->getGlobalBounds().height -
           moving_platform[i].getSprite()->getGlobalBounds().height * 3) ||
        (moving_platform[i].getSprite()->getPosition().y <
         moving_platform[i].getSprite()->getGlobalBounds().height * 5))
      {
        moving_platform[i].setMovingDirection(
          moving_platform[i].getMovingDirection().x,
          moving_platform[i].getMovingDirection().y * -1);
      }

      // player-platform collision check
      if (
        movingSpriteCollisionCheck(player_ground_hitbox, platform_hitbox[i]) &&
        gravity_scaler > 0)
      {
        player.setMovingDirection(
          player.getMovingDirection().x,
          moving_platform[i].getMovingDirection().y);
        player.horizontal_force = 0;
        gravity_scaler          = 0;
        player.setOnMovingPlatform(true);
        player.setIsJumping(false);
        player.setCanJump(true);
        if (player.getMovingDirection().x == 0)
        {
          player.getSprite()->setTexture(player_idle_texture);
          player.setPlayerState(Player::IDLE);
        }
        else
        {
          player.getSprite()->setTexture(player_run_texture);
          player.setPlayerState(Player::RUNNING);
        }
      }
      else
      {
        player.setOnMovingPlatform(false);
      }
    }

    if (player.isDead())
    {
      player.getSprite()->setTextureRect(player_texture_rect);
      player.getSprite()->setTexture(player_hurt_texture);
    }

    // Player loss life when it fell of the map
    if (
      player.getSprite()->getPosition().y >=
      background.getSprite()->getGlobalBounds().height)
    {
      player.setNumberofLife(player.getNumberOfLife() - 1);
      gameState = SHOW_PLAYER_LIFE;
      life_left.str("");
      life_left << player.getNumberOfLife();
      life_text.init("x " + life_left.str(), font, 150);
      last_round_time += timer.getElapsedTime().asSeconds();

      // game over when player out of lives
      if (player.getNumberOfLife() <= 0)
      {
        final_score.getText()->setString(
          "Your score is: " + score_number.str());
        gameState = GAME_OVER;
      }
    }

    // player-coins collision check
    for (int i = 0; i < no_of_coins; ++i)
    {
      if (coins[i].getVisibility())
      {
        if (collisionCheck(*player.getSprite(), *coins[i].getSprite()))
        {
          scoreBoardUpdate(10);
          coins[i].setVisibility(false);
        }
      }
    }

    // player reach the goal
    if (collisionCheck(*player.getSprite(), *goal.getSprite()))
    {
      final_score.getText()->setString("Your score is: " + score_number.str());
      timer_time.str("");
      timer_time << paused_time +last_round_time + timer.getElapsedTime().asSeconds();
      final_time_text.getText()->setString("Clear time:" + timer_time.str());
      gameState = GAME_WON;
    }
  }
  pause_menu_background.setPosition(
    camera.getCenter().x - camera.getSize().x / 2,
    camera.getCenter().y - camera.getSize().y / 2);
  if (pause)
  {
    pause_menu_text.getText()->setPosition(
      camera.getCenter().x -
        pause_menu_text.getText()->getGlobalBounds().width / 2,
      pause_menu_text.getText()->getGlobalBounds().height);
    continue_text.getText()->setPosition(
      camera.getCenter().x -
        continue_text.getText()->getGlobalBounds().width / 2,
      camera.getSize().y / 2);
    quit_game_text.getText()->setPosition(
      camera.getCenter().x -
        quit_game_text.getText()->getGlobalBounds().width / 2,
      camera.getSize().y / 2 +
        quit_game_text.getText()->getGlobalBounds().height * 2);

    if (pause_selected_text)
    {
      continue_text.getText()->setFillColor(sf::Color(0, 255, 0, 255));
      quit_game_text.getText()->setFillColor(sf::Color(200, 0, 0, 150));
    }
    else
    {
      continue_text.getText()->setFillColor(sf::Color(0, 200, 0, 150));
      quit_game_text.getText()->setFillColor(sf::Color(255, 0, 0, 255));
    }
  }

  if (gameState == SHOW_PLAYER_LIFE)
  {
    camera.setCenter(camera.getSize().x / 2, camera.getSize().y / 2);
  }
  if (gameState == GAME_WON)
  {
    camera.setCenter(camera.getSize().x / 2, camera.getSize().y / 2);
    if (selection)
    {
      restart_text.getText()->setFillColor(sf::Color(255, 255, 255, 255));
      back_to_menu_text.getText()->setFillColor(sf::Color(255, 255, 255, 125));
    }
    else
    {
      restart_text.getText()->setFillColor(sf::Color(255, 255, 255, 125));
      back_to_menu_text.getText()->setFillColor(sf::Color(255, 255, 255, 255));
    }
  }

  if (gameState == GAME_OVER)
  {
    camera.setCenter(camera.getSize().x / 2, camera.getSize().y / 2);
    if (selection)
    {
      restart_text.getText()->setFillColor(sf::Color(255, 255, 255, 255));
      back_to_menu_text.getText()->setFillColor(sf::Color(255, 255, 255, 125));
    }
    else
    {
      restart_text.getText()->setFillColor(sf::Color(255, 255, 255, 125));
      back_to_menu_text.getText()->setFillColor(sf::Color(255, 255, 255, 255));
    }
  }
}

void Game::render()
{
  if (gameState == START_MENU)
  {
    window.setView(camera);
    window.draw(*background.getSprite());
    window.draw(*title.getText());
    window.draw(*press_start_text.getText());
  }

  if (gameState == MAIN_MENU)
  {
    window.setView(camera);
    window.draw(*background.getSprite());
    window.draw(*start_text.getText());
    window.draw(*quit_text.getText());
  }

  if (gameState == GUIDE)
  {
    window.setView(camera);
    window.draw(*background.getSprite());
    window.draw(*a_key.getSprite());
    window.draw(*left_guide.getText());
    window.draw(*d_key.getSprite());
    window.draw(*right_guide.getText());
    window.draw(*space_key.getSprite());
    window.draw(*jump_guide.getText());
    window.draw(*coin_guide.getSprite());
    window.draw(*coins_guide_text.getText());
    window.draw(*slime_guide.getSprite());
    window.draw(*enemy_guide.getText());
    window.draw(*exit_guide.getText());
  }

  if (gameState == SHOW_PLAYER_LIFE)
  {
    window.setView(camera);
    window.draw(*background.getSprite());
    window.draw(*life_icon.getSprite());
    window.draw(*life_text.getText());
    window.draw(*key_press_text.getText());
  }

  if (gameState == IN_GAME)
  {
    window.setView(camera);
    window.draw(*background.getSprite());
    window.draw(*house.getSprite());
    window.draw(*goal.getSprite());
    window.draw(tilemap);
    window.draw(*time_text.getText());
    window.draw(*scoreboard.getText());

    // coins
    for (int i = 0; i < no_of_coins; ++i)
    {
      if (coins[i].getVisibility())
      {
        window.draw(*coins[i].getSprite());
      }
    }

    // moving platform
    for (int i = 0; i < no_of_m_platform; ++i)
    {
      window.draw(*moving_platform[i].getSprite());
    }

    // enemies
    for (int i = 0; i < no_of_slimes; ++i)
    {
      if (slime[i].getVisibility())
      {
        window.draw(*slime[i].getSprite());
      }
    }

    // player
    window.draw(*player.getSprite());

    if (pause)
    {
      window.draw(pause_menu_background);
      window.draw(*pause_menu_text.getText());
      window.draw(*continue_text.getText());
      window.draw(*quit_game_text.getText());
    }
  }

  if (gameState == GAME_WON)
  {
    window.setView(camera);
    window.draw(*background.getSprite());
    window.draw(*congrats_text.getText());
    window.draw(*final_time_text.getText());
    window.draw(*final_score.getText());
    window.draw(*restart_text.getText());
    window.draw(*back_to_menu_text.getText());
  }

  if (gameState == GAME_OVER)
  {
    window.setView(camera);
    window.draw(*background.getSprite());
    window.draw(*game_over_text.getText());
    window.draw(*final_score.getText());
    window.draw(*restart_text.getText());
    window.draw(*back_to_menu_text.getText());
  }
}

void Game::mouseClicked(sf::Event event)
{
  // get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);
}

void Game::keyPressed(sf::Event event)
{
  if (gameState == MAIN_MENU)
  {
    if (
      event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up ||
      event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
    {
      main_menu_selected_text = !main_menu_selected_text;
    }

    if (event.key.code == sf::Keyboard::Enter)
    {
      if (main_menu_selected_text)
      {
        gameState = GUIDE;
      }
      else
      {
        window.close();
      }
    }
  }

  if (gameState == IN_GAME)
  {
    if (!pause)
    {
      if (event.key.code == sf::Keyboard::A)
      {
        player.setMoveLeftBool(true);
        if (
          player.getPlayerState() != Player::FALLING ||
          player.getPlayerState() != Player::JUMPING)
        {
          player.getSprite()->setTexture(player_run_texture);
          player.setPlayerState(Player::RUNNING);
        }
      }

      if (event.key.code == sf::Keyboard::D)
      {
        player.setMoveRightBool(true);
        if (
          player.getPlayerState() != Player::FALLING ||
          player.getPlayerState() != Player::JUMPING)
        {
          player.getSprite()->setTexture(player_run_texture);
          player.setPlayerState(Player::RUNNING);
        }
      }

      if (event.key.code == sf::Keyboard::Space && player.isCanJump())
      {
        gravity_scaler -= 3.5;
        player.setIsJumping(true);
        player.getSprite()->setTexture(player_jump_texture);
        player.setPlayerState(Player::JUMPING);
      }
      if (event.key.code == sf::Keyboard::Escape)
      {
        pause = true;
        paused_time += last_round_time + timer.getElapsedTime().asSeconds();
      }
    }

    else
    {
      if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down)
      {
        pause_selected_text = !pause_selected_text;
      }

      if (event.key.code == sf::Keyboard::Enter)
      {
        if (pause_selected_text)
        {
          pause           = false;
          last_round_time = 0;
          timer.restart();
          timer_time.str("");
          timer_time << paused_time;
          time_text.getText()->setString(timer_time.str());
        }
        else
        {
          resetGame();
          gameState = START_MENU;
        }
      }
      if (event.key.code == sf::Keyboard::Escape)
      {
        pause           = false;
        last_round_time = 0;
        timer.restart();
        timer_time.str("");
        timer_time << paused_time;
        time_text.getText()->setString(timer_time.str());
      }
    }
  }

  if (gameState == SHOW_PLAYER_LIFE)
  {
    if (event.key.code == sf::Keyboard::Enter)
    {
      reset();
      gameState = IN_GAME;
    }
  }

  if (gameState == GUIDE)
  {
    if (event.key.code == sf::Keyboard::Space)
    {
      gameState = SHOW_PLAYER_LIFE;
    }
  }

  if (gameState == GAME_WON)
  {
    if (
      (event.key.code == sf::Keyboard::Left) ||
      (event.key.code == sf::Keyboard::A) ||
      (event.key.code == sf::Keyboard::Right) ||
      (event.key.code == sf::Keyboard::D))
    {
      selection = !selection;
    }

    if (event.key.code == sf::Keyboard::Enter)
    {
      if (selection)
      {
        resetGame();
        gameState = SHOW_PLAYER_LIFE;
      }
      else
      {
        resetGame();
        gameState = MAIN_MENU;
      }
    }
  }

  if (gameState == GAME_OVER)
  {
    if (
      (event.key.code == sf::Keyboard::Left) ||
      (event.key.code == sf::Keyboard::A) ||
      (event.key.code == sf::Keyboard::Right) ||
      (event.key.code == sf::Keyboard::D))
    {
      selection = !selection;
    }

    if (event.key.code == sf::Keyboard::Enter)
    {
      if (selection)
      {
        resetGame();
        gameState = SHOW_PLAYER_LIFE;
      }
      else
      {
        resetGame();
        gameState = MAIN_MENU;
      }
    }
  }
}

void Game::keyReleased(sf::Event event)
{
  if (gameState == START_MENU)
  {
    if (event.KeyPressed)
    {
      gameState = MAIN_MENU;
    }
  }
  if (gameState == IN_GAME)
  {
    if (event.key.code == sf::Keyboard::A)
    {
      player.setMoveLeftBool(false);
      player.getSprite()->setTexture(player_idle_texture);
      player.setPlayerState(Player::IDLE);
    }

    if (event.key.code == sf::Keyboard::D)
    {
      player.setMoveRightBool(false);
      player.getSprite()->setTexture(player_idle_texture);
      player.setPlayerState(Player::IDLE);
    }
  }
}

bool Game::initMap()
{
  if (!tilemap.load(
        "Data/Images/assets/gametileset.png",
        sf::Vector2u(64, 64),
        level,
        map_width,
        map_height))
  {
    return -1;
  }

  return true;
}

bool Game::movingSpriteCollisionCheck(
  sf::IntRect subject_hitbox, sf::IntRect hitobject_hitbox)
{
  if (
    (subject_hitbox.left + subject_hitbox.width > hitobject_hitbox.left) &
      (subject_hitbox.left < hitobject_hitbox.left + hitobject_hitbox.width) &&
    ((subject_hitbox.top + subject_hitbox.height > hitobject_hitbox.top) &
     (subject_hitbox.top < hitobject_hitbox.top + hitobject_hitbox.height)))
  {
    return true;
  }
  return false;
}

bool Game::collisionCheck(sf::Sprite subject_sprite, sf::Sprite object_sprite)
{
  if (
    (subject_sprite.getPosition().x <
     object_sprite.getPosition().x + object_sprite.getGlobalBounds().width) &&
    (subject_sprite.getPosition().x + subject_sprite.getGlobalBounds().width >
     object_sprite.getPosition().x) &&
    (subject_sprite.getPosition().y <
     object_sprite.getPosition().y + object_sprite.getGlobalBounds().height) &&
    (subject_sprite.getPosition().y + subject_sprite.getGlobalBounds().height >
     object_sprite.getPosition().y))
  {
    return true;
  }
  return false;
}

void Game::scoreBoardUpdate(int score_change)
{
  score += score_change;
  score_number.str("");
  score_number << score;
  scoreboard.getText()->setString("Score: " + score_number.str());
}

void Game::reset()
{
  timer.restart();
  pause          = false;
  gravity_scaler = 0;
  camera.setCenter(camera.getSize().x / 2, camera.getSize().y / 2);
  scoreboard.getText()->setPosition(
    camera.getCenter().x + camera.getSize().x / 2 - 600,
    scoreboard.getText()->getGlobalBounds().height);

  time_text.getText()->setPosition(
    camera.getCenter().x - camera.getSize().x / 2 + 200,
    scoreboard.getText()->getGlobalBounds().height);
  player.setDead(false);
  player.getSprite()->setPosition(300, 0);
  player.setMoveLeftBool(false);
  player.setMoveRightBool(false);
  for (int i = 0; i < no_of_slimes; ++i)
  {
    slime[i].setVisibility(true);
  }
  for (int i = 0; i < no_of_coins; ++i)
  {
    coins[i].setVisibility(true);
  }
}

void Game::resetGame()
{
  reset();
  last_round_time = 0;
  paused_time = 0;
  player.setNumberofLife(3);
  life_left.str("");
  life_left << player.getNumberOfLife();
  life_text.init("x " + life_left.str(), font, 150);
  score = 0;
  score_number.str("");
  score_number << score;
  scoreboard.getText()->setString("Score: " + score_number.str());
}