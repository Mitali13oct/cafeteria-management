#pragma once
#include "PreferenceRepository.h"

class PreferenceService {
    PreferenceRepository prefRepo;

public:
    PreferenceService()
        : prefRepo() {}

    void savePreference(const Preference &preference) {
        prefRepo.savePreference(preference);
    }

    Preference loadPreference(int userId) {
        
        return prefRepo.loadPreference(userId);
    }
};
