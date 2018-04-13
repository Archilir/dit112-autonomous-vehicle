#include <ACS.h>

// Constructor
ParallelParking::ParallelParking()
{

}

void ParallelParking::begin(DriveController& newController) {
  driveController = &newController;
}
void ParallelParking::stop() {

}
