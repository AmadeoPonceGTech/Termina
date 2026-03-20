#include <Termina/Scripting/API/ScriptingAPI.hpp>
#include <Termina/World/ComponentRegistry.hpp>

#include "FlyCamComponent.hpp"
#include "ParticleSystem.hpp"
#include "PhysicsTestComponent.hpp"

#include "Entities/Characters/Diane.h"
#include "Entities/Characters/Alex.h"
#include "Entities/Characters/Marcus.h"
#include "Entities/Characters/Edward.h"

#include "Entities/Enemies/Rat.h"
#include "Entities/Enemies/Wolf.h"
#include "Entities/Enemies/Bear.h"

COMPONENT_MODULE_BEGIN()
    REGISTER_COMPONENT(FlyCamComponent, "Fly Cam Component")
    REGISTER_COMPONENT(ParticleSystemComponent, "Particle System")
    REGISTER_COMPONENT(PhysicsTestComponent, "Physics Test")

    //Characters
    REGISTER_COMPONENT(Diane, "Diane")
    REGISTER_COMPONENT(Alex, "Alex")
    REGISTER_COMPONENT(Marcus, "Marcus")
    REGISTER_COMPONENT(Edward, "Edward")

    //Enemies
    REGISTER_COMPONENT(Rat, "Rat")
    REGISTER_COMPONENT(Wolf, "Wolf")
    REGISTER_COMPONENT(Bear, "Bear")

COMPONENT_MODULE_END()