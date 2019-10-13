#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Core {
namespace Constants {
// Pages
const char PAGE_WELCOME[]          = "Welcome";
const char PAGE_WORK[]             = "Work";
const int  P_PAGE_WELCOME          = 100;
const int  P_PAGE_WORK             = 90;
/** 定义项目中的常量 **/

/** RibbonBar **/
const char RIBBONBAR[]                  = "FEEM.RibbonBar";
/** pages **/
const char P_HOME[]                     = "FEEM.Page.Home";
const char P_DEFINITION[]               = "FEEM.Page.Definition";
const char P_GEOMETRY[]                 = "FEEM.Page.Geometry";
const char P_MATERIAL[]                 = "FEEM.Page.Material";
const char P_MESH[]                     = "FEEM.Page.Mesh";
const char P_SOLVER[]                   = "FEEM.Page.Solver";
const char P_RESULT[]                   = "FEEM.Page.Result";

// Contexts menu
const char C_GLOBAL[]                   = "Global Context";

// Project tree context menu
//const char M_PROJECT_CONTEXT[]          = "Project.Menu.Project";
//const char M_DEFINITION_CONTEXT[]       = "";
//const char M_MATERIAL_CONTEXT[]         = "";
//const char M_GEOMETRY_CONTEXT[]         = "";

/**  actions **/

/** Default groups **/
const char G_DEFAULT_ONE[]              = "FEEM.Group.Default.One";
const char G_DEFAULT_TWO[]              = "FEEM.Group.Default.Two";
const char G_DEFAULT_THREE[]            = "FEEM.Group.Default.Three";

/** RibbonBar groups **/
const char G_HOME[]                     = "FEEM.Group.Home";
const char G_DEFINITION[]               = "FEEM.Group.Definition";
const char G_GEOMETRY[]                 = "FEEM.Group.Geometry";
const char G_MATERIAL[]                 = "FEEM.Group.Material";
const char G_MESH[]                     = "FEEM.Group.Mesh";
const char G_SOLVER[]                   = "FEEM.Group.Solver";
const char G_RESULT[]                   = "FEEM.Group.Result";
/** Home RibbonBar page groups **/
const char G_HOME_PROJECT[]             = "FEEM.Group.Home.Project";
/** Definition RibbonBar page groups **/
const char G_DEFINITION_VARIABLE[]      = "FEEM.Group.Definition.Variable";
}
}
#endif // CONSTANTS_H
