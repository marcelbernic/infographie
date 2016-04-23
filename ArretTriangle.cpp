#include "ArretTriangle.h"
using namespace app;

ArretTriangle::ArretTriangle(ofVec3f p_pt1, ofVec3f p_pt2, ofVec3f p_pt3, ofVec3f p_pt4, ofVec3f p_pt5,
                             ofVec3f p_pt6, ofVec3f p_pt7, ofVec3f p_pt8){


    pt1 = p_pt1;
    pt2 = p_pt2;
    pt3 = p_pt3;
    pt4 = p_pt4;
    pt5 = p_pt5;
    pt6 = p_pt6;
    pt1Adj = p_pt7;
    pt2Adj = p_pt8;
}

vector<ofVec3f> ArretTriangle::get2Triangles(vector<ArretTriangle> p_vect, ofVec3f p_pt1, ofVec3f p_pt2){
    vector<ofVec3f> ret;
    int index = -1;
    for(int i = 0; i < p_vect.size(); i++){
        if((p_pt1 == p_vect[i].pt1Adj || p_pt1 == p_vect[i].pt2Adj) &&
                (p_pt2 == p_vect[i].pt1Adj || p_pt2 == p_vect[i].pt2Adj)){
            index = i;
            break;

        }

    }

    if(index == -1){
        return ret;
    }

    ret.push_back(p_vect[index].pt1);
    ret.push_back(p_vect[index].pt2);
    ret.push_back(p_vect[index].pt3);
    ret.push_back(p_vect[index].pt4);
    ret.push_back(p_vect[index].pt5);
    ret.push_back(p_vect[index].pt6);

    return ret;

}

ArretTriangle::~ArretTriangle()
{
}

