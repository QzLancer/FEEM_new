#ifndef PF_VARIABLEDICT_H
#define PF_VARIABLEDICT_H

#include "utils_global.h"

#include <QHash>
#include <QVariant>

class QString;
namespace Utils {
/*!
 \brief 用来保存变量

*/
class FEEM_UTILS_EXPORT PF_VariableDict
{
public:
    PF_VariableDict() = default;

    void clear();

    /*!
     \brief 变量个数

     \return int
    */
    int count() const{
        return variables.count();
    }

    void add(const QString& key, double var);
    void remove(const QString& key);

    QHash<QString, double> const& getVariableDict() const{
        return variables;
    }
    QHash<QString, double>& getVariableDict(){
        return variables;
    }

    double getValue(const QString& key);

private:
    QHash<QString, double> variables;
};
}//namespace Utils
#endif // PF_VARIABLEDICT_H
