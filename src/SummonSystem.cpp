#include "SummonSystem.h"
#include <iostream>

int main()
{
    auto tracker = std::make_unique<SummonTracker>();
    auto player = std::make_unique<Player>(tracker.get());  
    player->SummonCreature(ECreatureType::Golem);
    player->SummonCreature(ECreatureType::Wolf);
    player->SummonCreature(ECreatureType::Skeleton);
    player->DestroyCreatureByType(ECreatureType::Wolf);
    //player->SummonCreature(ECreatureType::Skeleton);
    player.reset();
}

////////// Summon /////////////////
Summon::Summon(ECreatureType new_type, Player *Owner):Type(new_type),Owner(Owner)
{
    std::cout << "Summon : I am a :" << Type << "\n";
    std::cout << "Summon : My owner is :" << Owner << "\n";
}

Summon::~Summon()
{
    std::cout << "Summon : I died too\n";
}

////////// Player /////////////////
Player::~Player()
{
    std::cout << "Player : I died!\n";
    for(const auto& s : Summons)
    {
        tracker->UnregisterSummon(s.second.get());
    }
}
void Player::SummonCreature(ECreatureType new_type)
{
    auto new_summon = std::make_unique<Summon>(new_type,this);
    tracker->RegisterSummon(new_summon.get());
    Summons.emplace(new_type,std::move(new_summon));
    std::cout << "Player : I have summoned a : " << new_type << "\n";
}

void Player::DestroyCreatureByRef(Summon *summon)
{
    if(Summons.empty()) return;
    // buscar el summon en la lista
    std::unordered_map<ECreatureType,std::unique_ptr<Summon>>::iterator it = Summons.find(summon->GetType());
    if(it != Summons.end())
    {
        tracker->UnregisterSummon(it->second.get());
        it->second.reset();
        Summons.erase(it);      
    }
}

void Player::DestroyCreatureByType(ECreatureType Type)
{
    if(Summons.empty()) return;
    // buscar el summon en la lista
    std::unordered_map<ECreatureType,std::unique_ptr<Summon>>::iterator it = Summons.find(Type);
    if(it != Summons.end())
    {
        tracker->UnregisterSummon(it->second.get());
        it->second.reset();
        Summons.erase(it);      
    }
}

////////// SummonTracker /////////////////
void SummonTracker::RegisterSummon(Summon *Summon)
{
    if(Summon)
    {
        std::cout << "SummonTracker : " << Summon->GetType() << " Summoned\n"; 
    }
}

void SummonTracker::UnregisterSummon(Summon *Summon)
{
    if(Summon)
    {
        std::cout << "SummonTracker : " << Summon->GetType() << " Unsummoned\n"; 
    }
}
