#include "phyber/logging.h"

int main() {
    PHYBER_LOG_DEBUG("Macro, %i", 1);
    PHYBER_LOG_INFO("Macro, %i", 2);
    PHYBER_LOG_WARNING("Macro, %i", 3);
    PHYBER_LOG_ERROR("Macro, %i", 4);
    PHYBER_LOG_CRITICAL("Macro, %i", 5);
}
