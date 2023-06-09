#ifndef PF_PREVIEW_H
#define PF_PREVIEW_H
#include "pf_entitycontainer.h"

class PF_Preview : public PF_EntityContainer
{
    Q_OBJECT
public:
    PF_Preview(PF_EntityContainer*parent=nullptr, PF_GraphicView *view=nullptr);
    ~PF_Preview()=default;

    virtual void addEntity(PF_Entity *entity) override;
    void draw(QCPPainter *painter) override;

    virtual PF::EntityType rtti() const override{
        return PF::EntityPreview;
    }
    QString toGeoString() override;
    int index() const override;
    void setIndex(int index) override;
};

#endif // PF_PREVIEW_H
