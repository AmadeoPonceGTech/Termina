#include <Termina/Scripting/API/ScriptingAPI.hpp>
#include <Termina/World/ComponentRegistry.hpp>

#include "FlyCamComponent.hpp"
#include "ParticleSystem.hpp"
#include "PhysicsTestComponent.hpp"

#include "Entities/Characters/Diane.h"

#include "Entities/Enemies/Rat.h"
#include "Game.h"
COMPONENT_MODULE_BEGIN()
    REGISTER_COMPONENT(FlyCamComponent, "Fly Cam Component")
    REGISTER_COMPONENT(ParticleSystemComponent, "Particle System")
    REGISTER_COMPONENT(PhysicsTestComponent, "Physics Test")

REGISTER_COMPONENT(Game, "Game")
    //Characters
    REGISTER_COMPONENT(Diane, "Diane")

    //Enemies
    REGISTER_COMPONENT(Rat, "Rat")

COMPONENT_MODULE_END()
