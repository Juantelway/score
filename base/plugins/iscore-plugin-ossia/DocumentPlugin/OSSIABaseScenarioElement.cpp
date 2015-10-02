#include "OSSIABaseScenarioElement.hpp"

#include <Process/ScenarioModel.hpp>

#include <API/Headers/Editor/TimeConstraint.h>
#include <API/Headers/Editor/TimeEvent.h>
#include <API/Headers/Editor/TimeNode.h>

#include "Document/BaseElement/BaseScenario/BaseScenario.hpp"
#include "iscore2OSSIA.hpp"
#include <QTimer>
#include <iscore/document/DocumentInterface.hpp>
#include <core/document/Document.hpp>
#include <core/document/DocumentModel.hpp>
#include "Plugin/DocumentPlugin/DeviceDocumentPlugin.hpp"

static void statusCallback(
        OSSIA::TimeEvent::Status newStatus)
{

}

OSSIABaseScenarioElement::OSSIABaseScenarioElement(
        const BaseScenario *element,
        QObject *parent):
    QObject{parent},
    m_deviceList{iscore::IDocument::documentFromObject(element)->model().pluginModel<DeviceDocumentPlugin>()->list()}
{
    auto main_start_node = OSSIA::TimeNode::create();
    auto main_end_node = OSSIA::TimeNode::create();
    auto main_start_event_it = main_start_node->emplace(main_start_node->timeEvents().begin(), statusCallback);
    auto main_end_event_it = main_end_node->emplace(main_end_node->timeEvents().begin(), statusCallback);
    auto main_start_state = OSSIA::State::create();
    auto main_end_state = OSSIA::State::create();

    (*main_start_event_it)->addState(main_start_state);
    (*main_end_event_it)->addState(main_end_state);

    OSSIA::TimeValue main_duration(iscore::convert::time(element->baseConstraint().duration.defaultDuration()));

    // TODO PlayDuration of base constraint.
    // TODO PlayDuration of FullView
    auto main_constraint = OSSIA::TimeConstraint::create(
                               [] (const OSSIA::TimeValue&, const OSSIA::TimeValue&,
                std::shared_ptr<OSSIA::StateElement> element) {
        element->launch();
    }, *main_start_event_it, *main_end_event_it, main_duration);

    m_ossia_startTimeNode = new OSSIATimeNodeElement{main_start_node, element->startTimeNode(),  m_deviceList, this};
    m_ossia_endTimeNode = new OSSIATimeNodeElement{main_end_node, element->endTimeNode(), m_deviceList, this};

    m_ossia_startEvent = new OSSIAEventElement{*main_start_event_it, element->startEvent(), m_deviceList, this};
    m_ossia_endEvent = new OSSIAEventElement{*main_end_event_it, element->endEvent(), m_deviceList, this};

    m_ossia_startState = new OSSIAStateElement{element->startState(), main_start_state, m_deviceList, this};
    m_ossia_endState = new OSSIAStateElement{element->endState(), main_end_state, m_deviceList, this};

    m_ossia_constraint = new OSSIAConstraintElement{main_constraint, element->baseConstraint(), this};
}

OSSIAConstraintElement *OSSIABaseScenarioElement::baseConstraint() const
{
    return m_ossia_constraint;
}

OSSIATimeNodeElement *OSSIABaseScenarioElement::startTimeNode() const
{
    return m_ossia_startTimeNode;
}

OSSIATimeNodeElement *OSSIABaseScenarioElement::endTimeNode() const
{
    return m_ossia_endTimeNode;
}

OSSIAEventElement *OSSIABaseScenarioElement::startEvent() const
{
    return m_ossia_startEvent;
}

OSSIAEventElement *OSSIABaseScenarioElement::endEvent() const
{
    return m_ossia_endEvent;
}

OSSIAStateElement *OSSIABaseScenarioElement::startState() const
{
    return m_ossia_startState;
}

OSSIAStateElement *OSSIABaseScenarioElement::endState() const
{
    return m_ossia_endState;
}
