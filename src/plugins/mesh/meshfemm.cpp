#include "meshfemm.h"

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <QDebug>

using namespace std;

template <class ForwardIterator>
ForwardIterator PF_unique (ForwardIterator first, ForwardIterator last)
{
    if (first==last) return last;

    ForwardIterator result = first;
    while (++first < last)
    {
        if(*result == *first){
            /** 由于在这里已经到达last了，导致下一次加的时候就超过
             * last了，报错 **/
            while (++first != last) {
//                qDebug()<<*first;
                if(*result != *first){
                    *result = *first;
                    break;
                }
            }
        }else{
            *(++result)=*first;
//            qDebug()<<*first;
        }
        /** 最后一个数是不重复的 **/
//        if (first==last-1){
//            break;
//        }
        /** 最后几个数是重复的 **/
        if (first==last){
            return result;
        }
    }
    return ++result;
}

int next_int(char **start)
{
    int i;
    char *end;

    i = strtol(*start,&end,10);
    *start = end;
    return(i);
}
/*!
 \brief 读入msh2.2版本的分网文件，这个版本的格式比较容易读取。
 格式简要如下：
$MeshFormat
版本号（2.2） 文件类型（0代表ASCII文件） 数据大小
$EndMeshFormat
$Nodes
节点数目
节点编号 x y z
...
$EndNodes
$Elements
单元数目
单元编号 单元类型 标签数 标签1（物理实体编号） 标签2（几何实体编号） ... 节点1 节点2 节点3 ...
...
$EndElements
 \param mshFilename
 \return bool
*/
CMesh::CMesh()
    :numNode(0)
    ,numEle(0)
    ,nodes(nullptr)
    ,eles(nullptr)
    ,edges(nullptr)
{

}

CMesh::~CMesh()
{
    if(nodes)
        delete nodes;
    nodes = nullptr;
    if(eles)
        delete eles;
    eles = nullptr;
}

void CMesh::loadGsh22(const char fn[])
{
    char *ch = (char *)calloc(256,sizeof (char));
    //------------open file----------------------------------
    FILE * fp = nullptr;
    fp = fopen(fn, "r");
    if (fp == nullptr) {
        qDebug() << "Error: openning file!";
        return ;
    }
    while(!feof(fp)){
        fgets(ch, 256, fp);

        if(strstr(ch,"$MeshFormat")){
            double version;
            int file_type;
            int data_size;
            if(fscanf(fp,"%lf %d %d\n",&version,&file_type,&data_size) != 3){
                qDebug()<<"error reading format";
                return ;
            }else{
                qDebug()<<version<<file_type<<data_size;
                if(version > 2.2){
                    qDebug()<<"Can only open gmsh version 2.2 format";
                    return ;
                }
            }
            fgets(ch, 256, fp);
            if(!strstr(ch,"$EndMeshFormat")) {
                printf("$MeshFormat section should end to string $EndMeshFormat:\n%s\n",ch);
            }
        }else if(strstr(ch,"$Nodes")){
            if(fscanf(fp,"%d\n",&numNode) != 1)
            {
                return ;
            }else{
                /**读取节点坐标**/
                nodes = new CNode[numNode];
                int index;
                for(int i = 0;i < numNode;++i){
                    fscanf(fp,"%d %lf %lf %lf\n",&index,&nodes[i].x,&nodes[i].y,&nodes[i].z);
                    //qDebug()<<index<<nodes[i].x<<nodes[i].y<<nodes[i].z;
                }
            }
            fgets(ch, 256, fp);
            if(!strstr(ch,"$EndNodes")) {
                printf("$Node section should end to string $EndNodes:\n%s\n",ch);
            }
        }else if(strstr(ch,"$Elements")){
            int ele_number;
            //    int elm_type;
            int number_of_tags;
            char * chtmp;
            if(fscanf(fp,"%d\n",&numEle) != 1){
                return ;
            }else{
                eles = new CElement[numEle];
                for(int i = 0;i < numEle;++i){
                    chtmp = fgets(ch, 256, fp);
                    ele_number = next_int(&chtmp);
                    eles[i].ele_type = next_int(&chtmp);
                    number_of_tags = next_int(&chtmp);
                    eles[i].physic_tag = next_int(&chtmp);
                    eles[i].geometry_tag = next_int(&chtmp);

                    int element_nodes = 0;
                    switch (eles[i].ele_type) {
                    case 15:
                        element_nodes = 1;
                        break;
                    case 1:
                        element_nodes = 2;
                        break;
                    case 2:
                        element_nodes = 3;
                        break;
                    default:
                        element_nodes = 0;
                        break;
                    }

                    for(int j = 0; j < element_nodes;++j)
                        eles[i].n[j] = next_int(&chtmp)-1;
//                    qDebug()<<eles[i].geometry_tag<<eles[i].physic_tag
//                           <<eles[i].n[0]<<eles[i].n[1]<<eles[i].n[2];

                }
            }
            fgets(ch, 256, fp);
            if(!strstr(ch,"$EndElements")) {
                printf("$Element section should end to string $EndElements:\n%s\n",ch);
            }
        }
    }

    fclose(fp);
    return ;
}


