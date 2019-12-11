#ifndef PF_ATOMICENTITY_H
#define PF_ATOMICENTITY_H

#include "pf_entity.h"

#include <QString>
//2018-02-11
//by Poofee
/**基本实体类，包括线段，圆弧，椭圆等**/
class PF_AtomicEntity: public PF_Entity
{
    Q_OBJECT
public:
    PF_AtomicEntity(PF_EntityContainer *parent=nullptr, PF_GraphicView* view=nullptr);

    bool isContainer() const override;
    bool isAtomic() const override;

    /**
     * @return Always 1 for atomic entities.
     */
    unsigned count() const override;

    virtual QString toGeoString() = 0;
};

#endif // PF_ATOMICENTITY_H
