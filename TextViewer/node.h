#ifndef NODE_H
#define NODE_H

#include <QDir>



struct Node
{
    QDir curentDir;
    QDir* parent;
    QList<Node> children;
};

#endif // NODE_H
