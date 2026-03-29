#include <Termina/Scripting/API/ScriptingAPI.hpp>
#include <Termina/World/ComponentRegistry.hpp>
#include <ImGui/imgui.h>

#include "FlyCamComponent.hpp"
#include "ParticleSystem.hpp"
#include "PhysicsTestComponent.hpp"

#include "Game.h"
#include "Entities/Characters/Tank/Diane.h"
#include "Entities/Characters/Close DPS/Alex.h"
#include "Entities/Characters/Support/Marcus.h"
#include "Entities/Characters/Range DPS/Edward.h"
#include "Entities/Characters/Close DPS/Penelope.h"
#include "Entities/Characters/Support/Claire.h"
#include "Entities/Characters/Range DPS/Brutus.h"
#include "Entities/Characters/Tank/Emilie.h"

#include "Entities/Enemies/Rat.h"
#include "Entities/Enemies/Wolf.h"
#include "Entities/Enemies/Bear.h"
#include "Entities/Enemies/Hawk.h"

COMPONENT_MODULE_BEGIN()
    REGISTER_COMPONENT(FlyCamComponent, "Fly Cam Component")
    REGISTER_COMPONENT(ParticleSystemComponent, "Particle System")
    REGISTER_COMPONENT(PhysicsTestComponent, "Physics Test")
    REGISTER_COMPONENT(Game, "Game")
    //Characters
    REGISTER_COMPONENT(Diane, "Diane")
    REGISTER_COMPONENT(Alex, "Alex")
    REGISTER_COMPONENT(Marcus, "Marcus")
    REGISTER_COMPONENT(Edward, "Edward")
    REGISTER_COMPONENT(Penelope, "Penelope")
    REGISTER_COMPONENT(Claire, "Claire")
    REGISTER_COMPONENT(Brutus, "Brutus")
    REGISTER_COMPONENT(Emilie, "Emilie")

    //Enemies
    REGISTER_COMPONENT(Rat, "Rat")
    REGISTER_COMPONENT(Wolf, "Wolf")
    REGISTER_COMPONENT(Bear, "Bear")
    REGISTER_COMPONENT(Hawk, "Hawk")

COMPONENT_MODULE_END()

TERMINA_DLL_EXPORT void SetImGuiContext(void* ctx, void* allocFunc, void* freeFunc, void* userData)
{
    ImGui::SetCurrentContext(static_cast<ImGuiContext*>(ctx));
    ImGui::SetAllocatorFunctions(
        reinterpret_cast<ImGuiMemAllocFunc>(allocFunc),
        reinterpret_cast<ImGuiMemFreeFunc>(freeFunc),
        userData);
}
