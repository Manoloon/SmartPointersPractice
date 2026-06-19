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
#include <memory>
#include <array>
#include <iostream>
enum ECreatureType
{
    Wolf,Skeleton,Golem,
};
class Summon;
// lifetime controller
class Player
{
    std::unique_ptr<Summon> Summons;
    public:
    void SummonCreature(ECreatureType new_type)
    {
        Summons = std::make_unique<Summon>(new_type);
        std::cout << "Player : I have summoned a : " << new_type << "\n";
    }
    ~Player()
    {
        std::cout << "Player : I died!\n"; 
    }
};

class Summon
{
    ECreatureType Type;
    public:
    Summon(ECreatureType new_type):Type(new_type)
    {
        std::cout << "Summon : I am a :" << Type << "\n";
    }
    ECreatureType GetType() const {return Type;}
    ~Summon()
    {
        std::cout << "Summon : I died too\n";
    }
};

// observer
class SummonTracker
{
    Summon* SummonOnStage;
    public:
    void RegisterSummon(Summon* new_summon)
    {
        if(new_summon)
        {
            SummonOnStage = new_summon;
            std::cout << "SummonTracker : " << new_summon->GetType() << "Summoned\n";
        }
    }
    void UnregisterSummon(Summon* summon)
    {
        if(SummonOnStage == summon)
        {
            std::cout << "SummonTracker : " << SummonOnStage->GetType() << "Unregistered\n";
            SummonOnStage = nullptr;
        }
    }
};

int main()
{
    
}