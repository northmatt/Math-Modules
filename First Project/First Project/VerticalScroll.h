#pragma once

#include "Camera.h"
#include "JSON.h"

class VerticalScroll {
public:
	VerticalScroll();

	//Makes sure that the camera is following the focus
	void Update();

	//Getters
	Camera* GetCam() const;
	Transform* GetFocus() const;
	float GetOffest() const;

	//Setters
	void SetCam(Camera* cam);
	void SetFocus(Transform* focus);
	void SetOffset(float offset);
private:
	Camera* m_cam = nullptr;
	Transform* m_focus = nullptr;

	float m_offset = 5.f;
};

inline void from_json(const nlohmann::json& j, VerticalScroll& verScroll) {
	verScroll.SetOffset(j["OffsetX"]);
}

inline void to_json(nlohmann::json& j, const VerticalScroll& verScroll) {
	j["OffsetX"] = verScroll.GetOffest();
}