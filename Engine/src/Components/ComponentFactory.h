#include "Component.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "ScriptComponent.h"

class ComponentFactory {
public:
    static Component* CopyComponent(const Component* original) {
        if (!original) return nullptr;

        const std::string& type = original->GetType();
        if (type == "Transform") {
            return new TransformComponent(*static_cast<const TransformComponent*>(original));
        } else if (type == "Sprite") {
            return new SpriteComponent(*static_cast<const SpriteComponent*>(original));
        } else if (type == "Physics") {
            return new PhysicsComponent(*static_cast<const PhysicsComponent*>(original));
        } else if (type == "Script") {
            return new IonixEngine::ScriptComponent(*static_cast<const IonixEngine::ScriptComponent*>(original));
        }

        return nullptr;
    }
};