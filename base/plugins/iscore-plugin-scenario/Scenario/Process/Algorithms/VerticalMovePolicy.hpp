#pragma once

#include <iscore/model/Identifier.hpp>
#include <iscore_plugin_scenario_export.h>

namespace Scenario
{
class IntervalModel;
class EventModel;
class ProcessModel;
class TimeSyncModel;
ISCORE_PLUGIN_SCENARIO_EXPORT void
updateTimeSyncExtent(const Id<TimeSyncModel>& id, Scenario::ProcessModel& s);

// Will call updateTimeSyncExtent
ISCORE_PLUGIN_SCENARIO_EXPORT void
updateEventExtent(const Id<EventModel>& id, Scenario::ProcessModel& s);

// Will call updateEventExtent
ISCORE_PLUGIN_SCENARIO_EXPORT void updateIntervalVerticalPos(
    double y, const Id<IntervalModel>& id, Scenario::ProcessModel& s);
}
