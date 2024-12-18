#include "TestObject.h"
#include <Objects/Object.h>
#include <Components/TransformComponent.h>
#include <Components/SpriteComponent.h>
#include <random>

namespace IonixEngine
{
    void TestObject::TestMethod()
    {
        Object* obj;
        TransformComponent* tr;
        SpriteComponent* sp;

        std::mt19937 rng = std::mt19937(std::random_device()());
        std::uniform_real_distribution<float> dist(0.0f, 1.0f);

        obj = new Object();
        tr = new TransformComponent();
        sp = new SpriteComponent();
        obj->AddComponent(tr);
        float x = 1000 * dist(rng);
        float y = 200 * dist(rng);
        tr->x = x; tr->y = y; tr->sx = 1.0f; tr->sy = 1.0f; tr->angle = 0.0f;
        obj->AddComponent(sp);
        sp->SetTexture("test_texture.png");
        sp->SetWidth(30); sp->SetHeight(30);

        Application::Get().layerObject->GetScene()->AddObject(obj);

    }
}

