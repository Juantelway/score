#pragma once
#include <Editor/TimeEvent.h>
#include <boost/optional/optional.hpp>
#include <iscore/tools/IdentifiedObjectMap.hpp>
#include <iscore/tools/SettableIdentifier.hpp>
#include <map>
#include <memory>

#include "ProcessElement.hpp"
#include <Scenario/Document/Constraint/ConstraintModel.hpp>

namespace Device
{
class DeviceList;
}
namespace Process { class ProcessModel; }
class QObject;
namespace OSSIA {
class TimeProcess;
}  // namespace OSSIA
namespace RecreateOnPlay {
class EventElement;
class StateElement;
class TimeNodeElement;
}  // namespace RecreateOnPlay
namespace Scenario {
class ScenarioModel;
class EventModel;
class StateModel;
class TimeNodeModel;
}  // namespace Scenario

namespace OSSIA
{
    class Scenario;
}

namespace RecreateOnPlay
{
class ConstraintElement;

// TODO see if this can be used for the base scenario model too.
class ScenarioElement final : public ProcessComponent
{
    public:
        ScenarioElement(
                ConstraintElement& cst,
                Scenario::ScenarioModel& proc,
                const Context& ctx,
                const Id<iscore::Component>& id,
                QObject* parent);

        const auto& states() const
        { return m_ossia_states; }
        const auto& constraints() const
        { return m_ossia_constraints; }
        const auto& events() const
        { return m_ossia_timeevents; }
        const auto& timeNodes() const
        { return m_ossia_timenodes; }

        void stop() override;

    private:
        void on_constraintCreated(const Scenario::ConstraintModel&);
        void on_stateCreated(const Scenario::StateModel&);
        void on_eventCreated(const Scenario::EventModel&);
        void on_timeNodeCreated(const Scenario::TimeNodeModel&);

        void startConstraintExecution(const Id<Scenario::ConstraintModel>&);
        void stopConstraintExecution(const Id<Scenario::ConstraintModel>&);

        void eventCallback(
                EventElement& ev,
                OSSIA::TimeEvent::Status newStatus);

    private:
        const Key &key() const override;
        // TODO use IdContainer
        std::map<Id<Scenario::ConstraintModel>, ConstraintElement*> m_ossia_constraints;
        std::map<Id<Scenario::StateModel>, StateElement*> m_ossia_states;
        std::map<Id<Scenario::TimeNodeModel>, TimeNodeElement*> m_ossia_timenodes;
        std::map<Id<Scenario::EventModel>, EventElement*> m_ossia_timeevents;

        IdContainer<Scenario::ConstraintModel> m_executingConstraints;

        const Context& m_ctx;
};


class ScenarioComponentFactory final :
        public ProcessComponentFactory
{
    public:
        virtual ~ScenarioComponentFactory();
        virtual ProcessComponent* make(
                ConstraintElement& cst,
                Process::ProcessModel& proc,
                const Context& ctx,
                const Id<iscore::Component>& id,
                QObject* parent) const override;

        const ConcreteFactoryKey& concreteFactoryKey() const override;

        bool matches(
                Process::ProcessModel&,
                const DocumentPlugin&,
                const iscore::DocumentContext &) const override;
};

}
