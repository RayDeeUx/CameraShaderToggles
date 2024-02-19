#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/EffectGameObject.hpp>
#include <map>

using namespace geode::prelude;

std::map<int, std::string> cameraIDToSetting = {
	{ 1913, "disableZoom" },
	{ 1914, "disableStatic" },
	{ 1916, "disableOffset" },
	{ 2015, "disableRotate" },
	{ 2016, "disableGuide" },
	{ 2062, "disableEdge" },
	{ 2901, "disableGPOffset" },
	{ 2925, "disableMode" }
};

std::map<std::string, std::string> cameraFrameToSetting = {
	{ "edit_eZoomBtn_001.png", "disableZoom" },
	{ "edit_eStaticBtn_001.png", "disableStatic" },
	{ "edit_eOffsetBtn_001.png", "disableOffset" },
	{ "edit_eCamRotBtn_001.png", "disableRotate" },
	{ "edit_eCamGuideBtn_001.png", "disableGuide" },
	{ "edit_eEdgeBtn_001.png", "disableEdge" },
	{ "edit_eGPOffsetBtn_001.png", "disableGPOffset" },
	{ "edit_eCamModeBtn_001.png", "disableMode" }
};

std::map<int, std::string> shaderIDToSetting = {
	{ 2904, "disableShader" },
	{ 2905, "disableShockWave" },
	{ 2907, "disableShockLine" },
	{ 2909, "disableGlitch" },
	{ 2910, "disableChromatic" },
	{ 2911, "disableChromaticGlitch" },
	{ 2912, "disablePixelate" },
	{ 2913, "disableLensCircle" },
	{ 2914, "disableRadialBlur" },
	{ 2915, "disableMotionBlur" },
	{ 2916, "disableBulge" },
	{ 2917, "disablePinch" },
	{ 2919, "disableGrayscale" },
	{ 2920, "disableSepia" },
	{ 2921, "disableInvertColor" },
	{ 2922, "disableHue" },
	{ 2923, "disableEditColor" },
	{ 2924, "disableSplitScreen" }
};

class $modify(MyPlayLayer, PlayLayer) {
	static void onModify(auto & self)
    {
        self.setHookPriority("PlayLayer::addObject", 901);
    }
	TodoReturn addObject(GameObject* p0) {
        if (Mod::get()->getSettingValue<bool>("enabled")) {
			bool dontSkipThisObject = true;
			auto id = p0->m_objectID;
			if (cameraIDToSetting.find(id) != cameraIDToSetting.end() && Mod::get()->getSettingValue<bool>(cameraIDToSetting.find(id)->second) && !Loader::get()->isModInstalled("absolllute.megahack")) { dontSkipThisObject = false; }
			if (shaderIDToSetting.find(id) != shaderIDToSetting.end() && Mod::get()->getSettingValue<bool>(shaderIDToSetting.find(id)->second)) { dontSkipThisObject = false; }
			if ((!Mod::get()->getSettingValue<bool>("enableOnRated") && this->m_level->m_stars != 0)) { dontSkipThisObject = true; }
			if (dontSkipThisObject) { PlayLayer::addObject(p0); }
		} else PlayLayer::addObject(p0);
	}
};

class $modify(MyEffectGameObject, EffectGameObject) {
	bool init(char const* p0) {
		if (!EffectGameObject::init(p0)) { return false; }
		if (GameManager::sharedState()->getPlayLayer() == nullptr) { return true; }
		if (!Mod::get()->getSettingValue<bool>("enabled")) { return true; }
		if (!Loader::get()->isModInstalled("absolllute.megahack")) { return true; }
		if (cameraFrameToSetting.find(p0) != cameraFrameToSetting.end() && Mod::get()->getSettingValue<bool>(cameraFrameToSetting.find(p0)->second)) { return false; }
		return true;
	}
};