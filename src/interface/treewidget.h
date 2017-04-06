#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QTreeWidget>
#include "models/model.h"

class TreeWidget : public QTreeWidget
{
public:
    TreeWidget();

    void addModels(std::vector<Model*> models);
    void addModel(Model *model);
    void removeModels();
    void removeModel(int index);

    void addElement(int modelIndex, Element* element);
    void removeElement(int modelIndex, int elementIndex);

    void addNode(int modelIndex, Node* node);
    //Tem que remover de todos os elementos que ele ocorre
    void removeNode(int modelIndex, int nodeIndex);
};

#endif // TREEWIDGET_H
