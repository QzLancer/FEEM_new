#include <QDebug>
#include "pf_actionhandler.h"
#include "pf_actiondrawcircle.h"
#include "pf_actiondrawpoint.h"
#include "pf_actiondrawline.h"
#include "pf_actiondrawrectangle.h"
#include "pf_actiondrawface.h"
#include "pf_actionselectall.h"
#include "pf_actionselectsingle.h"
#include "pf_document.h"
#include "pf_graphicview.h"

#include "geometry2d.h"

#include <coreplugin/geometrymanager/geometrymanager.h>
#include <coreplugin/geometrymanager/igeometry.h>


PF_ActionHandler::PF_ActionHandler(QObject *parent) : QObject(parent)
{

}

PF_ActionInterface *PF_ActionHandler::getCurrentAction()
{
    if(view){
        return view->getCurrentAction();
    }
    return nullptr;
}

PF_ActionInterface *PF_ActionHandler::setCurrentAction(PF::ActionType typeId)
{
    /** 因为现在的模式是多个cad页面切换，所以，
        绘图的时候，应该在当前的页面绘制，所以，
        在使用之前需要更新一下。**/
    Core::IGeometry* ig = Core::GeometryManager::instance()->currentCAD();
    if(Geometry2D* ig2 = qobject_cast<Geometry2D*>(ig)){
        set_document(ig2->document());
        set_view(ig2->view());
    }else{
        return nullptr;
    }
    PF_ActionInterface* a = nullptr;

    switch (typeId) {
    case PF::ActionDefault:

        break;
    case PF::ActionDrawArc:

        break;
    case PF::ActionDrawCircle:
        a = new PF_ActionDrawCircle(document,view);
        break;
    case PF::ActionDrawLine:
        a = new PF_ActionDrawLine(document,view);
        break;
    case PF::ActionDrawPoint:
        a = new PF_ActionDrawPoint(document,view);
        break;
    case PF::ActionDrawRectangle:
        //a = new PF_ActionDrawRectangle(document,view);
        break;
    case PF::ActionDrawFace:
        a = new PF_ActionDrawFace(document,view);
        break;
    case PF::ActionEditCopy:

        break;
    case PF::ActionEditCut:

        break;
    case PF::ActionEditDelete:

        break;
    case PF::ActionEditKillAllActions:

        break;
    case PF::ActionEditPaste:

        break;
    case PF::ActionEditRedo:

        break;
    case PF::ActionEditUndo:

        break;
    case PF::ActionFileClose:

        break;
    case PF::ActionFileExport:

        break;
    case PF::ActionFileOpen:

        break;
    case PF::ActionFilePrint:

        break;
    case PF::ActionFilePrintPreview:

        break;
    case PF::ActionFileQuit:

        break;
    case PF::ActionFileSave:

        break;
    case PF::ActionFileSaveAs:

        break;
    case PF::ActionFlieNew:

        break;
    case PF::ActionMeshDeleteMesh:

        break;
    case PF::ActionMeshDoMesh:

        break;
    case PF::ActionMeshHideMesh:

        break;
    case PF::ActionMeshShowMesh:

        break;
    case PF::ActionSelectAll:
        a = new PF_ActionSelectAll(document, view, true);
        break;
    case PF::ActionSelectSingle:
//        if(getCurrentAction()->rtti() != PF::ActionSelectSingle) {
            a = new PF_ActionSelectSingle(document, view);
//        }else{
//            a = nullptr;
//        }
        break;
    case PF::ActionDeSelectAll:
        a = new PF_ActionSelectAll(document, view, false);
        break;
    case PF::ActionShowResult:

        break;
    case PF::ActionSolve:

        break;
    case PF::ActionSolveSetting:

        break;
    case PF::ActionViewHideGrid:

        break;
    case PF::ActionViewShowGrid:

        break;
    case PF::ActionViewSetGrid:

        break;
    case PF::ACtionViewZoomAuto:
        this->view->zoomAuto(true,true);
        break;
    case PF::ActionViewZoomIn:
        this->view->zoomIn(1.2);
        break;
    case PF::ActionViewZoomOut:
        this->view->zoomOut(1.2);
        break;
    default:
        qDebug()<<Q_FUNC_INFO<<": No such action found!";
        break;
    }
    if(a){
        view->setCurrentAction(a);
    }
    return a;
}

void PF_ActionHandler::set_view(PF_GraphicView *graphicView)
{
    view = graphicView;
}

void PF_ActionHandler::set_document(PF_Document *_document)
{
    document = _document;
}

void PF_ActionHandler::slotUndo() {
    setCurrentAction(PF::ActionEditUndo);
}

void PF_ActionHandler::slotRedo() {
    setCurrentAction(PF::ActionEditRedo);
}

void PF_ActionHandler::slotCut() {
    setCurrentAction(PF::ActionEditCut);
}

void PF_ActionHandler::slotCopy() {
    setCurrentAction(PF::ActionEditCopy);
}

void PF_ActionHandler::slotPaste() {
    setCurrentAction(PF::ActionEditPaste);
}

void PF_ActionHandler::slotDelete() {
    setCurrentAction(PF::ActionEditDelete);
}

void PF_ActionHandler::slotSelectSingle() {
    setCurrentAction(PF::ActionSelectSingle);
}

void PF_ActionHandler::slotSelectAll() {
    setCurrentAction(PF::ActionSelectAll);
}

void PF_ActionHandler::slotDeSelectAll()
{
    setCurrentAction(PF::ActionDeSelectAll);
}

void PF_ActionHandler::slotDrawPoint() {
    setCurrentAction(PF::ActionDrawPoint);
}

void PF_ActionHandler::slotDrawLine() {
    setCurrentAction(PF::ActionDrawLine);
}

void PF_ActionHandler::slotDrawArc() {
    setCurrentAction(PF::ActionDrawArc);
}

void PF_ActionHandler::slotDrawCircle()
{
    setCurrentAction(PF::ActionDrawCircle);
}

void PF_ActionHandler::slotDrawRectangle()
{
    setCurrentAction(PF::ActionDrawRectangle);
}

void PF_ActionHandler::slotDrawFace()
{
    setCurrentAction(PF::ActionDrawFace);
}

void PF_ActionHandler::slotSetSnaps(const PF_SnapMode &s)
{
    if(view) {
        view->setDefaultSnapMode(s);
    }
}

void PF_ActionHandler::slotSnapFree()
{

}

void PF_ActionHandler::slotSnapGrid()
{

}

void PF_ActionHandler::slotSnapEndpoint()
{

}

void PF_ActionHandler::slotSnapOnEntity()
{

}

void PF_ActionHandler::slotSnapCenter()
{

}

void PF_ActionHandler::slotSnapMiddle()
{

}

void PF_ActionHandler::slotSnapDist()
{

}

void PF_ActionHandler::slotSnapIntersection()
{

}

void PF_ActionHandler::slotSnapIntersectionManual()
{

}

/*!
 \brief 导出Geo格式的几何文件

*/
void PF_ActionHandler::slotExportGeoFile()
{
    document->exportGeofile();
}

/*!
 \brief 导入支持格式的几何文件

 \param fileName
*/
void PF_ActionHandler::slotImportGeoFile(const QString &fileName)
{
    if(fileName.isEmpty()) return;

}

void PF_ActionHandler::slotZoomIn() {
    setCurrentAction(PF::ActionViewZoomIn);
}

void PF_ActionHandler::slotZoomOut() {
    setCurrentAction(PF::ActionViewZoomOut);
}

void PF_ActionHandler::slotZoomAuto() {
    setCurrentAction(PF::ACtionViewZoomAuto);
}

void PF_ActionHandler::slotShowGrid() {
    setCurrentAction(PF::ActionViewShowGrid);
}

void PF_ActionHandler::slotSetGrid() {
    setCurrentAction(PF::ActionViewSetGrid);
}

void PF_ActionHandler::slotDoMesh() {
    document->doMesh();
}

void PF_ActionHandler::slotShowMesh() {
    setCurrentAction(PF::ActionMeshShowMesh);
}

void PF_ActionHandler::slotDelMesh() {
    setCurrentAction(PF::ActionMeshDeleteMesh);
}

void PF_ActionHandler::slotSolve() {
    setCurrentAction(PF::ActionSolve);
}

void PF_ActionHandler::slotShowResult() {
    setCurrentAction(PF::ActionShowResult);
}

void PF_ActionHandler::slotSolveSetting() {
    setCurrentAction(PF::ActionSolveSetting);
}

void PF_ActionHandler::slotShowAbout() {

}
