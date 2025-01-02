#include "StickerSheet.h"
StickerSheet::StickerSheet (const Image &picture, unsigned max){
    max_=max;
    baseP = Image(picture);
    lay.resize(max);
    xCoor.resize(max);
    yCoor.resize(max);
}
StickerSheet::StickerSheet (const StickerSheet &other){
    baseP=other.baseP;
    max_=other.max_;
    lay.resize(max_);
    xCoor.resize(max_);
    yCoor.resize(max_);
    for (int i = 0; i < max_; i++) {
        lay[i]=other.lay[i];
        xCoor[i]=other.xCoor[i];
        yCoor[i]=other.yCoor[i];
    }
}
const StickerSheet & StickerSheet::operator= (const StickerSheet &other){
    if(&other==this){
        return *this;
    }
    baseP.resize(other.baseP.PNG::width(), other.baseP.PNG::height());
    for (int i = 0; i < (int)baseP.PNG::width(); i++) {
        for (int j = 0; j < (int)baseP.PNG::height(); j++) {
            baseP.getPixel(i,j).h=other.baseP.getPixel(i,j).h;
            baseP.getPixel(i,j).s=other.baseP.getPixel(i,j).s;
            baseP.getPixel(i,j).l=other.baseP.getPixel(i,j).l;
        }
    }
    max_=other.max_;
    lay.clear();
    lay.resize(max_);
    xCoor.clear();
    yCoor.clear();
    xCoor.resize(max_);
    yCoor.resize(max_);
    for (int i = 0; i < max_; i++) {
        lay[i]=other.lay[i];
        xCoor[i]=other.xCoor[i];
        yCoor[i]=other.yCoor[i];
    }
    return *this;
}
void StickerSheet::changeMaxStickers (unsigned max){
    max_=max;
    lay.resize(max);
    xCoor.resize(max);
    yCoor.resize(max);
}
int StickerSheet::addSticker (Image &sticker, int x, int y){
    for (int i = 0; i < max_; i++) {
        if (lay[i]==NULL){
            lay[i]=&sticker;
            xCoor[i]=x;
            yCoor[i]=y;
            return i;
        }
    }
    max_=max_+1;
    lay.reserve(max_);
    xCoor.reserve(max_);
    yCoor.reserve(max_);
    lay.push_back(&sticker);
    xCoor.push_back(x);
    yCoor.push_back(y);
    return max_-1;
}
int StickerSheet::setStickerAtLayer (Image &sticker, unsigned layer, int x, int y){
    if(max_<=(int)layer){
        return -1;
    } else{
        lay[layer]=&sticker;
        xCoor[layer]=x;
        yCoor[layer]=y;
    }
    return layer;
}
bool StickerSheet::translate (unsigned index, int x, int y){
    int max=(int)max_;
    if(max<=(int)index||lay[index]==NULL){
        return false;
    }
    xCoor[index]=x;
    yCoor[index]=y;
    return true;
}
void StickerSheet::removeSticker (unsigned index){
    lay[index]=NULL;
    xCoor[index]=0;
    yCoor[index]=0;
}
Image * StickerSheet::getSticker (unsigned index){
    unsigned int max=(unsigned int)max_;
    if(index>max){
        return NULL;
    }
    return lay[index];
}
int StickerSheet::layers () const{
    return lay.size();
}
Image StickerSheet::render () const{
    if(xCoor.size()==0){
        return baseP;
    }
    int widthLarge=xCoor[0];
    int widthSmall=xCoor[0];
    int wS=100;
    int inde=0;
    for(int i:xCoor){
        if(i>widthLarge){
            widthLarge=i;
        }
        if(i<widthSmall){
            widthSmall=i;
            wS=inde;
        }
        inde+=1;
    }
    inde=0;
    int heightLarge=yCoor[0];
    int heightSmall=yCoor[0];
    int hS=100;
    for(int i:yCoor){
        if(i>heightLarge){
            heightLarge=i;
        }
        if(i<heightSmall){
            heightSmall=i;
            hS=inde;
        }
        inde+=1;
    }
    int width=(int)baseP.PNG::width();
    int height=(int)baseP.PNG::height();
    int wid=0;
    int hi=0;
    if(widthSmall<0){
        wid=widthSmall;
        if(width<widthLarge){
           width=widthLarge;
        }
        width=width-widthSmall;
    }else{
        wS=100;
    }
    if(widthLarge>=width){
        width=widthLarge;
    }
    if(heightSmall<0){ 
        hi=heightSmall;
        if(height<heightLarge){
           height=heightLarge;
        }
        height=height-heightSmall;
    }else{
        hS=100;
    }
    if(height<=heightLarge){
        height=heightLarge;
    }
    Image image(width,height);
    image.resize(width,height);
    for (int i = 0; i < (int)baseP.PNG::width(); i++){
        for (int j = 0; j < (int)baseP.PNG::height(); j++){
            image.getPixel(i+abs(wid),j+abs(hi)).h=baseP.getPixel(i,j).h;
            image.getPixel(i+abs(wid),j+abs(hi)).s=baseP.getPixel(i,j).s;
            image.getPixel(i+abs(wid),j+abs(hi)).l=baseP.getPixel(i,j).l;
        }
    }
    for (int w = 0; w < (int)max_; w++) {
        if(lay[w]==NULL){
            continue;
        }
        Image* stick=lay[w];
        if(((int)stick->width()+abs(xCoor[w]))>width){
            width=(int)stick->width()+abs(xCoor[w]);
            if(wS!=100 && wS!=w){
                width+=abs(xCoor[wS]);
            }
        }
        if(((int)stick->height()+abs(yCoor[w]))>height){
            height=(int)stick->height()+abs(yCoor[w]);
            if(hS!=100 && hS!=w){
                height+=abs(yCoor[hS]);
            }
        }
        image.resize(width,height);
        for(int i=0;i<(int)stick->width();++i){
            for(int j=0;j<(int)stick->height();++j){
                if(stick->getPixel(i,j).a==0){
                    continue;
                }
                int newW=i+abs(xCoor[w]);
                int newH=j+abs(yCoor[w]);
                if(wS!=100 && wS!=w){
                    newW+=abs(xCoor[wS]);
                }
                if(hS!=100 && hS!=w){
                    newH+=abs(yCoor[hS]);
                }
                if(xCoor[w]<0){
                    newW=i;
                }
                if(yCoor[w]<0){
                    newH=j;
                }
                image.getPixel(newW,newH).h=stick->getPixel(i,j).h;
                image.getPixel(newW,newH).s=stick->getPixel(i,j).s;
                image.getPixel(newW,newH).l=stick->getPixel(i,j).l;
            }
        }
    }
    return image;
}