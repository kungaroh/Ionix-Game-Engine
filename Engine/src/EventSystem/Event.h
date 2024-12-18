#pragma once
#include "Architecture/Macros.h"
#include <string>
#include <functional>

namespace IonixEngine
{
    enum class IonixEventType : int;

    class IonixEvent {
        friend class EventDispatcher;

    public:
        bool m_Handled = false;
        virtual IonixEventType GetEventType() const = 0;

    protected:
        inline bool IsHandled() const { return m_Handled; }
    };

    class EventDispatcher {
    public:
        EventDispatcher(IonixEvent& event)
            : m_Event(event)
        { }

        template<typename T>
        void Dispatch(std::function<bool(T&)> handler) {
            if (m_Event.IsHandled()) { return; }

            if (m_Event.GetEventType() == T::GetStaticType())
                m_Event.m_Handled = handler(*(T*)&m_Event);
        }

    private:
        IonixEvent& m_Event;
    };
}


