#include <QtTest/QtTest>
#include <Document/Constraint/ConstraintModel.hpp>
#include <Document/Event/EventModel.hpp>
#include <Document/Constraint/Box/BoxModel.hpp>
#include <Process/ScenarioModel.hpp>
#include "ProcessInterface/ProcessList.hpp"

#include "Commands/Constraint/AddProcessToConstraint.hpp"
#include "Commands/Constraint/RemoveProcessFromConstraint.hpp"
#include "Commands/Constraint/AddBoxToConstraint.hpp"
#include <Process/ScenarioFactory.hpp>

using namespace iscore;
using namespace Scenario::Command;


class AddProcessToConstraintTest: public QObject
{
        Q_OBJECT

    private slots:
        void CreateCommandTest()
        {
            NamedObject* obj = new NamedObject {"obj", qApp};
            ProcessList* plist = new ProcessList {obj};
            plist->registerProcess(new ScenarioFactory);

            ConstraintModel* cstrModel  = new ConstraintModel {id_type<ConstraintModel>{1}, id_type<AbstractConstraintViewModel>{0}, qApp};

            //int_model->createBox(id_type<BoxModel> {421});  // TODO use command instead.
            AddBoxToConstraint boxCmd(
                        ObjectPath { {"ConstraintModel", {1}} });
            boxCmd.redo();

            AddProcessToConstraint cmd(
            {
                {"ConstraintModel", {1}}
            }, "Scenario");

            cmd.redo();
            QCOMPARE((int) cstrModel->processes().size(), 1 );
            cmd.undo();
            QCOMPARE((int) cstrModel->processes().size(), 0 );
            cmd.redo();
            QCOMPARE((int) cstrModel->processes().size(), 1 );

            // Delete them else they stay in qApp !
            delete cstrModel;
            delete obj;
        }

};

QTEST_MAIN(AddProcessToConstraintTest)
#include "AddProcessToConstraintTest.moc"

