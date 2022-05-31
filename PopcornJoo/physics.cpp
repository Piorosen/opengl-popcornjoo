#include "physics.h"

std::unique_ptr<phy::physicsEngine> phy::physicsEngine::shared = std::make_unique<phy::physicsEngine>();
