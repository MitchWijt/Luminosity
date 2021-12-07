#include <iostream>

#include "Scene/Scene.hpp"
#include "Application.hpp"


int main() {
	Application application = Application("Luminosity");
	
	Scene scene = Scene(application);
	scene.onUpdateRuntime();

	return -1;
}

