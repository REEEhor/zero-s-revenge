#include "CInputRecorder.h"

void CInputRecorder::record_input(char input) {
    if (m_RecordableInputs.find(input) != m_RecordableInputs.end()) {
        m_RecordedInputs.push_back(input);
    }
}

CInputRecorder& CInputRecorder::add_recordable_input(char newInput) {
    m_RecordableInputs.insert(newInput);
    return *this;
}

CInputRecorder::CInputRecorder(std::initializer_list<char> recordableInputs) {
    for (char input : recordableInputs)
        add_recordable_input(input);
}

std::vector<char> CInputRecorder::pop_recorded_inputs() {
    std::vector<char> resultList = m_RecordedInputs;
    m_RecordedInputs.clear();
    return resultList;
}

CInputRecorder::CInputRecorder() = default;

CInputRecorder::~CInputRecorder() = default;

