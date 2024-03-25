#include "CTimeTicks.h"

CTimeTicks::CTimeTicks(int period)
    : m_Period(period), m_CurrentCount(0) {}

bool CTimeTicks::decrement() {
    m_CurrentCount--;
    if (m_CurrentCount <= 0) {
        m_CurrentCount = m_Period;
        return true;
    }
    return false;
}

void CTimeTicks::reset() {
    m_CurrentCount = m_Period;
}

void CTimeTicks::update() {
    m_CurrentCount--;
}

bool CTimeTicks::time_ran_out() const {
    return m_CurrentCount <= 0;
}
