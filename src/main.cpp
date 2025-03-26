#include <ninxout.options_api/include/API.hpp>
#include <Geode/modify/CameraTriggerGameObject.hpp>
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
	void triggerObject(GJBaseGameLayer* gjbgl, int p1, gd::vector<int> const* p2) {
		if (!PlayLayer::get() || !Mod::get()->getSettingValue<bool>("enabled")) { return EffectGameObject::triggerObject(gjbgl, p1, p2); }
		const int id = this->m_objectID;
		const bool cameraMap = cameraIDToSetting.contains(id);
		const bool shaderMap = shaderIDToSetting.contains(id);
		if (!cameraMap && !shaderMap) return EffectGameObject::triggerObject(gjbgl, p1, p2);
		bool cameraSetting = false;
		if (cameraMap) cameraSetting = Mod::get()->getSettingValue<bool>(cameraIDToSetting.find(id)->second);
		bool shaderSetting = false;
		if (shaderMap) shaderSetting = Mod::get()->getSettingValue<bool>(shaderIDToSetting.find(id)->second);
		if (!cameraSetting && !shaderSetting) return EffectGameObject::triggerObject(gjbgl, p1, p2);
	}
};

class $modify(MyCameraTriggerGameObject, CameraTriggerGameObject) {
	void triggerObject(GJBaseGameLayer* gjbgl, int p1, gd::vector<int> const* p2) {
		if (!PlayLayer::get() || !Mod::get()->getSettingValue<bool>("enabled"))
			return CameraTriggerGameObject::triggerObject(gjbgl, p1, p2);
		const int id = this->m_objectID;
		if (!cameraIDToSetting.contains(id) || !Mod::get()->getSettingValue<bool>(cameraIDToSetting.find(id)->second))
			return CameraTriggerGameObject::triggerObject(gjbgl, p1, p2);
	}
};

#define ADD_TOGGLE(displayName, settingsID, detailedDesc)\
	OptionsAPI::addPreLevelSetting<bool>(\
		displayName,\
		settingsID""_spr,\
		[](GJGameLevel*) {\
			const bool origValue = Mod::get()->getSettingValue<bool>(settingsID);\
			Mod::get()->setSettingValue<bool>(settingsID, !origValue);\
		},\
		[](GJGameLevel*) {\
			return Mod::get()->getSettingValue<bool>(settingsID);\
		},\
		"<cl>(From CameraShaderToggles)</c>\n" detailedDesc\
	);

$on_mod(Loaded) {
	ADD_TOGGLE("Disable Shader Setup Shader", "disableShader", "Disable all Shader shader triggers.")
	ADD_TOGGLE("Disable Shock Wave Shader", "disableShockWave", "Disable all Shock Wave shader triggers.")
	ADD_TOGGLE("Disable Shock Line Shader", "disableShockLine", "Disable all Shock Line shader triggers.")
	ADD_TOGGLE("Disable Glitch Shader", "disableGlitch", "Disable all Glitch shader triggers.")
	ADD_TOGGLE("Disable Chromatic Shader", "disableChromatic", "Disable all Chromatic shader triggers.")
	ADD_TOGGLE("Disable Chromatic Glitch Shader", "disableChromaticGlitch", "Disable all Chromatic Glitch shader triggers.")
	ADD_TOGGLE("Disable Pixelate Shader", "disablePixelate", "Disable all Pixelate shader triggers.")
	ADD_TOGGLE("Disable Lens Circle Shader", "disableLensCircle", "Disable all Lens Circle shader triggers.")
	ADD_TOGGLE("Disable Radial Blur Shader", "disableRadialBlur", "Disable all Radial Blur shader triggers.")
	ADD_TOGGLE("Disable Motion Blur Shader", "disableMotionBlur", "Disable all Motion Blur shader triggers.")
	ADD_TOGGLE("Disable Bulge Shader", "disableBulge", "Disable all Bulge shader triggers.")
	ADD_TOGGLE("Disable Pinch Shader", "disablePinch", "Disable all Pinch shader triggers.")
	ADD_TOGGLE("Disable Grayscale Shader", "disableGrayscale", "Disable all Grayscale shader triggers.")
	ADD_TOGGLE("Disable Sepia Shader", "disableSepia", "Disable all Sepia shader triggers.")
	ADD_TOGGLE("Disable Invert Color Shader", "disableInvertColor", "Disable all Invert Color shader triggers.")
	ADD_TOGGLE("Disable Hue Shader", "disableHue", "Disable all Hue shader triggers.")
	ADD_TOGGLE("Disable Edit Color Shader", "disableEditColor", "Disable all Edit Color shader triggers.")
	ADD_TOGGLE("Disable Split Screen Shader", "disableSplitScreen", "Disable all Split Screen shader triggers.")
	ADD_TOGGLE("Disable Zoom Camera", "disableZoom", "Disable all Zoom camera triggers.")
	ADD_TOGGLE("Disable Static Camera", "disableStatic", "Disable all Static camera triggers.")
	ADD_TOGGLE("Disable Offset Camera", "disableOffset", "Disable all Offset camera triggers.")
	ADD_TOGGLE("Disable Rotate Camera", "disableRotate", "Disable all Rotate camera triggers.")
	ADD_TOGGLE("Disable Guide Camera", "disableGuide", "Disable all Guide camera triggers.")
	ADD_TOGGLE("Disable Edge Camera", "disableEdge", "Disable all Edge camera triggers.")
	ADD_TOGGLE("Disable GPOffset Camera", "disableGPOffset", "Disable all GPOffset camera triggers.")
	ADD_TOGGLE("Disable Mode Camera", "disableMode", "Disable all Mode camera triggers.")
}