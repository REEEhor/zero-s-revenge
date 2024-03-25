#include "CInputManager.h"

void CInputManager::update() {
    char input;
    // Load all characters from the input and put them
    // into managed recorders.
    while (true) {
        input = CTerminal::get_non_blocking_input();
        if (input == CTerminal::no_input()) break;
        for (auto& recorder: m_ManagedRecorders) {
            recorder->record_input(input);
        }
    }
}

CInputManager::CInputManager(std::initializer_list<std::shared_ptr<CInputRecorder>> recorderList) {
    for (const auto& recorder: recorderList) {
        m_ManagedRecorders.push_back(recorder);
    }
}
