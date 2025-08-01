//----------------------------------------------------------------------------------------------------
// Coin.cpp
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#include "Game/Gameplay/Coin.hpp"

#include "Engine/Core/EngineCommon.hpp"
#include "Engine/Core/NamedStrings.hpp"
#include "Engine/Math/RandomNumberGenerator.hpp"
#include "Game/Gameplay/Game.hpp"

//----------------------------------------------------------------------------------------------------
Coin::Coin(EntityID const entityID,
           Vec2 const&    position,
           float const    orientationDegrees,
           Rgba8 const&   color,
           bool const     isVisible,
           bool const     hasChildWindow)
    : Entity(position, orientationDegrees, color, isVisible, hasChildWindow)
{
    m_entityID       = entityID;
    m_name           = "Coin";
    m_health         = 1;
    m_physicRadius   = g_theRNG->RollRandomFloatInRange(2.f, 10.f);
    m_thickness      = 10.f;
    m_cosmeticRadius = m_physicRadius + m_thickness;

    // g_theEventSystem->SubscribeEventCallbackFunction("OnCollisionEnter", OnCollisionEnter);

    if (m_hasChildWindow)
    {
        g_theWindowSubsystem->CreateChildWindow(m_entityID, m_name, static_cast<int>(m_position.x), static_cast<int>(m_position.y), 200, 200);
    }
}

//----------------------------------------------------------------------------------------------------
Coin::~Coin()
{
    if (m_hasChildWindow)
    {
        g_theWindowSubsystem->RemoveEntityFromMappings(m_entityID);
    }
    // g_theEventSystem->UnsubscribeEventCallbackFunction("OnCollisionEnter", OnCollisionEnter);
}

//----------------------------------------------------------------------------------------------------
void Coin::Update(float const deltaSeconds)
{
    Entity::Update(deltaSeconds);
    if (m_hasChildWindow)
    {
        WindowID    windowID   = g_theWindowSubsystem->FindWindowIDByEntityID(m_entityID);
        WindowData* windowData = g_theWindowSubsystem->GetWindowData(windowID);
        windowData->m_window->SetClientPosition(m_position - windowData->m_window->GetClientDimensions() * 0.5f);
    }
}

//----------------------------------------------------------------------------------------------------
void Coin::Render() const
{
    VertexList_PCU verts;
    AddVertsForDisc2D(verts, m_position, m_physicRadius, m_color);
    g_theRenderer->SetModelConstants();
    g_theRenderer->SetBlendMode(eBlendMode::OPAQUE);
    g_theRenderer->SetRasterizerMode(eRasterizerMode::SOLID_CULL_BACK);
    g_theRenderer->SetSamplerMode(eSamplerMode::BILINEAR_CLAMP);
    g_theRenderer->SetDepthMode(eDepthMode::DISABLED);
    g_theRenderer->BindTexture(nullptr);
    g_theRenderer->BindShader(g_theRenderer->CreateOrGetShaderFromFile("Data/Shaders/Default"));
    g_theRenderer->DrawVertexArray(verts);
}

STATIC bool Coin::OnCollisionEnter(EventArgs& args)
{
    String   entityA   = args.GetValue("entityA", "DEFAULT");
    String   entityB   = args.GetValue("entityB", "DEFAULT");
    EntityID entityBID = args.GetValue("entityBID", -1);
    //Player*  player    = g_theGame->GetPlayer();
    Entity*  entity    = g_theGame->GetEntityByEntityID(entityBID);
    if (entityA == "You" && entityB == "Coin")
    {
        entity->DecreaseHealth(1);
        SoundID const attractBGM = g_theAudio->CreateOrGetSound("Data/Audio/coin.mp3", eAudioSystemSoundDimension::Sound2D);
        g_theAudio->StartSound(attractBGM, false, 1.f, 0.f, 1.f);
    }

    return false;
}

//----------------------------------------------------------------------------------------------------
void Coin::UpdateFromInput(float deltaSeconds)
{
    UNUSED(deltaSeconds)
}
