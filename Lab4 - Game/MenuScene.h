#pragma once

#include <vector>

#include "MenuItem.h"

using std::vector;

class MenuScene : public MenuObject
{
    typedef void(*CallbackKeyboard)(MenuScene*, unsigned char);
    typedef void(*CallbackIdle)(MenuScene*);
    typedef void(*CallbackSpecial)(MenuScene*, int);

public:
    MenuScene(int id, MenuObject* parent = nullptr);

    bool        getState();
    void        toggleState();

    void        display() override;
    void        addItem(MenuItem* newItem);

    void        setSpecialKeyboardFunc(CallbackKeyboard skf);
    void        setSpecialIdleFunc(CallbackIdle sif);
    void        setSpecialSpecialFunc(CallbackSpecial ssf);

    MenuItem*   getItemByID(int id);
    MenuItem*   getItemByCoord(prtd_ct::Point &position);
    void        removeItemByID(int id);
    int         getScore() { return _score; }
    int         getLifes() { return _defenderLifes; }

    void        processLeftClick(prtd_ct::Point &clickPosition);
    void        processKeyboard(unsigned char key);
    void        processIdle();
    void        processSpecial(int key);

public:
    vector<MenuItem*>   _enemies;
    vector<MenuItem*>   _alliesProjectiles;
    vector<MenuItem*>   _enemiesProjectiles;
    double              _projectileVelocity;
    double              _defenderVelocity;
    double              _enemiesVelocity;
    unsigned int        _defenderFireCooldown;
    unsigned int        _timeSinceLastShot          = 0;
    unsigned int        _enemyRespawnCooldown;
    unsigned int        _timeSinceLastEnemySpawned  = 0;
    int                 _enemyFireChance;
    unsigned int        _enemyFireCooldown;
    double              _enemyProjectileVelocity;
    int                 _enemyChangeDirectionChance;

    unsigned int        _defenderLifes              = 3;
    unsigned int        _score                      = 0;

private:
    bool                _isActive;
    vector<MenuItem*>   _items;

    CallbackKeyboard    _specialKeyboardFunc = nullptr;
    CallbackIdle        _specialIdleFunc = nullptr;
    CallbackSpecial     _specialSpecialFunc = nullptr;
};