#include "pf_entitycontainer.h"
#include "pf_graphicview.h"
#include "pf_line.h"
#include "pf_point.h"
#include "pf_face.h"
#include "gmsh.h"

#include "PolygonDetector.h"

#include <output/outputpluginplugin.h>

#include <QDebug>
#include <QFileInfo>

using namespace PolygonDetection;

const QLatin1String PointKey("Points");
const QLatin1String LineKey("Lines");
const QLatin1String FaceKey("Faces");

/** ///////////////////////////////////////////
导入dxf文件所需要的一些函数
**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <set>

#define DEG2RAD    3.14159265359/180.
#define BUFSIZE    2048
#define GEOLINE    1
#define GEOCIRCLE  2
#define GEOTRI     3
#define GEOQUAD    4

static FILE *infile, *outfile;
static char inname[80], /*outname[80],*/ curobj[80], linbuf[BUFSIZE];
static long primitives = 0L, degenerates = 0L;
static int groupcode, curcolor, ints[10], nump = 1, numc = 1;
static int cpt_vert_node = 1, num_vert_node[1024];
static double curthick, xcoords[10], ycoords[10], zcoords[10], floats[10], angles[10];
static double max_x, max_y, max_z, min_x, min_y, min_z;
static double THETOL=1e-20, THEROT = 0., THETRANSX = 0., THETRANSY = 0.;

class Point
{
public:
    int num;
    double x, y, z;
    void write() const
    {
        double xx = x;
        double yy = y;
        xx = cos(-THEROT * DEG2RAD) * x + sin(-THEROT * DEG2RAD) * y;
        yy = -sin(-THEROT * DEG2RAD) * x + cos(-THEROT * DEG2RAD) * y;
        xx += THETRANSX;
        yy += THETRANSY;
        fprintf(outfile, "Point (%d) = {%g *u, %g *u, %g *u, lc} ;\n",
                num, xx, yy, z);
    }
};

class PointLessThanLexicographic{
public:
    bool operator()(const Point &v1, const Point &v2) const
    {
        if(v1.x - v2.x >  THETOL) return true;
        if(v1.x - v2.x < -THETOL) return false;
        if(v1.y - v2.y >  THETOL) return true;
        if(v1.y - v2.y < -THETOL) return false;
        if(v1.z - v2.z >  THETOL) return true;
        return false;
    }
};

class Curve
{
public:
    int num, type, a, b, c;
    void write() const
    {
        switch (type) {
        case GEOLINE:
            fprintf(outfile, "Line (%d) = {%d, %d} ;\n", num, a, b);
            break;
        case GEOCIRCLE:
            fprintf(outfile, "Circle (%d) = {%d, %d, %d} ;\n",
                    num, a, b, c);
            break;
        }
    }
};

class CurveLessThan{
public:
    bool operator()(const Curve &c1, const Curve &c2) const
    {
        if(c1.a < c2.a)
            return true;
        else if(c1.a == c2.a){
            if(c1.b < c2.b)
                return true;
            else
                return false;
        }
        return false;
    }
};

static std::set<Point, PointLessThanLexicographic> Point_T;
static std::set<Curve, CurveLessThan> Curve_T;

int addpoint(Point &p)
{
    std::set<Point>::iterator it = Point_T.find(p);
    if(it != Point_T.end())
        return it->num;
    p.num = nump++;
    Point_T.insert(p);
    return p.num;
}

int addcurve(Curve &c)
{
    std::set<Curve>::iterator it = Curve_T.find(c);
    if(it != Curve_T.end())
        return it->num;
    c.num = numc++;
    Curve_T.insert(c);
    return c.num;
}

int checkdegen(int a, int b, int c)
{       /* check for degenerate triangle structure */
    if((xcoords[a] == xcoords[b] &&
        ycoords[a] == ycoords[b] &&
        zcoords[a] == zcoords[b]) ||
            (xcoords[b] == xcoords[c] &&
             ycoords[b] == ycoords[c] &&
             zcoords[b] == zcoords[c]) ||
            (xcoords[a] == xcoords[c] &&
             ycoords[a] == ycoords[c] &&
             zcoords[a] == zcoords[c]))
        return (1);
    return (0);
}

void addobj(void)
{       /* dump out current object we should have all info on */
    Point p;
    Curve c;
    int num[10];

    if(strstr(curobj, "POINT")) {
        p.x = xcoords[0];
        p.y = ycoords[0];
        p.z = zcoords[0];
        addpoint(p);
    }
    else if(strstr(curobj, "LINE") || strstr(curobj, "3DLINE")) {
        if(xcoords[0] == xcoords[1] && ycoords[0] == ycoords[1]
                && zcoords[0] == zcoords[1]) {
            degenerates++;
            return;
        }
        p.x = xcoords[0];
        p.y = ycoords[0];
        p.z = zcoords[0];
        num[0] = addpoint(p);
        p.x = xcoords[1];
        p.y = ycoords[1];
        p.z = zcoords[1];
        num[1] = addpoint(p);
        c.type = GEOLINE;
        c.a = num[0];
        c.b = num[1];
        addcurve(c);
    }
    else if(strstr(curobj, "CIRCLE")) {
        p.x = xcoords[0];
        p.y = ycoords[0];
        p.z = zcoords[0];
        num[0] = addpoint(p);
        p.x = xcoords[0] - floats[0];
        p.y = ycoords[0];
        p.z = zcoords[0];
        num[1] = addpoint(p);
        p.x = xcoords[0] + floats[0];
        p.y = ycoords[0];
        p.z = zcoords[0];
        num[2] = addpoint(p);
        p.x = xcoords[0];
        p.y = ycoords[0] - floats[0];
        p.z = zcoords[0];
        num[3] = addpoint(p);
        p.x = xcoords[0];
        p.y = ycoords[0] + floats[0];
        p.z = zcoords[0];
        num[4] = addpoint(p);
        c.type = GEOCIRCLE;
        c.a = num[2];
        c.b = num[0];
        c.c = num[4];
        addcurve(c);
        c.type = GEOCIRCLE;
        c.a = num[4];
        c.b = num[0];
        c.c = num[1];
        addcurve(c);
        c.type = GEOCIRCLE;
        c.a = num[1];
        c.b = num[0];
        c.c = num[3];
        addcurve(c);
        c.type = GEOCIRCLE;
        c.a = num[3];
        c.b = num[0];
        c.c = num[2];
        addcurve(c);
    }
    else if(strstr(curobj, "ARC")) {
        p.x = xcoords[0];
        p.y = ycoords[0];
        p.z = zcoords[0];
        num[0] = addpoint(p);

        p.x = xcoords[0] + floats[0] * cos(angles[0] * DEG2RAD);
        p.y = ycoords[0] + floats[0] * sin(angles[0] * DEG2RAD);
        p.z = zcoords[0];
        num[1] = addpoint(p);

        p.x = xcoords[0] + floats[0] * cos(angles[1] * DEG2RAD);
        p.y = ycoords[0] + floats[0] * sin(angles[1] * DEG2RAD);
        p.z = zcoords[0];
        num[2] = addpoint(p);

        if((angles[1] - angles[0] > 0 && angles[1] - angles[0] < 180) ||
                (angles[1] - angles[0] < 0 && angles[1] - angles[0] < -180)) {
            c.type = GEOCIRCLE;
            c.a = num[1];
            c.b = num[0];
            c.c = num[2];
            addcurve(c);
        }
        else {
            if(angles[1] - angles[0] > 0) {
                p.x =   xcoords[0] +
                        floats[0] * cos((angles[1] - angles[0]) * 0.5 * DEG2RAD);
                p.y =   ycoords[0] +
                        floats[0] * sin((angles[1] - angles[0]) * 0.5 * DEG2RAD);
            }
            else {
                p.x =   xcoords[0] +
                        floats[0] * cos((angles[0] - angles[1]) * 0.5 * DEG2RAD);
                p.y =   ycoords[0] +
                        floats[0] * sin((angles[0] - angles[1]) * 0.5 * DEG2RAD);
            }
            p.z = zcoords[0];
            num[3] = addpoint(p);
            c.type = GEOCIRCLE;
            c.a = num[1];
            c.b = num[0];
            c.c = num[3];
            addcurve(c);
            c.type = GEOCIRCLE;
            c.a = num[3];
            c.b = num[0];
            c.c = num[2];
            addcurve(c);
        }
    }
    else if(strstr(curobj, "TRACE")) {    /* 2 back-to-back triangles */
        if(checkdegen(0, 1, 2)) {
            degenerates++;
            return;
        }
        /* add triangle 0, 1, 2 */

        if(checkdegen(0, 3, 2)) {
            degenerates++;
            return;
        }
        /* add triangle 0 3 2 */
    }
    else if(strstr(curobj, "SOLID")) {    /* 1 or 2 triangles */
        if(checkdegen(0, 1, 2)) {
            degenerates++;
            return;
        }
        /* add triangle 0, 1, 2 */

        if(xcoords[2] == xcoords[3] && ycoords[2] == ycoords[3]
                && zcoords[2] == zcoords[3])
            return;   /* one triangle was enough... */

        if(checkdegen(0, 3, 2)) {
            degenerates++;
            return;
        }
        /* add triangle 0 3 2 */
    }
    else if(strstr(curobj, "TEXT")) {     /* not implemented for now */
    }
    else if(strstr(curobj, "SHAPE")) {    /* these look very hard */
        printf("SHAPE\n");
    }
    else if(strstr(curobj, "BLOCK")) {    /* these look very hard */
        printf("BLOCK\n");
    }
    else if(strstr(curobj, "ENDBLK")) {   /* these look very hard */
    }
    else if(strstr(curobj, "INSERT")) {   /* these look very hard */
    }
    else if(strstr(curobj, "ATTDEF")) {   /* not implemented for now */
    }
    else if(strstr(curobj, "ATTRIB")) {   /* not implemented for now */
    }
    else if(strstr(curobj, "POLYLINE")) { /* these look fairly hard */
        printf("POLYLINE\n");
    }
    else if(strstr(curobj, "VERTEX")) {   /* these look fairly hard */
        if(ints[0] == 192) {
            p.x = xcoords[0];
            p.y = ycoords[0];
            p.z = zcoords[0];
            num_vert_node[cpt_vert_node] = addpoint(p);
            cpt_vert_node++;
        }
        else if(ints[0] == 128) {
            c.type = GEOLINE;
            c.a = num_vert_node[ints[1]];
            c.b = num_vert_node[ints[2]];
            addcurve(c);
            c.type = GEOLINE;
            c.a = num_vert_node[ints[2]];
            c.b = num_vert_node[ints[3]];
            addcurve(c);
            if(ints[4] == 0) {
                c.type = GEOLINE;
                c.a = num_vert_node[ints[3]];
                c.b = num_vert_node[ints[1]];
                addcurve(c);
            }
            else {
                c.type = GEOLINE;
                c.a = num_vert_node[ints[3]];
                c.b = num_vert_node[ints[4]];
                addcurve(c);
                c.type = GEOLINE;
                c.a = num_vert_node[ints[4]];
                c.b = num_vert_node[ints[1]];
                addcurve(c);
            }
        }
        ints[0] = ints[1] = ints[2] = ints[3] = ints[4] = ints[5] = 0;
    }
    else if(strstr(curobj, "SEQEND")) {   /* these look fairly hard */
    }
    else if(strstr(curobj, "3DFACE")) {   /* 1 or 2 triangles */
#if 0   //removed by David Colignon
        if(checkdegen(0, 1, 2)) {
            degenerates++;
            return;
        }
        /* add triangle 0 1 2 */

        if(xcoords[2] == xcoords[3] && ycoords[2] == ycoords[3]
                && zcoords[2] == zcoords[3])
            return;   /* one triangle was enough... */

        if(checkdegen(0, 3, 2)) {
            degenerates++;
            return;
        }
        /* add triangle 0 3 2 */
#else
        p.x = xcoords[0];
        p.y = ycoords[0];
        p.z = zcoords[0];
        num[0] = addpoint(p);
        p.x = xcoords[1];
        p.y = ycoords[1];
        p.z = zcoords[1];
        num[1] = addpoint(p);
        p.x = xcoords[2];
        p.y = ycoords[2];
        p.z = zcoords[2];
        num[2] = addpoint(p);
        c.type = GEOLINE;
        c.a = num[0];
        c.b = num[1];
        addcurve(c);
        c.type = GEOLINE;
        c.a = num[1];
        c.b = num[2];
        addcurve(c);
        if(xcoords[3] == xcoords[2] &&
                ycoords[3] == ycoords[2] &&
                zcoords[3] == zcoords[2]) {
            c.type = GEOLINE;
            c.a = num[2];
            c.b = num[0];
            addcurve(c);
        }
        else {
            p.x = xcoords[3];
            p.y = ycoords[3];
            p.z = zcoords[3];
            num[3] = addpoint(p);
            c.type = GEOLINE;
            c.a = num[2];
            c.b = num[3];
            addcurve(c);
            c.type = GEOLINE;
            c.a = num[3];
            c.b = num[0];
            addcurve(c);
        }
#endif
    }
    else if(strstr(curobj, "DIMENSION")) {        /* not implemented for now */
    }
    else {
        printf("%s\n",curobj);
    }

}

int getline(void)
{       /* read a group code and the next line from infile */
    fgets(linbuf, BUFSIZE, infile);       /* get a line from .DXF */
    if(feof(infile))
        return (1);
    sscanf(linbuf, "%3d", &groupcode);    /* scan out group code */
    fgets(linbuf, BUFSIZE, infile);       /* get a line from .DXF */
    if(feof(infile))
        return (1);
    return (0);
}
////////////////////////////////////////////////
/// \brief PF_EntityContainer::PF_EntityContainer
////////////////////////////////////////////////
PF_EntityContainer::PF_EntityContainer(PF_EntityContainer *parent, PF_GraphicView *view, bool owner)
    :PF_Entity(parent,view)
{
    autoDelete = owner;
}

PF_EntityContainer::~PF_EntityContainer()
{
    if(autoDelete){
        while(!entities.isEmpty()){
            delete entities.takeFirst();
        }
    }else{
        entities.clear();
    }
}

void PF_EntityContainer::clear()
{
    //qDebug()<<"PF_EntityContainer::clear";
    if(autoDelete){
        while(!entities.isEmpty()){
            delete entities.takeFirst();
        }
    }else{
        entities.clear();
    }
    //qDebug()<<"PF_EntityContainer::clear: OK.";
}

/**
 * @brief 删除被选的实体。这里还有问题，如果是复合实体的话，得把附属
 * 实体删掉吧？
 *
 */
void PF_EntityContainer::clearSelected()
{
    for(int i = entities.size()-1; i >= 0 ;i--){
        auto e = entities.at(i);
        if(e && e->isSelected()){
            delete e;
            entities.removeAt(i);
        }
    }
    emit EntityChanged();
    this->parentPlot()->replot();
}

bool PF_EntityContainer::setSelected(bool select)
{
    if(select){
        for(auto e : entities){
            e->setFlag(PF::FlagSelected);
        }
    }else{
        for(auto e : entities){
            e->delFlag(PF::FlagSelected);
        }
    }
    return true;
}

bool PF_EntityContainer::toggleSelected()
{
    return setSelected(!isSelected());
}

bool PF_EntityContainer::isSelected() const
{
    return isVisible() && getFlag(PF::FlagSelected);
}

unsigned PF_EntityContainer::count() const
{
    return entities.size();
}


/**
 * @brief 返回第一个Entity
 *
 * @return PF_Entity
 */
PF_Entity *PF_EntityContainer::first() const
{
    return entities.first();
}


/**
 * @brief 返回最后一个Entity
 *
 * @return PF_Entity
 */
PF_Entity *PF_EntityContainer::last() const
{
    return entities.last();
}

void PF_EntityContainer::addEntity(PF_Entity *entity)
{
    if(!entity){
        return;
    }

    entities.append(entity);
    //qDebug()<<"PF_EntityContainer::addEntity:size:"<<entities.size();
    /** 导入的时候批量添加，导致tree不断地更新，删除。。。不输出还不知道这个。。。 **/
    emit EntityChanged();
}

/**
 * @brief 添加entity，但是不发出信号。
 *
 * @param entity
 */
void PF_EntityContainer::addEntitySilence(PF_Entity* entity)
{
    if(!entity){
        return;
    }

    entities.append(entity);
}


/**
 * @brief 在Entity列表的尾部添加entity
 *
 * @param entity
 */
void PF_EntityContainer::appendEntity(PF_Entity *entity)
{
    if (!entity)
        return;
    entities.append(entity);
}

/**
 * @brief 在Entity列表的头部添加entity
 *
 * @param entity
 */
void PF_EntityContainer::prependEntity(PF_Entity *entity)
{
    if (!entity) return;
    entities.prepend(entity);
}

void PF_EntityContainer::moveEntity(int index, QList<PF_Entity *> &entList)
{
    if (entList.isEmpty()) return;
    int ci = 0; //current index for insert without invert order
    bool ret, into = false;
    PF_Entity *mid = nullptr;
    if (index < 1) {
        ci = 0;
    } else if (index >= entities.size() ) {
        ci = entities.size() - entList.size();
    } else {
        into = true;
        mid = entities.at(index);
    }

    for (int i = 0; i < entList.size(); ++i) {
        PF_Entity *e = entList.at(i);
        ret = entities.removeOne(e);
        //if e not exist in entities list remove from entList
        if (!ret) {
            entList.removeAt(i);
        }
    }
    if (into) {
        ci = entities.indexOf(mid);
    }

    for(auto e: entList){
        entities.insert(ci++, e);
    }
}


/**
 * @brief 在Entity列表当中插入某个位置的entity
 *
 * @param index
 * @param entity
 */
void PF_EntityContainer::insertEntity(int index, PF_Entity *entity)
{
    if (!entity) return;

    entities.insert(index, entity);
}


/**
 * @brief 移除某个entity
 *
 * @param entity
 * @return bool
 */
bool PF_EntityContainer::removeEntity(PF_Entity *entity)
{
    bool ret;
    ret = entities.removeOne(entity);

    if (autoDelete && ret) {
        delete entity;
    }
    return ret;
}




void PF_EntityContainer::draw(QCPPainter *painter)
{
    if(!(painter && mParentPlot)){
        qDebug()<<Q_FUNC_INFO<<"NULL";
        return;
    }

    /** 有些东西适合绘制在顶层，有些适合绘制在底层，先画面，
        再画线，最后画点**/
    for(int i=0;i < entities.size();++i){

        mParentPlot->drawEntity(painter,entities.at(i));
    }
    for(int i=0;i < entities.size();++i){
        if(entities.at(i)->rtti() != PF::EntityFace)
            mParentPlot->drawEntity(painter,entities.at(i));
    }
}

void PF_EntityContainer::adjustBorders(PF_Entity *entity)
{
    if (entity) {
        // make sure a container is not empty (otherwise the border
        //   would get extended to 0/0):
        if (!entity->isContainer() || entity->count()>0) {
            minV = PF_Vector::minimum(entity->getMin(),minV);
            maxV = PF_Vector::maximum(entity->getMax(),maxV);
        }

        // Notify parents. The border for the parent might
        // also change TODO: Check for efficiency
        //if(parent) {
        //parent->adjustBorders(this);
        //}
    }
}


/**
 * Recalculates the borders of this entity container.
 */
void PF_EntityContainer::calculateBorders() {

    resetBorders();
    for (PF_Entity* e: entities){
        if (e->isVisible() /*&& !(layer && layer->isFrozen())*/) {
            e->calculateBorders();
            adjustBorders(e);
        }
    }

    if (minV.x>maxV.x || minV.x>PF_MAXDOUBLE || maxV.x>PF_MAXDOUBLE
            || minV.x<PF_MINDOUBLE || maxV.x<PF_MINDOUBLE) {

        minV.x = 0.0;
        maxV.x = 0.0;
    }
    if (minV.y>maxV.y || minV.y>PF_MAXDOUBLE || maxV.y>PF_MAXDOUBLE
            || minV.y<PF_MINDOUBLE || maxV.y<PF_MINDOUBLE) {

        minV.y = 0.0;
        maxV.y = 0.0;
    }
}



/**
 * @return The point which is closest to 'coord'
 * (one of the vertexes)
 */
PF_Vector PF_EntityContainer::getNearestEndpoint(const PF_Vector& coord,
                                                 double* dist  )const {

    double minDist = PF_MAXDOUBLE;  // minimum measured distance
    double curDist;                 // currently measured distance
    PF_Vector closestPoint(false);  // closest found endpoint
    PF_Vector point;                // endpoint found

    for (PF_Entity* en: entities){

        if (en->isVisible()
                //&& !en->getParent()->ignoredOnModification()
                ){//no end point for Insert, text, Dim
            point = en->getNearestEndpoint(coord, &curDist);
            if (point.valid && curDist<minDist) {
                closestPoint = point;
                minDist = curDist;
                if (dist) {
                    *dist = minDist;
                }
            }
        }
    }

    return closestPoint;
}



/**
 * @return The point which is closest to 'coord'
 * (one of the vertexes)
 */
PF_Vector PF_EntityContainer::getNearestEndpoint(const PF_Vector& coord,
                                                 double* dist,  PF_Entity** pEntity)const {

    double minDist = PF_MAXDOUBLE;  // minimum measured distance
    double curDist;                 // currently measured distance
    PF_Vector closestPoint(false);  // closest found endpoint
    PF_Vector point;                // endpoint found

    //QListIterator<PF_Entity> it = createIterator();
    //PF_Entity* en;
    //while ( (en = it.current())  ) {
    //    ++it;

    unsigned i0=0;
    for(auto en: entities){
        //if (!en->getParent()->ignoredOnModification() ){//no end point for Insert, text, Dim
        //            std::cout<<"find nearest for entity "<<i0<<std::endl;
        point = en->getNearestEndpoint(coord, &curDist);
        if (point.valid && curDist<minDist) {
            closestPoint = point;
            minDist = curDist;
            if (dist) {
                *dist = minDist;
            }
            if(pEntity){
                *pEntity=en;
            }
        }
        //}
        i0++;
    }

    //    std::cout<<__FILE__<<" : "<<__func__<<" : line "<<__LINE__<<std::endl;
    //    std::cout<<"count()="<<const_cast<PF_EntityContainer*>(this)->count()<<"\tminDist= "<<minDist<<"\tclosestPoint="<<closestPoint;
    //    if(pEntity ) std::cout<<"\t*pEntity="<<*pEntity;
    //    std::cout<<std::endl;
    return closestPoint;
}



PF_Vector PF_EntityContainer::getNearestPointOnEntity(const PF_Vector& coord,
                                                      bool onEntity, double* dist, PF_Entity** entity)const {

    PF_Vector point(false);

    PF_Entity* en = getNearestEntity(coord, dist, PF::ResolveNone);

    if (en && en->isVisible()
            //&& !en->getParent()->ignoredSnap()
            ){
        point = en->getNearestPointOnEntity(coord, onEntity, dist, entity);
    }

    return point;
}



PF_Vector PF_EntityContainer::getNearestCenter(const PF_Vector& coord,
                                               double* dist) const{
    double minDist = PF_MAXDOUBLE;  // minimum measured distance
    double curDist = PF_MAXDOUBLE;  // currently measured distance
    PF_Vector closestPoint(false);  // closest found endpoint
    PF_Vector point;                // endpoint found

    for(auto en: entities){

        if (en->isVisible()
                //&& !en->getParent()->ignoredSnap()
                ){//no center point for spline, text, Dim
            point = en->getNearestCenter(coord, &curDist);
            if (point.valid && curDist<minDist) {
                closestPoint = point;
                minDist = curDist;
            }
        }
    }
    if (dist) {
        *dist = minDist;
    }

    return closestPoint;
}

/** @return the nearest of equidistant middle points of the line. */

PF_Vector PF_EntityContainer::getNearestMiddle(const PF_Vector& coord,
                                               double* dist,
                                               int middlePoints
                                               ) const{
    double minDist = PF_MAXDOUBLE;  // minimum measured distance
    double curDist = PF_MAXDOUBLE;  // currently measured distance
    PF_Vector closestPoint(false);  // closest found endpoint
    PF_Vector point;                // endpoint found

    for(auto en: entities){

        if (en->isVisible()
                //&& !en->getParent()->ignoredSnap()
                ){//no midle point for spline, text, Dim
            point = en->getNearestMiddle(coord, &curDist, middlePoints);
            if (point.valid && curDist<minDist) {
                closestPoint = point;
                minDist = curDist;
            }
        }
    }
    if (dist) {
        *dist = minDist;
    }

    return closestPoint;
}



PF_Vector PF_EntityContainer::getNearestDist(double distance,
                                             const PF_Vector& coord,
                                             double* dist) const{

    PF_Vector point(false);
    PF_Entity* closestEntity;

    closestEntity = getNearestEntity(coord, nullptr, PF::ResolveNone);

    if (closestEntity) {
        point = closestEntity->getNearestDist(distance, coord, dist);
    }

    return point;
}

PF_Vector PF_EntityContainer::getNearestIntersection(const PF_Vector &coord, double *dist)
{
    return PF_Vector{};
}

PF_Vector PF_EntityContainer::getNearestRef(const PF_Vector& coord,
                                            double* dist) const{

    double minDist = PF_MAXDOUBLE;  // minimum measured distance
    double curDist;                 // currently measured distance
    PF_Vector closestPoint(false);  // closest found endpoint
    PF_Vector point;                // endpoint found

    for(auto en: entities){

        if (en->isVisible()) {
            point = en->getNearestRef(coord, &curDist);
            if (point.valid && curDist<minDist) {
                closestPoint = point;
                minDist = curDist;
                if (dist) {
                    *dist = minDist;
                }
            }
        }
    }

    return closestPoint;
}


PF_Vector PF_EntityContainer::getNearestSelectedRef(const PF_Vector& coord,
                                                    double* dist) const{

    double minDist = PF_MAXDOUBLE;  // minimum measured distance
    double curDist;                 // currently measured distance
    PF_Vector closestPoint(false);  // closest found endpoint
    PF_Vector point;                // endpoint found

    for(auto en: entities){

        if (en->isVisible() && en->isSelected() && !en->isParentSelected()) {
            point = en->getNearestSelectedRef(coord, &curDist);
            if (point.valid && curDist<minDist) {
                closestPoint = point;
                minDist = curDist;
                if (dist) {
                    *dist = minDist;
                }
            }
        }
    }

    return closestPoint;
}


/*!
 \brief 计算距离输入点最近的entity以及对应的距离

 \param coord
 \param entity
 \param level
 \param solidDist
 \return double
*/
double PF_EntityContainer::getDistanceToPoint(const PF_Vector& coord,
                                              PF_Entity** entity,
                                              PF::ResolveLevel level,
                                              double solidDist) const{

    // RS_DEBUG->print("PF_EntityContainer::getDistanceToPoint");


    double minDist = PF_MAXDOUBLE;      // minimum measured distance
    double curDist;                     // currently measured distance
    PF_Entity* closestEntity = nullptr;    // closest entity found
    PF_Entity* subEntity = nullptr;

    for(auto e: entities){

        if (e->isVisible()) {
            // RS_DEBUG->print("entity: getDistanceToPoint");
            // RS_DEBUG->print("entity: %d", e->rtti());
            // bug#426, need to ignore Images to find nearest intersections
            if(level==PF::ResolveAllButTextImage /*&& e->rtti()==PF::EntityImage*/) continue;
            curDist = e->getDistanceToPoint(coord, &subEntity, level, solidDist);

            // RS_DEBUG->print("entity: getDistanceToPoint: OK");

            /*
             * By using '<=', we will prefer the *last* item in the container if there are multiple
             * entities that are *exactly* the same distance away, which should tend to be the one
             * drawn most recently, and the one most likely to be visible (as it is also the order
             * that the software draws the entities). This makes a difference when one entity is
             * drawn directly over top of another, and it's reasonable to assume that humans will
             * tend to want to reference entities that they see or have recently drawn as opposed
             * to deeper more forgotten and invisible ones...
             */
            if (curDist<=minDist)
            {
                switch(level){
                case PF::ResolveAll:
                case PF::ResolveAllButTextImage:
                    closestEntity = subEntity;
                    break;
                default:
                    closestEntity = e;
                }
                minDist = curDist;
            }
        }
    }

    if (entity) {
        *entity = closestEntity;
    }
    // RS_DEBUG->print("PF_EntityContainer::getDistanceToPoint: OK");

    return minDist;
}



PF_Entity* PF_EntityContainer::getNearestEntity(const PF_Vector& coord,
                                                double* dist,
                                                PF::ResolveLevel level) const{

    // RS_DEBUG->print("PF_EntityContainer::getNearestEntity");

    PF_Entity* e = nullptr;

    // distance for points inside solids:
    double solidDist = PF_MAXDOUBLE;
    if (dist) {
        solidDist = *dist;
    }

    double d = getDistanceToPoint(coord, &e, level, solidDist);

    if (e && e->isVisible()==false) {
        e = nullptr;
    }

    // if d is negative, use the default distance (used for points inside solids)
    if (dist) {
        *dist = d;
    }
    // RS_DEBUG->print("PF_EntityContainer::getNearestEntity: OK");

    return e;
}



void PF_EntityContainer::move(const PF_Vector& offset) {
    for(auto e: entities){

        e->move(offset);
        //        if (autoUpdateBorders) {
        //            e->moveBorders(offset);
        //        }
    }
    //    if (autoUpdateBorders) {
    //        moveBorders(offset);
    //    }
}



void PF_EntityContainer::rotate(const PF_Vector& center, const double& angle) {
    PF_Vector angleVector(angle);

    for(auto e: entities){
        e->rotate(center, angleVector);
    }
    //    if (autoUpdateBorders) {
    //        calculateBorders();
    //    }
}


void PF_EntityContainer::rotate(const PF_Vector& center, const PF_Vector& angleVector) {

    for(auto e: entities){
        e->rotate(center, angleVector);
    }
    //    if (autoUpdateBorders) {
    //        calculateBorders();
    //    }
}


void PF_EntityContainer::scale(const PF_Vector& center, const PF_Vector& factor) {
    if (fabs(factor.x)>PF_TOLERANCE && fabs(factor.y)>PF_TOLERANCE) {

        for(auto e: entities){
            e->scale(center, factor);
        }
    }
    //    if (autoUpdateBorders) {
    //        calculateBorders();
    //    }
}



void PF_EntityContainer::mirror(const PF_Vector& axisPoint1, const PF_Vector& axisPoint2) {
    if (axisPoint1.distanceTo(axisPoint2)>PF_TOLERANCE) {

        for(auto e: entities){
            e->mirror(axisPoint1, axisPoint2);
        }
    }
}


//void PF_EntityContainer::stretch(const PF_Vector& firstCorner,
//                                 const PF_Vector& secondCorner,
//                                 const PF_Vector& offset) {

//    if (getMin().isInWindow(firstCorner, secondCorner) &&
//            getMax().isInWindow(firstCorner, secondCorner)) {

//        move(offset);
//    } else {

//        for(auto e: entities){
//            e->stretch(firstCorner, secondCorner, offset);
//        }
//    }

// some entitiycontainers might need an update (e.g. RS_Leader):
//    update();
//}



void PF_EntityContainer::moveRef(const PF_Vector& ref,
                                 const PF_Vector& offset) {


    for(auto e: entities){
        e->moveRef(ref, offset);
    }
    //    if (autoUpdateBorders) {
    //        calculateBorders();
    //    }
}


void PF_EntityContainer::moveSelectedRef(const PF_Vector& ref,
                                         const PF_Vector& offset) {


    for(auto e: entities){
        e->moveSelectedRef(ref, offset);
    }
    //    if (autoUpdateBorders) {
    //        calculateBorders();
    //    }
}

void PF_EntityContainer::revertDirection() {
    for(int k = 0; k < entities.size() / 2; ++k) {
        entities.swap(k, entities.size() - 1 - k);
    }

    for(PF_Entity*const entity: entities) {
        entity->revertDirection();
    }
}

QList<PF_Entity *>::const_iterator PF_EntityContainer::begin() const
{
    return entities.begin();
}

QList<PF_Entity *>::const_iterator PF_EntityContainer::end() const
{
    return entities.end();
}

QList<PF_Entity *>::iterator PF_EntityContainer::begin()
{
    return entities.begin();
}

QList<PF_Entity *>::iterator PF_EntityContainer::end()
{
    return entities.end();
}


const QList<PF_Entity*>& PF_EntityContainer::getEntityList()
{
    return entities;
}

QString PF_EntityContainer::toGeoString()
{
    return "";
}

/*!
 \brief 将实体导出为geo格式

 \return bool
*/
bool PF_EntityContainer::exportGeofile()
{
    QStringList qstrList;

    QFile file("D:/model.geo");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    /** 导出所有的点 **/
    for(auto e:entities){
        if(e->rtti() == PF::EntityPoint && e->isVisible()){
            out<<e->toGeoString()<<"\n";
        }
    }
    /** 导出所有的线段 **/
    for(auto e:entities){
        if(e->rtti() == PF::EntityLine && e->isVisible()){
            out<<e->toGeoString()<<"\n";
        }
    }
    /** 导出所有的面 **/
    for(auto e:entities){
        if(e->rtti() == PF::EntityFace && e->isVisible()){
            //            qDebug()<<"export face";
            out<<e->toGeoString()<<"\n";
        }
    }

    file.flush();
    file.close();
    return true;
}

void PF_EntityContainer::doMesh()
{
    PoofeeSay<<tr("Start mesh...");
    exportGeofile();
    int myargn = 3;
    char *myargv[] = {(char*)"gmsh",(char*)"-format",(char*)"msh2"};
    gmsh::initialize(myargn,myargv);
    gmsh::option::setNumber("General.Terminal", 1);
    gmsh::open("D:/model.geo");
    gmsh::model::mesh::generate(2);
    gmsh::write("D:/model.msh");
    //    CMesh* mesh = loadGmsh22("D:/model.msh");
    //    PF_Point** points = (PF_Point**)malloc(mesh->numNode * sizeof (PF_Point*));
    //    for(int i = 0;i < mesh->numNode;++i){
    //        double x = mesh->nodes[i].x;
    //        double y = mesh->nodes[i].y;
    //        points[i] = new PF_Point(this,this->mParentPlot,PF_PointData(PF_Vector(x,y)));
    //        this->addEntity(points[i]);
    //    }
    //    for(int i = 0;i < mesh->numEle;++i){
    //        if(mesh->eles[i].ele_type == TRIANGLE_NODE3){
    //            int n0 = mesh->eles[i].n[0];
    //            int n1 = mesh->eles[i].n[1];
    //            int n2 = mesh->eles[i].n[2];
    //            this->addEntity(new PF_Line(this,this->mParentPlot,points[n0],points[n1]));
    //            this->addEntity(new PF_Line(this,this->mParentPlot,points[n1],points[n2]));
    //            this->addEntity(new PF_Line(this,this->mParentPlot,points[n2],points[n0]));

    //        }
    //    }
    //    this->mParentPlot->replot();
    gmsh::finalize();
    PoofeeSay<<tr("Mesh over...");
}

/**
 * @brief 在顶部恢复的话，应该比较容易，因为掌握着所有的数据。
 *
 * @param map
 * @return bool
 */
bool PF_EntityContainer::fromMap(QVariantMap map)
{
    return true;
}

QVariantMap PF_EntityContainer::toMap()
{
    QVariantMap map;
    QVariantMap points,lines,faces;
    for(auto e : entities){
        switch (e->rtti()) {
        case PF::EntityPoint:
        {
            points.insert(QString("POINT%1").arg(e->index()),e->toMap());
            break;
        }
        case PF::EntityLine:
        {
            lines.insert(QString("LINE%1").arg(e->index()),e->toMap());
            break;
        }
        case PF::EntityFace:
        {
            faces.insert(QString("FACE%1").arg(e->index()),e->toMap());
            break;
        }
        default:
        {
            qDebug()<<"No such entity.";
            break;
        }
        }
    }
    map.insert(PointKey,points);
    map.insert(LineKey,lines);
    map.insert(FaceKey,faces);
    return map;
}

/*!
 \brief 导入DXF文件，这个文件应该是没有face的信息的。这个函数对DXF的
 导入程度是有限的，不完美的。真实的文件应该会比较复杂。

 \param fileName
 \return bool
*/
bool PF_EntityContainer::importDXF(const QString &fileName)
{
    /** 目前假定导入前要删除之前的数据，包括用户建模的数据，也就是不能多次导入。
        主要是因为编号的问题似乎不好解决，无法确定编号是不是存在？？可以这样，导入的时候
        设置一个新的基数作为编号的起始。**/
    Point_T.clear();
    Curve_T.clear();
    nump = 1;
    numc = 1;
    this->clear();

    PoofeeSay<<tr("Start importing DXF file \"%1\"").arg(fileName);
    /** 将QString转换为char，假定路径长度不超过80 **/
    QByteArray ba = fileName.toLatin1();
    //    inname = (char *)malloc(ba.length() + 1);
    memset(inname, 0, ba.length());
    memcpy(inname, ba.data(), ba.length());
    inname[ba.length()] = '\0';

    if(!strchr(inname, '.'))      /* no dot present in filename? */
        strcat(inname, ".dxf");
    if(!(infile = fopen(inname, "r"))) {
        PoofeeSay<<tr("Cannot open input file \"%1\"\n").arg(QString(QLatin1String(inname)));
        return false;
    }

    ints[0] = ints[1] = ints[2] = ints[3] = ints[4] = ints[5] = 0;
    curobj[0] = '\0';     /* not working on any object currently */
    curcolor = 7; /* and it also doesn't have a color yet... */
    max_x = max_y = max_z = -10000000.0;  /* init bounding limits */
    min_x = min_y = min_z = 10000000.0;

find:
    while(!feof(infile)) {        /* run file up to the "ENTITIES" section */
        if(getline())
            goto stopit;
        if(groupcode == 0) {        /* file section mark */
            if(strstr(linbuf, "EOF"))
                goto stopit;
            if(strstr(linbuf, "SECTION")) {
                if(getline())
                    goto stopit;
                if(groupcode != 2)
                    continue;
                if(strstr(linbuf, "ENTITIES"))
                    break;
            }
        }
    }

    while(!feof(infile)) {        /* scan ENTITIES section */
        if(getline())       /* get a group code and a line */
            break;
        if(groupcode < 10) {        /* cardinal group codes */
            switch (groupcode) {
            case 0:  /* start of entity, table, file sep */
                if(strstr(linbuf, "EOF")) {
                    addobj();     /* dump object */
                    goto stopit;
                }
                if(strstr(linbuf, "ENDSEC")) {
                    addobj();     /* dump object */
                    goto find;
                }
                addobj();       /* dump old object */
                curobj[0] = '\0';       /* reset object */
                curcolor = 7;
                strcpy(curobj, linbuf); /* get new */
                break;
            case 1:  /* primary text value for entity (?) */
                break;
            case 2:  /* block name, attribute tag, etc */
            case 3:  /* other names */
            case 4:
                break;
            case 5:  /* entity handle (hex string) */
                break;
            case 6:  /* line type name */
                break;
            case 7:  /* text style name */
                break;
            case 8:  /* layer name */
                break;
            case 9:  /* variable name ID (only in header) */
                break;
            }
        }
        else if(groupcode >= 10 && groupcode < 19) {        /* Some X coord */
            sscanf(linbuf, "%lf", &(xcoords[groupcode - 10]));
            if(xcoords[groupcode - 10] > max_x)
                max_x = xcoords[groupcode - 10];
            if(xcoords[groupcode - 10] < min_x)
                min_x = xcoords[groupcode - 10];
        }
        else if(groupcode >= 20 && groupcode < 29) {        /* Some Y coord */
            sscanf(linbuf, "%lf", &(ycoords[groupcode - 20]));
            if(ycoords[groupcode - 20] > max_y)
                max_y = ycoords[groupcode - 20];
            if(ycoords[groupcode - 20] < min_y)
                min_y = ycoords[groupcode - 20];
        }
        else if(groupcode >= 30 && groupcode < 38) {        /* Some Z coord */
            sscanf(linbuf, "%lf", &(zcoords[groupcode - 30]));
            if(zcoords[groupcode - 30] > max_z)
                max_z = zcoords[groupcode - 30];
            if(zcoords[groupcode - 30] < min_z)
                min_z = zcoords[groupcode - 30];
        }
        else if(groupcode == 38) {  /* entity elevation if nonzero */
        }
        else if(groupcode == 39) {  /* entity thickness if nonzero */
        }
        else if(groupcode >= 40 && groupcode < 49) {        /* misc floats */
            sscanf(linbuf, "%lf", &(floats[groupcode - 40]));
        }
        else if(groupcode == 49) {  /* repeated value groups */
        }
        else if(groupcode >= 50 && groupcode < 59) {        /* misc angles */
            sscanf(linbuf, "%lf", &(angles[groupcode - 50]));
        }
        else if(groupcode == 62) {  /* Color number */
            sscanf(linbuf, "%6d", &curcolor);
        }
        else if(groupcode == 66) {  /* "entities follow" flag */
        }
        else if(groupcode >= 70 && groupcode < 79) {        /* misc ints */
            sscanf(linbuf, "%d", &(ints[groupcode - 70]));
        }
        else if(groupcode == 210 || groupcode == 220 || groupcode == 230) {
            /* X, Y, Z components of extrusion direction */
        }
    }

stopit:
    fclose(infile);

    QMap<int,PF_Point*> ps;
    /** 生成所有的点 **/
    for(std::set<Point>::iterator it = Point_T.begin(); it != Point_T.end(); ++it){
//        qDebug()<<it->num<<" "<<it->x<<" "<<it->y;
        auto p = new PF_Point(this,mParentPlot,PF_Vector(it->x,it->y));
        p->setIndex(it->num);
        ps.insert(it->num,p);
    }
    /** 按照index排序的顺序 **/
    QMapIterator<int,PF_Point*> i(ps);
    while (i.hasNext()) {
        i.next();
        this->addEntitySilence(i.value());
    }
    /** 生成所有的线 **/
    for(std::set<Curve>::iterator it = Curve_T.begin(); it != Curve_T.end(); ++it){
//        qDebug()<<it->num<<" "<<it->a<<" "<<it->b;
        auto l = new PF_Line(this,mParentPlot,ps.value(it->a,nullptr),ps.value(it->b,nullptr));
        l->setIndex(it->num);
        this->addEntitySilence(l);
    }
    emit EntityChanged();
    PoofeeSay<<tr("%1 points, %2 curves imported").arg(Point_T.size()).arg(Curve_T.size());
    PoofeeSay<<tr("End importing DXF file \"%1\"").arg(fileName);
    this->parentPlot()->zoomAuto();
    return true;
}

/*!
 \brief 导入gmsh的geo文件，geo文件其实非常复杂，因为它支持表达式操作。
 所以还只是简单的导入。

 \param fileName
 \return bool
*/
bool PF_EntityContainer::importGeo(const QString &fileName)
{
    PoofeeSay<<tr("Start importing GEO file \"%1\"").arg(fileName);

    PoofeeSay<<tr("End importing GEO file \"%1\"").arg(fileName);
    return true;
}

/*!
 \brief 提供导入文件的接口。

 \param fileName
 \return bool
*/
bool PF_EntityContainer::importCADFile(const QString &fileName)
{
    /** 检查文件类型 **/
    QFileInfo fileInfo(fileName);
    if(fileInfo.suffix().compare("dxf",Qt::CaseInsensitive) == 0){
        importDXF(fileName);
    }else if(fileInfo.suffix().compare("geo",Qt::CaseInsensitive) == 0){
        importGeo(fileName);
    }else{
        PoofeeSay<<tr("Unsupported CAD file!");
    }
    return true;
}

/**
 * @brief 根据点和线的信息生成面
 *
 */
void PF_EntityContainer::buildFace()
{
    /** 为保险起见，先删除所有的面信息 **/

    PolygonDetector polygon_detector;
    /** 先搜集所有的线 **/
    for(int i = entities.size()-1; i >= 0; i--){
        auto e = entities.at(i);
        if(e->rtti() == PF::EntityLine){
            polygon_detector.AddLine(e->getStartpoint().x,e->getStartpoint().y,
                                     e->getEndpoint().x,e->getEndpoint().y);
        }else if(e->rtti() == PF::EntityFace){
            delete e;
            entities.removeAt(i);
        }
    }
    // the lines were loaded, lets detect the polygons
    if (!polygon_detector.DetectPolygons() || !polygon_detector.GetPolygonSet()) {
        PoofeeSay<<tr("Error: Failed to detect the polygons.\n");
        return;
    }
    //simplify the polygon set
    polygon_detector.SimplifyPolygons(0.0);
    /** 绘制生成的线和面 **/
    Point_T.clear();
    Curve_T.clear();
    nump = 1;
    numc = 1;
    this->clear();
    Point p;
    p.z = 0;
    Curve c;
    int num[10];
    PF_Face::face_index = 1;/** 既然删除了所有的面，那么应该把索引重置 **/
    /** 遍历所有的多边形，暂时不支持曲面 **/
    auto polyset = polygon_detector.GetPolygonSet();
    for(int i = 0; i < polyset->size();i++){
        auto poly = polyset->Item(i);
        QList<PF_LineLoop* > loops;
        auto lineloop = new PF_LineLoop();
        for(int j = 0; j < poly->GetVertexCount()-1;j++){
            auto point = poly->GetVertexAt(j);
            p.x = point->GetX();
            p.y = point->GetY();
            num[0] = addpoint(p);
            point = poly->GetVertexAt(j+1);
            p.x = point->GetX();
            p.y = point->GetY();
            num[1] = addpoint(p);
            /** 如果两个有公共线的话，就重复添加了 **/
            c.type = GEOLINE;
            c.a = num[0];
            c.b = num[1];
            num[2]=addcurve(c);
            lineloop->line_index.append(num[2]);
        }
        loops.append(lineloop);
        auto f = new PF_Face(this,mParentPlot,loops);
        this->addEntitySilence(f);
    }
//    for(int i = 0; i < polygon_detector.GetLineCount();i++){
//        auto line = polygon_detector.GetLineSet()->Item(i);
//        p.x = line->GetStartPoint()->GetX();
//        p.y = line->GetStartPoint()->GetY();
//        p.z = 0;
//        num[0] = addpoint(p);
//        p.x = line->GetEndPoint()->GetX();
//        p.y = line->GetEndPoint()->GetY();
//        p.z = 0;
//        num[1] = addpoint(p);
//        c.type = GEOLINE;
//        c.a = num[0];
//        c.b = num[1];
//        addcurve(c);
//    }
    QMap<int,PF_Point*> ps;
    QMap<int,PF_Line*> ls;
    /** 生成所有的点 **/
    for(std::set<Point>::iterator it = Point_T.begin(); it != Point_T.end(); ++it){
//        qDebug()<<it->num<<" "<<it->x<<" "<<it->y;
        auto p = new PF_Point(this,mParentPlot,PF_Vector(it->x,it->y));
        p->setIndex(it->num);
        ps.insert(it->num,p);
    }
    /** 按照index排序的顺序 **/
    QMapIterator<int,PF_Point*> i(ps);
    while (i.hasNext()) {
        i.next();
        this->addEntitySilence(i.value());
    }
    /** 生成所有的线 **/
    for(std::set<Curve>::iterator it = Curve_T.begin(); it != Curve_T.end(); ++it){
//        qDebug()<<it->num<<" "<<it->a<<" "<<it->b;
        auto l = new PF_Line(this,mParentPlot,ps.value(it->a,nullptr),ps.value(it->b,nullptr));
        l->setIndex(it->num);
        ls.insert(it->num,l);
        this->addEntitySilence(l);
    }
    /** 生成面数据。主要的困难在于数据编号不一致。 **/
    for(int i = entities.size()-1; i >= 0; i--){
        auto e = entities.at(i);
        if(e->rtti() == PF::EntityFace){
            dynamic_cast<PF_Face*>(e)->updateLineLoopByIndex(ls);
        }
    }
    // the polygons were detected, lets save them
//    if (!polygon_detector.CreateSVGwithPolygons("line2.svg")) {
//        PoofeeSay<<tr("Error: Failed to crate the SVG with the polygons.\n");
//    }
    /** UI更新 **/
    emit EntityChanged();
    this->parentPlot()->replot();
}

int PF_EntityContainer::index() const
{
    return 0;
}

void PF_EntityContainer::setIndex(int index)
{

}
