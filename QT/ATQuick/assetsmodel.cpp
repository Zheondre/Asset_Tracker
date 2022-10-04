#include "assetsmodel.h"

AssetsModel::AssetsModel(QObject *parent)
    : QAbstractListModel{parent}
{

}

int AssetsModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !m_pList)
        return 0;

    return m_pList->getNumSize();
}


void AssetsModel::update(const int pos, const int role){
    //qDebug() << "FcStatsModel: trying dataChanged slot";
    emit dataChanged(index(pos,0), index(pos,0), QVector<int>() << role);
}

QVariant AssetsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    //qDebug() << "Testing getData";

  switch(role){
    case FAV:
        return QVariant(m_pList->getFav(index.row()));
    case PLOT:
        return QVariant(m_pList->getPlot(index.row()));
    case NAME:
        return QVariant(m_pList->getName(index.row()));
    case VALUE:{
        int temp;
         //return QVariant(m_pList->getValue(index.row()));

        temp = m_pList->getValue(index.row());
        return QVariant(temp);
  }
    case MKCP:
       return QVariant(m_pList->getUnit(index.row()));
    case CHANGE:
        return QVariant(m_pList->getForce(index.row()));
    //case FCSTAT_UINPUT:
        //return QVariant(item.getInput());
    }
    return QVariant();
}

bool AssetsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
     //qDebug() << "AssetsModel: Testing setData";

    if(!m_pList)
        return false;

    switch(role){
       case FAV:
        m_pList->setFav(value.toBool(), index.row());
         //emit favDataChanged();
        break;

        case PLOT:
            m_pList->setPlot(value.toBool(), index.row());
        break;
        case NAME:
            //m_pList->setName(value.toString(), index.row());
            break;
        case VALUE:
            //m_pList->setValue(value.toInt(), index.row());
            break;
        case MKCP:
            m_pList->setForce(value.toBool(), index.row());
            break;
        case CHANGE:
             m_pList->setInput(value.toString(), index.row());
             break;
    }

    emit dataChanged(index, index, QVector<int>() << role);
    return true;
}

Qt::ItemFlags AssetsModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> AssetsModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[FAV]   ="fav";
    names[PLOT]  ="plot";
    names[NAME]  ="name";
    names[VALUE] ="value";
    names[MKCP]  ="mkcp";
    names[CHANGE] ="change";

    return names;
}

BaseStats *AssetsModel::getList() const{ return m_pList; }

void AssetsModel::setList(BaseStats *list){

    beginResetModel();

    if(m_pList)
        m_pList->disconnect(this);
/*
    //might not need this ///temp
    if(list){
        switch(list->getStatsType()){
            case BaseStats::StatsType::Sofc:
            break;
            case BaseStats::StatsType::Rws:
            break;
            case BaseStats::StatsType::FcAir:
                m_pList = (FcAirStats*)list;
            break;
            case BaseStats::StatsType::BMS:
            break;
            case BaseStats::StatsType::FcDiags:
            break;
            case BaseStats::StatsType::Custom:
            break;
            case BaseStats::StatsType::Any:
            break;
        }
    }
    // temp temp temp
    */
    m_pList = list;

    if(m_pList){
       //load model list data change notification connections
       connect(m_pList, SIGNAL(dataChanged(const int,const int)), this, SLOT(update(const int, const int)));
    }

    endResetModel();
}
