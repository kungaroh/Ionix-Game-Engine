#pragma once
#include "Eventsystem/Event.h"
#include "Logging/Console.h"
#include "Input/Input.h"
#include "Scripting/Scripting.h"

namespace IonixEngine
{
    enum class IonixEventType
    {
        None = 0,
        WindowClosed,
        KeyPressed,
        MouseButtonPressed,
        MouseButtonReleased, 
        PhysicsCollisionEnter,
        PhysicsCollisionExit,
        PhysicsTriggerEnter,
        PhysicsTriggerExit,
        UIButtonDown,
        UIButtonUp,
        TileMapDataLoaded
    };

#define IONIX_EVENT_CLASS_TYPE(type) \
        static IonixEventType GetStaticType() { return IonixEventType::type; } \
        virtual IonixEventType GetEventType() const override { return GetStaticType(); }

    // @@@@@@@@ E D I T O R    E V E N T S @@@@@@@@ //

    class Event_WindowClosed : public IonixEvent
    {
    public:
        IONIX_EVENT_CLASS_TYPE(WindowClosed)
    };

    // @@@@@@@@ K E Y B O A R D    E V E N T S @@@@@@@@ //

    class Event_KeyPressed : public IonixEvent
    {
    public:
        IONIX_EVENT_CLASS_TYPE(KeyPressed)

            Event_KeyPressed(int keycode)
            : m_KeyCode(keycode) {}

        inline int GetKeyCode() const { return m_KeyCode; }

    private:
        int m_KeyCode;
    };

    // @@@@@@@@ M O U S E    E V E N T S @@@@@@@@ //

    class Event_MouseButtonPressed : public IonixEvent
    {
    public:
        IONIX_EVENT_CLASS_TYPE(MouseButtonPressed)

            Event_MouseButtonPressed(Mousecode button)
            : m_Button(button) {}

        inline Mousecode GetButton() const { return m_Button; }

    private:
        Mousecode m_Button;
    };

    class Event_MouseButtonReleased : public IonixEvent
    {
    public:
        IONIX_EVENT_CLASS_TYPE(MouseButtonReleased)

            Event_MouseButtonReleased(Mousecode button)
            : m_Button(button) {}

        inline Mousecode GetButton() const { return m_Button; }

    private:
        Mousecode m_Button;
    };

    // @@@@@@@@ P H Y S I C S    E V E N T S @@@@@@@@ //

    class Event_OnCollisionEnter : public IonixEvent
    {
    public:
        IONIX_EVENT_CLASS_TYPE(PhysicsCollisionEnter)

            Event_OnCollisionEnter(int id1, int id2)
            : objId1(id1), objId2(id2) {}

        int GetObj1Id() const { return objId1; }
        int GetObj2Id() const { return objId2; }

    private:
        int objId1;
        int objId2;
    };

    class Event_OnCollisionExit : public IonixEvent
    {
    public:
        IONIX_EVENT_CLASS_TYPE(PhysicsCollisionExit)

            Event_OnCollisionExit(int id1, int id2)
            : objId1(id1), objId2(id2) {}

        int GetObj1Id() const { return objId1; }
        int GetObj2Id() const { return objId2; }

    private:
        int objId1;
        int objId2;
    };
    
    class Event_OnTriggerEnter : public IonixEvent 
    {
    public: 
        IONIX_EVENT_CLASS_TYPE(PhysicsTriggerEnter)

        Event_OnTriggerEnter(int id1, int id2) : objId1(id1), objId2(id2) {}

        int GetObj1Id() const { return objId1; }
        int GetObj2Id() const { return objId2; }

    private:
        int objId1;
        int objId2;

    };
    class Event_OnTriggerExit : public IonixEvent 
    {
    public:
        IONIX_EVENT_CLASS_TYPE(PhysicsTriggerExit)

        Event_OnTriggerExit(int id1, int id2) : objId1(id1), objId2(id2) {}

        int GetObj1Id() const { return objId1; }
        int GetObj2Id() const { return objId2; }

    private:
        int objId1;
        int objId2;
    };

    // @@@@@@@@ U I     E V E N T S @@@@@@@@ //

    class Event_OnUIButtonDown : public IonixEvent
    {
        IONIX_EVENT_CLASS_TYPE(UIButtonDown)
    public:
        Event_OnUIButtonDown(Keycode key) : m_key(key) {}

        inline Keycode GetKeyCode() const { return m_key; }

    private:
        Keycode m_key;
    };

    class Event_OnUIButtonUp : public IonixEvent
    {
        IONIX_EVENT_CLASS_TYPE(UIButtonUp)
    public:
        Event_OnUIButtonUp(Keycode key) : m_key(key) {}

        inline Keycode GetKeyCode() const { return m_key; }

    private:
        Keycode m_key;
    };

    // @@@@@@@@ E D I T        E V E N T S @@@@@@@@ //

    class Event_OnTileMapDataLoaded : public IonixEvent
    {
    public:
        IONIX_EVENT_CLASS_TYPE(TileMapDataLoaded)
        Event_OnTileMapDataLoaded(const TiledData data) : tileData(data) {}

        inline TiledData GetTileMapData() const { return tileData; }

    private:
        TiledData tileData;
    };
}

    



