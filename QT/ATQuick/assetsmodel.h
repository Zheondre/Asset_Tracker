#ifndef ASSETSMODEL_H
#define ASSETSMODEL_H

//#include <QObject>
#include <QAbstractListModel>

class AssetsModel : public QAbstractListModel
{
    Q_OBJECT

 protected:
    tracker *m_pList

public:
    explicit AssetsModel(QObject *parent = nullptr);

    enum {
     FAV = Qt::UserRole,
     PLOT,
     NAME,
     VALUE,
     MKCP,
     CHANGE,
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    tracker *getList() const;
    virtual void setList(tracker *list);

//signals:
public slots:
    void update(const int, const int);
};

#endif // ASSETSMODEL_H
