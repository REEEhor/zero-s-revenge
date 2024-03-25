#pragma once

#include "CClaymore.h"
#include "CMinePlacer.h"
#include "CShotgun.h"
#include "CPistol.h"
#include "CGun.h"
#include "CIndestructibleObject.h"
#include "CDamagingMovableObject.h"
#include "CCollidingMovableObject.h"
#include "CPlayer.h"
#include "CObject.h"
#include "CChargeEnemy.h"
#include "CRangedEnemy.h"
#include "CRangedEnemyAi.h"
#include "CMeleeEnemy.h"
#include "CMeleeEnemyAi.h"
#include "CSimpleFollowerAi.h"
#include "CLoopFollowerAi.h"
#include "CDumbFollowerAi.h"
#include "CScaredFollowerAi.h"
#include "CConfig.h"
#include <string>
#include <unordered_map>

/// @brief Class that that creates entities (objects, entities, guns, ...) from loaded configuration.
class CEntityFactory {
public:
    
    /// Constructor of CEntityFactory.
    /// @param[in] config Pointer to the configuration loaded from a file.
    explicit CEntityFactory(const std::shared_ptr<const CConfig>& config);
    
    /// Creates a box defined in %m_Config.
    /// Box is supposed to work like a wall except being easier to destroy.
    /// @param[in] position Position where the box should be created.
    /// @return Pointer to the created box.
    std::shared_ptr<CObject> create_box(const CPosition& position) const;
    
    /// Creates a wall defined in %m_Config.
    /// @param[in] position Position where the wall should be created.
    /// @return Pointer to the created wall.
    std::shared_ptr<CObject> create_wall(const CPosition& position) const;
    
    /// Creates a indestructible wall defined in %m_Config.
    /// @param[in] position Position where the indestructible wall should be created.
    /// @return Pointer to the created indestructible wall.
    std::shared_ptr<CObject> create_indestructible_wall(const CPosition& position) const;
    
    /// Creates either ranged or melee enemy based on the symbol that represents the
    /// enemy. This is used when defining waves of enemies, where the enemies are represented
    /// by a single character in the level file.
    /// @param[in] position Position where the enemy should be spawned.
    /// @param[in] enemySymbol Symbol that represent the enemy in a level file.
    /// @return Pointer to the created enemy.
    /// @throws std::invalid_argument When the name of the found enemy does not start with
    ///                               'M' or 'R' signalling internal error.
    std::shared_ptr<CEnemy> create_enemy(const CPosition& position, char enemySymbol) const;
    
    /// Since enemies are represented by a character, this method is used to check,
    /// whether a symbol corresponds to an enemy that can be created.
    /// @param[in] symbol Symbol that we want to check.
    /// @return Whether this factory can or cannot create enemy that is represented by
    ///         checked symbol.
    [[nodiscard]] bool can_create_enemy_with_symbol(char symbol) const;
    
    /// Creates new charged enemy. These enemies are not represented by a character
    /// (which is different from melee and ranged enemies) but rather a two digit value.
    /// @param[in] position Position where the enemy should be spawned.
    /// @param[in] strength The two digit value representing the enemy.
    /// @return Pointer to the created enemy.
    /// @throws std::invalid_argument When strength is not a two digit value.
    std::shared_ptr<CEnemy> create_charged_enemy(const CPosition& position, int strength) const;
    
    /// Creates a player object based on the loaded configuration from file.
    /// @param[in] position Starting position of the player.
    /// @param[in] inputs Pointer to the keyboard input of the player.
    CPlayer create_player(const CPosition& position, const std::shared_ptr<CActionsInputRecorder>& inputs) const;
    
    /// Creates a keyboard input for the player based on the loaded configuration from file.
    /// @return Pointer to the created keyboard input.
    std::shared_ptr<CActionsInputRecorder> create_player_controls() const;
    
    /// Creates a pistol object.
    /// @param[in] pistolId Name of the pistol in the configuration file.
    /// @param[in] infiniteAmmo Whether pistol should have infinite ammo or not.
    ///                         This parameter is actually set in the configuration file
    ///                         but setting this parameter to true overrides it and the value
    ///                         in the config is not looked up.
    ///                         This is useful for created enemies since their guns should have infinite ammo.
    /// @param[in] hasName Similar to %infiniteAmmo. If the value is set to false, name of the gun will not be
    ///                    looked up and set to an empty string.
    ///                    This is useful for created enemies since their guns do not need a name.
    /// @return Pointer to the created pistol
    std::shared_ptr<CPistol> create_pistol(const std::string& pistolId,
                                           bool infiniteAmmo = false, bool hasName = true) const;
    
    /// Creates a shotgun object based on the loaded values in %m_Config.
    /// @return Pointer to the created shotgun.
    std::shared_ptr<CGun> create_shotgun() const;
    
    /// Creates a claymore object based on the loaded values in %m_Config.
    /// @return Pointer to the created claymore.
    std::shared_ptr<CGun> create_claymore() const;
    
    /// Creates a mine placer object based on the loaded values in %m_Config.
    /// @return Pointer to the created mine placer.
    std::shared_ptr<CGun> create_mine_placer() const;
    
    /// Creates all guns available to the player.
    /// @return Vector of pointers to the created guns.
    std::vector<std::shared_ptr<CGun>> create_all_available_guns() const;

private:
    /// Creates a follower AI that is later used for creating enemies based on the level of
    /// 'smartness' of the AI.
    /// @param[in] level Level of AI. Available values are:
    ///                  (2) CSimpleEnemyAi (1) CDumbAi (0) CLoopAi (-1) CScaredAi
    ///                  invalid level of AI is treated as option 2.
    /// @return Pointer to the created follower AI.
    static std::shared_ptr<CFollowerAi> get_follower_ai_from_level(int level);
    
    /// Creates a melee enemy.
    /// @param[in] position Initial position of the created enemy.
    /// @param[in] enemyName Name of the enemy in the config file.
    /// @return Pointer to the created enemy.
    std::shared_ptr<CEnemy> create_melee_enemy(const CPosition& position, const std::string& enemyName) const;
    
    /// Creates a ranged enemy.
    /// @param[in] position Initial position of the created enemy.
    /// @param[in] enemyName Name of the enemy in the config file.
    /// @return Pointer to the created enemy.
    std::shared_ptr<CEnemy> create_ranged_enemy(const CPosition& position, const std::string& enemyName) const;
    
    /// Creates a pistol for a ranged enemy. The pistol has infinite ammo and empty string as a name,
    /// since these values are not needed.
    /// @param[in] enemyName Name of the enemy the gun belongs to.
    /// @return Pointer to the created pistol.
    std::shared_ptr<CPistol> create_enemy_pistol(const std::string& enemyName) const;
    
    /// Creates a colliding movable object used for creating entities.
    /// @param[in] position Initial position of the created object.
    /// @param[in] objectName Name of the object in the config file.
    /// @return Pointer to the created colliding movable object.
    std::shared_ptr<CCollidingMovableObject> create_colliding_object(const CPosition& position,
                                                                     const std::string& objectName) const;
    
    /// Creates colliding movable object that represents player physical state in the game.
    /// @param[in] position Initial position of the created object.
    /// @return Pointer to the created colliding movable object.
    std::shared_ptr<CCollidingMovableObject> create_player_object(const CPosition& position) const;
    
    
    /// Creates a bullet builder based on the name of the gun that uses it.
    /// @param[in] gunId Id of the gun (its name in the configuration file) that shoots the bullets
    ///                  created by the bullet builder that we want to create.
    /// @return Bullet builder that belongs to the gun.
    CBulletObjectBuilder create_bullet_builder(const std::string& gunId) const;
    
    /// Gets values that are needed for creating all types of guns (the guns might need additional attributes).
    /// @param[in] gunId Id of the gun (its name in the configuration file) that the values are for.
    /// @param[out] name Of the gun (the text that will be displayed when player has that gun as selected).
    /// @param[out] maxAmmo Maximum ammo of the gun (this value is set to -1 if the ammo is infinite).
    /// @param[out] fireRatePeriod How often (how frequently) should the gun be able to shoot.
    /// @param[out] infiniteAmmo Whether the gun should have an infinite magazine.
    void get_general_gun_stats(const std::string& gunId, std::string& name, int& maxAmmo,
                               int& fireRatePeriod, bool& infiniteAmmo) const;
    
    /// Pointer to the config loaded from file for lookup of necessary values.
    std::shared_ptr<const CConfig> m_Config;
    
    /// Map used for converting between symbols representing enemies in the level file
    /// and their name in the configuration file.
    std::unordered_map<char, std::string> m_EnemySymbolsToNames;
};
