#include <Geode/modify/CameraTriggerGameObject.hpp>
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
	void triggerObject(GJBaseGameLayer* gjbgl, int p1, gd::vector<int> const* p2) {
		if (!PlayLayer::get() || !Mod::get()->getSettingValue<bool>("enabled")) { return EffectGameObject::triggerObject(gjbgl, p1, p2); }
		int id = this->m_objectID;
		bool cameraMap = cameraIDToSetting.contains(id);
		bool shaderMap = shaderIDToSetting.contains(id);
		if (!cameraMap && !shaderMap) { return EffectGameObject::triggerObject(gjbgl, p1, p2); }
		bool cameraSetting = false;
		if (cameraMap) { cameraSetting = Mod::get()->getSettingValue<bool>(cameraIDToSetting.find(id)->second); }
		bool shaderSetting = false;
		if (shaderMap) { shaderSetting = Mod::get()->getSettingValue<bool>(shaderIDToSetting.find(id)->second); }
		if (!cameraSetting && !shaderSetting) { return EffectGameObject::triggerObject(gjbgl, p1, p2); }
	}
};

class $modify(MyCameraTriggerGameObject, CameraTriggerGameObject) {
	void triggerObject(GJBaseGameLayer* gjbgl, int p1, gd::vector<int> const* p2) {
		if (!PlayLayer::get() || !Mod::get()->getSettingValue<bool>("enabled")) {
			return CameraTriggerGameObject::triggerObject(gjbgl, p1, p2);
		}
		int id = this->m_objectID;
		if (!cameraIDToSetting.contains(id) || !Mod::get()->getSettingValue<bool>(cameraIDToSetting.find(id)->second)) {
			return CameraTriggerGameObject::triggerObject(gjbgl, p1, p2);
		}
	}
};