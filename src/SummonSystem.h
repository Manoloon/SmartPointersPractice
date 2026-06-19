/* Imagina un RPG donde un jugador puede invocar criaturas.
Un jugador puede invocar:
Wolf
Skeleton
Golem

Cada invocación tiene:
Nombre
Vida
Daño

Reglas de gameplay
    Una invocación conoce quién la creó. Skeleton -> Player

    El jugador mantiene una lista de sus invocaciones activas.
                                            Player
                                            ├── Wolf
                                            ├── Skeleton
                                            └── Golem
    Cuando una invocación muere: debe desaparecer automáticamente del juego.

    Cuando el jugador muere: todas las invocaciones deben desaparecer.

    Existe un sistema global: SummonTracker : que muestra por consola todas las invocaciones activas.
                                            Wolf
                                            Skeleton
                                            Golem
                                            Regla 6
    El SummonTracker NO debe impedir que una invocación sea destruida.*/
#pragma once
#include <memory>
#include <unordered_map>

class Player;
enum ECreatureType
{
    Wolf,Skeleton,Golem,
};

// yo no veo porque Summon deberia tener puntero a su owner.
class Summon
{
    ECreatureType Type;
    Player* Owner;
    public:
    Summon(ECreatureType new_type,Player* Owner);
    ~Summon();

    inline ECreatureType GetType() const {return Type;}
    void Die();
};

// observer
class SummonTracker
{
    public:
    void RegisterSummon(Summon* Summon);
    void UnregisterSummon(Summon* Summon);
};

// lifetime controller
// El Owner de las invocaciones
class Player
{
    std::unordered_map<ECreatureType,std::unique_ptr<Summon>> Summons;
    SummonTracker* tracker;
    public:
    explicit Player(SummonTracker* track):tracker(track){}
    ~Player();

    void SummonCreature(ECreatureType new_type);
    void DestroyCreatureByRef(Summon* summon);
    void DestroyCreatureByType(ECreatureType Type);
};
