// This is an open source non-commercial project. Dear PVS-Studio, please check
// it. PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <score/document/DocumentContext.hpp>
#include <score/plugins/panel/PanelDelegate.hpp>
#include <score/selection/Selection.hpp>
#include <score/selection/SelectionStack.hpp>
#include <score/tools/Todo.hpp>

#include <core/document/Document.hpp>
#include <core/document/DocumentBackupManager.hpp>
#include <core/document/DocumentModel.hpp>
#include <core/document/DocumentPresenter.hpp>
#include <core/document/DocumentView.hpp>

#include <QObject>

#include <algorithm>
#include <iterator>
#include <vector>

class QWidget;
class Selection;
#include <score/model/Identifier.hpp>

#include <wobjectimpl.h>
W_OBJECT_IMPL(score::Document)
namespace score
{
DocumentContext::DocumentContext(Document& d)
    : app{score::GUIAppContext()}
    , document{d}
    , commandStack{d.m_commandStack}
    , selectionStack{d.selectionStack()}
    , objectLocker{d.locker()}
    , focus{d.focusManager()}
    , updateTimer{d.m_documentUpdateTimer}
    , coarseUpdateTimer{d.m_documentCoarseUpdateTimer}
    , execTimer{d.m_execTimer}
    , dispatcher{d.m_disp}
{
}

const std::vector<DocumentPlugin*>& DocumentContext::pluginModels() const
{
  return document.model().pluginModels();
}

Document::Document(
    const QString& name, const Id<DocumentModel>& id,
    DocumentDelegateFactory& factory, QWidget* parentview, QObject* parent)
    : QObject{parent}
    , m_metadata{name}
    , m_commandStack{*this}
    , m_objectLocker{this}
    , m_backupMgr{new DocumentBackupManager{*this}}
    , m_context{*this}
    , m_virgin{true}
{
  /// Construction of the document model

  // Note : we have to separate allocation
  // because the model delegates init might call IDocument::path()
  // which requires the pointer to m_model to be intialized.
  std::allocator<DocumentModel> allocator;
  m_model = allocator.allocate(1);
  allocator.construct(m_model, id, m_context, factory, this);

  // TODO don't build them / destroy them if !application.gui.
  if (parentview)
  {
    m_view = new DocumentView{factory, *this, parentview};
    m_presenter
        = new DocumentPresenter{m_context, factory, *m_model, *m_view, this};
  }

  init();

  //    connect(m_model, &DocumentModel::fileNameChanged,
  //            this, &Document::fileNameChanged);
}

void Document::init()
{
  con(m_selectionStack, &SelectionStack::currentSelectionChanged, this,
      [&](const Selection& s) {
        Selection filtered = s;
        filtered.removeAll(nullptr);
        for (auto& panel : m_context.app.panels())
        {
          panel.setNewSelection(filtered);
        }
        m_presenter->setNewSelection(filtered);
      });

  m_documentUpdateTimer.setInterval(16);
  m_documentUpdateTimer.start();

  m_documentCoarseUpdateTimer.setInterval(64);
  m_documentCoarseUpdateTimer.start();

  m_execTimer.setInterval(32);
}

void Document::setBackupMgr(DocumentBackupManager* backupMgr)
{
  m_backupMgr = backupMgr;
}

Document::~Document()
{
  // We need a custom destructor because
  // for the sake of simplicity, we want the presenter
  // to be deleted before the model.
  // (Else we would have to fine-grain the deletion of the selection stack).

  m_commandStack.blockSignals(true);
  m_selectionStack.blockSignals(true);
  m_focus.blockSignals(true);
  delete m_presenter;
  delete m_view;
  delete m_model;
}

const Id<DocumentModel>& Document::id() const
{
  return m_model->id();
}
}
