#pragma once
#include <Scenario/Application/ScenarioActions.hpp>
#include <Scenario/Process/ScenarioGlobalCommandManager.hpp>
#include <Scenario/Document/ScenarioDocument/ScenarioDocumentModel.hpp>
#include <score/model/ObjectRemover.hpp>
#include <score/document/DocumentInterface.hpp>
#include <Dataflow/Commands/EditConnection.hpp>
#include <Scenario/Commands/Interval/RemoveProcessFromInterval.hpp>
#include <Scenario/Commands/State/RemoveStateProcess.hpp>
namespace Scenario
{
class ScenarioRemover final
    : public score::ObjectRemover
{
  SCORE_CONCRETE("90265073-0aae-4628-834a-f44048664476")

  bool remove(const Selection& s, const score::DocumentContext& ctx) override
  {
    if(s.size() == 1)
    {
      CommandDispatcher<> d{ctx.commandStack};

      auto first = s.begin()->data();
      if(auto c = qobject_cast<const Process::Cable*>(first))
      {
        auto& doc = score::IDocument::get<ScenarioDocumentModel>(ctx.document);
        d.submit<Dataflow::RemoveCable>(doc, *c);
        return true;
      }
      else if(auto proc = qobject_cast<const Process::ProcessModel*>(first))
      {
        using namespace Command;
        auto p = proc->parent();
        if(auto itv = qobject_cast<IntervalModel*>(p))
        {
          d.submit<RemoveProcessFromInterval>(*itv, proc->id());
        }
        else if(auto st = qobject_cast<StateModel*>(p))
        {
          d.submit<RemoveStateProcess>(*st, proc->id());
        }
      }
    }

    if (auto sm = focusedScenarioModel(ctx))
    {
      Scenario::removeSelection(*sm, ctx);
      return true;
    }

    auto si = focusedScenarioInterface(ctx);
    if (si && !selectedElements(si->getStates()).empty())
    {
      Scenario::clearContentFromSelection(
          selectedElements(si->getIntervals()),
          selectedElements(si->getStates()), ctx);
      return true;
    }

    return false;
  }
};

}
