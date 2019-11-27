#pragma once

#include "JSON.h"

class HealthBar {
public:
	//creates HealthBar
	HealthBar();
	//creates Healthbar and sets health to amount given
	HealthBar(float health);
	//destroys Healthbar
	~HealthBar();

	void DisplayHealth();
	//Getters
	float GetHealth() const;
	//Setters
	void SetHealth(float health);
private:
	float m_health = 1.f;
};

inline void to_json(nlohmann::json& j, const HealthBar& bar) {
	j["Health"] = bar.GetHealth();
}

inline void from_json(const nlohmann::json& j, HealthBar& bar) {
	bar.SetHealth(j["Health"]);
}