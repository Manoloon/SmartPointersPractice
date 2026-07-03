#include "BuffSystem.h"
#include <print>
#include <random>
#include <unordered_map>
#include <array>
    /*
    El jugador puede recibir buffs.
    ejemplos : Velocidad, Fuego, escudo.
    Los buffs se muestran en dos sitios: Sobre el personaje, y en el HUD
    Requisitos : 
    Player : nombre y lista de buffs activos
    Buff : nombre y duracion
    HUD : conserva una referencia a los buffs para dibujar sus iconos.
    */

int main()
{
    std::vector<std::string> PlayersNames{"Paul","John","Ringo","George"};
    std::vector<std::string> BuffsNames{"Speed","Power","Invisibility","Shield"};
    auto m_Hud = std::make_shared<BsHUD>();
    std::array<std::shared_ptr<BsPlayer>,4> Players;
    for(int i = 0; i < Players.size(); ++i)
    {
        std::string name = PlayersNames.at(i);
        Players.at(i) = std::make_shared<BsPlayer>(name);   
    }

    m_Hud->ShowAllBuffInView();
    std::random_device rd;
    std::mt19937 rng(rd());

    for(auto& p : Players)
    {
        int RandomIndex = std::uniform_int_distribution(0,static_cast<int>(BuffsNames.size()))(rng);
        const std::string buff = BuffsNames.at(RandomIndex);
        
        if(const auto& m_Buff = p->SpawnBuff(buff))
        {
        m_Hud->AddActiveBuff(m_Buff);
        m_Buff->PrintOwner();
        }
    }
    
    m_Hud->ShowAllBuffInView();
    for(auto& p : Players)
    {
        p.reset();
    }
    m_Hud->ShowAllBuffInView();
}

// Player //

BsPlayer::BsPlayer(std::string Name):name(Name)
{
    std::cout << "Player Constructor\n";
}

BsPlayer::~BsPlayer()
{
    std::cout << "Player Destroy\n";
}

float BsPlayer::GetHealth() const
{
    return health;
}

const std::string BsPlayer::GetName() const
{
    return name;
}

std::shared_ptr<BsBuff> BsPlayer::SpawnBuff(const std::string& Name)
{
    if(Name == "") return {};
    ActiveBuff = std::make_shared<BsBuff>(weak_from_this(),Name);
    std::cout << " Player : Buff Spawned : " << Name << '\n';   
    return ActiveBuff;
}

// Buffs //

BsBuff::BsBuff(const std::weak_ptr<BsPlayer>& Owner,const std::string& Name)
    :Owner(Owner),Name(Name)
{
    std::cout << "Buff spawned : " << Name << '\n';
}

BsBuff::~BsBuff()
{
     std::cout << "Buff destroy\n";
}

void BsBuff::PrintName() const
{
    std::cout << "Buff name : " << Name << '\n';
}

void BsBuff::PrintOwner() const
{
    if(auto owner = Owner.lock())
    {
        std::cout << "My owner is : " << owner->GetName() << '\n';
    }
    else
    {
        std::cout << "My owner is not available!\n";
    }
}

// BsHUD //

void BsHUD::AddActiveBuff(std::weak_ptr<BsBuff> new_buff)
{
    if(new_buff.lock())
    {
        ActiveBuffs.emplace_back(new_buff);
    }
}

void BsHUD::ShowAllBuffInView()
{
    if(ActiveBuffs.empty())
    {
        std::cout << "Hud : No Active buffs\n";
        return;
    }
    for(auto it = ActiveBuffs.begin(); it != ActiveBuffs.end();)
    {
        std::cout << "Hud: ";
        if(auto b = it->lock())
        {
            b->PrintName();
            ++it;
        }
        else
        {
            it = ActiveBuffs.erase(it);
            std::cout << "Hud : unavailable buff\n";
        }
    }
}
