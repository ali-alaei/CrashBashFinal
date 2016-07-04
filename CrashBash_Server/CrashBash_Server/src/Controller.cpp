#include "../include/Controller.h"

Controller::Controller(): playerNumbers(2),normalBoxNumbers(8),giftBoxNumbers(3),tntBoxNumbers(5),parser(this->playerNumbers)
{



}
Controller::~Controller()
{
    //dtor
}
void Controller::createPlayers()
{
    players.push_back(Player(80,80));
    players.push_back(Player(1020,698));
}
void Controller::createNormalBoxes()
{
    const int TotalBoxesNums = 16;
    const int BoxShapeLength = 60;
    const int normalBoxNums = 8;
    const int giftBoxNums = 3;
    const int tntBoxNums = 5;
     int x[normalBoxNums];
     int y[normalBoxNums];
    for(int i = 0; i < normalBoxNums; i++)
    {
        x[i] = (rand() %  1081) + 80;
        y[i] = (rand() % 754) + 80;
        int j=0;
        while((j != TotalBoxesNums) &&
              !(((x[i]+BoxShapeLength)<tnts[j].getXPos() ||
                 x[i]>(tnts[j].getXPos()+BoxShapeLength)) &&
                ((y[i]+BoxShapeLength)<tnts[j].getYPos() ||
                 y[i]>(tnts[j].getYPos()+BoxShapeLength)) &&
                ((x[i]+BoxShapeLength)<gifts[j].getXPos() ||
                 x[i]>(gifts[j].getXPos()+BoxShapeLength)) &&
                ((y[i]+BoxShapeLength)<gifts[j].getYPos() ||
                 y[i]>(gifts[j].getYPos()+BoxShapeLength))))
        {
            x[i] = (rand() %  1081) + 80;
            y[i] = (rand() % 754) + 80;
            j++;
        }
    }
    for(int i=0; i<normalBoxNums; i++)
    {
        normals.push_back(NoramlBox(x[i],y[i]));
    }

}
void Controller::createTntBoxes()
{
    const int TotalBoxesNums = 16;
    const int BoxShapeLength = 60;
    const int normalBoxNums = 8;
    const int giftBoxNums = 3;
    const int tntBoxNums = 5;
     int x[tntBoxNums];
     int y[tntBoxNums];
    for(int i = 0; i < tntBoxNums; i++)
    {
        x[i] = (rand() %  1081) + 80;
        y[i] = (rand() % 754) + 80;
        int j=0;
        while((j != TotalBoxesNums) &&
               !(((x[i]+BoxShapeLength)<normals[j].getXPos() ||
                   x[i]>(normals[j].getXPos()+BoxShapeLength)) &&
                  ((y[i]+BoxShapeLength)<normals[j].getYPos() ||
                    y[i]>(normals[j].getYPos()+BoxShapeLength)) &&
                  ((x[i]+BoxShapeLength)<gifts[j].getXPos() ||
                    (x[i]>gifts[j].getXPos()+BoxShapeLength)) &&
                  ((y[i]+BoxShapeLength)<gifts[j].getYPos() ||
                    y[i]>(gifts[j].getYPos()+BoxShapeLength))))
        {
            x[i] = (rand() %  1081) + 80;
            y[i] = (rand() % 754) + 80;
            j++;
        }
    }

    for(int i = 0; i < tntBoxNums; i++)
    {
        tnts.push_back(TntBox(x[i],y[i]));

    }
}
void Controller::createGiftBoxes()
{
    const int TotalBoxesNums = 16;
    const int BoxShapeLength = 60;
    const int normalBoxNums = 8;
    const int giftBoxNums = 3;
    const int tntBoxNums = 5;
     int x[giftBoxNums];
     int y[giftBoxNums];
    for(int i = 0; i < giftBoxNums; i++)
    {
        x[i] = (rand() %  1081) + 80;
        y[i] = (rand() % 754) + 80;
        int j=0;
        while((j != TotalBoxesNums) &&
               !(((x[i]+BoxShapeLength)<normals[j].getXPos() ||
                   (x[i]>normals[j].getXPos()+BoxShapeLength)) &&
                  ((y[i]+BoxShapeLength)<normals[j].getYPos() ||
                    y[i]>(normals[j].getYPos()+BoxShapeLength)) &&
                  ((x[i]+BoxShapeLength)<tnts[j].getXPos() ||
                    (x[i]>tnts[j].getXPos()+BoxShapeLength)) &&
                  ((y[i]+BoxShapeLength)<tnts[j].getYPos() ||
                    y[i]>(tnts[j].getYPos()+BoxShapeLength))))
        {
            x[i] = (rand() %  1081) + 80;
            y[i] = (rand() % 754) + 80;
            j++;
        }
    }
    for(int i = 0; i < this->giftBoxNumbers; i++)
    {
        gifts.push_back(GiftBox(x[i],y[i]));

    }

}

void Controller::run()
{
    createPlayers();
    createNormalBoxes();
    createTntBoxes();
    createGiftBoxes();
    connection.start();
    connection2.start();
    while(true)
    {
        if(connection.haveInQ())
        {
            sf::Packet packet = connection.receivePacket();
            string s;
            packet >>s;
            setWmodelToParser(s);
            parser.deCode(1);
        }
        else if(connection2.haveInQ())
        {
            sf::Packet packet = connection2.receivePacket();
            string s;
            packet >>s;
            setWmodelToParser(s);
            parser.deCode(2);
        }
        setParserGiftBoxNum();

        setParserNormalBoxNum();

        setParserTntBoxNum();

        setParserGiftBoxVector();

        setParserNormalBoxVector();

        setParserTntBoxVector();

        setParserPlayerVector();

        setParserPlayerId();

        setPlayerNormalBoxesNum();

        setPlayerGiftBoxesNum();

        setPlayerTntBoxesNum();

        setPlayerDirection();

        setPlayerGiftBoxes();

        setPlayerTntBoxes();

        setPlayerNormalBoxes();

        setPlayerSpaceKey();

        checkPlayerCollisionToBox();///jadid zadam (az too box rad nashe)

        playerCollisionToWall();///jadid az divar rad nashe

        changePosition();

        playerCollisionToNormalBox();

        playerCollisionToTntBox();

        playerCollisionToGiftBox();

        rebuildTntBox();

        setParserTntBoxVector();

        whoIsWinner();

        parser.code();

        if(parser.ch)
        {
            sf::Packet packet;
            packet <<parser.getWmodel();
            connection.sendPacket(packet);
            connection2.sendPacket(packet);
          //  cout <<parser.getWmodel()<<"\n";
        }


        setZeroToInputs();
    }

}
void Controller::deleteNormalBox()
{
    for(int i=0; i < normals.size(); i++)
    {
         if(normals[i].getDeadOrAlive())
        {
            normals.erase(normals.begin()+i);
            this->normalBoxNumbers--;
            std::cout<<"normalsize"<<normals.size()<<std::endl;
            ///delete from vectors and all functions that work with this box.
            //it should reduce number of normalboxes.
        }

    }

}
void Controller::deleteGiftBox()
{
     for(int i=0; i < gifts.size(); i++)
     {

        if(!gifts[i].getDeadOrAlive())
        {
       std::cout<<"this is deletetntbox"<<std::endl;

            gifts.erase(gifts.begin()+i);
            this->giftBoxNumbers--;
            std::cout<<"tntsize"<<gifts.size()<<std::endl;
       }

     }
}
void Controller::deleteTntBox()
{
        for(int i=0; i < tnts.size(); i++)
        {

             if(!tnts[i].getDeadOrAlive())
            {
            std::cout<<"this is deletetntbox"<<std::endl;
            tnts.erase(tnts.begin()+i);
            this->tntBoxNumbers--;
            std::cout<<"tntsize"<<tnts.size()<<std::endl;


            }

        }





}
void Controller::changePosition()
{
    for(int i=0; i < playerNumbers; i++)
    {

            if(parser.input[i]->up)
            {
                //if(players[i].checkCollisionToBox())
                //{
                    players[i].changePosUp();
                //}
            }

            else if(parser.input[i]->down)
            {
                //if(players[i].checkCollisionToBox())
               // {
                    players[i].changePosDown();
                //}
            }
            else if(parser.input[i]->right)
            {
                //if(players[i].checkCollisionToBox())
                //{
                    players[i].changePosRight();
                //}
            }
            else if(parser.input[i]->left)
            {
                //if(players[i].checkCollisionToBox())
                //{
                    players[i].changePosLeft();
             //   }
            }
            else if(parser.input[i]->right && parser.input[i]->up)
            {
               // if(players[i].checkCollisionToBox())
                //{
                    players[i].changePosUR();
                //}
            }
            else if(parser.input[i]->left && parser.input[i]->up)
            {
                //if(players[i].checkCollisionToBox())
                //{
                    players[i].changePosUL();
                //}
            }
            else if(parser.input[i]->left && parser.input[i]->down)
            {
                //if(players[i].checkCollisionToBox())
                //{
                    players[i].changePosDL();
                //}
            }
            else if(parser.input[i]->right && parser.input[i]->down)
            {
                //if(players[i].checkCollisionToBox())
                //{
                    players[i].changePosDR();
                //}
            }
    }

}
void Controller::whoIsWinner()
{
    if(players[0].getPlayerHealth() == 0)
    {
        parser.setWinner(2); ///means player 2 won the game.
        //exit(1);
    }
    else if(players[1].getPlayerHealth() == 0)
    {
        parser.setWinner(1); ///meas player 1 won the game.
        //exit(1);
    }
}
void Controller::rebuildGiftBox()
{
    if(gifts.size() == 0)
    {
        std::cout<<"this is produce Gifts"<<std::endl;
        createGiftBoxes();

    }
}
void Controller::rebuildNormalBox()
{
    if(normals.size()<2)
    {
        createNormalBoxes();
    }

}


void Controller::rebuildTntBox()
{
    std::cout<<"tnt sizes"<<std::endl;
    std::cout<<tnts.size()<<std::endl;
    if(tnts.size()<3)
    {

        createTntBoxes();

    }


}

void Controller::setPlayerNormalBoxesNum()
{
    for(int i = 0; i < this->playerNumbers; i++)
    {
        players[i].setNormalBoxesNum(normalBoxNumbers);
    }

}
void Controller::setPlayerGiftBoxesNum()
{
    for(int i = 0; i < this->playerNumbers; i++)
    {
        players[i].setGiftBoxesNum(giftBoxNumbers);
    }

}
void Controller::setPlayerTntBoxesNum()
{
    for(int i = 0; i < this->playerNumbers; i++)
    {
        players[i].setTntBoxesNum(tntBoxNumbers);
    }
}

void Controller::setPlayerDirection()
{
    for(int i = 0; i < this->playerNumbers; i++)
    {

        if(parser.input[i]->up)
        {
            players[i].setDirection(1);
        }
        else if(parser.input[i]->right)
        {
            players[i].setDirection(2);
        }
        else if(parser.input[i]->down)
        {
            players[i].setDirection(3);
        }
        else if(parser.input[i]->left)
        {
            players[i].setDirection(4);
        }


    }
}

void Controller::setPlayerGiftBoxes()
{

    for(int i=0; i<this->playerNumbers; i++)
    {
        players[i].setGiftBoxVector(gifts);


    }
}
void Controller::setPlayerTntBoxes()
{
    for(int i=0; i<this->playerNumbers; i++)
    {

        players[i].setTntBoxes(tnts);


    }

}
void Controller::setPlayerNormalBoxes()
{
    for(int i=0; i<this->playerNumbers; i++)
    {

        players[i].setNoramlBoxVector(this->normals);


    }


}
void Controller::setParserGiftBoxNum()
{

    parser.setGiftBoxNum(this->giftBoxNumbers);
}
void Controller::setParserNormalBoxNum()
{

    parser.setNoramlBoxNum(this->normalBoxNumbers);
}
void Controller::setParserTntBoxNum()
{

    parser.setTntBoxNum(this->tntBoxNumbers);
}
void Controller::setParserGiftBoxVector()
{
    parser.setGiftBoxVector(gifts);
}
void Controller::setParserNormalBoxVector()
{
    parser.setNormalBoxVector(normals);
 }
void Controller::setParserTntBoxVector()
{
    std::cout<<"tnts vector size"<<tnts.size()<<std::endl;
    parser.setTntBoxVector(tnts);
}
void Controller::setParserPlayerVector()
{
    parser.setPlayerVector(players);
}
void Controller::playerCollisionToGiftBox()
{
    for(int i=0; i<this->playerNumbers; i++)
    {
        if(players[i].playerCollisionGiftBox())
        {
            int giftType;
            giftType = players[i].earnedBox[i].giftType();

            if(giftType == 1)
            {
                players[i].increasePlayerHealth();

            }
            else if(giftType == 2)
            {

                players[i].increaseSpeed();
            }
            else if(giftType == 3)
            {

                players[i].increaseSpeedRate();
            }
            else if(giftType == 4)
            {
                players[i].increaseThrowRate();

            }
        }
        deleteGiftBox();
    }
}
void Controller::playerCollisionToTntBox()
{
    for(int i=0; i<this->playerNumbers; i++)
        {
            if(players[i].playerCollisionTntBox())
            {
                players[i].decreasePlayerHealth();
                deleteTntBox();
            }
        }
}
void Controller::playerCollisionToNormalBox()
{
    for(int i=0; i<this->playerNumbers; i++)
        {
            if(players[i].ownBox==true)
            {
                players[i].tokenBox->moveCatchBox();
            }

                players[i].throwBox();

                if(players[i].playerBox())
                {
                    players[i].catchBox();
                }

        }
}
/*void Controller::setInputs()
{

    playerInputs.push_back(parser.returnInputs());
}*/
void Controller::setZeroToInputs()
{
    for(int i=0; i<this->playerNumbers; i++)
    {
        parser.input[i]->up=0;
        parser.input[i]->down=0;
        parser.input[i]->left=0;
        parser.input[i]->right=0;
        parser.input[i]->space=0;
    }
}

void Controller::setParserPlayerId()
{
    players[0].setId(1);
    players[1].setId(2);
    parser.setPlayerId(players[0].getId(),players[1].getId());
}

void Controller::setPlayerSpaceKey()
{
    for(int i=0; i<this->playerNumbers; i++)
    {
        players[i].setSpace(parser.input[i]->space);

    }

}
void Controller::setWmodelToParser(string s)
{

    parser.setWmodel(s);
}

void Controller::playerCollisionToWall()
{
    int a=0;
    for(int i=0;i<players.size();i++)
       {
           a=players[i].checkCollisionToWall();

           if(a==1)
           {
                parser.input[i]->up=0;

           }
           else if(a==2)
           {
                parser.input[i]->right=0;

           }

           else if(a==3)
           {
                parser.input[i]->down=0;

           }

           else if(a==4)
           {
                 parser.input[i]->left=0;

           }

        }
}

void Controller::checkPlayerCollisionToBox()
{
    int a;
    for(int i=0;i<players.size();i++)
       {
            a=players[i].checkCollisionToBox();
            if(a==1)
            {
                parser.input[i]->up=0;
            }

            else if(a==2)
            {
                parser.input[i]->right=0;
            }

            else if(a==3)
            {
                parser.input[i]->down=0;
            }

            else if(a==4)
            {
                parser.input[i]->left=0;
            }

       }

}
