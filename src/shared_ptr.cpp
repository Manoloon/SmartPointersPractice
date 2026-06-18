#include <memory>
#include <iostream>

class Buff;

class Player
{
    public:
        std::shared_ptr<Buff> ActiveBuff;
        ~Player()
        {
            std::cout << "Player Destroy\n";
        }
};

class Buff
{
public:
   // std::shared_ptr<Player> Owner;
   std::weak_ptr<Player> Owner;
   ~Buff()
   {
        std::cout << "Buff destroy\n";
   }
};

int main()
{
    auto m_Player = std::make_shared<Player>();
    auto m_Buff = std::make_shared<Buff>();
    // Aqui tenemos una dependencia ciclica.
    // si m_player se destruye , y luego m_buff se destruye, el contador de shared_ptr todavia quedaria en uno cada uno. 
    // Memory leak.
    // se corrige con weak_ptr
    // Player -> shared_ptr -> Buff
    // Buff -> weak_ptr -> Player
    m_Player->ActiveBuff = m_Buff;
    m_Buff->Owner = m_Player;
     
    if(auto Owner = m_Buff->Owner.lock())
    {
        std::cout << "Player is still alive\n";
    }
    else
    {
        std::cout << "Player is Dead\n";
    }
    m_Player.reset();
    m_Buff.reset();
}