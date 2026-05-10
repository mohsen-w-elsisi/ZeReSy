#include <cassert>
#include <cstdio>
#include "schedule_exporter.h"
using namespace std;

const string FILE_NAME = "test_schedule_export.png";

const Schedule MOCK_SCHEDULE({
	Course("CS100", "Intro to AI", 3, "Dr. Smith", {{SUN, 8}}, 90, false).selectTime({SUN, 8}),
	Course("MATH101", "Calculus I", 2, "Dr. Johnson", {{MON, 9}}, 60, false).selectTime({MON, 9}),
	Course("PHYS120", "Physics I", 4, "Dr. Lee", {{WED, 12}}, 120, false).selectTime({WED, 12}),
	Course("CHEM120", "Chemistry I", 4, "Dr. Lee", {{THU, 14}}, 120, false).selectTime({THU, 14}),
});

int main() {
    remove(FILE_NAME.c_str());

	SchedualExporter* exporter = new SchedualExporter(MOCK_SCHEDULE, FILE_NAME);
	exporter->exportPNG();
	delete exporter;

	FILE* file = fopen(FILE_NAME.c_str(), "rb");
	assert(file != nullptr);
}