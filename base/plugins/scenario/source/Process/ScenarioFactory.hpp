#pragma once
#include "ProcessInterface/ProcessFactoryInterface.hpp"

class ScenarioFactory : public ProcessFactoryInterface
{
    public:
        virtual QString name() const override;

        virtual ProcessSharedModelInterface* makeModel(
                const TimeValue& duration,
                const id_type<ProcessSharedModelInterface>& id,
                QObject* parent) override;

        virtual ProcessSharedModelInterface* loadModel(
                const VisitorVariant&,
                QObject* parent) override;

        virtual ProcessPresenterInterface* makePresenter(
                const ProcessViewModelInterface&,
                ProcessViewInterface*,
                QObject* parent) override;

        virtual ProcessViewInterface* makeView(
                const ProcessViewModelInterface& viewmodel,
                QObject* parent) override;

};
