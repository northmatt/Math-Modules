#include "HealthBar.h"
#include <iostream>
#include <string>

using std::cout;
using std::to_string;
using std::endl;

HealthBar::HealthBar()
{
}

HealthBar::HealthBar(float health)
{
	m_health = health;
}

HealthBar::~HealthBar()
{
}

void HealthBar::DisplayHealth()
{
	cout << "Health: " << to_string(m_health * 100.f) << "%" << endl;
}

float HealthBar::GetHealth() const
{
	return m_health;
}

void HealthBar::SetHealth(float health)
{
	m_health = health;
}
