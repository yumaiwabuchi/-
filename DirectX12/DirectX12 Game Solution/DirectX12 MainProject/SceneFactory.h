//
// SceneFactory.h
//

#include "TitleScene.h"
#include "OperationScene.h"
#include "RuleOperationScene.h"
#include "TutorialScene.h"
#include "MainScene.h"
#include "WinScene.h"
#include "LossScene.h"

class SceneFactory final {
public:
	static std::unique_ptr<Scene> CreateScene(const NextScene nextScene)
	{
		std::unique_ptr<Scene> scene;
		switch (nextScene) {
		case NextScene::TitleScene:	scene         = std::make_unique<TitleScene>();	break;
		case NextScene::OperationScene:	scene     = std::make_unique<OperationScene>();	break;
		case NextScene::RuleOperationScene:	scene = std::make_unique<RuleOperationScene>();	break;
		case NextScene::TutorialScene:	scene     = std::make_unique<TutorialScene>();	break;
		case NextScene::MainScene:	scene         = std::make_unique<MainScene>();	break;
		case NextScene::WinScene:	scene         = std::make_unique<WinScene>();	break;
		case NextScene::LossScene:	scene         = std::make_unique<LossScene>();	break;
		}
		return scene;
	}
};