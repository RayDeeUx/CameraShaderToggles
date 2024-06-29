#include <map>
#include <Geode/modify/EffectGameObject.hpp>

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

class $modify(MyEffectGameObject, EffectGameObject) {
	virtual void triggerObject(GJBaseGameLayer* gjbgl, int p1, gd::vector<int> const* p2) {
		int id = this->m_objectID;
		bool existsInCameraMap = cameraIDToSetting.find(id) != cameraIDToSetting.end();
		bool existsInShaderMap = shaderIDToSetting.find(id) != shaderIDToSetting.end();
		if (!existsInCameraMap && !existsInShaderMap) { return; }
		bool settingIsTrue = Mod::get()->getSettingValue<bool>(shaderIDToSetting.find(id)->second) || Mod::get()->getSettingValue<bool>(cameraIDToSetting.find(id)->second);
		if (settingIsTrue) { return; }
		EffectGameObject::triggerObject(gjbgl, p1, p2);
	}
};


/*
// old code for archival purposes

#if defined(__APPLE__) || defined(GEODE_IS_ANDROID)
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(MyPlayLayer, PlayLayer) {
	void addObject(GameObject* p0) {
	        if (Mod::get()->getSettingValue<bool>("enabled")) {
			bool dontSkip = true;
			auto id = p0->m_objectID;
			if (cameraIDToSetting.find(id) != cameraIDToSetting.end() && Mod::get()->getSettingValue<bool>(cameraIDToSetting.find(id)->second)) { dontSkip = false; }
			if (shaderIDToSetting.find(id) != shaderIDToSetting.end() && Mod::get()->getSettingValue<bool>(shaderIDToSetting.find(id)->second)) { dontSkip = false; }
			if (dontSkip) { PlayLayer::addObject(p0); }
		} else {
			PlayLayer::addObject(p0);
		}
	}
};
#else
#include <Geode/modify/EffectGameObject.hpp>

using namespace geode::prelude;

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

std::map<std::string, std::string> shaderFrameToSetting = {
	{ "edit_eShaderBtn_001.png", "disableShader" },
	{ "edit_eSh_ShockWaveBtn_001.png", "disableShockWave" },
	{ "edit_eSh_ShockLineBtn_001.png", "disableShockLine" },
	{ "edit_eSh_GlitchBtn_001.png", "disableGlitch" },
	{ "edit_eSh_ChromaticBtn_001.png", "disableChromatic" },
	{ "edit_eSh_ChromaticGlitchBtn_001.png", "disableChromaticGlitch" },
	{ "edit_eSh_PixelateBtn_001.png", "disablePixelate" },
	{ "edit_eSh_LensCircleBtn_001.png", "disableLensCircle" },
	{ "edit_eSh_RadialBlurBtn_001.png", "disableRadialBlur" },
	{ "edit_eSh_MotionBlurBtn_001.png", "disableMotionBlur" },
	{ "edit_eSh_BulgeBtn_001.png", "disableBulge" },
	{ "edit_eSh_PinchBtn_001.png", "disablePinch" },
	{ "edit_eSh_GrayscaleBtn_001.png", "disableGrayscale" },
	{ "edit_eSh_SepiaBtn_001.png", "disableSepia" },
	{ "edit_eSh_InvertColorBtn_001.png", "disableInvertColor" },
	{ "edit_eSh_HueBtn_001.png", "disableHue" },
	{ "edit_eSh_EditColorBtn_001.png", "disableEditColor" },
	{ "edit_eSh_SplitScreenBtn_001.png", "disableSplitScreen" }
};

class $modify(MyEffectGameObject, EffectGameObject) {
	bool init(char const* p0) {
		if (!EffectGameObject::init(p0)) { return false; }
		if (PlayLayer::get() == nullptr) { return true; }
		if (!Mod::get()->getSettingValue<bool>("enabled")) { return true; }
		if (cameraFrameToSetting.find(p0) != cameraFrameToSetting.end() && Mod::get()->getSettingValue<bool>(cameraFrameToSetting.find(p0)->second)) { return false; }
		if (shaderFrameToSetting.find(p0) != shaderFrameToSetting.end() && Mod::get()->getSettingValue<bool>(shaderFrameToSetting.find(p0)->second)) { return false; }
		return true;
	}
};
#endif

*/