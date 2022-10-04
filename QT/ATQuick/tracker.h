#ifndef TRACKER_H
#define TRACKER_H

#include <QObject>

struct asset {

    QString name, price, date, mkcp;
    bool m_bFav;
    bool m_bPlot;

    int m_npos;

    std::vector< std::pair< std::string, std::string>> history;

    asset(int idx, QString name): name(name), price("0"), mkcp("0")  {
        m_bFav = false; m_bPlot = true; m_npos = idx;
    };

    asset(int idx, QString name, QString price, QString mkcp): name(name), price(price), mkcp(mkcp)  {
        m_bFav = false; m_bPlot = true; m_npos = idx;
    };
};


class tracker: public QObject
{
    Q_OBJECT

    //mutable std::mutex _mtx;
    //QVector<asset*> mItems;

    QVector< std::shared_ptr<asset>> assets, favs;

    inline static const std::vector<QString> coins = {
        "bitcoin",
        "ripple",
        "bitcoin",
        "solana",
        "ethereum"
    };
public:

    enum {
        FAV = Qt::UserRole,
        PLOT,
        NAME,
        PRICE,
        MKCP,
        CHANGE,
    };

    explicit tracker(QObject *parent = nullptr);
    //tracker(StatsType typ);
    tracker(const tracker *);

    // ~tracker(){
    //make sure to destroy all objects in vector
    //m}

    void updateAssets();
    void printAssets();
    int web();

    //static QVector<std::shared_ptr<asset>> m_pfavList;

    //QVector<std::shared_ptr<asset>> getStatItems();

    QString getFavPrice(int idx) const;
    QString getFavName(int idx) const;
    QString getFavUnit(int idx) const;
    bool getFavFav(int idx) const;
    bool getFavPlot(int idx) const;

    void setFavInput(const QString &val, int idx);
    void setFavFav(bool val, int idx);
    void setFavPlot(bool val, int idx);
    void setFavPrice(const QString& val, bool update, int idx);

    QString getPrice(int idx) const;
    QString getName(int idx) const;
    QString getUnit(int idx) const;
    bool getFav(int idx) const;
    bool getPlot(int idx) const;

    void setInput(const QString &val, int idx);
    void setFav(bool val, int idx);
    void setPlot(bool val, int idx);
    void setPrice(const QString& val, bool update, int idx);

    int getNumStats();

public slots:
    void updateFavList(std::shared_ptr<asset>obj, int rowIndex);

 signals:

    void preItemAppend();
    void postItemAppended();
    void preItemRemoved(int index);
    void postItemRemoved();

    void dataChanged(const int rowIndex, const int modelRole);
    void favChanged(const tracker *inst, const int modelRole, const bool val);
    void graphAdded(tracker *inst, int rowIndex);
    void graphRemoved(tracker *inst, int rowIndex);
};


#endif // TRACKER_H
