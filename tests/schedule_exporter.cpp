#include <cassert>
#include <cstdio>
#include "schedule_exporter.h"
using namespace std;

const string FILE_NAME = "test_schedule_export.png";

const Schedule MOCK_SCHEDULE({
	Course("CS100", "Intro to AI", 3, "Dr. Smith", {{SUN, 9}}, 90, false).selectTime({SUN, 9}),
	Course("MATH101", "Calculus I", 2, "Dr. Johnson", {{MON, 11}}, 90, false).selectTime({MON, 11}),
	Course("PHYS120", "Physics I", 4, "Dr. Lee", {{WED, 14}}, 90, false).selectTime({WED, 14}),
});

int main() {
    remove(FILE_NAME.c_str());

	SchedualExporter* exporter = new SchedualExporter(MOCK_SCHEDULE, FILE_NAME);
	exporter->exportPNG();
	delete exporter;

	FILE* file = fopen(FILE_NAME.c_str(), "rb");
	assert(file != nullptr);
}