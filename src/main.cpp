#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/EffectGameObject.hpp>
#include <map>

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
		if (GameManager::sharedState()->getPlayLayer() == nullptr) { return true; }
		if (!Mod::get()->getSettingValue<bool>("enabled")) { return true; }
		if (cameraFrameToSetting.find(p0) != cameraFrameToSetting.end() && Mod::get()->getSettingValue<bool>(cameraFrameToSetting.find(p0)->second)) { return false; }
		if (shaderFrameToSetting.find(p0) != shaderFrameToSetting.end() && Mod::get()->getSettingValue<bool>(shaderFrameToSetting.find(p0)->second)) { return false; }
		return true;
	}
};