#pragma once
#include <iscore/serialization/VisitorInterface.hpp>
class QObject;
class ProcessViewModelInterface;
class ProcessSharedModelInterface;
class ConstraintModel;


template<typename T>
ProcessViewModelInterface* createProcessViewModel(Deserializer<T>& deserializer,
        const ConstraintModel& constraint,
        QObject* parent);
