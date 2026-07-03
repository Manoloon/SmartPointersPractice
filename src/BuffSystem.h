#pragma once

#include <memory>
#include <vector>
#include <string>
#include <iostream>

class BsBuff;
// hereda de enable_shared... para poder crear un weak_ptr de el.
class BsPlayer : public std::enable_shared_from_this<BsPlayer>
{
    float health = 100.f;
    std::string name{};
    // Owner de los buffs
    std::shared_ptr<BsBuff> ActiveBuff;
    public:
        explicit BsPlayer(std::string Name);
        ~BsPlayer();
        float GetHealth() const;
        const std::string GetName() const;
        std::shared_ptr<BsBuff> SpawnBuff(const std::string& Name);
};

class BsBuff
{
   std::weak_ptr<BsPlayer> Owner;
   std::string Name{};
public:
    explicit BsBuff(const std::weak_ptr<BsPlayer>& Owner,const std::string& Name);
   ~BsBuff();
   void PrintName() const;
   void PrintOwner() const;
};

class BsHUD
{
    // necesita acceso a los buffs para poder imprimirlos en pantalla
    std::vector<std::weak_ptr<BsBuff>> ActiveBuffs;
    public:
    void AddActiveBuff(std::weak_ptr<BsBuff> new_buff );
    void ShowAllBuffInView();
};
