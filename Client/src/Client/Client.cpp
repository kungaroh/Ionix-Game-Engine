#include <EngineIncludes.h>

namespace ClientApp
{
	class Client :public IonixEngine::Application
	{
	public:
		Client() { }
		~Client() { }
	};

	IonixEngine::Application* CreateApplication()
	{
		return new Client();
	}
}

