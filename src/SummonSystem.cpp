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
#include <iostream>

class Player
{
};

class Summon
{
};

class SummonTracker
{
};