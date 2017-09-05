#pragma once

#include <QPoint>
#include <iscore/model/Identifier.hpp>
#include <iscore/widgets/GraphicsItem.hpp>
#include <iscore_plugin_scenario_export.h>
#include <sys/types.h>

class QGraphicsItem;
class QObject;

namespace Scenario
{
class EventModel;
class TimeSyncModel;
class TimeSyncView;
class TriggerView;

class ISCORE_PLUGIN_SCENARIO_EXPORT TimeSyncPresenter final : public QObject
{
  Q_OBJECT
public:
  TimeSyncPresenter(
      const TimeSyncModel& model, QGraphicsItem* parentview, QObject* parent);
  ~TimeSyncPresenter();

  const Id<TimeSyncModel>& id() const;
  int32_t id_val() const
  {
    return id().val();
  }

  const TimeSyncModel& model() const;
  TimeSyncView* view() const;

  void on_eventAdded(const Id<EventModel>& eventId);

signals:
  void pressed(const QPointF&);
  void moved(const QPointF&);
  void released(const QPointF&);

  void eventAdded(
      const Id<EventModel>& eventId, const Id<TimeSyncModel>& timeSyncId);

private:
  const TimeSyncModel& m_model;
  graphics_item_ptr<TimeSyncView> m_view;
  TriggerView* m_triggerView{};
};
}