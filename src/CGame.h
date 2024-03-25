#pragma once

#include "CPlayer.h"
#include "CValueDisplay.h"
#include "CLevelBuilder.h"
#include "CInputManager.h"
#include "CBonusManager.h"
#include "CFactory.h"

/// @brief Class for the game itself, that gets played.
class CGame {
public:
    /// Constructor of CGame.
    /// @param[in] config Pointer to const configuration of the application the game is running in.
    explicit CGame(const std::shared_ptr<const CConfig>& config);
    
    /// Method that loads level and plays it.
    /// @para[in] pathToLevel Path to the level to be played.
    /// @throws std::invalid_argument if the level could not be loaded properly.
    bool run(const std::string& pathToLevel);

private:
    /// Sets up internal variables of the CGame.
    /// @param[in] pathToLevel Path to load the level from.
    void setup(const std::string& pathToLevel);
    
    /// Updates keyboard input.
    /// @param[out] pause Whether player pressed the pause button.
    /// @param[out] exit Whether player pressed the exit button.
    void update_input(bool& pause, bool& exit);
    
    /// Updates keyboard input.
    /// @param[out] pause Whether player pressed the pause button.
    void update_input(bool& pause);
    
    /// Updates all internal variables that represent the state of the game.
    /// Meaning it moves the game one game tick forward.
    /// @param[out] success Set to true if player has beaten the game. Otherwise false.
    /// @param[out] exit Set to true if player has lost the game or won. Otherwise false.
    void update_game_state(bool& success, bool& exit);
    
    /// Updates all internal variables representing the state of bullets in the game.
    void update_bullets();
    
    /// Updates all internal variables representing the state of entities in the game.
    void update_entities();
    
    /// Updates all internal variables representing the state of enemies in the game.
    /// This method is called from 'update_entities()'.
    void update_enemies();
    
    /// Updates user interface so it shows in-game variables up to date.
    void update_interface();
    
    /// Sets up interface - meaning setting the position of elements and rendering them.
    void setup_interface();
    
    /// Renders the state of the game.
    /// @param[in, out] renderer Renderer used for displaying the state of the game.
    void render(CRenderer& renderer);
    
    /// Renderers entire game. This is useful when the rendering breaks in some way.
    /// This method is also called after exiting pause of the game.
    /// @param[out] renderer Renderer that should be reset - meaning it will render every
    ///                      element and not just differences between frames.
    void reset_rendering(CRenderer& renderer);
    
    /// Static method that resets terminal to its original state.
    static void cleanup();
    
    /// Configuration of the application the game is running in.
    std::shared_ptr<const CConfig> m_Config;
    
    /// Factory that creates object loaded from %m_Config.
    std::shared_ptr<const CFactory> m_Factory;
    
    /// Object used for loading a level from a file.
    CLevelBuilder m_LevelBuilder;
    
    /// Object for managing waves of enemies.
    CWavesManager m_WavesManager;
    
    /// Object for managing bonuses in the game - dropping bonuses from enemies, bonuses effecting player, ...
    CBonusManager m_BonusManager;
    
    /// Keyboard input for controlling the player.
    std::shared_ptr<CActionsInputRecorder> m_PlayerControls;
    
    /// Keyboard input for controlling the game.
    std::shared_ptr<CInputRecorder> m_UiControls;
    
    /// Updates the state of %m_PlayerControls and %m_UiControls.
    CInputManager m_InputManager;
    
    /// Map storing bullets in the game by their position.
    std::shared_ptr<CMap> m_BulletsMap;
    
    /// Map storing entities (player + enemies) in the game by their position.
    std::shared_ptr<CMap> m_EntitiesMap;
    
    /// Map storing static objects (walls + bonuses that are not picked up yet) in the game by their position.
    std::shared_ptr<CMap> m_EnvironmentMap;
    
    /// List of enemies in the game.
    std::list<std::shared_ptr<CEnemy>> m_Enemies;
    
    /// List of bullets in the game.
    std::list<CBullet> m_Bullets;
    
    /// Object representing player.
    CPlayer m_Player;
    
    /// Dimensions (width and height) of the current level.
    CPosition levelDimensions;
    
    /// UI element displaying player's health.
    CValueDisplay<int> m_HealthDisplay;
    
    /// UI element displaying number of bullets in player's magazine.
    CValueDisplay<int> m_AmmoDisplay;
    
    /// UI element displaying name of the gun that player has currently selected.
    CValueDisplay<std::string> m_CurrentGunDisplay;
};
