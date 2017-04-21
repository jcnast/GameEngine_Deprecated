#pragma once

namespace Engine
{
	class Camera;

	namespace Rendering
	{
		namespace RenderManagers
		{
			class RenderManager;
			class ShaderManager;
		}
	}

	namespace EngineManagers
	{
		class EngineManager
		{
		private:
			Engine::Camera* Camera;

			// managers
			Rendering::RenderManagers::RenderManager* RenderManager;
			Rendering::RenderManagers::ShaderManager* ShaderManager;
			//CameraManager* CameraManager;

		public:
			EngineManager();
			~EngineManager();

			void SetUpCamera(int width, int height);

			// persistent methods
			virtual void Update(float deltaTime);

			// input methods
			virtual void KeyboardInput(unsigned char key, int x, int y);
			virtual void MouseClick(int button, int state, int x, int y);
			virtual void MouseMove(int x, int y);

			// output methods
			virtual void NotifyBeginFrame();
			virtual void NotifyDisplayFrame();
			virtual void NotifyEndFrame();
			virtual void NotifyReshape(int width, int height, int previousWidth, int previousHeight);
		};
	}
}