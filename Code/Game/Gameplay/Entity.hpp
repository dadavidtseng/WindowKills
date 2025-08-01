//----------------------------------------------------------------------------------------------------
// Entity.hpp
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#pragma once

#include "Game/Framework/GameCommon.hpp"
#include "Game/Subsystem/Window/WindowSubsystem.hpp"

//----------------------------------------------------------------------------------------------------
class Entity
{
public:
    explicit Entity(Vec2 const& position, float orientationDegrees, Rgba8 const& color, bool isVisible, bool hasChildWindow);
    virtual  ~Entity();
    EntityID m_entityID           = 0;
    WindowID m_windowID           = 0;
    String   m_name               = "DEFAULT";
    Vec2     m_position           = Vec2::ZERO;
    Vec2     m_velocity           = Vec2::ZERO;
    Rgba8    m_color              = Rgba8::WHITE;
    int      m_health             = 0;
    int      m_coinToDrop         = 0;      // TODO: reconsider the name of this variable
    float    m_orientationDegrees = 0.f;
    float    m_physicRadius       = 0.f;
    float    m_cosmeticRadius     = 0.f;
    float    m_thickness          = 0.f;

    virtual void Update(float deltaSeconds);
    virtual void Render() const = 0;
    virtual void UpdateFromInput(float deltaSeconds) = 0;    // TODO: should entity handle its own input logic? or should the game handle it for him?

    virtual void MarkAsDead();
    virtual void MarkAsGarbage();
    virtual void MarkAsChildWindowInvisible();
    virtual void MarkAsChildWindowVisible();
    virtual void MarkAsEntityInvisible();
    virtual void MarkAsEntityVisible();

    virtual bool IsDead() const;
    virtual bool IsGarbage() const;
    virtual bool IsChildWindowVisible() const;
    virtual bool IsEntityVisible() const;

    void  IncreaseHealth(int amount);
    void  DecreaseHealth(int amount);
    float m_speed = 100.f;

protected:
    bool m_isDead               = false;
    bool m_isGarbage            = false;
    bool m_isChildWindowVisible = true;        // Should we show this entity's child window or not?
    bool m_isEntityVisible      = true;        // Should we render this entity or not?
    bool m_hasChildWindow       = false;       // Should this entity have child window or not?
};
