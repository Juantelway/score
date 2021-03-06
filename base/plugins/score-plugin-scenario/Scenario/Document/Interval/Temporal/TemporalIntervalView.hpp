#pragma once
#include <Process/TimeValue.hpp>
#include <score/graphics/TextItem.hpp>
#include <Scenario/Document/Interval/ExecutionState.hpp>
#include <Scenario/Document/Interval/IntervalView.hpp>

#include <score/model/ColorReference.hpp>
#include <score/widgets/MimeData.hpp>

#include <QColor>
#include <QPainter>
#include <QPoint>
#include <QRect>
#include <QString>
#include <QtGlobal>

#include <wobjectdefs.h>
namespace Process
{
class LayerPresenter;
}
namespace Scenario
{
class TemporalIntervalPresenter;
class IntervalDurations;
class SCORE_PLUGIN_SCENARIO_EXPORT TemporalIntervalView final
    : public IntervalView
{
  W_OBJECT(TemporalIntervalView)

public:
  TemporalIntervalView(
      TemporalIntervalPresenter& presenter, QGraphicsItem* parent);
  ~TemporalIntervalView() override;

  QRectF boundingRect() const override;

  const TemporalIntervalPresenter& presenter() const;
  void paint(
      QPainter* painter, const QStyleOptionGraphicsItem* option,
      QWidget* widget) override;

  void enableOverlay(bool b);

  void setLabelColor(score::ColorRef labelColor);
  void setLabel(const QString& label);

  void setExecutionDuration(const TimeVal& progress);

  void updateOverlayPos();
  void setSelected(bool selected);

public:
  void intervalHoverEnter()
      E_SIGNAL(SCORE_PLUGIN_SCENARIO_EXPORT, intervalHoverEnter);
  void intervalHoverLeave()
      E_SIGNAL(SCORE_PLUGIN_SCENARIO_EXPORT, intervalHoverLeave);
  void dropReceived(const QPointF& pos, const QMimeData& arg_2)
      E_SIGNAL(SCORE_PLUGIN_SCENARIO_EXPORT, dropReceived, pos, arg_2);

private:
  void hoverEnterEvent(QGraphicsSceneHoverEvent* h) override;
  void hoverLeaveEvent(QGraphicsSceneHoverEvent* h) override;
  void dragEnterEvent(QGraphicsSceneDragDropEvent* event) override;
  void dragLeaveEvent(QGraphicsSceneDragDropEvent* event) override;
  void dropEvent(QGraphicsSceneDragDropEvent* event) override;

  void updatePaths() final override;
  void updatePlayPaths() final override;
};
}
