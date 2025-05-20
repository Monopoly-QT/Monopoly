#include "mapHandler.h"

void mapInitialize(vector<int> &landCoordinate ,QList<QObject*> &m_mapList ,vector<Land*> land,vector<Player*> player){
    landCoordinate.resize(64);
    landCoordinate[0] = 0;
    landCoordinate[1] = 1;
    landCoordinate[2] = 2;
    landCoordinate[3] = 13;
    landCoordinate[4] = 24;
    landCoordinate[5] = 25;
    landCoordinate[6] = 26;
    landCoordinate[7] = 27;
    landCoordinate[8] = 38;
    landCoordinate[9] = 39;
    landCoordinate[10] = 28;
    landCoordinate[11] = 17;
    landCoordinate[12] = 6;
    landCoordinate[13] = 7;
    landCoordinate[14] = 8;
    landCoordinate[15] = 9;
    landCoordinate[16] = 10;
    landCoordinate[17] = 21;
    landCoordinate[18] = 32;
    landCoordinate[19] = 31;
    landCoordinate[20] = 30;
    landCoordinate[21] = 41;
    landCoordinate[22] = 52;
    landCoordinate[23] = 63;
    landCoordinate[24] = 74;
    landCoordinate[25] = 75;
    landCoordinate[26] = 86;
    landCoordinate[27] = 87;
    landCoordinate[28] = 98;
    landCoordinate[29] = 109;
    landCoordinate[30] = 108;
    landCoordinate[31] = 119;
    landCoordinate[32] = 118;
    landCoordinate[33] = 117;
    landCoordinate[34] = 116;
    landCoordinate[35] = 115;
    landCoordinate[36] = 114;
    landCoordinate[37] = 113;
    landCoordinate[38] = 112;
    landCoordinate[39] = 101;
    landCoordinate[40] = 102;
    landCoordinate[41] = 103;
    landCoordinate[42] = 92;
    landCoordinate[43] = 81;
    landCoordinate[44] = 80;
    landCoordinate[45] = 79;
    landCoordinate[46] = 78;
    landCoordinate[47] = 89;
    landCoordinate[48] = 100;
    landCoordinate[49] = 111;
    landCoordinate[50] = 110;
    landCoordinate[51] = 99;
    landCoordinate[52] = 88;
    landCoordinate[53] = 77;
    landCoordinate[54] = 66;
    landCoordinate[55] = 55;
    landCoordinate[56] = 56;
    landCoordinate[57] = 57;
    landCoordinate[58] = 46;
    landCoordinate[59] = 35;
    landCoordinate[60] = 34;
    landCoordinate[61] = 33;
    landCoordinate[62] = 22;
    landCoordinate[63] = 11;

    int order = 0;
    vector<int> playPos;
    for(int i = 0 ; i < 4 ; i++){
        playPos.push_back(player[i]->getPos());
    }

    for(int i = 0 ; i < 121 ; i++){
        bool exist = false;
        Map *regis;
        for(int j = 0 ; j < 64 ; j++){
            if(i == landCoordinate[j]){
                exist = true;
                order = j;
                break;
            }
        }
        if(exist){
            regis = new Map(true ,to_string(order) , land[order]->getName() ,land[order]->getTranslation(), playPos, land[order]);
            // regis = new Map(true ,to_string(order) , land[order].getName());
        }
        else{
            regis = new Map();
        }
        m_mapList.append(regis);
    }
}

void mapUpdate(vector<int> landCoordinate ,QList<QObject*> &m_mapList ,vector<Land> land,vector<Player> player){
    int order = 0;
    vector<int> playerPos;
    for(int i = 0 ; i < 4 ; i++){
        playerPos.push_back(player[i].getPos());
    }

    for(int i = 0 ; i < 64 ; i++){
        Map *regis = qobject_cast<Map*>(m_mapList[landCoordinate[i]]);
        regis->byPlayoerPosSetVisibility(playerPos,i);
        regis->byLevelSetBuildingVisibility(land[i].getLevel());
        regis->byTypeOrOwnerSetColor(land[i].getType(),land[i].getOwner());
    }
}
