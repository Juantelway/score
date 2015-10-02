#pragma once
#include <QObject>
#include <iscore/plugins/qt_interfaces/PluginControlInterface_QtInterface.hpp>
#include <iscore/plugins/qt_interfaces/PluginRequirements_QtInterface.hpp>

// TODO rename this file
/**
 * @brief The IScoreCohesion class
 *
 * This plug-in is here to set-up things that require multiple plug-ins.
 * For instance, if a feature requires the Scenario, the Curve, and the DeviceExplorer,
 * it should certainly be implemented here.
 *
 */
class iscore_plugin_cohesion:
    public QObject,
    public iscore::PluginControlInterface_QtInterface,
    public iscore::PluginRequirementslInterface_QtInterface
{
        Q_OBJECT
        Q_PLUGIN_METADATA(IID PluginControlInterface_QtInterface_iid)
        Q_INTERFACES(
            iscore::PluginControlInterface_QtInterface
            iscore::PluginRequirementslInterface_QtInterface
        )

    public:
        iscore_plugin_cohesion();
        ~iscore_plugin_cohesion() = default;

        iscore::PluginControlInterface* make_control(
                iscore::Presenter* pres) override;

        QStringList required() const override;
};

