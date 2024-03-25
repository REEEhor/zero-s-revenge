#include "CGame.h"

CGame::CGame(const std::shared_ptr<const CConfig>& config)
// Game configuration
        : m_Config(config), m_Factory(std::make_shared<CFactory>(config)),
          m_LevelBuilder(m_Config, m_Factory->m_EntityFactory),
          m_BonusManager(m_Factory->m_BonusFactory),
        // Keyboard input
          m_PlayerControls(m_Factory->m_EntityFactory->create_player_controls()),
          m_UiControls(std::make_shared<CInputRecorder>()),
          m_InputManager({m_PlayerControls, m_UiControls}),
        // Game's internal variables
          m_BulletsMap(std::make_shared<CMap>()),
          m_EntitiesMap(std::make_shared<CMap>()),
          m_EnvironmentMap(std::make_shared<CMap>()),
        // User Interface
          m_HealthDisplay(
                  config->m_Int["HEALTH_MAX_LENGTH"],
                  config->m_String["HEALTH_TEXT"],
                  config->m_Color["HEALTH_COLOR"]),
          m_AmmoDisplay(
                  config->m_Int["AMMO_MAX_LENGTH"],
                  config->m_String["AMMO_TEXT"],
                  config->m_Color["AMMO_COLOR"]),
          m_CurrentGunDisplay(
                  config->m_Int["GUN_MAX_LENGTH"],
                  config->m_String["GUN_TEXT"],
                  config->m_Color["GUN_COLOR"]) {
    
    m_UiControls->add_recordable_input(config->m_Char["PAUSE"]);
    m_UiControls->add_recordable_input(config->m_Char["QUIT"]);
    m_UiControls->add_recordable_input(config->m_Char["ENTER"]);
}

void CGame::setup(const std::string& pathToLevel) {
    // Load level from file
    CPosition playerStartingPosition;
    m_LevelBuilder.load_level(pathToLevel,
                              m_WavesManager,
                              m_EnvironmentMap,
                              playerStartingPosition,
                              levelDimensions);
    
    // Wait for correct size of the terminal depending on the width and height of the level.
    CTerminal::wait_for_terminal_size(levelDimensions.m_X * 2,
                                      levelDimensions.m_Y + 5);
    
    // Create player object and add it into the game.
    m_Player = m_Factory->m_EntityFactory->create_player(playerStartingPosition, m_PlayerControls);
    m_EntitiesMap->add_object(m_Player.get_object());
    for (auto& gun: m_Factory->m_EntityFactory->create_all_available_guns()) {
        m_Player.add_gun(*gun);
    }
    
    // Clear screen, turn of echo and blocking input.
    CTerminal::game_mode_on();
    
    // Initial render of UI.
    setup_interface();
}

bool CGame::run(const std::string& pathToLevel) {
    // Load level from file.
    setup(pathToLevel);
    
    // Create renderer responsible for displaying the state of the game.
    CRenderer renderer(levelDimensions.m_X, levelDimensions.m_Y, *m_Config);
    reset_rendering(renderer); // Initial render of the game.
    bool exit = false;
    bool success = false;
    
    // Length of time the game should pause for, so it is not too fast on faster computers.
    int sleepFor = m_Config->m_Int["MINIMUM_MILLISECONDS_PER_TICK"];
    
    // Main game loop
    while (!exit) {
        bool pause = false;
        // Run the game until player wins/loses or presses the pause button.
        while (!pause && !exit) {
            auto startTime = std::chrono::steady_clock::now();
            
            update_input(pause);
            update_game_state(success, exit);
            render(renderer);
            
            auto endTime = std::chrono::steady_clock::now();
            std::this_thread::sleep_for(std::chrono::milliseconds(sleepFor) - (endTime - startTime));
        }
        if (!exit) {
            pause = false;
            // Stop the game and wait for the player to press pause or exit.
            while (!pause && !exit) {
                update_input(pause, exit);
            }
            reset_rendering(renderer);
        }
    }
    
    // Reset terminal settings.
    cleanup();
    
    return success;
}

void CGame::update_input(bool& pause) {
    pause = false;
    m_InputManager.update(); // Get keyboard input.
    
    // Check if the pause button has been pressed.
    for (auto input: m_UiControls->pop_recorded_inputs()) {
        if (input == m_Config->m_Char["PAUSE"]) {
            pause = true;
            return;
        }
    }
}

void CGame::update_input(bool& pause, bool& exit) {
    pause = false;
    exit = false;
    m_InputManager.update(); // Get keyboard input.
    
    // Check if the pause or exit button has been pressed.
    for (auto input: m_UiControls->pop_recorded_inputs()) {
        if (input == m_Config->m_Char["PAUSE"]) {
            pause = true;
        } else if (input == m_Config->m_Char["QUIT"]) {
            exit = true;
        }
    }
}

void CGame::reset_rendering(CRenderer& renderer) {
    std::cout << CTerminal::reset_graphics() << CTerminal::erase_entire_screen();
    renderer.reset(); // Clear both buffers used in renderer.
    m_HealthDisplay.re_render(std::cout);
    m_AmmoDisplay.re_render(std::cout);
    m_CurrentGunDisplay.re_render(std::cout);
}

void CGame::update_game_state(bool& success, bool& exit) {
    success = false;
    
    update_bullets();
    update_entities();
    m_BonusManager.update(m_Player, *m_EnvironmentMap);
    m_EnvironmentMap->update_looks_all_objects();
    update_interface();
    
    // Player is dead -> exit the game as a loss.
    if (m_Player.get_object()->is_destroyed()) {
        exit = true;
        return;
    }
    
    // Player has killed all waves of enemies -> exit the game as a win.
    if (!m_WavesManager.update(m_Enemies, *m_EntitiesMap)) {
        success = true;
        exit = true;
        return;
    }
}

void CGame::update_bullets() {
    // Update all bullets in %m_Bullets. If a bullet says that it was destroyed, remove from the list.
    for (auto it = m_Bullets.begin(); it != m_Bullets.end();) {
        if (it->update(m_BulletsMap, {m_EnvironmentMap, m_EntitiesMap})) {
            ++it;
        } else {
            it = m_Bullets.erase(it);
        }
    }
    // Update visuals of the bullets.
    m_BulletsMap->update_looks_all_objects();
}

void CGame::update_enemies() {
    // Update all enemies in %m_Enemies. If an enemy says that it was killed, we remove it and pass
    // that information to %m_BonusManager, so it decides if a bonus should be dropped from the killed enemy.
    for (auto it = m_Enemies.begin(); it != m_Enemies.end();) {
        if ((**it).update(*m_Player.get_object(),
                          m_EntitiesMap, {m_EnvironmentMap},
                          m_Bullets, m_BulletsMap)) {
            ++it;
        } else {
            m_BonusManager.maybe_generate_new_bonus_object(
                    (**it).get_object()->get_position(), (**it).m_Toughness, *m_EnvironmentMap);
            it = m_Enemies.erase(it);
        }
    }
}

void CGame::update_entities() {
    update_enemies();
    m_Player.update(m_EntitiesMap, {m_EnvironmentMap}, m_Bullets, m_BulletsMap);
    m_EntitiesMap->update_looks_all_objects();
}

void CGame::update_interface() {
    // Get player's stats and display them.
    m_HealthDisplay.update(m_Player.get_object()->get_health(), std::cout);
    m_AmmoDisplay.update(m_Player.current_gun()->m_Ammo, std::cout);
    m_CurrentGunDisplay.update(m_Player.current_gun()->name(), std::cout);
}

void CGame::setup_interface() {
    // Set user interface position under the game window.
    m_HealthDisplay.set_position(1, levelDimensions.m_Y + 2);
    m_AmmoDisplay.set_position(1, levelDimensions.m_Y + 3);
    m_CurrentGunDisplay.set_position(1, levelDimensions.m_Y + 4);
    
    m_HealthDisplay.first_render(std::cout);
    m_AmmoDisplay.first_render(std::cout);
    m_CurrentGunDisplay.first_render(std::cout);
}

void CGame::render(CRenderer& renderer) {
    // Clear renderer's buffer and put sprites of objects in the game into it.
    renderer.clear_active_buffer();
    m_BulletsMap->push_objects_to_render(renderer);
    m_EntitiesMap->push_objects_to_render(renderer);
    m_EnvironmentMap->push_objects_to_render(renderer);
    
    // Compare that with the previous frame and render only differences.
    renderer.render_differences(std::cout);
    renderer.switch_active_buffer();
    
    // Update user interface.
    update_interface();
}

void CGame::cleanup() {
    CTerminal::reset_terminal();
}
