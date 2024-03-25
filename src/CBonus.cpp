#include "CBonus.h"


CBonus::CBonus(int probability, CVisualBlock sprite, int durationOfEffect)
        : m_Probability(probability), m_Sprite(std::move(sprite)), m_DurationOfEffect(durationOfEffect) {}

bool CBonus::has_time_run_out() {
    m_DurationOfEffect--;
    return m_DurationOfEffect > 0;
}

CBonus::~CBonus() = default;

