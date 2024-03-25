#include "CEntityFactory.h"

CEntityFactory::CEntityFactory(const std::shared_ptr<const CConfig>& config)
        : m_Config(config) {
    
    // Load enemy symbols into %m_EnemySymbolsToNames for later lookup.
    std::ostringstream stream;
    
    // Melee enemies.
    for (int i = 1; i <= 6; ++i) {
        stream.str("");
        stream << "M_ENEMY_" << i;
        m_EnemySymbolsToNames.insert({m_Config->m_Char[stream.str()], stream.str()});
    }
    // Ranges enemies.
    for (int i = 1; i <= 3; ++i) {
        stream.str("");
        stream << "R_ENEMY_" << i;
        m_EnemySymbolsToNames.insert({m_Config->m_Char[stream.str()], stream.str()});
    }
}

std::shared_ptr<CObject> CEntityFactory::create_wall(const CPosition& position) const {
    return std::make_shared<CObject>(position,
                                     m_Config->m_Int["WALL_HEALTH"],
                                     m_Config->m_CVisualBlock["WALL_SPRITE"],
                                     false);
}

std::shared_ptr<CObject> CEntityFactory::create_indestructible_wall(const CPosition& position) const {
    return std::make_shared<CIndestructibleObject>(position,
                                                   m_Config->m_CVisualBlock["IND_WALL_SPRITE"],
                                                   false);
}

std::shared_ptr<CCollidingMovableObject> CEntityFactory::create_player_object(const CPosition& position) const {
    return std::make_shared<CCollidingMovableObject>(position,
                                                     m_Config->m_Int["P_MAX_HEALTH"],
                                                     m_Config->get_sprites_of("P"),
                                                     false);
}

std::shared_ptr<CObject> CEntityFactory::create_box(const CPosition& position) const {
    return std::make_shared<CObject>(position,
                                     m_Config->m_Int["BOX_HEALTH"],
                                     m_Config->m_CVisualBlock["BOX_SPRITE"],
                                     false);
}

std::shared_ptr<CEnemy> CEntityFactory::create_enemy(const CPosition& position, char enemySymbol) const {
    const std::string name = m_EnemySymbolsToNames.at(enemySymbol);
    
    // First character in the enemy name determines whether it is a ranged or a melee type enemy.
    switch (name[0]) {
        case 'R': // Ranged enemy.
            return create_ranged_enemy(position, name);
        case 'M': // Melee enemy.
            return create_melee_enemy(position, name);
        default:
            throw std::invalid_argument("invalid enemy symbol");
    }
}

std::shared_ptr<CEnemy>
CEntityFactory::create_charged_enemy(const CPosition& position, int strength) const {
    std::ostringstream stream;
    stream << strength;
    if (stream.str().length() != 2) {
        throw std::invalid_argument("strength has to be a two digit value");
    }
    auto visualBlock = CVisualBlock(stream.str(),
                                    m_Config->m_Color["CHARGED_FG"],
                                    m_Config->m_Color["CHARGED_BG"]);
    auto object = std::make_shared<CDamagingMovableObject>(position,
                                                           strength,
                                                           visualBlock,
                                                           strength,
                                                           true);
    int updatePeriod = m_Config->m_Int["CHARGED_UPDATE_PERIOD"];
    
    auto& ai = *get_follower_ai_from_level(m_Config->m_Int["CHARGED_AI_LEVEL"]);
    return std::make_shared<CChargeEnemy>(object, ai, updatePeriod, Toughness::NONE);
}

std::shared_ptr<CFollowerAi> CEntityFactory::get_follower_ai_from_level(int level) {
    switch (level) {
        
        case -1: {
            CScaredFollowerAi ai;
            return ai.clone_as_follower();
        }
        
        case 0: {
            CLoopFollowerAi ai;
            return ai.clone_as_follower();
        }
        
        case 1: {
            CDumbFollowerAi ai;
            return ai.clone_as_follower();
        }
        
        default: {
            CSimpleFollowerAi ai;
            return ai.clone_as_follower();
        }
    }
}

std::shared_ptr<CEnemy>
CEntityFactory::create_melee_enemy(const CPosition& position, const std::string& enemyName) const {
    auto enemyObject = create_colliding_object(position, enemyName);
    
    // Rename for clearer syntax
    const std::string& e = enemyName;
    
    auto ai = CMeleeEnemyAi(*get_follower_ai_from_level(m_Config->m_Int[e + "_AI_LEVEL"]));
    int updatePeriod = m_Config->m_Int[e + "_UPDATE_PERIOD"];
    Toughness::EToughness toughness = m_Config->m_Toughness[e + "_TOUGHNESS"];
    int damage = m_Config->m_Int[e + "_DAMAGE"];
    
    return std::make_shared<CMeleeEnemy>(enemyObject, ai, updatePeriod, toughness, damage);
}

std::shared_ptr<CEnemy>
CEntityFactory::create_ranged_enemy(const CPosition& position, const std::string& enemyName) const {
    auto enemyObject = create_colliding_object(position, enemyName);
    
    // Rename for clearer syntax
    const std::string& e = enemyName;
    
    int sight = m_Config->m_Int[e + "_SIGHT"]; // Distance the enemy should look into when looking for player.
    auto ai = CRangedEnemyAi(sight,
                             *get_follower_ai_from_level(m_Config->m_Int[e + "_AI_LEVEL"]));
    int updatePeriod = m_Config->m_Int[e + "_UPDATE_PERIOD"];
    Toughness::EToughness toughness = m_Config->m_Toughness[e + "_TOUGHNESS"];
    auto gun = create_enemy_pistol(enemyName);
    return std::make_shared<CRangedEnemy>(enemyObject, ai, updatePeriod, toughness, *gun);
}

std::shared_ptr<CCollidingMovableObject>
CEntityFactory::create_colliding_object(const CPosition& position, const std::string& objectName) const {
    return std::make_shared<CCollidingMovableObject>(position,
                                                     m_Config->m_Int[objectName + "_HEALTH"],
                                                     m_Config->get_sprites_of(objectName),
                                                     false);
}

std::shared_ptr<CPistol> CEntityFactory::create_enemy_pistol(const std::string& enemyName) const {
    return create_pistol(enemyName + "_PISTOL", true, false);
}

std::shared_ptr<CPistol>
CEntityFactory::create_pistol(const std::string& pistolId, bool infiniteAmmo, bool hasName) const {
    
    // Rename for clearer syntax
    const std::string& p = pistolId;
    std::string name = (!hasName ? "" : m_Config->m_String[p + "_NAME"]);
    auto bulletBuilder = create_bullet_builder(pistolId);
    int maxAmmo = (infiniteAmmo ? -1 : m_Config->m_Int[p + "_MAX_AMMO"]);
    int fireRatePeriod = m_Config->m_Int[p + "_FIRE_RATE_PERIOD"];
    
    if (maxAmmo < 0) {
        infiniteAmmo = true;
    }
    
    return std::make_shared<CPistol>(name, bulletBuilder, maxAmmo, fireRatePeriod, infiniteAmmo, false);
}

CBulletObjectBuilder CEntityFactory::create_bullet_builder(const std::string& gunId) const {
    
    std::string bulletName = gunId + "_BULLET";
    //
    int damage = m_Config->m_Int[bulletName + "_DAMAGE"];
    Color::EColor fgColor = m_Config->m_Color[bulletName + "_FG"];
    Color::EColor bgColor = m_Config->m_Color[bulletName + "_BG"];
    int movePeriod = m_Config->m_Int[bulletName + "_MOVE_PERIOD"];
    int healthPoints = m_Config->m_Int[bulletName + "_HEALTH"];
    //
    const std::string visuals = m_Config->m_String[bulletName + "_VISUALS"];
    char upSymbol = visuals[0];
    char downSymbol = visuals[1];
    char leftSymbol = visuals[2];
    char rightSymbol = visuals[3];
    
    return {damage, fgColor, bgColor, movePeriod, healthPoints, upSymbol, downSymbol, leftSymbol, rightSymbol};
}

std::shared_ptr<CGun> CEntityFactory::create_shotgun() const {
    const std::string& shotgunId = "SHOTGUN";
    CBulletObjectBuilder bulletBuilder = create_bullet_builder(shotgunId);
    std::string name;
    int maxAmmo;
    int fireRatePeriod;
    bool infiniteAmmo;
    
    get_general_gun_stats(shotgunId, name, maxAmmo, fireRatePeriod, infiniteAmmo);
    return std::make_shared<CShotgun>(name, bulletBuilder, maxAmmo, fireRatePeriod, infiniteAmmo);
}

void CEntityFactory::get_general_gun_stats(const std::string& gunId, std::string& name, int& maxAmmo,
                                           int& fireRatePeriod, bool& infiniteAmmo) const {
    name = m_Config->m_String[gunId + "_NAME"];
    maxAmmo = m_Config->m_Int[gunId + "_MAX_AMMO"];
    fireRatePeriod = m_Config->m_Int[gunId + "_FIRE_RATE_PERIOD"];
    infiniteAmmo = maxAmmo == -1;
}

std::shared_ptr<CGun> CEntityFactory::create_claymore() const {
    const std::string& claymoreId = "CLAYMORE";
    CBulletObjectBuilder bulletBuilder = create_bullet_builder(claymoreId);
    std::string name;
    int maxAmmo;
    int fireRatePeriod;
    CVisualBlock claymoreSprite = m_Config->m_CVisualBlock[claymoreId + "_CLAYMORE_SPRITE"];
    bool infiniteAmmo;
    
    get_general_gun_stats(claymoreId, name, maxAmmo, fireRatePeriod, infiniteAmmo);
    return std::make_shared<CClaymore>(name, bulletBuilder, maxAmmo, fireRatePeriod, claymoreSprite, infiniteAmmo);
}

std::shared_ptr<CGun> CEntityFactory::create_mine_placer() const {
    const std::string& minePlacerId = "MINE_PLACER";
    CBulletObjectBuilder bulletBuilder = create_bullet_builder(minePlacerId);
    std::string name;
    int maxAmmo;
    int fireRatePeriod;
    bool infiniteAmmo;
    get_general_gun_stats(minePlacerId, name, maxAmmo, fireRatePeriod, infiniteAmmo);
    return std::make_shared<CMinePlacer>(name, bulletBuilder, maxAmmo, fireRatePeriod, infiniteAmmo);
}

CPlayer CEntityFactory::create_player(const CPosition& position,
                                      const std::shared_ptr<CActionsInputRecorder>& inputs) const {
    return {create_player_object(position), inputs};
}

bool CEntityFactory::can_create_enemy_with_symbol(char symbol) const {
    return m_EnemySymbolsToNames.find(symbol) != m_EnemySymbolsToNames.end();
}

std::shared_ptr<CActionsInputRecorder> CEntityFactory::create_player_controls() const {
    return std::make_shared<CActionsInputRecorder>(
            m_Config->m_Char["UP"],
            m_Config->m_Char["DOWN"],
            m_Config->m_Char["LEFT"],
            m_Config->m_Char["RIGHT"],
            m_Config->m_Char["SHOOT"],
            m_Config->m_Char["SELECT_FIRST_GUN"],
            m_Config->m_Char["SELECT_SECOND_GUN"],
            m_Config->m_Char["SELECT_THIRD_GUN"],
            m_Config->m_Char["SELECT_FOURTH_GUN"],
            m_Config->m_Char["SELECT_FIFTH_GUN"],
            m_Config->m_Char["SELECT_SIXTH_GUN"],
            m_Config->m_Char["SELECT_SEVENTH_GUN"],
            m_Config->m_Char["SELECT_EIGHT_GUN"],
            m_Config->m_Char["SELECT_NINTH_GUN"]
    );
}

std::vector<std::shared_ptr<CGun>> CEntityFactory::create_all_available_guns() const {
    std::vector<std::shared_ptr<CGun>> guns;
    for (const auto& pistol: {"LAME_GUN", "UZI", "AK-0"}) {
        guns.emplace_back(create_pistol(pistol));
    }
    guns.emplace_back(create_shotgun());
    guns.emplace_back(create_claymore());
    guns.emplace_back(create_mine_placer());
    return guns;
}



