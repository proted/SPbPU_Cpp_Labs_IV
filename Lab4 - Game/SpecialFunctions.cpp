#define _CRT_SECURE_NO_WARNINGS
#include "SpecialFunctions.h"

#include <cstdlib>
#include <ctime>
#include <string>

#include "Miscellaneous.h"

#define PI 3.1415926535897932384626433832795

//Special drawing functions
void sdf_button11(MenuItem* item)
{
    prtd_ct::Rectangle pos = item->getRectangle();
    double x = pos.point.x;
    double y = pos.point.y;
    double w = pos.width;
    double h = pos.height;

    glBegin(GL_TRIANGLES);
    glColor3d(1.0, 0.0, 0.5);

    glVertex2d(x, y);
    glVertex2d(x + w / 2, y + h);
    glVertex2d(x + w, y);

    glEnd();
}
void sdf_stats(MenuItem* item)
{
    prtd_ct::Rectangle  rect = item->getRectangle();
    double x = rect.point.x;
    double y = rect.point.y;
    double w = rect.width;
    double h = rect.height;

    glBegin(GL_LINES);
    glColor3d(0.0, 1.0, 0.5);
    glVertex2d(x, y);
    glVertex2d(x + w, y);
    glVertex2d(x + w, y);
    glVertex2d(x + w, y + h);
    glVertex2d(x + w, y + h);
    glVertex2d(x, y + h);
    glVertex2d(x, y + h);
    glVertex2d(x, y);
    glEnd();

    glRasterPos2d(x, y + h / 3.0);
    std::string score_str = "Score: ";
    score_str += std::to_string(((MenuScene*)item->getParent())->getScore());
    for (auto& ch : score_str)
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, ch);
    }
    std::string lifes_str = "Lifes: ";
    lifes_str += std::to_string(((MenuScene*)item->getParent())->getLifes());
    glRasterPos2d(x, y + 2 * h / 3.0);
    for (auto& ch : lifes_str)
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, ch);
    }
}
void sdf_projectile(MenuItem* item)
{
    prtd_ct::Rectangle rect = item->getRectangle();
    double x = rect.point.x + rect.width / 2.0;
    double y = rect.point.y + rect.height / 2.0;

    glColor3d(0.0, 1.0, 0.0);
    glBegin(GL_TRIANGLE_FAN);
    for (double r = 0.01; r < rect.height / 2; r += 0.25)
    {
        for (double phi = 0; phi < 2 * PI; phi += 0.1)
        {
            glVertex2d(x + r * cos(phi), y + r * sin(phi));
        }
    }
    glEnd();
}
void sdf_enemyProjectile(MenuItem* item)
{
    prtd_ct::Rectangle rect = item->getRectangle();
    double x = rect.point.x + rect.width / 2.0;
    double y = rect.point.y + rect.height / 2.0;

    glColor3d(1.0, 0.0, 0.3);
    glBegin(GL_TRIANGLE_FAN);
    for (double r = 0.01; r < rect.height / 2; r += 0.25)
    {
        for (double phi = 0; phi < 2 * PI; phi += 0.1)
        {
            glVertex2d(x + r * cos(phi), y + r * sin(phi));
        }
    }
    glEnd();
}

//Special clicking functions
void scf_button11(MenuItem* item, prtd_ct::Point &point)
{
    ((MenuView*)item->getParent()->getParent())->swapScene(2);
}
void scf_button21(MenuItem* item, prtd_ct::Point &point)
{
    ((MenuView*)item->getParent()->getParent())->swapScene(1);
}

//Special keyboard functions
void skf_scene2(MenuScene* scene, unsigned char key)
{
    static int projectileID = 100001;
    switch (key)
    {
    case 32:
        if (scene->_timeSinceLastShot <= scene->_defenderFireCooldown)
        {
            break;
        }
        else
        {
            scene->_timeSinceLastShot = 0;
        }
        prtd_ct::Point defenderPoint = scene->getItemByID(-1)->getRectangle().point;
        defenderPoint.x += scene->getItemByID(-1)->getRectangle().width / 2;
        prtd_ct::Rectangle rect = prtd_ct::Rectangle{ defenderPoint, 10, 10 };
        MenuItem* projectile = new MenuItem(projectileID++, rect, "", scene);
        projectile->setSpecialDrawingFunc(sdf_projectile);
        scene->addItem(projectile);
        scene->_alliesProjectiles.push_back(projectile);
        break;
    }
}

//Special idle functions
void sif_scene2(MenuScene* scene)
{
    static int enemiesID = -101;
    static int enemiesProjectileID = -1000001;
    scene->_timeSinceLastShot++;
    scene->_timeSinceLastEnemySpawned++;
    srand(unsigned(time(0)) ^ enemiesID);

    if (scene->_defenderLifes == 0)
    {
        printf("You lost!");
        exit(-1);
    }

    //Enemies spawning
    if (scene->_timeSinceLastEnemySpawned > scene->_enemyRespawnCooldown)
    {
        scene->_timeSinceLastEnemySpawned = 0;
        srand(rand() ^ (1 - rand()));
        scene->_timeSinceLastEnemySpawned = 0;
        double enemyXSpawnCoord = 20 + rand() % 1240;
        double enemyYSpawnCoord = 715;
        int direction = (rand() % 2) ? 1 : -1;
        prtd_ct::Rectangle enemyRect = prtd_ct::Rectangle{ prtd_ct::Point{enemyXSpawnCoord, enemyYSpawnCoord}, 50, 20 };
        MenuItem* newEnemy = new MenuItem(enemiesID++, enemyRect, "Enemy", scene);
        newEnemy->_enemyMovingDirection = direction;
        scene->addItem(newEnemy);
        scene->_enemies.push_back(newEnemy);
    }

    //Enemies projectile spawning
    for (auto& enemy : scene->_enemies)
    {
        srand(rand() ^ (1 + rand()));
        if (enemy->_enemyTimeSinceLastShot > scene->_enemyFireCooldown)
        {
            if (rand() % scene->_enemyFireChance == 1)
            {
                prtd_ct::Point enemyPos = enemy->getRectangle().point;
                prtd_ct::Rectangle enemyRect = prtd_ct::Rectangle{ enemyPos, 10, 10 };
                MenuItem* enemyProjectile = new MenuItem(enemiesProjectileID++, enemyRect, "", scene);
                enemyProjectile->setSpecialDrawingFunc(sdf_enemyProjectile);
                scene->addItem(enemyProjectile);
                scene->_enemiesProjectiles.push_back(enemyProjectile);
                enemy->_enemyTimeSinceLastShot = 0;
            }
        }
        enemy->_enemyTimeSinceLastShot++;
    } 

    //Enemies movind
    for (auto& enemy : scene->_enemies)
    {
        if (enemy->getID() == -100)
        {
            continue;
        }
        prtd_ct::Rectangle rect = enemy->getRectangle();
        prtd_ct::Point point = rect.point;
        point.x += scene->_enemiesVelocity * enemy->_enemyMovingDirection;
        if (point.x <= 0)
        {
            point.x = 0;
        }
        if (point.x + rect.width >= 720)
        {
            point.x = 720 - rect.width;
        }
        point.y -= scene->_enemiesVelocity;
        rect.setPosition(point);
        enemy->setRectangle(rect);
        if (rand() % scene->_enemyChangeDirectionChance == 1)
        {
            enemy->_enemyMovingDirection *= -1;
        }
    }
    for (auto iter = scene->_enemies.begin(); iter != scene->_enemies.end(); ++iter)
    {
        if ((*iter)->getID() == -100)
        {
            continue;
        }
        prtd_ct::Point point = (*iter)->getRectangle().point;
        if (point.y < 0 || point.y > 720)
        {
            if (scene->_enemies.size() > 1)
            {
                scene->removeItemByID((*iter)->getID());
                scene->_enemies.erase(iter);
                iter = scene->_enemies.begin();
            }
        }
    }

    //Allies projectiles moving
    for (auto& alliesProjectile : scene->_alliesProjectiles)
    {
        if (alliesProjectile->getID() == 100000)
        {
            continue;
        }
        prtd_ct::Rectangle rect = alliesProjectile->getRectangle();
        prtd_ct::Point point = rect.point;
        point.y += scene->_projectileVelocity;
        rect.setPosition(point);
        alliesProjectile->setRectangle(rect);
    }
    for (auto iter = scene->_alliesProjectiles.begin(); iter != scene->_alliesProjectiles.end(); ++iter)
    {
        if ((*iter)->getID() == 100000)
        {
            continue;
        }
        prtd_ct::Point point = (*iter)->getRectangle().point;
        if (point.y < 0 || point.y > 720)
        {
            if (scene->_alliesProjectiles.size() > 1)
            {
                scene->removeItemByID((*iter)->getID());
                scene->_alliesProjectiles.erase(iter);
                iter = scene->_alliesProjectiles.begin();
            }
        }
    }

    //Enemies projectiles moving
    for (auto& enemiesProjectile : scene->_enemiesProjectiles)
    {
        if (enemiesProjectile->getID() == -1000000)
        {
            continue;
        }
        prtd_ct::Rectangle rect = enemiesProjectile->getRectangle();
        prtd_ct::Point point = rect.point;
        point.y -= scene->_enemyProjectileVelocity;
        rect.setPosition(point);
        enemiesProjectile->setRectangle(rect);
    }
    for (auto iter = scene->_enemiesProjectiles.begin(); iter != scene->_enemiesProjectiles.end(); ++iter)
    {
        if ((*iter)->getID() == -1000000)
        {
            continue;
        }
        prtd_ct::Point point = (*iter)->getRectangle().point;
        if (point.y < 0 || point.y > 720)
        {
            if (scene->_enemiesProjectiles.size() > 1)
            {
                scene->removeItemByID((*iter)->getID());
                scene->_enemiesProjectiles.erase(iter);
                iter = scene->_enemiesProjectiles.begin();
            }
        }
    }

    //Defender projectile - enemies collision check
    for (auto defenderProjectileIter = scene->_alliesProjectiles.begin();
         defenderProjectileIter != scene->_alliesProjectiles.end();
         ++defenderProjectileIter)
    {
        if ((*defenderProjectileIter)->getID() == 100000)
        {
            continue;
        }
        for (auto enemyIter = scene->_enemies.begin(); enemyIter != scene->_enemies.end(); ++enemyIter)
        {
            if ((*enemyIter)->getID() == -100)
            {
                continue;
            }
            MenuItem* enemy = (*enemyIter);
            MenuItem* defenderProjectile = (*defenderProjectileIter);
            if (misc_isObjectsCollided(defenderProjectile, enemy))
            {
                if (scene->_alliesProjectiles.size() > 1)
                {
                    scene->removeItemByID(defenderProjectile->getID());
                    scene->_alliesProjectiles.erase(defenderProjectileIter);
                    defenderProjectileIter = scene->_alliesProjectiles.begin();
                }
                if (scene->_enemies.size() > 1)
                {
                    scene->removeItemByID(enemy->getID());
                    scene->_enemies.erase(enemyIter);
                    enemyIter = scene->_enemies.begin();
                }
                scene->_score += 1;
            }
        }
    }

    //Enemies projectile - defender collision check
    for (auto enemyProjectileIter = scene->_enemiesProjectiles.begin();
        enemyProjectileIter != scene->_enemiesProjectiles.end();
        ++enemyProjectileIter)
    {
        if ((*enemyProjectileIter)->getID() == -1000000)
        {
            continue;
        }
        MenuItem* enemyProjectile = (*enemyProjectileIter);
        MenuItem* defender = scene->getItemByID(-1);
        if (misc_isObjectsCollided(defender, enemyProjectile))
        {
            if (scene->_enemiesProjectiles.size() > 1)
            {
                scene->removeItemByID(enemyProjectile->getID());
                scene->_enemiesProjectiles.erase(enemyProjectileIter);
                enemyProjectileIter = scene->_enemiesProjectiles.begin();
            }
            scene->_defenderLifes -= 1;
        }
    }

}

//Special special functions :)
void ssf_scene2(MenuScene* scene, int key)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
    {
        prtd_ct::Rectangle rect = scene->getItemByID(-1)->getRectangle();
        if (rect.point.x > 0)
        {
            rect.point.x -= scene->_defenderVelocity;
        }
        scene->getItemByID(-1)->setRectangle(rect);
        break;
    }
    case GLUT_KEY_RIGHT:
    {
        prtd_ct::Rectangle rect = scene->getItemByID(-1)->getRectangle();
        if (rect.point.x + rect.width < 1280)
        {
            rect.point.x += scene->_defenderVelocity;
        }
        scene->getItemByID(-1)->setRectangle(rect);
        break;
    }
    }
}
