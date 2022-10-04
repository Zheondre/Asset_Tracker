

#include <QObject>


#include "tracker.h"

/*
tracker::tracker(StatsType type,tracker* fl) : QObject(nullptr), m_Type(type), favs(fl)
{
     connect(this,SIGNAL(favChanged(asset *obj, int rowIndex)),
    favs,SLOT(addFavorite(asset *obj, int rowIndex)));
}
*/

//QVector<std::shared_ptr<asset>> tracker::favs; //make this a hash map instead ?

tracker::tracker(QObject *parent) : QObject(parent){

    for(int i = 0; i < coins.size(); i++){
        //if new app
         std::shared_ptr<asset> t = std::make_shared<asset>(i, coins[i]);
         //else load from files saved on disk
         assets.append(t);
    }
}


//QVector<std::shared_ptr<asset>> tracker::getStatItems(){ return assets; }

void tracker::updateFavList(std::shared_ptr<asset>obj, int rowIndex){
    if(obj->m_bFav){
        if(!assets.contains(obj))
            assets.append(obj);
    }else{
        if(assets.contains(obj)){
            //if custom update front end
            //emit preItemRemove
            assets.remove( assets.indexOf(obj,0));
            //if custom update front end
            //emit postItemRemove
        }
    }
}


int tracker::getNumStats()
{
    return assets.size();
}
//#ifdef TRUE

  /*
  double tracker::getPrice(int item)
{
    return mItem.at(item).m_sPrice;
}
*/
//#ifdef true
 QString tracker::getFavPrice(int idx) const
{
      if(favs.size() > idx)
         return favs.at(idx)->price;
      else
         return "Err";
}

  QString tracker::getFavName(int idx) const
{
      return "";
}

  QString tracker::getFavUnit(int idx) const
{
      return "";
}

 /*
void tracker::setFavInput(const QString &val, int idx){

    if(favs.at(idx)->m_sInput != val){
        favs.at(idx)->m_sInput = val;
     //send message out to the world about the update
    }
}
*/

bool tracker::getFavFav(int idx) const
{
    if(favs.size() > idx)
        return favs.at(idx)->m_bFav;
    else
        return false;
}


bool tracker::getFavPlot(int idx) const
{
    if(favs.size() > idx)
        return favs.at(idx)->m_bPlot;
    else
        return false;
}


void tracker::setFavFav(bool val, int idx)
{//fav list only show items that are selected
    if(favs.size() > idx){
      favs.at(idx)->m_bFav = val;

      int j = 0, l = 0;

      for(auto i: favs){
          if(i == favs.at(j)){

              for(auto k: assets){
               if(i == k)
                   break;
                j++;
              }

             // emit preItemRemove();

              favs.remove(l);
                break;

             // emit postItemRemove();
          }
          l++;
      }

      emit dataChanged( j, FAV);
    }

}

void tracker::setFavPlot(bool val, int idx)
{
    if(favs.size() > idx)
        favs.at(idx)->m_bPlot = val;
}
// have worker thread call function bellow

void tracker::setFavPrice(const QString& val, bool update, int idx)
{
    if(favs.size() > idx){
        if(favs.at(idx)->price != val){
          favs.at(idx)->price = val;
          if(update)
            emit dataChanged(idx,PRICE);
        }
    }
}

//#endif
  QString tracker::getPrice(int idx) const
{
      if(assets.size() > idx)
         return assets.at(idx)->price;
      else
         return "ERR";
}

  QString tracker::getName(int idx) const
{
    return "";
}

  QString tracker::getUnit(int idx) const
{
    return "";
}

bool tracker::getFav(int idx) const
{
    if(assets.size() > idx)
        return assets.at(idx)->m_bFav;
    else
        return false;
}


bool tracker::getPlot(int idx) const
{
    if(assets.size() > idx)
        return assets.at(idx)->m_bPlot;
    else
        return false;
}

void tracker::setFav(bool val, int idx)
{
    if(assets.size() > idx){
      assets.at(idx)->m_bFav = val;

      if(assets.at(idx)->m_bFav){
          if(!favs.contains(assets.at(idx ))){
              emit preItemAppend();
              favs.append(assets.at(idx));
              emit postItemAppended();
            //emit favChanged(favs.size());
          }
      }else
          if(favs.contains(assets.at(idx))){
              int j  =0;
              for(auto i: favs){
                  if(i == favs.at(j)){
                      emit preItemRemoved(j);
                      favs.remove(j);
                      emit postItemRemoved();
                        break;
                  }
                   j++;
              }

          }
       //emit favchanged(t/f, idx );
      //emit favChanged(this, idx, val);
    }

}

void tracker::setPlot(bool val, int idx)
{
    if(assets.size() > idx)
        assets.at(idx)->m_bPlot = val;
}
// have worker thread call function bellow
void tracker::setPrice(const QString& val, bool update, int idx)
{
    if(assets.size() > idx){
        if(assets.at(idx)->price != val){
          assets.at(idx)->price = val;
          if(update)
            emit dataChanged(idx,PRICE);
        }
    }
}
