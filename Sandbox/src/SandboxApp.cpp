#include <Umbra.h>

class Sandbox : public Umbra::Application {
public:
	Sandbox() {}
	~Sandbox() {}
};

Umbra::Application* Umbra::CreateApplication() {
	return new Sandbox();
}